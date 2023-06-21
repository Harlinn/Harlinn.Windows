#pragma once
#ifndef HARLINN_WINDOWS_HWDWRITE_H_
#define HARLINN_WINDOWS_HWDWRITE_H_

#include <HWGraphics.h>

namespace Harlinn::Windows::DirectWrite
{
    class FontFileStream;
    class FontFileLoader : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFileLoader, Unknown, IDWriteFontFileLoader, IUnknown )

        HW_EXPORT FontFileLoader& CreateStreamFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileStream** fontFileStream );
        HW_EXPORT FontFileStream CreateStreamFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize );
    };

    class LocalFontFileLoader : public FontFileLoader
    {
    public:
        typedef FontFileLoader Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( LocalFontFileLoader, FontFileLoader, IDWriteLocalFontFileLoader, IDWriteFontFileLoader )

            HW_EXPORT LocalFontFileLoader& GetFilePathLengthFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, UINT32* filePathLength );
        HW_EXPORT UINT32 GetFilePathLengthFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize );

        HW_EXPORT LocalFontFileLoader& GetFilePathFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, WCHAR* filePath, UINT32 filePathSize );
        HW_EXPORT std::shared_ptr<WideString> GetFilePathFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize );

        HW_EXPORT LocalFontFileLoader& GetLastWriteTimeFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, FILETIME* lastWriteTime );
        HW_EXPORT FILETIME GetLastWriteTimeFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize );
    };

    class FontFileStream : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFileStream, Unknown, IDWriteFontFileStream, IUnknown )

            HW_EXPORT FontFileStream& ReadFileFragment( void const** fragmentStart, UINT64 fileOffset, UINT64 fragmentSize, void** fragmentContext );
        HW_EXPORT FontFileStream& ReleaseFileFragment( void* fragmentContext );

        HW_EXPORT FontFileStream& GetFileSize( UINT64* fileSize );
        HW_EXPORT UINT64 GetFileSize( );

        HW_EXPORT FontFileStream& GetLastWriteTime( UINT64* lastWriteTime );
        HW_EXPORT UINT64 GetLastWriteTime( );
    };


    class FontFile : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFile, Unknown, IDWriteFontFile, IUnknown )

            HW_EXPORT FontFile& GetReferenceKey( void const** fontFileReferenceKey, UINT32* fontFileReferenceKeySize );
        HW_EXPORT FontFile& GetLoader( IDWriteFontFileLoader** fontFileLoader );
        HW_EXPORT FontFileLoader GetLoader( );
        HW_EXPORT FontFile& Analyze( BOOL* isSupportedFontType, DWRITE_FONT_FILE_TYPE* fontFileType, DWRITE_FONT_FACE_TYPE* fontFaceType, UINT32* numberOfFaces );
        HW_EXPORT FontFile& Analyze( BOOL& isSupportedFontType, DWRITE_FONT_FILE_TYPE& fontFileType, DWRITE_FONT_FACE_TYPE& fontFaceType, UINT32& numberOfFaces );
        HW_EXPORT FontFile& Analyze( BOOL& isSupportedFontType, DWRITE_FONT_FILE_TYPE& fontFileType, UINT32& numberOfFaces );
    };


    class RenderingParams : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( RenderingParams, Unknown, IDWriteRenderingParams, IUnknown )

            HW_EXPORT FLOAT GetGamma( );
        HW_EXPORT FLOAT GetEnhancedContrast( );
        HW_EXPORT FLOAT GetClearTypeLevel( );
        HW_EXPORT DWRITE_PIXEL_GEOMETRY GetPixelGeometry( );
        HW_EXPORT DWRITE_RENDERING_MODE GetRenderingMode( );
    };

    



    class FontFace : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFace, Unknown, IDWriteFontFace, IUnknown )

            HW_EXPORT DWRITE_FONT_FACE_TYPE GetType( );
        HW_EXPORT FontFace& GetFiles( _Inout_ UINT32* numberOfFiles, IDWriteFontFile** fontFiles );
        HW_EXPORT UINT32 GetNumberOfFiles( );
        HW_EXPORT std::shared_ptr< std::vector<FontFile> > GetFiles( );

        HW_EXPORT UINT32 GetIndex( );
        HW_EXPORT DWRITE_FONT_SIMULATIONS GetSimulations( );
        HW_EXPORT BOOL IsSymbolFont( );
        HW_EXPORT FontFace& GetMetrics( DWRITE_FONT_METRICS* fontFaceMetrics );
        HW_EXPORT FontFace& GetMetrics( DWRITE_FONT_METRICS& fontFaceMetrics );
        HW_EXPORT UINT16 GetGlyphCount( );
        HW_EXPORT FontFace& GetDesignGlyphMetrics( UINT16 const* glyphIndices, UINT32 glyphCount, DWRITE_GLYPH_METRICS* glyphMetrics, BOOL isSideways = FALSE );
        HW_EXPORT FontFace& GetGlyphIndices( UINT32 const* codePoints, UINT32 codePointCount, UINT16* glyphIndices );
        HW_EXPORT FontFace& TryGetFontTable( UINT32 openTypeTableTag, const void** tableData, UINT32* tableSize, void** tableContext, BOOL* exists );
        HW_EXPORT FontFace& ReleaseFontTable( void* tableContext );
        HW_EXPORT FontFace& GetGlyphRunOutline( FLOAT emSize, UINT16 const* glyphIndices, FLOAT const* glyphAdvances, DWRITE_GLYPH_OFFSET const* glyphOffsets, UINT32 glyphCount, BOOL isSideways, BOOL isRightToLeft, IDWriteGeometrySink* geometrySink );
        HW_EXPORT FontFace& GetRecommendedRenderingMode( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MEASURING_MODE measuringMode, IDWriteRenderingParams* renderingParams, DWRITE_RENDERING_MODE* renderingMode );
        HW_EXPORT DWRITE_RENDERING_MODE GetRecommendedRenderingMode( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MEASURING_MODE measuringMode, IDWriteRenderingParams* renderingParams );

        HW_EXPORT FontFace& GetGdiCompatibleMetrics( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_FONT_METRICS* fontFaceMetrics );
        HW_EXPORT FontFace& GetGdiCompatibleGlyphMetrics( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural, UINT16 const* glyphIndices, UINT32 glyphCount, DWRITE_GLYPH_METRICS* glyphMetrics, BOOL isSideways = FALSE );
    };

    class FontFileEnumerator;
    class FontCollectionLoader : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontCollectionLoader, Unknown, IDWriteFontCollectionLoader, IUnknown )

            HW_EXPORT FontCollectionLoader& CreateEnumeratorFromKey( IDWriteFactory* factory, void const* collectionKey, UINT32 collectionKeySize, IDWriteFontFileEnumerator** fontFileEnumerator );
        HW_EXPORT FontFileEnumerator CreateEnumeratorFromKey( IDWriteFactory* factory, void const* collectionKey, UINT32 collectionKeySize );
    };

    class FontFileEnumerator : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFileEnumerator, Unknown, IDWriteFontFileEnumerator, IUnknown )

            HW_EXPORT FontFileEnumerator& MoveNext( BOOL* hasCurrentFile );
        HW_EXPORT bool MoveNext( );

        HW_EXPORT FontFileEnumerator& GetCurrentFontFile( IDWriteFontFile** fontFile );
        HW_EXPORT FontFile GetCurrentFontFile( );
    };


    class LocalizedStrings : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( LocalizedStrings, Unknown, IDWriteLocalizedStrings, IUnknown )

            HW_EXPORT UINT32 GetCount( );
        HW_EXPORT LocalizedStrings& FindLocaleName( WCHAR const* localeName, UINT32* index, BOOL* exists );
        HW_EXPORT bool FindLocaleName( WCHAR const* localeName, UINT32* index );

        HW_EXPORT LocalizedStrings& GetLocaleNameLength( UINT32 index, UINT32* length );
        HW_EXPORT UINT32 GetLocaleNameLength( UINT32 index );

        HW_EXPORT LocalizedStrings& GetLocaleName( UINT32 index, WCHAR* localeName, UINT32 size );
        HW_EXPORT std::shared_ptr<WideString> GetLocaleName( UINT32 index );

        HW_EXPORT LocalizedStrings& GetStringLength( UINT32 index, UINT32* length );
        HW_EXPORT UINT32 GetStringLength( UINT32 index );

        HW_EXPORT LocalizedStrings& GetString( UINT32 index, WCHAR* stringBuffer, UINT32 size );
        HW_EXPORT std::shared_ptr<WideString> GetString( UINT32 index );
    };

    class FontFamily;
    class Font;
    class FontCollection : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontCollection, Unknown, IDWriteFontCollection, IUnknown )

            HW_EXPORT UINT32 GetFontFamilyCount( );
        HW_EXPORT FontCollection& GetFontFamily( UINT32 index, IDWriteFontFamily** fontFamily );
        HW_EXPORT FontFamily GetFontFamily( UINT32 index );
        HW_EXPORT std::shared_ptr< std::vector<FontFamily> > GetFontFamilies( );

        HW_EXPORT FontCollection& FindFamilyName( WCHAR const* familyName, UINT32* index, BOOL* exists );
        HW_EXPORT bool FindFamilyName( WCHAR const* familyName, UINT32* index );

        HW_EXPORT FontCollection& GetFontFromFontFace( IDWriteFontFace* fontFace, IDWriteFont** font );
        HW_EXPORT Font GetFontFromFontFace( IDWriteFontFace* fontFace );
    };

    class FontList : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontList, Unknown, IDWriteFontList, IUnknown )

            HW_EXPORT FontList& GetFontCollection( IDWriteFontCollection** fontCollection );
        HW_EXPORT FontCollection GetFontCollection( );
        HW_EXPORT UINT32 GetFontCount( );
        HW_EXPORT FontList& GetFont( UINT32 index, IDWriteFont** font );
        HW_EXPORT Font GetFont( UINT32 index );
    };


    class FontFamily : public FontList
    {
    public:
        typedef FontList Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFamily, FontList, IDWriteFontFamily, IDWriteFontList )

            HW_EXPORT FontFamily& GetFamilyNames( IDWriteLocalizedStrings** names );
        HW_EXPORT LocalizedStrings GetFamilyNames( );

        HW_EXPORT FontFamily& GetFirstMatchingFont( DWRITE_FONT_WEIGHT  weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style, IDWriteFont** matchingFont );
        HW_EXPORT Font GetFirstMatchingFont( DWRITE_FONT_WEIGHT  weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style );

        HW_EXPORT FontFamily& GetMatchingFonts( DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style, IDWriteFontList** matchingFonts );
        HW_EXPORT FontList GetMatchingFonts( DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style );
    };


    class Font : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Font, Unknown, IDWriteFont, IUnknown )

            HW_EXPORT Font& GetFontFamily( IDWriteFontFamily** fontFamily );
        HW_EXPORT FontFamily GetFontFamily( );
        HW_EXPORT DWRITE_FONT_WEIGHT GetWeight( );
        HW_EXPORT DWRITE_FONT_STRETCH GetStretch( );
        HW_EXPORT DWRITE_FONT_STYLE GetStyle( );
        HW_EXPORT bool IsSymbolFont( );
        HW_EXPORT Font& GetFaceNames( IDWriteLocalizedStrings** names );
        HW_EXPORT LocalizedStrings GetFaceNames( );
        HW_EXPORT Font& GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_ID informationalStringID, IDWriteLocalizedStrings** informationalStrings, BOOL* exists );
        HW_EXPORT DWRITE_FONT_SIMULATIONS GetSimulations( );
        HW_EXPORT Font& GetMetrics( DWRITE_FONT_METRICS* fontMetrics );
        HW_EXPORT Font& HasCharacter( UINT32 unicodeValue, BOOL* exists );
        HW_EXPORT bool HasCharacter( UINT32 unicodeValue );
        HW_EXPORT Font& CreateFontFace( IDWriteFontFace** fontFace );
        HW_EXPORT FontFace CreateFontFace( );
    };


    class InlineObject;
    class TextFormat : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextFormat, Unknown, IDWriteTextFormat, IUnknown )

            HW_EXPORT TextFormat& SetTextAlignment( DWRITE_TEXT_ALIGNMENT textAlignment );
        HW_EXPORT TextFormat& SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment );
        HW_EXPORT TextFormat& SetWordWrapping( DWRITE_WORD_WRAPPING wordWrapping );
        HW_EXPORT TextFormat& SetReadingDirection( DWRITE_READING_DIRECTION readingDirection );
        HW_EXPORT TextFormat& SetFlowDirection( DWRITE_FLOW_DIRECTION flowDirection );
        HW_EXPORT TextFormat& SetIncrementalTabStop( FLOAT incrementalTabStop );
        HW_EXPORT TextFormat& SetTrimming( DWRITE_TRIMMING const* trimmingOptions, IDWriteInlineObject* trimmingSign );
        HW_EXPORT TextFormat& SetLineSpacing( DWRITE_LINE_SPACING_METHOD lineSpacingMethod, FLOAT lineSpacing, FLOAT baseline );
        HW_EXPORT DWRITE_TEXT_ALIGNMENT GetTextAlignment( );
        HW_EXPORT DWRITE_PARAGRAPH_ALIGNMENT GetParagraphAlignment( );
        HW_EXPORT DWRITE_WORD_WRAPPING GetWordWrapping( );
        HW_EXPORT DWRITE_READING_DIRECTION GetReadingDirection( );
        HW_EXPORT DWRITE_FLOW_DIRECTION GetFlowDirection( );
        HW_EXPORT FLOAT GetIncrementalTabStop( );
        HW_EXPORT TextFormat& GetTrimming( DWRITE_TRIMMING* trimmingOptions, IDWriteInlineObject** trimmingSign );
        HW_EXPORT InlineObject GetTrimming( DWRITE_TRIMMING& trimmingOptions );
        HW_EXPORT TextFormat& GetLineSpacing( DWRITE_LINE_SPACING_METHOD* lineSpacingMethod, FLOAT* lineSpacing, FLOAT* baseline );
        HW_EXPORT TextFormat& GetFontCollection( IDWriteFontCollection** fontCollection );
        HW_EXPORT FontCollection GetFontCollection( );
        HW_EXPORT UINT32 GetFontFamilyNameLength( );
        HW_EXPORT TextFormat& GetFontFamilyName( WCHAR* fontFamilyName, UINT32 nameSize );
        HW_EXPORT std::shared_ptr<WideString> GetFontFamilyName( );
        HW_EXPORT DWRITE_FONT_WEIGHT GetFontWeight( );
        HW_EXPORT DWRITE_FONT_STYLE GetFontStyle( );
        HW_EXPORT DWRITE_FONT_STRETCH GetFontStretch( );
        HW_EXPORT FLOAT GetFontSize( );
        HW_EXPORT UINT32 GetLocaleNameLength( );
        HW_EXPORT TextFormat& GetLocaleName( WCHAR* localeName, UINT32 nameSize );
        HW_EXPORT std::shared_ptr<WideString> GetLocaleName( );
    };


    


    class Typography : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Typography, Unknown, IDWriteTypography, IUnknown )

            HW_EXPORT Typography& AddFontFeature( DWRITE_FONT_FEATURE fontFeature );
        HW_EXPORT Typography& AddFontFeatures( std::shared_ptr< std::vector<DWRITE_FONT_FEATURE> > fontFeatures );
        HW_EXPORT UINT32 GetFontFeatureCount( );
        HW_EXPORT Typography& GetFontFeature( UINT32 fontFeatureIndex, DWRITE_FONT_FEATURE* fontFeature );
        HW_EXPORT DWRITE_FONT_FEATURE GetFontFeature( UINT32 fontFeatureIndex );
        HW_EXPORT std::shared_ptr< std::vector<DWRITE_FONT_FEATURE> > GetFontFeatures( );
    };


    class TextAnalysisSource : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextAnalysisSource, Unknown, IDWriteTextAnalysisSource, IUnknown )

            HW_EXPORT TextAnalysisSource& GetTextAtPosition( UINT32 textPosition, WCHAR const** textString, UINT32* textLength );
        HW_EXPORT TextAnalysisSource& GetTextBeforePosition( UINT32 textPosition, WCHAR const** textString, UINT32* textLength );
        HW_EXPORT DWRITE_READING_DIRECTION GetParagraphReadingDirection( );
        HW_EXPORT TextAnalysisSource& GetLocaleName( UINT32 textPosition, UINT32* textLength, _Outptr_result_z_ WCHAR const** localeName );
        HW_EXPORT TextAnalysisSource& GetNumberSubstitution( UINT32 textPosition, UINT32* textLength, _Outptr_ IDWriteNumberSubstitution** numberSubstitution );
    };


    class TextAnalysisSink : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextAnalysisSink, Unknown, IDWriteTextAnalysisSink, IUnknown )

            HW_EXPORT TextAnalysisSink& SetScriptAnalysis( UINT32 textPosition, UINT32 textLength, DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis );
        HW_EXPORT TextAnalysisSink& SetLineBreakpoints( UINT32 textPosition, UINT32 textLength, DWRITE_LINE_BREAKPOINT const* lineBreakpoints );
        HW_EXPORT TextAnalysisSink& SetBidiLevel( UINT32 textPosition, UINT32 textLength, UINT8 explicitLevel, UINT8 resolvedLevel );
        HW_EXPORT TextAnalysisSink& SetNumberSubstitution( UINT32 textPosition, UINT32 textLength, IDWriteNumberSubstitution* numberSubstitution );
    };

    class TextAnalyzer : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextAnalyzer, Unknown, IDWriteTextAnalyzer, IUnknown )

            HW_EXPORT TextAnalyzer& AnalyzeScript(
                IDWriteTextAnalysisSource* analysisSource,
                UINT32 textPosition,
                UINT32 textLength,
                IDWriteTextAnalysisSink* analysisSink );

        HW_EXPORT TextAnalyzer& AnalyzeBidi(
            IDWriteTextAnalysisSource* analysisSource,
            UINT32 textPosition,
            UINT32 textLength,
            IDWriteTextAnalysisSink* analysisSink );

        HW_EXPORT TextAnalyzer& AnalyzeNumberSubstitution(
            IDWriteTextAnalysisSource* analysisSource,
            UINT32 textPosition,
            UINT32 textLength,
            IDWriteTextAnalysisSink* analysisSink );

        HW_EXPORT TextAnalyzer& AnalyzeLineBreakpoints(
            IDWriteTextAnalysisSource* analysisSource,
            UINT32 textPosition,
            UINT32 textLength,
            IDWriteTextAnalysisSink* analysisSink );

        HW_EXPORT TextAnalyzer& GetGlyphs(
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
            UINT32* actualGlyphCount );

        HW_EXPORT TextAnalyzer& GetGlyphPlacements(
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
            DWRITE_GLYPH_OFFSET* glyphOffsets );

        HW_EXPORT TextAnalyzer& GetGdiCompatibleGlyphPlacements(
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
            DWRITE_GLYPH_OFFSET* glyphOffsets );
    };

    class InlineObject : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( InlineObject, Unknown, IDWriteInlineObject, IUnknown )

            HW_EXPORT InlineObject& Draw( void* clientDrawingContext, IDWriteTextRenderer* renderer, FLOAT originX, FLOAT originY, BOOL isSideways, BOOL isRightToLeft, IUnknown* clientDrawingEffect );

        HW_EXPORT InlineObject& GetMetrics( DWRITE_INLINE_OBJECT_METRICS* metrics );

        HW_EXPORT InlineObject& GetOverhangMetrics( DWRITE_OVERHANG_METRICS* overhangs );

        HW_EXPORT InlineObject& GetBreakConditions( DWRITE_BREAK_CONDITION* breakConditionBefore, DWRITE_BREAK_CONDITION* breakConditionAfter );
    };

    class PixelSnapping : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( PixelSnapping, Unknown, IDWritePixelSnapping, IUnknown )

            HW_EXPORT PixelSnapping& IsPixelSnappingDisabled( void* clientDrawingContext, BOOL* isDisabled );

        HW_EXPORT PixelSnapping& GetCurrentTransform( void* clientDrawingContext, DWRITE_MATRIX* transform );

        HW_EXPORT PixelSnapping& GetPixelsPerDip( void* clientDrawingContext, FLOAT* pixelsPerDip );
    };


    class TextRenderer : public PixelSnapping
    {
    public:
        typedef PixelSnapping Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextRenderer, PixelSnapping, IDWriteTextRenderer, IDWritePixelSnapping )

            HW_EXPORT TextRenderer& DrawGlyphRun( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_MEASURING_MODE measuringMode, DWRITE_GLYPH_RUN const* glyphRun, DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription, IUnknown* clientDrawingEffect );

        HW_EXPORT TextRenderer& DrawUnderline( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_UNDERLINE const* underline, IUnknown* clientDrawingEffect );

        HW_EXPORT TextRenderer& DrawStrikethrough( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_STRIKETHROUGH const* strikethrough, IUnknown* clientDrawingEffect );

        HW_EXPORT TextRenderer& DrawInlineObject( void* clientDrawingContext, FLOAT originX, FLOAT originY, IDWriteInlineObject* inlineObject, BOOL isSideways, BOOL isRightToLeft, IUnknown* clientDrawingEffect );
    };


    class TextLayout : public TextFormat
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextLayout, TextFormat, IDWriteTextLayout, IDWriteTextFormat )

            HW_EXPORT TextLayout& SetMaxWidth( FLOAT maxWidth );
        HW_EXPORT TextLayout& SetMaxHeight( FLOAT maxHeight );

        HW_EXPORT TextLayout& SetFontCollection( IDWriteFontCollection* fontCollection, DWRITE_TEXT_RANGE textRange );

        HW_EXPORT TextLayout& SetFontFamilyName( WCHAR const* fontFamilyName, DWRITE_TEXT_RANGE textRange );

        HW_EXPORT TextLayout& SetFontWeight( DWRITE_FONT_WEIGHT fontWeight, DWRITE_TEXT_RANGE textRange );

        HW_EXPORT TextLayout& SetFontStyle( DWRITE_FONT_STYLE fontStyle, DWRITE_TEXT_RANGE textRange );

        HW_EXPORT TextLayout& SetFontStretch( DWRITE_FONT_STRETCH fontStretch, DWRITE_TEXT_RANGE textRange );

        HW_EXPORT TextLayout& SetFontSize( FLOAT fontSize, DWRITE_TEXT_RANGE textRange );

        HW_EXPORT TextLayout& SetUnderline( BOOL hasUnderline, DWRITE_TEXT_RANGE textRange );

        HW_EXPORT TextLayout& SetStrikethrough( BOOL hasStrikethrough, DWRITE_TEXT_RANGE textRange );

        HW_EXPORT TextLayout& SetDrawingEffect( IUnknown* drawingEffect, DWRITE_TEXT_RANGE textRange );

        HW_EXPORT TextLayout& SetInlineObject( IDWriteInlineObject* inlineObject, DWRITE_TEXT_RANGE textRange );

        HW_EXPORT TextLayout& SetTypography( IDWriteTypography* typography, DWRITE_TEXT_RANGE textRange );

        HW_EXPORT TextLayout& SetLocaleName( WCHAR const* localeName, DWRITE_TEXT_RANGE textRange );

        HW_EXPORT FLOAT GetMaxWidth( );

        HW_EXPORT FLOAT GetMaxHeight( );

        HW_EXPORT TextLayout& GetFontCollection( UINT32 currentPosition, IDWriteFontCollection** fontCollection, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& GetFontFamilyNameLength( UINT32 currentPosition, UINT32* nameLength, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& GetFontFamilyName( UINT32 currentPosition, _Out_writes_z_( nameSize ) WCHAR* fontFamilyName, UINT32 nameSize, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& GetFontWeight( UINT32 currentPosition, DWRITE_FONT_WEIGHT* fontWeight, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& GetFontStyle( UINT32 currentPosition, DWRITE_FONT_STYLE* fontStyle, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& GetFontStretch( UINT32 currentPosition, DWRITE_FONT_STRETCH* fontStretch, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& GetFontSize( UINT32 currentPosition, FLOAT* fontSize, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& GetUnderline( UINT32 currentPosition, BOOL* hasUnderline, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& GetStrikethrough( UINT32 currentPosition, BOOL* hasStrikethrough, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& GetDrawingEffect( UINT32 currentPosition, IUnknown** drawingEffect, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& GetInlineObject( UINT32 currentPosition, IDWriteInlineObject** inlineObject, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& GetTypography( UINT32 currentPosition, IDWriteTypography** typography, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& GetLocaleNameLength( UINT32 currentPosition, UINT32* nameLength, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& GetLocaleName( UINT32 currentPosition, _Out_writes_z_( nameSize ) WCHAR* localeName, UINT32 nameSize, DWRITE_TEXT_RANGE* textRange = nullptr );

        HW_EXPORT TextLayout& Draw( void* clientDrawingContext, IDWriteTextRenderer* renderer, FLOAT originX, FLOAT originY );

        HW_EXPORT TextLayout& GetLineMetrics( DWRITE_LINE_METRICS* lineMetrics, UINT32 maxLineCount, UINT32* actualLineCount );

        HW_EXPORT TextLayout& GetMetrics( DWRITE_TEXT_METRICS* textMetrics );

        HW_EXPORT TextLayout& GetOverhangMetrics( DWRITE_OVERHANG_METRICS* overhangs );

        HW_EXPORT TextLayout& GetClusterMetrics( _Out_writes_opt_( maxClusterCount ) DWRITE_CLUSTER_METRICS* clusterMetrics, UINT32 maxClusterCount, UINT32* actualClusterCount );

        HW_EXPORT TextLayout& DetermineMinWidth( FLOAT* minWidth );

        HW_EXPORT TextLayout& HitTestPoint( FLOAT pointX, FLOAT pointY, BOOL* isTrailingHit, BOOL* isInside, DWRITE_HIT_TEST_METRICS* hitTestMetrics );

        HW_EXPORT TextLayout& HitTestTextPosition( UINT32 textPosition, BOOL isTrailingHit, FLOAT* pointX, FLOAT* pointY, DWRITE_HIT_TEST_METRICS* hitTestMetrics );

        HW_EXPORT TextLayout& HitTestTextRange( UINT32 textPosition, UINT32 textLength, FLOAT originX, FLOAT originY, DWRITE_HIT_TEST_METRICS* hitTestMetrics, UINT32 maxHitTestMetricsCount, UINT32* actualHitTestMetricsCount );
    };

    



    class BitmapRenderTarget : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( BitmapRenderTarget, Unknown, IDWriteBitmapRenderTarget, IUnknown )

            HW_EXPORT BitmapRenderTarget& DrawGlyphRun( FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_MEASURING_MODE measuringMode, DWRITE_GLYPH_RUN const* glyphRun, IDWriteRenderingParams* renderingParams, COLORREF textColor, RECT* blackBoxRect = nullptr );

        HW_EXPORT HDC GetMemoryDC( );

        HW_EXPORT FLOAT GetPixelsPerDip( );

        HW_EXPORT BitmapRenderTarget& SetPixelsPerDip( FLOAT pixelsPerDip );

        HW_EXPORT BitmapRenderTarget& GetCurrentTransform( DWRITE_MATRIX* transform );

        HW_EXPORT BitmapRenderTarget& SetCurrentTransform( DWRITE_MATRIX const* transform );

        HW_EXPORT BitmapRenderTarget& GetSize( SIZE* size );

        HW_EXPORT BitmapRenderTarget& Resize( UINT32 width, UINT32 height );
    };


    class GdiInterop : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GdiInterop, Unknown, IDWriteGdiInterop, IUnknown )

            HW_EXPORT GdiInterop& CreateFontFromLOGFONT( LOGFONTW const* logFont, IDWriteFont** font );

        HW_EXPORT GdiInterop& ConvertFontToLOGFONT( IDWriteFont* font, LOGFONTW* logFont, BOOL* isSystemFont );

        HW_EXPORT GdiInterop& ConvertFontFaceToLOGFONT( IDWriteFontFace* font, LOGFONTW* logFont );

        HW_EXPORT GdiInterop& CreateFontFaceFromHdc( HDC hdc, IDWriteFontFace** fontFace );

        HW_EXPORT GdiInterop& CreateBitmapRenderTarget( HDC hdc, UINT32 width, UINT32 height, IDWriteBitmapRenderTarget** renderTarget );
    };


    class GlyphRunAnalysis : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GlyphRunAnalysis, Unknown, IDWriteGlyphRunAnalysis, IUnknown )

            HW_EXPORT GlyphRunAnalysis& GetAlphaTextureBounds( DWRITE_TEXTURE_TYPE textureType, RECT* textureBounds );

        HW_EXPORT GlyphRunAnalysis& CreateAlphaTexture( DWRITE_TEXTURE_TYPE textureType, RECT const* textureBounds, BYTE* alphaValues, UINT32 bufferSize );

        HW_EXPORT GlyphRunAnalysis& GetAlphaBlendParams( IDWriteRenderingParams* renderingParams, FLOAT* blendGamma, FLOAT* blendEnhancedContrast, FLOAT* blendClearTypeLevel );
    };


    class Factory : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Factory, Unknown, IDWriteFactory, IUnknown )

            HW_EXPORT Factory( DWRITE_FACTORY_TYPE factoryType );

        HW_EXPORT Factory& GetSystemFontCollection( IDWriteFontCollection** fontCollection, BOOL checkForUpdates = FALSE );
        HW_EXPORT FontCollection GetSystemFontCollection( bool checkForUpdates = false );

        HW_EXPORT Factory& CreateCustomFontCollection( IDWriteFontCollectionLoader* collectionLoader, void const* collectionKey, UINT32 collectionKeySize, IDWriteFontCollection** fontCollection );
        HW_EXPORT FontCollection CreateCustomFontCollection( IDWriteFontCollectionLoader* collectionLoader, void const* collectionKey, UINT32 collectionKeySize );

        HW_EXPORT Factory& RegisterFontCollectionLoader( IDWriteFontCollectionLoader* fontCollectionLoader );
        HW_EXPORT Factory& UnregisterFontCollectionLoader( IDWriteFontCollectionLoader* fontCollectionLoader );

        HW_EXPORT Factory& CreateFontFileReference( WCHAR const* filePath, FILETIME const* lastWriteTime, IDWriteFontFile** fontFile );
        HW_EXPORT FontFile CreateFontFileReference( WCHAR const* filePath, FILETIME const* lastWriteTime = nullptr );

        HW_EXPORT Factory& CreateCustomFontFileReference( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileLoader* fontFileLoader, IDWriteFontFile** fontFile );
        HW_EXPORT FontFile CreateCustomFontFileReference( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileLoader* fontFileLoader );

        HW_EXPORT Factory& CreateFontFace( DWRITE_FONT_FACE_TYPE fontFaceType, UINT32 numberOfFiles, IDWriteFontFile* const* fontFiles, UINT32 faceIndex, DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags, IDWriteFontFace** fontFace );
        HW_EXPORT FontFace CreateFontFace( DWRITE_FONT_FACE_TYPE fontFaceType, UINT32 numberOfFiles, IDWriteFontFile* const* fontFiles, UINT32 faceIndex, DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags );

        HW_EXPORT Factory& CreateRenderingParams( IDWriteRenderingParams** renderingParams );
        HW_EXPORT RenderingParams CreateRenderingParams( );

        HW_EXPORT Factory& CreateMonitorRenderingParams( HMONITOR monitor, IDWriteRenderingParams** renderingParams );
        HW_EXPORT RenderingParams CreateMonitorRenderingParams( HMONITOR monitor );

        HW_EXPORT Factory& CreateCustomRenderingParams( FLOAT gamma, FLOAT enhancedContrast, FLOAT clearTypeLevel, DWRITE_PIXEL_GEOMETRY pixelGeometry, DWRITE_RENDERING_MODE renderingMode, IDWriteRenderingParams** renderingParams );
        HW_EXPORT RenderingParams CreateCustomRenderingParams( FLOAT gamma, FLOAT enhancedContrast, FLOAT clearTypeLevel, DWRITE_PIXEL_GEOMETRY pixelGeometry, DWRITE_RENDERING_MODE renderingMode );

        HW_EXPORT Factory& RegisterFontFileLoader( IDWriteFontFileLoader* fontFileLoader );
        HW_EXPORT Factory& UnregisterFontFileLoader( IDWriteFontFileLoader* fontFileLoader );

        HW_EXPORT Factory& CreateTextFormat( WCHAR const* fontFamilyName, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName, IDWriteTextFormat** textFormat );
        HW_EXPORT TextFormat CreateTextFormat( WCHAR const* fontFamilyName, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName );
        HW_EXPORT TextFormat CreateTextFormat( WCHAR const* fontFamilyName, FLOAT fontSize );

        HW_EXPORT Factory& CreateTypography( IDWriteTypography** typography );
        HW_EXPORT Typography CreateTypography( );

        HW_EXPORT Factory& GetGdiInterop( IDWriteGdiInterop** gdiInterop );
        HW_EXPORT GdiInterop GetGdiInterop( );

        HW_EXPORT Factory& CreateTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT maxWidth, FLOAT maxHeight, IDWriteTextLayout** textLayout );
        HW_EXPORT TextLayout CreateTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT maxWidth, FLOAT maxHeight );

        HW_EXPORT Factory& CreateGdiCompatibleTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT layoutWidth, FLOAT layoutHeight, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural, IDWriteTextLayout** textLayout );
        HW_EXPORT TextLayout CreateGdiCompatibleTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT layoutWidth, FLOAT layoutHeight, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural );

        HW_EXPORT Factory& CreateEllipsisTrimmingSign( IDWriteTextFormat* textFormat, IDWriteInlineObject** trimmingSign );
        HW_EXPORT InlineObject CreateEllipsisTrimmingSign( IDWriteTextFormat* textFormat );

        HW_EXPORT Factory& CreateTextAnalyzer( IDWriteTextAnalyzer** textAnalyzer );
        HW_EXPORT TextAnalyzer CreateTextAnalyzer( );

        HW_EXPORT Factory& CreateNumberSubstitution( DWRITE_NUMBER_SUBSTITUTION_METHOD substitutionMethod, WCHAR const* localeName, BOOL ignoreUserOverride, IDWriteNumberSubstitution** numberSubstitution );

        HW_EXPORT Factory& CreateGlyphRunAnalysis( DWRITE_GLYPH_RUN const* glyphRun, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_RENDERING_MODE renderingMode, DWRITE_MEASURING_MODE measuringMode, FLOAT baselineOriginX, FLOAT baselineOriginY, IDWriteGlyphRunAnalysis** glyphRunAnalysis );
        HW_EXPORT GlyphRunAnalysis CreateGlyphRunAnalysis( DWRITE_GLYPH_RUN const* glyphRun, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_RENDERING_MODE renderingMode, DWRITE_MEASURING_MODE measuringMode, FLOAT baselineOriginX, FLOAT baselineOriginY );
    };
}

namespace Harlinn::Windows::Graphics
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
