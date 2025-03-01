/*
 * Copyright (c) 2016, Alliance for Open Media. All rights reserved
 *
 * This source code is subject to the terms of the BSD 2 Clause License and
 * the Alliance for Open Media Patent License 1.0. If the BSD 2 Clause License
 * was not distributed with this source code in the LICENSE file, you can
 * obtain it at www.aomedia.org/license/software. If the Alliance for Open
 * Media Patent License 1.0 was not distributed with this source code in the
 * PATENTS file, you can obtain it at www.aomedia.org/license/patent.
 */

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <assert.h>

#include "third_party/fastfeat/fast.h"

#include "aom_dsp/aom_dsp_common.h"
#include "aom_dsp/flow_estimation/corner_detect.h"
#include "aom_mem/aom_mem.h"
#include "aom_util/aom_pthread.h"
#include "av1/common/common.h"

#define FAST_BARRIER 18

HAOM_EXPORT size_t av1_get_corner_list_size(void) { return sizeof(CornerList); }

HAOM_EXPORT CornerList *av1_alloc_corner_list(void) {
  CornerList *corners = (CornerList *)aom_calloc(1, sizeof(*corners));
  if (!corners) {
    return NULL;
  }

  corners->valid = false;
#if CONFIG_MULTITHREAD
  pthread_mutex_init(&corners->mutex, NULL);
#endif  // CONFIG_MULTITHREAD
  return corners;
}

static bool compute_corner_list(const YV12_BUFFER_CONFIG *frame, int bit_depth,
                                int downsample_level, CornerList *corners) {
  ImagePyramid *pyr = frame->y_pyramid;
  const int layers =
      aom_compute_pyramid(frame, bit_depth, downsample_level + 1, pyr);

  if (layers < 0) {
    return false;
  }

  // Clamp downsampling ratio base on max number of layers allowed
  // for this frame size
  downsample_level = layers - 1;

  const uint8_t *buf = pyr->layers[downsample_level].buffer;
  int width = pyr->layers[downsample_level].width;
  int height = pyr->layers[downsample_level].height;
  int stride = pyr->layers[downsample_level].stride;

  int *scores = NULL;
  int num_corners;
  xy *const frame_corners_xy = aom_fast9_detect_nonmax(
      buf, width, height, stride, FAST_BARRIER, &scores, &num_corners);
  if (num_corners < 0) return false;

  if (num_corners <= MAX_CORNERS) {
    // Use all detected corners
    for (int i = 0; i < num_corners; i++) {
      corners->corners[2 * i + 0] =
          frame_corners_xy[i].x * (1 << downsample_level);
      corners->corners[2 * i + 1] =
          frame_corners_xy[i].y * (1 << downsample_level);
    }
    corners->num_corners = num_corners;
  } else {
    // There are more than MAX_CORNERS corners avilable, so pick out a subset
    // of the sharpest corners, as these will be the most useful for flow
    // estimation
    int histogram[256];
    av1_zero(histogram);
    for (int i = 0; i < num_corners; i++) {
      assert(FAST_BARRIER <= scores[i] && scores[i] <= 255);
      histogram[scores[i]] += 1;
    }

    int threshold = -1;
    int found_corners = 0;
    for (int bucket = 255; bucket >= 0; bucket--) {
      if (found_corners + histogram[bucket] > MAX_CORNERS) {
        // Set threshold here
        threshold = bucket;
        break;
      }
      found_corners += histogram[bucket];
    }
    assert(threshold != -1 && "Failed to select a valid threshold");

    int copied_corners = 0;
    for (int i = 0; i < num_corners; i++) {
      if (scores[i] > threshold) {
        assert(copied_corners < MAX_CORNERS);
        corners->corners[2 * copied_corners + 0] =
            frame_corners_xy[i].x * (1 << downsample_level);
        corners->corners[2 * copied_corners + 1] =
            frame_corners_xy[i].y * (1 << downsample_level);
        copied_corners += 1;
      }
    }
    assert(copied_corners == found_corners);
    corners->num_corners = copied_corners;
  }

  free(scores);
  free(frame_corners_xy);
  return true;
}

HAOM_EXPORT bool av1_compute_corner_list(const YV12_BUFFER_CONFIG *frame, int bit_depth,
                             int downsample_level, CornerList *corners) {
  assert(corners);

#if CONFIG_MULTITHREAD
  pthread_mutex_lock(&corners->mutex);
#endif  // CONFIG_MULTITHREAD

  if (!corners->valid) {
    corners->valid =
        compute_corner_list(frame, bit_depth, downsample_level, corners);
  }
  bool valid = corners->valid;

#if CONFIG_MULTITHREAD
  pthread_mutex_unlock(&corners->mutex);
#endif  // CONFIG_MULTITHREAD
  return valid;
}

#ifndef NDEBUG
// Check if a corner list has already been computed.
// This is mostly a debug helper - as it is necessary to hold corners->mutex
// while reading the valid flag, we cannot just write:
//   assert(corners->valid);
// This function allows the check to be correctly written as:
//   assert(aom_is_corner_list_valid(corners));
HAOM_EXPORT bool aom_is_corner_list_valid(CornerList *corners) {
  assert(corners);

  // Per the comments in the CornerList struct, we must take this mutex
  // before reading or writing the "valid" flag, and hold it while computing
  // the pyramid, to ensure proper behaviour if multiple threads call this
  // function simultaneously
#if CONFIG_MULTITHREAD
  pthread_mutex_lock(&corners->mutex);
#endif  // CONFIG_MULTITHREAD

  bool valid = corners->valid;

#if CONFIG_MULTITHREAD
  pthread_mutex_unlock(&corners->mutex);
#endif  // CONFIG_MULTITHREAD

  return valid;
}
#endif

HAOM_EXPORT void av1_invalidate_corner_list(CornerList *corners) {
  if (corners) {
#if CONFIG_MULTITHREAD
    pthread_mutex_lock(&corners->mutex);
#endif  // CONFIG_MULTITHREAD
    corners->valid = false;
#if CONFIG_MULTITHREAD
    pthread_mutex_unlock(&corners->mutex);
#endif  // CONFIG_MULTITHREAD
  }
}

HAOM_EXPORT void av1_free_corner_list(CornerList *corners) {
  if (corners) {
#if CONFIG_MULTITHREAD
    pthread_mutex_destroy(&corners->mutex);
#endif  // CONFIG_MULTITHREAD
    aom_free(corners);
  }
}
