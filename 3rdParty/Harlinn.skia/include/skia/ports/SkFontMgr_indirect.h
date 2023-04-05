#pragma once
/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkFontMgr_indirect_DEFINED
#define SkFontMgr_indirect_DEFINED

#include <skia/core/SkFontMgr.h>
#include <skia/core/SkRefCnt.h>
#include <skia/core/SkTypeface.h>
#include <skia/core/SkTypes.h>
#include <skia/ports/SkRemotableFontMgr.h>
#include <skia/private/SkMutex.h>
#include <skia/private/SkOnce.h>
#include <skia/private/SkTArray.h>

class SkData;
class SkFontStyle;
class SkStreamAsset;
class SkString;

class SkFontMgr_Indirect : public SkFontMgr {
public:
    // TODO: The SkFontMgr is only used for createFromStream/File/Data.
    // In the future these calls should be broken out into their own interface
    // with a name like SkFontRenderer.
    SkFontMgr_Indirect(sk_sp<SkFontMgr> impl, sk_sp<SkRemotableFontMgr> proxy)
        : fImpl(std::move(impl)), fProxy(std::move(proxy))
    { }

protected:
    SK_API int onCountFamilies() const override;
    SK_API void onGetFamilyName(int index, SkString* familyName) const override;
    SK_API SkFontStyleSet* onCreateStyleSet(int index) const override;

    SK_API SkFontStyleSet* onMatchFamily(const char familyName[]) const override;

    SK_API SkTypeface* onMatchFamilyStyle(const char familyName[],
                                   const SkFontStyle& fontStyle) const override;

    SK_API SkTypeface* onMatchFamilyStyleCharacter(const char familyName[],
                                            const SkFontStyle&,
                                            const char* bcp47[],
                                            int bcp47Count,
                                            SkUnichar character) const override;

    SK_API sk_sp<SkTypeface> onMakeFromStreamIndex(std::unique_ptr<SkStreamAsset>, int ttcIndex) const override;
    SK_API sk_sp<SkTypeface> onMakeFromStreamArgs(std::unique_ptr<SkStreamAsset> stream,
                                           const SkFontArguments& args) const override;
    SK_API sk_sp<SkTypeface> onMakeFromFile(const char path[], int ttcIndex) const override;
    SK_API sk_sp<SkTypeface> onMakeFromData(sk_sp<SkData>, int ttcIndex) const override;
    SK_API sk_sp<SkTypeface> onLegacyMakeTypeface(const char familyName[], SkFontStyle) const override;

private:
    SK_API SkTypeface* createTypefaceFromFontId(const SkFontIdentity& fontId) const;

    sk_sp<SkFontMgr> fImpl;
    sk_sp<SkRemotableFontMgr> fProxy;

    struct DataEntry {
        uint32_t fDataId;  // key1
        uint32_t fTtcIndex;  // key2
        SkTypeface* fTypeface;  // value: weak ref to typeface

        DataEntry() = default;

        DataEntry(DataEntry&& that) { *this = std::move(that); }
        DataEntry& operator=(DataEntry&& that) {
            if (this != &that) {
                fDataId = that.fDataId;
                fTtcIndex = that.fTtcIndex;
                fTypeface = that.fTypeface;

                SkDEBUGCODE(that.fDataId = SkFontIdentity::kInvalidDataId;)
                SkDEBUGCODE(that.fTtcIndex = 0xbbadbeef;)
                that.fTypeface = nullptr;
            }
            return *this;
        }

        ~DataEntry() {
            if (fTypeface) {
                fTypeface->weak_unref();
            }
        }
    };
    /**
     *  This cache is essentially { dataId: { ttcIndex: typeface } }
     *  For data caching we want a mapping from data id to weak references to
     *  typefaces with that data id. By storing the index next to the typeface,
     *  this data cache also acts as a typeface cache.
     */
    mutable SkTArray<DataEntry> fDataCache;
    mutable SkMutex fDataCacheMutex;

    friend class SkStyleSet_Indirect;
};

#endif
