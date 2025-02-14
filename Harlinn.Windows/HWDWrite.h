#pragma once
#ifndef HARLINN_WINDOWS_HWDWRITE_H_
#define HARLINN_WINDOWS_HWDWRITE_H_
/*
   Copyright 2024-2025 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <HWGraphics.h>

namespace Harlinn::Windows::Graphics::DirectWrite
{
    class FontFileStream;
    /// <summary>
    /// Handles loading font file resources of a particular type from a font file reference key into a font file stream object.
    /// </summary>
    class FontFileLoader : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFileLoader, Unknown, IDWriteFontFileLoader, IUnknown )

        HW_EXPORT void CreateStreamFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileStream** fontFileStream ) const;
        HW_EXPORT FontFileStream CreateStreamFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize ) const;
    };

    /// <summary>
    /// A built-in implementation of the IDWriteFontFileLoader interface, that 
    /// operates on local font files and exposes local font file information 
    /// from the font file reference key. Font file references created using 
    /// CreateFontFileReference use this font file loader.
    /// </summary>
    class LocalFontFileLoader : public FontFileLoader
    {
    public:
        typedef FontFileLoader Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( LocalFontFileLoader, FontFileLoader, IDWriteLocalFontFileLoader, IDWriteFontFileLoader )

        HW_EXPORT void GetFilePathLengthFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, UINT32* filePathLength ) const;
        HW_EXPORT UINT32 GetFilePathLengthFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize ) const;

        HW_EXPORT void GetFilePathFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, WCHAR* filePath, UINT32 filePathSize ) const;
        HW_EXPORT WideString GetFilePathFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize ) const;

        HW_EXPORT void GetLastWriteTimeFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, FILETIME* lastWriteTime ) const;
        HW_EXPORT FILETIME GetLastWriteTimeFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize ) const;
    };

    /// <summary>
    /// Loads font file data from a custom font file loader.
    /// </summary>
    class FontFileStream : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFileStream, Unknown, IDWriteFontFileStream, IUnknown )

        HW_EXPORT void ReadFileFragment( void const** fragmentStart, UINT64 fileOffset, UINT64 fragmentSize, void** fragmentContext ) const;
        HW_EXPORT void ReleaseFileFragment( void* fragmentContext ) const;

        HW_EXPORT void GetFileSize( UINT64* fileSize ) const;
        HW_EXPORT UINT64 GetFileSize( ) const;

        HW_EXPORT void GetLastWriteTime( UINT64* lastWriteTime ) const;
        HW_EXPORT UINT64 GetLastWriteTime( ) const;
    };

    /// <summary>
    /// Represents a font file. Applications such as font managers or font viewers can call 
    /// FontFile::Analyze to find out if a particular file is a font file, and whether it 
    /// is a font type that is supported by the font system.
    /// </summary>
    class FontFile : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFile, Unknown, IDWriteFontFile, IUnknown )

        HW_EXPORT void GetReferenceKey( void const** fontFileReferenceKey, UINT32* fontFileReferenceKeySize ) const;
        HW_EXPORT void GetLoader( IDWriteFontFileLoader** fontFileLoader ) const;
        HW_EXPORT FontFileLoader GetLoader( ) const;
        HW_EXPORT void Analyze( BOOL* isSupportedFontType, DWRITE_FONT_FILE_TYPE* fontFileType, DWRITE_FONT_FACE_TYPE* fontFaceType, UINT32* numberOfFaces ) const;
        HW_EXPORT void Analyze( BOOL& isSupportedFontType, DWRITE_FONT_FILE_TYPE& fontFileType, DWRITE_FONT_FACE_TYPE& fontFaceType, UINT32& numberOfFaces ) const;
        HW_EXPORT void Analyze( BOOL& isSupportedFontType, DWRITE_FONT_FILE_TYPE& fontFileType, UINT32& numberOfFaces ) const;
    };


    /// <summary>
    /// Represents text rendering settings such as ClearType level, enhanced contrast, 
    /// and gamma correction for glyph rasterization and filtering.
    /// </summary>
    class RenderingParams : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( RenderingParams, Unknown, IDWriteRenderingParams, IUnknown )

        HW_EXPORT FLOAT GetGamma( ) const;
        HW_EXPORT FLOAT GetEnhancedContrast( ) const;
        HW_EXPORT FLOAT GetClearTypeLevel( ) const;
        HW_EXPORT DWRITE_PIXEL_GEOMETRY GetPixelGeometry( ) const;
        HW_EXPORT DWRITE_RENDERING_MODE GetRenderingMode( ) const;
    };

    



    /// <summary>
    /// Exposes various font data such as metrics, names, and glyph outlines. 
    /// It contains font face type, appropriate file references, and face identification data.
    /// </summary>
    class FontFace : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFace, Unknown, IDWriteFontFace, IUnknown )

        HW_EXPORT DWRITE_FONT_FACE_TYPE GetType( ) const;
        HW_EXPORT void GetFiles( _Inout_ UINT32* numberOfFiles, IDWriteFontFile** fontFiles ) const;
        HW_EXPORT UINT32 GetNumberOfFiles( ) const;
        HW_EXPORT std::shared_ptr< std::vector<FontFile> > GetFiles( ) const;

        HW_EXPORT UINT32 GetIndex( ) const;
        HW_EXPORT DWRITE_FONT_SIMULATIONS GetSimulations( ) const;
        HW_EXPORT BOOL IsSymbolFont( ) const;
        HW_EXPORT void GetMetrics( DWRITE_FONT_METRICS* fontFaceMetrics ) const;
        HW_EXPORT void GetMetrics( DWRITE_FONT_METRICS& fontFaceMetrics ) const;
        HW_EXPORT UINT16 GetGlyphCount( ) const;
        HW_EXPORT void GetDesignGlyphMetrics( UINT16 const* glyphIndices, UINT32 glyphCount, DWRITE_GLYPH_METRICS* glyphMetrics, BOOL isSideways = FALSE ) const;
        HW_EXPORT void GetGlyphIndices( UINT32 const* codePoints, UINT32 codePointCount, UINT16* glyphIndices ) const;
        HW_EXPORT void TryGetFontTable( UINT32 openTypeTableTag, const void** tableData, UINT32* tableSize, void** tableContext, BOOL* exists ) const;
        HW_EXPORT void ReleaseFontTable( void* tableContext ) const;
        HW_EXPORT void GetGlyphRunOutline( FLOAT emSize, UINT16 const* glyphIndices, FLOAT const* glyphAdvances, DWRITE_GLYPH_OFFSET const* glyphOffsets, UINT32 glyphCount, BOOL isSideways, BOOL isRightToLeft, IDWriteGeometrySink* geometrySink ) const;
        HW_EXPORT void GetRecommendedRenderingMode( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MEASURING_MODE measuringMode, IDWriteRenderingParams* renderingParams, DWRITE_RENDERING_MODE* renderingMode ) const;
        HW_EXPORT DWRITE_RENDERING_MODE GetRecommendedRenderingMode( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MEASURING_MODE measuringMode, IDWriteRenderingParams* renderingParams ) const;

        HW_EXPORT void GetGdiCompatibleMetrics( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_FONT_METRICS* fontFaceMetrics ) const;
        HW_EXPORT void GetGdiCompatibleGlyphMetrics( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural, UINT16 const* glyphIndices, UINT32 glyphCount, DWRITE_GLYPH_METRICS* glyphMetrics, BOOL isSideways = FALSE ) const;
    };

    class FontFileEnumerator;
    /// <summary>
    /// Used to construct a collection of fonts given a particular type of key.
    /// </summary>
    class FontCollectionLoader : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontCollectionLoader, Unknown, IDWriteFontCollectionLoader, IUnknown )

        HW_EXPORT void CreateEnumeratorFromKey( IDWriteFactory* factory, void const* collectionKey, UINT32 collectionKeySize, IDWriteFontFileEnumerator** fontFileEnumerator ) const;
        HW_EXPORT FontFileEnumerator CreateEnumeratorFromKey( IDWriteFactory* factory, void const* collectionKey, UINT32 collectionKeySize ) const;
    };

    /// <summary>
    /// Encapsulates a collection of font files. The font system uses this 
    /// interface to enumerate font files when building a font collection.
    /// </summary>
    class FontFileEnumerator : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFileEnumerator, Unknown, IDWriteFontFileEnumerator, IUnknown )

        HW_EXPORT void MoveNext( BOOL* hasCurrentFile ) const;
        HW_EXPORT bool MoveNext( ) const;

        HW_EXPORT void GetCurrentFontFile( IDWriteFontFile** fontFile ) const;
        HW_EXPORT FontFile GetCurrentFontFile( ) const;
    };


    /// <summary>
    /// Represents a collection of strings indexed by locale name.
    /// </summary>
    class LocalizedStrings : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( LocalizedStrings, Unknown, IDWriteLocalizedStrings, IUnknown )

        HW_EXPORT UINT32 GetCount( ) const;
        HW_EXPORT void FindLocaleName( WCHAR const* localeName, UINT32* index, BOOL* exists ) const;
        HW_EXPORT bool FindLocaleName( WCHAR const* localeName, UINT32* index ) const;

        HW_EXPORT void GetLocaleNameLength( UINT32 index, UINT32* length ) const;
        HW_EXPORT UINT32 GetLocaleNameLength( UINT32 index ) const;

        HW_EXPORT void GetLocaleName( UINT32 index, WCHAR* localeName, UINT32 size ) const;
        HW_EXPORT WideString GetLocaleName( UINT32 index ) const;

        HW_EXPORT void GetStringLength( UINT32 index, UINT32* length ) const;
        HW_EXPORT UINT32 GetStringLength( UINT32 index ) const;

        HW_EXPORT void GetString( UINT32 index, WCHAR* stringBuffer, UINT32 size ) const;
        HW_EXPORT WideString GetString( UINT32 index ) const;
    };

    class FontFamily;
    class Font;
    /// <summary>
    /// An object that encapsulates a set of fonts, such as the set of 
    /// fonts installed on the system, or the set of fonts in a particular 
    /// directory. The font collection API can be used to discover what font 
    /// families and fonts are available, and to obtain some metadata about the fonts.
    /// </summary>
    class FontCollection : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontCollection, Unknown, IDWriteFontCollection, IUnknown )

        HW_EXPORT UINT32 GetFontFamilyCount( ) const;
        HW_EXPORT void GetFontFamily( UINT32 index, IDWriteFontFamily** fontFamily ) const;
        HW_EXPORT FontFamily GetFontFamily( UINT32 index ) const;
        HW_EXPORT std::vector<FontFamily> GetFontFamilies( ) const;

        HW_EXPORT void FindFamilyName( WCHAR const* familyName, UINT32* index, BOOL* exists ) const;
        HW_EXPORT bool FindFamilyName( WCHAR const* familyName, UINT32* index ) const;

        HW_EXPORT void GetFontFromFontFace( IDWriteFontFace* fontFace, IDWriteFont** font ) const;
        HW_EXPORT Font GetFontFromFontFace( IDWriteFontFace* fontFace ) const;
    };

    /// <summary>
    /// Represents a list of fonts.
    /// </summary>
    class FontList : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontList, Unknown, IDWriteFontList, IUnknown )

        HW_EXPORT void GetFontCollection( IDWriteFontCollection** fontCollection ) const;
        HW_EXPORT FontCollection GetFontCollection( ) const;
        HW_EXPORT UINT32 GetFontCount( ) const;
        HW_EXPORT void GetFont( UINT32 index, IDWriteFont** font ) const;
        HW_EXPORT Font GetFont( UINT32 index ) const;
    };

    /// <summary>
    /// Represents a family of related fonts.
    /// </summary>
    class FontFamily : public FontList
    {
    public:
        typedef FontList Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFamily, FontList, IDWriteFontFamily, IDWriteFontList )

        HW_EXPORT void GetFamilyNames( IDWriteLocalizedStrings** names ) const;
        HW_EXPORT LocalizedStrings GetFamilyNames( ) const;

        HW_EXPORT void GetFirstMatchingFont( DWRITE_FONT_WEIGHT  weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style, IDWriteFont** matchingFont ) const;
        HW_EXPORT Font GetFirstMatchingFont( DWRITE_FONT_WEIGHT  weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style ) const;

        HW_EXPORT void GetMatchingFonts( DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style, IDWriteFontList** matchingFonts ) const;
        HW_EXPORT FontList GetMatchingFonts( DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style ) const;
    };

    /// <summary>
    /// Represents a physical font in a font collection. This interface is used to create 
    /// font faces from physical fonts, or to retrieve information such as font face 
    /// metrics or face names from existing font faces.
    /// </summary>
    class Font : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Font, Unknown, IDWriteFont, IUnknown )

        HW_EXPORT void GetFontFamily( IDWriteFontFamily** fontFamily ) const;
        HW_EXPORT FontFamily GetFontFamily( ) const;
        HW_EXPORT DWRITE_FONT_WEIGHT GetWeight( ) const;
        HW_EXPORT DWRITE_FONT_STRETCH GetStretch( ) const;
        HW_EXPORT DWRITE_FONT_STYLE GetStyle( ) const;
        HW_EXPORT bool IsSymbolFont( ) const;
        HW_EXPORT void GetFaceNames( IDWriteLocalizedStrings** names ) const;
        HW_EXPORT LocalizedStrings GetFaceNames( ) const;
        HW_EXPORT void GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_ID informationalStringID, IDWriteLocalizedStrings** informationalStrings, BOOL* exists ) const;
        HW_EXPORT DWRITE_FONT_SIMULATIONS GetSimulations( ) const;
        HW_EXPORT void GetMetrics( DWRITE_FONT_METRICS* fontMetrics ) const;
        HW_EXPORT void HasCharacter( UINT32 unicodeValue, BOOL* exists ) const;
        HW_EXPORT bool HasCharacter( UINT32 unicodeValue ) const;
        HW_EXPORT void CreateFontFace( IDWriteFontFace** fontFace ) const;
        HW_EXPORT FontFace CreateFontFace( ) const;
    };


    class InlineObject;
    /// <summary>
    /// The TextFormat class describes the font and paragraph properties 
    /// used to format text, and it describes locale information.
    /// </summary>
    class TextFormat : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextFormat, Unknown, IDWriteTextFormat, IUnknown )

        HW_EXPORT void SetTextAlignment( DWRITE_TEXT_ALIGNMENT textAlignment ) const;
        HW_EXPORT void SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment ) const;
        HW_EXPORT void SetWordWrapping( DWRITE_WORD_WRAPPING wordWrapping ) const;
        HW_EXPORT void SetReadingDirection( DWRITE_READING_DIRECTION readingDirection ) const;
        HW_EXPORT void SetFlowDirection( DWRITE_FLOW_DIRECTION flowDirection ) const;
        HW_EXPORT void SetIncrementalTabStop( FLOAT incrementalTabStop ) const;
        HW_EXPORT void SetTrimming( DWRITE_TRIMMING const* trimmingOptions, IDWriteInlineObject* trimmingSign ) const;
        HW_EXPORT void SetLineSpacing( DWRITE_LINE_SPACING_METHOD lineSpacingMethod, FLOAT lineSpacing, FLOAT baseline ) const;
        HW_EXPORT DWRITE_TEXT_ALIGNMENT GetTextAlignment( ) const;
        HW_EXPORT DWRITE_PARAGRAPH_ALIGNMENT GetParagraphAlignment( ) const;
        HW_EXPORT DWRITE_WORD_WRAPPING GetWordWrapping( ) const;
        HW_EXPORT DWRITE_READING_DIRECTION GetReadingDirection( ) const;
        HW_EXPORT DWRITE_FLOW_DIRECTION GetFlowDirection( ) const;
        HW_EXPORT FLOAT GetIncrementalTabStop( ) const;
        HW_EXPORT void GetTrimming( DWRITE_TRIMMING* trimmingOptions, IDWriteInlineObject** trimmingSign ) const;
        HW_EXPORT InlineObject GetTrimming( DWRITE_TRIMMING& trimmingOptions ) const;
        HW_EXPORT void GetLineSpacing( DWRITE_LINE_SPACING_METHOD* lineSpacingMethod, FLOAT* lineSpacing, FLOAT* baseline ) const;
        HW_EXPORT void GetFontCollection( IDWriteFontCollection** fontCollection ) const;
        HW_EXPORT FontCollection GetFontCollection( ) const;
        HW_EXPORT UINT32 GetFontFamilyNameLength( ) const;
        HW_EXPORT void GetFontFamilyName( WCHAR* fontFamilyName, UINT32 nameSize ) const;
        HW_EXPORT WideString GetFontFamilyName( ) const;
        HW_EXPORT DWRITE_FONT_WEIGHT GetFontWeight( ) const;
        HW_EXPORT DWRITE_FONT_STYLE GetFontStyle( ) const;
        HW_EXPORT DWRITE_FONT_STRETCH GetFontStretch( ) const;
        HW_EXPORT FLOAT GetFontSize( ) const;
        HW_EXPORT UINT32 GetLocaleNameLength( ) const;
        HW_EXPORT void GetLocaleName( WCHAR* localeName, UINT32 nameSize ) const;
        HW_EXPORT WideString GetLocaleName( ) const;
    };


    

    /// <summary>
    /// Represents a font typography setting.
    /// </summary>
    class Typography : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Typography, Unknown, IDWriteTypography, IUnknown )

        HW_EXPORT void AddFontFeature( DWRITE_FONT_FEATURE fontFeature ) const;
        HW_EXPORT void AddFontFeatures( std::shared_ptr< std::vector<DWRITE_FONT_FEATURE> > fontFeatures ) const;
        HW_EXPORT UINT32 GetFontFeatureCount( ) const;
        HW_EXPORT void GetFontFeature( UINT32 fontFeatureIndex, DWRITE_FONT_FEATURE* fontFeature ) const;
        HW_EXPORT DWRITE_FONT_FEATURE GetFontFeature( UINT32 fontFeatureIndex ) const;
        HW_EXPORT std::vector<DWRITE_FONT_FEATURE> GetFontFeatures( ) const;
    };

    /// <summary>
    /// Implemented by the text analyzer's client to provide text to the analyzer. 
    /// It allows the separation between the logical view of text as a continuous 
    /// stream of characters identifiable by unique text positions, and the actual 
    /// memory layout of potentially discrete blocks of text in the client's 
    /// backing store.
    /// </summary>
    class TextAnalysisSource : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextAnalysisSource, Unknown, IDWriteTextAnalysisSource, IUnknown )

        HW_EXPORT void GetTextAtPosition( UINT32 textPosition, WCHAR const** textString, UINT32* textLength ) const;
        HW_EXPORT void GetTextBeforePosition( UINT32 textPosition, WCHAR const** textString, UINT32* textLength ) const;
        HW_EXPORT DWRITE_READING_DIRECTION GetParagraphReadingDirection( ) const;
        HW_EXPORT void GetLocaleName( UINT32 textPosition, UINT32* textLength, _Outptr_result_z_ WCHAR const** localeName ) const;
        HW_EXPORT void GetNumberSubstitution( UINT32 textPosition, UINT32* textLength, _Outptr_ IDWriteNumberSubstitution** numberSubstitution ) const;
    };


    /// <summary>
    /// This interface is implemented by the text analyzer's client to receive the output of a given text analysis.
    /// </summary>
    class TextAnalysisSink : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextAnalysisSink, Unknown, IDWriteTextAnalysisSink, IUnknown )

        HW_EXPORT void SetScriptAnalysis( UINT32 textPosition, UINT32 textLength, DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis ) const;
        HW_EXPORT void SetLineBreakpoints( UINT32 textPosition, UINT32 textLength, DWRITE_LINE_BREAKPOINT const* lineBreakpoints ) const;
        HW_EXPORT void SetBidiLevel( UINT32 textPosition, UINT32 textLength, UINT8 explicitLevel, UINT8 resolvedLevel ) const;
        HW_EXPORT void SetNumberSubstitution( UINT32 textPosition, UINT32 textLength, IDWriteNumberSubstitution* numberSubstitution ) const;
    };

    /// <summary>
    /// Analyzes various text properties for complex script processing such as 
    /// bidirectional (bidi) support for languages like Arabic, determination of 
    /// line break opportunities, glyph placement, and number substitution.
    /// </summary>
    class TextAnalyzer : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextAnalyzer, Unknown, IDWriteTextAnalyzer, IUnknown )

        HW_EXPORT void AnalyzeScript(
            IDWriteTextAnalysisSource* analysisSource,
            UINT32 textPosition,
            UINT32 textLength,
            IDWriteTextAnalysisSink* analysisSink ) const;

        HW_EXPORT void AnalyzeBidi(
            IDWriteTextAnalysisSource* analysisSource,
            UINT32 textPosition,
            UINT32 textLength,
            IDWriteTextAnalysisSink* analysisSink ) const;

        HW_EXPORT void AnalyzeNumberSubstitution(
            IDWriteTextAnalysisSource* analysisSource,
            UINT32 textPosition,
            UINT32 textLength,
            IDWriteTextAnalysisSink* analysisSink ) const;

        HW_EXPORT void AnalyzeLineBreakpoints(
            IDWriteTextAnalysisSource* analysisSource,
            UINT32 textPosition,
            UINT32 textLength,
            IDWriteTextAnalysisSink* analysisSink ) const;

        HW_EXPORT void GetGlyphs(
            WCHAR const* textString,
            UINT32 textLength,
            IDWriteFontFace* fontFace,
            BOOL isSideways,
            BOOL isRightToLeft,
            DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis,
            WCHAR const* localeName,
            IDWriteNumberSubstitution* numberSubstitution,
            DWRITE_TYPOGRAPHIC_FEATURES const** features,
            UINT32 const* featureRangeLengths,
            UINT32 featureRanges,
            UINT32 maxGlyphCount,
            UINT16* clusterMap,
            DWRITE_SHAPING_TEXT_PROPERTIES* textProps,
            UINT16* glyphIndices,
            DWRITE_SHAPING_GLYPH_PROPERTIES* glyphProps,
            UINT32* actualGlyphCount ) const;

        HW_EXPORT void GetGlyphPlacements(
            WCHAR const* textString,
            UINT16 const* clusterMap,
            DWRITE_SHAPING_TEXT_PROPERTIES* textProps,
            UINT32 textLength,
            UINT16 const* glyphIndices,
            DWRITE_SHAPING_GLYPH_PROPERTIES const* glyphProps,
            UINT32 glyphCount,
            IDWriteFontFace* fontFace,
            FLOAT fontEmSize,
            BOOL isSideways,
            BOOL isRightToLeft,
            DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis,
            WCHAR const* localeName,
            DWRITE_TYPOGRAPHIC_FEATURES const** features,
            UINT32 const* featureRangeLengths,
            UINT32 featureRanges,
            FLOAT* glyphAdvances,
            DWRITE_GLYPH_OFFSET* glyphOffsets ) const;

        HW_EXPORT void GetGdiCompatibleGlyphPlacements(
            WCHAR const* textString,
            UINT16 const* clusterMap,
            DWRITE_SHAPING_TEXT_PROPERTIES* textProps,
            UINT32 textLength,
            UINT16 const* glyphIndices,
            DWRITE_SHAPING_GLYPH_PROPERTIES const* glyphProps,
            UINT32 glyphCount,
            IDWriteFontFace* fontFace,
            FLOAT fontEmSize,
            FLOAT pixelsPerDip,
            DWRITE_MATRIX const* transform,
            BOOL useGdiNatural,
            BOOL isSideways,
            BOOL isRightToLeft,
            DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis,
            WCHAR const* localeName,
            DWRITE_TYPOGRAPHIC_FEATURES const** features,
            UINT32 const* featureRangeLengths,
            UINT32 featureRanges,
            FLOAT* glyphAdvances,
            DWRITE_GLYPH_OFFSET* glyphOffsets ) const;
    };

    /// <summary>
    /// Wraps an application-defined inline graphic, allowing DWrite to 
    /// query metrics as if the graphic were a glyph inline with the text.
    /// </summary>
    class InlineObject : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( InlineObject, Unknown, IDWriteInlineObject, IUnknown )

        HW_EXPORT void Draw( void* clientDrawingContext, IDWriteTextRenderer* renderer, FLOAT originX, FLOAT originY, BOOL isSideways, BOOL isRightToLeft, IUnknown* clientDrawingEffect ) const;

        HW_EXPORT void GetMetrics( DWRITE_INLINE_OBJECT_METRICS* metrics ) const;

        HW_EXPORT void GetOverhangMetrics( DWRITE_OVERHANG_METRICS* overhangs ) const;

        HW_EXPORT void GetBreakConditions( DWRITE_BREAK_CONDITION* breakConditionBefore, DWRITE_BREAK_CONDITION* breakConditionAfter ) const;
    };

    /// <summary>
    /// Defines the pixel snapping properties such as pixels per 
    /// DIP(device-independent pixel) and the current transform 
    /// matrix of a text renderer.
    /// </summary>
    class PixelSnapping : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( PixelSnapping, Unknown, IDWritePixelSnapping, IUnknown )

        HW_EXPORT void IsPixelSnappingDisabled( void* clientDrawingContext, BOOL* isDisabled ) const;

        HW_EXPORT void GetCurrentTransform( void* clientDrawingContext, DWRITE_MATRIX* transform ) const;

        HW_EXPORT void GetPixelsPerDip( void* clientDrawingContext, FLOAT* pixelsPerDip ) const;
    };

    /// <summary>
    /// Represents a set of application-defined callbacks that perform rendering of text, inline objects, and decorations such as underlines.
    /// </summary>
    class TextRenderer : public PixelSnapping
    {
    public:
        typedef PixelSnapping Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextRenderer, PixelSnapping, IDWriteTextRenderer, IDWritePixelSnapping )

        HW_EXPORT void DrawGlyphRun( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_MEASURING_MODE measuringMode, DWRITE_GLYPH_RUN const* glyphRun, DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription, IUnknown* clientDrawingEffect ) const;

        HW_EXPORT void DrawUnderline( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_UNDERLINE const* underline, IUnknown* clientDrawingEffect ) const;

        HW_EXPORT void DrawStrikethrough( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_STRIKETHROUGH const* strikethrough, IUnknown* clientDrawingEffect ) const;

        HW_EXPORT void DrawInlineObject( void* clientDrawingContext, FLOAT originX, FLOAT originY, IDWriteInlineObject* inlineObject, BOOL isSideways, BOOL isRightToLeft, IUnknown* clientDrawingEffect ) const;
    };

    /// <summary>
    /// The TextLayout class represents a block of text after it has been fully analyzed and formatted.
    /// </summary>
    class TextLayout : public TextFormat
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextLayout, TextFormat, IDWriteTextLayout, IDWriteTextFormat )

        HW_EXPORT void SetMaxWidth( FLOAT maxWidth ) const;
        HW_EXPORT void SetMaxHeight( FLOAT maxHeight ) const;

        HW_EXPORT void SetFontCollection( IDWriteFontCollection* fontCollection, DWRITE_TEXT_RANGE textRange ) const;

        HW_EXPORT void SetFontFamilyName( WCHAR const* fontFamilyName, DWRITE_TEXT_RANGE textRange ) const;

        HW_EXPORT void SetFontWeight( DWRITE_FONT_WEIGHT fontWeight, DWRITE_TEXT_RANGE textRange ) const;

        HW_EXPORT void SetFontStyle( DWRITE_FONT_STYLE fontStyle, DWRITE_TEXT_RANGE textRange ) const;

        HW_EXPORT void SetFontStretch( DWRITE_FONT_STRETCH fontStretch, DWRITE_TEXT_RANGE textRange ) const;

        HW_EXPORT void SetFontSize( FLOAT fontSize, DWRITE_TEXT_RANGE textRange ) const;

        HW_EXPORT void SetUnderline( BOOL hasUnderline, DWRITE_TEXT_RANGE textRange ) const;

        HW_EXPORT void SetStrikethrough( BOOL hasStrikethrough, DWRITE_TEXT_RANGE textRange ) const;

        HW_EXPORT void SetDrawingEffect( IUnknown* drawingEffect, DWRITE_TEXT_RANGE textRange ) const;

        HW_EXPORT void SetInlineObject( IDWriteInlineObject* inlineObject, DWRITE_TEXT_RANGE textRange ) const;

        HW_EXPORT void SetTypography( IDWriteTypography* typography, DWRITE_TEXT_RANGE textRange ) const;

        HW_EXPORT void SetLocaleName( WCHAR const* localeName, DWRITE_TEXT_RANGE textRange ) const;

        HW_EXPORT FLOAT GetMaxWidth( ) const;

        HW_EXPORT FLOAT GetMaxHeight( ) const;

        HW_EXPORT void GetFontCollection( UINT32 currentPosition, IDWriteFontCollection** fontCollection, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void GetFontFamilyNameLength( UINT32 currentPosition, UINT32* nameLength, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void GetFontFamilyName( UINT32 currentPosition, _Out_writes_z_( nameSize ) WCHAR* fontFamilyName, UINT32 nameSize, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void GetFontWeight( UINT32 currentPosition, DWRITE_FONT_WEIGHT* fontWeight, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void GetFontStyle( UINT32 currentPosition, DWRITE_FONT_STYLE* fontStyle, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void GetFontStretch( UINT32 currentPosition, DWRITE_FONT_STRETCH* fontStretch, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void GetFontSize( UINT32 currentPosition, FLOAT* fontSize, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void GetUnderline( UINT32 currentPosition, BOOL* hasUnderline, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void GetStrikethrough( UINT32 currentPosition, BOOL* hasStrikethrough, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void GetDrawingEffect( UINT32 currentPosition, IUnknown** drawingEffect, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void GetInlineObject( UINT32 currentPosition, IDWriteInlineObject** inlineObject, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void GetTypography( UINT32 currentPosition, IDWriteTypography** typography, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void GetLocaleNameLength( UINT32 currentPosition, UINT32* nameLength, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void GetLocaleName( UINT32 currentPosition, _Out_writes_z_( nameSize ) WCHAR* localeName, UINT32 nameSize, DWRITE_TEXT_RANGE* textRange = nullptr ) const;

        HW_EXPORT void Draw( void* clientDrawingContext, IDWriteTextRenderer* renderer, FLOAT originX, FLOAT originY ) const;

        HW_EXPORT void GetLineMetrics( DWRITE_LINE_METRICS* lineMetrics, UINT32 maxLineCount, UINT32* actualLineCount ) const;

        HW_EXPORT void GetMetrics( DWRITE_TEXT_METRICS* textMetrics ) const;

        HW_EXPORT void GetOverhangMetrics( DWRITE_OVERHANG_METRICS* overhangs ) const;

        HW_EXPORT void GetClusterMetrics( _Out_writes_opt_( maxClusterCount ) DWRITE_CLUSTER_METRICS* clusterMetrics, UINT32 maxClusterCount, UINT32* actualClusterCount ) const;

        HW_EXPORT void DetermineMinWidth( FLOAT* minWidth ) const;

        HW_EXPORT void HitTestPoint( FLOAT pointX, FLOAT pointY, BOOL* isTrailingHit, BOOL* isInside, DWRITE_HIT_TEST_METRICS* hitTestMetrics ) const;

        HW_EXPORT void HitTestTextPosition( UINT32 textPosition, BOOL isTrailingHit, FLOAT* pointX, FLOAT* pointY, DWRITE_HIT_TEST_METRICS* hitTestMetrics ) const;

        HW_EXPORT void HitTestTextRange( UINT32 textPosition, UINT32 textLength, FLOAT originX, FLOAT originY, DWRITE_HIT_TEST_METRICS* hitTestMetrics, UINT32 maxHitTestMetricsCount, UINT32* actualHitTestMetricsCount ) const;
    };

    


    /// <summary>
    /// Encapsulates a 32-bit device independent bitmap and device context, which can be used for rendering glyphs.
    /// </summary>
    class BitmapRenderTarget : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( BitmapRenderTarget, Unknown, IDWriteBitmapRenderTarget, IUnknown )

        HW_EXPORT void DrawGlyphRun( FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_MEASURING_MODE measuringMode, DWRITE_GLYPH_RUN const* glyphRun, IDWriteRenderingParams* renderingParams, COLORREF textColor, RECT* blackBoxRect = nullptr ) const;

        HW_EXPORT HDC GetMemoryDC( ) const;

        HW_EXPORT FLOAT GetPixelsPerDip( ) const;

        HW_EXPORT void SetPixelsPerDip( FLOAT pixelsPerDip ) const;

        HW_EXPORT void GetCurrentTransform( DWRITE_MATRIX* transform ) const;

        HW_EXPORT void SetCurrentTransform( DWRITE_MATRIX const* transform ) const;

        HW_EXPORT void GetSize( SIZE* size ) const;

        HW_EXPORT void Resize( UINT32 width, UINT32 height ) const;
    };


    /// <summary>
    /// Provides interoperability with GDI, such as methods to convert a font 
    /// face to a LOGFONT structure, or to convert a GDI font description into 
    /// a font face. It is also used to create bitmap render target objects.
    /// </summary>
    class GdiInterop : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GdiInterop, Unknown, IDWriteGdiInterop, IUnknown )

        HW_EXPORT void CreateFontFromLOGFONT( LOGFONTW const* logFont, IDWriteFont** font ) const;

        HW_EXPORT void ConvertFontToLOGFONT( IDWriteFont* font, LOGFONTW* logFont, BOOL* isSystemFont ) const;

        HW_EXPORT void ConvertFontFaceToLOGFONT( IDWriteFontFace* font, LOGFONTW* logFont ) const;

        HW_EXPORT void CreateFontFaceFromHdc( HDC hdc, IDWriteFontFace** fontFace ) const;

        HW_EXPORT void CreateBitmapRenderTarget( HDC hdc, UINT32 width, UINT32 height, IDWriteBitmapRenderTarget** renderTarget ) const;
    };

    /// <summary>
    /// Contains low-level information used to render a glyph run.
    /// </summary>
    class GlyphRunAnalysis : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GlyphRunAnalysis, Unknown, IDWriteGlyphRunAnalysis, IUnknown )

        HW_EXPORT void GetAlphaTextureBounds( DWRITE_TEXTURE_TYPE textureType, RECT* textureBounds ) const;

        HW_EXPORT void CreateAlphaTexture( DWRITE_TEXTURE_TYPE textureType, RECT const* textureBounds, BYTE* alphaValues, UINT32 bufferSize ) const;

        HW_EXPORT void GetAlphaBlendParams( IDWriteRenderingParams* renderingParams, FLOAT* blendGamma, FLOAT* blendEnhancedContrast, FLOAT* blendClearTypeLevel ) const;
    };

    /// <summary>
    /// Used to create all subsequent DirectWrite objects. This class is the root factory for all DirectWrite objects.
    /// </summary>
    class Factory : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Factory, Unknown, IDWriteFactory, IUnknown )

        HW_EXPORT Factory( DWRITE_FACTORY_TYPE factoryType );

        HW_EXPORT void GetSystemFontCollection( IDWriteFontCollection** fontCollection, BOOL checkForUpdates = FALSE ) const;
        HW_EXPORT FontCollection GetSystemFontCollection( bool checkForUpdates = false ) const;

        HW_EXPORT void CreateCustomFontCollection( IDWriteFontCollectionLoader* collectionLoader, void const* collectionKey, UINT32 collectionKeySize, IDWriteFontCollection** fontCollection ) const;
        HW_EXPORT FontCollection CreateCustomFontCollection( IDWriteFontCollectionLoader* collectionLoader, void const* collectionKey, UINT32 collectionKeySize ) const;

        HW_EXPORT void RegisterFontCollectionLoader( IDWriteFontCollectionLoader* fontCollectionLoader ) const;
        HW_EXPORT void UnregisterFontCollectionLoader( IDWriteFontCollectionLoader* fontCollectionLoader ) const;

        HW_EXPORT void CreateFontFileReference( WCHAR const* filePath, FILETIME const* lastWriteTime, IDWriteFontFile** fontFile ) const;
        HW_EXPORT FontFile CreateFontFileReference( WCHAR const* filePath, FILETIME const* lastWriteTime = nullptr ) const;

        HW_EXPORT void CreateCustomFontFileReference( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileLoader* fontFileLoader, IDWriteFontFile** fontFile ) const;
        HW_EXPORT FontFile CreateCustomFontFileReference( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileLoader* fontFileLoader ) const;

        HW_EXPORT void CreateFontFace( DWRITE_FONT_FACE_TYPE fontFaceType, UINT32 numberOfFiles, IDWriteFontFile* const* fontFiles, UINT32 faceIndex, DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags, IDWriteFontFace** fontFace ) const;
        HW_EXPORT FontFace CreateFontFace( DWRITE_FONT_FACE_TYPE fontFaceType, UINT32 numberOfFiles, IDWriteFontFile* const* fontFiles, UINT32 faceIndex, DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags ) const;

        HW_EXPORT void CreateRenderingParams( IDWriteRenderingParams** renderingParams ) const;
        HW_EXPORT RenderingParams CreateRenderingParams( ) const;

        HW_EXPORT void CreateMonitorRenderingParams( HMONITOR monitor, IDWriteRenderingParams** renderingParams ) const;
        HW_EXPORT RenderingParams CreateMonitorRenderingParams( HMONITOR monitor ) const;

        HW_EXPORT void CreateCustomRenderingParams( FLOAT gamma, FLOAT enhancedContrast, FLOAT clearTypeLevel, DWRITE_PIXEL_GEOMETRY pixelGeometry, DWRITE_RENDERING_MODE renderingMode, IDWriteRenderingParams** renderingParams ) const;
        HW_EXPORT RenderingParams CreateCustomRenderingParams( FLOAT gamma, FLOAT enhancedContrast, FLOAT clearTypeLevel, DWRITE_PIXEL_GEOMETRY pixelGeometry, DWRITE_RENDERING_MODE renderingMode ) const;

        HW_EXPORT void RegisterFontFileLoader( IDWriteFontFileLoader* fontFileLoader ) const;
        HW_EXPORT void UnregisterFontFileLoader( IDWriteFontFileLoader* fontFileLoader ) const;

        HW_EXPORT void CreateTextFormat( WCHAR const* fontFamilyName, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName, IDWriteTextFormat** textFormat ) const;
        HW_EXPORT TextFormat CreateTextFormat( WCHAR const* fontFamilyName, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName ) const;
        HW_EXPORT TextFormat CreateTextFormat( WCHAR const* fontFamilyName, FLOAT fontSize ) const;

        HW_EXPORT void CreateTypography( IDWriteTypography** typography ) const;
        HW_EXPORT Typography CreateTypography( ) const;

        HW_EXPORT void GetGdiInterop( IDWriteGdiInterop** gdiInterop ) const;
        HW_EXPORT GdiInterop GetGdiInterop( ) const;

        HW_EXPORT void CreateTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT maxWidth, FLOAT maxHeight, IDWriteTextLayout** textLayout ) const;
        HW_EXPORT TextLayout CreateTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT maxWidth, FLOAT maxHeight ) const;

        HW_EXPORT void CreateGdiCompatibleTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT layoutWidth, FLOAT layoutHeight, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural, IDWriteTextLayout** textLayout ) const;
        HW_EXPORT TextLayout CreateGdiCompatibleTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT layoutWidth, FLOAT layoutHeight, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural ) const;

        HW_EXPORT void CreateEllipsisTrimmingSign( IDWriteTextFormat* textFormat, IDWriteInlineObject** trimmingSign ) const;
        HW_EXPORT InlineObject CreateEllipsisTrimmingSign( IDWriteTextFormat* textFormat ) const;

        HW_EXPORT void CreateTextAnalyzer( IDWriteTextAnalyzer** textAnalyzer ) const;
        HW_EXPORT TextAnalyzer CreateTextAnalyzer( ) const;

        HW_EXPORT void CreateNumberSubstitution( DWRITE_NUMBER_SUBSTITUTION_METHOD substitutionMethod, WCHAR const* localeName, BOOL ignoreUserOverride, IDWriteNumberSubstitution** numberSubstitution ) const;

        HW_EXPORT void CreateGlyphRunAnalysis( DWRITE_GLYPH_RUN const* glyphRun, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_RENDERING_MODE renderingMode, DWRITE_MEASURING_MODE measuringMode, FLOAT baselineOriginX, FLOAT baselineOriginY, IDWriteGlyphRunAnalysis** glyphRunAnalysis ) const;
        HW_EXPORT GlyphRunAnalysis CreateGlyphRunAnalysis( DWRITE_GLYPH_RUN const* glyphRun, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_RENDERING_MODE renderingMode, DWRITE_MEASURING_MODE measuringMode, FLOAT baselineOriginX, FLOAT baselineOriginY ) const;
    };
}

namespace Harlinn::Windows::Graphics::D2D
{
    inline void DrawingStateBlock::SetTextRenderingParams( const DirectWrite::RenderingParams& textRenderingParams ) const
    {
        SetTextRenderingParams( textRenderingParams.GetInterfacePointer<IDWriteRenderingParams>( ) );
    }
    inline DirectWrite::RenderingParams DrawingStateBlock::GetTextRenderingParams( ) const
    {
        IDWriteRenderingParams* ptr;
        GetTextRenderingParams( &ptr );
        return DirectWrite::RenderingParams( ptr );
    }

    inline void RenderTarget::SetTextRenderingParams( const DirectWrite::RenderingParams& textRenderingParams ) const
    {
        SetTextRenderingParams( textRenderingParams.GetInterfacePointer<IDWriteRenderingParams>( ) );
    }
    inline DirectWrite::RenderingParams RenderTarget::GetTextRenderingParams( ) const
    {
        IDWriteRenderingParams* ptr;
        GetTextRenderingParams( &ptr );
        return DirectWrite::RenderingParams( ptr );
    }

    inline void Factory::CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION* drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams, ID2D1DrawingStateBlock** drawingStateBlock ) const
    {
        CreateDrawingStateBlock( drawingStateDescription, textRenderingParams.GetInterfacePointer<IDWriteRenderingParams>( ), drawingStateBlock );
    }
    inline void Factory::CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION& drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams, ID2D1DrawingStateBlock** drawingStateBlock ) const
    {
        CreateDrawingStateBlock( drawingStateDescription, textRenderingParams.GetInterfacePointer<IDWriteRenderingParams>( ), drawingStateBlock );
    }
    inline DrawingStateBlock Factory::CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION* drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams ) const
    {
        return CreateDrawingStateBlock( drawingStateDescription, textRenderingParams.GetInterfacePointer<IDWriteRenderingParams>( ) );
    }
    inline DrawingStateBlock Factory::CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION& drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams ) const
    {
        return CreateDrawingStateBlock( &drawingStateDescription, textRenderingParams.GetInterfacePointer<IDWriteRenderingParams>( ) );
    }

    inline void RenderTarget::DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, const D2D1_RECT_F* layoutRect, const Brush& defaultForegroundBrush, D2D1_DRAW_TEXT_OPTIONS options, DWRITE_MEASURING_MODE measuringMode ) const
    {
        DrawText( string, stringLength, textFormat.GetInterfacePointer<IDWriteTextFormat>( ), layoutRect, defaultForegroundBrush.GetInterfacePointer<ID2D1Brush>( ), options, measuringMode );
    }

    inline void RenderTarget::DrawText( const WideString& text, const DirectWrite::TextFormat& textFormat, const D2D1_RECT_F* layoutRect, const Brush& defaultForegroundBrush, D2D1_DRAW_TEXT_OPTIONS options, DWRITE_MEASURING_MODE measuringMode ) const
    {
        DrawText( text.c_str( ), static_cast<UINT32>( text.length( ) ), textFormat.GetInterfacePointer<IDWriteTextFormat>( ), layoutRect, defaultForegroundBrush.GetInterfacePointer<ID2D1Brush>( ), options, measuringMode );
    }

    inline void RenderTarget::DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, const Brush& defaultForegroundBrush, D2D1_DRAW_TEXT_OPTIONS options ) const
    {
        DrawTextLayout( origin, textLayout.GetInterfacePointer<IDWriteTextLayout>( ), defaultForegroundBrush.GetInterfacePointer<ID2D1Brush>( ), options );
    }

    inline void Factory1::CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION1* drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams, ID2D1DrawingStateBlock1** drawingStateBlock ) const
    {
        CreateDrawingStateBlock( drawingStateDescription, textRenderingParams.GetInterfacePointer<IDWriteRenderingParams>( ), drawingStateBlock );
    }
    inline void Factory1::CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION1& drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams, ID2D1DrawingStateBlock1** drawingStateBlock ) const
    {
        CreateDrawingStateBlock( &drawingStateDescription, textRenderingParams.GetInterfacePointer<IDWriteRenderingParams>( ), drawingStateBlock );
    }
    inline DrawingStateBlock1 Factory1::CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION1* drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams ) const
    {
        return CreateDrawingStateBlock( drawingStateDescription, textRenderingParams.GetInterfacePointer<IDWriteRenderingParams>( ) );
    }
    inline DrawingStateBlock1 Factory1::CreateDrawingStateBlock( const D2D1_DRAWING_STATE_DESCRIPTION1& drawingStateDescription, const DirectWrite::RenderingParams& textRenderingParams ) const
    {
        return CreateDrawingStateBlock( &drawingStateDescription, textRenderingParams.GetInterfacePointer<IDWriteRenderingParams>( ) );
    }

    inline void DeviceContext4::DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, const D2D1_RECT_F* layoutRect, ID2D1Brush* defaultFillBrush, ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options, DWRITE_MEASURING_MODE measuringMode ) const
    {
        DrawText( string, stringLength, textFormat.GetInterfacePointer<IDWriteTextFormat>( ), layoutRect, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, options, measuringMode );
    }

    inline void DeviceContext4::DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, const D2D1_RECT_F* layoutRect, const Brush& defaultFillBrush, ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options, DWRITE_MEASURING_MODE measuringMode ) const
    {
        DrawText( string, stringLength, textFormat.GetInterfacePointer<IDWriteTextFormat>( ), layoutRect, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle, colorPaletteIndex, options, measuringMode );
    }
    inline void DeviceContext4::DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, const D2D1_RECT_F* layoutRect, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options, DWRITE_MEASURING_MODE measuringMode ) const
    {
        DrawText( string, stringLength, textFormat.GetInterfacePointer<IDWriteTextFormat>( ), layoutRect, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, options, measuringMode );
    }

    inline void DeviceContext4::DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, CONST D2D1_RECT_F& layoutRect, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options, DWRITE_MEASURING_MODE measuringMode ) const
    {
        return DrawText( string, stringLength, textFormat.GetInterfacePointer<IDWriteTextFormat>( ), &layoutRect, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, options, measuringMode );
    }
    inline void DeviceContext4::DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, CONST D2D1_RECT_F& layoutRect, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options, DWRITE_MEASURING_MODE measuringMode ) const
    {
        return DrawText( string, stringLength, textFormat.GetInterfacePointer<IDWriteTextFormat>( ), &layoutRect, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle, colorPaletteIndex, options, measuringMode );
    }
    inline void DeviceContext4::DrawText( const WCHAR* string, UINT32 stringLength, const DirectWrite::TextFormat& textFormat, CONST D2D1_RECT_F& layoutRect, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options, DWRITE_MEASURING_MODE measuringMode ) const
    {
        return DrawText( string, stringLength, textFormat.GetInterfacePointer<IDWriteTextFormat>( ), &layoutRect, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, options, measuringMode );
    }
    inline void DeviceContext4::DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options ) const
    {
        DrawTextLayout( origin, textLayout.GetInterfacePointer<IDWriteTextLayout>( ), defaultFillBrush, svgGlyphStyle, colorPaletteIndex, options );
    }
    inline void DeviceContext4::DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options ) const
    {
        DrawTextLayout( origin, textLayout.GetInterfacePointer<IDWriteTextLayout>( ), defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle, colorPaletteIndex, options );
    }
    inline void DeviceContext4::DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options ) const
    {
        DrawTextLayout( origin, textLayout.GetInterfacePointer<IDWriteTextLayout>( ), defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, options );
    }

    inline void DeviceContext4::DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options ) const
    {
        DrawTextLayout( origin, textLayout, nullptr, nullptr, colorPaletteIndex, options );
    }
    inline void DeviceContext4::DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options ) const
    {
        DrawTextLayout( origin, textLayout, nullptr, svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, options );
    }
    inline void DeviceContext4::DrawTextLayout( const D2D1_POINT_2F& origin, const DirectWrite::TextLayout& textLayout, const Brush& defaultFillBrush, UINT32 colorPaletteIndex, D2D1_DRAW_TEXT_OPTIONS options ) const
    {
        DrawTextLayout( origin, textLayout, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), nullptr, colorPaletteIndex, options );
    }

    inline void DeviceContext4::GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, ID2D1Image** glyphImage ) const
    { 
        GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, worldTransform, dpiX, dpiY, glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, FLOAT dpiX, FLOAT dpiY, D2D1_MATRIX_3X2_F& glyphTransform, ID2D1Image** glyphImage ) const
    { 
        GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, worldTransform, dpiX, dpiY, &glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, ID2D1Image** glyphImage ) const
    { 
        GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, dpiX, dpiY, glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, ID2D1Image** glyphImage ) const
    {
        GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, dpiX, dpiY, &glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, ID2D1Image** glyphImage ) const
    {
        GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, dpiX, dpiY, glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, ID2D1Image** glyphImage ) const
    {
        GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, dpiX, dpiY, &glyphTransform, glyphImage );
    }
    inline Image DeviceContext4::GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const
    {
        return GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, worldTransform, dpiX, dpiY, glyphTransform );
    }
    inline Image DeviceContext4::GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, FLOAT dpiX, FLOAT dpiY, D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, worldTransform, dpiX, dpiY, &glyphTransform );
    }
    inline Image DeviceContext4::GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const
    {
        return GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, dpiX, dpiY, glyphTransform );
    }
    inline Image DeviceContext4::GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, dpiX, dpiY, &glyphTransform );
    }
    inline Image DeviceContext4::GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const
    {
        return GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, dpiX, dpiY, glyphTransform );
    }
    inline Image DeviceContext4::GetColorBitmapGlyphImage( DWRITE_GLYPH_IMAGE_FORMATS glyphImageFormat, const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, FLOAT dpiX, FLOAT dpiY, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetColorBitmapGlyphImage( glyphImageFormat, glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, dpiX, dpiY, &glyphTransform );
    }
    
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, worldTransform, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, &glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle, colorPaletteIndex, &glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, nullptr, svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), nullptr, colorPaletteIndex, &glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, nullptr, nullptr, colorPaletteIndex, &glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F* glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, &glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle, colorPaletteIndex, &glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, nullptr, svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), nullptr, colorPaletteIndex, &glyphTransform, glyphImage );
    }
    inline void DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform, _COM_Outptr_ ID2D1CommandList** glyphImage ) const
    {
        GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, nullptr, nullptr, colorPaletteIndex, &glyphTransform, glyphImage );
    }
    //
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ const D2D1_MATRIX_3X2_F* worldTransform, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, worldTransform, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, glyphTransform );
    }
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, &glyphTransform );
    }
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle, colorPaletteIndex, &glyphTransform );
    }
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform );
    }
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, nullptr, svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform );
    }
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, const Brush& defaultFillBrush, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), nullptr, colorPaletteIndex, &glyphTransform );
    }
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const D2D1_MATRIX_3X2_F& worldTransform, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, &worldTransform, nullptr, nullptr, colorPaletteIndex, &glyphTransform );
    }
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F* glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, glyphTransform );
    }
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, _In_opt_ ID2D1Brush* defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush, svgGlyphStyle, colorPaletteIndex, &glyphTransform );
    }
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, _In_opt_ ID2D1SvgGlyphStyle* svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle, colorPaletteIndex, &glyphTransform );
    }
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform );
    }
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const SvgGlyphStyle& svgGlyphStyle, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, nullptr, svgGlyphStyle.GetInterfacePointer<ID2D1SvgGlyphStyle>( ), colorPaletteIndex, &glyphTransform );
    }
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, const Brush& defaultFillBrush, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, defaultFillBrush.GetInterfacePointer<ID2D1Brush>( ), nullptr, colorPaletteIndex, &glyphTransform );
    }
    inline Image DeviceContext4::GetSvgGlyphImage( const D2D1_POINT_2F& glyphOrigin, const DirectWrite::FontFace& fontFace, FLOAT fontEmSize, UINT16 glyphIndex, BOOL isSideways, UINT32 colorPaletteIndex, _Out_ D2D1_MATRIX_3X2_F& glyphTransform ) const
    {
        return GetSvgGlyphImage( glyphOrigin, fontFace.GetInterfacePointer<IDWriteFontFace>( ), fontEmSize, glyphIndex, isSideways, nullptr, nullptr, nullptr, colorPaletteIndex, &glyphTransform );
    }

}


#endif
