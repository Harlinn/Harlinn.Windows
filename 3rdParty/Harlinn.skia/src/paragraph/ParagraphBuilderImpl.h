// Copyright 2019 Google LLC.
#ifndef ParagraphBuilderImpl_DEFINED
#define ParagraphBuilderImpl_DEFINED

#include <memory>
#include <stack>
#include <string>
#include <tuple>
#include "skia/paragraph/FontCollection.h"
#include "skia/paragraph/Paragraph.h"
#include "skia/paragraph/ParagraphBuilder.h"
#include "skia/paragraph/ParagraphStyle.h"
#include "skia/paragraph/TextStyle.h"
#include "skia/unicode/SkUnicode.h"

namespace skia {
namespace textlayout {

class ParagraphBuilderImpl : public ParagraphBuilder {
public:
    ParagraphBuilderImpl(const ParagraphStyle& style,
        sk_sp<FontCollection> fontCollection,
        std::unique_ptr<SkUnicode> unicode);

    // Just until we fix all the code; calls icu::make inside
    ParagraphBuilderImpl(const ParagraphStyle& style, sk_sp<FontCollection> fontCollection);

    ~ParagraphBuilderImpl() override;

    // Push a style to the stack. The corresponding text added with AddText will
    // use the top-most style.
    void pushStyle(const TextStyle& style) override;

    // Remove a style from the stack. Useful to apply different styles to chunks
    // of text such as bolding.
    // Example:
    //   builder.PushStyle(normal_style);
    //   builder.AddText("Hello this is normal. ");
    //
    //   builder.PushStyle(bold_style);
    //   builder.AddText("And this is BOLD. ");
    //
    //   builder.Pop();
    //   builder.AddText(" Back to normal again.");
    void pop() override;

    TextStyle peekStyle() override;

    // Adds text to the builder. Forms the proper runs to use the upper-most style
    // on the style_stack.
    void addText(const std::u16string& text) override;

    // Adds text to the builder, using the top-most style on on the style_stack.
    void addText(const char* text) override; // Don't use this one - going away soon
    void addText(const char* text, size_t len) override;

    void addPlaceholder(const PlaceholderStyle& placeholderStyle) override;

    void setParagraphStyle(const ParagraphStyle& style) override;

    // Constructs a SkParagraph object that can be used to layout and paint the text to a SkCanvas.
    std::unique_ptr<Paragraph> Build() override;

    static std::unique_ptr<ParagraphBuilder> make(const ParagraphStyle& style,
                                                  sk_sp<FontCollection> fontCollection,
                                                  std::unique_ptr<SkUnicode> unicode);

    // Just until we fix all the code; calls icu::make inside
    static std::unique_ptr<ParagraphBuilder> make(const ParagraphStyle& style,
                                                  sk_sp<FontCollection> fontCollection);
private:
    void endRunIfNeeded();
    void addPlaceholder(const PlaceholderStyle& placeholderStyle, bool lastOne);

    SkString fUtf8;
    std::stack<TextStyle> fTextStyles;
    SkTArray<Block, true> fStyledBlocks;
    SkTArray<Placeholder, true> fPlaceholders;
    sk_sp<FontCollection> fFontCollection;
    ParagraphStyle fParagraphStyle;

    std::unique_ptr<SkUnicode> fUnicode;
};
}  // namespace textlayout
}  // namespace skia

#endif  // ParagraphBuilderImpl_DEFINED
