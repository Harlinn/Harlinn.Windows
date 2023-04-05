#pragma once
/*
 * Copyright 2021 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkOrderedFontMgr_DEFINED
#define SkOrderedFontMgr_DEFINED

#include <skia/core/SkFontMgr.h>
#include <vector>
/**
 *  Collects an order list of other font managers, and visits them in order
 *  when a request to find or match is issued.
 *
 *  Note: this explicitly fails on any attempt to Make a typeface: all of
 *  those requests will return null.
 */
class SkOrderedFontMgr : public SkFontMgr {
public:
    SK_API SkOrderedFontMgr();
    SK_API ~SkOrderedFontMgr() override;

    SK_API void append(sk_sp<SkFontMgr>);

protected:
    SK_API int onCountFamilies() const override;
    SK_API void onGetFamilyName(int index, SkString* familyName) const override;
    SK_API SkFontStyleSet* onCreateStyleSet(int index)const override;

    SK_API SkFontStyleSet* onMatchFamily(const char familyName[]) const override;

    SK_API SkTypeface* onMatchFamilyStyle(const char familyName[], const SkFontStyle&) const override;
    SK_API SkTypeface* onMatchFamilyStyleCharacter(const char familyName[], const SkFontStyle&,
                                            const char* bcp47[], int bcp47Count,
                                            SkUnichar character) const override;

    // Note: all of these always return null
    SK_API sk_sp<SkTypeface> onMakeFromData(sk_sp<SkData>, int ttcIndex) const override;
    SK_API sk_sp<SkTypeface> onMakeFromStreamIndex(std::unique_ptr<SkStreamAsset>,
                                            int ttcIndex) const override;
    SK_API sk_sp<SkTypeface> onMakeFromStreamArgs(std::unique_ptr<SkStreamAsset>,
                                           const SkFontArguments&) const override;
    SK_API sk_sp<SkTypeface> onMakeFromFile(const char path[], int ttcIndex) const override;

    SK_API sk_sp<SkTypeface> onLegacyMakeTypeface(const char familyName[], SkFontStyle) const override;

private:
    std::vector<sk_sp<SkFontMgr>> fList;
};

#endif
