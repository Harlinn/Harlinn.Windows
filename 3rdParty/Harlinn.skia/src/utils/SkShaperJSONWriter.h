/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkShaperJSONWriter_DEFINED
#define SkShaperJSONWriter_DEFINED

#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include <skia/core/SkSpan.h>
#include <skia/shaper/SkShaper.h>

class SkJSONWriter;

class SkShaperJSONWriter final : public SkShaper::RunHandler {
public:
    SK_API SkShaperJSONWriter(SkJSONWriter* JSONWriter, const char* utf8, size_t size);

    SK_API void beginLine() override;
    SK_API void runInfo(const RunInfo& info) override;
    SK_API void commitRunInfo() override;

    SK_API Buffer runBuffer(const RunInfo& info) override;

    SK_API void commitRunBuffer(const RunInfo& info) override;

    void commitLine() override {}

    using BreakupCluastersCallback =
            std::function<void(size_t, size_t, uint32_t, uint32_t)>;

    // Break up cluster into a set of ranges for the UTF8, and the glyphIDs.
    SK_API static void BreakupClusters(size_t utf8Begin, size_t utf8End,
                                SkSpan<const uint32_t> clusters,
                                const BreakupCluastersCallback& processMToN);


    using VisualizeClustersCallback =
        std::function<void(size_t, SkSpan<const char>, SkSpan<const SkGlyphID>)>;

    // Gather runs of 1:1 into larger runs, and display M:N as single entries.
    SK_API static void VisualizeClusters(const char utf8[],
                                  size_t utf8Begin, size_t utf8End,
                                  SkSpan<const SkGlyphID> glyphIDs,
                                  SkSpan<const uint32_t> clusters,
                                  const VisualizeClustersCallback& processMToN);

private:
    SK_API void displayMToN(size_t codePointCount,
                     SkSpan<const char> utf8,
                     SkSpan<const SkGlyphID> glyphIDs);

    SkJSONWriter* fJSONWriter;
    std::vector<SkGlyphID> fGlyphs;
    std::vector<SkPoint> fPositions;
    std::vector<uint32_t> fClusters;

    std::string fUTF8;
};

#endif  // SkShaperJSONWriter_DEFINED
