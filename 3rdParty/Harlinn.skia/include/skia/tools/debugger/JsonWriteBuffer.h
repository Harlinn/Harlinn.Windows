/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef JsonWriteBuffer_DEFINED
#define JsonWriteBuffer_DEFINED

#include "src/core/SkWriteBuffer.h"

class SkJSONWriter;
class SkPath;
class UrlDataManager;

class JsonWriteBuffer final : public SkWriteBuffer {
public:
    JsonWriteBuffer(SkJSONWriter* writer, UrlDataManager* urlDataManager)
            : fUrlDataManager(urlDataManager), fWriter(writer), fCount(0) {}

    SK_API void writePad32(const void* buffer, size_t bytes) override;
    SK_API void writeByteArray(const void* data, size_t size) override;
    SK_API void writeBool(bool value) override;
    SK_API void writeScalar(SkScalar value) override;
    SK_API void writeScalarArray(const SkScalar* value, uint32_t count) override;
    SK_API void writeInt(int32_t value) override;
    SK_API void writeIntArray(const int32_t* value, uint32_t count) override;
    SK_API void writeUInt(uint32_t value) override;
    SK_API void writeString(const char* value) override;

    SK_API void   writeFlattenable(const SkFlattenable* flattenable) override;
    SK_API void   writeColor(SkColor color) override;
    SK_API void   writeColorArray(const SkColor* color, uint32_t count) override;
    SK_API void   writeColor4f(const SkColor4f& color) override;
    SK_API void   writeColor4fArray(const SkColor4f* color, uint32_t count) override;
    SK_API void   writePoint(const SkPoint& point) override;
    SK_API void   writePointArray(const SkPoint* point, uint32_t count) override;
    SK_API void   writePoint3(const SkPoint3& point) override;
    SK_API void   write(const SkM44&) override;
    SK_API void   writeMatrix(const SkMatrix& matrix) override;
    SK_API void   writeIRect(const SkIRect& rect) override;
    SK_API void   writeRect(const SkRect& rect) override;
    SK_API void   writeRegion(const SkRegion& region) override;
    SK_API void   writePath(const SkPath& path) override;
    SK_API size_t writeStream(SkStream* stream, size_t length) override;
    SK_API void   writeImage(const SkImage*) override;
    SK_API void   writeTypeface(SkTypeface* typeface) override;
    SK_API void   writePaint(const SkPaint& paint) override;

private:
    SK_API void append(const char* type);

    UrlDataManager* fUrlDataManager;
    SkJSONWriter*   fWriter;
    int             fCount;
};

#endif
