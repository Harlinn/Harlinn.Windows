/*
   Copyright 2024 Espen Harlinn

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
    FontFileLoader& FontFileLoader::CreateStreamFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileStream** fontFileStream )
    {

        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateStreamFromKey( fontFileReferenceKey, fontFileReferenceKeySize, fontFileStream );
        CheckHRESULT( hr );
        return *this;

    }
    FontFileStream FontFileLoader::CreateStreamFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize )
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
    LocalFontFileLoader& LocalFontFileLoader::GetFilePathLengthFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, UINT32* filePathLength )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFilePathLengthFromKey( fontFileReferenceKey, fontFileReferenceKeySize, filePathLength );
        CheckHRESULT( hr );
        return *this;
    }
    UINT32 LocalFontFileLoader::GetFilePathLengthFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize )
    {
        UINT32 result = 0;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFilePathLengthFromKey( fontFileReferenceKey, fontFileReferenceKeySize, &result );
        CheckHRESULT( hr );
        return result;
    }

    LocalFontFileLoader& LocalFontFileLoader::GetFilePathFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, WCHAR* filePath, UINT32 filePathSize )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFilePathFromKey( fontFileReferenceKey, fontFileReferenceKeySize, filePath, filePathSize );
        CheckHRESULT( hr );
        return *this;
    }
    std::shared_ptr<WideString> LocalFontFileLoader::GetFilePathFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize )
    {
        UINT32 filePathSize = GetFilePathLengthFromKey( fontFileReferenceKey, fontFileReferenceKeySize );

        std::shared_ptr<WideString> result = std::make_shared<WideString>( filePathSize, WideString::value_type( 0 ) );

        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFilePathFromKey( fontFileReferenceKey, fontFileReferenceKeySize, const_cast<WCHAR*>( result->c_str( ) ), filePathSize );
        CheckHRESULT( hr );
        return result;
    }

    LocalFontFileLoader& LocalFontFileLoader::GetLastWriteTimeFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, FILETIME* lastWriteTime )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLastWriteTimeFromKey( fontFileReferenceKey, fontFileReferenceKeySize, lastWriteTime );
        CheckHRESULT( hr );
        return *this;
    }
    FILETIME LocalFontFileLoader::GetLastWriteTimeFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize )
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
    FontFileStream& FontFileStream::ReadFileFragment( void const** fragmentStart, UINT64 fileOffset, UINT64 fragmentSize, void** fragmentContext )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->ReadFileFragment( fragmentStart, fileOffset, fragmentSize, fragmentContext );
        CheckHRESULT( hr );
        return *this;
    }

    FontFileStream& FontFileStream::ReleaseFileFragment( void* fragmentContext )
    {
        InterfaceType* pInterface = GetInterface( );
        pInterface->ReleaseFileFragment( fragmentContext );
        return *this;
    }

    FontFileStream& FontFileStream::GetFileSize( UINT64* fileSize )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFileSize( fileSize );
        CheckHRESULT( hr );
        return *this;
    }
    UINT64 FontFileStream::GetFileSize( )
    {
        UINT64 result = 0;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFileSize( &result );
        CheckHRESULT( hr );
        return result;
    }

    FontFileStream& FontFileStream::GetLastWriteTime( UINT64* lastWriteTime )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLastWriteTime( lastWriteTime );
        CheckHRESULT( hr );
        return *this;
    }
    UINT64 FontFileStream::GetLastWriteTime( )
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
    FontFile& FontFile::GetReferenceKey( void const** fontFileReferenceKey, UINT32* fontFileReferenceKeySize )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetReferenceKey( fontFileReferenceKey, fontFileReferenceKeySize );
        CheckHRESULT( hr );
        return *this;
    }
    FontFile& FontFile::GetLoader( IDWriteFontFileLoader** fontFileLoader )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLoader( fontFileLoader );
        CheckHRESULT( hr );
        return *this;
    }
    FontFileLoader FontFile::GetLoader( )
    {
        IDWriteFontFileLoader* fontFileLoader = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLoader( &fontFileLoader );
        CheckHRESULT( hr );
        FontFileLoader result( fontFileLoader );
        return result;
    }
    FontFile& FontFile::Analyze( BOOL* isSupportedFontType, DWRITE_FONT_FILE_TYPE* fontFileType, _Out_opt_ DWRITE_FONT_FACE_TYPE* fontFaceType, UINT32* numberOfFaces )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->Analyze( isSupportedFontType, fontFileType, fontFaceType, numberOfFaces );
        CheckHRESULT( hr );
        return *this;
    }
    FontFile& FontFile::Analyze( BOOL& isSupportedFontType, DWRITE_FONT_FILE_TYPE& fontFileType, _Out_opt_ DWRITE_FONT_FACE_TYPE& fontFaceType, UINT32& numberOfFaces )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->Analyze( &isSupportedFontType, &fontFileType, &fontFaceType, &numberOfFaces );
        CheckHRESULT( hr );
        return *this;
    }

    FontFile& FontFile::Analyze( BOOL& isSupportedFontType, DWRITE_FONT_FILE_TYPE& fontFileType, UINT32& numberOfFaces )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->Analyze( &isSupportedFontType, &fontFileType, nullptr, &numberOfFaces );
        CheckHRESULT( hr );
        return *this;
    }

    // ================================================================
    // RenderingParams
    // ================================================================
    FLOAT RenderingParams::GetGamma( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetGamma( );
    }
    FLOAT RenderingParams::GetEnhancedContrast( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetEnhancedContrast( );
    }
    FLOAT RenderingParams::GetClearTypeLevel( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetClearTypeLevel( );
    }
    DWRITE_PIXEL_GEOMETRY RenderingParams::GetPixelGeometry( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetPixelGeometry( );
    }
    DWRITE_RENDERING_MODE RenderingParams::GetRenderingMode( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetRenderingMode( );
    }

    // ================================================================
    // FontFace
    // ================================================================
    DWRITE_FONT_FACE_TYPE FontFace::GetType( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetType( );
    }
    FontFace& FontFace::GetFiles( _Inout_ UINT32* numberOfFiles, IDWriteFontFile** fontFiles )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFiles( numberOfFiles, fontFiles );
        CheckHRESULT( hr );
        return *this;
    }

    UINT32 FontFace::GetNumberOfFiles( )
    {
        UINT32 result;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFiles( &result, nullptr );
        CheckHRESULT( hr );
        return result;
    }

    std::shared_ptr< std::vector<FontFile> > FontFace::GetFiles( )
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

    UINT32 FontFace::GetIndex( )
    {
        UINT32 result;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFiles( &result, nullptr );
        CheckHRESULT( hr );
        return result;
    }

    DWRITE_FONT_SIMULATIONS FontFace::GetSimulations( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetSimulations( );
    }
    BOOL FontFace::IsSymbolFont( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetSimulations( );
    }
    FontFace& FontFace::GetMetrics( DWRITE_FONT_METRICS* fontFaceMetrics )
    {
        CheckPointerNotNull( fontFaceMetrics );
        InterfaceType* pInterface = GetInterface( );
        pInterface->GetMetrics( fontFaceMetrics );
        return *this;
    }
    FontFace& FontFace::GetMetrics( DWRITE_FONT_METRICS& fontFaceMetrics )
    {
        InterfaceType* pInterface = GetInterface( );
        pInterface->GetMetrics( &fontFaceMetrics );
        return *this;
    }
    UINT16 FontFace::GetGlyphCount( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetGlyphCount( );
    }
    FontFace& FontFace::GetDesignGlyphMetrics( UINT16 const* glyphIndices, UINT32 glyphCount, DWRITE_GLYPH_METRICS* glyphMetrics, BOOL isSideways )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetDesignGlyphMetrics( glyphIndices, glyphCount, glyphMetrics, isSideways );
        CheckHRESULT( hr );
        return *this;
    }
    FontFace& FontFace::GetGlyphIndices( UINT32 const* codePoints, UINT32 codePointCount, UINT16* glyphIndices )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGlyphIndices( codePoints, codePointCount, glyphIndices );
        CheckHRESULT( hr );
        return *this;
    }
    FontFace& FontFace::TryGetFontTable( UINT32 openTypeTableTag, const void** tableData, UINT32* tableSize, void** tableContext, BOOL* exists )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->TryGetFontTable( openTypeTableTag, tableData, tableSize, tableContext, exists );
        CheckHRESULT( hr );
        return *this;
    }
    FontFace& FontFace::ReleaseFontTable( void* tableContext )
    {
        InterfaceType* pInterface = GetInterface( );
        pInterface->ReleaseFontTable( tableContext );
        return *this;
    }
    FontFace& FontFace::GetGlyphRunOutline( FLOAT emSize, UINT16 const* glyphIndices, FLOAT const* glyphAdvances, DWRITE_GLYPH_OFFSET const* glyphOffsets, UINT32 glyphCount, BOOL isSideways, BOOL isRightToLeft, IDWriteGeometrySink* geometrySink )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGlyphRunOutline( emSize, glyphIndices, glyphAdvances, glyphOffsets, glyphCount, isSideways, isRightToLeft, geometrySink );
        CheckHRESULT( hr );
        return *this;
    }
    FontFace& FontFace::GetRecommendedRenderingMode( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MEASURING_MODE measuringMode, IDWriteRenderingParams* renderingParams, DWRITE_RENDERING_MODE* renderingMode )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetRecommendedRenderingMode( emSize, pixelsPerDip, measuringMode, renderingParams, renderingMode );
        CheckHRESULT( hr );
        return *this;
    }
    DWRITE_RENDERING_MODE FontFace::GetRecommendedRenderingMode( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MEASURING_MODE measuringMode, IDWriteRenderingParams* renderingParams )
    {
        DWRITE_RENDERING_MODE result = DWRITE_RENDERING_MODE( 0 );
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetRecommendedRenderingMode( emSize, pixelsPerDip, measuringMode, renderingParams, &result );
        CheckHRESULT( hr );
        return result;
    }

    FontFace& FontFace::GetGdiCompatibleMetrics( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_FONT_METRICS* fontFaceMetrics )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGdiCompatibleMetrics( emSize, pixelsPerDip, transform, fontFaceMetrics );
        CheckHRESULT( hr );
        return *this;
    }
    FontFace& FontFace::GetGdiCompatibleGlyphMetrics( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural, UINT16 const* glyphIndices, UINT32 glyphCount, DWRITE_GLYPH_METRICS* glyphMetrics, BOOL isSideways )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGdiCompatibleGlyphMetrics( emSize, pixelsPerDip, transform, useGdiNatural, glyphIndices, glyphCount, glyphMetrics, isSideways );
        CheckHRESULT( hr );
        return *this;
    }

    // ================================================================
    // FontCollectionLoader
    // ================================================================
    FontCollectionLoader& FontCollectionLoader::CreateEnumeratorFromKey( IDWriteFactory* factory, void const* collectionKey, UINT32 collectionKeySize, IDWriteFontFileEnumerator** fontFileEnumerator )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateEnumeratorFromKey( factory, collectionKey, collectionKeySize, fontFileEnumerator );
        CheckHRESULT( hr );
        return *this;
    }

    FontFileEnumerator FontCollectionLoader::CreateEnumeratorFromKey( IDWriteFactory* factory, void const* collectionKey, UINT32 collectionKeySize )
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
    FontFileEnumerator& FontFileEnumerator::MoveNext( BOOL* hasCurrentFile )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->MoveNext( hasCurrentFile );
        CheckHRESULT( hr );
        return *this;
    }
    bool FontFileEnumerator::MoveNext( )
    {
        BOOL hasCurrentFile;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->MoveNext( &hasCurrentFile );
        CheckHRESULT( hr );
        return hasCurrentFile != FALSE;
    }

    FontFileEnumerator& FontFileEnumerator::GetCurrentFontFile( IDWriteFontFile** fontFile )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetCurrentFontFile( fontFile );
        CheckHRESULT( hr );
        return *this;
    }
    FontFile FontFileEnumerator::GetCurrentFontFile( )
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
    UINT32 LocalizedStrings::GetCount( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetCount( );
    }
    LocalizedStrings& LocalizedStrings::FindLocaleName( WCHAR const* localeName, UINT32* index, BOOL* exists )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->FindLocaleName( localeName, index, exists );
        CheckHRESULT( hr );
        return *this;
    }
    bool LocalizedStrings::FindLocaleName( WCHAR const* localeName, UINT32* index )
    {
        BOOL exists = FALSE;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->FindLocaleName( localeName, index, &exists );
        CheckHRESULT( hr );
        return exists != FALSE;
    }
    LocalizedStrings& LocalizedStrings::GetLocaleNameLength( UINT32 index, UINT32* length )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleNameLength( index, length );
        CheckHRESULT( hr );
        return *this;
    }
    UINT32 LocalizedStrings::GetLocaleNameLength( UINT32 index )
    {
        UINT32 result = 0;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleNameLength( index, &result );
        CheckHRESULT( hr );
        return result;
    }

    LocalizedStrings& LocalizedStrings::GetLocaleName( UINT32 index, WCHAR* localeName, UINT32 size )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleName( index, localeName, size );
        CheckHRESULT( hr );
        return *this;
    }
    std::shared_ptr<WideString> LocalizedStrings::GetLocaleName( UINT32 index )
    {
        UINT32 size = GetLocaleNameLength( index );
        std::shared_ptr<WideString> result = std::make_shared<WideString>( size, WideString::value_type( 0 ) );
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleName( index, const_cast< WideString::value_type*>( result->c_str( ) ), size );
        CheckHRESULT( hr );
        return result;
    }

    LocalizedStrings& LocalizedStrings::GetStringLength( UINT32 index, UINT32* length )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetStringLength( index, length );
        CheckHRESULT( hr );
        return *this;
    }
    UINT32 LocalizedStrings::GetStringLength( UINT32 index )
    {
        UINT32 result = 0;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetStringLength( index, &result );
        CheckHRESULT( hr );
        return result;
    }

    LocalizedStrings& LocalizedStrings::GetString( UINT32 index, WCHAR* stringBuffer, UINT32 size )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetString( index, stringBuffer, size );
        CheckHRESULT( hr );
        return *this;
    }
    std::shared_ptr<WideString> LocalizedStrings::GetString( UINT32 index )
    {
        UINT32 size = GetStringLength( index );
        std::shared_ptr<WideString> result = std::make_shared<WideString>( size, WideString::value_type( 0 ) );
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetString( index, const_cast< WideString::value_type*>( result->c_str( ) ), size );
        CheckHRESULT( hr );
        return result;
    }

    // ================================================================
    // FontCollection
    // ================================================================
    UINT32 FontCollection::GetFontFamilyCount( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontFamilyCount( );
    }

    FontCollection& FontCollection::GetFontFamily( UINT32 index, IDWriteFontFamily** fontFamily )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamily( index, fontFamily );
        CheckHRESULT( hr );
        return *this;
    }
    FontFamily FontCollection::GetFontFamily( UINT32 index )
    {
        IDWriteFontFamily* fontFamily = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamily( index, &fontFamily );
        CheckHRESULT( hr );
        FontFamily result( fontFamily );
        return result;
    }
    std::shared_ptr< std::vector<FontFamily> > FontCollection::GetFontFamilies( )
    {
        std::vector<FontFamily>::size_type fontFamilyCount = GetFontFamilyCount( );
        std::shared_ptr< std::vector<FontFamily> > result = std::make_shared< std::vector<FontFamily> >( fontFamilyCount );
        for ( UINT32 i = 0; i < fontFamilyCount; i++ )
        {
            FontFamily writeFontFamily = GetFontFamily( i );
            result->push_back( writeFontFamily );
        }
        return result;
    }

    FontCollection& FontCollection::FindFamilyName( WCHAR const* familyName, UINT32* index, BOOL* exists )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->FindFamilyName( familyName, index, exists );
        CheckHRESULT( hr );
        return *this;
    }
    bool FontCollection::FindFamilyName( WCHAR const* familyName, UINT32* index )
    {
        BOOL exists = FALSE;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->FindFamilyName( familyName, index, &exists );
        CheckHRESULT( hr );
        return exists != FALSE;
    }

    FontCollection& FontCollection::GetFontFromFontFace( IDWriteFontFace* fontFace, IDWriteFont** font )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFromFontFace( fontFace, font );
        CheckHRESULT( hr );
        return *this;
    }
    Font FontCollection::GetFontFromFontFace( IDWriteFontFace* fontFace )
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
    FontList& FontList::GetFontCollection( IDWriteFontCollection** fontCollection )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontCollection( fontCollection );
        CheckHRESULT( hr );
        return *this;
    }
    FontCollection FontList::GetFontCollection( )
    {
        IDWriteFontCollection* fontCollection = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontCollection( &fontCollection );
        CheckHRESULT( hr );
        FontCollection result( fontCollection );
        return result;
    }
    UINT32 FontList::GetFontCount( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontCount( );
    }
    FontList& FontList::GetFont( UINT32 index, IDWriteFont** font )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFont( index, font );
        CheckHRESULT( hr );
        return *this;
    }
    Font FontList::GetFont( UINT32 index )
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
    FontFamily& FontFamily::GetFamilyNames( IDWriteLocalizedStrings** names )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFamilyNames( names );
        CheckHRESULT( hr );
        return *this;
    }
    LocalizedStrings FontFamily::GetFamilyNames( )
    {
        IDWriteLocalizedStrings* names = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFamilyNames( &names );
        CheckHRESULT( hr );
        LocalizedStrings result( names );
        return result;
    }
    FontFamily& FontFamily::GetFirstMatchingFont( DWRITE_FONT_WEIGHT  weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style, IDWriteFont** matchingFont )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFirstMatchingFont( weight, stretch, style, matchingFont );
        CheckHRESULT( hr );
        return *this;
    }
    Font FontFamily::GetFirstMatchingFont( DWRITE_FONT_WEIGHT  weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style )
    {
        IDWriteFont* matchingFont = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFirstMatchingFont( weight, stretch, style, &matchingFont );
        CheckHRESULT( hr );
        Font result( matchingFont );
        return result;
    }
    FontFamily& FontFamily::GetMatchingFonts( DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style, IDWriteFontList** matchingFonts )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetMatchingFonts( weight, stretch, style, matchingFonts );
        CheckHRESULT( hr );
        return *this;
    }
    FontList FontFamily::GetMatchingFonts( DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style )
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
    Font& Font::GetFontFamily( IDWriteFontFamily** fontFamily )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamily( fontFamily );
        CheckHRESULT( hr );
        return *this;
    }
    FontFamily Font::GetFontFamily( )
    {
        IDWriteFontFamily* fontFamily = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamily( &fontFamily );
        CheckHRESULT( hr );
        FontFamily result( fontFamily );
        return result;
    }
    DWRITE_FONT_WEIGHT Font::GetWeight( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetWeight( );
    }
    DWRITE_FONT_STRETCH Font::GetStretch( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetStretch( );
    }
    DWRITE_FONT_STYLE Font::GetStyle( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetStyle( );
    }
    bool Font::IsSymbolFont( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->IsSymbolFont( ) != FALSE;
    }
    Font& Font::GetFaceNames( IDWriteLocalizedStrings** names )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFaceNames( names );
        CheckHRESULT( hr );
        return *this;
    }
    LocalizedStrings Font::GetFaceNames( )
    {
        IDWriteLocalizedStrings* names = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFaceNames( &names );
        CheckHRESULT( hr );
        LocalizedStrings result( names );
        return result;
    }
    Font& Font::GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_ID informationalStringID, IDWriteLocalizedStrings** informationalStrings, BOOL* exists )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetInformationalStrings( informationalStringID, informationalStrings, exists );
        CheckHRESULT( hr );
        return *this;
    }
    DWRITE_FONT_SIMULATIONS Font::GetSimulations( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetSimulations( );
    }
    Font& Font::GetMetrics( DWRITE_FONT_METRICS* fontMetrics )
    {
        InterfaceType* pInterface = GetInterface( );
        pInterface->GetMetrics( fontMetrics );
        return *this;
    }
    Font& Font::HasCharacter( UINT32 unicodeValue, BOOL* exists )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->HasCharacter( unicodeValue, exists );
        CheckHRESULT( hr );
        return *this;
    }
    bool Font::HasCharacter( UINT32 unicodeValue )
    {
        BOOL exists = FALSE;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->HasCharacter( unicodeValue, &exists );
        CheckHRESULT( hr );
        return exists != FALSE;
    }
    Font& Font::CreateFontFace( IDWriteFontFace** fontFace )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFace( fontFace );
        CheckHRESULT( hr );
        return *this;
    }
    FontFace Font::CreateFontFace( )
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
    TextFormat& TextFormat::SetTextAlignment( DWRITE_TEXT_ALIGNMENT textAlignment )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetTextAlignment( textAlignment );
        CheckHRESULT( hr );
        return *this;
    }
    TextFormat& TextFormat::SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetParagraphAlignment( paragraphAlignment );
        CheckHRESULT( hr );
        return *this;
    }
    TextFormat& TextFormat::SetWordWrapping( DWRITE_WORD_WRAPPING wordWrapping )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetWordWrapping( wordWrapping );
        CheckHRESULT( hr );
        return *this;
    }
    TextFormat& TextFormat::SetReadingDirection( DWRITE_READING_DIRECTION readingDirection )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetReadingDirection( readingDirection );
        CheckHRESULT( hr );
        return *this;
    }
    TextFormat& TextFormat::SetFlowDirection( DWRITE_FLOW_DIRECTION flowDirection )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFlowDirection( flowDirection );
        CheckHRESULT( hr );
        return *this;
    }
    TextFormat& TextFormat::SetIncrementalTabStop( FLOAT incrementalTabStop )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetIncrementalTabStop( incrementalTabStop );
        CheckHRESULT( hr );
        return *this;
    }
    TextFormat& TextFormat::SetTrimming( DWRITE_TRIMMING const* trimmingOptions, IDWriteInlineObject* trimmingSign )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetTrimming( trimmingOptions, trimmingSign );
        CheckHRESULT( hr );
        return *this;
    }
    TextFormat& TextFormat::SetLineSpacing( DWRITE_LINE_SPACING_METHOD lineSpacingMethod, FLOAT lineSpacing, FLOAT baseline )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetLineSpacing( lineSpacingMethod, lineSpacing, baseline );
        CheckHRESULT( hr );
        return *this;
    }
    DWRITE_TEXT_ALIGNMENT TextFormat::GetTextAlignment( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetTextAlignment( );
    }
    DWRITE_PARAGRAPH_ALIGNMENT TextFormat::GetParagraphAlignment( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetParagraphAlignment( );
    }
    DWRITE_WORD_WRAPPING TextFormat::GetWordWrapping( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetWordWrapping( );
    }
    DWRITE_READING_DIRECTION TextFormat::GetReadingDirection( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetReadingDirection( );
    }
    DWRITE_FLOW_DIRECTION TextFormat::GetFlowDirection( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFlowDirection( );
    }
    FLOAT TextFormat::GetIncrementalTabStop( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetIncrementalTabStop( );
    }
    TextFormat& TextFormat::GetTrimming( DWRITE_TRIMMING* trimmingOptions, IDWriteInlineObject** trimmingSign )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetTrimming( trimmingOptions, trimmingSign );
        CheckHRESULT( hr );
        return *this;
    }
    InlineObject TextFormat::GetTrimming( DWRITE_TRIMMING& trimmingOptions )
    {
        IDWriteInlineObject* trimmingSign = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetTrimming( &trimmingOptions, &trimmingSign );
        CheckHRESULT( hr );
        InlineObject result( trimmingSign );
        return result;
    }
    TextFormat& TextFormat::GetLineSpacing( DWRITE_LINE_SPACING_METHOD* lineSpacingMethod, FLOAT* lineSpacing, FLOAT* baseline )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLineSpacing( lineSpacingMethod, lineSpacing, baseline );
        CheckHRESULT( hr );
        return *this;
    }
    TextFormat& TextFormat::GetFontCollection( IDWriteFontCollection** fontCollection )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontCollection( fontCollection );
        CheckHRESULT( hr );
        return *this;
    }
    FontCollection TextFormat::GetFontCollection( )
    {
        IDWriteFontCollection* fontCollection = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontCollection( &fontCollection );
        CheckHRESULT( hr );
        FontCollection result( fontCollection );
        return result;
    }

    UINT32 TextFormat::GetFontFamilyNameLength( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontFamilyNameLength( );
    }
    TextFormat& TextFormat::GetFontFamilyName( WCHAR* fontFamilyName, UINT32 nameSize )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamilyName( fontFamilyName, nameSize );
        CheckHRESULT( hr );
        return *this;
    }
    std::shared_ptr<WideString> TextFormat::GetFontFamilyName( )
    {
        UINT32 nameSize = GetFontFamilyNameLength( );
        std::shared_ptr<WideString> result = std::make_shared<WideString>( nameSize, WideString::value_type( 0 ) );
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamilyName( const_cast<wchar_t*>( result->c_str( ) ), nameSize );
        CheckHRESULT( hr );
        return result;
    }
    DWRITE_FONT_WEIGHT TextFormat::GetFontWeight( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontWeight( );
    }
    DWRITE_FONT_STYLE TextFormat::GetFontStyle( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontStyle( );
    }
    DWRITE_FONT_STRETCH TextFormat::GetFontStretch( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontStretch( );
    }
    FLOAT TextFormat::GetFontSize( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontSize( );
    }
    UINT32 TextFormat::GetLocaleNameLength( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetLocaleNameLength( );
    }
    TextFormat& TextFormat::GetLocaleName( WCHAR* localeName, UINT32 nameSize )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleName( localeName, nameSize );
        CheckHRESULT( hr );
        return *this;
    }
    std::shared_ptr<WideString> TextFormat::GetLocaleName( )
    {
        UINT32 nameSize = GetLocaleNameLength( );
        std::shared_ptr<WideString> result = std::make_shared<WideString>( nameSize, WideString::value_type( 0 ) );
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleName( const_cast<wchar_t*>( result->c_str( ) ), nameSize );
        CheckHRESULT( hr );
        return result;
    }
    // ================================================================
    // Typography
    // ================================================================
    Typography& Typography::AddFontFeature( DWRITE_FONT_FEATURE fontFeature )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->AddFontFeature( fontFeature );
        CheckHRESULT( hr );
        return *this;
    }
    Typography& Typography::AddFontFeatures( std::shared_ptr< std::vector<DWRITE_FONT_FEATURE> > fontFeatures )
    {
        const std::vector<DWRITE_FONT_FEATURE>& elements = *fontFeatures.get( );
        for ( DWRITE_FONT_FEATURE fontFeature : elements )
        {
            AddFontFeature( fontFeature );
        }
        return *this;
    }
    UINT32 Typography::GetFontFeatureCount( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetFontFeatureCount( );
    }
    Typography& Typography::GetFontFeature( UINT32 fontFeatureIndex, DWRITE_FONT_FEATURE* fontFeature )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFeature( fontFeatureIndex, fontFeature );
        CheckHRESULT( hr );
        return *this;
    }
    DWRITE_FONT_FEATURE Typography::GetFontFeature( UINT32 fontFeatureIndex )
    {
        DWRITE_FONT_FEATURE fontFeature;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFeature( fontFeatureIndex, &fontFeature );
        CheckHRESULT( hr );
        return fontFeature;
    }
    std::shared_ptr< std::vector<DWRITE_FONT_FEATURE> > Typography::GetFontFeatures( )
    {
        std::vector<DWRITE_FONT_FEATURE>::size_type fontFeatureCount = GetFontFeatureCount( );
        std::shared_ptr< std::vector<DWRITE_FONT_FEATURE> > result = std::make_shared< std::vector<DWRITE_FONT_FEATURE> >( fontFeatureCount );
        for ( UINT32 i = 0; i < fontFeatureCount; i++ )
        {
            DWRITE_FONT_FEATURE fontFeature = GetFontFeature( i );
            result->push_back( fontFeature );
        }
        return result;
    }

    // ================================================================
    // TextAnalysisSource
    // ================================================================
    TextAnalysisSource& TextAnalysisSource::GetTextAtPosition( UINT32 textPosition, WCHAR const** textString, UINT32* textLength )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetTextAtPosition( textPosition, textString, textLength );
        CheckHRESULT( hr );
        return *this;
    }
    TextAnalysisSource& TextAnalysisSource::GetTextBeforePosition( UINT32 textPosition, WCHAR const** textString, UINT32* textLength )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetTextBeforePosition( textPosition, textString, textLength );
        CheckHRESULT( hr );
        return *this;
    }
    DWRITE_READING_DIRECTION TextAnalysisSource::GetParagraphReadingDirection( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetParagraphReadingDirection( );
    }
    TextAnalysisSource& TextAnalysisSource::GetLocaleName( UINT32 textPosition, UINT32* textLength, _Outptr_result_z_ WCHAR const** localeName )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleName( textPosition, textLength, localeName );
        CheckHRESULT( hr );
        return *this;
    }
    TextAnalysisSource& TextAnalysisSource::GetNumberSubstitution( UINT32 textPosition, UINT32* textLength, _Outptr_ IDWriteNumberSubstitution** numberSubstitution )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetNumberSubstitution( textPosition, textLength, numberSubstitution );
        CheckHRESULT( hr );
        return *this;
    }

    // ================================================================
    // TextAnalysisSink
    // ================================================================
    TextAnalysisSink& TextAnalysisSink::SetScriptAnalysis( UINT32 textPosition, UINT32 textLength, DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetScriptAnalysis( textPosition, textLength, scriptAnalysis );
        CheckHRESULT( hr );
        return *this;
    }
    TextAnalysisSink& TextAnalysisSink::SetLineBreakpoints( UINT32 textPosition, UINT32 textLength, DWRITE_LINE_BREAKPOINT const* lineBreakpoints )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetLineBreakpoints( textPosition, textLength, lineBreakpoints );
        CheckHRESULT( hr );
        return *this;
    }
    TextAnalysisSink& TextAnalysisSink::SetBidiLevel( UINT32 textPosition, UINT32 textLength, UINT8 explicitLevel, UINT8 resolvedLevel )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetBidiLevel( textPosition, textLength, explicitLevel, resolvedLevel );
        CheckHRESULT( hr );
        return *this;
    }
    TextAnalysisSink& TextAnalysisSink::SetNumberSubstitution( UINT32 textPosition, UINT32 textLength, IDWriteNumberSubstitution* numberSubstitution )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetNumberSubstitution( textPosition, textLength, numberSubstitution );
        CheckHRESULT( hr );
        return *this;
    }
    // ================================================================
    // TextAnalyzer
    // ================================================================
    TextAnalyzer& TextAnalyzer::AnalyzeScript(
        IDWriteTextAnalysisSource* analysisSource,
        UINT32 textPosition,
        UINT32 textLength,
        IDWriteTextAnalysisSink* analysisSink )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->AnalyzeScript( analysisSource, textPosition, textLength, analysisSink );
        CheckHRESULT( hr );
        return *this;
    }

    TextAnalyzer& TextAnalyzer::AnalyzeBidi(
        IDWriteTextAnalysisSource* analysisSource,
        UINT32 textPosition,
        UINT32 textLength,
        IDWriteTextAnalysisSink* analysisSink )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->AnalyzeBidi( analysisSource, textPosition, textLength, analysisSink );
        CheckHRESULT( hr );
        return *this;
    }

    TextAnalyzer& TextAnalyzer::AnalyzeNumberSubstitution(
        IDWriteTextAnalysisSource* analysisSource,
        UINT32 textPosition,
        UINT32 textLength,
        IDWriteTextAnalysisSink* analysisSink )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->AnalyzeNumberSubstitution( analysisSource, textPosition, textLength, analysisSink );
        CheckHRESULT( hr );
        return *this;
    }

    TextAnalyzer& TextAnalyzer::AnalyzeLineBreakpoints(
        IDWriteTextAnalysisSource* analysisSource,
        UINT32 textPosition,
        UINT32 textLength,
        IDWriteTextAnalysisSink* analysisSink )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->AnalyzeLineBreakpoints( analysisSource, textPosition, textLength, analysisSink );
        CheckHRESULT( hr );
        return *this;
    }

    TextAnalyzer& TextAnalyzer::GetGlyphs(
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
        UINT32* actualGlyphCount )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGlyphs( textString, textLength, fontFace, isSideways, isRightToLeft, scriptAnalysis, localeName, numberSubstitution, features, featureRangeLengths, featureRanges, maxGlyphCount, clusterMap, textProps, glyphIndices, glyphProps, actualGlyphCount );
        CheckHRESULT( hr );
        return *this;
    }

    TextAnalyzer& TextAnalyzer::GetGlyphPlacements(
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
        DWRITE_GLYPH_OFFSET* glyphOffsets )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGlyphPlacements( textString, clusterMap, textProps, textLength, glyphIndices, glyphProps, glyphCount, fontFace, fontEmSize, isSideways, isRightToLeft, scriptAnalysis, localeName, features, featureRangeLengths, featureRanges, glyphAdvances, glyphOffsets );
        CheckHRESULT( hr );
        return *this;
    }

    TextAnalyzer& TextAnalyzer::GetGdiCompatibleGlyphPlacements(
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
        DWRITE_GLYPH_OFFSET* glyphOffsets )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGdiCompatibleGlyphPlacements( textString, clusterMap, textProps, textLength, glyphIndices, glyphProps, glyphCount, fontFace, fontEmSize, pixelsPerDip, transform, useGdiNatural, isSideways, isRightToLeft, scriptAnalysis, localeName, features, featureRangeLengths, featureRanges, glyphAdvances, glyphOffsets );
        CheckHRESULT( hr );
        return *this;
    }


    // ================================================================
    // InlineObject
    // ================================================================
    InlineObject& InlineObject::Draw( void* clientDrawingContext, IDWriteTextRenderer* renderer, FLOAT originX, FLOAT originY, BOOL isSideways, BOOL isRightToLeft, IUnknown* clientDrawingEffect )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->Draw( clientDrawingContext, renderer, originX, originY, isSideways, isRightToLeft, clientDrawingEffect );
        CheckHRESULT( hr );
        return *this;
    }
    InlineObject& InlineObject::GetMetrics( DWRITE_INLINE_OBJECT_METRICS* metrics )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetMetrics( metrics );
        CheckHRESULT( hr );
        return *this;
    }

    InlineObject& InlineObject::GetOverhangMetrics( DWRITE_OVERHANG_METRICS* overhangs )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetOverhangMetrics( overhangs );
        CheckHRESULT( hr );
        return *this;
    }
    InlineObject& InlineObject::GetBreakConditions( DWRITE_BREAK_CONDITION* breakConditionBefore, DWRITE_BREAK_CONDITION* breakConditionAfter )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetBreakConditions( breakConditionBefore, breakConditionAfter );
        CheckHRESULT( hr );
        return *this;
    }

    // ================================================================
    // PixelSnapping
    // ================================================================
    PixelSnapping& PixelSnapping::IsPixelSnappingDisabled( void* clientDrawingContext, BOOL* isDisabled )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->IsPixelSnappingDisabled( clientDrawingContext, isDisabled );
        CheckHRESULT( hr );
        return *this;
    }
    PixelSnapping& PixelSnapping::GetCurrentTransform( void* clientDrawingContext, DWRITE_MATRIX* transform )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetCurrentTransform( clientDrawingContext, transform );
        CheckHRESULT( hr );
        return *this;
    }
    PixelSnapping& PixelSnapping::GetPixelsPerDip( void* clientDrawingContext, FLOAT* pixelsPerDip )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetPixelsPerDip( clientDrawingContext, pixelsPerDip );
        CheckHRESULT( hr );
        return *this;
    }

    // ================================================================
    // TextRenderer
    // ================================================================
    TextRenderer& TextRenderer::DrawGlyphRun( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_MEASURING_MODE measuringMode, DWRITE_GLYPH_RUN const* glyphRun, DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription, IUnknown* clientDrawingEffect )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->DrawGlyphRun( clientDrawingContext, baselineOriginX, baselineOriginY, measuringMode, glyphRun, glyphRunDescription, clientDrawingEffect );
        CheckHRESULT( hr );
        return *this;
    }
    TextRenderer& TextRenderer::DrawUnderline( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_UNDERLINE const* underline, IUnknown* clientDrawingEffect )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->DrawUnderline( clientDrawingContext, baselineOriginX, baselineOriginY, underline, clientDrawingEffect );
        CheckHRESULT( hr );
        return *this;
    }
    TextRenderer& TextRenderer::DrawStrikethrough( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_STRIKETHROUGH const* strikethrough, IUnknown* clientDrawingEffect )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->DrawStrikethrough( clientDrawingContext, baselineOriginX, baselineOriginY, strikethrough, clientDrawingEffect );
        CheckHRESULT( hr );
        return *this;
    }
    TextRenderer& TextRenderer::DrawInlineObject( void* clientDrawingContext, FLOAT originX, FLOAT originY, IDWriteInlineObject* inlineObject, BOOL isSideways, BOOL isRightToLeft, IUnknown* clientDrawingEffect )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->DrawInlineObject( clientDrawingContext, originX, originY, inlineObject, isSideways, isRightToLeft, clientDrawingEffect );
        CheckHRESULT( hr );
        return *this;
    }
    // ================================================================
    // 
    // ================================================================
    TextLayout& TextLayout::SetMaxWidth( FLOAT maxWidth )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetMaxWidth( maxWidth );
        CheckHRESULT( hr );
        return *this;
    }
    TextLayout& TextLayout::SetMaxHeight( FLOAT maxHeight )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetMaxHeight( maxHeight );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::SetFontCollection( IDWriteFontCollection* fontCollection, DWRITE_TEXT_RANGE textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFontCollection( fontCollection, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::SetFontFamilyName( WCHAR const* fontFamilyName, DWRITE_TEXT_RANGE textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFontFamilyName( fontFamilyName, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::SetFontWeight( DWRITE_FONT_WEIGHT fontWeight, DWRITE_TEXT_RANGE textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFontWeight( fontWeight, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::SetFontStyle( DWRITE_FONT_STYLE fontStyle, DWRITE_TEXT_RANGE textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFontStyle( fontStyle, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::SetFontStretch( DWRITE_FONT_STRETCH fontStretch, DWRITE_TEXT_RANGE textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFontStretch( fontStretch, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::SetFontSize( FLOAT fontSize, DWRITE_TEXT_RANGE textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetFontSize( fontSize, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::SetUnderline( BOOL hasUnderline, DWRITE_TEXT_RANGE textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetUnderline( hasUnderline, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::SetStrikethrough( BOOL hasStrikethrough, DWRITE_TEXT_RANGE textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetStrikethrough( hasStrikethrough, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::SetDrawingEffect( IUnknown* drawingEffect, DWRITE_TEXT_RANGE textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetDrawingEffect( drawingEffect, textRange );
        CheckHRESULT( hr );
        return *this;
    }
    TextLayout& TextLayout::SetInlineObject( IDWriteInlineObject* inlineObject, DWRITE_TEXT_RANGE textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetInlineObject( inlineObject, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::SetTypography( IDWriteTypography* typography, DWRITE_TEXT_RANGE textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetTypography( typography, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::SetLocaleName( WCHAR const* localeName, DWRITE_TEXT_RANGE textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetLocaleName( localeName, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    FLOAT TextLayout::GetMaxWidth( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetMaxWidth( );
    }

    FLOAT TextLayout::GetMaxHeight( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetMaxHeight( );
    }

    TextLayout& TextLayout::GetFontCollection( UINT32 currentPosition, IDWriteFontCollection** fontCollection, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontCollection( currentPosition, fontCollection, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::GetFontFamilyNameLength( UINT32 currentPosition, UINT32* nameLength, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamilyNameLength( currentPosition, nameLength, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::GetFontFamilyName( UINT32 currentPosition, _Out_writes_z_( nameSize ) WCHAR* fontFamilyName, UINT32 nameSize, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontFamilyName( currentPosition, fontFamilyName, nameSize, textRange );
        CheckHRESULT( hr );
        return *this;
    }
    TextLayout& TextLayout::GetFontWeight( UINT32 currentPosition, DWRITE_FONT_WEIGHT* fontWeight, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontWeight( currentPosition, fontWeight, textRange );
        CheckHRESULT( hr );
        return *this;
    }
    TextLayout& TextLayout::GetFontStyle( UINT32 currentPosition, DWRITE_FONT_STYLE* fontStyle, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontStyle( currentPosition, fontStyle, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::GetFontStretch( UINT32 currentPosition, DWRITE_FONT_STRETCH* fontStretch, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontStretch( currentPosition, fontStretch, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::GetFontSize( UINT32 currentPosition, FLOAT* fontSize, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetFontSize( currentPosition, fontSize, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::GetUnderline( UINT32 currentPosition, BOOL* hasUnderline, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetUnderline( currentPosition, hasUnderline, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::GetStrikethrough( UINT32 currentPosition, BOOL* hasStrikethrough, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetStrikethrough( currentPosition, hasStrikethrough, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::GetDrawingEffect( UINT32 currentPosition, IUnknown** drawingEffect, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetDrawingEffect( currentPosition, drawingEffect, textRange );
        CheckHRESULT( hr );
        return *this;
    }
    TextLayout& TextLayout::GetInlineObject( UINT32 currentPosition, IDWriteInlineObject** inlineObject, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetInlineObject( currentPosition, inlineObject, textRange );
        CheckHRESULT( hr );
        return *this;
    }
    TextLayout& TextLayout::GetTypography( UINT32 currentPosition, IDWriteTypography** typography, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetTypography( currentPosition, typography, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::GetLocaleNameLength( UINT32 currentPosition, UINT32* nameLength, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleNameLength( currentPosition, nameLength, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::GetLocaleName( UINT32 currentPosition, _Out_writes_z_( nameSize ) WCHAR* localeName, UINT32 nameSize, _Out_opt_ DWRITE_TEXT_RANGE* textRange )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLocaleName( currentPosition, localeName, nameSize, textRange );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::Draw( void* clientDrawingContext, IDWriteTextRenderer* renderer, FLOAT originX, FLOAT originY )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->Draw( clientDrawingContext, renderer, originX, originY );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::GetLineMetrics( DWRITE_LINE_METRICS* lineMetrics, UINT32 maxLineCount, UINT32* actualLineCount )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetLineMetrics( lineMetrics, maxLineCount, actualLineCount );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::GetMetrics( DWRITE_TEXT_METRICS* textMetrics )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetMetrics( textMetrics );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::GetOverhangMetrics( DWRITE_OVERHANG_METRICS* overhangs )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetOverhangMetrics( overhangs );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::GetClusterMetrics( DWRITE_CLUSTER_METRICS* clusterMetrics, UINT32 maxClusterCount, UINT32* actualClusterCount )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetClusterMetrics( clusterMetrics, maxClusterCount, actualClusterCount );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::DetermineMinWidth( FLOAT* minWidth )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->DetermineMinWidth( minWidth );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::HitTestPoint( FLOAT pointX, FLOAT pointY, BOOL* isTrailingHit, BOOL* isInside, DWRITE_HIT_TEST_METRICS* hitTestMetrics )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->HitTestPoint( pointX, pointY, isTrailingHit, isInside, hitTestMetrics );
        CheckHRESULT( hr );
        return *this;
    }

    TextLayout& TextLayout::HitTestTextPosition( UINT32 textPosition, BOOL isTrailingHit, FLOAT* pointX, FLOAT* pointY, DWRITE_HIT_TEST_METRICS* hitTestMetrics )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->HitTestTextPosition( textPosition, isTrailingHit, pointX, pointY, hitTestMetrics );
        CheckHRESULT( hr );
        return *this;
    }
    TextLayout& TextLayout::HitTestTextRange( UINT32 textPosition, UINT32 textLength, FLOAT originX, FLOAT originY, DWRITE_HIT_TEST_METRICS* hitTestMetrics, UINT32 maxHitTestMetricsCount, UINT32* actualHitTestMetricsCount )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->HitTestTextRange( textPosition, textLength, originX, originY, hitTestMetrics, maxHitTestMetricsCount, actualHitTestMetricsCount );
        CheckHRESULT( hr );
        return *this;
    }

    // ================================================================
    // BitmapRenderTarget
    // ================================================================
    BitmapRenderTarget& BitmapRenderTarget::DrawGlyphRun( FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_MEASURING_MODE measuringMode, DWRITE_GLYPH_RUN const* glyphRun, IDWriteRenderingParams* renderingParams, COLORREF textColor, _Out_opt_ RECT* blackBoxRect )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->DrawGlyphRun( baselineOriginX, baselineOriginY, measuringMode, glyphRun, renderingParams, textColor, blackBoxRect );
        CheckHRESULT( hr );
        return *this;
    }

    HDC BitmapRenderTarget::GetMemoryDC( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetMemoryDC( );
    }

    FLOAT BitmapRenderTarget::GetPixelsPerDip( )
    {
        InterfaceType* pInterface = GetInterface( );
        return pInterface->GetPixelsPerDip( );
    }
    BitmapRenderTarget& BitmapRenderTarget::SetPixelsPerDip( FLOAT pixelsPerDip )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetPixelsPerDip( pixelsPerDip );
        CheckHRESULT( hr );
        return *this;
    }

    BitmapRenderTarget& BitmapRenderTarget::GetCurrentTransform( DWRITE_MATRIX* transform )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetCurrentTransform( transform );
        CheckHRESULT( hr );
        return *this;
    }
    BitmapRenderTarget& BitmapRenderTarget::SetCurrentTransform( DWRITE_MATRIX const* transform )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->SetCurrentTransform( transform );
        CheckHRESULT( hr );
        return *this;
    }

    BitmapRenderTarget& BitmapRenderTarget::GetSize( SIZE* size )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetSize( size );
        CheckHRESULT( hr );
        return *this;
    }

    BitmapRenderTarget& BitmapRenderTarget::Resize( UINT32 width, UINT32 height )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->Resize( width, height );
        CheckHRESULT( hr );
        return *this;
    }
    // ================================================================
    // GdiInterop
    // ================================================================
    GdiInterop& GdiInterop::CreateFontFromLOGFONT( LOGFONTW const* logFont, IDWriteFont** font )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFromLOGFONT( logFont, font );
        CheckHRESULT( hr );
        return *this;
    }

    GdiInterop& GdiInterop::ConvertFontToLOGFONT( IDWriteFont* font, LOGFONTW* logFont, BOOL* isSystemFont )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->ConvertFontToLOGFONT( font, logFont, isSystemFont );
        CheckHRESULT( hr );
        return *this;
    }

    GdiInterop& GdiInterop::ConvertFontFaceToLOGFONT( IDWriteFontFace* font, LOGFONTW* logFont )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->ConvertFontFaceToLOGFONT( font, logFont );
        CheckHRESULT( hr );
        return *this;
    }

    GdiInterop& GdiInterop::CreateFontFaceFromHdc( HDC hdc, IDWriteFontFace** fontFace )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFaceFromHdc( hdc, fontFace );
        CheckHRESULT( hr );
        return *this;
    }

    GdiInterop& GdiInterop::CreateBitmapRenderTarget( HDC hdc, UINT32 width, UINT32 height, IDWriteBitmapRenderTarget** renderTarget )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateBitmapRenderTarget( hdc, width, height, renderTarget );
        CheckHRESULT( hr );
        return *this;
    }
    // ================================================================
    // GlyphRunAnalysis
    // ================================================================
    GlyphRunAnalysis& GlyphRunAnalysis::GetAlphaTextureBounds( DWRITE_TEXTURE_TYPE textureType, RECT* textureBounds )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetAlphaTextureBounds( textureType, textureBounds );
        CheckHRESULT( hr );
        return *this;
    }
    GlyphRunAnalysis& GlyphRunAnalysis::CreateAlphaTexture( DWRITE_TEXTURE_TYPE textureType, RECT const* textureBounds, BYTE* alphaValues, UINT32 bufferSize )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateAlphaTexture( textureType, textureBounds, alphaValues, bufferSize );
        CheckHRESULT( hr );
        return *this;
    }

    GlyphRunAnalysis& GlyphRunAnalysis::GetAlphaBlendParams( IDWriteRenderingParams* renderingParams, FLOAT* blendGamma, FLOAT* blendEnhancedContrast, FLOAT* blendClearTypeLevel )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetAlphaBlendParams( renderingParams, blendGamma, blendEnhancedContrast, blendClearTypeLevel );
        CheckHRESULT( hr );
        return *this;
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

    Factory& Factory::GetSystemFontCollection( IDWriteFontCollection** fontCollection, BOOL checkForUpdates )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetSystemFontCollection( fontCollection, checkForUpdates );
        CheckHRESULT( hr );
        return *this;
    }
    FontCollection Factory::GetSystemFontCollection( bool checkForUpdates )
    {
        IDWriteFontCollection* fontCollection = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetSystemFontCollection( &fontCollection, checkForUpdates );
        CheckHRESULT( hr );
        FontCollection result( fontCollection );
        return result;
    }

    Factory& Factory::CreateCustomFontCollection( IDWriteFontCollectionLoader* collectionLoader, void const* collectionKey, UINT32 collectionKeySize, IDWriteFontCollection** fontCollection )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateCustomFontCollection( collectionLoader, collectionKey, collectionKeySize, fontCollection );
        CheckHRESULT( hr );
        return *this;
    }
    FontCollection Factory::CreateCustomFontCollection( IDWriteFontCollectionLoader* collectionLoader, void const* collectionKey, UINT32 collectionKeySize )
    {
        IDWriteFontCollection* fontCollection = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateCustomFontCollection( collectionLoader, collectionKey, collectionKeySize, &fontCollection );
        CheckHRESULT( hr );
        FontCollection result( fontCollection );
        return result;
    }

    Factory& Factory::RegisterFontCollectionLoader( IDWriteFontCollectionLoader* fontCollectionLoader )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->RegisterFontCollectionLoader( fontCollectionLoader );
        CheckHRESULT( hr );
        return *this;
    }
    Factory& Factory::UnregisterFontCollectionLoader( IDWriteFontCollectionLoader* fontCollectionLoader )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->UnregisterFontCollectionLoader( fontCollectionLoader );
        CheckHRESULT( hr );
        return *this;
    }
    Factory& Factory::CreateFontFileReference( WCHAR const* filePath, FILETIME const* lastWriteTime, IDWriteFontFile** fontFile )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFileReference( filePath, lastWriteTime, fontFile );
        CheckHRESULT( hr );
        return *this;
    }
    FontFile Factory::CreateFontFileReference( WCHAR const* filePath, FILETIME const* lastWriteTime )
    {
        IDWriteFontFile* fontFile = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFileReference( filePath, lastWriteTime, &fontFile );
        CheckHRESULT( hr );
        FontFile result( fontFile );
        return result;
    }
    Factory& Factory::CreateCustomFontFileReference( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileLoader* fontFileLoader, IDWriteFontFile** fontFile )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateCustomFontFileReference( fontFileReferenceKey, fontFileReferenceKeySize, fontFileLoader, fontFile );
        CheckHRESULT( hr );
        return *this;
    }
    FontFile Factory::CreateCustomFontFileReference( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileLoader* fontFileLoader )
    {
        IDWriteFontFile* fontFile = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateCustomFontFileReference( fontFileReferenceKey, fontFileReferenceKeySize, fontFileLoader, &fontFile );
        CheckHRESULT( hr );
        FontFile result( fontFile );
        return result;
    }

    Factory& Factory::CreateFontFace( DWRITE_FONT_FACE_TYPE fontFaceType, UINT32 numberOfFiles, IDWriteFontFile* const* fontFiles, UINT32 faceIndex, DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags, IDWriteFontFace** fontFace )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFace( fontFaceType, numberOfFiles, fontFiles, faceIndex, fontFaceSimulationFlags, fontFace );
        CheckHRESULT( hr );
        return *this;
    }
    FontFace Factory::CreateFontFace( DWRITE_FONT_FACE_TYPE fontFaceType, UINT32 numberOfFiles, IDWriteFontFile* const* fontFiles, UINT32 faceIndex, DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags )
    {
        IDWriteFontFace* fontFace = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateFontFace( fontFaceType, numberOfFiles, fontFiles, faceIndex, fontFaceSimulationFlags, &fontFace );
        CheckHRESULT( hr );
        FontFace result( fontFace );
        return result;
    }

    Factory& Factory::CreateRenderingParams( IDWriteRenderingParams** renderingParams )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateRenderingParams( renderingParams );
        CheckHRESULT( hr );
        return *this;
    }
    RenderingParams Factory::CreateRenderingParams( )
    {
        IDWriteRenderingParams* renderingParams = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateRenderingParams( &renderingParams );
        CheckHRESULT( hr );
        RenderingParams result( renderingParams );
        return result;
    }

    Factory& Factory::CreateMonitorRenderingParams( HMONITOR monitor, IDWriteRenderingParams** renderingParams )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateMonitorRenderingParams( monitor, renderingParams );
        CheckHRESULT( hr );
        return *this;
    }
    RenderingParams Factory::CreateMonitorRenderingParams( HMONITOR monitor )
    {
        IDWriteRenderingParams* renderingParams = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateMonitorRenderingParams( monitor, &renderingParams );
        CheckHRESULT( hr );
        RenderingParams result( renderingParams );
        return result;
    }

    Factory& Factory::CreateCustomRenderingParams( FLOAT gamma, FLOAT enhancedContrast, FLOAT clearTypeLevel, DWRITE_PIXEL_GEOMETRY pixelGeometry, DWRITE_RENDERING_MODE renderingMode, IDWriteRenderingParams** renderingParams )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateCustomRenderingParams( gamma, enhancedContrast, clearTypeLevel, pixelGeometry, renderingMode, renderingParams );
        CheckHRESULT( hr );
        return *this;
    }
    RenderingParams Factory::CreateCustomRenderingParams( FLOAT gamma, FLOAT enhancedContrast, FLOAT clearTypeLevel, DWRITE_PIXEL_GEOMETRY pixelGeometry, DWRITE_RENDERING_MODE renderingMode )
    {
        IDWriteRenderingParams* renderingParams = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateCustomRenderingParams( gamma, enhancedContrast, clearTypeLevel, pixelGeometry, renderingMode, &renderingParams );
        CheckHRESULT( hr );
        RenderingParams result( renderingParams );
        return result;
    }

    Factory& Factory::RegisterFontFileLoader( IDWriteFontFileLoader* fontFileLoader )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->RegisterFontFileLoader( fontFileLoader );
        CheckHRESULT( hr );
        return *this;
    }

    Factory& Factory::UnregisterFontFileLoader( IDWriteFontFileLoader* fontFileLoader )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->UnregisterFontFileLoader( fontFileLoader );
        CheckHRESULT( hr );
        return *this;
    }

    Factory& Factory::CreateTextFormat( WCHAR const* fontFamilyName, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName, IDWriteTextFormat** textFormat )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTextFormat( fontFamilyName, fontCollection, fontWeight, fontStyle, fontStretch, fontSize, localeName, textFormat );
        CheckHRESULT( hr );
        return *this;
    }
    TextFormat Factory::CreateTextFormat( WCHAR const* fontFamilyName, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName )
    {
        IDWriteTextFormat* textFormat = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTextFormat( fontFamilyName, fontCollection, fontWeight, fontStyle, fontStretch, fontSize, localeName, &textFormat );
        CheckHRESULT( hr );
        TextFormat result( textFormat );
        return result;
    }

    TextFormat Factory::CreateTextFormat( WCHAR const* fontFamilyName, FLOAT fontSize )
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


    Factory& Factory::CreateTypography( IDWriteTypography** typography )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTypography( typography );
        CheckHRESULT( hr );
        return *this;
    }

    Typography Factory::CreateTypography( )
    {
        IDWriteTypography* typography = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTypography( &typography );
        CheckHRESULT( hr );
        Typography result( typography );
        return result;
    }

    Factory& Factory::GetGdiInterop( IDWriteGdiInterop** gdiInterop )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGdiInterop( gdiInterop );
        CheckHRESULT( hr );
        return *this;
    }

    GdiInterop Factory::GetGdiInterop( )
    {
        IDWriteGdiInterop* gdiInterop = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->GetGdiInterop( &gdiInterop );
        CheckHRESULT( hr );
        GdiInterop result( gdiInterop );
        return result;
    }

    Factory& Factory::CreateTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT maxWidth, FLOAT maxHeight, IDWriteTextLayout** textLayout )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTextLayout( string, stringLength, textFormat, maxWidth, maxHeight, textLayout );
        CheckHRESULT( hr );
        return *this;
    }
    TextLayout Factory::CreateTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT maxWidth, FLOAT maxHeight )
    {
        IDWriteTextLayout* textLayout = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTextLayout( string, stringLength, textFormat, maxWidth, maxHeight, &textLayout );
        CheckHRESULT( hr );
        TextLayout result( textLayout );
        return result;
    }

    Factory& Factory::CreateGdiCompatibleTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT layoutWidth, FLOAT layoutHeight, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural, IDWriteTextLayout** textLayout )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateGdiCompatibleTextLayout( string, stringLength, textFormat, layoutWidth, layoutHeight, pixelsPerDip, transform, useGdiNatural, textLayout );
        CheckHRESULT( hr );
        return *this;
    }
    TextLayout Factory::CreateGdiCompatibleTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT layoutWidth, FLOAT layoutHeight, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural )
    {
        IDWriteTextLayout* textLayout = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateGdiCompatibleTextLayout( string, stringLength, textFormat, layoutWidth, layoutHeight, pixelsPerDip, transform, useGdiNatural, &textLayout );
        CheckHRESULT( hr );
        TextLayout result( textLayout );
        return result;
    }

    Factory& Factory::CreateEllipsisTrimmingSign( IDWriteTextFormat* textFormat, IDWriteInlineObject** trimmingSign )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateEllipsisTrimmingSign( textFormat, trimmingSign );
        CheckHRESULT( hr );
        return *this;
    }
    InlineObject Factory::CreateEllipsisTrimmingSign( IDWriteTextFormat* textFormat )
    {
        IDWriteInlineObject* trimmingSign = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateEllipsisTrimmingSign( textFormat, &trimmingSign );
        CheckHRESULT( hr );
        InlineObject result( trimmingSign );
        return result;
    }
    Factory& Factory::CreateTextAnalyzer( IDWriteTextAnalyzer** textAnalyzer )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTextAnalyzer( textAnalyzer );
        CheckHRESULT( hr );
        return *this;
    }
    TextAnalyzer Factory::CreateTextAnalyzer( )
    {
        IDWriteTextAnalyzer* textAnalyzer = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateTextAnalyzer( &textAnalyzer );
        CheckHRESULT( hr );
        TextAnalyzer result( textAnalyzer );
        return result;
    }

    Factory& Factory::CreateNumberSubstitution( DWRITE_NUMBER_SUBSTITUTION_METHOD substitutionMethod, WCHAR const* localeName, BOOL ignoreUserOverride, IDWriteNumberSubstitution** numberSubstitution )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateNumberSubstitution( substitutionMethod, localeName, ignoreUserOverride, numberSubstitution );
        CheckHRESULT( hr );
        return *this;
    }

    Factory& Factory::CreateGlyphRunAnalysis( DWRITE_GLYPH_RUN const* glyphRun, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_RENDERING_MODE renderingMode, DWRITE_MEASURING_MODE measuringMode, FLOAT baselineOriginX, FLOAT baselineOriginY, IDWriteGlyphRunAnalysis** glyphRunAnalysis )
    {
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateGlyphRunAnalysis( glyphRun, pixelsPerDip, transform, renderingMode, measuringMode, baselineOriginX, baselineOriginY, glyphRunAnalysis );
        CheckHRESULT( hr );
        return *this;
    }

    GlyphRunAnalysis Factory::CreateGlyphRunAnalysis( DWRITE_GLYPH_RUN const* glyphRun, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_RENDERING_MODE renderingMode, DWRITE_MEASURING_MODE measuringMode, FLOAT baselineOriginX, FLOAT baselineOriginY )
    {
        IDWriteGlyphRunAnalysis* glyphRunAnalysis = nullptr;
        InterfaceType* pInterface = GetInterface( );
        HRESULT hr = pInterface->CreateGlyphRunAnalysis( glyphRun, pixelsPerDip, transform, renderingMode, measuringMode, baselineOriginX, baselineOriginY, &glyphRunAnalysis );
        CheckHRESULT( hr );
        GlyphRunAnalysis result( glyphRunAnalysis );
        return result;
    }


}