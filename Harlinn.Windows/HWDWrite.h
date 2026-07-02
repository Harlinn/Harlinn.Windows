#pragma once
#ifndef HARLINN_WINDOWS_HWDWRITE_H_
#define HARLINN_WINDOWS_HWDWRITE_H_
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

#include <HWGraphics.h>

namespace Harlinn::Windows::Graphics::DirectWrite
{
    /// <summary>
    /// The type of a font represented by a single font file.
    /// Font formats that consist of multiple files, e.g. Type 1 .PFM and .PFB, have
    /// separate enum values for each of the file type.
    /// </summary>
    enum class FontFileType : int
    {
        /// <summary>
        /// Font type is not recognized by the DirectWrite font system.
        /// </summary>
        Unknown = DWRITE_FONT_FILE_TYPE_UNKNOWN,

        /// <summary>
        /// OpenType font with CFF outlines.
        /// </summary>
        CFF = DWRITE_FONT_FILE_TYPE_CFF,

        /// <summary>
        /// OpenType font with TrueType outlines.
        /// </summary>
        TrueType = DWRITE_FONT_FILE_TYPE_TRUETYPE,

        /// <summary>
        /// OpenType font that contains a TrueType collection.
        /// </summary>
        OpenTypeCollection = DWRITE_FONT_FILE_TYPE_OPENTYPE_COLLECTION,

        /// <summary>
        /// Type 1 PFM font.
        /// </summary>
        Type1PFM = DWRITE_FONT_FILE_TYPE_TYPE1_PFM,

        /// <summary>
        /// Type 1 PFB font.
        /// </summary>
        Type1PFB = DWRITE_FONT_FILE_TYPE_TYPE1_PFB,

        /// <summary>
        /// Vector .FON font.
        /// </summary>
        Vector = DWRITE_FONT_FILE_TYPE_VECTOR,

        /// <summary>
        /// Bitmap .FON font.
        /// </summary>
        Bitmap = DWRITE_FONT_FILE_TYPE_BITMAP,

        // The following name is obsolete, but kept as an alias to avoid breaking existing code.
        TrueTypeCollection = DWRITE_FONT_FILE_TYPE_OPENTYPE_COLLECTION
    };


    /// <summary>
    /// The file format of a complete font face.
    /// Font formats that consist of multiple files, e.g. Type 1 .PFM and .PFB, have
    /// a single enum entry.
    /// </summary>
    enum class FontFaceType : int
    {
        /// <summary>
        /// OpenType font face with CFF outlines.
        /// </summary>
        CFF = DWRITE_FONT_FACE_TYPE_CFF,

        /// <summary>
        /// OpenType font face with TrueType outlines.
        /// </summary>
        TrueType = DWRITE_FONT_FACE_TYPE_TRUETYPE,

        /// <summary>
        /// OpenType font face that is a part of a TrueType or CFF collection.
        /// </summary>
        OpenTypeCollection = DWRITE_FONT_FACE_TYPE_OPENTYPE_COLLECTION,

        /// <summary>
        /// A Type 1 font face.
        /// </summary>
        Type1 = DWRITE_FONT_FACE_TYPE_TYPE1,

        /// <summary>
        /// A vector .FON format font face.
        /// </summary>
        Vector = DWRITE_FONT_FACE_TYPE_VECTOR,

        /// <summary>
        /// A bitmap .FON format font face.
        /// </summary>
        Bitmap = DWRITE_FONT_FACE_TYPE_BITMAP,

        /// <summary>
        /// Font face type is not recognized by the DirectWrite font system.
        /// </summary>
        Unknown = DWRITE_FONT_FACE_TYPE_UNKNOWN,

        /// <summary>
        /// The font data includes only the CFF table from an OpenType CFF font.
        /// This font face type can be used only for embedded fonts (i.e., custom
        /// font file loaders) and the resulting font face object supports only the
        /// minimum functionality necessary to render glyphs.
        /// </summary>
        RawCFF = DWRITE_FONT_FACE_TYPE_RAW_CFF,

        // The following name is obsolete, but kept as an alias to avoid breaking existing code.
        TrueTypeCollection = DWRITE_FONT_FACE_TYPE_OPENTYPE_COLLECTION,
    };


    /// <summary>
    /// Specifies algorithmic style simulations to be applied to the font face.
    /// Bold and oblique simulations can be combined via bitwise OR operation.
    /// </summary>
    enum class FontSimulation : int
    {
        /// <summary>
        /// No simulations are performed.
        /// </summary>
        None = DWRITE_FONT_SIMULATIONS_NONE,

        /// <summary>
        /// Algorithmic emboldening is performed.
        /// </summary>
        Bold = DWRITE_FONT_SIMULATIONS_BOLD,

        /// <summary>
        /// Algorithmic italicization is performed.
        /// </summary>
        Oblique = DWRITE_FONT_SIMULATIONS_OBLIQUE
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( FontSimulation, int );


    /// <summary>
    /// The font weight enumeration describes common values for degree of blackness or thickness of strokes of characters in a font.
    /// Font weight values less than 1 or greater than 999 are considered to be invalid, and they are rejected by font API functions.
    /// </summary>
    enum class FontWeight : int
    {
        /// <summary>
        /// Predefined font weight : Thin (100).
        /// </summary>
        Thin = DWRITE_FONT_WEIGHT_THIN,

        /// <summary>
        /// Predefined font weight : Extra-light (200).
        /// </summary>
        ExtraLight = DWRITE_FONT_WEIGHT_EXTRA_LIGHT,

        /// <summary>
        /// Predefined font weight : Ultra-light (200).
        /// </summary>
        UltraLight = DWRITE_FONT_WEIGHT_ULTRA_LIGHT,

        /// <summary>
        /// Predefined font weight : Light (300).
        /// </summary>
        Light = DWRITE_FONT_WEIGHT_LIGHT,

        /// <summary>
        /// Predefined font weight : Semi-light (350).
        /// </summary>
        SemiLight = DWRITE_FONT_WEIGHT_SEMI_LIGHT,

        /// <summary>
        /// Predefined font weight : Normal (400).
        /// </summary>
        Normal = DWRITE_FONT_WEIGHT_NORMAL,

        /// <summary>
        /// Predefined font weight : Regular (400).
        /// </summary>
        Regular = DWRITE_FONT_WEIGHT_REGULAR,

        /// <summary>
        /// Predefined font weight : Medium (500).
        /// </summary>
        Medium = DWRITE_FONT_WEIGHT_MEDIUM,

        /// <summary>
        /// Predefined font weight : Demi-bold (600).
        /// </summary>
        DemiBold = DWRITE_FONT_WEIGHT_DEMI_BOLD,

        /// <summary>
        /// Predefined font weight : Semi-bold (600).
        /// </summary>
        SemiBold = DWRITE_FONT_WEIGHT_SEMI_BOLD,

        /// <summary>
        /// Predefined font weight : Bold (700).
        /// </summary>
        Bold = DWRITE_FONT_WEIGHT_BOLD,

        /// <summary>
        /// Predefined font weight : Extra-bold (800).
        /// </summary>
        ExtraBold = DWRITE_FONT_WEIGHT_EXTRA_BOLD,

        /// <summary>
        /// Predefined font weight : Ultra-bold (800).
        /// </summary>
        UltraBold = DWRITE_FONT_WEIGHT_ULTRA_BOLD,

        /// <summary>
        /// Predefined font weight : Black (900).
        /// </summary>
        Black = DWRITE_FONT_WEIGHT_BLACK,

        /// <summary>
        /// Predefined font weight : Heavy (900).
        /// </summary>
        Heavy = DWRITE_FONT_WEIGHT_HEAVY,

        /// <summary>
        /// Predefined font weight : Extra-black (950).
        /// </summary>
        ExtraBlack = DWRITE_FONT_WEIGHT_EXTRA_BLACK,

        /// <summary>
        /// Predefined font weight : Ultra-black (950).
        /// </summary>
        UltraBlack = DWRITE_FONT_WEIGHT_ULTRA_BLACK
    };

    /// <summary>
    /// The font stretch enumeration describes relative change from the normal aspect ratio
    /// as specified by a font designer for the glyphs in a font.
    /// Values less than 1 or greater than 9 are considered to be invalid, and they are rejected by font API functions.
    /// </summary>
    enum class FontStretch : int
    {
        /// <summary>
        /// Predefined font stretch : Not known (0).
        /// </summary>
        Undefined = DWRITE_FONT_STRETCH_UNDEFINED,

        /// <summary>
        /// Predefined font stretch : Ultra-condensed (1).
        /// </summary>
        UltraCondensed = DWRITE_FONT_STRETCH_ULTRA_CONDENSED,

        /// <summary>
        /// Predefined font stretch : Extra-condensed (2).
        /// </summary>
        ExtraCondensed = DWRITE_FONT_STRETCH_EXTRA_CONDENSED,

        /// <summary>
        /// Predefined font stretch : Condensed (3).
        /// </summary>
        Condensed = DWRITE_FONT_STRETCH_CONDENSED,

        /// <summary>
        /// Predefined font stretch : Semi-condensed (4).
        /// </summary>
        SemiCondensed = DWRITE_FONT_STRETCH_SEMI_CONDENSED,

        /// <summary>
        /// Predefined font stretch : Normal (5).
        /// </summary>
        Normal = DWRITE_FONT_STRETCH_NORMAL,

        /// <summary>
        /// Predefined font stretch : Medium (5).
        /// </summary>
        Medium = DWRITE_FONT_STRETCH_MEDIUM,

        /// <summary>
        /// Predefined font stretch : Semi-expanded (6).
        /// </summary>
        SemiExpanded = DWRITE_FONT_STRETCH_SEMI_EXPANDED,

        /// <summary>
        /// Predefined font stretch : Expanded (7).
        /// </summary>
        Expanded = DWRITE_FONT_STRETCH_EXPANDED,

        /// <summary>
        /// Predefined font stretch : Extra-expanded (8).
        /// </summary>
        ExtraExpanded = DWRITE_FONT_STRETCH_EXTRA_EXPANDED,

        /// <summary>
        /// Predefined font stretch : Ultra-expanded (9).
        /// </summary>
        UltraExpanded = DWRITE_FONT_STRETCH_ULTRA_EXPANDED
    };


    /// <summary>
    /// The font style enumeration describes the slope style of a font face, such as Normal, Italic or Oblique.
    /// Values other than the ones defined in the enumeration are considered to be invalid, and they are rejected by font API functions.
    /// </summary>
    enum class FontStyle : int
    {
        /// <summary>
        /// Font slope style : Normal.
        /// </summary>
        Normal = DWRITE_FONT_STYLE_NORMAL,

        /// <summary>
        /// Font slope style : Oblique.
        /// </summary>
        Oblique = DWRITE_FONT_STYLE_OBLIQUE,

        /// <summary>
        /// Font slope style : Italic.
        /// </summary>
        Italic = DWRITE_FONT_STYLE_ITALIC
    };


    /// <summary>
    /// The informational string enumeration identifies a string in a font.
    /// </summary>
    enum class InformationalStringId : int
    {
        /// <summary>
        /// Unspecified name ID.
        /// </summary>
        None = DWRITE_INFORMATIONAL_STRING_NONE,

        /// <summary>
        /// Copyright notice provided by the font.
        /// </summary>
        CopyrightNotice = DWRITE_INFORMATIONAL_STRING_COPYRIGHT_NOTICE,

        /// <summary>
        /// String containing a version number.
        /// </summary>
        VersionStrings = DWRITE_INFORMATIONAL_STRING_VERSION_STRINGS,

        /// <summary>
        /// Trademark information provided by the font.
        /// </summary>
        Trademark = DWRITE_INFORMATIONAL_STRING_TRADEMARK,

        /// <summary>
        /// Name of the font manufacturer.
        /// </summary>
        Manufacturer = DWRITE_INFORMATIONAL_STRING_MANUFACTURER,

        /// <summary>
        /// Name of the font designer.
        /// </summary>
        Designer = DWRITE_INFORMATIONAL_STRING_DESIGNER,

        /// <summary>
        /// URL of font designer (with protocol, e.g., http://, ftp://).
        /// </summary>
        DesignerUrl = DWRITE_INFORMATIONAL_STRING_DESIGNER_URL,

        /// <summary>
        /// Description of the font. Can contain revision information, usage recommendations, history, features, etc.
        /// </summary>
        Description = DWRITE_INFORMATIONAL_STRING_DESCRIPTION,

        /// <summary>
        /// URL of font vendor (with protocol, e.g., http://, ftp://). If a unique serial number is embedded in the URL, it can be used to register the font.
        /// </summary>
        FontVendorUrl = DWRITE_INFORMATIONAL_STRING_FONT_VENDOR_URL,

        /// <summary>
        /// Description of how the font may be legally used, or different example scenarios for licensed use. This field should be written in plain language, not legalese.
        /// </summary>
        LicenseDescription = DWRITE_INFORMATIONAL_STRING_LICENSE_DESCRIPTION,

        /// <summary>
        /// URL where additional licensing information can be found.
        /// </summary>
        LicenseInfoUrl = DWRITE_INFORMATIONAL_STRING_LICENSE_INFO_URL,

        /// <summary>
        /// GDI-compatible family name. Because GDI allows a maximum of four fonts per family, fonts in the same family may have different GDI-compatible family names
        /// (e.g., "Arial", "Arial Narrow", "Arial Black").
        /// </summary>
        Win32FamilyNames = DWRITE_INFORMATIONAL_STRING_WIN32_FAMILY_NAMES,

        /// <summary>
        /// GDI-compatible subfamily name.
        /// </summary>
        Win32SubfamilyNames = DWRITE_INFORMATIONAL_STRING_WIN32_SUBFAMILY_NAMES,

        /// <summary>
        /// Typographic family name preferred by the designer. This enables font designers to group more than four fonts in a single family without losing compatibility with
        /// GDI. This name is typically only present if it differs from the GDI-compatible family name.
        /// </summary>
        TypographicFamilyNames = DWRITE_INFORMATIONAL_STRING_TYPOGRAPHIC_FAMILY_NAMES,

        /// <summary>
        /// Typographic subfamily name preferred by the designer. This name is typically only present if it differs from the GDI-compatible subfamily name. 
        /// </summary>
        TypographicSubfamilyNames = DWRITE_INFORMATIONAL_STRING_TYPOGRAPHIC_SUBFAMILY_NAMES,

        /// <summary>
        /// Sample text. This can be the font name or any other text that the designer thinks is the best example to display the font in.
        /// </summary>
        SampleText = DWRITE_INFORMATIONAL_STRING_SAMPLE_TEXT,

        /// <summary>
        /// The full name of the font, e.g. "Arial Bold", from name id 4 in the name table.
        /// </summary>
        FullName = DWRITE_INFORMATIONAL_STRING_FULL_NAME,

        /// <summary>
        /// The postscript name of the font, e.g. "GillSans-Bold" from name id 6 in the name table.
        /// </summary>
        PostscriptName = DWRITE_INFORMATIONAL_STRING_POSTSCRIPT_NAME,

        /// <summary>
        /// The postscript CID findfont name, from name id 20 in the name table.
        /// </summary>
        PostscriptCidName = DWRITE_INFORMATIONAL_STRING_POSTSCRIPT_CID_NAME,

        /// <summary>
        /// Family name for the weight-stretch-style model.
        /// </summary>
        WeightStretchStyleFamilyName = DWRITE_INFORMATIONAL_STRING_WEIGHT_STRETCH_STYLE_FAMILY_NAME,

        /// <summary>
        /// Script/language tag to identify the scripts or languages that the font was
        /// primarily designed to support. See DWRITE_FONT_PROPERTY_ID_DESIGN_SCRIPT_LANGUAGE_TAG
        /// for a longer description.
        /// </summary>
        DesignScriptLanguageTag = DWRITE_INFORMATIONAL_STRING_DESIGN_SCRIPT_LANGUAGE_TAG,

        /// <summary>
        /// Script/language tag to identify the scripts or languages that the font declares
        /// it is able to support.
        /// </summary>
        SupportedScriptLanguageTag = DWRITE_INFORMATIONAL_STRING_SUPPORTED_SCRIPT_LANGUAGE_TAG,

        // Obsolete aliases kept to avoid breaking existing code.
        PreferredFamilyNames = DWRITE_INFORMATIONAL_STRING_TYPOGRAPHIC_FAMILY_NAMES,
        PreferredSubfamilyNames = DWRITE_INFORMATIONAL_STRING_TYPOGRAPHIC_SUBFAMILY_NAMES,
        WwsFamilyName = DWRITE_INFORMATIONAL_STRING_WEIGHT_STRETCH_STYLE_FAMILY_NAME,
    };


    /// <summary>
    /// The FontMetrics structure specifies the metrics of a font face that
    /// are applicable to all glyphs within the font face.
    /// </summary>
    struct FontMetrics : public DWRITE_FONT_METRICS
    {
        using Base = DWRITE_FONT_METRICS;

        FontMetrics( )
            : Base{}
        {}
    };


    /// <summary>
    /// The GlyphMetrics structure specifies the metrics of an individual glyph.
    /// The units depend on how the metrics are obtained.
    /// </summary>
    struct GlyphMetrics : public DWRITE_GLYPH_METRICS
    {
        using Base = DWRITE_GLYPH_METRICS;

        GlyphMetrics( )
            : Base{}
        {}
    };


    /// <summary>
    /// Optional adjustment to a glyph's position. A glyph offset changes the 
    /// position of a glyph without affecting the pen position. Offsets are in 
    /// logical, pre-transform units.
    /// </summary>
    struct GlyphOffset : public DWRITE_GLYPH_OFFSET
    {
        using Base = DWRITE_GLYPH_OFFSET;

        GlyphOffset( )
            : Base{}
        {}
    };


    /// <summary>
    /// Specifies the type of DirectWrite factory object.
    /// DirectWrite factory contains internal state such as font loader registration and cached font data.
    /// In most cases it is recommended to use the shared factory object, because it allows multiple components
    /// that use DirectWrite to share internal DirectWrite state and reduce memory usage.
    /// However, there are cases when it is desirable to reduce the impact of a component,
    /// such as a plug-in from an untrusted source, on the rest of the process by sandboxing and isolating it
    /// from the rest of the process components. In such cases, it is recommended to use an isolated factory for the sandboxed
    /// component.
    /// </summary>
    enum class FactoryType : int 
    {
        /// <summary>
        /// The factory is a shared factory object that can be used by multiple components in the process.
        /// </summary>
        Shared = DWRITE_FACTORY_TYPE_SHARED,
        /// <summary>
        /// The factory is private to the component that created it. It cannot be shared with other components in the process.
        /// </summary>
        Isolated = DWRITE_FACTORY_TYPE_ISOLATED
    };


    class FontFileStream;
    
    /// <summary>
    /// Handles loading font file resources of a particular type from a font file reference key into a font file stream object.
    /// </summary>
    class FontFileLoader : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFileLoader, Unknown, IDWriteFontFileLoader, IUnknown )

        /// <summary>
        /// Creates a font file stream object that encapsulates an open file resource.
        /// </summary>
        /// <param name="fontFileReferenceKey">
        /// A pointer to a font file reference key that uniquely identifies the font file 
        /// resource within the scope of the font loader being used. The buffer allocated 
        /// for this key must at least be the size, in bytes, specified by fontFileReferenceKeySize.
        /// </param>
        /// <param name="fontFileReferenceKeySize">
        /// The size of font file reference key, in bytes.
        /// </param>
        /// <param name="fontFileStream">
        /// When this method returns, contains the address of a pointer to the newly created IDWriteFontFileStream object.
        /// </param>
        void CreateStreamFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileStream** fontFileStream ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateStreamFromKey( fontFileReferenceKey, fontFileReferenceKeySize, fontFileStream );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Creates a font file stream object that encapsulates an open file resource.
        /// </summary>
        /// <typeparam name="T">
        /// The type of the font file reference key container.
        /// </typeparam>
        /// <param name="fontFileReferenceKey">
        /// A reference to the font file reference key container.
        /// </param>
        /// <param name="fontFileStream">
        /// When this method returns, contains the address of a pointer to the newly created IDWriteFontFileStream object.
        /// </param>
        template<typename T>
            requires std::is_standard_layout_v<typename T::value_type>&& ContiguousRange<T>
        void CreateStreamFromKey( const T& fontFileReferenceKey, IDWriteFontFileStream** fontFileStream ) const
        {
            CreateStreamFromKey( fontFileReferenceKey.data( ), static_cast< UINT32 >( fontFileReferenceKey.size( ) * sizeof( typename T::value_type ) ), fontFileStream );
        }


        /// <summary>
        /// Creates a font file stream object that encapsulates an open file resource.
        /// </summary>
        /// <param name="fontFileReferenceKey">
        /// A pointer to a font file reference key that uniquely identifies the font file 
        /// resource within the scope of the font loader being used. The buffer allocated 
        /// for this key must at least be the size, in bytes, specified by fontFileReferenceKeySize.
        /// </param>
        /// <param name="fontFileReferenceKeySize">
        /// The size of font file reference key, in bytes.
        /// </param>
        /// <returns>
        /// A FontFileStream object that encapsulates the open file resource.
        /// </returns>
        inline FontFileStream CreateStreamFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize ) const;

        /// <summary>
        /// Creates a font file stream object that encapsulates an open file resource.
        /// </summary>
        /// <typeparam name="T">
        /// The type of the font file reference key container.
        /// </typeparam>
        /// <param name="fontFileReferenceKey">
        /// A reference to the font file reference key container.
        /// </param>
        /// <returns>
        /// A FontFileStream object that encapsulates the open file resource.
        /// </returns>
        template<typename T>
            requires std::is_standard_layout_v<typename T::value_type>&& ContiguousRange<T>
        FontFileStream CreateStreamFromKey( const T& fontFileReferenceKey ) const
        {
            return CreateStreamFromKey( fontFileReferenceKey.data( ), static_cast<UINT32>( fontFileReferenceKey.size( ) * sizeof( typename T::value_type ) ) );
        }

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

        /// <summary>
        /// Obtains the length of the absolute file path from the font file reference key.
        /// </summary>
        /// <param name="fontFileReferenceKey">
        /// A pointer to the font file reference key.
        /// </param>
        /// <param name="fontFileReferenceKeySize">
        /// The size of the font file reference key, in bytes.
        /// </param>
        /// <param name="filePathLength">
        /// Length of the file path string not including the terminating NULL character.
        /// </param>
        void GetFilePathLengthFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, UINT32* filePathLength ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFilePathLengthFromKey( fontFileReferenceKey, fontFileReferenceKeySize, filePathLength );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }


        /// <summary>
        /// Obtains the length of the absolute file path from the font file reference key.
        /// </summary>
        /// <typeparam name="T">
        /// The type of the font file reference key container.
        /// </typeparam>
        /// <param name="fontFileReferenceKey">
        /// A reference to the font file reference key container.
        /// </param>
        /// <param name="filePathLength">
        /// Length of the file path string not including the terminating NULL character.
        /// </param>
        template<typename T>
            requires std::is_standard_layout_v<typename T::value_type>&& ContiguousRange<T>
        void GetFilePathLengthFromKey( const T& fontFileReferenceKey, UINT32* filePathLength ) const
        {
            GetFilePathLengthFromKey( fontFileReferenceKey.data( ), static_cast<UINT32>( fontFileReferenceKey.size( ) * sizeof( typename T::value_type ) ), filePathLength );
        }

        /// <summary>
        /// Obtains the length of the absolute file path from the font file reference key.
        /// </summary>
        /// <typeparam name="T">
        /// The type of the font file reference key container.
        /// </typeparam>
        /// <param name="fontFileReferenceKey">
        /// A reference to the font file reference key container.
        /// </param>
        /// <returns>
        /// Length of the file path string not including the terminating NULL character.
        /// </returns>
        UINT32 GetFilePathLengthFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize ) const
        {
            UINT32 result = 0;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFilePathLengthFromKey( fontFileReferenceKey, fontFileReferenceKeySize, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        /// <summary>
        /// Obtains the length of the absolute file path from the font file reference key.
        /// </summary>
        /// <typeparam name="T">
        /// The type of the font file reference key container.
        /// </typeparam>
        /// <param name="fontFileReferenceKey">
        /// A reference to the font file reference key container.
        /// </param>
        /// <returns>
        /// Length of the file path string not including the terminating NULL character.
        /// </returns>
        template<typename T>
            requires std::is_standard_layout_v<typename T::value_type>&& ContiguousRange<T>
        UINT32 GetFilePathLengthFromKey( const T& fontFileReferenceKey ) const
        {
            return GetFilePathLengthFromKey( fontFileReferenceKey.data( ), static_cast<UINT32>( fontFileReferenceKey.size( ) * sizeof( typename T::value_type ) ) );
        }

        /// <summary>
        /// Obtains the absolute font file path from the font file reference key.
        /// </summary>
        /// <param name="fontFileReferenceKey">
        /// Font file reference key that uniquely identifies the local font file
        /// within the scope of the font loader being used.
        /// </param>
        /// <param name="fontFileReferenceKeySize">
        /// Size of font file reference key in bytes.
        /// </param>
        /// <param name="filePath">
        /// Character array that receives the local file path.
        /// </param>
        /// <param name="filePathSize">
        /// Size of the filePath array in character count including the terminated NULL character.
        /// </param>
        void GetFilePathFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, WCHAR* filePath, UINT32 filePathSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFilePathFromKey( fontFileReferenceKey, fontFileReferenceKeySize, filePath, filePathSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Obtains the absolute font file path from the font file reference key.
        /// </summary>
        /// <typeparam name="T">
        /// The type of the font file reference key container.
        /// </typeparam>
        /// <param name="fontFileReferenceKey">
        /// A reference to the font file reference key container.
        /// </param>
        /// <param name="filePath">
        /// Character array that receives the absolute font file path.
        /// </param>
        /// <param name="filePathSize">
        /// Size of the filePath array in character count including the terminated NULL character.
        /// </param>
        template<typename T>
            requires std::is_standard_layout_v<typename T::value_type>&& ContiguousRange<T>
        void GetFilePathFromKey( const T& fontFileReferenceKey, WCHAR* filePath, UINT32 filePathSize ) const
        {
            GetFilePathFromKey( fontFileReferenceKey.data( ), static_cast<UINT32>( fontFileReferenceKey.size( ) * sizeof( typename T::value_type ) ), filePath, filePathSize );
        }


        /// <summary>
        /// Obtains the absolute font file path from the font file reference key.
        /// </summary>
        /// <typeparam name="ST">
        /// The type of the string to return.
        /// </typeparam>
        /// <param name="fontFileReferenceKey">
        /// Font file reference key that uniquely identifies the local font file
        /// within the scope of the font loader being used.
        /// </param>
        /// <param name="fontFileReferenceKeySize">
        /// Size of font file reference key in bytes.
        /// </param>
        /// <returns>
        /// The absolute font file path.
        /// </returns>
        template<WideStringLike ST = WideString>
        ST GetFilePathFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize ) const
        {
            UINT32 filePathSize = GetFilePathLengthFromKey( fontFileReferenceKey, fontFileReferenceKeySize );

            ST result;

            result.resize( filePathSize );

            InterfaceType* pInterface = GetInterface( );
            GetFilePathFromKey( fontFileReferenceKey, fontFileReferenceKeySize, result.data( ), filePathSize + 1 );
            return result;
        }

        /// <summary>
        /// Obtains the absolute font file path from the font file reference key.
        /// </summary>
        /// <typeparam name="T">
        /// The type of the font file reference key container.
        /// </typeparam>
        /// <typeparam name="ST">
        /// The type of the string to return.
        /// </typeparam>
        /// <param name="fontFileReferenceKey">
        /// A reference to the font file reference key container.
        /// </param>
        /// <returns>
        /// The absolute font file path.
        /// </returns>
        template<typename T, WideStringLike ST = WideString>
            requires std::is_standard_layout_v<typename T::value_type>&& ContiguousRange<T>
        ST GetFilePathFromKey( const T& fontFileReferenceKey ) const
        {
            return GetFilePathFromKey<ST>( fontFileReferenceKey.data( ), static_cast< UINT32 >( fontFileReferenceKey.size( ) * sizeof( typename T::value_type ) ) );
        }

        /// <summary>
        /// Obtains the last write time of a font file from the font file reference key.
        /// </summary>
        /// <param name="fontFileReferenceKey">
        /// Font file reference key that uniquely identifies the local font file
        /// within the scope of the font loader being used.
        /// </param>
        /// <param name="fontFileReferenceKeySize">
        /// Size of font file reference key in bytes.
        /// </param>
        /// <param name="lastWriteTime">
        /// Pointer to a FILETIME structure that receives the last write time of the font file.
        /// </param>
        void GetLastWriteTimeFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, FILETIME* lastWriteTime ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetLastWriteTimeFromKey( fontFileReferenceKey, fontFileReferenceKeySize, lastWriteTime );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Obtains the last write time of a font file from the font file reference key.
        /// </summary>
        /// <param name="fontFileReferenceKey">
        /// Font file reference key that uniquely identifies the local font file
        /// within the scope of the font loader being used.
        /// </param>
        /// <param name="fontFileReferenceKeySize">
        /// Size of font file reference key in bytes.
        /// </param>
        /// <param name="lastWriteTime">
        /// Pointer to a DateTime structure that receives the last write time of the font file.
        /// </param>
        void GetLastWriteTimeFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, DateTime* lastWriteTime ) const
        {
            FILETIME result = {};
            GetLastWriteTimeFromKey( fontFileReferenceKey, fontFileReferenceKeySize, &result );
            if ( lastWriteTime )
            {
                *lastWriteTime = DateTime::FromFileTime( result );
            }
            else
            {
                InterfaceType* pInterface = GetInterface( );
                HCC_COM_CHECK_HRESULT2( E_POINTER, pInterface );
            }
        }


        /// <summary>
        /// Obtains the last write time of a font file from the font file reference key.
        /// </summary>
        /// <typeparam name="DT">
        /// The type of the last write time to return. Must be either DateTime or FILETIME.
        /// </typeparam>
        /// <param name="fontFileReferenceKey">
        /// Font file reference key that uniquely identifies the local font file
        /// within the scope of the font loader being used.
        /// </param>
        /// <param name="fontFileReferenceKeySize">
        /// Size of font file reference key in bytes.
        /// </param>
        /// <returns>
        /// The last write time of the font file.
        /// </returns>
        template<typename DT = DateTime>
            requires std::is_same_v<DT, DateTime> || std::is_same_v<DT, FILETIME>
        DT GetLastWriteTimeFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize ) const
        {
            DT result{};
            GetLastWriteTimeFromKey( fontFileReferenceKey, fontFileReferenceKeySize, &result );
            return result;
        }

        /// <summary>
        /// Obtains the last write time of a font file from the font file reference key.
        /// </summary>
        /// <typeparam name="DT">
        /// The type of the last write time to return. Must be either DateTime or FILETIME.
        /// </typeparam>
        /// <typeparam name="T">
        /// The type of the font file reference key. Must be a contiguous range of standard layout types.
        /// </typeparam>
        /// <param name="fontFileReferenceKey">
        /// Font file reference key that uniquely identifies the local font file
        /// within the scope of the font loader being used.
        /// </param>
        /// <returns>
        /// The last write time of the font file.
        /// </returns>
        template<typename DT = DateTime, typename T>
            requires std::is_standard_layout_v<typename T::value_type>&& ContiguousRange<T> &&(  std::is_same_v<DT, DateTime> || std::is_same_v<DT, FILETIME> )
        DT GetLastWriteTimeFromKey( const T& fontFileReferenceKey ) const
        {
            DT result{};
            GetLastWriteTimeFromKey( fontFileReferenceKey.data( ), static_cast<UINT32>( fontFileReferenceKey.size( ) ), &result );
            return result;
        }



    };

    /// <summary>
    /// Loads font file data from a custom font file loader.
    /// </summary>
    class FontFileStream : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFileStream, Unknown, IDWriteFontFileStream, IUnknown )

        /// <summary>
        /// Reads a fragment of a font file.
        /// </summary>
        /// <param name="fragmentStart">
        /// Receives the pointer to the start of the font file fragment.
        /// </param>
        /// <param name="fileOffset">
        /// Offset of the fragment from the beginning of the font file.
        /// </param>
        /// <param name="fragmentSize">
        /// Size of the fragment in bytes.
        /// </param>
        /// <param name="fragmentContext">
        /// The client defined context to be passed to the ReleaseFileFragment.
        /// </param>
        void ReadFileFragment( void const** fragmentStart, UINT64 fileOffset, UINT64 fragmentSize, void** fragmentContext ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->ReadFileFragment( fragmentStart, fileOffset, fragmentSize, fragmentContext );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// A moveable, span-like RAII wrapper for font file fragment data.
        /// Automatically manages ReadFileFragment and ReleaseFileFragment lifecycle.
        /// </summary>
        class Fragment
        {
            const FontFileStream* fontFileStream_;
            const void* fragmentStart_;
            UINT64 fragmentSize_;
            void* fragmentContext_;
        public:
            /// <summary>
            /// Constructs an empty Fragment.
            /// </summary>
            Fragment( ) noexcept
                : fontFileStream_( nullptr ), fragmentStart_( nullptr ),
                fragmentSize_( 0 ), fragmentContext_( nullptr )
            {}

            /// <summary>
            /// Constructs a Fragment by reading a fragment from the font file stream.
            /// </summary>
            /// <param name="fontFileStream">The FontFileStream to read from.</param>
            /// <param name="fileOffset">Offset of the fragment from the beginning of the font file.</param>
            /// <param name="fragmentSize">Size of the fragment in bytes.</param>
            Fragment( const FontFileStream& fontFileStream, UINT64 fileOffset, UINT64 fragmentSize )
                : fontFileStream_( &fontFileStream ), fragmentStart_( nullptr ),
                fragmentSize_( fragmentSize ), fragmentContext_( nullptr )
            {
                fontFileStream_->ReadFileFragment( &fragmentStart_, fileOffset, fragmentSize, &fragmentContext_ );
            }

            /// <summary>
            /// Move constructor.
            /// </summary>
            Fragment( Fragment&& other ) noexcept
                : fontFileStream_( other.fontFileStream_ ), fragmentStart_( other.fragmentStart_ ),
                fragmentSize_( other.fragmentSize_ ), fragmentContext_( other.fragmentContext_ )
            {
                other.fontFileStream_ = nullptr;
                other.fragmentStart_ = nullptr;
                other.fragmentSize_ = 0;
                other.fragmentContext_ = nullptr;
            }

            /// <summary>
            /// Move assignment operator.
            /// </summary>
            Fragment& operator=( Fragment&& other ) noexcept
            {
                if ( this != &other )
                {
                    Release( );
                    fontFileStream_ = other.fontFileStream_;
                    fragmentStart_ = other.fragmentStart_;
                    fragmentSize_ = other.fragmentSize_;
                    fragmentContext_ = other.fragmentContext_;

                    other.fontFileStream_ = nullptr;
                    other.fragmentStart_ = nullptr;
                    other.fragmentSize_ = 0;
                    other.fragmentContext_ = nullptr;
                }
                return *this;
            }

            /// <summary>
            /// Destructor. Releases the fragment if it was successfully acquired.
            /// </summary>
            ~Fragment( ) noexcept
            {
                Release( );
            }

            // Deleted copy operations
            Fragment( const Fragment& ) = delete;
            Fragment& operator=( const Fragment& ) = delete;

            /// <summary>
            /// Returns a pointer to the fragment data.
            /// </summary>
            /// <returns>Pointer to the fragment data, or nullptr if no fragment is held.</returns>
            const void* data( ) const noexcept
            {
                return fragmentStart_;
            }

            /// <summary>
            /// Returns the size of the fragment in bytes.
            /// </summary>
            /// <returns>Size of the fragment in bytes.</returns>
            UINT64 size( ) const noexcept
            {
                return fragmentSize_;
            }

            /// <summary>
            /// Returns whether the fragment holds valid data.
            /// </summary>
            /// <returns>True if the fragment holds valid data; otherwise, false.</returns>
            bool Empty( ) const noexcept
            {
                return fragmentStart_ == nullptr;
            }

            /// <summary>
            /// Returns a span view of the fragment data as bytes.
            /// </summary>
            /// <returns>A span of bytes covering the fragment.</returns>
            std::span<const std::byte> AsSpan( ) const noexcept
            {
                return std::span<const std::byte>(
                    static_cast< const std::byte* >( fragmentStart_ ), fragmentSize_ );
            }

            /// <summary>
            /// Returns a span view of the fragment data as a specific type.
            /// </summary>
            /// <typeparam name="T">The element type for the span.</typeparam>
            /// <returns>A span of T covering the fragment (if size is compatible).</returns>
            template<typename T>
            std::span<const T> AsSpan( ) const noexcept
            {
                return std::span<const T>(
                    static_cast< const T* >( fragmentStart_ ),
                    fragmentSize_ / sizeof( T ) );
            }

        private:
            /// <summary>
            /// Releases the held fragment if valid.
            /// </summary>
            void Release( ) noexcept
            {
                if ( fontFileStream_ && fragmentContext_ )
                {
                    fontFileStream_->ReleaseFileFragment( fragmentContext_ );
                }
            }
        };

        /// <summary>
        /// Reads a fragment of the font file.
        /// </summary>
        /// <param name="fileOffset">The offset in the file where the fragment starts.</param>
        /// <param name="fragmentSize">The size of the fragment to read.</param>
        /// <returns>A Fragment object representing the read fragment.</returns>
        Fragment ReadFileFragment( UINT64 fileOffset, UINT64 fragmentSize ) const
        {
            Fragment result(*this, fileOffset, fragmentSize );
            return result;
        }

        /// <summary>
        /// Releases a previously acquired fragment of the font file.
        /// </summary>
        /// <param name="fragmentContext">The context of the fragment to release.</param>
        void ReleaseFileFragment( void* fragmentContext ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ReleaseFileFragment( fragmentContext );
        }

        /// <summary>
        /// Retrieves the size of the font file.
        /// </summary>
        /// <param name="fileSize">A pointer to a variable that receives the file size.</param>
        void GetFileSize( UINT64* fileSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFileSize( fileSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Retrieves the size of the font file.
        /// </summary>
        /// <returns>The size of the font file.</returns>
        UINT64 GetFileSize( ) const
        {
            UINT64 fileSize = 0;
            GetFileSize( &fileSize );
            return fileSize;
        }

        /// <summary>
        /// Retrieves the last write time of the font file.
        /// </summary>
        /// <param name="lastWriteTime">
        /// A pointer to a variable that receives the last write time.
        /// </param>
        /// <returns>
        /// true if the last write time was retrieved successfully; otherwise, false.
        /// </returns>
        bool GetLastWriteTime( UINT64* lastWriteTime ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetLastWriteTime( lastWriteTime );
            if(FAILED(hr))
            {
                if ( hr == E_NOTIMPL )
                {
                    return false;
                }
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return true;
        }

        /// <summary>
        /// Retrieves the last write time of the font file.
        /// </summary>
        /// <param name="lastWriteTime">
        /// A pointer to a variable that receives the last write time.
        /// </param>
        /// <returns>
        /// true if the last write time was retrieved successfully; otherwise, false.
        /// </returns>
        bool GetLastWriteTime( FILETIME* lastWriteTime ) const
        {
            return GetLastWriteTime( reinterpret_cast< UINT64* >( lastWriteTime ) );
        }

        /// <summary>
        /// Retrieves the last write time of the font file.
        /// </summary>
        /// <param name="lastWriteTime">
        /// A pointer to a variable that receives the last write time.
        /// </param>
        /// <returns>
        /// true if the last write time was retrieved successfully; otherwise, false.
        /// </returns>
        bool GetLastWriteTime( DateTime* lastWriteTime ) const
        {
            UINT64 result = 0;
            if ( GetLastWriteTime( &result ) )
            {
                if ( lastWriteTime )
                {
                    *lastWriteTime = DateTime::FromFileTime( result );
                }
                else
                {
                    InterfaceType* pInterface = GetInterface( );
                    HCC_COM_CHECK_HRESULT2( E_POINTER, pInterface );
                }
                return true;
            }
            return false;
        }


        /// <summary>
        /// Retrieves the last write time of the font file.
        /// </summary>
        /// <typeparam name="T">The type of the last write time. Can be DateTime, FILETIME, or UINT64.</typeparam>
        /// <returns>
        /// An optional containing the last write time if it was retrieved successfully; otherwise, std::nullopt.
        /// </returns>
        template<typename T = DateTime>
        std::optional<T> GetLastWriteTime( ) const
            requires std::is_same_v<T, DateTime> || std::is_same_v<T, FILETIME> || std::is_same_v<T, UINT64>
        {
            T result{};
            if ( GetLastWriteTime( &result ) )
            {
                return result;
            }
            return std::nullopt;
        }
    };

    inline FontFileStream FontFileLoader::CreateStreamFromKey( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize ) const
    {
        IDWriteFontFileStream* fontFileStream = nullptr;
        CreateStreamFromKey( fontFileReferenceKey, fontFileReferenceKeySize, &fontFileStream );
        FontFileStream result( fontFileStream );
        return result;
    }



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

        /// <summary>
        /// Obtains the pointer to the reference key of a font file. The returned 
        /// pointer is valid until the font file object is released.
        /// </summary>
        /// <param name="fontFileReferenceKey">A pointer to a variable that receives the reference key.</param>
        /// <param name="fontFileReferenceKeySize">A pointer to a variable that receives the size of the reference key.</param>
        void GetReferenceKey( void const** fontFileReferenceKey, UINT32* fontFileReferenceKeySize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetReferenceKey( fontFileReferenceKey, fontFileReferenceKeySize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Obtains the pointer to the reference key of a font file. The returned 
        /// span is valid until the font file object is released.
        /// </summary>
        /// <returns>
        /// A span containing the reference key bytes.
        /// </returns>
        std::span<const std::byte> GetReferenceKey( ) const
        {
            void const* fontFileReferenceKey = nullptr;
            UINT32 fontFileReferenceKeySize = 0;
            GetReferenceKey( &fontFileReferenceKey, &fontFileReferenceKeySize );
            return std::span<const std::byte>( reinterpret_cast< const std::byte* >( fontFileReferenceKey ), fontFileReferenceKeySize );
        }

        /// <summary>
        /// Obtains the file loader associated with a font file object.
        /// </summary>
        /// <param name="fontFileLoader">
        /// A pointer to a variable that receives the file loader.
        /// </param>
        void GetLoader( IDWriteFontFileLoader** fontFileLoader ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetLoader( fontFileLoader );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Obtains the file loader associated with a font file object.
        /// </summary>
        /// <returns>
        /// The file loader associated with the font file object.
        /// </returns>
        FontFileLoader GetLoader( ) const
        {
            IDWriteFontFileLoader* fontFileLoader = nullptr;
            GetLoader( &fontFileLoader );
            FontFileLoader result( fontFileLoader );
            return result;
        }


        /// <summary>
        /// Analyzes a file and returns whether it represents a font, and whether the font type is supported by the font system.
        /// </summary>
        /// <param name="isSupportedFontType">
        /// `TRUE` if the font type is supported by the font system, `FALSE` otherwise.
        /// </param>
        /// <param name="fontFileType">
        /// The type of the font file. Note that even if `isSupportedFontType` is `FALSE`,
        /// the `fontFileType` value may be different from `DWRITE_FONT_FILE_TYPE_UNKNOWN`.
        /// </param>
        /// <param name="fontFaceType">
        /// The type of the font face that can be constructed from the font file.
        /// Note that even if `isSupportedFontType` is `FALSE`, the `fontFaceType` value may be different from
        /// `DWRITE_FONT_FACE_TYPE_UNKNOWN`.
        /// </param>
        /// <param name="numberOfFaces">
        /// Number of font faces contained in the font file.
        /// </param>
        void Analyze( _Out_ BOOL* isSupportedFontType, _Out_ DWRITE_FONT_FILE_TYPE* fontFileType, _Out_opt_ DWRITE_FONT_FACE_TYPE* fontFaceType, _Out_ UINT32* numberOfFaces ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Analyze( isSupportedFontType, fontFileType, fontFaceType, numberOfFaces );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }


        /// <summary>
        /// Analyzes a file and returns whether it represents a font, and whether the font type is supported by the font system.
        /// </summary>
        /// <param name="isSupportedFontType">
        /// `true` if the font type is supported by the font system, `false` otherwise.
        /// </param>
        /// <param name="fontFileType">
        /// The type of the font file. Note that even if `isSupportedFontType` is `false`,
        /// the `fontFileType` value may be different from `FontFileType::Unknown`.
        /// </param>
        /// <param name="fontFaceType">
        /// The type of the font face that can be constructed from the font file.
        /// Note that even if `isSupportedFontType` is `false`, the `fontFaceType` value may be different from
        /// `FontFaceType::Unknown`.
        /// </param>
        /// <param name="numberOfFaces">
        /// Number of font faces contained in the font file.
        /// </param>
        void Analyze( _Out_ bool* isSupportedFontType, _Out_ FontFileType* fontFileType, _Out_opt_ FontFaceType* fontFaceType, _Out_ UINT32* numberOfFaces ) const
        {
            BOOL isft = FALSE;
            Analyze( &isft, reinterpret_cast< DWRITE_FONT_FILE_TYPE* >( fontFileType ), reinterpret_cast< DWRITE_FONT_FACE_TYPE* >( fontFaceType ), numberOfFaces );
            *isSupportedFontType = isft != FALSE ? true : false;
        }

        /// <summary>
        /// Analyzes a file and returns whether it represents a font, and whether the font type is supported by the font system.
        /// </summary>
        /// <param name="isSupportedFontType">
        /// `TRUE` if the font type is supported by the font system, `FALSE` otherwise.
        /// </param>
        /// <param name="fontFileType">
        /// The type of the font file. Note that even if `isSupportedFontType` is `FALSE`,
        /// the `fontFileType` value may be different from `DWRITE_FONT_FILE_TYPE_UNKNOWN`.
        /// </param>
        /// <param name="fontFaceType">
        /// The type of the font face that can be constructed from the font file.
        /// Note that even if `isSupportedFontType` is `FALSE`, the `fontFaceType` value may be different from
        /// `DWRITE_FONT_FACE_TYPE_UNKNOWN`.
        /// </param>
        /// <param name="numberOfFaces">
        /// Number of font faces contained in the font file.
        /// </param>
        void Analyze( BOOL& isSupportedFontType, DWRITE_FONT_FILE_TYPE& fontFileType, DWRITE_FONT_FACE_TYPE& fontFaceType, UINT32& numberOfFaces ) const
        {
            Analyze( &isSupportedFontType, &fontFileType, &fontFaceType, &numberOfFaces );
        }

        /// <summary>
        /// Analyzes a file and returns whether it represents a font, and whether the font type is supported by the font system.
        /// </summary>
        /// <param name="isSupportedFontType">
        /// `true` if the font type is supported by the font system, `false` otherwise.
        /// </param>
        /// <param name="fontFileType">
        /// The type of the font file. Note that even if `isSupportedFontType` is `false`,
        /// the `fontFileType` value may be different from `FontFileType::Unknown`.
        /// </param>
        /// <param name="fontFaceType">
        /// The type of the font face that can be constructed from the font file.
        /// Note that even if `isSupportedFontType` is `false`, the `fontFaceType` value may be different from
        /// `FontFaceType::Unknown`.
        /// </param>
        /// <param name="numberOfFaces">
        /// Number of font faces contained in the font file.
        /// </param>
        void Analyze( bool& isSupportedFontType, FontFileType& fontFileType, FontFaceType& fontFaceType, UINT32& numberOfFaces ) const
        {
            Analyze( &isSupportedFontType, &fontFileType, &fontFaceType, &numberOfFaces );
        }

        /// <summary>
        /// Analyzes a file and returns whether it represents a font, and whether the font type is supported by the font system.
        /// </summary>
        /// <param name="isSupportedFontType">
        /// `TRUE` if the font type is supported by the font system, `FALSE` otherwise.
        /// </param>
        /// <param name="fontFileType">
        /// The type of the font file. Note that even if `isSupportedFontType` is `FALSE`,
        /// the `fontFileType` value may be different from `DWRITE_FONT_FILE_TYPE_UNKNOWN`.
        /// </param>
        /// <param name="numberOfFaces">
        /// Number of font faces contained in the font file.
        /// </param>
        void Analyze( BOOL& isSupportedFontType, DWRITE_FONT_FILE_TYPE& fontFileType, UINT32& numberOfFaces ) const
        {
            Analyze( &isSupportedFontType, &fontFileType, nullptr, &numberOfFaces );
        }

        /// <summary>
        /// Analyzes a file and returns whether it represents a font, and whether the font type is supported by the font system.
        /// </summary>
        /// <param name="isSupportedFontType">
        /// `true` if the font type is supported by the font system, `false` otherwise.
        /// </param>
        /// <param name="fontFileType">
        /// The type of the font file. Note that even if `isSupportedFontType` is `false`,
        /// the `fontFileType` value may be different from `FontFileType::Unknown`.
        /// </param>
        /// <param name="numberOfFaces">
        /// Number of font faces contained in the font file.
        /// </param>
        void Analyze( bool& isSupportedFontType, FontFileType& fontFileType, UINT32& numberOfFaces ) const
        {
            Analyze( &isSupportedFontType, &fontFileType, nullptr, &numberOfFaces );
        }


        struct AnalyzeResult
        {
            bool IsSupportedFontType; 
            FontFileType FontFileType; 
            FontFaceType FontFaceType; 
            UINT32 NumberOfFaces;
        };

        /// <summary>
        /// Analyzes a font file and returns comprehensive information about its format and content.
        /// </summary>
        /// <returns>
        /// An AnalyzeResult structure containing:
        /// - IsSupportedFontType: true if the font type is supported by the font system, false otherwise.
        /// - FontFileType: The type of the font file (e.g., TrueType, CFF, OpenTypeCollection).
        ///   Note: this value may be different from Unknown even if IsSupportedFontType is false.
        /// - FontFaceType: The type of the font face that can be constructed from the font file.
        ///   Note: this value may be different from Unknown even if IsSupportedFontType is false.
        /// - NumberOfFaces: The number of font faces contained in the font file.
        /// </returns>
        /// <remarks>
        /// This is a convenience overload that combines all output parameters from the multi-parameter
        /// Analyze overloads into a single return value. Use this method when you need all analysis results
        /// at once. Use the multi-parameter overloads if you only need specific information.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// FontFile fontFile = factory.CreateFontFileReference( L"C:\\Fonts\\Arial.ttf" );
        /// auto result = fontFile.Analyze();
        /// 
        /// if ( result.IsSupportedFontType )
        /// {
        ///     // Process font
        ///     int faceCount = result.NumberOfFaces;
        ///     FontFileType fileType = result.FontFileType;
        /// }
        /// </code>
        /// </example>
        AnalyzeResult Analyze( ) const
        {
            AnalyzeResult result{};
            Analyze( result.IsSupportedFontType, result.FontFileType, result.FontFaceType, result.NumberOfFaces );
            return result;
        }



    };

    /// <summary>
    /// Represents the internal structure of a device pixel (i.e., the physical arrangement of red,
    /// green, and blue color components) that is assumed for purposes of rendering text.
    /// </summary>
    enum class PixelGeometry : int
    {
        /// <summary>
        /// The red, green, and blue color components of each pixel are assumed to occupy the same point.
        /// </summary>
        Flat = DWRITE_PIXEL_GEOMETRY_FLAT,

        /// <summary>
        /// Each pixel comprises three vertical stripes, with red on the left, green in the center, and 
        /// blue on the right. This is the most common pixel geometry for LCD monitors.
        /// </summary>
        RGB = DWRITE_PIXEL_GEOMETRY_RGB,

        /// <summary>
        /// Each pixel comprises three vertical stripes, with blue on the left, green in the center, and 
        /// red on the right.
        /// </summary>
        BGR = DWRITE_PIXEL_GEOMETRY_BGR
    };


    /// <summary>
    /// Represents a method of rendering glyphs.
    /// </summary>
    enum class RenderingMode : int
    {
        /// <summary>
        /// Specifies that the rendering mode is determined automatically based on the font and size.
        /// </summary>
        Default = DWRITE_RENDERING_MODE_DEFAULT,

        /// <summary>
        /// Specifies that no antialiasing is performed. Each pixel is either set to the foreground 
        /// color of the text or retains the color of the background.
        /// </summary>
        Aliased = DWRITE_RENDERING_MODE_ALIASED,

        /// <summary>
        /// Specifies that antialiasing is performed in the horizontal direction and the appearance
        /// of glyphs is layout-compatible with GDI using CLEARTYPE_QUALITY. Use DWRITE_MEASURING_MODE_GDI_CLASSIC 
        /// to get glyph advances. The antialiasing may be either ClearType or grayscale depending on
        /// the text antialiasing mode.
        /// </summary>
        GDIClassic = DWRITE_RENDERING_MODE_GDI_CLASSIC,

        /// <summary>
        /// Specifies that antialiasing is performed in the horizontal direction and the appearance
        /// of glyphs is layout-compatible with GDI using CLEARTYPE_NATURAL_QUALITY. Glyph advances
        /// are close to the font design advances, but are still rounded to whole pixels. Use
        /// DWRITE_MEASURING_MODE_GDI_NATURAL to get glyph advances. The antialiasing may be either
        /// ClearType or grayscale depending on the text antialiasing mode.
        /// </summary>
        GDINatural = DWRITE_RENDERING_MODE_GDI_NATURAL,

        /// <summary>
        /// Specifies that antialiasing is performed in the horizontal direction. This rendering
        /// mode allows glyphs to be positioned with subpixel precision and is therefore suitable
        /// for natural (i.e., resolution-independent) layout. The antialiasing may be either
        /// ClearType or grayscale depending on the text antialiasing mode.
        /// </summary>
        Natural = DWRITE_RENDERING_MODE_NATURAL,

        /// <summary>
        /// Similar to natural mode except that antialiasing is performed in both the horizontal
        /// and vertical directions. This is typically used at larger sizes to make curves and
        /// diagonal lines look smoother. The antialiasing may be either ClearType or grayscale
        /// depending on the text antialiasing mode.
        /// </summary>
        NaturalSymmetric = DWRITE_RENDERING_MODE_NATURAL_SYMMETRIC,

        /// <summary>
        /// Specifies that rendering should bypass the rasterizer and use the outlines directly. 
        /// This is typically used at very large sizes.
        /// </summary>
        Outline = DWRITE_RENDERING_MODE_OUTLINE,

        // The following names are obsolete, but are kept as aliases to avoid breaking existing code.
        // Each of these rendering modes may result in either ClearType or grayscale antialiasing 
        // depending on the DWRITE_TEXT_ANTIALIASING_MODE.
        ClearTypeGDIClassic = DWRITE_RENDERING_MODE_CLEARTYPE_GDI_CLASSIC,
        ClearTypeGDINatural = DWRITE_RENDERING_MODE_CLEARTYPE_GDI_NATURAL,
        ClearTypeNatural = DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL,
        ClearTypeNaturalSymmetric = DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL_SYMMETRIC
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

        /// <summary>
        /// Gets the gamma value used for gamma correction. Valid values must be
        /// greater than zero and cannot exceed 256.
        /// </summary>
        FLOAT GetGamma( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            FLOAT gamma = pInterface->GetGamma( );
            return gamma;
        }

        /// <summary>
        /// Gets the amount of contrast enhancement. Valid values are greater than
        /// or equal to zero.
        /// </summary>
        FLOAT GetEnhancedContrast( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            FLOAT enhancedContrast = pInterface->GetEnhancedContrast( );
            return enhancedContrast;
        }

        /// <summary>
        /// Gets the ClearType level. Valid values range from 0.0f (no ClearType) 
        /// to 1.0f (full ClearType).
        /// </summary>
        FLOAT GetClearTypeLevel( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            FLOAT clearTypeLevel = pInterface->GetClearTypeLevel( );
            return clearTypeLevel;
        }

        /// <summary>
        /// Gets the pixel geometry.
        /// </summary>
        PixelGeometry GetPixelGeometry( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            DWRITE_PIXEL_GEOMETRY pixelGeometry = pInterface->GetPixelGeometry( );
            return static_cast< PixelGeometry >( pixelGeometry ); 
        }

        /// <summary>
        /// Gets the rendering mode.
        /// </summary>
        RenderingMode GetRenderingMode( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            DWRITE_RENDERING_MODE renderingMode = pInterface->GetRenderingMode( );
            return static_cast< RenderingMode >( renderingMode );
        }
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

        /// <summary>
        /// Obtains the file format type of a font face.
        /// </summary>
        FontFaceType GetType( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return static_cast< FontFaceType >( pInterface->GetType( ) );
        }

        /// <summary>
        /// Obtains the font files representing a font face.
        /// </summary>
        /// <param name="numberOfFiles">
        /// The number of files representing the font face.
        /// </param>
        /// <param name="fontFiles">
        /// User provided array that stores pointers to font files representing the font face.
        /// This parameter can be NULL if the user is only interested in the number of files representing the font face.
        /// This API increments reference count of the font file pointers returned according to COM conventions, and the client
        /// should release them when finished.
        /// </param>
        void GetFiles( _Inout_ UINT32* numberOfFiles, IDWriteFontFile** fontFiles ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFiles( numberOfFiles, fontFiles );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Obtains the number of font files representing a font face.
        /// </summary>
        /// <returns>
        /// The number of font files representing the font face.
        /// </returns>
        UINT32 GetNumberOfFiles( ) const
        {
            UINT32 result;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFiles( &result, nullptr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        /// <summary>
        /// Obtains the font files representing a font face.
        /// </summary>
        /// <returns>
        /// A vector of FontFile objects representing the font face.
        /// </returns>
        std::vector<FontFile> GetFiles( ) const
        {
            UINT32 numberOfFiles = GetNumberOfFiles( );
            std::vector<FontFile> result;
            result.resize( numberOfFiles );
            IDWriteFontFile** fontFiles = reinterpret_cast< IDWriteFontFile** >( result.data() );

            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFiles( &numberOfFiles, fontFiles );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        /// <summary>
        /// Obtains the zero-based index of the font face in its font file or files. If the font files contain a single face,
        /// the return value is zero.
        /// </summary>
        /// <returns>
        /// The zero-based index of the font face in its font file or files.
        /// </returns>
        UINT32 GetIndex( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetIndex( );
        }

        /// <summary>
        /// Obtains the algorithmic style simulation flags of a font face.
        /// </summary>
        /// <returns>
        /// The algorithmic style simulation flags of the font face.
        /// </returns>
        FontSimulation GetSimulations( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return static_cast< FontSimulation >( pInterface->GetSimulations( ) );
        }


        /// <summary>
        /// Determines whether the font is a symbol font.
        /// </summary>
        /// <returns>
        /// true if the font is a symbol font; otherwise, false.
        /// </returns>
        bool IsSymbolFont( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsSymbolFont( );
        }


        /// <summary>
        /// Obtains design units and common metrics for the font face.
        /// These metrics are applicable to all the glyphs within a fontface and are used by applications for layout calculations.
        /// </summary>
        /// <param name="fontFaceMetrics">
        /// Points to a DWRITE_FONT_METRICS structure to fill in.
        /// The metrics returned by this function are in font design units.
        /// </param>
        void GetMetrics( DWRITE_FONT_METRICS* fontFaceMetrics ) const
        {
            CheckPointerNotNull( fontFaceMetrics );
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetMetrics( fontFaceMetrics );
        }

        /// <summary>
        /// Obtains design units and common metrics for the font face.
        /// These metrics are applicable to all the glyphs within a fontface and are used by applications for layout calculations.
        /// </summary>
        /// <param name="fontFaceMetrics">
        /// Reference to a DWRITE_FONT_METRICS structure to fill in.
        /// The metrics returned by this function are in font design units.
        /// </param>
        void GetMetrics( DWRITE_FONT_METRICS& fontFaceMetrics ) const
        {
            GetMetrics( &fontFaceMetrics );
        }

        /// <summary>
        /// Obtains design units and common metrics for the font face.
        /// These metrics are applicable to all the glyphs within a fontface and are used by applications for layout calculations.
        /// </summary>
        /// <returns>
        /// A FontMetrics structure containing the design units and common metrics for the font face.
        /// </returns>
        FontMetrics GetMetrics( ) const
        {
            FontMetrics result;
            GetMetrics( &result );
            return result;
        }

        /// <summary>
        /// Obtains the number of glyphs in the font face.
        /// </summary>
        /// <returns>
        /// The number of glyphs in the font face.
        /// </returns>
        UINT16 GetGlyphCount( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetGlyphCount( );
        }

        /// <summary>
        /// Obtains ideal glyph metrics in font design units. Design glyphs metrics are used for glyph positioning.
        /// </summary>
        /// <param name="glyphIndices">
        /// An array of glyph indices to compute the metrics for.
        /// </param>
        /// <param name="glyphCount">
        /// The number of elements in the glyphIndices array.
        /// </param>
        /// <param name="glyphMetrics">
        /// Array of DWRITE_GLYPH_METRICS structures filled by this function.
        /// The metrics returned by this function are in font design units.
        /// </param>
        /// <param name="isSideways">
        /// Indicates whether the font is being used in a sideways run.
        /// This can affect the glyph metrics if the font has oblique simulation
        /// because sideways oblique simulation differs from non-sideways oblique simulation.
        /// </param>
        void GetDesignGlyphMetrics( UINT16 const* glyphIndices, UINT32 glyphCount, DWRITE_GLYPH_METRICS* glyphMetrics, BOOL isSideways ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDesignGlyphMetrics( glyphIndices, glyphCount, glyphMetrics, isSideways );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Obtains ideal glyph metrics in font design units for a span of glyph indices. Design glyph metrics are used for glyph positioning.
        /// </summary>
        /// <typeparam name="SpanT">
        /// A span-like type containing glyph indices.
        /// </typeparam>
        /// <param name="glyphIndices">
        /// A span of glyph indices to compute the metrics for.
        /// </param>
        /// <param name="isSideways">
        /// Indicates whether the font is being used in a sideways run.
        /// </param>
        /// <returns>
        /// A vector of GlyphMetrics structures containing the metrics for each glyph.
        /// </returns>
        template<SpanLike SpanT>
            requires std::is_same_v<typename SpanT::value_type, UINT16> || std::is_same_v<typename SpanT::value_type, const UINT16>
        std::vector<GlyphMetrics> GetDesignGlyphMetrics( const SpanT& glyphIndices, bool isSideways = false ) const
        {
            UINT32 glyphCount = static_cast<UINT32>(glyphIndices.size());
            std::vector<GlyphMetrics> glyphMetrics( glyphCount );
            GetDesignGlyphMetrics( glyphIndices.data(), glyphCount, glyphMetrics.data(), isSideways ? TRUE : FALSE );
            return glyphMetrics;
        }



        /// <summary>
        /// Returns the nominal mapping of UTF-32 Unicode code points to glyph indices as defined by the font 'cmap' table.
        /// Note that this mapping is primarily provided for line layout engines built on top of the physical font API.
        /// Because of OpenType glyph substitution and line layout character substitution, the nominal conversion does not always correspond
        /// to how a Unicode string will map to glyph indices when rendering using a particular font face.
        /// Also, note that Unicode Variation Selectors provide for alternate mappings for character to glyph.
        /// This call will always return the default variant.
        /// </summary>
        /// <param name="codePoints">
        /// An array of UTF-32 code points to obtain nominal glyph indices from.
        /// </param>
        /// <param name="codePointCount">
        /// The number of elements in the codePoints array.
        /// </param>
        /// <param name="glyphIndices">
        /// Array of nominal glyph indices filled by this function.
        /// </param>
        void GetGlyphIndices( UINT32 const* codePoints, UINT32 codePointCount, UINT16* glyphIndices ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetGlyphIndices( codePoints, codePointCount, glyphIndices );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Finds the specified OpenType font table if it exists and returns a pointer to it.
        /// The function accesses the underlying font data via the IDWriteFontFileStream interface
        /// implemented by the font file loader.
        /// </summary>
        /// <param name="openTypeTableTag">
        /// Four character tag of table to find.
        /// Use the DWRITE_MAKE_OPENTYPE_TAG() macro to create it.
        /// Unlike GDI, it does not support the special TTCF and null tags to access the whole font.
        /// </param>
        /// <param name="tableData">
        /// Pointer to base of table in memory.
        /// The pointer is only valid so long as the FontFace used to get the font table still exists
        /// (not any other FontFace, even if it actually refers to the same physical font).
        /// </param>
        /// <param name="tableSize">
        /// Byte size of table.
        /// </param>
        /// <param name="tableContext">
        /// Opaque context which must be freed by calling ReleaseFontTable.
        /// The context actually comes from the lower level IDWriteFontFileStream,
        /// which may be implemented by the application or DWrite itself.
        /// It is possible for a NULL tableContext to be returned, especially if
        /// the implementation directly memory maps the whole file.
        /// Nevertheless, always release it later, and do not use it as a test for function success.
        /// The same table can be queried multiple times,
        /// but each returned context can be different, so release each separately.
        /// </param>
        /// <param name="exists">
        /// True if table exists.
        /// </param>
        /// <returns>
        /// Standard HRESULT error code.
        /// If a table can not be found, the function will not return an error, but the size will be 0, table NULL, and exists = FALSE.
        /// The context does not need to be freed if the table was not found.
        /// </returns>
        /// <remarks>
        /// The context for the same tag may be different for each call,
        /// so each one must be held and released separately.
        /// </remarks>
        void TryGetFontTable( UINT32 openTypeTableTag, const void** tableData, UINT32* tableSize, void** tableContext, BOOL* exists ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->TryGetFontTable( openTypeTableTag, tableData, tableSize, tableContext, exists );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Releases the table obtained earlier from TryGetFontTable.
        /// </summary>
        /// <param name="tableContext">Opaque context from TryGetFontTable.</param>
        void ReleaseFontTable( void* tableContext ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ReleaseFontTable( tableContext );
        }

        /// <summary>
        /// A moveable, RAII wrapper for OpenType font table data.
        /// Automatically manages TryGetFontTable and ReleaseFontTable lifecycle.
        /// </summary>
        class FontTable
        {
            const FontFace* fontFace_;
            const void* tableData_;
            UINT32 tableSize_;
            void* tableContext_;
            BOOL exists_;
        public:
            /// <summary>
            /// Constructs an empty FontTable.
            /// </summary>
            FontTable( ) noexcept
                : fontFace_( nullptr ), tableData_( nullptr ),
                tableSize_( 0 ), tableContext_( nullptr ), exists_( FALSE )
            {}

            /// <summary>
            /// Constructs a FontTable by reading a font table from the font face.
            /// </summary>
            /// <param name="fontFace">The FontFace to read from.</param>
            /// <param name="openTypeTableTag">Four character tag of table to find. Use DWRITE_MAKE_OPENTYPE_TAG() to create it.</param>
            FontTable( const FontFace& fontFace, UINT32 openTypeTableTag )
                : fontFace_( &fontFace ), tableData_( nullptr ),
                tableSize_( 0 ), tableContext_( nullptr ), exists_( FALSE )
            {
                fontFace_->TryGetFontTable( openTypeTableTag, &tableData_, &tableSize_, &tableContext_, &exists_ );
            }

            /// <summary>
            /// Move constructor.
            /// </summary>
            FontTable( FontTable&& other ) noexcept
                : fontFace_( other.fontFace_ ), tableData_( other.tableData_ ),
                tableSize_( other.tableSize_ ), tableContext_( other.tableContext_ ),
                exists_( other.exists_ )
            {
                other.fontFace_ = nullptr;
                other.tableData_ = nullptr;
                other.tableSize_ = 0;
                other.tableContext_ = nullptr;
                other.exists_ = FALSE;
            }

            /// <summary>
            /// Move assignment operator.
            /// </summary>
            FontTable& operator=( FontTable&& other ) noexcept
            {
                if ( this != &other )
                {
                    Release( );
                    fontFace_ = other.fontFace_;
                    tableData_ = other.tableData_;
                    tableSize_ = other.tableSize_;
                    tableContext_ = other.tableContext_;
                    exists_ = other.exists_;

                    other.fontFace_ = nullptr;
                    other.tableData_ = nullptr;
                    other.tableSize_ = 0;
                    other.tableContext_ = nullptr;
                    other.exists_ = FALSE;
                }
                return *this;
            }

            /// <summary>
            /// Destructor. Releases the table if it was successfully acquired.
            /// </summary>
            ~FontTable( ) noexcept
            {
                Release( );
            }

            // Deleted copy operations
            FontTable( const FontTable& ) = delete;
            FontTable& operator=( const FontTable& ) = delete;

            /// <summary>
            /// Returns whether the table exists in the font face.
            /// </summary>
            /// <returns>True if the table exists and was successfully retrieved; otherwise, false.</returns>
            bool Exists( ) const noexcept
            {
                return exists_ != FALSE;
            }

            /// <summary>
            /// Returns a pointer to the table data.
            /// </summary>
            /// <returns>Pointer to the table data, or nullptr if table does not exist.</returns>
            const void* data( ) const noexcept
            {
                return tableData_;
            }

            /// <summary>
            /// Returns the size of the table in bytes.
            /// </summary>
            /// <returns>Size of the table in bytes, or 0 if table does not exist.</returns>
            UINT32 size( ) const noexcept
            {
                return tableSize_;
            }

            /// <summary>
            /// Returns whether the table data is empty (does not exist or has zero size).
            /// </summary>
            /// <returns>True if the table is empty; otherwise, false.</returns>
            bool Empty( ) const noexcept
            {
                return tableData_ == nullptr || tableSize_ == 0;
            }

            /// <summary>
            /// Returns a span view of the table data as bytes.
            /// </summary>
            /// <returns>A span of bytes covering the table.</returns>
            std::span<const std::byte> AsSpan( ) const noexcept
            {
                return std::span<const std::byte>(
                    static_cast< const std::byte* >( tableData_ ), tableSize_ );
            }

            /// <summary>
            /// Returns a span view of the table data as a specific type.
            /// </summary>
            /// <typeparam name="T">The element type for the span.</typeparam>
            /// <returns>A span of T covering the table (if size is compatible).</returns>
            /// <remarks>
            /// The number of elements in the returned span is calculated as tableSize_ / sizeof(T).
            /// Ensure the table size is a multiple of sizeof(T) for meaningful results.
            /// </remarks>
            template<typename T>
            std::span<const T> AsSpan( ) const noexcept
            {
                return std::span<const T>(
                    static_cast< const T* >( tableData_ ),
                    tableSize_ / sizeof( T ) );
            }

        private:
            /// <summary>
            /// Releases the held table if valid.
            /// </summary>
            void Release( ) noexcept
            {
                if ( fontFace_ && tableContext_ )
                {
                    fontFace_->ReleaseFontTable( tableContext_ );
                }
            }
        };

        /// <summary>
        /// Retrieves an OpenType font table.
        /// </summary>
        /// <param name="openTypeTableTag">Four character tag of table to find. Use DWRITE_MAKE_OPENTYPE_TAG() to create it.</param>
        /// <returns>A FontTable object representing the retrieved table.</returns>
        FontTable GetFontTable( UINT32 openTypeTableTag ) const
        {
            return FontTable( *this, openTypeTableTag );
        }


        void GetGlyphRunOutline( FLOAT emSize, UINT16 const* glyphIndices, FLOAT const* glyphAdvances, DWRITE_GLYPH_OFFSET const* glyphOffsets, UINT32 glyphCount, BOOL isSideways, BOOL isRightToLeft, IDWriteGeometrySink* geometrySink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetGlyphRunOutline( emSize, glyphIndices, glyphAdvances, glyphOffsets, glyphCount, isSideways, isRightToLeft, geometrySink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetRecommendedRenderingMode( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MEASURING_MODE measuringMode, IDWriteRenderingParams* renderingParams, DWRITE_RENDERING_MODE* renderingMode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetRecommendedRenderingMode( emSize, pixelsPerDip, measuringMode, renderingParams, renderingMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        DWRITE_RENDERING_MODE GetRecommendedRenderingMode( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MEASURING_MODE measuringMode, IDWriteRenderingParams* renderingParams ) const
        {
            DWRITE_RENDERING_MODE result = DWRITE_RENDERING_MODE( 0 );
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetRecommendedRenderingMode( emSize, pixelsPerDip, measuringMode, renderingParams, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        void GetGdiCompatibleMetrics( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_FONT_METRICS* fontFaceMetrics ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetGdiCompatibleMetrics( emSize, pixelsPerDip, transform, fontFaceMetrics );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetGdiCompatibleGlyphMetrics( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural, UINT16 const* glyphIndices, UINT32 glyphCount, DWRITE_GLYPH_METRICS* glyphMetrics, BOOL isSideways ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetGdiCompatibleGlyphMetrics( emSize, pixelsPerDip, transform, useGdiNatural, glyphIndices, glyphCount, glyphMetrics, isSideways );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
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
