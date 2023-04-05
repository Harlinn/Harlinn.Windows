// Copyright 2019 Google LLC.
#ifndef FontCollection_DEFINED
#define FontCollection_DEFINED

#include <memory>
#include <set>
#include "skia/core/SkFontMgr.h"
#include "skia/core/SkRefCnt.h"
#include "skia/private/SkTHash.h"
#include "skia/paragraph/ParagraphCache.h"
#include "skia/paragraph/TextStyle.h"

namespace skia {
namespace textlayout {

class TextStyle;
class Paragraph;
class FontCollection : public SkRefCnt {
public:
    SK_API FontCollection();

    SK_API size_t getFontManagersCount() const;

    SK_API void setAssetFontManager(sk_sp<SkFontMgr> fontManager);
    SK_API void setDynamicFontManager(sk_sp<SkFontMgr> fontManager);
    SK_API void setTestFontManager(sk_sp<SkFontMgr> fontManager);
    SK_API void setDefaultFontManager(sk_sp<SkFontMgr> fontManager);
    SK_API void setDefaultFontManager(sk_sp<SkFontMgr> fontManager, const char defaultFamilyName[]);
    SK_API void setDefaultFontManager(sk_sp<SkFontMgr> fontManager, const std::vector<SkString>& defaultFamilyNames);

    sk_sp<SkFontMgr> getFallbackManager() const { return fDefaultFontManager; }

    SK_API std::vector<sk_sp<SkTypeface>> findTypefaces(const std::vector<SkString>& familyNames, SkFontStyle fontStyle);

    SK_API sk_sp<SkTypeface> defaultFallback(SkUnichar unicode, SkFontStyle fontStyle, const SkString& locale);
    SK_API sk_sp<SkTypeface> defaultFallback();

    SK_API void disableFontFallback();
    SK_API void enableFontFallback();
    bool fontFallbackEnabled() { return fEnableFontFallback; }

    ParagraphCache* getParagraphCache() { return &fParagraphCache; }

    SK_API void clearCaches();

private:
    SK_API std::vector<sk_sp<SkFontMgr>> getFontManagerOrder() const;

    SK_API sk_sp<SkTypeface> matchTypeface(const SkString& familyName, SkFontStyle fontStyle);

    struct FamilyKey {
        FamilyKey(const std::vector<SkString>& familyNames, SkFontStyle style)
                : fFamilyNames(familyNames), fFontStyle(style) {}

        FamilyKey() {}

        std::vector<SkString> fFamilyNames;
        SkFontStyle fFontStyle;

        bool operator==(const FamilyKey& other) const;

        struct Hasher {
            size_t operator()(const FamilyKey& key) const;
        };
    };

    bool fEnableFontFallback;
    SkTHashMap<FamilyKey, std::vector<sk_sp<SkTypeface>>, FamilyKey::Hasher> fTypefaces;
    sk_sp<SkFontMgr> fDefaultFontManager;
    sk_sp<SkFontMgr> fAssetFontManager;
    sk_sp<SkFontMgr> fDynamicFontManager;
    sk_sp<SkFontMgr> fTestFontManager;

    std::vector<SkString> fDefaultFamilyNames;
    ParagraphCache fParagraphCache;
};
}  // namespace textlayout
}  // namespace skia

#endif  // FontCollection_DEFINED
