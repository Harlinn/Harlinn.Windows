/*
   Copyright 2024-2026 Espen Harlinn

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

#include "pch.h"
#include <HWDWrite.h>

namespace Harlinn::Windows::Graphics::DirectWrite
{
    // ================================================================
    // FontFileLoader
    // ================================================================
    void FontFileLoader::CreateStreamFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileStream** fontFileStream ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateStreamFromKey( fontFileReferenceKey, fontFileReferenceKeySize, fontFileStream );
        CheckHRESULT( hr );
    }
    FontFileStream FontFileLoader::CreateStreamFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize ) const
    {
        IDWriteFontFileStream* fontFileStream = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateStreamFromKey( fontFileReferenceKey, fontFileReferenceKeySize, &fontFileStream );
        CheckHRESULT( hr );
        FontFileStream result( fontFileStream );
        return result;
    }
    // ================================================================
    // LocalFontFileLoader
    // ================================================================
    void LocalFontFileLoader::GetFilePathLengthFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, UINT32* filePathLength ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFilePathLengthFromKey( fontFileReferenceKey, fontFileReferenceKeySize, filePathLength );
        CheckHRESULT( hr );
    }
    UINT32 LocalFontFileLoader::GetFilePathLengthFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize ) const
    {
        UINT32 result = 0;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFilePathLengthFromKey( fontFileReferenceKey, fontFileReferenceKeySize, &result );
        CheckHRESULT( hr );
        return result;
    }

    void LocalFontFileLoader::GetFilePathFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, WCHAR* filePath, UINT32 filePathSize ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFilePathFromKey( fontFileReferenceKey, fontFileReferenceKeySize, filePath, filePathSize );
        CheckHRESULT( hr );
    }
    WideString LocalFontFileLoader::GetFilePathFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize ) const
    {
        UINT32 filePathSize = GetFilePathLengthFromKey( fontFileReferenceKey, fontFileReferenceKeySize );

        WideString result;
        result.SetLength( filePathSize );

        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFilePathFromKey( fontFileReferenceKey, fontFileReferenceKeySize, result.data( ), filePathSize );
        CheckHRESULT( hr );
        return result;
    }

    void LocalFontFileLoader::GetLastWriteTimeFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, FILETIME* lastWriteTime ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLastWriteTimeFromKey( fontFileReferenceKey, fontFileReferenceKeySize, lastWriteTime );
        CheckHRESULT( hr );
    }
    FILETIME LocalFontFileLoader::GetLastWriteTimeFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize ) const
    {
        FILETIME result;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLastWriteTimeFromKey( fontFileReferenceKey, fontFileReferenceKeySize, &result );
        CheckHRESULT( hr );
        return result;
    }

    // ================================================================
    // FontFileStream
    // ================================================================
    void FontFileStream::ReadFileFragment( void const** fragmentStart, UINT64 fileOffset, UINT64 fragmentSize, void** fragmentContext ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->ReadFileFragment( fragmentStart, fileOffset, fragmentSize, fragmentContext );
        CheckHRESULT( hr );
    }

    void FontFileStream::ReleaseFileFragment( void* fragmentContext ) const
    {
        InterfaceType* pInterface = GetInterface( );
        pInterface->ReleaseFileFragment( fragmentContext );
    }

    void FontFileStream::GetFileSize( UINT64* fileSize ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFileSize( fileSize );
        CheckHRESULT( hr );
    }
    UINT64 FontFileStream::GetFileSize( ) const
    {
        UINT64 result = 0;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFileSize( &result );
        CheckHRESULT( hr );
        return result;
    }

    void FontFileStream::GetLastWriteTime( UINT64* lastWriteTime ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLastWriteTime( lastWriteTime );
        CheckHRESULT( hr );
    }
    UINT64 FontFileStream::GetLastWriteTime( ) const
    {
        UINT64 result = 0;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLastWriteTime( &result );
        CheckHRESULT( hr );
        return result;
    }

    // ================================================================
    // FontFile
    // ================================================================
    void FontFile::GetReferenceKey( void const** fontFileReferenceKey, UINT32* fontFileReferenceKeySize ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetReferenceKey( fontFileReferenceKey, fontFileReferenceKeySize );
        CheckHRESULT( hr );
    }
    void FontFile::GetLoader( IDWriteFontFileLoader** fontFileLoader ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLoader( fontFileLoader );
        CheckHRESULT( hr );
    }
    FontFileLoader FontFile::GetLoader( ) const
    {
        IDWriteFontFileLoader* fontFileLoader = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLoader( &fontFileLoader );
        CheckHRESULT( hr );
        FontFileLoader result( fontFileLoader );
        return result;
    }
    void FontFile::Analyze( BOOL* isSupportedFontType, DWRITE_FONT_FILE_TYPE* fontFileType, _Out_opt_ DWRITE_FONT_FACE_TYPE* fontFaceType, UINT32* numberOfFaces ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->Analyze( isSupportedFontType, fontFileType, fontFaceType, numberOfFaces );
        CheckHRESULT( hr );
    }
    void FontFile::Analyze( BOOL& isSupportedFontType, DWRITE_FONT_FILE_TYPE& fontFileType, _Out_opt_ DWRITE_FONT_FACE_TYPE& fontFaceType, UINT32& numberOfFaces ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->Analyze( &isSupportedFontType, &fontFileType, &fontFaceType, &numberOfFaces );
        CheckHRESULT( hr );
    }

    void FontFile::Analyze( BOOL& isSupportedFontType, DWRITE_FONT_FILE_TYPE& fontFileType, UINT32& numberOfFaces ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->Analyze( &isSupportedFontType, &fontFileType, nullptr, &numberOfFaces );
        CheckHRESULT( hr );
    }

    // ================================================================
    // RenderingParams
    // ================================================================
    FLOAT RenderingParams::GetGamma( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetGamma( );
    }
    FLOAT RenderingParams::GetEnhancedContrast( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetEnhancedContrast( );
    }
    FLOAT RenderingParams::GetClearTypeLevel( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetClearTypeLevel( );
    }
    DWRITE_PIXEL_GEOMETRY RenderingParams::GetPixelGeometry( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetPixelGeometry( );
    }
    DWRITE_RENDERING_MODE RenderingParams::GetRenderingMode( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetRenderingMode( );
    }

    // ================================================================
    // FontFace
    // ================================================================
    DWRITE_FONT_FACE_TYPE FontFace::GetType( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetType( );
    }
    void FontFace::GetFiles( _Inout_ UINT32* numberOfFiles, IDWriteFontFile** fontFiles ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFiles( numberOfFiles, fontFiles );
        CheckHRESULT( hr );
    }

    UINT32 FontFace::GetNumberOfFiles( ) const
    {
        UINT32 result;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFiles( &result, nullptr );
        CheckHRESULT( hr );
        return result;
    }

    std::shared_ptr< std::vector<FontFile> > FontFace::GetFiles( ) const
    {
        UINT32 numberOfFiles = GetNumberOfFiles( );
        IDWriteFontFile** fontFiles = reinterpret_cast<IDWriteFontFile**>( alloca( numberOfFiles * sizeof( IDWriteFontFile* ) ) );

        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFiles( &numberOfFiles, fontFiles );
        CheckHRESULT( hr );

        std::shared_ptr< std::vector<FontFile> > result = std::make_shared< std::vector<FontFile> >( numberOfFiles );

        for ( std::vector<FontFile>::size_type i = 0; i < numberOfFiles; i++ )
        {
            IDWriteFontFile* fontFile = fontFiles[i];
            FontFile writeFontFile( fontFile );
            result->push_back( writeFontFile );
        }

        return result;
    }

    UINT32 FontFace::GetIndex( ) const
    {
        UINT32 result;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFiles( &result, nullptr );
        CheckHRESULT( hr );
        return result;
    }

    DWRITE_FONT_SIMULATIONS FontFace::GetSimulations( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetSimulations( );
    }
    BOOL FontFace::IsSymbolFont( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetSimulations( );
    }
    void FontFace::GetMetrics( DWRITE_FONT_METRICS* fontFaceMetrics ) const
    {
        CheckPointerNotNull( fontFaceMetrics );
        InterfaceType* pInterface = GetInterface( );
        pInterface->GetMetrics( fontFaceMetrics );
    }
    void FontFace::GetMetrics( DWRITE_FONT_METRICS& fontFaceMetrics ) const
    {
        InterfaceType* pInterface = GetInterface( );
        pInterface->GetMetrics( &fontFaceMetrics );
    }
    UINT16 FontFace::GetGlyphCount( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetGlyphCount( );
    }
    void FontFace::GetDesignGlyphMetrics( UINT16 const* glyphIndices, UINT32 glyphCount, DWRITE_GLYPH_METRICS* glyphMetrics, BOOL isSideways ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetDesignGlyphMetrics( glyphIndices, glyphCount, glyphMetrics, isSideways );
        CheckHRESULT( hr );
    }
    void FontFace::GetGlyphIndices( UINT32 const* codePoints, UINT32 codePointCount, UINT16* glyphIndices ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGlyphIndices( codePoints, codePointCount, glyphIndices );
        CheckHRESULT( hr );
    }
    void FontFace::TryGetFontTable( UINT32 openTypeTableTag, const void** tableData, UINT32* tableSize, void** tableContext, BOOL* exists ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->TryGetFontTable( openTypeTableTag, tableData, tableSize, tableContext, exists );
        CheckHRESULT( hr );
    }
    void FontFace::ReleaseFontTable( void* tableContext ) const
    {
        InterfaceType* pInterface = GetInterface( );
        pInterface->ReleaseFontTable( tableContext );
    }
    void FontFace::GetGlyphRunOutline( FLOAT emSize, UINT16 const* glyphIndices, FLOAT const* glyphAdvances, DWRITE_GLYPH_OFFSET const* glyphOffsets, UINT32 glyphCount, BOOL isSideways, BOOL isRightToLeft, IDWriteGeometrySink* geometrySink ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGlyphRunOutline( emSize, glyphIndices, glyphAdvances, glyphOffsets, glyphCount, isSideways, isRightToLeft, geometrySink );
        CheckHRESULT( hr );
    }
    void FontFace::GetRecommendedRenderingMode( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MEASURING_MODE measuringMode, IDWriteRenderingParams* renderingParams, DWRITE_RENDERING_MODE* renderingMode ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetRecommendedRenderingMode( emSize, pixelsPerDip, measuringMode, renderingParams, renderingMode );
        CheckHRESULT( hr );
    }
    DWRITE_RENDERING_MODE FontFace::GetRecommendedRenderingMode( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MEASURING_MODE measuringMode, IDWriteRenderingParams* renderingParams ) const
    {
        DWRITE_RENDERING_MODE result = DWRITE_RENDERING_MODE( 0 );
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetRecommendedRenderingMode( emSize, pixelsPerDip, measuringMode, renderingParams, &result );
        CheckHRESULT( hr );
        return result;
    }

    void FontFace::GetGdiCompatibleMetrics( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_FONT_METRICS* fontFaceMetrics ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGdiCompatibleMetrics( emSize, pixelsPerDip, transform, fontFaceMetrics );
        CheckHRESULT( hr );
    }
    void FontFace::GetGdiCompatibleGlyphMetrics( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural, UINT16 const* glyphIndices, UINT32 glyphCount, DWRITE_GLYPH_METRICS* glyphMetrics, BOOL isSideways ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGdiCompatibleGlyphMetrics( emSize, pixelsPerDip, transform, useGdiNatural, glyphIndices, glyphCount, glyphMetrics, isSideways );
        CheckHRESULT( hr );
    }

    // ================================================================
    // FontCollectionLoader
    // ================================================================
    void FontCollectionLoader::CreateEnumeratorFromKey( IDWriteFactory* factory, void const* collectionKey, UINT32 collectionKeySize, IDWriteFontFileEnumerator** fontFileEnumerator ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateEnumeratorFromKey( factory, collectionKey, collectionKeySize, fontFileEnumerator );
        CheckHRESULT( hr );
    }

    FontFileEnumerator FontCollectionLoader::CreateEnumeratorFromKey( IDWriteFactory* factory, void const* collectionKey, UINT32 collectionKeySize ) const
    {
        IDWriteFontFileEnumerator* fontFileEnumerator;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateEnumeratorFromKey( factory, collectionKey, collectionKeySize, &fontFileEnumerator );
        CheckHRESULT( hr );
        FontFileEnumerator result( fontFileEnumerator );
        return result;
    }

    // ================================================================
    // FontFileEnumerator
    // ================================================================
    void FontFileEnumerator::MoveNext( BOOL* hasCurrentFile ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->MoveNext( hasCurrentFile );
        CheckHRESULT( hr );
    }
    bool FontFileEnumerator::MoveNext( ) const
    {
        BOOL hasCurrentFile;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->MoveNext( &hasCurrentFile );
        CheckHRESULT( hr );
        return hasCurrentFile != FALSE;
    }

    void FontFileEnumerator::GetCurrentFontFile( IDWriteFontFile** fontFile ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetCurrentFontFile( fontFile );
        CheckHRESULT( hr );
    }
    FontFile FontFileEnumerator::GetCurrentFontFile( ) const
    {
        IDWriteFontFile* fontFile = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetCurrentFontFile( &fontFile );
        CheckHRESULT( hr );
        FontFile result( fontFile );
        return result;
    }

    // ================================================================
    // LocalizedStrings
    // ================================================================
    UINT32 LocalizedStrings::GetCount( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetCount( );
    }
    void LocalizedStrings::FindLocaleName( WCHAR const* localeName, UINT32* index, BOOL* exists ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->FindLocaleName( localeName, index, exists );
        CheckHRESULT( hr );
    }
    bool LocalizedStrings::FindLocaleName( WCHAR const* localeName, UINT32* index ) const
    {
        BOOL exists = FALSE;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->FindLocaleName( localeName, index, &exists );
        CheckHRESULT( hr );
        return exists != FALSE;
    }
    void LocalizedStrings::GetLocaleNameLength( UINT32 index, UINT32* length ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleNameLength( index, length );
        CheckHRESULT( hr );
    }
    UINT32 LocalizedStrings::GetLocaleNameLength( UINT32 index ) const
    {
        UINT32 result = 0;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleNameLength( index, &result );
        CheckHRESULT( hr );
        return result;
    }

    void LocalizedStrings::GetLocaleName( UINT32 index, WCHAR* localeName, UINT32 size ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleName( index, localeName, size );
        CheckHRESULT( hr );
    }
    WideString LocalizedStrings::GetLocaleName( UINT32 index ) const
    {
        UINT32 size = GetLocaleNameLength( index );
        WideString result;
        result.resize( size );
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleName( index, result.data( ), size );
        CheckHRESULT( hr );
        return result;
    }

    void LocalizedStrings::GetStringLength( UINT32 index, UINT32* length ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetStringLength( index, length );
        CheckHRESULT( hr );
    }
    UINT32 LocalizedStrings::GetStringLength( UINT32 index ) const
    {
        UINT32 result = 0;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetStringLength( index, &result );
        CheckHRESULT( hr );
        return result;
    }

    void LocalizedStrings::GetString( UINT32 index, WCHAR* stringBuffer, UINT32 size ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetString( index, stringBuffer, size );
        CheckHRESULT( hr );
    }
    WideString LocalizedStrings::GetString( UINT32 index ) const
    {
        UINT32 size = GetStringLength( index );
        WideString result;
        result.resize( size );
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetString( index, result.data( ), size );
        CheckHRESULT( hr );
        return result;
    }

    // ================================================================
    // FontCollection
    // ================================================================
    UINT32 FontCollection::GetFontFamilyCount( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontFamilyCount( );
    }

    void FontCollection::GetFontFamily( UINT32 index, IDWriteFontFamily** fontFamily ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamily( index, fontFamily );
        CheckHRESULT( hr );
    }
    FontFamily FontCollection::GetFontFamily( UINT32 index ) const
    {
        IDWriteFontFamily* fontFamily = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamily( index, &fontFamily );
        CheckHRESULT( hr );
        FontFamily result( fontFamily );
        return result;
    }
    std::vector<FontFamily> FontCollection::GetFontFamilies( ) const
    {
        std::vector<FontFamily>::size_type fontFamilyCount = GetFontFamilyCount( );
        std::vector<FontFamily> result( fontFamilyCount );
        for ( UINT32 i = 0; i < fontFamilyCount; i++ )
        {
            FontFamily writeFontFamily = GetFontFamily( i );
            result.push_back( writeFontFamily );
        }
        return result;
    }

    void FontCollection::FindFamilyName( WCHAR const* familyName, UINT32* index, BOOL* exists ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->FindFamilyName( familyName, index, exists );
        CheckHRESULT( hr );
    }
    bool FontCollection::FindFamilyName( WCHAR const* familyName, UINT32* index ) const
    {
        BOOL exists = FALSE;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->FindFamilyName( familyName, index, &exists );
        CheckHRESULT( hr );
        return exists != FALSE;
    }

    void FontCollection::GetFontFromFontFace( IDWriteFontFace* fontFace, IDWriteFont** font ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFromFontFace( fontFace, font );
        CheckHRESULT( hr );
    }
    Font FontCollection::GetFontFromFontFace( IDWriteFontFace* fontFace ) const
    {
        IDWriteFont* font = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFromFontFace( fontFace, &font );
        CheckHRESULT( hr );
        Font result( font );
        return result;
    }

    // ================================================================
    // FontList
    // ================================================================
    void FontList::GetFontCollection( IDWriteFontCollection** fontCollection ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontCollection( fontCollection );
        CheckHRESULT( hr );
    }
    FontCollection FontList::GetFontCollection( ) const
    {
        IDWriteFontCollection* fontCollection = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontCollection( &fontCollection );
        CheckHRESULT( hr );
        FontCollection result( fontCollection );
        return result;
    }
    UINT32 FontList::GetFontCount( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontCount( );
    }
    void FontList::GetFont( UINT32 index, IDWriteFont** font ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFont( index, font );
        CheckHRESULT( hr );
    }
    Font FontList::GetFont( UINT32 index ) const
    {
        IDWriteFont* font;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFont( index, &font );
        CheckHRESULT( hr );
        Font result( font );
        return result;
    }
    // ================================================================
    // FontFamily
    // ================================================================
    void FontFamily::GetFamilyNames( IDWriteLocalizedStrings** names ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFamilyNames( names );
        CheckHRESULT( hr );
    }
    LocalizedStrings FontFamily::GetFamilyNames( ) const
    {
        IDWriteLocalizedStrings* names = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFamilyNames( &names );
        CheckHRESULT( hr );
        LocalizedStrings result( names );
        return result;
    }
    void FontFamily::GetFirstMatchingFont( DWRITE_FONT_WEIGHT  weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style, IDWriteFont** matchingFont ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFirstMatchingFont( weight, stretch, style, matchingFont );
        CheckHRESULT( hr );
    }
    Font FontFamily::GetFirstMatchingFont( DWRITE_FONT_WEIGHT  weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style ) const
    {
        IDWriteFont* matchingFont = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFirstMatchingFont( weight, stretch, style, &matchingFont );
        CheckHRESULT( hr );
        Font result( matchingFont );
        return result;
    }
    void FontFamily::GetMatchingFonts( DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style, IDWriteFontList** matchingFonts ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetMatchingFonts( weight, stretch, style, matchingFonts );
        CheckHRESULT( hr );
    }
    FontList FontFamily::GetMatchingFonts( DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style ) const
    {
        IDWriteFontList* matchingFonts = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetMatchingFonts( weight, stretch, style, &matchingFonts );
        CheckHRESULT( hr );
        FontList result( matchingFonts );
        return result;
    }

    // ================================================================
    // Font
    // ================================================================
    void Font::GetFontFamily( IDWriteFontFamily** fontFamily ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamily( fontFamily );
        CheckHRESULT( hr );
    }
    FontFamily Font::GetFontFamily( ) const
    {
        IDWriteFontFamily* fontFamily = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamily( &fontFamily );
        CheckHRESULT( hr );
        FontFamily result( fontFamily );
        return result;
    }
    DWRITE_FONT_WEIGHT Font::GetWeight( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetWeight( );
    }
    DWRITE_FONT_STRETCH Font::GetStretch( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetStretch( );
    }
    DWRITE_FONT_STYLE Font::GetStyle( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetStyle( );
    }
    bool Font::IsSymbolFont( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->IsSymbolFont( ) != FALSE;
    }
    void Font::GetFaceNames( IDWriteLocalizedStrings** names ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFaceNames( names );
        CheckHRESULT( hr );
    }
    LocalizedStrings Font::GetFaceNames( ) const
    {
        IDWriteLocalizedStrings* names = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFaceNames( &names );
        CheckHRESULT( hr );
        LocalizedStrings result( names );
        return result;
    }
    void Font::GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_ID informationalStringID, IDWriteLocalizedStrings** informationalStrings, BOOL* exists ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetInformationalStrings( informationalStringID, informationalStrings, exists );
        CheckHRESULT( hr );
    }
    DWRITE_FONT_SIMULATIONS Font::GetSimulations( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetSimulations( );
    }
    void Font::GetMetrics( DWRITE_FONT_METRICS* fontMetrics ) const
    {
        InterfaceType* pInterface = GetInterface( );
        pInterface->GetMetrics( fontMetrics );
    }
    void Font::HasCharacter( UINT32 unicodeValue, BOOL* exists ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->HasCharacter( unicodeValue, exists );
        CheckHRESULT( hr );
    }
    bool Font::HasCharacter( UINT32 unicodeValue ) const
    {
        BOOL exists = FALSE;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->HasCharacter( unicodeValue, &exists );
        CheckHRESULT( hr );
        return exists != FALSE;
    }
    void Font::CreateFontFace( IDWriteFontFace** fontFace ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFace( fontFace );
        CheckHRESULT( hr );
    }
    FontFace Font::CreateFontFace( ) const
    {
        IDWriteFontFace* fontFace = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFace( &fontFace );
        CheckHRESULT( hr );
        FontFace result( fontFace );
        return result;
    }
    // ================================================================
    // TextFormat
    // ================================================================
    void TextFormat::SetTextAlignment( DWRITE_TEXT_ALIGNMENT textAlignment ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetTextAlignment( textAlignment );
        CheckHRESULT( hr );
    }
    void TextFormat::SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetParagraphAlignment( paragraphAlignment );
        CheckHRESULT( hr );
    }
    void TextFormat::SetWordWrapping( DWRITE_WORD_WRAPPING wordWrapping ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetWordWrapping( wordWrapping );
        CheckHRESULT( hr );
    }
    void TextFormat::SetReadingDirection( DWRITE_READING_DIRECTION readingDirection ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetReadingDirection( readingDirection );
        CheckHRESULT( hr );
    }
    void TextFormat::SetFlowDirection( DWRITE_FLOW_DIRECTION flowDirection ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFlowDirection( flowDirection );
        CheckHRESULT( hr );
    }
    void TextFormat::SetIncrementalTabStop( FLOAT incrementalTabStop ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetIncrementalTabStop( incrementalTabStop );
        CheckHRESULT( hr );
    }
    void TextFormat::SetTrimming( DWRITE_TRIMMING const* trimmingOptions, IDWriteInlineObject* trimmingSign ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetTrimming( trimmingOptions, trimmingSign );
        CheckHRESULT( hr );
    }
    void TextFormat::SetLineSpacing( DWRITE_LINE_SPACING_METHOD lineSpacingMethod, FLOAT lineSpacing, FLOAT baseline ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetLineSpacing( lineSpacingMethod, lineSpacing, baseline );
        CheckHRESULT( hr );
    }
    DWRITE_TEXT_ALIGNMENT TextFormat::GetTextAlignment( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetTextAlignment( );
    }
    DWRITE_PARAGRAPH_ALIGNMENT TextFormat::GetParagraphAlignment( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetParagraphAlignment( );
    }
    DWRITE_WORD_WRAPPING TextFormat::GetWordWrapping( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetWordWrapping( );
    }
    DWRITE_READING_DIRECTION TextFormat::GetReadingDirection( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetReadingDirection( );
    }
    DWRITE_FLOW_DIRECTION TextFormat::GetFlowDirection( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFlowDirection( );
    }
    FLOAT TextFormat::GetIncrementalTabStop( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetIncrementalTabStop( );
    }
    void TextFormat::GetTrimming( DWRITE_TRIMMING* trimmingOptions, IDWriteInlineObject** trimmingSign ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetTrimming( trimmingOptions, trimmingSign );
        CheckHRESULT( hr );
    }
    InlineObject TextFormat::GetTrimming( DWRITE_TRIMMING& trimmingOptions ) const
    {
        IDWriteInlineObject* trimmingSign = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetTrimming( &trimmingOptions, &trimmingSign );
        CheckHRESULT( hr );
        InlineObject result( trimmingSign );
        return result;
    }
    void TextFormat::GetLineSpacing( DWRITE_LINE_SPACING_METHOD* lineSpacingMethod, FLOAT* lineSpacing, FLOAT* baseline ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLineSpacing( lineSpacingMethod, lineSpacing, baseline );
        CheckHRESULT( hr );
    }
    void TextFormat::GetFontCollection( IDWriteFontCollection** fontCollection ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontCollection( fontCollection );
        CheckHRESULT( hr );
    }
    FontCollection TextFormat::GetFontCollection( ) const
    {
        IDWriteFontCollection* fontCollection = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontCollection( &fontCollection );
        CheckHRESULT( hr );
        FontCollection result( fontCollection );
        return result;
    }

    UINT32 TextFormat::GetFontFamilyNameLength( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontFamilyNameLength( );
    }
    void TextFormat::GetFontFamilyName( WCHAR* fontFamilyName, UINT32 nameSize ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamilyName( fontFamilyName, nameSize );
        CheckHRESULT( hr );
    }
    WideString TextFormat::GetFontFamilyName( ) const
    {
        UINT32 nameSize = GetFontFamilyNameLength( );
        WideString result;
        result.resize( nameSize );
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamilyName( result.data( ), nameSize );
        CheckHRESULT( hr );
        return result;
    }
    DWRITE_FONT_WEIGHT TextFormat::GetFontWeight( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontWeight( );
    }
    DWRITE_FONT_STYLE TextFormat::GetFontStyle( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontStyle( );
    }
    DWRITE_FONT_STRETCH TextFormat::GetFontStretch( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontStretch( );
    }
    FLOAT TextFormat::GetFontSize( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontSize( );
    }
    UINT32 TextFormat::GetLocaleNameLength( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetLocaleNameLength( );
    }
    void TextFormat::GetLocaleName( WCHAR* localeName, UINT32 nameSize ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleName( localeName, nameSize );
        CheckHRESULT( hr );
    }
    WideString TextFormat::GetLocaleName( ) const
    {
        UINT32 nameSize = GetLocaleNameLength( );
        WideString result;
        result.resize( nameSize );
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleName( result.data( ), nameSize );
        CheckHRESULT( hr );
        return result;
    }
    // ================================================================
    // Typography
    // ================================================================
    void Typography::AddFontFeature( DWRITE_FONT_FEATURE fontFeature ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->AddFontFeature( fontFeature );
        CheckHRESULT( hr );
    }
    void Typography::AddFontFeatures( std::shared_ptr< std::vector<DWRITE_FONT_FEATURE> > fontFeatures ) const
    {
        const std::vector<DWRITE_FONT_FEATURE>& elements = *fontFeatures.get( );
        for ( DWRITE_FONT_FEATURE fontFeature : elements )
        {
            AddFontFeature( fontFeature );
        }
    }
    UINT32 Typography::GetFontFeatureCount( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontFeatureCount( );
    }
    void Typography::GetFontFeature( UINT32 fontFeatureIndex, DWRITE_FONT_FEATURE* fontFeature ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFeature( fontFeatureIndex, fontFeature );
        CheckHRESULT( hr );
    }
    DWRITE_FONT_FEATURE Typography::GetFontFeature( UINT32 fontFeatureIndex ) const
    {
        DWRITE_FONT_FEATURE fontFeature;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFeature( fontFeatureIndex, &fontFeature );
        CheckHRESULT( hr );
        return fontFeature;
    }
    std::vector<DWRITE_FONT_FEATURE> Typography::GetFontFeatures( ) const
    {
        std::vector<DWRITE_FONT_FEATURE>::size_type fontFeatureCount = GetFontFeatureCount( );
        std::vector<DWRITE_FONT_FEATURE> result( fontFeatureCount );
        for ( UINT32 i = 0; i < fontFeatureCount; i++ )
        {
            DWRITE_FONT_FEATURE fontFeature = GetFontFeature( i );
            result.push_back( fontFeature );
        }
        return result;
    }

    // ================================================================
    // TextAnalysisSource
    // ================================================================
    void TextAnalysisSource::GetTextAtPosition( UINT32 textPosition, WCHAR const** textString, UINT32* textLength ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetTextAtPosition( textPosition, textString, textLength );
        CheckHRESULT( hr );
    }
    void TextAnalysisSource::GetTextBeforePosition( UINT32 textPosition, WCHAR const** textString, UINT32* textLength ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetTextBeforePosition( textPosition, textString, textLength );
        CheckHRESULT( hr );
    }
    DWRITE_READING_DIRECTION TextAnalysisSource::GetParagraphReadingDirection( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetParagraphReadingDirection( );
    }
    void TextAnalysisSource::GetLocaleName( UINT32 textPosition, UINT32* textLength, _Outptr_result_z_ WCHAR const** localeName ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleName( textPosition, textLength, localeName );
        CheckHRESULT( hr );
    }
    void TextAnalysisSource::GetNumberSubstitution( UINT32 textPosition, UINT32* textLength, _Outptr_ IDWriteNumberSubstitution** numberSubstitution ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetNumberSubstitution( textPosition, textLength, numberSubstitution );
        CheckHRESULT( hr );
    }

    // ================================================================
    // TextAnalysisSink
    // ================================================================
    void TextAnalysisSink::SetScriptAnalysis( UINT32 textPosition, UINT32 textLength, DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetScriptAnalysis( textPosition, textLength, scriptAnalysis );
        CheckHRESULT( hr );
    }
    void TextAnalysisSink::SetLineBreakpoints( UINT32 textPosition, UINT32 textLength, DWRITE_LINE_BREAKPOINT const* lineBreakpoints ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetLineBreakpoints( textPosition, textLength, lineBreakpoints );
        CheckHRESULT( hr );
    }
    void TextAnalysisSink::SetBidiLevel( UINT32 textPosition, UINT32 textLength, UINT8 explicitLevel, UINT8 resolvedLevel ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetBidiLevel( textPosition, textLength, explicitLevel, resolvedLevel );
        CheckHRESULT( hr );
    }
    void TextAnalysisSink::SetNumberSubstitution( UINT32 textPosition, UINT32 textLength, IDWriteNumberSubstitution* numberSubstitution ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetNumberSubstitution( textPosition, textLength, numberSubstitution );
        CheckHRESULT( hr );
    }
    // ================================================================
    // TextAnalyzer
    // ================================================================
    void TextAnalyzer::AnalyzeScript(
        IDWriteTextAnalysisSource* analysisSource,
        UINT32 textPosition,
        UINT32 textLength,
        IDWriteTextAnalysisSink* analysisSink ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->AnalyzeScript( analysisSource, textPosition, textLength, analysisSink );
        CheckHRESULT( hr );
    }

    void TextAnalyzer::AnalyzeBidi(
        IDWriteTextAnalysisSource* analysisSource,
        UINT32 textPosition,
        UINT32 textLength,
        IDWriteTextAnalysisSink* analysisSink ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->AnalyzeBidi( analysisSource, textPosition, textLength, analysisSink );
        CheckHRESULT( hr );
    }

    void TextAnalyzer::AnalyzeNumberSubstitution(
        IDWriteTextAnalysisSource* analysisSource,
        UINT32 textPosition,
        UINT32 textLength,
        IDWriteTextAnalysisSink* analysisSink ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->AnalyzeNumberSubstitution( analysisSource, textPosition, textLength, analysisSink );
        CheckHRESULT( hr );
    }

    void TextAnalyzer::AnalyzeLineBreakpoints(
        IDWriteTextAnalysisSource* analysisSource,
        UINT32 textPosition,
        UINT32 textLength,
        IDWriteTextAnalysisSink* analysisSink ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->AnalyzeLineBreakpoints( analysisSource, textPosition, textLength, analysisSink );
        CheckHRESULT( hr );
    }

    void TextAnalyzer::GetGlyphs(
        WCHAR const* textString,
        UINT32 textLength,
        IDWriteFontFace* fontFace,
        BOOL isSideways,
        BOOL isRightToLeft,
        DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis,
        _In_opt_z_ WCHAR const* localeName,
        IDWriteNumberSubstitution* numberSubstitution,
        DWRITE_TYPOGRAPHIC_FEATURES const** features,
        UINT32 const* featureRangeLengths,
        UINT32 featureRanges,
        UINT32 maxGlyphCount,
        UINT16* clusterMap,
        DWRITE_SHAPING_TEXT_PROPERTIES* textProps,
        UINT16* glyphIndices,
        DWRITE_SHAPING_GLYPH_PROPERTIES* glyphProps,
        UINT32* actualGlyphCount ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGlyphs( textString, textLength, fontFace, isSideways, isRightToLeft, scriptAnalysis, localeName, numberSubstitution, features, featureRangeLengths, featureRanges, maxGlyphCount, clusterMap, textProps, glyphIndices, glyphProps, actualGlyphCount );
        CheckHRESULT( hr );
    }

    void TextAnalyzer::GetGlyphPlacements(
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
        _In_opt_z_ WCHAR const* localeName,
        DWRITE_TYPOGRAPHIC_FEATURES const** features,
        UINT32 const* featureRangeLengths,
        UINT32 featureRanges,
        FLOAT* glyphAdvances,
        DWRITE_GLYPH_OFFSET* glyphOffsets ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGlyphPlacements( textString, clusterMap, textProps, textLength, glyphIndices, glyphProps, glyphCount, fontFace, fontEmSize, isSideways, isRightToLeft, scriptAnalysis, localeName, features, featureRangeLengths, featureRanges, glyphAdvances, glyphOffsets );
        CheckHRESULT( hr );
    }

    void TextAnalyzer::GetGdiCompatibleGlyphPlacements(
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
        _In_opt_z_ WCHAR const* localeName,
        DWRITE_TYPOGRAPHIC_FEATURES const** features,
        UINT32 const* featureRangeLengths,
        UINT32 featureRanges,
        FLOAT* glyphAdvances,
        DWRITE_GLYPH_OFFSET* glyphOffsets ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGdiCompatibleGlyphPlacements( textString, clusterMap, textProps, textLength, glyphIndices, glyphProps, glyphCount, fontFace, fontEmSize, pixelsPerDip, transform, useGdiNatural, isSideways, isRightToLeft, scriptAnalysis, localeName, features, featureRangeLengths, featureRanges, glyphAdvances, glyphOffsets );
        CheckHRESULT( hr );
    }


    // ================================================================
    // InlineObject
    // ================================================================
    void InlineObject::Draw( void* clientDrawingContext, IDWriteTextRenderer* renderer, FLOAT originX, FLOAT originY, BOOL isSideways, BOOL isRightToLeft, IUnknown* clientDrawingEffect ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->Draw( clientDrawingContext, renderer, originX, originY, isSideways, isRightToLeft, clientDrawingEffect );
        CheckHRESULT( hr );
    }
    void InlineObject::GetMetrics( DWRITE_INLINE_OBJECT_METRICS* metrics ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetMetrics( metrics );
        CheckHRESULT( hr );
    }

    void InlineObject::GetOverhangMetrics( DWRITE_OVERHANG_METRICS* overhangs ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetOverhangMetrics( overhangs );
        CheckHRESULT( hr );
    }
    void InlineObject::GetBreakConditions( DWRITE_BREAK_CONDITION* breakConditionBefore, DWRITE_BREAK_CONDITION* breakConditionAfter ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetBreakConditions( breakConditionBefore, breakConditionAfter );
        CheckHRESULT( hr );
    }

    // ================================================================
    // PixelSnapping
    // ================================================================
    void PixelSnapping::IsPixelSnappingDisabled( void* clientDrawingContext, BOOL* isDisabled ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->IsPixelSnappingDisabled( clientDrawingContext, isDisabled );
        CheckHRESULT( hr );
    }
    void PixelSnapping::GetCurrentTransform( void* clientDrawingContext, DWRITE_MATRIX* transform ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetCurrentTransform( clientDrawingContext, transform );
        CheckHRESULT( hr );
    }
    void PixelSnapping::GetPixelsPerDip( void* clientDrawingContext, FLOAT* pixelsPerDip ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetPixelsPerDip( clientDrawingContext, pixelsPerDip );
        CheckHRESULT( hr );
    }

    // ================================================================
    // TextRenderer
    // ================================================================
    void TextRenderer::DrawGlyphRun( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_MEASURING_MODE measuringMode, DWRITE_GLYPH_RUN const* glyphRun, DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription, IUnknown* clientDrawingEffect ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->DrawGlyphRun( clientDrawingContext, baselineOriginX, baselineOriginY, measuringMode, glyphRun, glyphRunDescription, clientDrawingEffect );
        CheckHRESULT( hr );
    }
    void TextRenderer::DrawUnderline( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_UNDERLINE const* underline, IUnknown* clientDrawingEffect ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->DrawUnderline( clientDrawingContext, baselineOriginX, baselineOriginY, underline, clientDrawingEffect );
        CheckHRESULT( hr );
    }
    void TextRenderer::DrawStrikethrough( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_STRIKETHROUGH const* strikethrough, IUnknown* clientDrawingEffect ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->DrawStrikethrough( clientDrawingContext, baselineOriginX, baselineOriginY, strikethrough, clientDrawingEffect );
        CheckHRESULT( hr );
    }
    void TextRenderer::DrawInlineObject( void* clientDrawingContext, FLOAT originX, FLOAT originY, IDWriteInlineObject* inlineObject, BOOL isSideways, BOOL isRightToLeft, IUnknown* clientDrawingEffect ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->DrawInlineObject( clientDrawingContext, originX, originY, inlineObject, isSideways, isRightToLeft, clientDrawingEffect );
        CheckHRESULT( hr );
    }
    // ================================================================
    // 
    // ================================================================
    void TextLayout::SetMaxWidth( FLOAT maxWidth ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetMaxWidth( maxWidth );
        CheckHRESULT( hr );
    }
    void TextLayout::SetMaxHeight( FLOAT maxHeight ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetMaxHeight( maxHeight );
        CheckHRESULT( hr );
    }

    void TextLayout::SetFontCollection( IDWriteFontCollection* fontCollection, DWRITE_TEXT_RANGE textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFontCollection( fontCollection, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::SetFontFamilyName( WCHAR const* fontFamilyName, DWRITE_TEXT_RANGE textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFontFamilyName( fontFamilyName, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::SetFontWeight( DWRITE_FONT_WEIGHT fontWeight, DWRITE_TEXT_RANGE textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFontWeight( fontWeight, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::SetFontStyle( DWRITE_FONT_STYLE fontStyle, DWRITE_TEXT_RANGE textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFontStyle( fontStyle, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::SetFontStretch( DWRITE_FONT_STRETCH fontStretch, DWRITE_TEXT_RANGE textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFontStretch( fontStretch, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::SetFontSize( FLOAT fontSize, DWRITE_TEXT_RANGE textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFontSize( fontSize, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::SetUnderline( BOOL hasUnderline, DWRITE_TEXT_RANGE textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetUnderline( hasUnderline, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::SetStrikethrough( BOOL hasStrikethrough, DWRITE_TEXT_RANGE textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetStrikethrough( hasStrikethrough, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::SetDrawingEffect( IUnknown* drawingEffect, DWRITE_TEXT_RANGE textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetDrawingEffect( drawingEffect, textRange );
        CheckHRESULT( hr );
    }
    void TextLayout::SetInlineObject( IDWriteInlineObject* inlineObject, DWRITE_TEXT_RANGE textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetInlineObject( inlineObject, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::SetTypography( IDWriteTypography* typography, DWRITE_TEXT_RANGE textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetTypography( typography, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::SetLocaleName( WCHAR const* localeName, DWRITE_TEXT_RANGE textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetLocaleName( localeName, textRange );
        CheckHRESULT( hr );
    }

    FLOAT TextLayout::GetMaxWidth( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetMaxWidth( );
    }

    FLOAT TextLayout::GetMaxHeight( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetMaxHeight( );
    }

    void TextLayout::GetFontCollection( UINT32 currentPosition, IDWriteFontCollection** fontCollection, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontCollection( currentPosition, fontCollection, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::GetFontFamilyNameLength( UINT32 currentPosition, UINT32* nameLength, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamilyNameLength( currentPosition, nameLength, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::GetFontFamilyName( UINT32 currentPosition, _Out_writes_z_( nameSize ) WCHAR* fontFamilyName, UINT32 nameSize, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamilyName( currentPosition, fontFamilyName, nameSize, textRange );
        CheckHRESULT( hr );
    }
    void TextLayout::GetFontWeight( UINT32 currentPosition, DWRITE_FONT_WEIGHT* fontWeight, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontWeight( currentPosition, fontWeight, textRange );
        CheckHRESULT( hr );
    }
    void TextLayout::GetFontStyle( UINT32 currentPosition, DWRITE_FONT_STYLE* fontStyle, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontStyle( currentPosition, fontStyle, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::GetFontStretch( UINT32 currentPosition, DWRITE_FONT_STRETCH* fontStretch, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontStretch( currentPosition, fontStretch, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::GetFontSize( UINT32 currentPosition, FLOAT* fontSize, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontSize( currentPosition, fontSize, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::GetUnderline( UINT32 currentPosition, BOOL* hasUnderline, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetUnderline( currentPosition, hasUnderline, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::GetStrikethrough( UINT32 currentPosition, BOOL* hasStrikethrough, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetStrikethrough( currentPosition, hasStrikethrough, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::GetDrawingEffect( UINT32 currentPosition, IUnknown** drawingEffect, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetDrawingEffect( currentPosition, drawingEffect, textRange );
        CheckHRESULT( hr );
    }
    void TextLayout::GetInlineObject( UINT32 currentPosition, IDWriteInlineObject** inlineObject, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetInlineObject( currentPosition, inlineObject, textRange );
        CheckHRESULT( hr );
    }
    void TextLayout::GetTypography( UINT32 currentPosition, IDWriteTypography** typography, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetTypography( currentPosition, typography, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::GetLocaleNameLength( UINT32 currentPosition, UINT32* nameLength, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleNameLength( currentPosition, nameLength, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::GetLocaleName( UINT32 currentPosition, _Out_writes_z_( nameSize ) WCHAR* localeName, UINT32 nameSize, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleName( currentPosition, localeName, nameSize, textRange );
        CheckHRESULT( hr );
    }

    void TextLayout::Draw( void* clientDrawingContext, IDWriteTextRenderer* renderer, FLOAT originX, FLOAT originY ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->Draw( clientDrawingContext, renderer, originX, originY );
        CheckHRESULT( hr );
    }

    void TextLayout::GetLineMetrics( DWRITE_LINE_METRICS* lineMetrics, UINT32 maxLineCount, UINT32* actualLineCount ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLineMetrics( lineMetrics, maxLineCount, actualLineCount );
        CheckHRESULT( hr );
    }

    void TextLayout::GetMetrics( DWRITE_TEXT_METRICS* textMetrics ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetMetrics( textMetrics );
        CheckHRESULT( hr );
    }

    void TextLayout::GetOverhangMetrics( DWRITE_OVERHANG_METRICS* overhangs ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetOverhangMetrics( overhangs );
        CheckHRESULT( hr );
    }

    void TextLayout::GetClusterMetrics( DWRITE_CLUSTER_METRICS* clusterMetrics, UINT32 maxClusterCount, UINT32* actualClusterCount ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetClusterMetrics( clusterMetrics, maxClusterCount, actualClusterCount );
        CheckHRESULT( hr );
    }

    void TextLayout::DetermineMinWidth( FLOAT* minWidth ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->DetermineMinWidth( minWidth );
        CheckHRESULT( hr );
    }

    void TextLayout::HitTestPoint( FLOAT pointX, FLOAT pointY, BOOL* isTrailingHit, BOOL* isInside, DWRITE_HIT_TEST_METRICS* hitTestMetrics ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->HitTestPoint( pointX, pointY, isTrailingHit, isInside, hitTestMetrics );
        CheckHRESULT( hr );
    }

    void TextLayout::HitTestTextPosition( UINT32 textPosition, BOOL isTrailingHit, FLOAT* pointX, FLOAT* pointY, DWRITE_HIT_TEST_METRICS* hitTestMetrics ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->HitTestTextPosition( textPosition, isTrailingHit, pointX, pointY, hitTestMetrics );
        CheckHRESULT( hr );
    }
    void TextLayout::HitTestTextRange( UINT32 textPosition, UINT32 textLength, FLOAT originX, FLOAT originY, DWRITE_HIT_TEST_METRICS* hitTestMetrics, UINT32 maxHitTestMetricsCount, UINT32* actualHitTestMetricsCount ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->HitTestTextRange( textPosition, textLength, originX, originY, hitTestMetrics, maxHitTestMetricsCount, actualHitTestMetricsCount );
        CheckHRESULT( hr );
    }

    // ================================================================
    // BitmapRenderTarget
    // ================================================================
    void BitmapRenderTarget::DrawGlyphRun( FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_MEASURING_MODE measuringMode, DWRITE_GLYPH_RUN const* glyphRun, IDWriteRenderingParams* renderingParams, COLORREF textColor, _Out_opt_ RECT* blackBoxRect ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->DrawGlyphRun( baselineOriginX, baselineOriginY, measuringMode, glyphRun, renderingParams, textColor, blackBoxRect );
        CheckHRESULT( hr );
    }

    HDC BitmapRenderTarget::GetMemoryDC( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetMemoryDC( );
    }

    FLOAT BitmapRenderTarget::GetPixelsPerDip( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetPixelsPerDip( );
    }
    void BitmapRenderTarget::SetPixelsPerDip( FLOAT pixelsPerDip ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetPixelsPerDip( pixelsPerDip );
        CheckHRESULT( hr );
    }

    void BitmapRenderTarget::GetCurrentTransform( DWRITE_MATRIX* transform ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetCurrentTransform( transform );
        CheckHRESULT( hr );
    }
    void BitmapRenderTarget::SetCurrentTransform( DWRITE_MATRIX const* transform ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetCurrentTransform( transform );
        CheckHRESULT( hr );
    }

    void BitmapRenderTarget::GetSize( SIZE* size ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetSize( size );
        CheckHRESULT( hr );
    }

    void BitmapRenderTarget::Resize( UINT32 width, UINT32 height ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->Resize( width, height );
        CheckHRESULT( hr );
    }
    // ================================================================
    // GdiInterop
    // ================================================================
    void GdiInterop::CreateFontFromLOGFONT( LOGFONTW const* logFont, IDWriteFont** font ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFromLOGFONT( logFont, font );
        CheckHRESULT( hr );
    }

    void GdiInterop::ConvertFontToLOGFONT( IDWriteFont* font, LOGFONTW* logFont, BOOL* isSystemFont ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->ConvertFontToLOGFONT( font, logFont, isSystemFont );
        CheckHRESULT( hr );
    }

    void GdiInterop::ConvertFontFaceToLOGFONT( IDWriteFontFace* font, LOGFONTW* logFont ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->ConvertFontFaceToLOGFONT( font, logFont );
        CheckHRESULT( hr );
    }

    void GdiInterop::CreateFontFaceFromHdc( HDC hdc, IDWriteFontFace** fontFace ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFaceFromHdc( hdc, fontFace );
        CheckHRESULT( hr );
    }

    void GdiInterop::CreateBitmapRenderTarget( HDC hdc, UINT32 width, UINT32 height, IDWriteBitmapRenderTarget** renderTarget ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateBitmapRenderTarget( hdc, width, height, renderTarget );
        CheckHRESULT( hr );
    }
    // ================================================================
    // GlyphRunAnalysis
    // ================================================================
    void GlyphRunAnalysis::GetAlphaTextureBounds( DWRITE_TEXTURE_TYPE textureType, RECT* textureBounds ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetAlphaTextureBounds( textureType, textureBounds );
        CheckHRESULT( hr );
    }
    void GlyphRunAnalysis::CreateAlphaTexture( DWRITE_TEXTURE_TYPE textureType, RECT const* textureBounds, BYTE* alphaValues, UINT32 bufferSize ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateAlphaTexture( textureType, textureBounds, alphaValues, bufferSize );
        CheckHRESULT( hr );
    }

    void GlyphRunAnalysis::GetAlphaBlendParams( IDWriteRenderingParams* renderingParams, FLOAT* blendGamma, FLOAT* blendEnhancedContrast, FLOAT* blendClearTypeLevel ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetAlphaBlendParams( renderingParams, blendGamma, blendEnhancedContrast, blendClearTypeLevel );
        CheckHRESULT( hr );
    }

    // ================================================================
    // Factory
    // ================================================================
    Factory::Factory( DWRITE_FACTORY_TYPE factoryType )
    {
        IUnknown* factory = nullptr;
        HRESULT hr = DWriteCreateFactory( factoryType, __uuidof( IDWriteFactory ), &factory );
        CheckHRESULT( hr );
        unknown_ = factory;
    }

    void Factory::GetSystemFontCollection( IDWriteFontCollection** fontCollection, BOOL checkForUpdates ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetSystemFontCollection( fontCollection, checkForUpdates );
        CheckHRESULT( hr );
    }
    FontCollection Factory::GetSystemFontCollection( bool checkForUpdates ) const
    {
        IDWriteFontCollection* fontCollection = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetSystemFontCollection( &fontCollection, checkForUpdates );
        CheckHRESULT( hr );
        FontCollection result( fontCollection );
        return result;
    }

    void Factory::CreateCustomFontCollection( IDWriteFontCollectionLoader* collectionLoader, void const* collectionKey, UINT32 collectionKeySize, IDWriteFontCollection** fontCollection ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateCustomFontCollection( collectionLoader, collectionKey, collectionKeySize, fontCollection );
        CheckHRESULT( hr );
    }
    FontCollection Factory::CreateCustomFontCollection( IDWriteFontCollectionLoader* collectionLoader, void const* collectionKey, UINT32 collectionKeySize ) const
    {
        IDWriteFontCollection* fontCollection = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateCustomFontCollection( collectionLoader, collectionKey, collectionKeySize, &fontCollection );
        CheckHRESULT( hr );
        FontCollection result( fontCollection );
        return result;
    }

    void Factory::RegisterFontCollectionLoader( IDWriteFontCollectionLoader* fontCollectionLoader ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->RegisterFontCollectionLoader( fontCollectionLoader );
        CheckHRESULT( hr );
    }
    void Factory::UnregisterFontCollectionLoader( IDWriteFontCollectionLoader* fontCollectionLoader ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->UnregisterFontCollectionLoader( fontCollectionLoader );
        CheckHRESULT( hr );
    }
    void Factory::CreateFontFileReference( WCHAR const* filePath, FILETIME const* lastWriteTime, IDWriteFontFile** fontFile ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFileReference( filePath, lastWriteTime, fontFile );
        CheckHRESULT( hr );
    }
    FontFile Factory::CreateFontFileReference( WCHAR const* filePath, FILETIME const* lastWriteTime ) const
    {
        IDWriteFontFile* fontFile = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFileReference( filePath, lastWriteTime, &fontFile );
        CheckHRESULT( hr );
        FontFile result( fontFile );
        return result;
    }
    void Factory::CreateCustomFontFileReference( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileLoader* fontFileLoader, IDWriteFontFile** fontFile ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateCustomFontFileReference( fontFileReferenceKey, fontFileReferenceKeySize, fontFileLoader, fontFile );
        CheckHRESULT( hr );
    }
    FontFile Factory::CreateCustomFontFileReference( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileLoader* fontFileLoader ) const
    {
        IDWriteFontFile* fontFile = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateCustomFontFileReference( fontFileReferenceKey, fontFileReferenceKeySize, fontFileLoader, &fontFile );
        CheckHRESULT( hr );
        FontFile result( fontFile );
        return result;
    }

    void Factory::CreateFontFace( DWRITE_FONT_FACE_TYPE fontFaceType, UINT32 numberOfFiles, IDWriteFontFile* const* fontFiles, UINT32 faceIndex, DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags, IDWriteFontFace** fontFace ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFace( fontFaceType, numberOfFiles, fontFiles, faceIndex, fontFaceSimulationFlags, fontFace );
        CheckHRESULT( hr );
    }
    FontFace Factory::CreateFontFace( DWRITE_FONT_FACE_TYPE fontFaceType, UINT32 numberOfFiles, IDWriteFontFile* const* fontFiles, UINT32 faceIndex, DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags ) const
    {
        IDWriteFontFace* fontFace = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFace( fontFaceType, numberOfFiles, fontFiles, faceIndex, fontFaceSimulationFlags, &fontFace );
        CheckHRESULT( hr );
        FontFace result( fontFace );
        return result;
    }

    void Factory::CreateRenderingParams( IDWriteRenderingParams** renderingParams ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateRenderingParams( renderingParams );
        CheckHRESULT( hr );
    }
    RenderingParams Factory::CreateRenderingParams( ) const
    {
        IDWriteRenderingParams* renderingParams = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateRenderingParams( &renderingParams );
        CheckHRESULT( hr );
        RenderingParams result( renderingParams );
        return result;
    }

    void Factory::CreateMonitorRenderingParams( HMONITOR monitor, IDWriteRenderingParams** renderingParams ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateMonitorRenderingParams( monitor, renderingParams );
        CheckHRESULT( hr );
    }
    RenderingParams Factory::CreateMonitorRenderingParams( HMONITOR monitor ) const
    {
        IDWriteRenderingParams* renderingParams = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateMonitorRenderingParams( monitor, &renderingParams );
        CheckHRESULT( hr );
        RenderingParams result( renderingParams );
        return result;
    }

    void Factory::CreateCustomRenderingParams( FLOAT gamma, FLOAT enhancedContrast, FLOAT clearTypeLevel, DWRITE_PIXEL_GEOMETRY pixelGeometry, DWRITE_RENDERING_MODE renderingMode, IDWriteRenderingParams** renderingParams ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateCustomRenderingParams( gamma, enhancedContrast, clearTypeLevel, pixelGeometry, renderingMode, renderingParams );
        CheckHRESULT( hr );
    }
    RenderingParams Factory::CreateCustomRenderingParams( FLOAT gamma, FLOAT enhancedContrast, FLOAT clearTypeLevel, DWRITE_PIXEL_GEOMETRY pixelGeometry, DWRITE_RENDERING_MODE renderingMode ) const
    {
        IDWriteRenderingParams* renderingParams = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateCustomRenderingParams( gamma, enhancedContrast, clearTypeLevel, pixelGeometry, renderingMode, &renderingParams );
        CheckHRESULT( hr );
        RenderingParams result( renderingParams );
        return result;
    }

    void Factory::RegisterFontFileLoader( IDWriteFontFileLoader* fontFileLoader ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->RegisterFontFileLoader( fontFileLoader );
        CheckHRESULT( hr );
    }

    void Factory::UnregisterFontFileLoader( IDWriteFontFileLoader* fontFileLoader ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->UnregisterFontFileLoader( fontFileLoader );
        CheckHRESULT( hr );
    }

    void Factory::CreateTextFormat( WCHAR const* fontFamilyName, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName, IDWriteTextFormat** textFormat ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTextFormat( fontFamilyName, fontCollection, fontWeight, fontStyle, fontStretch, fontSize, localeName, textFormat );
        CheckHRESULT( hr );
    }
    TextFormat Factory::CreateTextFormat( WCHAR const* fontFamilyName, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName ) const
    {
        IDWriteTextFormat* textFormat = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTextFormat( fontFamilyName, fontCollection, fontWeight, fontStyle, fontStretch, fontSize, localeName, &textFormat );
        CheckHRESULT( hr );
        TextFormat result( textFormat );
        return result;
    }

    TextFormat Factory::CreateTextFormat( WCHAR const* fontFamilyName, FLOAT fontSize ) const
    {
        wchar_t localeName[LOCALE_NAME_MAX_LENGTH + 1] = { 0, };
        LCIDToLocaleName( LOCALE_USER_DEFAULT, localeName, LOCALE_NAME_MAX_LENGTH, 0 );

        IDWriteTextFormat* textFormat = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTextFormat( fontFamilyName, nullptr,
            DWRITE_FONT_WEIGHT_REGULAR,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            fontSize,
            localeName,
            &textFormat );
        CheckHRESULT( hr );
        TextFormat result( textFormat );
        return result;
    }


    void Factory::CreateTypography( IDWriteTypography** typography ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTypography( typography );
        CheckHRESULT( hr );
    }

    Typography Factory::CreateTypography( ) const
    {
        IDWriteTypography* typography = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTypography( &typography );
        CheckHRESULT( hr );
        Typography result( typography );
        return result;
    }

    void Factory::GetGdiInterop( IDWriteGdiInterop** gdiInterop ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGdiInterop( gdiInterop );
        CheckHRESULT( hr );
    }

    GdiInterop Factory::GetGdiInterop( ) const
    {
        IDWriteGdiInterop* gdiInterop = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGdiInterop( &gdiInterop );
        CheckHRESULT( hr );
        GdiInterop result( gdiInterop );
        return result;
    }

    void Factory::CreateTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT maxWidth, FLOAT maxHeight, IDWriteTextLayout** textLayout ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTextLayout( string, stringLength, textFormat, maxWidth, maxHeight, textLayout );
        CheckHRESULT( hr );
    }
    TextLayout Factory::CreateTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT maxWidth, FLOAT maxHeight ) const
    {
        IDWriteTextLayout* textLayout = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTextLayout( string, stringLength, textFormat, maxWidth, maxHeight, &textLayout );
        CheckHRESULT( hr );
        TextLayout result( textLayout );
        return result;
    }

    void Factory::CreateGdiCompatibleTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT layoutWidth, FLOAT layoutHeight, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural, IDWriteTextLayout** textLayout ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateGdiCompatibleTextLayout( string, stringLength, textFormat, layoutWidth, layoutHeight, pixelsPerDip, transform, useGdiNatural, textLayout );
        CheckHRESULT( hr );
    }
    TextLayout Factory::CreateGdiCompatibleTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT layoutWidth, FLOAT layoutHeight, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural ) const
    {
        IDWriteTextLayout* textLayout = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateGdiCompatibleTextLayout( string, stringLength, textFormat, layoutWidth, layoutHeight, pixelsPerDip, transform, useGdiNatural, &textLayout );
        CheckHRESULT( hr );
        TextLayout result( textLayout );
        return result;
    }

    void Factory::CreateEllipsisTrimmingSign( IDWriteTextFormat* textFormat, IDWriteInlineObject** trimmingSign ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateEllipsisTrimmingSign( textFormat, trimmingSign );
        CheckHRESULT( hr );
    }
    InlineObject Factory::CreateEllipsisTrimmingSign( IDWriteTextFormat* textFormat ) const
    {
        IDWriteInlineObject* trimmingSign = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateEllipsisTrimmingSign( textFormat, &trimmingSign );
        CheckHRESULT( hr );
        InlineObject result( trimmingSign );
        return result;
    }
    void Factory::CreateTextAnalyzer( IDWriteTextAnalyzer** textAnalyzer ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTextAnalyzer( textAnalyzer );
        CheckHRESULT( hr );
    }
    TextAnalyzer Factory::CreateTextAnalyzer( ) const
    {
        IDWriteTextAnalyzer* textAnalyzer = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTextAnalyzer( &textAnalyzer );
        CheckHRESULT( hr );
        TextAnalyzer result( textAnalyzer );
        return result;
    }

    void Factory::CreateNumberSubstitution( DWRITE_NUMBER_SUBSTITUTION_METHOD substitutionMethod, WCHAR const* localeName, BOOL ignoreUserOverride, IDWriteNumberSubstitution** numberSubstitution ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateNumberSubstitution( substitutionMethod, localeName, ignoreUserOverride, numberSubstitution );
        CheckHRESULT( hr );
    }

    void Factory::CreateGlyphRunAnalysis( DWRITE_GLYPH_RUN const* glyphRun, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_RENDERING_MODE renderingMode, DWRITE_MEASURING_MODE measuringMode, FLOAT baselineOriginX, FLOAT baselineOriginY, IDWriteGlyphRunAnalysis** glyphRunAnalysis ) const
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateGlyphRunAnalysis( glyphRun, pixelsPerDip, transform, renderingMode, measuringMode, baselineOriginX, baselineOriginY, glyphRunAnalysis );
        CheckHRESULT( hr );
    }

    GlyphRunAnalysis Factory::CreateGlyphRunAnalysis( DWRITE_GLYPH_RUN const* glyphRun, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_RENDERING_MODE renderingMode, DWRITE_MEASURING_MODE measuringMode, FLOAT baselineOriginX, FLOAT baselineOriginY ) const
    {
        IDWriteGlyphRunAnalysis* glyphRunAnalysis = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateGlyphRunAnalysis( glyphRun, pixelsPerDip, transform, renderingMode, measuringMode, baselineOriginX, baselineOriginY, &glyphRunAnalysis );
        CheckHRESULT( hr );
        GlyphRunAnalysis result( glyphRunAnalysis );
        return result;
    }


}