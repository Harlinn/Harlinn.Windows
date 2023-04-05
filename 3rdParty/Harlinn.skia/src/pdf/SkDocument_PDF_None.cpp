/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <skia/core/SkCanvas.h>
#include <skia/core/SkData.h>
#include <skia/docs/SkPDFDocument.h>

class SkPDFArray {};

sk_sp<SkDocument> SkPDF::MakeDocument(SkWStream*, const SkPDF::Metadata&) { return nullptr; }

void SkPDF::SetNodeId(SkCanvas* c, int n) {
    c->drawAnnotation({0, 0, 0, 0}, "PDF_Node_Key", SkData::MakeWithCopy(&n, sizeof(n)).get());
}

SkPDF::AttributeList::AttributeList() = default;

SkPDF::AttributeList::~AttributeList() = default;
