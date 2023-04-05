#pragma once
/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkBBHFactory_DEFINED
#define SkBBHFactory_DEFINED

#include <skia/core/SkRect.h>
#include <skia/core/SkRefCnt.h>
#include <skia/core/SkTypes.h>
#include <vector>

class SkBBoxHierarchy : public SkRefCnt {
public:
    struct Metadata {
        bool isDraw;  // The corresponding SkRect bounds a draw command, not a pure state change.
    };

    /**
     * Insert N bounding boxes into the hierarchy.
     */
    virtual void insert(const SkRect[], int N) = 0;
    SK_API virtual void insert(const SkRect[], const Metadata[], int N);

    /**
     * Populate results with the indices of bounding boxes intersecting that query.
     */
    virtual void search(const SkRect& query, std::vector<int>* results) const = 0;

    /**
     * Return approximate size in memory of *this.
     */
    virtual size_t bytesUsed() const = 0;

protected:
    SkBBoxHierarchy() = default;
    SkBBoxHierarchy(const SkBBoxHierarchy&) = delete;
    SkBBoxHierarchy& operator=(const SkBBoxHierarchy&) = delete;
};

class SkBBHFactory {
public:
    /**
     *  Allocate a new SkBBoxHierarchy. Return NULL on failure.
     */
    virtual sk_sp<SkBBoxHierarchy> operator()() const = 0;
    virtual ~SkBBHFactory() {}

protected:
    SkBBHFactory() = default;
    SkBBHFactory(const SkBBHFactory&) = delete;
    SkBBHFactory& operator=(const SkBBHFactory&) = delete;
};

class SkRTreeFactory : public SkBBHFactory {
public:
    SK_API sk_sp<SkBBoxHierarchy> operator()() const override;
};

#endif
