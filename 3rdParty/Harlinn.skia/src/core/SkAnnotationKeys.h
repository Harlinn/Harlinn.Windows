/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkAnnotationKeys_DEFINED
#define SkAnnotationKeys_DEFINED

#include <skia/core/SkTypes.h>

class SkAnnotationKeys {
public:
    /**
     *  Returns the canonical key whose payload is a URL
     */
    SK_API static const char* URL_Key();

    /**
     *  Returns the canonical key whose payload is the name of a destination to
     *  be defined.
     */
    SK_API static const char* Define_Named_Dest_Key();

    /**
     *  Returns the canonical key whose payload is the name of a destination to
     *  be linked to.
     */
    SK_API static const char* Link_Named_Dest_Key();
};

#endif
