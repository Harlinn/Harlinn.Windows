/*
 * Copyright 2020 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#include "tests/Test.h"

#ifdef SK_SUPPORT_PDF

#include "skia/core/SkAnnotation.h"
#include "skia/core/SkCanvas.h"
#include "skia/core/SkFont.h"
#include "skia/core/SkStream.h"
#include "skia/docs/SkPDFDocument.h"

using PDFTag = SkPDF::StructureElementNode;

// Test building a tagged PDF with links.
// Add this to args.gn to output the PDF to a file:
//   extra_cflags = [ "-DSK_PDF_TEST_TAGS_OUTPUT_PATH=\"/tmp/links.pdf\"" ]
DEF_TEST(SkPDF_tagged_links, r) {
    REQUIRE_PDF_DOCUMENT(SkPDF_tagged_links, r);
#ifdef SK_PDF_TEST_TAGS_OUTPUT_PATH
    SkFILEWStream outputStream(SK_PDF_TEST_TAGS_OUTPUT_PATH);
#else
    SkDynamicMemoryWStream outputStream;
#endif

    SkSize pageSize = SkSize::Make(612, 792);  // U.S. Letter

    SkPDF::Metadata metadata;
    metadata.fTitle = "Example Tagged PDF With Links";
    metadata.fCreator = "Skia";
    SkTime::DateTime now;
    SkTime::GetDateTime(&now);
    metadata.fCreation = now;
    metadata.fModified = now;

    // The document tag.
    auto root = std::make_unique<PDFTag>();
    root->fNodeId = 1;
    root->fTypeString = "Document";
    root->fLang = "en-US";

    // A link.
    auto l1 = std::make_unique<PDFTag>();
    l1->fNodeId = 2;
    l1->fTypeString = "Link";
    root->fChildVector.push_back(std::move(l1));

    metadata.fStructureElementTreeRoot = root.get();
    sk_sp<SkDocument> document = SkPDF::MakeDocument(
        &outputStream, metadata);

    SkPaint paint;
    paint.setColor(SK_ColorBLUE);

    SkCanvas* canvas =
            document->beginPage(pageSize.width(),
                                pageSize.height());
    SkFont font(nullptr, 20);

    // The node ID should cover both the text and the annotation.
    SkPDF::SetNodeId(canvas, 2);
    canvas->drawString("Click to visit Google.com", 72, 72, font, paint);
    SkRect linkRect = SkRect::MakeXYWH(
        SkIntToScalar(72), SkIntToScalar(54),
        SkIntToScalar(218), SkIntToScalar(24));
    sk_sp<SkData> url(SkData::MakeWithCString("http://www.google.com"));
    SkAnnotateRectWithURL(canvas, linkRect, url.get());

    document->endPage();
    document->close();
    outputStream.flush();
}

#endif
