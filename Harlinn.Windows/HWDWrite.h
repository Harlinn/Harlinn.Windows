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


    /// <summary>
    /// Direction for how reading progresses.
    /// </summary>
    enum class ReadingDirection
    {
        /// <summary>
        /// Reading progresses from left to right.
        /// </summary>
        LeftToRight = DWRITE_READING_DIRECTION_LEFT_TO_RIGHT,

        /// <summary>
        /// Reading progresses from right to left.
        /// </summary>
        RightToLeft = DWRITE_READING_DIRECTION_RIGHT_TO_LEFT,

        /// <summary>
        /// Reading progresses from top to bottom.
        /// </summary>
        TopToBottom = DWRITE_READING_DIRECTION_TOP_TO_BOTTOM,

        /// <summary>
        /// Reading progresses from bottom to top.
        /// </summary>
        BottomToTop = DWRITE_READING_DIRECTION_BOTTOM_TO_TOP,
    };

    /// <summary>
    /// Direction for how lines of text are placed relative to one another.
    /// </summary>
    enum class FlowDirection
    {
        /// <summary>
        /// Text lines are placed from top to bottom.
        /// </summary>
        TopToBottom = DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM,

        /// <summary>
        /// Text lines are placed from bottom to top.
        /// </summary>
        BottomToTop = DWRITE_FLOW_DIRECTION_BOTTOM_TO_TOP,

        /// <summary>
        /// Text lines are placed from left to right.
        /// </summary>
        LeftToRight = DWRITE_FLOW_DIRECTION_LEFT_TO_RIGHT,

        /// <summary>
        /// Text lines are placed from right to left.
        /// </summary>
        RightToLeft = DWRITE_FLOW_DIRECTION_RIGHT_TO_LEFT,
    };

    /// <summary>
    /// Alignment of paragraph text along the reading direction axis relative to 
    /// the leading and trailing edge of the layout box.
    /// </summary>
    enum class TextAlignment
    {
        /// <summary>
        /// The leading edge of the paragraph text is aligned to the layout box's leading edge.
        /// </summary>
        Leading = DWRITE_TEXT_ALIGNMENT_LEADING,

        /// <summary>
        /// The trailing edge of the paragraph text is aligned to the layout box's trailing edge.
        /// </summary>
        Trailing = DWRITE_TEXT_ALIGNMENT_TRAILING,

        /// <summary>
        /// The center of the paragraph text is aligned to the center of the layout box.
        /// </summary>
        Center = DWRITE_TEXT_ALIGNMENT_CENTER,

        /// <summary>
        /// Align text to the leading side, and also justify text to fill the lines.
        /// </summary>
        Justified = DWRITE_TEXT_ALIGNMENT_JUSTIFIED
    };

    /// <summary>
    /// Alignment of paragraph text along the flow direction axis relative to the
    /// flow's beginning and ending edge of the layout box.
    /// </summary>
    enum class ParagraphAlignment
    {
        /// <summary>
        /// The first line of paragraph is aligned to the flow's beginning edge of the layout box.
        /// </summary>
        Near = DWRITE_PARAGRAPH_ALIGNMENT_NEAR,

        /// <summary>
        /// The last line of paragraph is aligned to the flow's ending edge of the layout box.
        /// </summary>
        Far = DWRITE_PARAGRAPH_ALIGNMENT_FAR,

        /// <summary>
        /// The center of the paragraph is aligned to the center of the flow of the layout box.
        /// </summary>
        Center = DWRITE_PARAGRAPH_ALIGNMENT_CENTER
    };

    /// <summary>
    /// Word wrapping in multiline paragraph.
    /// </summary>
    enum class WordWrapping
    {
        /// <summary>
        /// Words are broken across lines to avoid text overflowing the layout box.
        /// </summary>
        Wrap = DWRITE_WORD_WRAPPING_WRAP,

        /// <summary>
        /// Words are kept within the same line even when it overflows the layout box.
        /// This option is often used with scrolling to reveal overflow text. 
        /// </summary>
        NoWrap = DWRITE_WORD_WRAPPING_NO_WRAP,

        /// <summary>
        /// Words are broken across lines to avoid text overflowing the layout box.
        /// Emergency wrapping occurs if the word is larger than the maximum width.
        /// </summary>
        EmergencyBreak = DWRITE_WORD_WRAPPING_EMERGENCY_BREAK,

        /// <summary>
        /// Only wrap whole words, never breaking words (emergency wrapping) when the
        /// layout width is too small for even a single word.
        /// </summary>
        WholeWord = DWRITE_WORD_WRAPPING_WHOLE_WORD,

        /// <summary>
        /// Wrap between any valid characters clusters.
        /// </summary>
        Character = DWRITE_WORD_WRAPPING_CHARACTER,
    };

    /// <summary>
    /// The method used for line spacing in layout.
    /// </summary>
    enum class LineSpacingMethod
    {
        /// <summary>
        /// Line spacing depends solely on the content, growing to accommodate the size of fonts and inline objects.
        /// </summary>
        Default = DWRITE_LINE_SPACING_METHOD_DEFAULT,

        /// <summary>
        /// Lines are explicitly set to uniform spacing, regardless of contained font sizes.
        /// This can be useful to avoid the uneven appearance that can occur from font fallback.
        /// </summary>
        Uniform = DWRITE_LINE_SPACING_METHOD_UNIFORM,

        /// <summary>
        /// Line spacing and baseline distances are proportional to the computed values based on the content, the size of the fonts and inline objects.
        /// </summary>
        Proportional = DWRITE_LINE_SPACING_METHOD_PROPORTIONAL
    };

    struct LineSpacingData
    {
        LineSpacingMethod lineSpacingMethod = LineSpacingMethod::Default;
        FLOAT lineSpacing = 0.0f;
        FLOAT baseline = 0.0f;
    };

    /// <summary>
    /// Text granularity used to trim text overflowing the layout box.
    /// </summary>
    enum class TrimmingGranularity
    {
        /// <summary>
        /// No trimming occurs. Text flows beyond the layout width.
        /// </summary>
        None = DWRITE_TRIMMING_GRANULARITY_NONE,

        /// <summary>
        /// Trimming occurs at character cluster boundary.
        /// </summary>
        Character = DWRITE_TRIMMING_GRANULARITY_CHARACTER,

        /// <summary>
        /// Trimming occurs at word boundary.
        /// </summary>
        Word = DWRITE_TRIMMING_GRANULARITY_WORD
    };

    /// <summary>
    /// Typographic feature of text supplied by the font.
    /// </summary>
    /// <remarks>
    /// Use DWRITE_MAKE_FONT_FEATURE_TAG() to create a custom one.
    /// <remarks>
    enum class FontFeatureTag
    {
        AlternativeFractions = DWRITE_FONT_FEATURE_TAG_ALTERNATIVE_FRACTIONS,
        PetiteCapitalsFromCapitals = DWRITE_FONT_FEATURE_TAG_PETITE_CAPITALS_FROM_CAPITALS,
        SmallCapitalsFromCapitals = DWRITE_FONT_FEATURE_TAG_SMALL_CAPITALS_FROM_CAPITALS,
        ContextualAlternates = DWRITE_FONT_FEATURE_TAG_CONTEXTUAL_ALTERNATES,
        CaseSensitiveForms = DWRITE_FONT_FEATURE_TAG_CASE_SENSITIVE_FORMS,
        GlyphCompositionDecomposition = DWRITE_FONT_FEATURE_TAG_GLYPH_COMPOSITION_DECOMPOSITION,
        ContextualLigatures = DWRITE_FONT_FEATURE_TAG_CONTEXTUAL_LIGATURES,
        CapitalSpacing = DWRITE_FONT_FEATURE_TAG_CAPITAL_SPACING,
        ContextualSwash = DWRITE_FONT_FEATURE_TAG_CONTEXTUAL_SWASH,
        CursivePositioning = DWRITE_FONT_FEATURE_TAG_CURSIVE_POSITIONING,
        Default = DWRITE_FONT_FEATURE_TAG_DEFAULT,
        DiscretionaryLigatures = DWRITE_FONT_FEATURE_TAG_DISCRETIONARY_LIGATURES,
        ExpertForms = DWRITE_FONT_FEATURE_TAG_EXPERT_FORMS,
        Fractions = DWRITE_FONT_FEATURE_TAG_FRACTIONS,
        FullWidth = DWRITE_FONT_FEATURE_TAG_FULL_WIDTH,
        HalfForms = DWRITE_FONT_FEATURE_TAG_HALF_FORMS,
        HalantForms = DWRITE_FONT_FEATURE_TAG_HALANT_FORMS,
        AlternateHalfWidth = DWRITE_FONT_FEATURE_TAG_ALTERNATE_HALF_WIDTH,
        HistoricalForms = DWRITE_FONT_FEATURE_TAG_HISTORICAL_FORMS,
        HorizontalKanaAlternates = DWRITE_FONT_FEATURE_TAG_HORIZONTAL_KANA_ALTERNATES,
        HistoricalLigatures = DWRITE_FONT_FEATURE_TAG_HISTORICAL_LIGATURES,
        HalfWidth = DWRITE_FONT_FEATURE_TAG_HALF_WIDTH,
        HojoKanjiForms = DWRITE_FONT_FEATURE_TAG_HOJO_KANJI_FORMS,
        JIS04Forms = DWRITE_FONT_FEATURE_TAG_JIS04_FORMS,
        JIS78Forms = DWRITE_FONT_FEATURE_TAG_JIS78_FORMS,
        JIS83Forms = DWRITE_FONT_FEATURE_TAG_JIS83_FORMS,
        JIS90Forms = DWRITE_FONT_FEATURE_TAG_JIS90_FORMS,
        Kerning = DWRITE_FONT_FEATURE_TAG_KERNING,
        StandardLigatures = DWRITE_FONT_FEATURE_TAG_STANDARD_LIGATURES,
        LiningFigures = DWRITE_FONT_FEATURE_TAG_LINING_FIGURES,
        LocalizedForms = DWRITE_FONT_FEATURE_TAG_LOCALIZED_FORMS,
        MarkPositioning = DWRITE_FONT_FEATURE_TAG_MARK_POSITIONING,
        MathematicalGreek = DWRITE_FONT_FEATURE_TAG_MATHEMATICAL_GREEK,
        MarkToMarkPositioning = DWRITE_FONT_FEATURE_TAG_MARK_TO_MARK_POSITIONING,
        AlternateAnnotationForms = DWRITE_FONT_FEATURE_TAG_ALTERNATE_ANNOTATION_FORMS,
        NLCKanjiForms = DWRITE_FONT_FEATURE_TAG_NLC_KANJI_FORMS,
        OldStyleFigures = DWRITE_FONT_FEATURE_TAG_OLD_STYLE_FIGURES,
        Ordinals = DWRITE_FONT_FEATURE_TAG_ORDINALS,
        ProportionalAlternateWidth = DWRITE_FONT_FEATURE_TAG_PROPORTIONAL_ALTERNATE_WIDTH,
        PetiteCapitals = DWRITE_FONT_FEATURE_TAG_PETITE_CAPITALS,
        ProportionalFigures = DWRITE_FONT_FEATURE_TAG_PROPORTIONAL_FIGURES,
        ProportionalWidths = DWRITE_FONT_FEATURE_TAG_PROPORTIONAL_WIDTHS,
        QuarterWidths = DWRITE_FONT_FEATURE_TAG_QUARTER_WIDTHS,
        RequiredLigatures = DWRITE_FONT_FEATURE_TAG_REQUIRED_LIGATURES,
        RubyNotationForms = DWRITE_FONT_FEATURE_TAG_RUBY_NOTATION_FORMS,
        StylisticAlternates = DWRITE_FONT_FEATURE_TAG_STYLISTIC_ALTERNATES,
        ScientificInferiors = DWRITE_FONT_FEATURE_TAG_SCIENTIFIC_INFERIORS,
        SmallCapitals = DWRITE_FONT_FEATURE_TAG_SMALL_CAPITALS,
        SimplifiedForms = DWRITE_FONT_FEATURE_TAG_SIMPLIFIED_FORMS,
        StylisticSet1 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_1,
        StylisticSet2 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_2,
        StylisticSet3 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_3,
        StylisticSet4 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_4,
        StylisticSet5 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_5,
        StylisticSet6 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_6,
        StylisticSet7 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_7,
        StylisticSet8 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_8,
        StylisticSet9 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_9,
        StylisticSet10 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_10,
        StylisticSet11 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_11,
        StylisticSet12 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_12,
        StylisticSet13 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_13,
        StylisticSet14 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_14,
        StylisticSet15 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_15,
        StylisticSet16 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_16,
        StylisticSet17 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_17,
        StylisticSet18 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_18,
        StylisticSet19 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_19,
        StylisticSet20 = DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_20,
        Subscript = DWRITE_FONT_FEATURE_TAG_SUBSCRIPT,
        Superscript = DWRITE_FONT_FEATURE_TAG_SUPERSCRIPT,
        Swash = DWRITE_FONT_FEATURE_TAG_SWASH,
        Titling = DWRITE_FONT_FEATURE_TAG_TITLING,
        TraditionalNameForms = DWRITE_FONT_FEATURE_TAG_TRADITIONAL_NAME_FORMS,
        TabularFigures = DWRITE_FONT_FEATURE_TAG_TABULAR_FIGURES,
        TraditionalForms = DWRITE_FONT_FEATURE_TAG_TRADITIONAL_FORMS,
        ThirdWidths = DWRITE_FONT_FEATURE_TAG_THIRD_WIDTHS,
        Unicase = DWRITE_FONT_FEATURE_TAG_UNICASE,
        VerticalWriting = DWRITE_FONT_FEATURE_TAG_VERTICAL_WRITING,
        VerticalAlternatesAndRotation = DWRITE_FONT_FEATURE_TAG_VERTICAL_ALTERNATES_AND_ROTATION,
        SlashedZero = DWRITE_FONT_FEATURE_TAG_SLASHED_ZERO,
    };

    /// <summary>
    /// The TextRange structure specifies a range of text positions where format is applied.
    /// </summary>
    struct TextRange : public DWRITE_TEXT_RANGE
    {
        using Base = DWRITE_TEXT_RANGE;
        TextRange( ) : Base{}
        {}
    };

    /// <summary>
    /// The DWRITE_FONT_FEATURE structure specifies properties used to identify and execute typographic feature in the font.
    /// </summary>
    struct FontFeature : public DWRITE_FONT_FEATURE
    {
        using Base = DWRITE_FONT_FEATURE;
        FontFeature( ) : Base{}
        {}
    };

    /// <summary>
    /// Defines a set of typographic features to be applied during shaping.
    /// Notice the character range which this feature list spans is specified
    /// as a separate parameter to GetGlyphs.
    /// </summary>
    struct TypographicFeatures : public DWRITE_TYPOGRAPHIC_FEATURES
    {
        using Base = DWRITE_TYPOGRAPHIC_FEATURES;
        TypographicFeatures( ) : Base{}
        {}
    };

    /// <summary>
    /// The Trimming structure specifies the trimming option for text overflowing the layout box.
    /// </summary>
    struct Trimming : public DWRITE_TRIMMING
    {
        using Base = DWRITE_TRIMMING;
        Trimming( ) : Base{}
        {}
    };


    /// <summary>
    /// The overall kind of family.
    /// </summary>
    enum class PanoseFamily
    {
        Any = DWRITE_PANOSE_FAMILY_ANY,
        NoFit = DWRITE_PANOSE_FAMILY_NO_FIT,
        TextDisplay = DWRITE_PANOSE_FAMILY_TEXT_DISPLAY,
        Script = DWRITE_PANOSE_FAMILY_SCRIPT, // or hand written
        Decorative = DWRITE_PANOSE_FAMILY_DECORATIVE,
        Symbol = DWRITE_PANOSE_FAMILY_SYMBOL, // or symbol
        Pictorial = DWRITE_PANOSE_FAMILY_PICTORIAL
    };

    /// <summary>
    /// Appearance of the serifs.
    /// Present for families: 2-text
    /// </summary>
    enum class PanoseSerifStyle
    {
        Any = DWRITE_PANOSE_SERIF_STYLE_ANY,
        NoFit = DWRITE_PANOSE_SERIF_STYLE_NO_FIT,
        Cove = DWRITE_PANOSE_SERIF_STYLE_COVE,
        ObtuseCove = DWRITE_PANOSE_SERIF_STYLE_OBTUSE_COVE,
        SquareCove = DWRITE_PANOSE_SERIF_STYLE_SQUARE_COVE,
        ObtuseSquareCove = DWRITE_PANOSE_SERIF_STYLE_OBTUSE_SQUARE_COVE,
        Square = DWRITE_PANOSE_SERIF_STYLE_SQUARE,
        Thin = DWRITE_PANOSE_SERIF_STYLE_THIN,
        Oval = DWRITE_PANOSE_SERIF_STYLE_OVAL,
        Exaggerated = DWRITE_PANOSE_SERIF_STYLE_EXAGGERATED,
        Triangle = DWRITE_PANOSE_SERIF_STYLE_TRIANGLE,
        NormalSans = DWRITE_PANOSE_SERIF_STYLE_NORMAL_SANS,
        ObtuseSans = DWRITE_PANOSE_SERIF_STYLE_OBTUSE_SANS,
        PerpendicularSans = DWRITE_PANOSE_SERIF_STYLE_PERPENDICULAR_SANS,
        Flared = DWRITE_PANOSE_SERIF_STYLE_FLARED,
        Rounded = DWRITE_PANOSE_SERIF_STYLE_ROUNDED,
        Script = DWRITE_PANOSE_SERIF_STYLE_SCRIPT,
        PerpSans = DWRITE_PANOSE_SERIF_STYLE_PERP_SANS,
        Bone = DWRITE_PANOSE_SERIF_STYLE_BONE
    };

    /// <summary>
    /// PANOSE font weights. These roughly correspond to the DWRITE_FONT_WEIGHT's
    /// using (panose_weight - 2) * 100.
    /// Present for families: 2-text, 3-script, 4-decorative, 5-symbol
    /// </summary>
    enum class PanoseWeight
    {
        Any = DWRITE_PANOSE_WEIGHT_ANY,
        NoFit = DWRITE_PANOSE_WEIGHT_NO_FIT,
        VeryLight = DWRITE_PANOSE_WEIGHT_VERY_LIGHT,
        Light = DWRITE_PANOSE_WEIGHT_LIGHT,
        Thin = DWRITE_PANOSE_WEIGHT_THIN,
        Book = DWRITE_PANOSE_WEIGHT_BOOK,
        Medium = DWRITE_PANOSE_WEIGHT_MEDIUM,
        Demi = DWRITE_PANOSE_WEIGHT_DEMI,
        Bold = DWRITE_PANOSE_WEIGHT_BOLD,
        Heavy = DWRITE_PANOSE_WEIGHT_HEAVY,
        Black = DWRITE_PANOSE_WEIGHT_BLACK,
        ExtraBlack = DWRITE_PANOSE_WEIGHT_EXTRA_BLACK,
        Nord = DWRITE_PANOSE_WEIGHT_NORD
    };

    /// <summary>
    /// Proportion of the glyph shape considering additional detail to standard
    /// characters.
    /// Present for families: 2-text
    /// </summary>
    enum class PanoseProportion
    {
        Any = DWRITE_PANOSE_PROPORTION_ANY,
        NoFit = DWRITE_PANOSE_PROPORTION_NO_FIT,
        OldStyle = DWRITE_PANOSE_PROPORTION_OLD_STYLE,
        Modern = DWRITE_PANOSE_PROPORTION_MODERN,
        EvenWidth = DWRITE_PANOSE_PROPORTION_EVEN_WIDTH,
        Expanded = DWRITE_PANOSE_PROPORTION_EXPANDED,
        Condensed = DWRITE_PANOSE_PROPORTION_CONDENSED,
        VeryExpanded = DWRITE_PANOSE_PROPORTION_VERY_EXPANDED,
        VeryCondensed = DWRITE_PANOSE_PROPORTION_VERY_CONDENSED,
        Monospaced = DWRITE_PANOSE_PROPORTION_MONOSPACED
    };

    /// <summary>
    /// Ratio between thickest and thinnest point of the stroke for a letter such
    /// as uppercase 'O'.
    /// Present for families: 2-text, 3-script, 4-decorative
    /// </summary>
    enum class PanoseContrast
    {
        Any = DWRITE_PANOSE_CONTRAST_ANY,
        NoFit = DWRITE_PANOSE_CONTRAST_NO_FIT,
        None = DWRITE_PANOSE_CONTRAST_NONE,
        VeryLow = DWRITE_PANOSE_CONTRAST_VERY_LOW,
        Low = DWRITE_PANOSE_CONTRAST_LOW,
        MediumLow = DWRITE_PANOSE_CONTRAST_MEDIUM_LOW,
        Medium = DWRITE_PANOSE_CONTRAST_MEDIUM,
        MediumHigh = DWRITE_PANOSE_CONTRAST_MEDIUM_HIGH,
        High = DWRITE_PANOSE_CONTRAST_HIGH,
        VeryHigh = DWRITE_PANOSE_CONTRAST_VERY_HIGH,
        HorizontalLow = DWRITE_PANOSE_CONTRAST_HORIZONTAL_LOW,
        HorizontalMedium = DWRITE_PANOSE_CONTRAST_HORIZONTAL_MEDIUM,
        HorizontalHigh = DWRITE_PANOSE_CONTRAST_HORIZONTAL_HIGH,
        Broken = DWRITE_PANOSE_CONTRAST_BROKEN
    };

    /// <summary>
    /// Relationship between thin and thick stems.
    /// Present for families: 2-text
    /// </summary>
    enum class PanoseStrokeVariation
    {
        Any = DWRITE_PANOSE_STROKE_VARIATION_ANY,
        NoFit = DWRITE_PANOSE_STROKE_VARIATION_NO_FIT,
        NoVariation = DWRITE_PANOSE_STROKE_VARIATION_NO_VARIATION,
        GradualDiagonal = DWRITE_PANOSE_STROKE_VARIATION_GRADUAL_DIAGONAL,
        GradualTransitional = DWRITE_PANOSE_STROKE_VARIATION_GRADUAL_TRANSITIONAL,
        GradualVertical = DWRITE_PANOSE_STROKE_VARIATION_GRADUAL_VERTICAL,
        GradualHorizontal = DWRITE_PANOSE_STROKE_VARIATION_GRADUAL_HORIZONTAL,
        RapidVertical = DWRITE_PANOSE_STROKE_VARIATION_RAPID_VERTICAL,
        RapidHorizontal = DWRITE_PANOSE_STROKE_VARIATION_RAPID_HORIZONTAL,
        InstantVertical = DWRITE_PANOSE_STROKE_VARIATION_INSTANT_VERTICAL,
        InstantHorizontal = DWRITE_PANOSE_STROKE_VARIATION_INSTANT_HORIZONTAL
    };

    /// <summary>
    /// Style of termination of stems and rounded letterforms.
    /// Present for families: 2-text
    /// </summary>
    enum class PanoseArmStyle
    {
        Any = DWRITE_PANOSE_ARM_STYLE_ANY,
        NoFit = DWRITE_PANOSE_ARM_STYLE_NO_FIT,
        StraightArmsHorizontal = DWRITE_PANOSE_ARM_STYLE_STRAIGHT_ARMS_HORIZONTAL,
        StraightArmsWedge = DWRITE_PANOSE_ARM_STYLE_STRAIGHT_ARMS_WEDGE,
        StraightArmsVertical = DWRITE_PANOSE_ARM_STYLE_STRAIGHT_ARMS_VERTICAL,
        StraightArmsSingleSerif = DWRITE_PANOSE_ARM_STYLE_STRAIGHT_ARMS_SINGLE_SERIF,
        StraightArmsDoubleSerif = DWRITE_PANOSE_ARM_STYLE_STRAIGHT_ARMS_DOUBLE_SERIF,
        NonstraightArmsHorizontal = DWRITE_PANOSE_ARM_STYLE_NONSTRAIGHT_ARMS_HORIZONTAL,
        NonstraightArmsWedge = DWRITE_PANOSE_ARM_STYLE_NONSTRAIGHT_ARMS_WEDGE,
        NonstraightArmsVertical = DWRITE_PANOSE_ARM_STYLE_NONSTRAIGHT_ARMS_VERTICAL,
        NonstraightArmsSingleSerif = DWRITE_PANOSE_ARM_STYLE_NONSTRAIGHT_ARMS_SINGLE_SERIF,
        NonstraightArmsDoubleSerif = DWRITE_PANOSE_ARM_STYLE_NONSTRAIGHT_ARMS_DOUBLE_SERIF
    };

    /// <summary>
    /// Roundness of letterform.
    /// Present for families: 2-text
    /// </summary>
    enum class PanoseLetterform
    {
        Any = DWRITE_PANOSE_LETTERFORM_ANY,
        NoFit = DWRITE_PANOSE_LETTERFORM_NO_FIT,
        NormalContact = DWRITE_PANOSE_LETTERFORM_NORMAL_CONTACT,
        NormalWeighted = DWRITE_PANOSE_LETTERFORM_NORMAL_WEIGHTED,
        NormalBoxed = DWRITE_PANOSE_LETTERFORM_NORMAL_BOXED,
        NormalFlattened = DWRITE_PANOSE_LETTERFORM_NORMAL_FLATTENED,
        NormalRounded = DWRITE_PANOSE_LETTERFORM_NORMAL_ROUNDED,
        NormalOffCenter = DWRITE_PANOSE_LETTERFORM_NORMAL_OFF_CENTER,
        NormalSquare = DWRITE_PANOSE_LETTERFORM_NORMAL_SQUARE,
        ObliqueContact = DWRITE_PANOSE_LETTERFORM_OBLIQUE_CONTACT,
        ObliqueWeighted = DWRITE_PANOSE_LETTERFORM_OBLIQUE_WEIGHTED,
        ObliqueBoxed = DWRITE_PANOSE_LETTERFORM_OBLIQUE_BOXED,
        ObliqueFlattened = DWRITE_PANOSE_LETTERFORM_OBLIQUE_FLATTENED,
        ObliqueRounded = DWRITE_PANOSE_LETTERFORM_OBLIQUE_ROUNDED,
        ObliqueOffCenter = DWRITE_PANOSE_LETTERFORM_OBLIQUE_OFF_CENTER,
        ObliqueSquare = DWRITE_PANOSE_LETTERFORM_OBLIQUE_SQUARE
    };

    /// <summary>
    /// Placement of midline across uppercase characters and treatment of diagonal
    /// stem apexes.
    /// Present for families: 2-text
    /// </summary>
    enum class PanoseMidline
    {
        Any = DWRITE_PANOSE_MIDLINE_ANY,
        NoFit = DWRITE_PANOSE_MIDLINE_NO_FIT,
        StandardTrimmed = DWRITE_PANOSE_MIDLINE_STANDARD_TRIMMED,
        StandardPointed = DWRITE_PANOSE_MIDLINE_STANDARD_POINTED,
        StandardSerifed = DWRITE_PANOSE_MIDLINE_STANDARD_SERIFED,
        HighTrimmed = DWRITE_PANOSE_MIDLINE_HIGH_TRIMMED,
        HighPointed = DWRITE_PANOSE_MIDLINE_HIGH_POINTED,
        HighSerifed = DWRITE_PANOSE_MIDLINE_HIGH_SERIFED,
        ConstantTrimmed = DWRITE_PANOSE_MIDLINE_CONSTANT_TRIMMED,
        ConstantPointed = DWRITE_PANOSE_MIDLINE_CONSTANT_POINTED,
        ConstantSerifed = DWRITE_PANOSE_MIDLINE_CONSTANT_SERIFED,
        LowTrimmed = DWRITE_PANOSE_MIDLINE_LOW_TRIMMED,
        LowPointed = DWRITE_PANOSE_MIDLINE_LOW_POINTED,
        LowSerifed = DWRITE_PANOSE_MIDLINE_LOW_SERIFED
    };

    /// <summary>
    /// Relative size of lowercase letters and treament of diacritic marks
    /// and uppercase glyphs.
    /// Present for families: 2-text
    /// </summary>
    enum class PanoseXHeight
    {
        Any = DWRITE_PANOSE_XHEIGHT_ANY,
        NoFit = DWRITE_PANOSE_XHEIGHT_NO_FIT,
        ConstantSmall = DWRITE_PANOSE_XHEIGHT_CONSTANT_SMALL,
        ConstantStandard = DWRITE_PANOSE_XHEIGHT_CONSTANT_STANDARD,
        ConstantLarge = DWRITE_PANOSE_XHEIGHT_CONSTANT_LARGE,
        DuckingSmall = DWRITE_PANOSE_XHEIGHT_DUCKING_SMALL,
        DuckingStandard = DWRITE_PANOSE_XHEIGHT_DUCKING_STANDARD,
        DuckingLarge = DWRITE_PANOSE_XHEIGHT_DUCKING_LARGE,
        ConstantStd = DWRITE_PANOSE_XHEIGHT_CONSTANT_STD,
        DuckingStd = DWRITE_PANOSE_XHEIGHT_DUCKING_STD
    };

    /// <summary>
    /// Kind of tool used to create character forms.
    /// Present for families: 3-script
    /// </summary>
    enum class PanoseToolKind
    {
        Any = DWRITE_PANOSE_TOOL_KIND_ANY,
        NoFit = DWRITE_PANOSE_TOOL_KIND_NO_FIT,
        FlatNib = DWRITE_PANOSE_TOOL_KIND_FLAT_NIB,
        PressurePoint = DWRITE_PANOSE_TOOL_KIND_PRESSURE_POINT,
        Engraved = DWRITE_PANOSE_TOOL_KIND_ENGRAVED,
        Ball = DWRITE_PANOSE_TOOL_KIND_BALL,
        Brush = DWRITE_PANOSE_TOOL_KIND_BRUSH,
        Rough = DWRITE_PANOSE_TOOL_KIND_ROUGH,
        FeltPenBrushTip = DWRITE_PANOSE_TOOL_KIND_FELT_PEN_BRUSH_TIP,
        WildBrush = DWRITE_PANOSE_TOOL_KIND_WILD_BRUSH
    };

    /// <summary>
    /// Monospace vs proportional.
    /// Present for families: 3-script, 5-symbol
    /// </summary>
    enum class PanoseSpacing
    {
        Any = DWRITE_PANOSE_SPACING_ANY,
        NoFit = DWRITE_PANOSE_SPACING_NO_FIT,
        ProportionalSpaced = DWRITE_PANOSE_SPACING_PROPORTIONAL_SPACED,
        Monospaced = DWRITE_PANOSE_SPACING_MONOSPACED
    };

    /// <summary>
    /// Ratio between width and height of the face.
    /// Present for families: 3-script
    /// </summary>
    enum class PanoseAspectRatio
    {
        Any = DWRITE_PANOSE_ASPECT_RATIO_ANY,
        NoFit = DWRITE_PANOSE_ASPECT_RATIO_NO_FIT,
        VeryCondensed = DWRITE_PANOSE_ASPECT_RATIO_VERY_CONDENSED,
        Condensed = DWRITE_PANOSE_ASPECT_RATIO_CONDENSED,
        Normal = DWRITE_PANOSE_ASPECT_RATIO_NORMAL,
        Expanded = DWRITE_PANOSE_ASPECT_RATIO_EXPANDED,
        VeryExpanded = DWRITE_PANOSE_ASPECT_RATIO_VERY_EXPANDED
    };

    /// <summary>
    /// Topology of letterforms.
    /// Present for families: 3-script
    /// </summary>
    enum class PanoseScriptTopology
    {
        Any = DWRITE_PANOSE_SCRIPT_TOPOLOGY_ANY,
        NoFit = DWRITE_PANOSE_SCRIPT_TOPOLOGY_NO_FIT,
        RomanDisconnected = DWRITE_PANOSE_SCRIPT_TOPOLOGY_ROMAN_DISCONNECTED,
        RomanTrailing = DWRITE_PANOSE_SCRIPT_TOPOLOGY_ROMAN_TRAILING,
        RomanConnected = DWRITE_PANOSE_SCRIPT_TOPOLOGY_ROMAN_CONNECTED,
        CursiveDisconnected = DWRITE_PANOSE_SCRIPT_TOPOLOGY_CURSIVE_DISCONNECTED,
        CursiveTrailing = DWRITE_PANOSE_SCRIPT_TOPOLOGY_CURSIVE_TRAILING,
        CursiveConnected = DWRITE_PANOSE_SCRIPT_TOPOLOGY_CURSIVE_CONNECTED,
        BlackletterDisconnected = DWRITE_PANOSE_SCRIPT_TOPOLOGY_BLACKLETTER_DISCONNECTED,
        BlackletterTrailing = DWRITE_PANOSE_SCRIPT_TOPOLOGY_BLACKLETTER_TRAILING,
        BlackletterConnected = DWRITE_PANOSE_SCRIPT_TOPOLOGY_BLACKLETTER_CONNECTED
    };

    /// <summary>
    /// General look of the face, considering slope and tails.
    /// Present for families: 3-script
    /// </summary>
    enum class PanoseScriptForm
    {
        Any = DWRITE_PANOSE_SCRIPT_FORM_ANY,
        NoFit = DWRITE_PANOSE_SCRIPT_FORM_NO_FIT,
        UprightNoWrapping = DWRITE_PANOSE_SCRIPT_FORM_UPRIGHT_NO_WRAPPING,
        UprightSomeWrapping = DWRITE_PANOSE_SCRIPT_FORM_UPRIGHT_SOME_WRAPPING,
        UprightMoreWrapping = DWRITE_PANOSE_SCRIPT_FORM_UPRIGHT_MORE_WRAPPING,
        UprightExtremeWrapping = DWRITE_PANOSE_SCRIPT_FORM_UPRIGHT_EXTREME_WRAPPING,
        ObliqueNoWrapping = DWRITE_PANOSE_SCRIPT_FORM_OBLIQUE_NO_WRAPPING,
        ObliqueSomeWrapping = DWRITE_PANOSE_SCRIPT_FORM_OBLIQUE_SOME_WRAPPING,
        ObliqueMoreWrapping = DWRITE_PANOSE_SCRIPT_FORM_OBLIQUE_MORE_WRAPPING,
        ObliqueExtremeWrapping = DWRITE_PANOSE_SCRIPT_FORM_OBLIQUE_EXTREME_WRAPPING,
        ExaggeratedNoWrapping = DWRITE_PANOSE_SCRIPT_FORM_EXAGGERATED_NO_WRAPPING,
        ExaggeratedSomeWrapping = DWRITE_PANOSE_SCRIPT_FORM_EXAGGERATED_SOME_WRAPPING,
        ExaggeratedMoreWrapping = DWRITE_PANOSE_SCRIPT_FORM_EXAGGERATED_MORE_WRAPPING,
        ExaggeratedExtremeWrapping = DWRITE_PANOSE_SCRIPT_FORM_EXAGGERATED_EXTREME_WRAPPING
    };

    /// <summary>
    /// How character ends and miniscule ascenders are treated.
    /// Present for families: 3-script
    /// </summary>
    enum class PanoseFinials
    {
        Any = DWRITE_PANOSE_FINIALS_ANY,
        NoFit = DWRITE_PANOSE_FINIALS_NO_FIT,
        NoneNoLoops = DWRITE_PANOSE_FINIALS_NONE_NO_LOOPS,
        NoneClosedLoops = DWRITE_PANOSE_FINIALS_NONE_CLOSED_LOOPS,
        NoneOpenLoops = DWRITE_PANOSE_FINIALS_NONE_OPEN_LOOPS,
        SharpNoLoops = DWRITE_PANOSE_FINIALS_SHARP_NO_LOOPS,
        SharpClosedLoops = DWRITE_PANOSE_FINIALS_SHARP_CLOSED_LOOPS,
        SharpOpenLoops = DWRITE_PANOSE_FINIALS_SHARP_OPEN_LOOPS,
        TaperedNoLoops = DWRITE_PANOSE_FINIALS_TAPERED_NO_LOOPS,
        TaperedClosedLoops = DWRITE_PANOSE_FINIALS_TAPERED_CLOSED_LOOPS,
        TaperedOpenLoops = DWRITE_PANOSE_FINIALS_TAPERED_OPEN_LOOPS,
        RoundNoLoops = DWRITE_PANOSE_FINIALS_ROUND_NO_LOOPS,
        RoundClosedLoops = DWRITE_PANOSE_FINIALS_ROUND_CLOSED_LOOPS,
        RoundOpenLoops = DWRITE_PANOSE_FINIALS_ROUND_OPEN_LOOPS
    };

    /// <summary>
    /// Relative size of the lowercase letters.
    /// Present for families: 3-script
    /// </summary>
    enum class PanoseXAscent
    {
        Any = DWRITE_PANOSE_XASCENT_ANY,
        NoFit = DWRITE_PANOSE_XASCENT_NO_FIT,
        VeryLow = DWRITE_PANOSE_XASCENT_VERY_LOW,
        Low = DWRITE_PANOSE_XASCENT_LOW,
        Medium = DWRITE_PANOSE_XASCENT_MEDIUM,
        High = DWRITE_PANOSE_XASCENT_HIGH,
        VeryHigh = DWRITE_PANOSE_XASCENT_VERY_HIGH
    };

    /// <summary>
    /// General look of the face.
    /// Present for families: 4-decorative
    /// </summary>
    enum class PanoseDecorativeClass
    {
        Any = DWRITE_PANOSE_DECORATIVE_CLASS_ANY,
        NoFit = DWRITE_PANOSE_DECORATIVE_CLASS_NO_FIT,
        Derivative = DWRITE_PANOSE_DECORATIVE_CLASS_DERIVATIVE,
        NonstandardTopology = DWRITE_PANOSE_DECORATIVE_CLASS_NONSTANDARD_TOPOLOGY,
        NonstandardElements = DWRITE_PANOSE_DECORATIVE_CLASS_NONSTANDARD_ELEMENTS,
        NonstandardAspect = DWRITE_PANOSE_DECORATIVE_CLASS_NONSTANDARD_ASPECT,
        Initials = DWRITE_PANOSE_DECORATIVE_CLASS_INITIALS,
        Cartoon = DWRITE_PANOSE_DECORATIVE_CLASS_CARTOON,
        PictureStems = DWRITE_PANOSE_DECORATIVE_CLASS_PICTURE_STEMS,
        Ornamented = DWRITE_PANOSE_DECORATIVE_CLASS_ORNAMENTED,
        TextAndBackground = DWRITE_PANOSE_DECORATIVE_CLASS_TEXT_AND_BACKGROUND,
        Collage = DWRITE_PANOSE_DECORATIVE_CLASS_COLLAGE,
        Montage = DWRITE_PANOSE_DECORATIVE_CLASS_MONTAGE
    };

    /// <summary>
    /// Ratio between the width and height of the face.
    /// Present for families: 4-decorative
    /// </summary>
    enum class PanoseAspect
    {
        Any = DWRITE_PANOSE_ASPECT_ANY,
        NoFit = DWRITE_PANOSE_ASPECT_NO_FIT,
        SuperCondensed = DWRITE_PANOSE_ASPECT_SUPER_CONDENSED,
        VeryCondensed = DWRITE_PANOSE_ASPECT_VERY_CONDENSED,
        Condensed = DWRITE_PANOSE_ASPECT_CONDENSED,
        Normal = DWRITE_PANOSE_ASPECT_NORMAL,
        Extended = DWRITE_PANOSE_ASPECT_EXTENDED,
        VeryExtended = DWRITE_PANOSE_ASPECT_VERY_EXTENDED,
        SuperExtended = DWRITE_PANOSE_ASPECT_SUPER_EXTENDED,
        Monospaced = DWRITE_PANOSE_ASPECT_MONOSPACED
    };

    /// <summary>
    /// Type of fill/line (treatment).
    /// Present for families: 4-decorative
    /// </summary>
    enum class PanoseFill
    {
        Any = DWRITE_PANOSE_FILL_ANY,
        NoFit = DWRITE_PANOSE_FILL_NO_FIT,
        StandardSolidFill = DWRITE_PANOSE_FILL_STANDARD_SOLID_FILL,
        NoFill = DWRITE_PANOSE_FILL_NO_FILL,
        PatternedFill = DWRITE_PANOSE_FILL_PATTERNED_FILL,
        ComplexFill = DWRITE_PANOSE_FILL_COMPLEX_FILL,
        ShapedFill = DWRITE_PANOSE_FILL_SHAPED_FILL,
        DrawnDistressed = DWRITE_PANOSE_FILL_DRAWN_DISTRESSED,
    };

    /// <summary>
    /// Outline handling.
    /// Present for families: 4-decorative
    /// </summary>
    enum class PanoseLining
    {
        Any = DWRITE_PANOSE_LINING_ANY,
        NoFit = DWRITE_PANOSE_LINING_NO_FIT,
        None = DWRITE_PANOSE_LINING_NONE,
        Inline = DWRITE_PANOSE_LINING_INLINE,
        Outline = DWRITE_PANOSE_LINING_OUTLINE,
        Engraved = DWRITE_PANOSE_LINING_ENGRAVED,
        Shadow = DWRITE_PANOSE_LINING_SHADOW,
        Relief = DWRITE_PANOSE_LINING_RELIEF,
        Backdrop = DWRITE_PANOSE_LINING_BACKDROP
    };

    /// <summary>
    /// Overall shape characteristics of the font.
    /// Present for families: 4-decorative
    /// </summary>
    enum class PanoseDecorativeTopology
    {
        Any = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_ANY,
        NoFit = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_NO_FIT,
        Standard = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_STANDARD,
        Square = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_SQUARE,
        MultipleSegment = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_MULTIPLE_SEGMENT,
        ArtDeco = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_ART_DECO,
        UnevenWeighting = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_UNEVEN_WEIGHTING,
        DiverseArms = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_DIVERSE_ARMS,
        DiverseForms = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_DIVERSE_FORMS,
        LombardicForms = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_LOMBARDIC_FORMS,
        UpperCaseInLowerCase = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_UPPER_CASE_IN_LOWER_CASE,
        ImpliedTopology = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_IMPLIED_TOPOLOGY,
        HorseshoeEAndA = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_HORSESHOE_E_AND_A,
        Cursive = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_CURSIVE,
        Blackletter = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_BLACKLETTER,
        SwashVariance = DWRITE_PANOSE_DECORATIVE_TOPOLOGY_SWASH_VARIANCE
    };

    /// <summary>
    /// Type of characters available in the font.
    /// Present for families: 4-decorative
    /// </summary>
    enum class PanoseCharacterRanges
    {
        Any = DWRITE_PANOSE_CHARACTER_RANGES_ANY,
        NoFit = DWRITE_PANOSE_CHARACTER_RANGES_NO_FIT,
        ExtendedCollection = DWRITE_PANOSE_CHARACTER_RANGES_EXTENDED_COLLECTION,
        Literals = DWRITE_PANOSE_CHARACTER_RANGES_LITERALS,
        NoLowerCase = DWRITE_PANOSE_CHARACTER_RANGES_NO_LOWER_CASE,
        SmallCaps = DWRITE_PANOSE_CHARACTER_RANGES_SMALL_CAPS
    };

    /// <summary>
    /// Kind of symbol set.
    /// Present for families: 5-symbol
    /// </summary>
    enum class PanoseSymbolKind
    {
        Any = DWRITE_PANOSE_SYMBOL_KIND_ANY,
        NoFit = DWRITE_PANOSE_SYMBOL_KIND_NO_FIT,
        Montages = DWRITE_PANOSE_SYMBOL_KIND_MONTAGES,
        Pictures = DWRITE_PANOSE_SYMBOL_KIND_PICTURES,
        Shapes = DWRITE_PANOSE_SYMBOL_KIND_SHAPES,
        Scientific = DWRITE_PANOSE_SYMBOL_KIND_SCIENTIFIC,
        Music = DWRITE_PANOSE_SYMBOL_KIND_MUSIC,
        Expert = DWRITE_PANOSE_SYMBOL_KIND_EXPERT,
        Patterns = DWRITE_PANOSE_SYMBOL_KIND_PATTERNS,
        Boarders = DWRITE_PANOSE_SYMBOL_KIND_BOARDERS,
        Icons = DWRITE_PANOSE_SYMBOL_KIND_ICONS,
        Logos = DWRITE_PANOSE_SYMBOL_KIND_LOGOS,
        IndustrySpecific = DWRITE_PANOSE_SYMBOL_KIND_INDUSTRY_SPECIFIC
    };

    /// <summary>
    /// Aspect ratio of symbolic characters.
    /// Present for families: 5-symbol
    /// </summary>
    enum class PanoseSymbolAspectRatio
    {
        Any = DWRITE_PANOSE_SYMBOL_ASPECT_RATIO_ANY,
        NoFit = DWRITE_PANOSE_SYMBOL_ASPECT_RATIO_NO_FIT,
        NoWidth = DWRITE_PANOSE_SYMBOL_ASPECT_RATIO_NO_WIDTH,
        ExceptionallyWide = DWRITE_PANOSE_SYMBOL_ASPECT_RATIO_EXCEPTIONALLY_WIDE,
        SuperWide = DWRITE_PANOSE_SYMBOL_ASPECT_RATIO_SUPER_WIDE,
        VeryWide = DWRITE_PANOSE_SYMBOL_ASPECT_RATIO_VERY_WIDE,
        Wide = DWRITE_PANOSE_SYMBOL_ASPECT_RATIO_WIDE,
        Normal = DWRITE_PANOSE_SYMBOL_ASPECT_RATIO_NORMAL,
        Narrow = DWRITE_PANOSE_SYMBOL_ASPECT_RATIO_NARROW,
        VeryNarrow = DWRITE_PANOSE_SYMBOL_ASPECT_RATIO_VERY_NARROW
    };

    /// <summary>
    /// Specifies the policy used by GetRecommendedRenderingMode to determine whether to 
    /// render glyphs in outline mode. Glyphs are rendered in outline mode by default at
    /// large sizes for performance reasons, but how large (i.e., the outline threshold)
    /// depends on the quality of outline rendering. If the graphics system renders anti-
    /// aliased outlines then a relatively low threshold is used, but if the graphics
    /// system renders aliased outlines then a much higher threshold is used.
    /// </summary>
    enum class OutlineThreshold
    {
        Antialiased = DWRITE_OUTLINE_THRESHOLD_ANTIALIASED,
        Aliased = DWRITE_OUTLINE_THRESHOLD_ALIASED
    };

    /// <summary>
    /// Baseline for text alignment.
    /// </summary>
    enum class Baseline
    {
        /// <summary>
        /// The Roman baseline for horizontal, Central baseline for vertical.
        /// </summary>
        Default = DWRITE_BASELINE_DEFAULT,

        /// <summary>
        /// The baseline used by alphabetic scripts such as Latin, Greek, Cyrillic.
        /// </summary>
        Roman = DWRITE_BASELINE_ROMAN,

        /// <summary>
        /// Central baseline, generally used for vertical text.
        /// </summary>
        Central = DWRITE_BASELINE_CENTRAL,

        /// <summary>
        /// Mathematical baseline which math characters are centered on.
        /// </summary>
        Math = DWRITE_BASELINE_MATH,

        /// <summary>
        /// Hanging baseline, used in scripts like Devanagari.
        /// </summary>
        Hanging = DWRITE_BASELINE_HANGING,

        /// <summary>
        /// Ideographic bottom baseline for CJK, left in vertical.
        /// </summary>
        IdeographicBottom = DWRITE_BASELINE_IDEOGRAPHIC_BOTTOM,

        /// <summary>
        /// Ideographic top baseline for CJK, right in vertical.
        /// </summary>
        IdeographicTop = DWRITE_BASELINE_IDEOGRAPHIC_TOP,

        /// <summary>
        /// The bottom-most extent in horizontal, left-most in vertical.
        /// </summary>
        Minimum = DWRITE_BASELINE_MINIMUM,

        /// <summary>
        /// The top-most extent in horizontal, right-most in vertical.
        /// </summary>
        Maximum = DWRITE_BASELINE_MAXIMUM,
    };

    /// <summary>
    /// The desired kind of glyph orientation for the text. The client specifies
    /// this to the analyzer as the desired orientation, but note this is the
    /// client preference, and the constraints of the script will determine the
    /// final presentation.
    /// </summary>
    enum class VerticalGlyphOrientation
    {
        /// <summary>
        /// In vertical layout, naturally horizontal scripts (Latin, Thai, Arabic,
        /// Devanagari) rotate 90 degrees clockwise, while ideographic scripts
        /// (Chinese, Japanese, Korean) remain upright, 0 degrees.
        /// </summary>
        Default = DWRITE_VERTICAL_GLYPH_ORIENTATION_DEFAULT,

        /// <summary>
        /// Ideographic scripts and scripts that permit stacking
        /// (Latin, Hebrew) are stacked in vertical reading layout.
        /// Connected scripts (Arabic, Syriac, 'Phags-pa, Ogham),
        /// which would otherwise look broken if glyphs were kept
        /// at 0 degrees, remain connected and rotate.
        /// </summary>
        Stacked = DWRITE_VERTICAL_GLYPH_ORIENTATION_STACKED,
    };

    /// <summary>
    /// How the glyph is oriented to the x-axis. This is an output from the text
    /// analyzer, dependent on the desired orientation, bidi level, and character
    /// properties.
    /// </summary>
    enum class GlyphOrientationAngle
    {
        /// <summary>
        /// Glyph orientation is upright.
        /// </summary>
        Angle0Degrees = DWRITE_GLYPH_ORIENTATION_ANGLE_0_DEGREES,

        /// <summary>
        /// Glyph orientation is rotated 90 clockwise.
        /// </summary>
        Angle90Degrees = DWRITE_GLYPH_ORIENTATION_ANGLE_90_DEGREES,

        /// <summary>
        /// Glyph orientation is upside-down.
        /// </summary>
        Angle180Degrees = DWRITE_GLYPH_ORIENTATION_ANGLE_180_DEGREES,

        /// <summary>
        /// Glyph orientation is rotated 270 clockwise.
        /// </summary>
        Angle270Degrees = DWRITE_GLYPH_ORIENTATION_ANGLE_270_DEGREES,
    };


    struct FontMetrics1 : public DWRITE_FONT_METRICS1
    {
        using Base = DWRITE_FONT_METRICS1;
        FontMetrics1( ) 
            : Base{} 
        {}
    };


    /// <summary>
    /// Metrics for caret placement in a font.
    /// </summary>
    struct CaretMetrics : public DWRITE_CARET_METRICS
    {
        using Base = DWRITE_CARET_METRICS;
        CaretMetrics( )
            : Base{}
        {}
    };


    /// <summary>
    /// Typeface classification values, used for font selection and matching.
    /// </summary>
    /// <remarks>
    /// Note the family type (index 0) is the only stable entry in the 10-byte
    /// array, as all the following entries can change dynamically depending on
    /// context of the first field.
    /// </remarks>
    struct Panose 
    {
        DWRITE_PANOSE Data;
        
        Panose( )
            : Data{}
        {}
    };




    /// <summary>
    /// Range of Unicode codepoints.
    /// </summary>
    struct UnicodeRange : public DWRITE_UNICODE_RANGE
    {
        using Base = DWRITE_UNICODE_RANGE;
        
        UnicodeRange()
            : Base{}
        {}
    };


    /// <summary>
    /// Script-specific properties for caret navigation and justification.
    /// </summary>
    struct ScriptProperties : public DWRITE_SCRIPT_PROPERTIES
    {
        using Base = DWRITE_SCRIPT_PROPERTIES;
        ScriptProperties()
            : Base{}
        {}
    };


    /// <summary>
    /// Justification information per glyph.
    /// </summary>
    struct JustificationOpportunity : public DWRITE_JUSTIFICATION_OPPORTUNITY
    {
        using Base = DWRITE_JUSTIFICATION_OPPORTUNITY;
        JustificationOpportunity()
            : Base{}
        {}
    };


    /// <summary>
    /// How to align glyphs to the margin.
    /// </summary>
    enum class OpticalAlignment
    {
        /// <summary>
        /// Align to the default metrics of the glyph.
        /// </summary>
        None,

        /// <summary>
        /// Align glyphs to the margins. Without this, some small whitespace
        /// may be present between the text and the margin from the glyph's side
        /// bearing values. Note that glyphs may still overhang outside the
        /// margin, such as flourishes or italic slants.
        /// </summary>
        NoSideBearings,
    };


    /// <summary>
    /// Whether to enable grid-fitting of glyph outlines (a.k.a. hinting).
    /// </summary>
    enum class GridFitMode
    {
        /// <summary>
        /// Choose grid fitting base on the font's gasp table information.
        /// </summary>
        DWRITE_GRID_FIT_MODE_DEFAULT,

        /// <summary>
        /// Always disable grid fitting, using the ideal glyph outlines.
        /// </summary>
        DWRITE_GRID_FIT_MODE_DISABLED,

        /// <summary>
        /// Enable grid fitting, adjusting glyph outlines for device pixel display.
        /// </summary>
        DWRITE_GRID_FIT_MODE_ENABLED
    };


    /// <summary>
    /// Overall metrics associated with text after layout.
    /// All coordinates are in device independent pixels (DIPs).
    /// </summary>
    struct TextMetrics1 : public DWRITE_TEXT_METRICS1
    {
        using Base = DWRITE_TEXT_METRICS1;
        TextMetrics1()
            : Base{}
        {}
    };


    /// <summary>
    /// The font property enumeration identifies a string in a font.
    /// </summary>
    enum class FontPropertyId
    {
        /// <summary>
        /// Unspecified font property identifier.
        /// </summary>
        None = DWRITE_FONT_PROPERTY_ID_NONE,

        /// <summary>
        /// Family name for the weight-stretch-style model.
        /// </summary>
        WeightStretchStyleFamilyName = DWRITE_FONT_PROPERTY_ID_WEIGHT_STRETCH_STYLE_FAMILY_NAME,

        /// <summary>
        /// Family name preferred by the designer. This enables font designers to group more than four fonts in a single family without losing compatibility with
        /// GDI. This name is typically only present if it differs from the GDI-compatible family name.
        /// </summary>
        TypographicFamilyName = DWRITE_FONT_PROPERTY_ID_TYPOGRAPHIC_FAMILY_NAME,

        /// <summary>
        /// Face name of the for the weight-stretch-style (e.g., Regular or Bold).
        /// </summary>
        WeightStretchStyleFaceName = DWRITE_FONT_PROPERTY_ID_WEIGHT_STRETCH_STYLE_FACE_NAME,

        /// <summary>
        /// The full name of the font, e.g. "Arial Bold", from name id 4 in the name table.
        /// </summary>
        FullName = DWRITE_FONT_PROPERTY_ID_FULL_NAME,

        /// <summary>
        /// GDI-compatible family name. Because GDI allows a maximum of four fonts per family, fonts in the same family may have different GDI-compatible family names
        /// (e.g., "Arial", "Arial Narrow", "Arial Black").
        /// </summary>
        Win32FamilyName = DWRITE_FONT_PROPERTY_ID_WIN32_FAMILY_NAME,

        /// <summary>
        /// The postscript name of the font, e.g. "GillSans-Bold" from name id 6 in the name table.
        /// </summary>
        PostscriptName = DWRITE_FONT_PROPERTY_ID_POSTSCRIPT_NAME,

        /// <summary>
        /// Script/language tag to identify the scripts or languages that the font was
        /// primarily designed to support.
        /// </summary>
        /// <remarks>
        /// The design script/language tag is meant to be understood from the perspective of
        /// users. For example, a font is considered designed for English if it is considered
        /// useful for English users. Note that this is different from what a font might be
        /// capable of supporting. For example, the Meiryo font was primarily designed for
        /// Japanese users. While it is capable of displaying English well, it was not
        /// meant to be offered for the benefit of non-Japanese-speaking English users.
        ///
        /// As another example, a font designed for Chinese may be capable of displaying
        /// Japanese text, but would likely look incorrect to Japanese users.
        /// 
        /// The valid values for this property are "ScriptLangTag" values. These are adapted
        /// from the IETF BCP 47 specification, "Tags for Identifying Languages" (see
        /// http://tools.ietf.org/html/bcp47). In a BCP 47 language tag, a language subtag
        /// element is mandatory and other subtags are optional. In a ScriptLangTag, a
        /// script subtag is mandatory and other subtags are option. The following
        /// augmented BNF syntax, adapted from BCP 47, is used:
        /// 
        ///     ScriptLangTag = [language "-"]
        ///                     script
        ///                     ["-" region]
        ///                     *("-" variant)
        ///                     *("-" extension)
        ///                     ["-" privateuse]
        /// 
        /// The expansion of the elements and the intended semantics associated with each
        /// are as defined in BCP 47. Script subtags are taken from ISO 15924. At present,
        /// no extensions are defined, and any extension should be ignored. Private use
        /// subtags are defined by private agreement between the source and recipient and
        /// may be ignored.
        /// 
        /// Subtags must be valid for use in BCP 47 and contained in the Language Subtag
        /// Registry maintained by IANA. (See
        /// http://www.iana.org/assignments/language-subtag-registry/language-subtag-registry
        /// and section 3 of BCP 47 for details.
        /// 
        /// Any ScriptLangTag value not conforming to these specifications is ignored.
        /// 
        /// Examples:
        ///   "Latn" denotes Latin script (and any language or writing system using Latin)
        ///   "Cyrl" denotes Cyrillic script
        ///   "sr-Cyrl" denotes Cyrillic script as used for writing the Serbian language;
        ///       a font that has this property value may not be suitable for displaying
        ///       text in Russian or other languages written using Cyrillic script
        ///   "Jpan" denotes Japanese writing (Han + Hiragana + Katakana)
        ///
        /// When passing this property to GetPropertyValues, use the overload which does
        /// not take a language parameter, since this property has no specific language.
        /// </remarks>
         DesignScriptLanguageTag = DWRITE_FONT_PROPERTY_ID_DESIGN_SCRIPT_LANGUAGE_TAG,

        /// <summary>
        /// Script/language tag to identify the scripts or languages that the font declares
        /// it is able to support.
        /// </summary>
         SupportedScriptLanguageTag = DWRITE_FONT_PROPERTY_ID_SUPPORTED_SCRIPT_LANGUAGE_TAG,

        /// <summary>
        /// Semantic tag to describe the font (e.g. Fancy, Decorative, Handmade, Sans-serif, Swiss, Pixel, Futuristic).
        /// </summary>
        SemanticTag = DWRITE_FONT_PROPERTY_ID_SEMANTIC_TAG,

        /// <summary>
        /// Weight of the font represented as a decimal string in the range 1-999.
        /// </summary>
        /// <remark>
        /// This enum is discouraged for use with IDWriteFontSetBuilder2 in favor of the more generic font axis
        /// DWRITE_FONT_AXIS_TAG_WEIGHT which supports higher precision and range.
        /// </remark>
        Weight = DWRITE_FONT_PROPERTY_ID_WEIGHT,

        /// <summary>
        /// Stretch of the font represented as a decimal string in the range 1-9.
        /// </summary>
        /// <remark>
        /// This enum is discouraged for use with IDWriteFontSetBuilder2 in favor of the more generic font axis
        /// DWRITE_FONT_AXIS_TAG_WIDTH which supports higher precision and range.
        /// </remark>
        Stretch = DWRITE_FONT_PROPERTY_ID_STRETCH,

        /// <summary>
        /// Style of the font represented as a decimal string in the range 0-2.
        /// </summary>
        /// <remark>
        /// This enum is discouraged for use with IDWriteFontSetBuilder2 in favor of the more generic font axes
        /// DWRITE_FONT_AXIS_TAG_SLANT and DWRITE_FONT_AXIS_TAG_ITAL.
        /// </remark>
        Style = DWRITE_FONT_PROPERTY_ID_STYLE,

        /// <summary>
        /// Face name preferred by the designer. This enables font designers to group more than four fonts in a single
        /// family without losing compatibility with GDI.
        /// </summary>
        TypographicFaceName = DWRITE_FONT_PROPERTY_ID_TYPOGRAPHIC_FACE_NAME,

        /// <summary>
        /// Total number of properties for NTDDI_WIN10 (IDWriteFontSet).
        /// </summary>
        /// <remarks>
        /// DWRITE_FONT_PROPERTY_ID_TOTAL cannot be used as a property ID.
        /// </remarks>
        Total = DWRITE_FONT_PROPERTY_ID_STYLE + 1,

        /// <summary>
        /// Total number of properties for NTDDI_WIN10_RS3 (IDWriteFontSet1).
        /// </summary>
        TotalRs3 = DWRITE_FONT_PROPERTY_ID_TYPOGRAPHIC_FACE_NAME + 1,

        // Obsolete aliases kept to avoid breaking existing code.
        PreferredFamilyName = DWRITE_FONT_PROPERTY_ID_TYPOGRAPHIC_FAMILY_NAME,
        FamilyName = DWRITE_FONT_PROPERTY_ID_WEIGHT_STRETCH_STYLE_FAMILY_NAME,
        FaceName = DWRITE_FONT_PROPERTY_ID_WEIGHT_STRETCH_STYLE_FACE_NAME,
    };


    /// <summary>
    /// Font property used for filtering font sets and
    /// building a font set with explicit properties.
    /// </summary>
    struct FontProperty : public DWRITE_FONT_PROPERTY
    {
        using Base = DWRITE_FONT_PROPERTY;
        FontProperty( )
            : Base{}
        {}
    };


    /// <summary>
    /// Specifies the locality of a resource.
    /// </summary>
    enum class Locality
    {
        /// <summary>
        /// The resource is remote, and information is unknown yet, including the file size and date.
        /// Attempting to create a font or file stream will fail until locality becomes at least partial.
        /// </summary>
        Remote = DWRITE_LOCALITY_REMOTE,

        /// <summary>
        /// The resource is partially local, meaning you can query the size and date of the file
        /// stream, and you may be able to create a font face and retrieve the particular glyphs
        /// for metrics and drawing, but not all the glyphs will be present.
        /// </summary>
        Partial = DWRITE_LOCALITY_PARTIAL,

        /// <summary>
        /// The resource is completely local, and all font functions can be called
        /// without concern of missing data or errors related to network connectivity.
        /// </summary>
        Local = DWRITE_LOCALITY_LOCAL,
    };


    /// <summary>
    /// Represents a method of rendering glyphs.
    /// </summary>
    enum class RenderingMode1
    {
        /// <summary>
        /// Specifies that the rendering mode is determined automatically based on the font and size.
        /// </summary>
        Default = DWRITE_RENDERING_MODE1_DEFAULT,

        /// <summary>
        /// Specifies that no antialiasing is performed. Each pixel is either set to the foreground 
        /// color of the text or retains the color of the background.
        /// </summary>
        Aliased = DWRITE_RENDERING_MODE1_ALIASED,

        /// <summary>
        /// Specifies that antialiasing is performed in the horizontal direction and the appearance
        /// of glyphs is layout-compatible with GDI using CLEARTYPE_QUALITY. Use DWRITE_MEASURING_MODE_GDI_CLASSIC 
        /// to get glyph advances. The antialiasing may be either ClearType or grayscale depending on
        /// the text antialiasing mode.
        /// </summary>
        GdiClassic = DWRITE_RENDERING_MODE1_GDI_CLASSIC,

        /// <summary>
        /// Specifies that antialiasing is performed in the horizontal direction and the appearance
        /// of glyphs is layout-compatible with GDI using CLEARTYPE_NATURAL_QUALITY. Glyph advances
        /// are close to the font design advances, but are still rounded to whole pixels. Use
        /// DWRITE_MEASURING_MODE_GDI_NATURAL to get glyph advances. The antialiasing may be either
        /// ClearType or grayscale depending on the text antialiasing mode.
        /// </summary>
        GdiNatural = DWRITE_RENDERING_MODE1_GDI_NATURAL,

        /// <summary>
        /// Specifies that antialiasing is performed in the horizontal direction. This rendering
        /// mode allows glyphs to be positioned with subpixel precision and is therefore suitable
        /// for natural (i.e., resolution-independent) layout. The antialiasing may be either
        /// ClearType or grayscale depending on the text antialiasing mode.
        /// </summary>
        Natural = DWRITE_RENDERING_MODE1_NATURAL,

        /// <summary>
        /// Similar to natural mode except that antialiasing is performed in both the horizontal
        /// and vertical directions. This is typically used at larger sizes to make curves and
        /// diagonal lines look smoother. The antialiasing may be either ClearType or grayscale
        /// depending on the text antialiasing mode.
        /// </summary>
        NaturalSymmetric = DWRITE_RENDERING_MODE1_NATURAL_SYMMETRIC,

        /// <summary>
        /// Specifies that rendering should bypass the rasterizer and use the outlines directly. 
        /// This is typically used at very large sizes.
        /// </summary>
        Outline = DWRITE_RENDERING_MODE1_OUTLINE,

        /// <summary>
        /// Similar to natural symmetric mode except that when possible, text should be rasterized
        /// in a downsampled form.
        /// </summary>
        NaturalSymmetricDownsampled = DWRITE_RENDERING_MODE1_NATURAL_SYMMETRIC_DOWNSAMPLED,
    };


    /// <summary>
    /// Information about a formatted line of text.
    /// </summary>
    struct LineMetrics1 : public DWRITE_LINE_METRICS1
    {
        using Base = DWRITE_LINE_METRICS1;

        LineMetrics1()
            : Base{}
        {}
    };

    /// <summary>
    /// Specify whether DWRITE_FONT_METRICS::lineGap value should be part of the line metrics. 
    /// </summary>
    enum class FontLineGapUsage
    {
        /// <summary>
        /// The usage of the font line gap depends on the method used for text layout.
        /// </summary>
         Default = DWRITE_FONT_LINE_GAP_USAGE_DEFAULT,

        /// <summary>
        /// The font line gap is excluded from line spacing
        /// </summary>
        Disabled = DWRITE_FONT_LINE_GAP_USAGE_DISABLED,

        /// <summary>
        /// The font line gap is included in line spacing
        /// </summary>
        Enabled = DWRITE_FONT_LINE_GAP_USAGE_ENABLED
    };

    /// <summary>
    /// The DWRITE_LINE_SPACING structure specifies the parameters used to specify how to manage space between lines.
    /// </summary>
    struct LineSpacing : public DWRITE_LINE_SPACING
    {
        using Base = DWRITE_LINE_SPACING;

        LineSpacing()
            : Base{}
        {}
    };


    /// <summary>
    /// Represents a color glyph run. The IDWriteFactory4::TranslateColorGlyphRun
    /// method returns an ordered collection of color glyph runs of varying types
    /// depending on what the font supports.
    /// </summary>
    /// <summary>
    /// For runs without any specific color, such as PNG data, the runColor field will be zero.
    /// </summary>
    struct ColorGlyphRun1 : public DWRITE_COLOR_GLYPH_RUN1
    {
        using Base = DWRITE_COLOR_GLYPH_RUN1;
        ColorGlyphRun1( )
            : Base{}
        {}
    };


    /// <summary>
    /// Data for a single glyph from GetGlyphImageData.
    /// </summary>
    struct GlyphImageData : public DWRITE_GLYPH_IMAGE_DATA
    {
        using Base = DWRITE_GLYPH_IMAGE_DATA;
        GlyphImageData()
            : Base{}
        {}
    };


    /// <summary>
    /// DWRITE_FILE_FRAGMENT represents a range of bytes in a font file.
    /// </summary>
    struct FileFragment : public DWRITE_FILE_FRAGMENT
    {
        using Base = DWRITE_FILE_FRAGMENT;
        FileFragment()
            : Base{}
        {}
    };


    /// <summary>
    /// Specifies the container format of a font resource. A container format is distinct from
    /// a font file format (DWRITE_FONT_FILE_TYPE) because the container describes the container
    /// in which the underlying font file is packaged.
    /// </summary>
    enum class ContainerType
    {
        Unknown = DWRITE_CONTAINER_TYPE_UNKNOWN,
        Woff = DWRITE_CONTAINER_TYPE_WOFF,
        Woff2 = DWRITE_CONTAINER_TYPE_WOFF2
    };

    /// <summary>
/// Four character identifier for a font axis.
/// </summary>
/// <remarks>
/// Use DWRITE_MAKE_FONT_AXIS_TAG() to create a custom one.
/// <remarks>
    enum class FontAxisTag : UINT32
    {
        Weight = DWRITE_FONT_AXIS_TAG_WEIGHT,
        Width = DWRITE_FONT_AXIS_TAG_WIDTH,
        Slant = DWRITE_FONT_AXIS_TAG_SLANT,
        OpticalSize = DWRITE_FONT_AXIS_TAG_OPTICAL_SIZE,
        Italic = DWRITE_FONT_AXIS_TAG_ITALIC,
    };

#define DWRITE_STANDARD_FONT_AXIS_COUNT 5

    /// <summary>
    /// Value for a font axis, used when querying and creating font instances.
    /// </summary>
    struct FontAxisValue : public DWRITE_FONT_AXIS_VALUE
    {
        using Base = DWRITE_FONT_AXIS_VALUE;
        FontAxisValue()
            : Base{}
        {}
    };


    /// <summary>
    /// Minimum and maximum range of a font axis.
    /// </summary>
    struct FontAxisRange : public DWRITE_FONT_AXIS_RANGE
    {
        using Base = DWRITE_FONT_AXIS_RANGE;
        FontAxisRange()
            : Base{}
        {}
    };


    /// <summary>
    /// How font families are grouped together, used by IDWriteFontCollection.
    /// </summary>
    enum class FontFamilyModel
    {
        /// <summary>
        /// Families are grouped by the typographic family name preferred by the font author. The family can contain as
        /// many face as the font author wants.
        /// This corresponds to the DWRITE_FONT_PROPERTY_ID_TYPOGRAPHIC_FAMILY_NAME.
        /// </summary>
        Typographic = DWRITE_FONT_FAMILY_MODEL_TYPOGRAPHIC,

        /// <summary>
        /// Families are grouped by the weight-stretch-style family name, where all faces that differ only by those three
        /// axes are grouped into the same family, but any other axes go into a distinct family. For example, the Sitka
        /// family with six different optical sizes yields six separate families (Sitka Caption, Display, Text, Subheading,
        /// Heading, Banner...). This corresponds to the DWRITE_FONT_PROPERTY_ID_WEIGHT_STRETCH_STYLE_FAMILY_NAME.
        /// </summary>
        WeightStretchStyle = DWRITE_FONT_FAMILY_MODEL_WEIGHT_STRETCH_STYLE,
    };


    /// <summary>
    /// Apply certain axes automatically in layout during font selection.
    /// </summary>
    enum class AutomaticFontAxes
    {
        /// <summary>
        /// No axes are automatically applied.
        /// </summary>
        None = DWRITE_AUTOMATIC_FONT_AXES_NONE,

        /// <summary>
        /// Automatically pick an appropriate optical value based on the font size (via SetFontSize) when no value is
        /// specified via DWRITE_FONT_AXIS_TAG_OPTICAL_SIZE. Callers can still explicitly apply the 'opsz' value over
        /// text ranges via SetFontAxisValues, which take priority.
        /// </summary>
        OpticalSize = DWRITE_AUTOMATIC_FONT_AXES_OPTICAL_SIZE,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( AutomaticFontAxes, Int32 );


    /// <summary>
    /// Attributes for a font axis.
    /// </summary>
    enum class FontAxisAttributes
    {
        /// <summary>
        /// No attributes.
        /// </summary>
        None = DWRITE_FONT_AXIS_ATTRIBUTES_NONE,

        /// <summary>
        /// This axis is implemented as a variation axis in a variable font, with a continuous range of
        /// values, such as a range of weights from 100..900. Otherwise it is either a static axis that
        /// holds a single point, or it has a range but doesn't vary, such as optical size in the Skia
        /// Heading font which covers a range of points but doesn't interpolate any new glyph outlines.
        /// </summary>
        Variable = DWRITE_FONT_AXIS_ATTRIBUTES_VARIABLE,

        /// <summary>
        /// This axis is recommended to be remain hidden in user interfaces. The font developer may
        /// recommend this if an axis is intended to be accessed only programmatically, or is meant for
        /// font-internal or font-developer use only. The axis may be exposed in lower-level font
        /// inspection utilities, but should not be exposed in common or even advanced-mode user
        /// interfaces in content-authoring apps.
        /// </summary>
        Hidden = DWRITE_FONT_AXIS_ATTRIBUTES_HIDDEN,
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( FontAxisAttributes, Int32 );

    /// <summary>
    /// The font source type identifies the mechanism by which a font came to be included in a font set.
    /// </summary>
    enum class FontSourceType
    {
        /// <summary>
        /// The font source is unknown or is not any of the other defined font source types.
        /// </summary>
        Unknown = DWRITE_FONT_SOURCE_TYPE_UNKNOWN,

        /// <summary>
        /// The font source is a font file, which is installed for all users on the device.
        /// </summary>
        PerMachine = DWRITE_FONT_SOURCE_TYPE_PER_MACHINE,

        /// <summary>
        /// The font source is a font file, which is installed for the current user.
        /// </summary>
        PerUser = DWRITE_FONT_SOURCE_TYPE_PER_USER,

        /// <summary>
        /// The font source is an APPX package, which includes one or more font files.
        /// The font source name is the full name of the package.
        /// </summary>
        AppxPackage = DWRITE_FONT_SOURCE_TYPE_APPX_PACKAGE,

        /// <summary>
        /// The font source is a font provider for downloadable fonts.
        /// </summary>
        RemoteFontProvider = DWRITE_FONT_SOURCE_TYPE_REMOTE_FONT_PROVIDER
    };

    /// <summary>
    /// Contains information about a bitmap associated with an IDWriteBitmapRenderTarget.
    /// The bitmap is top-down with 32-bits per pixel and no padding between scan lines.
    /// </summary>
    struct BitmapDataBGRA32 : public DWRITE_BITMAP_DATA_BGRA32
    {
        using Base = DWRITE_BITMAP_DATA_BGRA32;
        BitmapDataBGRA32()
            : Base{}
        {}
    };

    /// <summary>
    /// Defines known feature level for use with the IDWritePaintReader interface and 
    /// related APIs. A feature level represents a level of functionality. For example, it
    /// determines what DWRITE_PAINT_TYPE values might be returned.
    /// </summary>
    /// <remarks>
    /// See the DWRITE_PAINT_TYPE enumeration for which paint types are required for each
    /// feature level.
    /// </remarks>
    enum class PaintFeatureLevel : INT32
    {
        /// <summary>
        /// No paint API support.
        /// </summary>
        None = DWRITE_PAINT_FEATURE_LEVEL_NONE,

        /// <summary>
        /// Specifies a level of functionality corresponding to OpenType COLR version 0.
        /// </summary>
        ColrV0 = DWRITE_PAINT_FEATURE_LEVEL_COLR_V0,

        /// <summary>
        /// Specifies a level of functionality corresponding to OpenType COLR version 1.
        /// </summary>
        ColrV1 = DWRITE_PAINT_FEATURE_LEVEL_COLR_V1
    };

    /// <summary>
    /// Combination of flags specifying attributes of a color glyph or of specific color values in
    /// a color glyph.
    /// </summary>
    enum class PaintAttributes : Int32
    {
        None = DWRITE_PAINT_ATTRIBUTES_NONE,

        /// <summary>
        /// Specifies that the color value (or any color value in the glyph) comes from the font's
        /// color palette. This means the appearance may depend on the current palette index, which
        /// may be important to clients that cache color glyphs.
        /// </summary>
        UsesPalette = DWRITE_PAINT_ATTRIBUTES_USES_PALETTE,

        /// <summary>
        /// Specifies that the color value (or any color value in the glyph) comes from the client-specified
        /// text color. This means the appearance may depend on the text color, which may be important to
        /// clients that cache color glyphs.
        /// </summary>
        UsesTextColor = DWRITE_PAINT_ATTRIBUTES_USES_TEXT_COLOR
    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( PaintAttributes, Int32 );


    /// <summary>
    /// Represents a color in a color glyph.
    /// </summary>
    struct PaintColor : public DWRITE_PAINT_COLOR
    {
        using Base = DWRITE_PAINT_COLOR;
        PaintColor()
            : Base{}
        {}
    };

    /// <summary>
    /// Specifies a composite mode for combining source and destination paint elements in a
    /// color glyph. These are taken from the W3C Compositing and Blending Level 1 specification.
    /// </summary>
    enum class ColorCompositeMode : Int32
    {
        // Porter-Duff modes.
        Clear = DWRITE_COLOR_COMPOSITE_CLEAR,
        Src = DWRITE_COLOR_COMPOSITE_SRC,
        Dest = DWRITE_COLOR_COMPOSITE_DEST,
        SrcOver = DWRITE_COLOR_COMPOSITE_SRC_OVER,
        DestOver = DWRITE_COLOR_COMPOSITE_DEST_OVER,
        SrcIn = DWRITE_COLOR_COMPOSITE_SRC_IN,
        DestIn = DWRITE_COLOR_COMPOSITE_DEST_IN,
        SrcOut = DWRITE_COLOR_COMPOSITE_SRC_OUT,
        DestOut = DWRITE_COLOR_COMPOSITE_DEST_OUT,
        SrcAtop = DWRITE_COLOR_COMPOSITE_SRC_ATOP,
        DestAtop = DWRITE_COLOR_COMPOSITE_DEST_ATOP,
        Xor = DWRITE_COLOR_COMPOSITE_XOR,
        Plus = DWRITE_COLOR_COMPOSITE_PLUS,

        // Separable color blend modes.
        Screen = DWRITE_COLOR_COMPOSITE_SCREEN,
        Overlay = DWRITE_COLOR_COMPOSITE_OVERLAY,
        Darken = DWRITE_COLOR_COMPOSITE_DARKEN,
        Lighten = DWRITE_COLOR_COMPOSITE_LIGHTEN,
        ColorDodge = DWRITE_COLOR_COMPOSITE_COLOR_DODGE,
        ColorBurn = DWRITE_COLOR_COMPOSITE_COLOR_BURN,
        HardLight = DWRITE_COLOR_COMPOSITE_HARD_LIGHT,
        SoftLight = DWRITE_COLOR_COMPOSITE_SOFT_LIGHT,
        Difference = DWRITE_COLOR_COMPOSITE_DIFFERENCE,
        Exclusion = DWRITE_COLOR_COMPOSITE_EXCLUSION,
        Multiply = DWRITE_COLOR_COMPOSITE_MULTIPLY,

        // Non-separable color blend modes.
        HslHue = DWRITE_COLOR_COMPOSITE_HSL_HUE,
        HslSaturation = DWRITE_COLOR_COMPOSITE_HSL_SATURATION,
        HslColor = DWRITE_COLOR_COMPOSITE_HSL_COLOR,
        HslLuminosity = DWRITE_COLOR_COMPOSITE_HSL_LUMINOSITY
    };

    /// <summary>
    /// Identifies a type of paint element in a color glyph. A color glyph's visual representation
    /// is defined by a tree of paint elements. A paint element's properties are specified by a
    /// DWRITE_PAINT_ELEMENT structure, which combines a paint type an a union.
    /// </summary>
    /// <remarks>
    /// For more information about each paint type, see DWRITE_PAINT_ELEMENT. 
    /// </remarks>
    enum class PaintType : Int32
    {
        // The following paint types may be returned for color feature levels greater than
        // or equal to DWRITE_PAINT_FEATURE_LEVEL_COLR_V0.
        None = DWRITE_PAINT_TYPE_NONE,
        Layers = DWRITE_PAINT_TYPE_LAYERS,
        SolidGlyph = DWRITE_PAINT_TYPE_SOLID_GLYPH,

        // The following paint types may be returned for color feature levels greater than
        // or equal to DWRITE_PAINT_FEATURE_LEVEL_COLR_V1.
        Solid = DWRITE_PAINT_TYPE_SOLID,
        LinearGradient = DWRITE_PAINT_TYPE_LINEAR_GRADIENT,
        RadialGradient = DWRITE_PAINT_TYPE_RADIAL_GRADIENT,
        SweepGradient = DWRITE_PAINT_TYPE_SWEEP_GRADIENT,
        Glyph = DWRITE_PAINT_TYPE_GLYPH,
        ColorGlyph = DWRITE_PAINT_TYPE_COLOR_GLYPH,
        Transform = DWRITE_PAINT_TYPE_TRANSFORM,
        Composite = DWRITE_PAINT_TYPE_COMPOSITE
    };

    /// <summary>
    /// Specifies properties of a paint element, which is one node in a visual tree associated
    /// with a color glyph. This is passed as an output parameter to various IDWritePaintReader
    /// methods.
    /// </summary>
    /// <remarks>
    /// For a detailed description of how paint elements should be rendered, see the OpenType COLR
    /// table specification. Comments below reference the COLR paint record formats associated with
    /// each paint type.
    ///
    /// Note that this structure (and its size) may differ for different versions of the API, as
    /// newer versions may have additional union members for new paint types. For this reason,
    /// IDWritePaintReader methods that take a DWRITE_PAINT_ELEMENT output parameter also take a
    /// structSize parameter, for which the caller should specify actual size of the structure
    /// allocated by the caller, i.e., sizeof(DWRITE_PAINT_ELEMENT). Clients should use caution
    /// when passing DWRITE_PAINT_ELEMENT objects between components that may have been compiled
    /// against different versions of this header file.
    /// </remarks>
    struct PaintElement : public DWRITE_PAINT_ELEMENT
    {
        using Base = DWRITE_PAINT_ELEMENT;

        PaintElement( )
            : Base{}
        {}

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
            /// <returns>
            /// True if the table exists and was successfully retrieved; otherwise, false.
            /// </returns>
            bool Exists( ) const noexcept
            {
                return exists_ != FALSE;
            }


            /// <summary>
            /// Returns whether the table exists in the font face.
            /// </summary>
            /// <returns>
            /// True if the table exists and was successfully retrieved; otherwise, false.
            /// </returns>
            explicit operator bool( ) const noexcept
            {
                return Exists( );
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
        /// <example>
        /// <code language="cpp">
        /// // Get a specific font table (e.g., 'head' table)
        /// auto headTable = fontFace.GetFontTable( DWRITE_MAKE_OPENTYPE_TAG( 'h', 'e', 'a', 'd' ) );
        /// 
        /// if ( headTable )
        /// {
        ///     // Access as bytes
        ///     auto bytes = headTable.AsSpan<std::byte>();
        ///     
        ///     // Or access as a specific structure (if you have one defined)
        ///     // auto headers = headTable.AsSpan<FontHeadTable>();
        ///     
        ///     UINT32 tableSize = headTable.size();
        ///     const void* data = headTable.data();
        /// }
        /// // FontTable automatically released here
        /// </code>
        /// </example>
        FontTable GetFontTable( UINT32 openTypeTableTag ) const
        {
            return FontTable( *this, openTypeTableTag );
        }


        /// <summary>
        /// Computes the outline of a run of glyphs by calling back to the outline sink interface.
        /// </summary>
        /// <param name="emSize">
        /// Logical size of the font in DIP units. A DIP ("device-independent pixel") equals 1/96 inch.
        /// </param>
        /// <param name="glyphIndices">
        /// Array of glyph indices.
        /// </param>
        /// <param name="glyphAdvances">
        /// Optional array of glyph advances in DIPs.
        /// </param>
        /// <param name="glyphOffsets">
        /// Optional array of glyph offsets.
        /// </param>
        /// <param name="glyphCount">
        /// Number of glyphs.
        /// </param>
        /// <param name="isSideways">
        /// <para>
        /// If true, specifies that glyphs are rotated 90 degrees to the left and vertical 
        /// metrics are used.
        /// </para>
        /// <para>
        /// A client can render a vertical run by specifying `isSideways = true` and rotating 
        /// the resulting geometry 90 degrees to the right using a transform.
        /// </para>
        /// </param>
        /// <param name="isRightToLeft">
        /// If `true`, specifies that the advance direction is right to left. By default, 
        /// the advance direction is left to right.
        /// </param>
        /// <param name="geometrySink">
        /// Interface the function calls back to draw each element of the geometry.
        /// </param>
        void GetGlyphRunOutline( FLOAT emSize, UINT16 const* glyphIndices, FLOAT const* glyphAdvances, DWRITE_GLYPH_OFFSET const* glyphOffsets, UINT32 glyphCount, BOOL isSideways, BOOL isRightToLeft, IDWriteGeometrySink* geometrySink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetGlyphRunOutline( emSize, glyphIndices, glyphAdvances, glyphOffsets, glyphCount, isSideways, isRightToLeft, geometrySink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Determines the recommended rendering mode for the font given the 
        /// specified size and rendering parameters.
        /// </summary>
        /// <param name="emSize">
        /// Logical size of the font in DIP units. A DIP ("device-independent pixel") equals 1/96 inch.
        /// </param>
        /// <param name="pixelsPerDip">
        /// Number of physical pixels per DIP. For example, if the DPI of the rendering surface is 96 this 
        /// value is 1.0f. If the DPI is 120, this value is 120.0f/96.
        /// </param>
        /// <param name="measuringMode">
        /// Specifies measuring mode that will be used for glyphs in the font.
        /// Renderer implementations may choose different rendering modes for given measuring modes, but
        /// best results are seen when the corresponding modes match:
        /// DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL for DWRITE_MEASURING_MODE_NATURAL
        /// DWRITE_RENDERING_MODE_CLEARTYPE_GDI_CLASSIC for DWRITE_MEASURING_MODE_GDI_CLASSIC
        /// DWRITE_RENDERING_MODE_CLEARTYPE_GDI_NATURAL for DWRITE_MEASURING_MODE_GDI_NATURAL
        /// </param>
        /// <param name="renderingParams">
        /// Rendering parameters object. This parameter is necessary in case the 
        /// rendering parameters object overrides the rendering mode.
        /// </param>
        /// <param name="renderingMode">
        /// Receives the recommended rendering mode to use.
        /// </param>
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

        /// <summary>
        /// <para>
        /// Obtains design units and common metrics for the font face.
        /// </para>
        /// <para>
        /// These metrics are applicable to all the glyphs within a 
        /// fontface and are used by applications for layout calculations.
        /// </para>
        /// </summary>
        /// <param name="emSize">
        /// Logical size of the font in DIP units. A DIP ("device-independent 
        /// pixel") equals 1/96 inch.
        /// </param>
        /// <param name="pixelsPerDip">
        /// Number of physical pixels per DIP. For example, if the DPI of the 
        /// rendering surface is 96 this value is 1.0f. If the DPI is 120, 
        /// this value is 120.0f/96.
        /// </param>
        /// <param name="transform">
        /// Optional transform applied to the glyphs and their positions. 
        /// This transform is applied after the scaling specified by the 
        /// font size and pixelsPerDip.
        /// </param>
        /// <param name="fontFaceMetrics">
        /// Points to a DWRITE_FONT_METRICS structure to fill in. The metrics 
        /// returned by this function are in font design units.
        /// </param>
        void GetGdiCompatibleMetrics( FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_FONT_METRICS* fontFaceMetrics ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetGdiCompatibleMetrics( emSize, pixelsPerDip, transform, fontFaceMetrics );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// <para>
        /// Obtains glyph metrics in font design units with the return values 
        /// compatible with what GDI would produce.
        /// </para>
        /// <para>
        /// Glyphs metrics are used for positioning of individual glyphs.
        /// </para>
        /// </summary>
        /// <param name="emSize">
        /// Logical size of the font in DIP units. A DIP ("device-independent 
        /// pixel") equals 1/96 inch.
        /// </param>
        /// <param name="pixelsPerDip">
        /// Number of physical pixels per DIP. For example, if the DPI of the 
        /// rendering surface is 96 this value is 1.0f. If the DPI is 120, 
        /// this value is 120.0f/96.
        /// </param>
        /// <param name="transform">
        /// Optional transform applied to the glyphs and their positions. This 
        /// transform is applied after the scaling specified by the font size 
        /// and pixelsPerDip.
        /// </param>
        /// <param name="useGdiNatural">
        /// <para>
        /// When set to FALSE, the metrics are the same as the metrics of GDI 
        /// aliased text.
        /// </para>
        /// <para>
        /// When set to TRUE, the metrics are the same as the metrics of text 
        /// measured by GDI using a font created with CLEARTYPE_NATURAL_QUALITY.
        /// </para>
        /// </param>
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
        /// <para>
        /// Indicates whether the font is being used in a sideways run.
        /// </para>
        /// <para>
        /// This can affect the glyph metrics if the font has oblique simulation
        /// because sideways oblique simulation differs from non-sideways oblique 
        /// simulation.
        /// </para>
        /// </param>
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

        /// <summary>
        /// Creates a font file enumerator object that encapsulates a collection of font files.
        /// The font system calls back to this interface to create a font collection.
        /// </summary>
        /// <param name="factory">Factory associated with the loader.</param>
        /// <param name="collectionKey">Font collection key that uniquely identifies the collection of font files within
        /// the scope of the font collection loader being used.</param>
        /// <param name="collectionKeySize">Size of the font collection key in bytes.</param>
        /// <param name="fontFileEnumerator">Pointer to the newly created font file enumerator.</param>
        void CreateEnumeratorFromKey( IDWriteFactory* factory, void const* collectionKey, UINT32 collectionKeySize, IDWriteFontFileEnumerator** fontFileEnumerator ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateEnumeratorFromKey( factory, collectionKey, collectionKeySize, fontFileEnumerator );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        inline FontFileEnumerator CreateEnumeratorFromKey( IDWriteFactory* factory, void const* collectionKey, UINT32 collectionKeySize ) const;
    };

    /// <summary>
    /// Encapsulates a collection of font files. The font system uses this 
    /// interface to enumerate font files when building a font collection.
    /// </summary>
    class FontFileEnumerator : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFileEnumerator, Unknown, IDWriteFontFileEnumerator, IUnknown )

        void MoveNext( BOOL* hasCurrentFile ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->MoveNext( hasCurrentFile );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        bool MoveNext( ) const
        {
            BOOL hasCurrentFile = FALSE;
            MoveNext( &hasCurrentFile );
            return hasCurrentFile != FALSE;
        }

        void GetCurrentFontFile( IDWriteFontFile** fontFile ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetCurrentFontFile( fontFile );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        FontFile GetCurrentFontFile( ) const
        {
            IDWriteFontFile* fontFile = nullptr;
            GetCurrentFontFile( &fontFile );
            FontFile result( fontFile );
            return result;
        }
    };

    inline FontFileEnumerator FontCollectionLoader::CreateEnumeratorFromKey( IDWriteFactory* factory, void const* collectionKey, UINT32 collectionKeySize ) const
    {
        IDWriteFontFileEnumerator* fontFileEnumerator = nullptr;
        CreateEnumeratorFromKey( factory, collectionKey, collectionKeySize, &fontFileEnumerator );
        
        FontFileEnumerator result( fontFileEnumerator );
        return result;
    }


    /// <summary>
    /// Represents a collection of strings indexed by locale name.
    /// </summary>
    class LocalizedStrings : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( LocalizedStrings, Unknown, IDWriteLocalizedStrings, IUnknown )

        /// <summary>
        /// Gets the number of language/string pairs.
        /// </summary>
        UINT32 GetCount( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetCount( );
        }

        /// <summary>
        /// Gets the index of the item with the specified locale name.
        /// </summary>
        /// <param name="localeName">
        /// Locale name to look for.
        /// </param>
        /// <param name="index">
        /// Receives the zero-based index of the locale name/string pair.
        /// </param>
        /// <param name="exists">
        /// Receives `TRUE` if the locale name exists or `FALSE` if not.
        /// </param>
        void FindLocaleName( WCHAR const* localeName, UINT32* index, BOOL* exists ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->FindLocaleName( localeName, index, exists );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the index of the item with the specified locale name.
        /// </summary>
        /// <typeparam name="StringT">
        /// The type of the string.
        /// </typeparam>
        /// <param name="localeName">
        /// Locale name to look for.
        /// </param>
        /// <param name="index">
        /// Receives the zero-based index of the locale name/string pair.
        /// </param>
        /// <param name="exists">
        /// Receives `TRUE` if the locale name exists or `FALSE` if not.
        /// </param>
        template<WideStringLike StringT>
        void FindLocaleName( const StringT& localeName, UINT32* index, BOOL* exists ) const
        {
            FindLocaleName( localeName.c_str( ), index, exists );
        }

        /// <summary>
        /// Gets the index of the item with the specified locale name.
        /// </summary>
        /// <param name="localeName">
        /// Locale name to look for.
        /// </param>
        /// <param name="index">
        /// Receives the zero-based index of the locale name/string pair.
        /// </param>
        /// <returns>
        /// `true` if the locale name exists or `false` if not.
        /// </returns>
        bool FindLocaleName( WCHAR const* localeName, UINT32* index ) const
        {
            BOOL exists = FALSE;
            FindLocaleName( localeName, index, &exists );
            return exists != FALSE;
        }

        /// <summary>
        /// Gets the index of the item with the specified locale name.
        /// </summary>
        /// <typeparam name="StringT">
        /// The type of the string.
        /// </typeparam>
        /// <param name="localeName">
        /// Locale name to look for.
        /// </param>
        /// <param name="index">
        /// Receives the zero-based index of the locale name/string pair.
        /// </param>
        /// <returns>
        /// `true` if the locale name exists or `false` if not.
        /// </returns>
        template<WideStringLike StringT>
        bool FindLocaleName( const StringT& localeName, UINT32* index ) const
        {
            return FindLocaleName( localeName.c_str( ), index );
        }


        /// <summary>
        /// Gets the index of the item with the specified locale name.
        /// </summary>
        /// <param name="localeName">
        /// Locale name to look for.
        /// </param>
        /// <returns>
        /// `std::optional<UINT32>` containing the index if the locale name exists, or `std::nullopt` if not.
        /// </returns>
        std::optional<UINT32> FindLocaleName( WCHAR const* localeName ) const
        {
            UINT32 index = 0;
            BOOL exists = FALSE;
            FindLocaleName( localeName, &index, &exists );
            if ( exists )
            { 
                return index;
            }
            else
            {
                return std::nullopt;
            }
        }

        /// <summary>
        /// Gets the index of the item with the specified locale name.
        /// </summary>
        /// <typeparam name="StringT">
        /// The type of the string.
        /// </typeparam>
        /// <param name="localeName">
        /// Locale name to look for.
        /// </param>
        /// <returns>
        /// `std::optional<UINT32>` containing the index if the locale name exists, or `std::nullopt` if not.
        /// </returns>
        template<WideStringLike StringT>
        std::optional<UINT32> FindLocaleName( const StringT& localeName ) const
        {
            return FindLocaleName( localeName.c_str( ) );
        }


        /// <summary>
        /// Gets the length in characters (not including the null terminator) 
        /// of the locale name with the specified index.
        /// </summary>
        /// <param name="index">
        /// Zero-based index of the locale name.
        /// </param>
        /// <param name="length">
        /// Receives the length in characters, not including the null terminator.
        /// </param>
        void GetLocaleNameLength( UINT32 index, UINT32* length ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetLocaleNameLength( index, length );
            
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the length in characters (not including the null terminator) 
        /// of the locale name with the specified index.
        /// </summary>
        /// <param name="index">
        /// Zero-based index of the locale name.
        /// </param>
        /// <returns>
        /// The length in characters, not including the null terminator.
        /// </returns>
        UINT32 GetLocaleNameLength( UINT32 index ) const
        {
            UINT32 result = 0;
            GetLocaleNameLength( index, &result );
            return result;
        }

        /// <summary>
        /// Copies the locale name with the specified index to the specified array.
        /// </summary>
        /// <param name="index">
        /// Zero-based index of the locale name.
        /// </param>
        /// <param name="localeName">
        /// Character array that receives the locale name.
        /// </param>
        /// <param name="size">
        /// Size of the array in characters. The size must include space for the terminating
        /// null character.
        /// </param>
        void GetLocaleName( UINT32 index, WCHAR* localeName, UINT32 size ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetLocaleName( index, localeName, size );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the locale name with the specified index.
        /// </summary>
        /// <typeparam name="StringT">
        /// The type of the string.
        /// </typeparam>
        /// <param name="index">
        /// Zero-based index of the locale name.
        /// </param>
        /// <returns>
        /// The locale name.
        /// </returns>
        template<WideStringLike StringT = WideString>
        StringT GetLocaleName( UINT32 index ) const
        {
            UINT32 size = GetLocaleNameLength( index );
            StringT result;
            result.resize( size );
            GetLocaleName( index, result.data( ), size + 1 );
            return result;
        }

        /// <summary>
        /// Gets the length in characters (not including the null terminator) of 
        /// the string with the specified index.
        /// </summary>
        /// <param name="index">
        /// Zero-based index of the string.
        /// </param>
        /// <param name="length">
        /// Receives the length in characters, not including the null terminator.
        /// </param>
        void GetStringLength( UINT32 index, UINT32* length ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetStringLength( index, length );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the length in characters (not including the null terminator) of 
        /// the string with the specified index.
        /// </summary>
        /// <param name="index">
        /// Zero-based index of the string.
        /// </param>
        /// <returns>
        /// The length in characters, not including the null terminator.
        /// </returns>
        UINT32 GetStringLength( UINT32 index ) const
        {
            UINT32 result = 0;
            GetStringLength( index, &result );
            return result;
        }
        /// <summary>
        /// Copies the string with the specified index to the specified array.
        /// </summary>
        /// <param name="index">
        /// Zero-based index of the string.
        /// </param>
        /// <param name="stringBuffer">
        /// Character array that receives the string.
        /// </param>
        /// <param name="size">
        /// Size of the array in characters. The size must include space for the terminating
        /// null character.
        /// </param>
        void GetString( UINT32 index, WCHAR* stringBuffer, UINT32 size ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetString( index, stringBuffer, size );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the string with the specified index.
        /// </summary>
        /// <typeparam name="StringT">
        /// The type of the string.
        /// </typeparam>
        /// <param name="index">
        /// Zero-based index of the string.
        /// </param>
        /// <returns>
        /// The string.
        /// </returns>
        template<WideStringLike StringT = WideString>
        StringT GetString( UINT32 index ) const
        {
            UINT32 size = GetStringLength( index );
            StringT result;
            result.resize( size );
            GetString( index, result.data( ), size + 1 );
            return result;
        }
    };


    namespace Internal
    {
        class FontCollectionIterator;
    }


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
        using Base = Unknown;
        using Iterator = Internal::FontCollectionIterator;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontCollection, Unknown, IDWriteFontCollection, IUnknown )

        UINT32 GetFontFamilyCount( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFontFamilyCount( );
        }

        void GetFontFamily( UINT32 index, IDWriteFontFamily** fontFamily ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontFamily( index, fontFamily );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        inline FontFamily GetFontFamily( UINT32 index ) const;
        inline std::vector<FontFamily> GetFontFamilies( ) const;

        void FindFamilyName( WCHAR const* familyName, UINT32* index, BOOL* exists ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->FindFamilyName( familyName, index, exists );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool FindFamilyName( WCHAR const* familyName, UINT32* index ) const
        {
            BOOL exists = FALSE;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->FindFamilyName( familyName, index, &exists );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return exists != FALSE;
        }

        void GetFontFromFontFace( IDWriteFontFace* fontFace, IDWriteFont** font ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontFromFontFace( fontFace, font );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        inline Font GetFontFromFontFace( IDWriteFontFace* fontFace ) const;

        /// <summary>
        /// Returns an iterator to the first font family in the font collection.
        /// </summary>
        /// <returns>An iterator pointing to the first font family.</returns>
        inline Iterator begin( ) const noexcept;

        /// <summary>
        /// Returns an iterator past the last font family in the font collection.
        /// </summary>
        /// <returns>An iterator pointing past the last font family.</returns>
        inline Iterator end( ) const noexcept;

        /// <summary>
        /// Returns a reverse iterator to the last font family in the font collection.
        /// </summary>
        /// <returns>A reverse iterator pointing to the last font family.</returns>
        inline std::reverse_iterator<Iterator> rbegin( ) const noexcept;

        /// <summary>
        /// Returns a reverse iterator before the first font family in the font collection.
        /// </summary>
        /// <returns>A reverse iterator pointing before the first font family.</returns>
        inline std::reverse_iterator<Iterator> rend( ) const noexcept;


    };


    namespace Internal
    {
        class FontListIterator;
    }


    /// <summary>
    /// Represents a list of fonts.
    /// </summary>
    class FontList : public Unknown
    {
    public:
        using Base = Unknown;
        using Iterator = Internal::FontListIterator;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontList, Unknown, IDWriteFontList, IUnknown )

        /// <summary>
        /// Gets the font collection that contains the fonts.
        /// </summary>
        /// <param name="fontCollection">
        /// Receives a pointer to the font collection object.
        /// </param>
        void GetFontCollection( IDWriteFontCollection** fontCollection ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontCollection( fontCollection );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        /// <summary>
        /// Gets the font collection that contains the fonts.
        /// </summary>
        /// <returns>
        /// A FontCollection object that represents the font collection.
        /// </returns>
        FontCollection GetFontCollection( ) const
        {
            IDWriteFontCollection* fontCollection = nullptr;
            GetFontCollection( &fontCollection );
            FontCollection result( fontCollection );
            return result;
        }

        /// <summary>
        /// Gets the number of fonts in the font list.
        /// </summary>
        UINT32 GetFontCount( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFontCount( );
        }

        /// <summary>
        /// Gets a font given its zero-based index.
        /// </summary>
        /// <param name="index">
        /// Zero-based index of the font in the font list.
        /// </param>
        /// <param name="font">
        /// Receives a pointer to the newly created font object.
        /// </param>
        void GetFont( UINT32 index, IDWriteFont** font ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFont( index, font );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        /// <summary>
        /// Gets a font given its zero-based index.
        /// </summary>
        /// <param name="index">
        /// Zero-based index of the font in the font list.
        /// </param>
        /// <returns>
        /// A Font object that represents the font.
        /// </returns>
        inline Font GetFont( UINT32 index ) const;

        /// <summary>
        /// Gets all fonts in the font list.
        /// </summary>
        /// <returns>
        /// A vector of Font objects that represent the fonts.
        /// </returns>
        inline std::vector<Font> GetFonts( ) const;

        /// <summary>
        /// Returns an iterator to the first font in the font list.
        /// </summary>
        /// <returns>An iterator pointing to the first font.</returns>
        inline Iterator begin( ) const noexcept;

        /// <summary>
        /// Returns an iterator past the last font in the font list.
        /// </summary>
        /// <returns>An iterator pointing past the last font.</returns>
        inline Iterator end( ) const noexcept;

        /// <summary>
        /// Returns a reverse iterator to the last font in the font list.
        /// </summary>
        /// <returns>A reverse iterator pointing to the last font.</returns>
        inline std::reverse_iterator<Iterator> rbegin( ) const noexcept;

        /// <summary>
        /// Returns a reverse iterator before the first font in the font list.
        /// </summary>
        /// <returns>A reverse iterator pointing before the first font.</returns>
        inline std::reverse_iterator<Iterator> rend( ) const noexcept;


    };

    /// <summary>
    /// Represents a family of related fonts.
    /// </summary>
    class FontFamily : public FontList
    {
    public:
        using Base = FontList;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFamily, FontList, IDWriteFontFamily, IDWriteFontList )

        /// <summary>
        /// Creates a localized strings object that contains the family names for the font family, indexed by locale name.
        /// </summary>
        /// <param name="names">
        /// Receives a pointer to the newly created localized strings object.
        /// </param>
        void GetFamilyNames( IDWriteLocalizedStrings** names ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFamilyNames( names );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Creates a localized strings object that contains the family names for the font family, indexed by locale name.
        /// </summary>
        /// <returns>
        /// A LocalizedStrings object that represents the family names.
        /// </returns>
        LocalizedStrings GetFamilyNames( ) const
        {
            IDWriteLocalizedStrings* names = nullptr;
            GetFamilyNames( &names );
            LocalizedStrings result( names );
            return result;
        }

        /// <summary>
        /// Gets the font that best matches the specified properties.
        /// </summary>
        /// <param name="weight">The requested weight of the font.</param>
        /// <param name="stretch">The requested stretch of the font.</param>
        /// <param name="style">The requested style of the font.</param>
        /// <param name="matchingFont">Receives a pointer to the matching font.</param>
        void GetFirstMatchingFont( DWRITE_FONT_WEIGHT  weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style, IDWriteFont** matchingFont ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFirstMatchingFont( weight, stretch, style, matchingFont );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the font that best matches the specified properties.
        /// </summary>
        /// <param name="weight">The requested weight of the font.</param>
        /// <param name="stretch">The requested stretch of the font.</param>
        /// <param name="style">The requested style of the font.</param>
        /// <param name="matchingFont">Receives a pointer to the matching font.</param>
        void GetFirstMatchingFont( FontWeight weight, FontStretch stretch, FontStyle style, IDWriteFont** matchingFont ) const
        {
            GetFirstMatchingFont( static_cast< DWRITE_FONT_WEIGHT >( weight ), static_cast< DWRITE_FONT_STRETCH >( stretch ), static_cast< DWRITE_FONT_STYLE >( style ), matchingFont );
        }

        /// <summary>
        /// Gets the font that best matches the specified properties.
        /// </summary>
        /// <param name="weight">The requested weight of the font.</param>
        /// <param name="stretch">The requested stretch of the font.</param>
        /// <param name="style">The requested style of the font.</param>
        /// <returns>
        /// A Font object that represents the matching font.
        /// </returns>
        inline Font GetFirstMatchingFont( DWRITE_FONT_WEIGHT  weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style ) const;
        
        /// <summary>
        /// Gets the font that best matches the specified properties.
        /// </summary>
        /// <param name="weight">The requested weight of the font.</param>
        /// <param name="stretch">The requested stretch of the font.</param>
        /// <param name="style">The requested style of the font.</param>
        /// <returns>
        /// A Font object that represents the matching font.
        /// </returns>
        inline Font GetFirstMatchingFont( FontWeight weight, FontStretch stretch, FontStyle style ) const;

        /// <summary>
        /// Gets a list of fonts in the font family ranked in order of how well they match the specified properties.
        /// </summary>
        /// <param name="weight">The requested font weight.</param>
        /// <param name="stretch">The requested font stretch.</param>
        /// <param name="style">The requested font style.</param>
        /// <param name="matchingFonts">Receives a pointer to the list of matching fonts.</param>
        void GetMatchingFonts( DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style, IDWriteFontList** matchingFonts ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetMatchingFonts( weight, stretch, style, matchingFonts );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets a list of fonts in the font family ranked in order of how well they match the specified properties.
        /// </summary>
        /// <param name="weight">The requested font weight.</param>
        /// <param name="stretch">The requested font stretch.</param>
        /// <param name="style">The requested font style.</param>
        /// <param name="matchingFonts">Receives a pointer to the list of matching fonts.</param>
        void GetMatchingFonts( FontWeight weight, FontStretch stretch, FontStyle style, IDWriteFontList** matchingFonts ) const
        {
            GetMatchingFonts( static_cast< DWRITE_FONT_WEIGHT >( weight ), static_cast< DWRITE_FONT_STRETCH >( stretch ), static_cast< DWRITE_FONT_STYLE >( style ), matchingFonts );
        }

        /// <summary>
        /// Gets a list of fonts in the font family ranked in order of how well they match the specified properties.
        /// </summary>
        /// <param name="weight">The requested font weight.</param>
        /// <param name="stretch">The requested font stretch.</param>
        /// <param name="style">The requested font style.</param>
        /// <returns>A FontList object that represents the matching fonts.</returns>
        inline FontList GetMatchingFonts( DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style ) const;

        /// <summary>
        /// Gets a list of fonts in the font family ranked in order of how well they match the specified properties.
        /// </summary>
        /// <param name="weight">The requested font weight.</param>
        /// <param name="stretch">The requested font stretch.</param>
        /// <param name="style">The requested font style.</param>
        /// <returns>A FontList object that represents the matching fonts.</returns>
        inline FontList GetMatchingFonts( FontWeight weight, FontStretch stretch, FontStyle style ) const;
    };

    namespace Internal
    {
        struct FontCollectionTraits
        {
            using ListType = FontCollection;
            using ItemType = FontFamily;
            using IndexType = UInt32;

            static IndexType Count( const ListType& list )
            {
                return list.GetFontFamilyCount( );
            }

            static ItemType At( const ListType& list, IndexType index )
            {
                return list.GetFontFamily( index );
            }
        };

        /// <summary>
        /// A random access iterator for iterating over font families in the font collection.
        /// </summary>
        class FontCollectionIterator : public Com::Internal::ListIterator<FontCollectionTraits>
        {
        public:
            using Base = Com::Internal::ListIterator<FontCollectionTraits>;
            // Inherit constructors
            using Base::Base;
        };
    }


    inline FontCollection::Iterator FontCollection::begin( ) const noexcept
    {
        return Iterator( this, 0 );
    }

    inline FontCollection::Iterator FontCollection::end( ) const noexcept
    {
        return Iterator( this, GetFontFamilyCount( ) );
    }

    inline std::reverse_iterator<FontCollection::Iterator> FontCollection::rbegin( ) const noexcept
    {
        return std::reverse_iterator<Iterator>( end( ) );
    }

    inline std::reverse_iterator<FontCollection::Iterator> FontCollection::rend( ) const noexcept
    {
        return std::reverse_iterator<Iterator>( begin( ) );
    }




    inline FontFamily FontCollection::GetFontFamily( UINT32 index ) const
    {
        IDWriteFontFamily* fontFamily = nullptr;
        GetFontFamily( index, &fontFamily );
        FontFamily result( fontFamily );
        return result;
    }

    inline std::vector<FontFamily> FontCollection::GetFontFamilies( ) const
    {
        std::vector<FontFamily>::size_type fontFamilyCount = GetFontFamilyCount( );
        std::vector<FontFamily> result( fontFamilyCount );
        for ( UINT32 i = 0; i < fontFamilyCount; i++ )
        {
            FontFamily writeFontFamily = GetFontFamily( i );
            result.emplace_back( std::move( writeFontFamily ) );
        }
        return result;
    }


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

        /// <summary>
        /// Gets the font family to which the specified font belongs.
        /// </summary>
        /// <param name="fontFamily">Receives a pointer to the font family object.</param>
        void GetFontFamily( IDWriteFontFamily** fontFamily ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontFamily( fontFamily );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the font family to which the specified font belongs.
        /// </summary>
        /// <returns>A FontFamily object that represents the font family.</returns>
        FontFamily GetFontFamily( ) const
        {
            IDWriteFontFamily* fontFamily = nullptr;
            GetFontFamily( &fontFamily );
            FontFamily result( fontFamily );
            return result;
        }

        /// <summary>
        /// Gets the weight of the specified font.
        /// </summary>
        /// <returns>The weight of the font.</returns>
        DWRITE_FONT_WEIGHT GetWeight( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetWeight( );
        }

        /// <summary>
        /// Gets the weight of the specified font.
        /// </summary>
        /// <returns>The weight of the font.</returns>
        FontWeight Weight( ) const
        {
            return static_cast< FontWeight >( GetWeight( ) );
        }

        /// <summary>
        /// Gets the stretch (aka. width) of the specified font.
        /// </summary>
        /// <returns>The stretch of the font.</returns>
        DWRITE_FONT_STRETCH GetStretch( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetStretch( );
        }

        /// <summary>
        /// Gets the stretch (aka. width) of the specified font.
        /// </summary>
        /// <returns>The stretch of the font.</returns>
        FontStretch Stretch( ) const
        {
            return static_cast< FontStretch >( GetStretch( ) );
        }

        /// <summary>
        /// Gets the style (aka. slope) of the specified font.
        /// </summary>
        /// <returns>The style of the font.</returns>
        DWRITE_FONT_STYLE GetStyle( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetStyle( );
        }

        /// <summary>
        /// Gets the style (aka. slope) of the specified font.
        /// </summary>
        /// <returns>The style of the font.</returns>
        FontStyle Style( ) const
        {
            return static_cast< FontStyle >( GetStyle( ) );
        }

        /// <summary>
        /// Determines whether the specified font is a symbol font.
        /// </summary>
        /// <returns>true if the font is a symbol font; otherwise, false.</returns>
        bool IsSymbolFont( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsSymbolFont( ) != FALSE;
        }

        /// <summary>
        /// Gets a localized strings collection containing the face names 
        /// for the font (e.g., Regular or Bold), indexed by locale name.
        /// </summary>
        /// <param name="names">Receives a pointer to the newly created localized strings object.</param>
        void GetFaceNames( IDWriteLocalizedStrings** names ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFaceNames( names );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets a localized strings collection containing the face names 
        /// for the font (e.g., Regular or Bold), indexed by locale name.
        /// </summary>
        /// <returns>A localized strings object containing the face names for the font.</returns>
        LocalizedStrings GetFaceNames( ) const
        {
            IDWriteLocalizedStrings* names = nullptr;
            GetFaceNames( &names );
            LocalizedStrings result( names );
            return result;
        }

        /// <summary>
        /// Gets a localized strings collection containing the specified informational strings, indexed by locale name.
        /// </summary>
        /// <param name="informationalStringID">The ID of the informational string to retrieve.</param>
        /// <param name="informationalStrings">Receives a pointer to the newly created localized strings object.</param>
        /// <param name="exists">Receives a boolean value indicating whether the informational string exists.</param>
        void GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_ID informationalStringID, IDWriteLocalizedStrings** informationalStrings, BOOL* exists ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetInformationalStrings( informationalStringID, informationalStrings, exists );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets a localized strings collection containing the specified informational strings, indexed by locale name.
        /// </summary>
        /// <param name="informationalStringID">The ID of the informational string to retrieve.</param>
        /// <param name="informationalStrings">Receives a pointer to the newly created localized strings object.</param>
        /// <param name="exists">Receives a boolean value indicating whether the informational string exists.</param>
        void GetInformationalStrings( InformationalStringId informationalStringID, IDWriteLocalizedStrings** informationalStrings, BOOL* exists ) const
        {
            GetInformationalStrings( static_cast< DWRITE_INFORMATIONAL_STRING_ID >( informationalStringID ), informationalStrings, exists );
        }

        /// <summary>
        /// Gets a localized strings collection containing the specified informational strings, indexed by locale name.
        /// </summary>
        /// <param name="informationalStringID">The ID of the informational string to retrieve.</param>
        /// <returns>A localized strings object containing the specified informational strings, or std::nullopt if the informational string does not exist.</returns>
        std::optional<LocalizedStrings> GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_ID informationalStringID ) const
        {
            IDWriteLocalizedStrings* informationalStrings = nullptr;
            BOOL exists = FALSE;
            GetInformationalStrings( informationalStringID, &informationalStrings, &exists );
            if ( exists )
            {
                LocalizedStrings result( informationalStrings );
                return result;
            }
            else
            {
                return std::nullopt;
            }
        }

        /// <summary>
        /// Gets a localized strings collection containing the specified informational strings, indexed by locale name.
        /// </summary>
        /// <param name="informationalStringID">The ID of the informational string to retrieve.</param>
        /// <returns>A localized strings object containing the specified informational strings, or std::nullopt if the informational string does not exist.</returns>
        std::optional<LocalizedStrings> GetInformationalStrings( InformationalStringId informationalStringID ) const
        {
            return GetInformationalStrings( static_cast< DWRITE_INFORMATIONAL_STRING_ID >( informationalStringID ) );
        }

        /// <summary>
        /// Gets a value that indicates what simulation are applied to the specified font.
        /// </summary>
        /// <returns>
        /// A value that indicates what simulation are applied to the specified font.
        /// </returns>
        DWRITE_FONT_SIMULATIONS GetSimulations( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetSimulations( );
        }

        /// <summary>
        /// Gets a value that indicates what simulation are applied to the specified font.
        /// </summary>
        /// <returns>
        /// A value that indicates what simulation are applied to the specified font.
        /// </returns>
        FontSimulation Simulations( ) const
        {
            return static_cast< FontSimulation >( GetSimulations( ) );
        }


        /// <summary>
        /// Gets the metrics for the font.
        /// </summary>
        /// <param name="fontMetrics">A pointer to a DWRITE_FONT_METRICS structure that receives the font metrics.</param>
        void GetMetrics( DWRITE_FONT_METRICS* fontMetrics ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetMetrics( fontMetrics );
        }

        /// <summary>
        /// Gets the metrics for the font.
        /// </summary>
        /// <returns>A FontMetrics object containing the metrics for the font.</returns>
        FontMetrics GetMetrics( ) const
        {
            FontMetrics metrics;
            GetMetrics( &metrics );
            return metrics;
        }


        /// <summary>
        /// Determines whether the font supports the specified character.
        /// </summary>
        /// <param name="unicodeValue">The Unicode (UCS-4) value of the character to check.</param>
        /// <param name="exists">A pointer to a BOOL that receives TRUE if the font supports the character, or FALSE otherwise.</param>
        void HasCharacter( UINT32 unicodeValue, BOOL* exists ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->HasCharacter( unicodeValue, exists );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Determines whether the font supports the specified character.
        /// </summary>
        /// <param name="unicodeValue">The Unicode (UCS-4) value of the character to check.</param>
        /// <returns>True if the font supports the character, false otherwise.</returns>
        bool HasCharacter( UINT32 unicodeValue ) const
        {
            BOOL exists = FALSE;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->HasCharacter( unicodeValue, &exists );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return exists != FALSE;
        }

        /// <summary>
        /// Creates a font face object for the font.
        /// </summary>
        /// <param name="fontFace">A pointer to an IDWriteFontFace interface that receives the font face object.</param>
        void CreateFontFace( IDWriteFontFace** fontFace ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateFontFace( fontFace );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        /// <summary>
        /// Creates a font face object for the font.
        /// </summary>
        /// <returns>A FontFace object representing the font face.</returns>
        FontFace CreateFontFace( ) const
        {
            IDWriteFontFace* fontFace = nullptr;
            CreateFontFace( &fontFace );
            FontFace result( fontFace );
            return result;
        }
    };

    inline Font FontCollection::GetFontFromFontFace( IDWriteFontFace* fontFace ) const
    {
        IDWriteFont* font = nullptr;
        GetFontFromFontFace( fontFace, &font );
        Font result( font );
        return result;
    }

    inline Font FontList::GetFont( UINT32 index ) const
    {
        IDWriteFont* font;
        GetFont( index, &font );
        Font result( font );
        return result;
    }

    inline std::vector<Font> FontList::GetFonts( ) const
    {
        std::vector<Font>::size_type fontCount = GetFontCount( );
        std::vector<Font> result( fontCount );
        for ( UINT32 i = 0; i < fontCount; i++ )
        {
            Font writeFont = GetFont( i );
            result.emplace_back( std::move( writeFont ) );
        }
        return result;
    }

    inline Font FontFamily::GetFirstMatchingFont( DWRITE_FONT_WEIGHT  weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style ) const
    {
        IDWriteFont* matchingFont = nullptr;
        GetFirstMatchingFont( weight, stretch, style, &matchingFont );
        Font result( matchingFont );
        return result;
    }
    inline Font FontFamily::GetFirstMatchingFont( FontWeight weight, FontStretch stretch, FontStyle style ) const
    {
        return GetFirstMatchingFont( static_cast< DWRITE_FONT_WEIGHT >( weight ), static_cast< DWRITE_FONT_STRETCH >( stretch ), static_cast< DWRITE_FONT_STYLE >( style ) );
    }

    inline FontList FontFamily::GetMatchingFonts( DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STRETCH stretch, DWRITE_FONT_STYLE style ) const
    {
        IDWriteFontList* matchingFonts = nullptr;
        GetMatchingFonts( weight, stretch, style, &matchingFonts );
        FontList result( matchingFonts );
        return result;
    }
    inline FontList FontFamily::GetMatchingFonts( FontWeight weight, FontStretch stretch, FontStyle style ) const
    {
        return GetMatchingFonts( static_cast< DWRITE_FONT_WEIGHT >( weight ), static_cast< DWRITE_FONT_STRETCH >( stretch ), static_cast< DWRITE_FONT_STYLE >( style ) );
    }


    namespace Internal
    {
        struct FontListTraits
        {
            using ListType = FontList;
            using ItemType = Font;
            using IndexType = UInt32;

            static IndexType Count( const ListType& list )
            {
                return list.GetFontCount( );
            }

            static ItemType At( const ListType& list, IndexType index )
            {
                return list.GetFont( index );
            }
        };

        /// <summary>
        /// A random access iterator for iterating over fonts in the font list.
        /// </summary>
        class FontListIterator : public Com::Internal::ListIterator<FontListTraits>
        {
        public:
            using Base = Com::Internal::ListIterator<FontListTraits>;
            // Inherit constructors
            using Base::Base; 
        };

    }

    inline FontList::Iterator FontList::begin( ) const noexcept
    {
        return Iterator( this, 0 );
    }

    inline FontList::Iterator FontList::end( ) const noexcept
    {
        return Iterator( this, GetFontCount( ) );
    }

    inline std::reverse_iterator<FontList::Iterator> FontList::rbegin( ) const noexcept
    {
        return std::reverse_iterator<Iterator>( end( ) );
    }

    inline std::reverse_iterator<FontList::Iterator> FontList::rend( ) const noexcept
    {
        return std::reverse_iterator<Iterator>( begin( ) );
    }



    class InlineObject;
    /// <summary>
    /// The TextFormat class describes the font and paragraph properties 
    /// used to format text, and it describes locale information.
    /// </summary>
    class TextFormat : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextFormat, Unknown, IDWriteTextFormat, IUnknown )

        /// <summary>
        /// Set alignment option of text relative to layout box's leading and trailing edge.
        /// </summary>
        /// <param name="textAlignment">
        /// The text alignment option.
        /// </param>
        void SetTextAlignment( DWRITE_TEXT_ALIGNMENT textAlignment ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetTextAlignment( textAlignment );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        /// <summary>
        /// Set alignment option of text relative to layout box's leading and trailing edge.
        /// </summary>
        /// <param name="textAlignment">
        /// The text alignment option.
        /// </param>
        void SetTextAlignment( TextAlignment textAlignment ) const
        {
            SetTextAlignment( static_cast< DWRITE_TEXT_ALIGNMENT >( textAlignment ) );
        }
        /// <summary>
        /// Set alignment option of paragraph relative to layout box's top and bottom edge.
        /// </summary>
        /// <param name="paragraphAlignment">
        /// The paragraph alignment option.
        /// </param>
        void SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetParagraphAlignment( paragraphAlignment );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        /// <summary>
        /// Set alignment option of paragraph relative to layout box's top and bottom edge.
        /// </summary>
        /// <param name="paragraphAlignment">
        /// The paragraph alignment option.
        /// </param>
        void SetParagraphAlignment( ParagraphAlignment paragraphAlignment ) const
        {
            SetParagraphAlignment( static_cast< DWRITE_PARAGRAPH_ALIGNMENT >( paragraphAlignment ) );
        }

        /// <summary>
        /// Set word wrapping option.
        /// </summary>
        /// <param name="wordWrapping">
        /// The word wrapping option.
        /// </param>
        void SetWordWrapping( DWRITE_WORD_WRAPPING wordWrapping ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetWordWrapping( wordWrapping );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        /// <summary>
        /// Set word wrapping option.
        /// </summary>
        /// <param name="wordWrapping">
        /// The word wrapping option.
        /// </param>
        void SetWordWrapping( WordWrapping wordWrapping ) const
        {
            SetWordWrapping( static_cast< DWRITE_WORD_WRAPPING >( wordWrapping ) );
        }

        /// <summary>
        /// Set paragraph reading direction.
        /// </summary>
        /// <param name="readingDirection">
        /// The paragraph reading direction option.
        /// </param>
        /// <remarks>
        /// The flow direction must be perpendicular to the reading direction.
        /// Setting both to a vertical direction or both to horizontal yields
        /// DWRITE_E_FLOWDIRECTIONCONFLICTS when calling GetMetrics or Draw.
        /// </remarks>
        void SetReadingDirection( DWRITE_READING_DIRECTION readingDirection ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetReadingDirection( readingDirection );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        /// <summary>
        /// Set paragraph reading direction.
        /// </summary>
        /// <param name="readingDirection">
        /// The paragraph reading direction option.
        /// </param>
        /// <remarks>
        /// The flow direction must be perpendicular to the reading direction.
        /// Setting both to a vertical direction or both to horizontal yields
        /// DWRITE_E_FLOWDIRECTIONCONFLICTS when calling GetMetrics or Draw.
        /// </remarks>
        void SetReadingDirection( ReadingDirection readingDirection ) const
        {
            SetReadingDirection( static_cast< DWRITE_READING_DIRECTION >( readingDirection ) );
        }
        /// <summary>
        /// Set paragraph flow direction.
        /// </summary>
        /// <param name="flowDirection">
        /// The paragraph flow direction option.
        /// </param>
        /// <remarks>
        /// The flow direction must be perpendicular to the reading direction.
        /// Setting both to a vertical direction or both to horizontal yields
        /// DWRITE_E_FLOWDIRECTIONCONFLICTS when calling GetMetrics or Draw.
        /// </remarks>
        void SetFlowDirection( DWRITE_FLOW_DIRECTION flowDirection ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetFlowDirection( flowDirection );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        /// <summary>
        /// Set paragraph flow direction.
        /// </summary>
        /// <param name="flowDirection">
        /// The paragraph flow direction option.
        /// </param>
        /// <remarks>
        /// The flow direction must be perpendicular to the reading direction.
        /// Setting both to a vertical direction or both to horizontal yields
        /// DWRITE_E_FLOWDIRECTIONCONFLICTS when calling GetMetrics or Draw.
        /// </remarks>
        void SetFlowDirection( FlowDirection flowDirection ) const
        {
            SetFlowDirection( static_cast< DWRITE_FLOW_DIRECTION >( flowDirection ) );
        }

        /// <summary>
        /// Set incremental tab stop position.
        /// </summary>
        /// <param name="incrementalTabStop">
        /// The position of the incremental tab stop.
        /// </param>
        void SetIncrementalTabStop( FLOAT incrementalTabStop ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetIncrementalTabStop( incrementalTabStop );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Set trimming options for any trailing text exceeding the layout width
        /// or for any far text exceeding the layout height.
        /// </summary>
        /// <param name="trimmingOptions">
        /// Text trimming options.
        /// </param>
        /// <param name="trimmingSign">
        /// Application-defined omission sign. This parameter may be NULL if no trimming sign is desired.
        /// </param>
        /// <remarks>
        /// Any inline object can be used for the trimming sign, but CreateEllipsisTrimmingSign
        /// provides a typical ellipsis symbol. Trimming is also useful vertically for hiding
        /// partial lines.
        /// </remarks>
        void SetTrimming( DWRITE_TRIMMING const* trimmingOptions, IDWriteInlineObject* trimmingSign ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetTrimming( trimmingOptions, trimmingSign );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        /// <summary>
        /// Set trimming options for any trailing text exceeding the layout width
        /// or for any far text exceeding the layout height.
        /// </summary>
        /// <param name="trimmingOptions">
        /// Text trimming options.
        /// </param>
        /// <param name="trimmingSign">
        /// Application-defined omission sign. Use the default InlineObject if no 
        /// trimming sign is desired.
        /// </param>
        void SetTrimming( const Trimming& trimmingOptions, const InlineObject& trimmingSign ) const;
        void SetTrimming( const Trimming& trimmingOptions ) const;

        /// <summary>
        /// Set line spacing.
        /// </summary>
        /// <param name="lineSpacingMethod">How to determine line height.</param>
        /// <param name="lineSpacing">The line height, or rather distance between one baseline to another.</param>
        /// <param name="baseline">Distance from top of line to baseline. A reasonable ratio to lineSpacing is 80%.</param>
        /// <remarks>
        /// For the default method, spacing depends solely on the content.
        /// For uniform spacing, the given line height will override the content.
        /// </remarks>
        void SetLineSpacing( DWRITE_LINE_SPACING_METHOD lineSpacingMethod, FLOAT lineSpacing, FLOAT baseline ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetLineSpacing( lineSpacingMethod, lineSpacing, baseline );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Set line spacing.
        /// </summary>
        /// <param name="lineSpacingMethod">How to determine line height.</param>
        /// <param name="lineSpacing">The line height, or rather distance between one baseline to another.</param>
        /// <param name="baseline">Distance from top of line to baseline. A reasonable ratio to lineSpacing is 80%.</param>
        /// <remarks>
        /// For the default method, spacing depends solely on the content.
        /// For uniform spacing, the given line height will override the content.
        /// </remarks>
        void SetLineSpacing( LineSpacingMethod lineSpacingMethod, FLOAT lineSpacing, FLOAT baseline ) const
        {
            SetLineSpacing( static_cast< DWRITE_LINE_SPACING_METHOD >( lineSpacingMethod ), lineSpacing, baseline );
        }

        /// <summary>
        /// Set line spacing.
        /// </summary>
        /// <param name="lineSpacing">The line spacing options.</param>
        void SetLineSpacing( const LineSpacingData& lineSpacing ) const
        {
            SetLineSpacing( lineSpacing.lineSpacingMethod, lineSpacing.lineSpacing, lineSpacing.baseline );
        }

        /// <summary>
        /// Get alignment option of text relative to layout box's leading and trailing edge.
        /// </summary>
        /// <returns>The text alignment.</returns>
        DWRITE_TEXT_ALIGNMENT GetTextAlignment( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetTextAlignment( );
        }
        /// <summary>
        /// Get alignment option of text relative to layout box's leading and trailing edge.
        /// </summary>
        /// <returns>The text alignment.</returns>
        DirectWrite::TextAlignment TextAlignment( ) const
        {
            return static_cast< DirectWrite::TextAlignment >( GetTextAlignment( ) );
        }

        /// <summary>
        /// Get alignment option of paragraph relative to layout box's top and bottom edge.
        /// </summary>
        /// <returns>The paragraph alignment.</returns>
        DWRITE_PARAGRAPH_ALIGNMENT GetParagraphAlignment( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetParagraphAlignment( );
        }

        /// <summary>
        /// Get alignment option of paragraph relative to layout box's top and bottom edge.
        /// </summary>
        /// <returns>The paragraph alignment.</returns>
        DirectWrite::ParagraphAlignment ParagraphAlignment( ) const
        {
            return static_cast< DirectWrite::ParagraphAlignment >( GetParagraphAlignment( ) );
        }

        /// <summary>
        /// Get word wrapping option.
        /// </summary>
        /// <returns>The word wrapping option.</returns>
        DWRITE_WORD_WRAPPING GetWordWrapping( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetWordWrapping( );
        }

        /// <summary>
        /// Get word wrapping option.
        /// </summary>
        /// <returns>The word wrapping option.</returns>
        DirectWrite::WordWrapping WordWrapping( ) const
        {
            return static_cast< DirectWrite::WordWrapping >( GetWordWrapping( ) );
        }
        
        /// <summary>
        /// Get paragraph reading direction.
        /// </summary>
        /// <returns>The paragraph reading direction.</returns>
        DWRITE_READING_DIRECTION GetReadingDirection( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetReadingDirection( );
        }

        /// <summary>
        /// Get paragraph reading direction.
        /// </summary>
        /// <returns>The paragraph reading direction.</returns>
        DirectWrite::ReadingDirection ReadingDirection( ) const
        {
            return static_cast< DirectWrite::ReadingDirection >( GetReadingDirection( ) );
        }

        /// <summary>
        /// Get paragraph flow direction.
        /// </summary>
        /// <returns>The paragraph flow direction.</returns>
        DWRITE_FLOW_DIRECTION GetFlowDirection( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFlowDirection( );
        }

        /// <summary>
        /// Get paragraph flow direction.
        /// </summary>
        /// <returns>The paragraph flow direction.</returns>
        DirectWrite::FlowDirection FlowDirection( ) const
        {
            return static_cast< DirectWrite::FlowDirection >( GetFlowDirection( ) );
        }

        /// <summary>
        /// Get incremental tab stop position.
        /// </summary>
        /// <returns>The incremental tab stop position.</returns>
        FLOAT GetIncrementalTabStop( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetIncrementalTabStop( );
        }

        /// <summary>
        /// Get trimming options for text overflowing the layout width.
        /// </summary>
        /// <param name="trimmingOptions">Text trimming options.</param>
        /// <param name="trimmingSign">Trimming omission sign. This parameter may be NULL.</param>
        void GetTrimming( DWRITE_TRIMMING* trimmingOptions, IDWriteInlineObject** trimmingSign ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetTrimming( trimmingOptions, trimmingSign );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Get trimming options for text overflowing the layout width.
        /// </summary>
        /// <param name="trimmingOptions">Text trimming options.</param>
        /// <returns>The trimming omission sign.</returns>
        inline InlineObject GetTrimming( DWRITE_TRIMMING& trimmingOptions ) const;


        /// <summary>
        /// Get line spacing.
        /// </summary>
        /// <param name="lineSpacingMethod">How line height is determined.</param>
        /// <param name="lineSpacing">The line height, or rather distance between one baseline to another.</param>
        /// <param name="baseline">Distance from top of line to baseline.</param>
        void GetLineSpacing( DWRITE_LINE_SPACING_METHOD* lineSpacingMethod, FLOAT* lineSpacing, FLOAT* baseline ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetLineSpacing( lineSpacingMethod, lineSpacing, baseline );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Get line spacing.
        /// </summary>
        /// <param name="lineSpacingMethod">How line height is determined.</param>
        /// <param name="lineSpacing">The line height, or rather distance between one baseline to another.</param>
        /// <param name="baseline">Distance from top of line to baseline.</param>
        void GetLineSpacing( LineSpacingMethod* lineSpacingMethod, FLOAT* lineSpacing, FLOAT* baseline ) const
        {
            DWRITE_LINE_SPACING_METHOD method;
            GetLineSpacing( &method, lineSpacing, baseline );
            *lineSpacingMethod = static_cast< LineSpacingMethod >( method );
        }

        /// <summary>
        /// Get line spacing.
        /// </summary>
        /// <returns>The line spacing options.</returns>
        LineSpacingData GetLineSpacing( ) const
        {
            DWRITE_LINE_SPACING_METHOD method;
            FLOAT lineSpacing;
            FLOAT baseline;
            GetLineSpacing( &method, &lineSpacing, &baseline );
            return LineSpacingData( static_cast< LineSpacingMethod >( method ), lineSpacing, baseline );
        }

        /// <summary>
        /// Get the font collection.
        /// </summary>
        /// <param name="fontCollection">The font collection.</param>
        void GetFontCollection( IDWriteFontCollection** fontCollection ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontCollection( fontCollection );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Get the font collection.
        /// </summary>
        /// <returns>The font collection.</returns>
        FontCollection GetFontCollection( ) const
        {
            IDWriteFontCollection* fontCollection = nullptr;
            GetFontCollection( &fontCollection );
            FontCollection result( fontCollection );
            return result;
        }

        /// <summary>
        /// Get the length of the font family name, in characters, not including the terminating NULL character.
        /// </summary>
        /// <returns>The length of the font family name.</returns>
        UINT32 GetFontFamilyNameLength( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFontFamilyNameLength( );
        }

        /// <summary>
        /// Get a copy of the font family name.
        /// </summary>
        /// <param name="fontFamilyName">Character array that receives the current font family name</param>
        /// <param name="nameSize">Size of the character array in character count including the terminated NULL character.</param>
        void GetFontFamilyName( WCHAR* fontFamilyName, UINT32 nameSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontFamilyName( fontFamilyName, nameSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Get a copy of the font family name.
        /// </summary>
        /// <typeparam name="StringType">The type of string to return.</typeparam>
        /// <returns>A copy of the font family name.</returns>
        template<WideStringLike StringType = WideString>
        StringType GetFontFamilyName( ) const
        {
            UINT32 nameLength = GetFontFamilyNameLength( );
            StringType result;
            result.resize( nameLength );
            GetFontFamilyName( result.data( ), nameLength + 1 );
            return result;
        }

        /// <summary>
        /// Get the font weight.
        /// </summary>
        /// <returns>The font weight.</returns>
        DWRITE_FONT_WEIGHT GetFontWeight( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFontWeight( );
        }
        /// <summary>
        /// Get the font weight.
        /// </summary>
        /// <returns>The font weight.</returns>
        DirectWrite::FontWeight FontWeight( ) const
        {
            return static_cast< DirectWrite::FontWeight >( GetFontWeight( ) );
        }

        /// <summary>
        /// Get the font style.
        /// </summary>
        /// <returns>The font style.</returns>
        DWRITE_FONT_STYLE GetFontStyle( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFontStyle( );
        }

        /// <summary>
        /// Get the font style.
        /// </summary>
        /// <returns>The font style.</returns>
        DirectWrite::FontStyle FontStyle( ) const
        {
            return static_cast< DirectWrite::FontStyle >( GetFontStyle( ) );
        }
        /// <summary>
        /// Get the font stretch.
        /// </summary>
        /// <returns>The font stretch.</returns>
        DWRITE_FONT_STRETCH GetFontStretch( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFontStretch( );
        }
        /// <summary>
        /// Get the font stretch.
        /// </summary>
        /// <returns>The font stretch.</returns>
        DirectWrite::FontStretch FontStretch( ) const
        {
            return static_cast< DirectWrite::FontStretch >( GetFontStretch( ) );
        }
        /// <summary>
        /// Get the font size.
        /// </summary>
        /// <returns>The font size.</returns>
        FLOAT GetFontSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFontSize( );
        }
        
        /// <summary>
        /// Get the length of the locale name, in characters, not including the terminating NULL character.
        /// </summary>
        /// <returns>The length of the locale name.</returns>
        UINT32 GetLocaleNameLength( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetLocaleNameLength( );
        }

        /// <summary>
        /// Get a copy of the locale name.
        /// </summary>
        /// <param name="localeName">
        /// Character array that receives the current locale name
        /// </param>
        /// <param name="nameSize">
        /// Size of the character array in character count including the terminated NULL character.
        /// </param>
        void GetLocaleName( WCHAR* localeName, UINT32 nameSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetLocaleName( localeName, nameSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Get a copy of the locale name.
        /// </summary>
        /// <typeparam name="StringType">The type of string to return.</typeparam>
        /// <returns>The locale name as a string of the specified type.</returns>
        template<WideStringLike StringType = WideString>
        StringType GetLocaleName( ) const
        {
            UINT32 nameLength = GetLocaleNameLength( );
            StringType result;
            result.resize( nameLength );
            GetLocaleName( result.data( ), nameLength + 1 );
            return result;
        }
    };


    

    /// <summary>
    /// Represents a font typography setting.
    /// </summary>
    class Typography : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Typography, Unknown, IDWriteTypography, IUnknown )

        void AddFontFeature( const DWRITE_FONT_FEATURE& fontFeature ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->AddFontFeature( fontFeature );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void AddFontFeatures( const std::vector<DWRITE_FONT_FEATURE>& fontFeatures ) const
        {
            for ( const auto& fontFeature : fontFeatures )
            {
                AddFontFeature( fontFeature );
            }
        }
        UINT32 GetFontFeatureCount( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFontFeatureCount( );
        }
        void GetFontFeature( UINT32 fontFeatureIndex, DWRITE_FONT_FEATURE* fontFeature ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontFeature( fontFeatureIndex, fontFeature );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        DWRITE_FONT_FEATURE GetFontFeature( UINT32 fontFeatureIndex ) const
        {
            DWRITE_FONT_FEATURE fontFeature;
            GetFontFeature( fontFeatureIndex, &fontFeature );
            return fontFeature;
        }
        std::vector<DWRITE_FONT_FEATURE> GetFontFeatures( ) const
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
    };

    /*
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
    */

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

        void AnalyzeScript(
                IDWriteTextAnalysisSource* analysisSource,
                UINT32 textPosition,
                UINT32 textLength,
                IDWriteTextAnalysisSink* analysisSink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->AnalyzeScript( analysisSource, textPosition, textLength, analysisSink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AnalyzeBidi(
            IDWriteTextAnalysisSource* analysisSource,
            UINT32 textPosition,
            UINT32 textLength,
            IDWriteTextAnalysisSink* analysisSink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->AnalyzeBidi( analysisSource, textPosition, textLength, analysisSink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AnalyzeNumberSubstitution(
            IDWriteTextAnalysisSource* analysisSource,
            UINT32 textPosition,
            UINT32 textLength,
            IDWriteTextAnalysisSink* analysisSink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->AnalyzeNumberSubstitution( analysisSource, textPosition, textLength, analysisSink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void AnalyzeLineBreakpoints(
            IDWriteTextAnalysisSource* analysisSource,
            UINT32 textPosition,
            UINT32 textLength,
            IDWriteTextAnalysisSink* analysisSink ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->AnalyzeLineBreakpoints( analysisSource, textPosition, textLength, analysisSink );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetGlyphs(
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
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetGlyphPlacements(
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
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetGdiCompatibleGlyphPlacements(
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
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
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

        void Draw( void* clientDrawingContext, IDWriteTextRenderer* renderer, FLOAT originX, FLOAT originY, BOOL isSideways, BOOL isRightToLeft, IUnknown* clientDrawingEffect ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Draw( clientDrawingContext, renderer, originX, originY, isSideways, isRightToLeft, clientDrawingEffect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetMetrics( DWRITE_INLINE_OBJECT_METRICS* metrics ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetMetrics( metrics );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetOverhangMetrics( DWRITE_OVERHANG_METRICS* overhangs ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetOverhangMetrics( overhangs );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetBreakConditions( DWRITE_BREAK_CONDITION* breakConditionBefore, DWRITE_BREAK_CONDITION* breakConditionAfter ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetBreakConditions( breakConditionBefore, breakConditionAfter );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    inline void TextFormat::SetTrimming( const Trimming& trimmingOptions, const InlineObject& trimmingSign ) const
    {
        SetTrimming( &trimmingOptions, trimmingSign.GetInterfacePointer< IDWriteInlineObject >( ) );
    }

    void TextFormat::SetTrimming( const Trimming& trimmingOptions ) const
    {
        SetTrimming( &trimmingOptions, nullptr );
    }

    inline InlineObject TextFormat::GetTrimming( DWRITE_TRIMMING& trimmingOptions ) const
    {
        IDWriteInlineObject* trimmingSign = nullptr;
        GetTrimming( &trimmingOptions, &trimmingSign );
        InlineObject result( trimmingSign );
        return result;
    }



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

        void IsPixelSnappingDisabled( void* clientDrawingContext, BOOL* isDisabled ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->IsPixelSnappingDisabled( clientDrawingContext, isDisabled );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetCurrentTransform( void* clientDrawingContext, DWRITE_MATRIX* transform ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetCurrentTransform( clientDrawingContext, transform );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetPixelsPerDip( void* clientDrawingContext, FLOAT* pixelsPerDip ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetPixelsPerDip( clientDrawingContext, pixelsPerDip );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Represents a set of application-defined callbacks that perform rendering of text, inline objects, and decorations such as underlines.
    /// </summary>
    class TextRenderer : public PixelSnapping
    {
    public:
        typedef PixelSnapping Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextRenderer, PixelSnapping, IDWriteTextRenderer, IDWritePixelSnapping )

        void DrawGlyphRun( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_MEASURING_MODE measuringMode, DWRITE_GLYPH_RUN const* glyphRun, DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription, IUnknown* clientDrawingEffect ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->DrawGlyphRun( clientDrawingContext, baselineOriginX, baselineOriginY, measuringMode, glyphRun, glyphRunDescription, clientDrawingEffect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void DrawUnderline( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_UNDERLINE const* underline, IUnknown* clientDrawingEffect ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->DrawUnderline( clientDrawingContext, baselineOriginX, baselineOriginY, underline, clientDrawingEffect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void DrawStrikethrough( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_STRIKETHROUGH const* strikethrough, IUnknown* clientDrawingEffect ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->DrawStrikethrough( clientDrawingContext, baselineOriginX, baselineOriginY, strikethrough, clientDrawingEffect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void DrawInlineObject( void* clientDrawingContext, FLOAT originX, FLOAT originY, IDWriteInlineObject* inlineObject, BOOL isSideways, BOOL isRightToLeft, IUnknown* clientDrawingEffect ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->DrawInlineObject( clientDrawingContext, originX, originY, inlineObject, isSideways, isRightToLeft, clientDrawingEffect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// The TextLayout class represents a block of text after it has been fully analyzed and formatted.
    /// </summary>
    class TextLayout : public TextFormat
    {
    public:
        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextLayout, TextFormat, IDWriteTextLayout, IDWriteTextFormat )

        void SetMaxWidth( FLOAT maxWidth ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetMaxWidth( maxWidth );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void SetMaxHeight( FLOAT maxHeight ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetMaxHeight( maxHeight );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetFontCollection( IDWriteFontCollection* fontCollection, DWRITE_TEXT_RANGE textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetFontCollection( fontCollection, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetFontFamilyName( WCHAR const* fontFamilyName, DWRITE_TEXT_RANGE textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetFontFamilyName( fontFamilyName, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetFontWeight( DWRITE_FONT_WEIGHT fontWeight, DWRITE_TEXT_RANGE textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetFontWeight( fontWeight, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetFontStyle( DWRITE_FONT_STYLE fontStyle, DWRITE_TEXT_RANGE textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetFontStyle( fontStyle, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetFontStretch( DWRITE_FONT_STRETCH fontStretch, DWRITE_TEXT_RANGE textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetFontStretch( fontStretch, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetFontSize( FLOAT fontSize, DWRITE_TEXT_RANGE textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetFontSize( fontSize, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetUnderline( BOOL hasUnderline, DWRITE_TEXT_RANGE textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetUnderline( hasUnderline, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetStrikethrough( BOOL hasStrikethrough, DWRITE_TEXT_RANGE textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetStrikethrough( hasStrikethrough, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetDrawingEffect( IUnknown* drawingEffect, DWRITE_TEXT_RANGE textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetDrawingEffect( drawingEffect, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void SetInlineObject( IDWriteInlineObject* inlineObject, DWRITE_TEXT_RANGE textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetInlineObject( inlineObject, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetTypography( IDWriteTypography* typography, DWRITE_TEXT_RANGE textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetTypography( typography, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetLocaleName( WCHAR const* localeName, DWRITE_TEXT_RANGE textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetLocaleName( localeName, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        FLOAT GetMaxWidth( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetMaxWidth( );
        }

        FLOAT GetMaxHeight( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetMaxHeight( );
        }

        void GetFontCollection( UINT32 currentPosition, IDWriteFontCollection** fontCollection, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontCollection( currentPosition, fontCollection, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFontFamilyNameLength( UINT32 currentPosition, UINT32* nameLength, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontFamilyNameLength( currentPosition, nameLength, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFontFamilyName( UINT32 currentPosition, _Out_writes_z_( nameSize ) WCHAR* fontFamilyName, UINT32 nameSize, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontFamilyName( currentPosition, fontFamilyName, nameSize, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetFontWeight( UINT32 currentPosition, DWRITE_FONT_WEIGHT* fontWeight, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontWeight( currentPosition, fontWeight, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetFontStyle( UINT32 currentPosition, DWRITE_FONT_STYLE* fontStyle, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontStyle( currentPosition, fontStyle, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFontStretch( UINT32 currentPosition, DWRITE_FONT_STRETCH* fontStretch, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontStretch( currentPosition, fontStretch, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetFontSize( UINT32 currentPosition, FLOAT* fontSize, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetFontSize( currentPosition, fontSize, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetUnderline( UINT32 currentPosition, BOOL* hasUnderline, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetUnderline( currentPosition, hasUnderline, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetStrikethrough( UINT32 currentPosition, BOOL* hasStrikethrough, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetStrikethrough( currentPosition, hasStrikethrough, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetDrawingEffect( UINT32 currentPosition, IUnknown** drawingEffect, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDrawingEffect( currentPosition, drawingEffect, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetInlineObject( UINT32 currentPosition, IDWriteInlineObject** inlineObject, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetInlineObject( currentPosition, inlineObject, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void GetTypography( UINT32 currentPosition, IDWriteTypography** typography, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetTypography( currentPosition, typography, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetLocaleNameLength( UINT32 currentPosition, UINT32* nameLength, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetLocaleNameLength( currentPosition, nameLength, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetLocaleName( UINT32 currentPosition, _Out_writes_z_( nameSize ) WCHAR* localeName, UINT32 nameSize, _Out_opt_ DWRITE_TEXT_RANGE* textRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetLocaleName( currentPosition, localeName, nameSize, textRange );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Draw( void* clientDrawingContext, IDWriteTextRenderer* renderer, FLOAT originX, FLOAT originY ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Draw( clientDrawingContext, renderer, originX, originY );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetLineMetrics( DWRITE_LINE_METRICS* lineMetrics, UINT32 maxLineCount, UINT32* actualLineCount ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetLineMetrics( lineMetrics, maxLineCount, actualLineCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetMetrics( DWRITE_TEXT_METRICS* textMetrics ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetMetrics( textMetrics );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetOverhangMetrics( DWRITE_OVERHANG_METRICS* overhangs ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetOverhangMetrics( overhangs );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetClusterMetrics( DWRITE_CLUSTER_METRICS* clusterMetrics, UINT32 maxClusterCount, UINT32* actualClusterCount ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetClusterMetrics( clusterMetrics, maxClusterCount, actualClusterCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void DetermineMinWidth( FLOAT* minWidth ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->DetermineMinWidth( minWidth );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void HitTestPoint( FLOAT pointX, FLOAT pointY, BOOL* isTrailingHit, BOOL* isInside, DWRITE_HIT_TEST_METRICS* hitTestMetrics ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->HitTestPoint( pointX, pointY, isTrailingHit, isInside, hitTestMetrics );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void HitTestTextPosition( UINT32 textPosition, BOOL isTrailingHit, FLOAT* pointX, FLOAT* pointY, DWRITE_HIT_TEST_METRICS* hitTestMetrics ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->HitTestTextPosition( textPosition, isTrailingHit, pointX, pointY, hitTestMetrics );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void HitTestTextRange( UINT32 textPosition, UINT32 textLength, FLOAT originX, FLOAT originY, DWRITE_HIT_TEST_METRICS* hitTestMetrics, UINT32 maxHitTestMetricsCount, UINT32* actualHitTestMetricsCount ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->HitTestTextRange( textPosition, textLength, originX, originY, hitTestMetrics, maxHitTestMetricsCount, actualHitTestMetricsCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    


    /// <summary>
    /// Encapsulates a 32-bit device independent bitmap and device context, which can be used for rendering glyphs.
    /// </summary>
    class BitmapRenderTarget : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( BitmapRenderTarget, Unknown, IDWriteBitmapRenderTarget, IUnknown )

        void DrawGlyphRun( FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_MEASURING_MODE measuringMode, DWRITE_GLYPH_RUN const* glyphRun, IDWriteRenderingParams* renderingParams, COLORREF textColor, _Out_opt_ RECT* blackBoxRect ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->DrawGlyphRun( baselineOriginX, baselineOriginY, measuringMode, glyphRun, renderingParams, textColor, blackBoxRect );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        HDC GetMemoryDC( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetMemoryDC( );
        }

        FLOAT GetPixelsPerDip( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetPixelsPerDip( );
        }
        void SetPixelsPerDip( FLOAT pixelsPerDip ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetPixelsPerDip( pixelsPerDip );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetCurrentTransform( DWRITE_MATRIX* transform ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetCurrentTransform( transform );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void SetCurrentTransform( DWRITE_MATRIX const* transform ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetCurrentTransform( transform );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetSize( SIZE* size ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetSize( size );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Resize( UINT32 width, UINT32 height ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Resize( width, height );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
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

        void CreateFontFromLOGFONT( LOGFONTW const* logFont, IDWriteFont** font ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateFontFromLOGFONT( logFont, font );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ConvertFontToLOGFONT( IDWriteFont* font, LOGFONTW* logFont, BOOL* isSystemFont ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->ConvertFontToLOGFONT( font, logFont, isSystemFont );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ConvertFontFaceToLOGFONT( IDWriteFontFace* font, LOGFONTW* logFont ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->ConvertFontFaceToLOGFONT( font, logFont );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateFontFaceFromHdc( HDC hdc, IDWriteFontFace** fontFace ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateFontFaceFromHdc( hdc, fontFace );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateBitmapRenderTarget( HDC hdc, UINT32 width, UINT32 height, IDWriteBitmapRenderTarget** renderTarget ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateBitmapRenderTarget( hdc, width, height, renderTarget );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Contains low-level information used to render a glyph run.
    /// </summary>
    class GlyphRunAnalysis : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( GlyphRunAnalysis, Unknown, IDWriteGlyphRunAnalysis, IUnknown )

        void GetAlphaTextureBounds( DWRITE_TEXTURE_TYPE textureType, RECT* textureBounds ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetAlphaTextureBounds( textureType, textureBounds );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateAlphaTexture( DWRITE_TEXTURE_TYPE textureType, RECT const* textureBounds, BYTE* alphaValues, UINT32 bufferSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateAlphaTexture( textureType, textureBounds, alphaValues, bufferSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetAlphaBlendParams( IDWriteRenderingParams* renderingParams, FLOAT* blendGamma, FLOAT* blendEnhancedContrast, FLOAT* blendClearTypeLevel ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetAlphaBlendParams( renderingParams, blendGamma, blendEnhancedContrast, blendClearTypeLevel );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Used to create all subsequent DirectWrite objects. This class is the root factory for all DirectWrite objects.
    /// </summary>
    class Factory : public Unknown
    {
    public:
        typedef Unknown Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Factory, Unknown, IDWriteFactory, IUnknown )

        Factory( DWRITE_FACTORY_TYPE factoryType )
        {
            IUnknown* factory = nullptr;
            HRESULT hr = DWriteCreateFactory( factoryType, __uuidof( IDWriteFactory ), &factory );
            CheckHRESULT( hr );
            unknown_ = factory;
        }

        Factory(FactoryType factoryType)
            : Factory( static_cast< DWRITE_FACTORY_TYPE >( factoryType ) )
        {}

        void GetSystemFontCollection( IDWriteFontCollection** fontCollection, BOOL checkForUpdates ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetSystemFontCollection( fontCollection, checkForUpdates );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        FontCollection GetSystemFontCollection( bool checkForUpdates ) const
        {
            IDWriteFontCollection* fontCollection = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetSystemFontCollection( &fontCollection, checkForUpdates );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            FontCollection result( fontCollection );
            return result;
        }

        void CreateCustomFontCollection( IDWriteFontCollectionLoader* collectionLoader, void const* collectionKey, UINT32 collectionKeySize, IDWriteFontCollection** fontCollection ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateCustomFontCollection( collectionLoader, collectionKey, collectionKeySize, fontCollection );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        FontCollection CreateCustomFontCollection( IDWriteFontCollectionLoader* collectionLoader, void const* collectionKey, UINT32 collectionKeySize ) const
        {
            IDWriteFontCollection* fontCollection = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateCustomFontCollection( collectionLoader, collectionKey, collectionKeySize, &fontCollection );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            FontCollection result( fontCollection );
            return result;
        }

        void RegisterFontCollectionLoader( IDWriteFontCollectionLoader* fontCollectionLoader ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->RegisterFontCollectionLoader( fontCollectionLoader );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void UnregisterFontCollectionLoader( IDWriteFontCollectionLoader* fontCollectionLoader ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->UnregisterFontCollectionLoader( fontCollectionLoader );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateFontFileReference( WCHAR const* filePath, FILETIME const* lastWriteTime, IDWriteFontFile** fontFile ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateFontFileReference( filePath, lastWriteTime, fontFile );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        FontFile CreateFontFileReference( WCHAR const* filePath, FILETIME const* lastWriteTime ) const
        {
            IDWriteFontFile* fontFile = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateFontFileReference( filePath, lastWriteTime, &fontFile );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            FontFile result( fontFile );
            return result;
        }
        void CreateCustomFontFileReference( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileLoader* fontFileLoader, IDWriteFontFile** fontFile ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateCustomFontFileReference( fontFileReferenceKey, fontFileReferenceKeySize, fontFileLoader, fontFile );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        FontFile CreateCustomFontFileReference( void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileLoader* fontFileLoader ) const
        {
            IDWriteFontFile* fontFile = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateCustomFontFileReference( fontFileReferenceKey, fontFileReferenceKeySize, fontFileLoader, &fontFile );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            FontFile result( fontFile );
            return result;
        }

        void CreateFontFace( DWRITE_FONT_FACE_TYPE fontFaceType, UINT32 numberOfFiles, IDWriteFontFile* const* fontFiles, UINT32 faceIndex, DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags, IDWriteFontFace** fontFace ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateFontFace( fontFaceType, numberOfFiles, fontFiles, faceIndex, fontFaceSimulationFlags, fontFace );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        FontFace CreateFontFace( DWRITE_FONT_FACE_TYPE fontFaceType, UINT32 numberOfFiles, IDWriteFontFile* const* fontFiles, UINT32 faceIndex, DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags ) const
        {
            IDWriteFontFace* fontFace = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateFontFace( fontFaceType, numberOfFiles, fontFiles, faceIndex, fontFaceSimulationFlags, &fontFace );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            FontFace result( fontFace );
            return result;
        }

        void CreateRenderingParams( IDWriteRenderingParams** renderingParams ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateRenderingParams( renderingParams );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        RenderingParams CreateRenderingParams( ) const
        {
            IDWriteRenderingParams* renderingParams = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateRenderingParams( &renderingParams );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            RenderingParams result( renderingParams );
            return result;
        }

        void CreateMonitorRenderingParams( HMONITOR monitor, IDWriteRenderingParams** renderingParams ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateMonitorRenderingParams( monitor, renderingParams );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        RenderingParams CreateMonitorRenderingParams( HMONITOR monitor ) const
        {
            IDWriteRenderingParams* renderingParams = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateMonitorRenderingParams( monitor, &renderingParams );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            RenderingParams result( renderingParams );
            return result;
        }

        void CreateCustomRenderingParams( FLOAT gamma, FLOAT enhancedContrast, FLOAT clearTypeLevel, DWRITE_PIXEL_GEOMETRY pixelGeometry, DWRITE_RENDERING_MODE renderingMode, IDWriteRenderingParams** renderingParams ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateCustomRenderingParams( gamma, enhancedContrast, clearTypeLevel, pixelGeometry, renderingMode, renderingParams );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        RenderingParams CreateCustomRenderingParams( FLOAT gamma, FLOAT enhancedContrast, FLOAT clearTypeLevel, DWRITE_PIXEL_GEOMETRY pixelGeometry, DWRITE_RENDERING_MODE renderingMode ) const
        {
            IDWriteRenderingParams* renderingParams = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateCustomRenderingParams( gamma, enhancedContrast, clearTypeLevel, pixelGeometry, renderingMode, &renderingParams );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            RenderingParams result( renderingParams );
            return result;
        }

        void RegisterFontFileLoader( IDWriteFontFileLoader* fontFileLoader ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->RegisterFontFileLoader( fontFileLoader );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void UnregisterFontFileLoader( IDWriteFontFileLoader* fontFileLoader ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->UnregisterFontFileLoader( fontFileLoader );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateTextFormat( WCHAR const* fontFamilyName, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName, IDWriteTextFormat** textFormat ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateTextFormat( fontFamilyName, fontCollection, fontWeight, fontStyle, fontStretch, fontSize, localeName, textFormat );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        TextFormat CreateTextFormat( WCHAR const* fontFamilyName, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName ) const
        {
            IDWriteTextFormat* textFormat = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateTextFormat( fontFamilyName, fontCollection, fontWeight, fontStyle, fontStretch, fontSize, localeName, &textFormat );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            TextFormat result( textFormat );
            return result;
        }

        TextFormat CreateTextFormat( WCHAR const* fontFamilyName, FLOAT fontSize ) const
        {
            wchar_t localeName[ LOCALE_NAME_MAX_LENGTH + 1 ] = { 0, };
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


        void CreateTypography( IDWriteTypography** typography ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateTypography( typography );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        Typography CreateTypography( ) const
        {
            IDWriteTypography* typography = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateTypography( &typography );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            Typography result( typography );
            return result;
        }

        void GetGdiInterop( IDWriteGdiInterop** gdiInterop ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetGdiInterop( gdiInterop );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        GdiInterop GetGdiInterop( ) const
        {
            IDWriteGdiInterop* gdiInterop = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetGdiInterop( &gdiInterop );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            GdiInterop result( gdiInterop );
            return result;
        }

        void CreateTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT maxWidth, FLOAT maxHeight, IDWriteTextLayout** textLayout ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateTextLayout( string, stringLength, textFormat, maxWidth, maxHeight, textLayout );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        TextLayout CreateTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT maxWidth, FLOAT maxHeight ) const
        {
            IDWriteTextLayout* textLayout = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateTextLayout( string, stringLength, textFormat, maxWidth, maxHeight, &textLayout );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            TextLayout result( textLayout );
            return result;
        }

        void CreateGdiCompatibleTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT layoutWidth, FLOAT layoutHeight, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural, IDWriteTextLayout** textLayout ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateGdiCompatibleTextLayout( string, stringLength, textFormat, layoutWidth, layoutHeight, pixelsPerDip, transform, useGdiNatural, textLayout );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        TextLayout CreateGdiCompatibleTextLayout( WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT layoutWidth, FLOAT layoutHeight, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural ) const
        {
            IDWriteTextLayout* textLayout = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateGdiCompatibleTextLayout( string, stringLength, textFormat, layoutWidth, layoutHeight, pixelsPerDip, transform, useGdiNatural, &textLayout );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            TextLayout result( textLayout );
            return result;
        }

        void CreateEllipsisTrimmingSign( IDWriteTextFormat* textFormat, IDWriteInlineObject** trimmingSign ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateEllipsisTrimmingSign( textFormat, trimmingSign );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        InlineObject CreateEllipsisTrimmingSign( IDWriteTextFormat* textFormat ) const
        {
            IDWriteInlineObject* trimmingSign = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateEllipsisTrimmingSign( textFormat, &trimmingSign );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            InlineObject result( trimmingSign );
            return result;
        }
        void CreateTextAnalyzer( IDWriteTextAnalyzer** textAnalyzer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateTextAnalyzer( textAnalyzer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        TextAnalyzer CreateTextAnalyzer( ) const
        {
            IDWriteTextAnalyzer* textAnalyzer = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateTextAnalyzer( &textAnalyzer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            TextAnalyzer result( textAnalyzer );
            return result;
        }

        void CreateNumberSubstitution( DWRITE_NUMBER_SUBSTITUTION_METHOD substitutionMethod, WCHAR const* localeName, BOOL ignoreUserOverride, IDWriteNumberSubstitution** numberSubstitution ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateNumberSubstitution( substitutionMethod, localeName, ignoreUserOverride, numberSubstitution );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateGlyphRunAnalysis( DWRITE_GLYPH_RUN const* glyphRun, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_RENDERING_MODE renderingMode, DWRITE_MEASURING_MODE measuringMode, FLOAT baselineOriginX, FLOAT baselineOriginY, IDWriteGlyphRunAnalysis** glyphRunAnalysis ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateGlyphRunAnalysis( glyphRun, pixelsPerDip, transform, renderingMode, measuringMode, baselineOriginX, baselineOriginY, glyphRunAnalysis );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        GlyphRunAnalysis CreateGlyphRunAnalysis( DWRITE_GLYPH_RUN const* glyphRun, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_RENDERING_MODE renderingMode, DWRITE_MEASURING_MODE measuringMode, FLOAT baselineOriginX, FLOAT baselineOriginY ) const
        {
            IDWriteGlyphRunAnalysis* glyphRunAnalysis = nullptr;
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateGlyphRunAnalysis( glyphRun, pixelsPerDip, transform, renderingMode, measuringMode, baselineOriginX, baselineOriginY, &glyphRunAnalysis );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            GlyphRunAnalysis result( glyphRunAnalysis );
            return result;
        }
    };


    /// <summary>
    /// The interface that represents an absolute reference to a font face.
    /// It contains font face type, appropriate file references and face identification data.
    /// Various font data such as metrics, names and glyph outlines is obtained from IDWriteFontFace.
    /// </summary>
    class FontFace1 : public FontFace
    {
    public:
        typedef FontFace Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( FontFace1, FontFace, IDWriteFontFace1, IDWriteFontFace )

        /// <summary>
        /// Gets common metrics for the font in design units.
        /// These metrics are applicable to all the glyphs within a font,
        /// and are used by applications for layout calculations.
        /// </summary>
        /// <param name="fontMetrics">Metrics structure to fill in.</param>
        void GetMetrics( _Out_ DWRITE_FONT_METRICS1* fontMetrics ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetMetrics( fontMetrics );
        }

        /// <summary>
        /// Gets common metrics for the font in design units.
        /// These metrics are applicable to all the glyphs within a font,
        /// and are used by applications for layout calculations.
        /// </summary>
        /// <returns>Font metrics structure.</returns>
        FontMetrics1 GetMetrics( ) const
        {
            FontMetrics1 fontMetrics;
            GetMetrics( &fontMetrics );
            return fontMetrics;
        }


        /// <summary>
        /// Gets common metrics for the font in design units.
        /// These metrics are applicable to all the glyphs within a font,
        /// and are used by applications for layout calculations.
        /// </summary>
        /// <param name="emSize">
        /// Logical size of the font in DIP units. A DIP ("device-independent pixel") 
        /// equals 1/96 inch.
        /// </param>
        /// <param name="pixelsPerDip">
        /// Number of physical pixels per DIP. For example, if the DPI of the rendering 
        /// surface is 96 this value is 1.0f. If the DPI is 120, this value is 120.0f/96.
        /// </param>
        /// <param name="transform">
        /// Optional transform applied to the glyphs and their positions. This transform 
        /// is applied after the scaling specified by the font size and pixelsPerDip.
        /// </param>
        /// <param name="fontMetrics">
        /// Font metrics structure to fill in.
        /// </param>
        void GetGdiCompatibleMetrics( FLOAT emSize, FLOAT pixelsPerDip, _In_opt_ DWRITE_MATRIX const* transform, _Out_ DWRITE_FONT_METRICS1* fontMetrics ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetGdiCompatibleMetrics( emSize, pixelsPerDip, transform, fontMetrics );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets GDI-compatible metrics for the font in design units.
        /// These metrics are applicable to all the glyphs within a font,
        /// and are used by applications for layout calculations.
        /// </summary>
        /// <param name="emSize">
        /// Logical size of the font in DIP units. A DIP ("device-independent pixel") 
        /// equals 1/96 inch.
        /// </param>
        /// <param name="pixelsPerDip">
        /// Number of physical pixels per DIP. For example, if the DPI of the rendering 
        /// surface is 96 this value is 1.0f. If the DPI is 120, this value is 120.0f/96.
        /// </param>
        /// <param name="transform">
        /// Optional transform applied to the glyphs and their positions. This transform 
        /// is applied after the scaling specified by the font size and pixelsPerDip.
        /// </param>
        /// <returns>
        /// Font metrics structure.
        /// </returns>
        FontMetrics1 GetGdiCompatibleMetrics( FLOAT emSize, FLOAT pixelsPerDip, _In_opt_ DWRITE_MATRIX const* transform = nullptr ) const
        {
            FontMetrics1 fontMetrics;
            GetGdiCompatibleMetrics( emSize, pixelsPerDip, transform, &fontMetrics );
            return fontMetrics;
        }


        /// <summary>
        /// Gets GDI-compatible metrics for the font in design units.
        /// These metrics are applicable to all the glyphs within a font,
        /// and are used by applications for layout calculations.
        /// </summary>
        /// <param name="emSize">
        /// Logical size of the font in DIP units. A DIP ("device-independent pixel") 
        /// equals 1/96 inch.
        /// </param>
        /// <param name="pixelsPerDip">
        /// Number of physical pixels per DIP. For example, if the DPI of the rendering 
        /// surface is 96 this value is 1.0f. If the DPI is 120, this value is 120.0f/96.
        /// </param>
        /// <param name="transform">
        /// Transform applied to the glyphs and their positions. This transform 
        /// is applied after the scaling specified by the font size and pixelsPerDip.
        /// </param>
        /// <returns>
        /// Font metrics structure.
        /// </returns>
        FontMetrics1 GetGdiCompatibleMetrics( FLOAT emSize, FLOAT pixelsPerDip, const DWRITE_MATRIX& transform ) const
        {
            FontMetrics1 fontMetrics;
            GetGdiCompatibleMetrics( emSize, pixelsPerDip, &transform, &fontMetrics );
            return fontMetrics;
        }



        /// <summary>
        /// Gets caret metrics for the font in design units. These are used by
        /// text editors for drawing the correct caret placement/slant.
        /// </summary>
        /// <param name="caretMetrics">Metrics structure to fill in.</param>
        void GetCaretMetrics( _Out_ DWRITE_CARET_METRICS* caretMetrics ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetCaretMetrics( caretMetrics );
        }

        /// <summary>
        /// Gets caret metrics for the font in design units. These are used by
        /// text editors for drawing the correct caret placement/slant.
        /// </summary>
        /// <returns>Metrics structure.</returns>
        CaretMetrics GetCaretMetrics( ) const
        {
            CaretMetrics caretMetrics;
            GetCaretMetrics( &caretMetrics );
            return caretMetrics;
        }


        /// <summary>
        /// Returns the list of character ranges supported by the font, which is
        /// useful for scenarios like character picking, glyph display, and
        /// efficient font selection lookup. This is similar to GDI's
        /// GetFontUnicodeRanges, except that it returns the full Unicode range,
        /// not just 16-bit UCS-2.
        /// </summary>
        /// <param name="maxRangeCount">
        /// Maximum number of character ranges passed in from the client.
        /// </param>
        /// <param name="unicodeRanges">
        /// Array of character ranges.
        /// </param>
        /// <param name="actualRangeCount">
        /// Actual number of character ranges, regardless of the maximum count.
        /// </param>
        /// <remarks>
        /// These ranges are from the cmap, not the OS/2::ulCodePageRange1.
        /// </remarks>
        void GetUnicodeRanges( UINT32 maxRangeCount, _Out_writes_to_opt_( maxRangeCount, *actualRangeCount ) DWRITE_UNICODE_RANGE* unicodeRanges, _Out_ UINT32* actualRangeCount ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr =  pInterface->GetUnicodeRanges( maxRangeCount, unicodeRanges, actualRangeCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }


        /// <summary>
        /// Returns the list of character ranges supported by the font, which is
        /// useful for scenarios like character picking, glyph display, and
        /// efficient font selection lookup. This is similar to GDI's
        /// GetFontUnicodeRanges, except that it returns the full Unicode range,
        /// not just 16-bit UCS-2.
        /// </summary>
        /// <returns>
        /// Vector of Unicode ranges.
        /// </returns>
        std::vector<UnicodeRange> GetUnicodeRanges( ) const
        {
            UINT32 actualRangeCount = 0;
            GetUnicodeRanges( 0, nullptr, &actualRangeCount );
            std::vector<UnicodeRange> result( actualRangeCount );
            GetUnicodeRanges( actualRangeCount, result.data( ), &actualRangeCount );
            return result;
        }



        /// <summary>
        /// Returns true if the font is monospaced, meaning its characters are the
        /// same fixed-pitch width (non-proportional).
        /// </summary>
        bool IsMonospacedFont( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsMonospacedFont( ) != FALSE;
        }

        /// <summary>
        /// Returns the advances in design units for a sequences of glyphs.
        /// </summary>
        /// <param name="glyphCount">
        /// Number of glyphs to retrieve advances for.
        /// </param>
        /// <param name="glyphIndices">
        /// Array of glyph id's to retrieve advances for.
        /// </param>
        /// <param name="glyphAdvances">
        /// Returned advances in font design units for each glyph.
        /// </param>
        /// <param name="isSideways">
        /// Retrieve the glyph's vertical advance height rather than horizontal advance widths.
        /// </param>
        /// <remarks>
        /// This is equivalent to calling GetGlyphMetrics and using only the
        /// advance width/height.
        /// </remarks>
        void GetDesignGlyphAdvances( UINT32 glyphCount, _In_reads_( glyphCount ) UINT16 const* glyphIndices, _Out_writes_( glyphCount ) INT32* glyphAdvances, BOOL isSideways = FALSE ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetDesignGlyphAdvances( glyphCount, glyphIndices, glyphAdvances, isSideways );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Returns the advances in design units for a sequences of glyphs.
        /// </summary>
        /// <param name="glyphCount">
        /// Number of glyphs to retrieve advances for.
        /// </param>
        /// <param name="glyphIndices">
        /// Array of glyph id's to retrieve advances for.
        /// </param>
        /// <param name="isSideways">
        /// Retrieve the glyph's vertical advance height rather than horizontal advance widths.
        /// </param>
        /// <returns>
        /// Vector of advances in font design units for each glyph.
        /// </returns>
        std::vector<INT32> GetDesignGlyphAdvances( UINT32 glyphCount, _In_reads_( glyphCount ) UINT16 const* glyphIndices, BOOL isSideways = FALSE ) const
        {
            std::vector<INT32> result( glyphCount );
            GetDesignGlyphAdvances( glyphCount, glyphIndices, result.data( ), isSideways );
            return result;
        }


        /// <summary>
        /// Returns the pixel-aligned advances for a sequences of glyphs, the same
        /// as GetGdiCompatibleGlyphMetrics would return.
        /// </summary>
        /// <param name="emSize">
        /// Logical size of the font in DIP units. A DIP ("device-independent pixel") equals 1/96 inch.
        /// </param>
        /// <param name="pixelsPerDip">
        /// Number of physical pixels per DIP. For example, if the DPI 
        /// of the rendering surface is 96 this value is 1.0f. If the 
        /// DPI is 120, this value is 120.0f/96.
        /// </param>
        /// <param name="transform">
        /// Optional transform applied to the glyphs and their positions. 
        /// This transform is applied after the scaling specified by the 
        /// font size and pixelsPerDip.
        /// </param>
        /// <param name="useGdiNatural">
        /// When FALSE, the metrics are the same as GDI aliased text 
        /// (DWRITE_MEASURING_MODE_GDI_CLASSIC). 
        /// When TRUE, the metrics are the same as those measured by GDI 
        /// using a font using CLEARTYPE_NATURAL_QUALITY (DWRITE_MEASURING_MODE_GDI_NATURAL).
        /// </param>
        /// <param name="isSideways">
        /// Retrieve the glyph's vertical advances rather than horizontal advances.
        /// </param>
        /// <param name="glyphCount">
        /// Total glyphs to retrieve adjustments for.
        /// </param>
        /// <param name="glyphIndices">
        /// Array of glyph id's to retrieve advances.
        /// </param>
        /// <param name="glyphAdvances">
        /// Returned advances in font design units for each glyph.
        /// </param>
        /// <remarks>
        /// This is equivalent to calling GetGdiCompatibleGlyphMetrics and using only
        /// the advance width/height. Like GetGdiCompatibleGlyphMetrics, these are in
        /// design units, meaning they must be scaled down by
        /// DWRITE_FONT_METRICS::designUnitsPerEm.
        /// </remarks>
        void GetGdiCompatibleGlyphAdvances( FLOAT emSize, FLOAT pixelsPerDip,
                                            _In_opt_ DWRITE_MATRIX const* transform,
                                            BOOL useGdiNatural, BOOL isSideways,
                                            UINT32 glyphCount, _In_reads_( glyphCount ) UINT16 const* glyphIndices,
                                            _Out_writes_( glyphCount ) INT32* glyphAdvances ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetGdiCompatibleGlyphAdvances( emSize, pixelsPerDip, transform, useGdiNatural, isSideways, glyphCount, glyphIndices, glyphAdvances );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Returns the pixel-aligned advances for a sequences of glyphs, the same
        /// as GetGdiCompatibleGlyphMetrics would return.
        /// </summary>
        /// <param name="emSize">
        /// Logical size of the font in DIP units. A DIP ("device-independent pixel") equals 1/96 inch.
        /// </param>
        /// <param name="pixelsPerDip">
        /// Number of physical pixels per DIP. For example, if the DPI 
        /// of the rendering surface is 96 this value is 1.0f. If the 
        /// DPI is 120, this value is 120.0f/96.
        /// </param>
        /// <param name="transform">
        /// Optional transform applied to the glyphs and their positions. 
        /// This transform is applied after the scaling specified by the 
        /// font size and pixelsPerDip.
        /// </param>
        /// <param name="useGdiNatural">
        /// When FALSE, the metrics are the same as GDI aliased text 
        /// (DWRITE_MEASURING_MODE_GDI_CLASSIC). 
        /// When TRUE, the metrics are the same as those measured by GDI 
        /// using a font using CLEARTYPE_NATURAL_QUALITY (DWRITE_MEASURING_MODE_GDI_NATURAL).
        /// </param>
        /// <param name="isSideways">
        /// Retrieve the glyph's vertical advances rather than horizontal advances.
        /// </param>
        /// <param name="glyphCount">
        /// Total glyphs to retrieve adjustments for.
        /// </param>
        /// <param name="glyphIndices">
        /// Array of glyph id's to retrieve advances.
        /// </param>
        /// <remarks>
        /// This is equivalent to calling GetGdiCompatibleGlyphMetrics and using only
        /// the advance width/height. Like GetGdiCompatibleGlyphMetrics, these are in
        /// design units, meaning they must be scaled down by
        /// FontMetrics::designUnitsPerEm.
        /// </remarks>
        /// <returns>
        /// A vector of INT32 containing the pixel-aligned advances for each glyph.
        /// </returns>
        std::vector<INT32> GetGdiCompatibleGlyphAdvances( FLOAT emSize, FLOAT pixelsPerDip,
                                            _In_opt_ DWRITE_MATRIX const* transform, BOOL useGdiNatural, BOOL isSideways,
                                            UINT32 glyphCount, _In_reads_( glyphCount ) UINT16 const* glyphIndices ) const
        {
            std::vector<INT32> result( glyphCount );
            GetGdiCompatibleGlyphAdvances( emSize, pixelsPerDip, transform, useGdiNatural, isSideways, glyphCount, glyphIndices, result.data( ) );
            return result;
        }



        /// <summary>
        /// Retrieves the kerning pair adjustments from the font's kern table.
        /// </summary>
        /// <param name="glyphCount">
        /// Number of glyphs to retrieve adjustments for.
        /// </param>
        /// <param name="glyphIndices">
        /// Array of glyph id's to retrieve adjustments for.
        /// </param>
        /// <param name="glyphAdvanceAdjustments">
        /// Returned advances in font design units for each glyph. The last 
        /// glyph adjustment is zero.
        /// </param>
        /// <remarks>
        /// This is not a direct replacement for GDI's character based
        /// GetKerningPairs, but it serves the same role, without the client
        /// needing to cache them locally. It also uses glyph id's directly
        /// rather than UCS-2 characters (how the kern table actually stores
        /// them) which avoids glyph collapse and ambiguity, such as the dash
        /// and hyphen, or space and non-breaking space.
        /// </remarks>
        /// <remarks>
        /// Newer fonts may have only GPOS kerning instead of the legacy pair
        /// table kerning. Such fonts, like Gabriola, will only return 0's for
        /// adjustments. This function does not virtualize and flatten these
        /// GPOS entries into kerning pairs.
        /// </remarks>
        void GetKerningPairAdjustments( UINT32 glyphCount, _In_reads_( glyphCount ) UINT16 const* glyphIndices, _Out_writes_( glyphCount ) INT32* glyphAdvanceAdjustments ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetKerningPairAdjustments( glyphCount, glyphIndices, glyphAdvanceAdjustments );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Retrieves the kerning pair adjustments from the font's kern table.
        /// </summary>
        /// <param name="glyphIndices">
        /// A std::span&lt;UInt16&gt; of glyph id's to retrieve adjustments for.
        /// </param>
        /// <param name="glyphAdvanceAdjustments">
        /// Returned advances in font design units for each glyph. The last 
        /// glyph adjustment is zero.
        /// </param>
        void GetKerningPairAdjustments( const std::span<UInt16>& glyphIndices, INT32* glyphAdvanceAdjustments ) const
        {
            assert( glyphIndices.size( ) <= static_cast< size_t >( MaxUInt32 ) );
            GetKerningPairAdjustments( static_cast<UInt32>( glyphIndices.size() ), glyphIndices.data( ), glyphAdvanceAdjustments );
        }


        /// <summary>
        /// Retrieves the kerning pair adjustments from the font's kern table.
        /// </summary>
        /// <param name="glyphCount">
        /// Number of glyphs to retrieve adjustments for.
        /// </param>
        /// <param name="glyphIndices">
        /// Array of glyph id's to retrieve adjustments for.
        /// </param>
        /// <returns>
        /// std::vector&lt;Int32&gt; of advances in font design units for each 
        /// glyph. The last glyph adjustment is zero.
        /// </returns>
        std::vector<Int32> GetKerningPairAdjustments( UINT32 glyphCount, _In_reads_( glyphCount ) UINT16 const* glyphIndices ) const
        {
            std::vector<Int32> result( glyphCount );
            GetKerningPairAdjustments( glyphCount, glyphIndices, result.data( ) );
            return result;
        }

        /// <summary>
        /// Retrieves the kerning pair adjustments from the font's kern table.
        /// </summary>
        /// <param name="glyphIndices">
        /// A std::span&lt;UInt16&gt; of glyph id's to retrieve adjustments for.
        /// </param>
        /// <returns>
        /// std::vector&lt;Int32&gt; of advances in font design units for each 
        /// glyph. The last glyph adjustment is zero.
        /// </returns>
        std::vector<Int32> GetKerningPairAdjustments( const std::span<UInt16>& glyphIndices ) const
        {
            assert( glyphIndices.size( ) <= static_cast< size_t >( MaxUInt32 ) );
            std::vector<INT32> result( glyphIndices.size( ) );
            GetKerningPairAdjustments( static_cast< UInt32 >( glyphIndices.size( ) ), glyphIndices.data( ), result.data( ) );
            return result;
        }



        /// <summary>
        /// Returns whether or not the font supports pair-kerning.
        /// </summary>
        /// <remarks>
        /// If the font does not support pair table kerning, there is no need to
        /// call GetKerningPairAdjustments (it would be all zeroes).
        /// </remarks>
        /// <returns>
        /// Whether the font supports kerning pairs.
        /// </returns>
        bool HasKerningPairs( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->HasKerningPairs( ) != FALSE;
        }

        /// <summary>
        /// Determines the recommended text rendering mode to be used based on the
        /// font, size, world transform, and measuring mode.
        /// </summary>
        /// <param name="fontEmSize">
        /// Logical font size in DIPs.
        /// </param>
        /// <param name="dpiX">
        /// Number of pixels per logical inch in the horizontal direction.
        /// </param>
        /// <param name="dpiY">
        /// Number of pixels per logical inch in the vertical direction.
        /// </param>
        /// <param name="transform">
        /// Specifies the world transform.
        /// </param>
        /// <param name="outlineThreshold">
        /// Specifies the quality of the graphics system's outline rendering,
        /// affects the size threshold above which outline rendering is used.
        /// </param>
        /// <param name="measuringMode">
        /// Specifies the method used to measure during text layout. For proper 
        /// glyph spacing, the function returns a rendering mode that is compatible 
        /// with the specified measuring mode.
        /// </param>
        /// <param name="renderingMode">
        /// Receives the recommended rendering mode.
        /// </param>
        /// <remarks>
        /// This method should be used to determine the actual rendering mode in cases where the rendering 
        /// mode of the rendering params object is DWRITE_RENDERING_MODE_DEFAULT.
        /// </remarks>
        void GetRecommendedRenderingMode( FLOAT fontEmSize, FLOAT dpiX, FLOAT dpiY, _In_opt_ DWRITE_MATRIX const* transform, BOOL isSideways, DWRITE_OUTLINE_THRESHOLD outlineThreshold, DWRITE_MEASURING_MODE measuringMode, _Out_ DWRITE_RENDERING_MODE* renderingMode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetRecommendedRenderingMode( fontEmSize, dpiX, dpiY, transform, isSideways, outlineThreshold, measuringMode, renderingMode );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Determines the recommended text rendering mode to be used based on the
        /// font, size, world transform, and measuring mode.
        /// </summary>
        /// <param name="fontEmSize">
        /// Logical font size in DIPs.
        /// </param>
        /// <param name="dpiX">
        /// Number of pixels per logical inch in the horizontal direction.
        /// </param>
        /// <param name="dpiY">
        /// Number of pixels per logical inch in the vertical direction.
        /// </param>
        /// <param name="transform">
        /// Specifies the world transform.
        /// </param>
        /// <param name="outlineThreshold">
        /// Specifies the quality of the graphics system's outline rendering,
        /// affects the size threshold above which outline rendering is used.
        /// </param>
        /// <param name="measuringMode">
        /// Specifies the method used to measure during text layout. For proper 
        /// glyph spacing, the function returns a rendering mode that is compatible 
        /// with the specified measuring mode.
        /// </param>
        /// <returns>
        /// The recommended rendering mode.
        /// </returns>
        /// <remarks>
        /// This method should be used to determine the actual rendering mode in cases where the rendering 
        /// mode of the rendering params object is DWRITE_RENDERING_MODE_DEFAULT.
        /// </remarks>
        RenderingMode GetRecommendedRenderingMode( FLOAT fontEmSize, FLOAT dpiX, FLOAT dpiY, _In_opt_ DWRITE_MATRIX const* transform, BOOL isSideways, DWRITE_OUTLINE_THRESHOLD outlineThreshold, DWRITE_MEASURING_MODE measuringMode ) const
        {
            DWRITE_RENDERING_MODE result{};
            GetRecommendedRenderingMode( fontEmSize, dpiX, dpiY, transform, isSideways, outlineThreshold, measuringMode, &result );
            return static_cast< RenderingMode >( result );
        }


        /// <summary>
        /// Retrieves the vertical forms of the nominal glyphs retrieved from
        /// GetGlyphIndices, using the font's 'vert' table. This is used in
        /// CJK vertical layout so the correct characters are shown.
        /// </summary>
        /// <param name="glyphCount">
        /// Number of glyphs to retrieve.
        /// </param>
        /// <param name="nominalGlyphIndices">
        /// Original glyph indices from cmap.
        /// </param>
        /// <param name="verticalGlyphIndices">
        /// The vertical form of glyph indices.
        /// </param>
        /// <remarks>
        /// Call GetGlyphIndices to get the nominal glyph indices, followed by
        /// calling this to remap the to the substituted forms, when the run
        /// is sideways, and the font has vertical glyph variants.
        /// </remarks>
        void GetVerticalGlyphVariants( UINT32 glyphCount, _In_reads_( glyphCount ) UINT16 const* nominalGlyphIndices, _Out_writes_( glyphCount ) UINT16* verticalGlyphIndices ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetVerticalGlyphVariants( glyphCount, nominalGlyphIndices, verticalGlyphIndices );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Retrieves the vertical forms of the nominal glyphs retrieved from
        /// GetGlyphIndices, using the font's 'vert' table. This is used in
        /// CJK vertical layout so the correct characters are shown.
        /// </summary>
        /// <param name="nominalGlyphIndices">
        /// A std::span&lt;UInt16&gt; of original glyph indices from cmap.
        /// </param>
        /// <param name="verticalGlyphIndices">
        /// The returned vertical form of glyph indices.
        /// </param>
        void GetVerticalGlyphVariants( const std::span<UInt16>& nominalGlyphIndices, UINT16* verticalGlyphIndices ) const
        {
            assert( nominalGlyphIndices.size( ) <= static_cast< size_t >( MaxUInt32 ) );
            GetVerticalGlyphVariants( static_cast< UInt32 >( nominalGlyphIndices.size( ) ), nominalGlyphIndices.data( ), verticalGlyphIndices );
        }

        /// <summary>
        /// Retrieves the vertical forms of the nominal glyphs retrieved from
        /// GetGlyphIndices, using the font's 'vert' table. This is used in
        /// CJK vertical layout so the correct characters are shown.
        /// </summary>
        /// <param name="glyphCount">
        /// Number of glyphs to retrieve.
        /// </param>
        /// <param name="nominalGlyphIndices">
        /// Original glyph indices from cmap.
        /// </param>
        /// <returns>
        /// The vertical form of glyph indices.
        /// </returns>
        std::vector<UInt16> GetVerticalGlyphVariants( UINT32 glyphCount, _In_reads_( glyphCount ) UINT16 const* nominalGlyphIndices ) const
        {
            std::vector<UINT16> result( glyphCount );
            GetVerticalGlyphVariants( glyphCount, nominalGlyphIndices, result.data( ) );
            return result;
        }

        /// <summary>
        /// Retrieves the vertical forms of the nominal glyphs retrieved from
        /// GetGlyphIndices, using the font's 'vert' table. This is used in
        /// CJK vertical layout so the correct characters are shown.
        /// </summary>
        /// <param name="nominalGlyphIndices">
        /// A std::span&lt;UInt16&gt; of original glyph indices from cmap.
        /// </param>
        /// <returns>
        /// The vertical form of glyph indices.
        /// </returns>
        std::vector<UInt16> GetVerticalGlyphVariants( const std::span<UInt16>& nominalGlyphIndices) const
        {
            assert( nominalGlyphIndices.size( ) <= static_cast< size_t >( MaxUInt32 ) );
            std::vector<UINT16> result( nominalGlyphIndices.size( ) );
            GetVerticalGlyphVariants( static_cast< UInt32 >( nominalGlyphIndices.size( ) ), nominalGlyphIndices.data( ), result.data( ) );
            return result;
        }


        /// <summary>
        /// Returns whether or not the font has any vertical glyph variants.
        /// </summary>
        /// <remarks>
        /// For OpenType fonts, this will return true if the font contains a 'vert'
        /// feature.
        /// </remarks>
        /// <returns>
        /// True if the font contains vertical glyph variants.
        /// </returns>
        bool HasVerticalGlyphVariants( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->HasVerticalGlyphVariants( ) != FALSE;
        }

        using Base::GetMetrics;
        using Base::GetGdiCompatibleMetrics;
        using Base::GetRecommendedRenderingMode;

    };


    /// <summary>
    /// The Font1, a wrapper around the IDWriteFont1 interface, represents 
    /// a physical font in a font collection.
    /// </summary>
    class Font1 : public Font
    {
    public:
        typedef Font Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Font1, Font, IDWriteFont1, IDWriteFont )

        /// <summary>
        /// Gets common metrics for the font in design units.
        /// These metrics are applicable to all the glyphs within a font,
        /// and are used by applications for layout calculations.
        /// </summary>
        /// <param name="fontMetrics">
        /// Metrics structure to fill in.
        /// </param>
        void GetMetrics( _Out_ DWRITE_FONT_METRICS1* fontMetrics ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetMetrics( fontMetrics );
        }

        /// <summary>
        /// Gets common metrics for the font in design units.
        /// These metrics are applicable to all the glyphs within a font,
        /// and are used by applications for layout calculations.
        /// </summary>
        /// <returns>
        /// A FontMetrics1 structure containing the font metrics.
        /// </returns>
        FontMetrics1 GetMetrics( ) const
        {
            FontMetrics1 fontMetrics;
            GetMetrics( &fontMetrics );
            return fontMetrics;
        }

        using Base::GetMetrics;




        /// <summary>
        /// Gets the PANOSE values from the font, used for font selection and
        /// matching.
        /// </summary>
        /// <param name="panose">
        /// PANOSE structure to fill in.
        /// </param>
        /// <remarks>
        /// The function does not simulate these, such as substituting a weight or
        /// proportion inferred on other values. If the font does not specify them,
        /// they are all set to 'any' (0).
        /// </remarks>
        void GetPanose( _Out_ DWRITE_PANOSE* panose ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetPanose( panose );
        }

        /// <summary>
        /// Gets the PANOSE values from the font, used for font selection and
        /// matching.
        /// </summary>
        /// <param name="panose">
        /// Panose structure to fill in.
        /// </param>
        /// <remarks>
        /// The function does not simulate these, such as substituting a weight or
        /// proportion inferred on other values. If the font does not specify them,
        /// they are all set to 'any' (0).
        /// </remarks>
        void GetPanose( _Out_ Panose* panose ) const
        {
            if(panose)
            {
                GetPanose( &panose->Data );
            }
            else
            {
                InterfaceType* pInterface = GetInterface( );
                HCC_COM_CHECK_HRESULT2( E_POINTER, pInterface );
            }
        }

        /// <summary>
        /// Gets the PANOSE values from the font, used for font selection and
        /// matching.
        /// </summary>
        /// <returns>
        /// A Panose structure containing the PANOSE values.
        /// </returns>
        /// <remarks>
        /// The function does not simulate these, such as substituting a weight or
        /// proportion inferred on other values. If the font does not specify them,
        /// they are all set to 'any' (0).
        /// </remarks>
        Panose GetPanose( ) const
        {
            Panose panose;
            GetPanose( &panose.Data );
            return panose;
        }



        /// <summary>
        /// Returns the list of character ranges supported by the font, which is
        /// useful for scenarios like character picking, glyph display, and
        /// efficient font selection lookup. This is similar to GDI's
        /// GetFontUnicodeRanges, except that it returns the full Unicode range,
        /// not just 16-bit UCS-2.
        /// </summary>
        /// <param name="maxRangeCount">
        /// Maximum number of character ranges passed in from the client.
        /// </param>
        /// <param name="unicodeRanges">
        /// Array of character ranges.
        /// </param>
        /// <param name="actualRangeCount">
        /// Actual number of character ranges, regardless of the maximum count.
        /// </param>
        /// <remarks>
        /// These ranges are from the cmap, not the OS/2::ulCodePageRange1.
        /// </remarks>
        void GetUnicodeRanges(UINT32 maxRangeCount, _Out_writes_to_opt_( maxRangeCount, *actualRangeCount ) DWRITE_UNICODE_RANGE* unicodeRanges, _Out_ UINT32* actualRangeCount ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetUnicodeRanges( maxRangeCount, unicodeRanges, actualRangeCount );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Returns a vector of character ranges supported by the font, which is
        /// useful for scenarios like character picking, glyph display, and
        /// efficient font selection lookup. This is similar to GDI's
        /// GetFontUnicodeRanges, except that it returns the full Unicode range,
        /// not just 16-bit UCS-2.
        /// </summary>
        /// <returns>
        /// A vector of UnicodeRange structures.
        /// </returns>
        std::vector<UnicodeRange> GetUnicodeRanges( ) const
        {
            UINT32 actualRangeCount = 0;
            GetUnicodeRanges( 0, nullptr, &actualRangeCount );
            std::vector<UnicodeRange> result( actualRangeCount );
            GetUnicodeRanges( actualRangeCount, result.data( ), &actualRangeCount );
            return result;
        }


        /// <summary>
        /// Returns true if the font is monospaced, meaning its characters are the
        /// same fixed-pitch width (non-proportional).
        /// </summary>
        bool IsMonospacedFont( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->IsMonospacedFont( ) != FALSE;
        }

    };

    /// <summary>
    /// The interface that represents text rendering settings for glyph rasterization and filtering.
    /// </summary>
    class RenderingParams1 : public RenderingParams
    {
    public:
        typedef RenderingParams Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( RenderingParams1, RenderingParams, IDWriteRenderingParams1, IDWriteRenderingParams )


        /// <summary>
        /// Gets the amount of contrast enhancement to use for grayscale antialiasing.
        /// Valid values are greater than or equal to zero.
        /// </summary>
        FLOAT GetGrayscaleEnhancedContrast( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetGrayscaleEnhancedContrast( );
        }

    };

    /// <summary>
    /// Analyzes various text properties for complex script processing.
    /// </summary>
    class TextAnalyzer1 : public TextAnalyzer
    {
    public:
        typedef TextAnalyzer Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextAnalyzer1, TextAnalyzer, IDWriteTextAnalyzer1, IDWriteTextAnalyzer )



    };


    class TextLayout1 : public TextLayout
    {
    public:
        typedef TextLayout Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( TextLayout1, TextLayout, IDWriteTextLayout1, IDWriteTextLayout )

    };

    /// <summary>
    /// Represents the type of antialiasing to use for text when the rendering mode calls for
    /// antialiasing.
    /// </summary>
    enum class TextAntialiasMode
    {
        /// <summary>
        /// ClearType antialiasing computes coverage independently for the red, green, and blue
        /// color elements of each pixel. This allows for more detail than conventional antialiasing.
        /// However, because there is no one alpha value for each pixel, ClearType is not suitable
        /// rendering text onto a transparent intermediate bitmap.
        /// </summary>
        ClearType = DWRITE_TEXT_ANTIALIAS_MODE_CLEARTYPE,

        /// <summary>
        /// Grayscale antialiasing computes one coverage value for each pixel. Because the alpha
        /// value of each pixel is well-defined, text can be rendered onto a transparent bitmap, 
        /// which can then be composited with other content. Note that grayscale rendering with
        /// IDWriteBitmapRenderTarget1 uses premultiplied alpha.
        /// </summary>
        Grayscale = DWRITE_TEXT_ANTIALIAS_MODE_GRAYSCALE
    };


    class BitmapRenderTarget1 : public BitmapRenderTarget
    {
    public:
        typedef BitmapRenderTarget Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( BitmapRenderTarget1, BitmapRenderTarget, IDWriteBitmapRenderTarget1, IDWriteBitmapRenderTarget )

    };


    /// <summary>
    /// The root factory interface for all DWrite objects.
    /// </summary>
    class Factory1 : public Factory
    {
    public:
        typedef Factory Base;

        COMMON_GRAPHICS_STANDARD_METHODS_IMPL( Factory1, Factory, IDWriteFactory1, IDWriteFactory )

        /// <summary>
        /// Gets a font collection representing the set of end-user defined
        /// custom fonts.
        /// </summary>
        /// <param name="fontCollection">
        /// Receives a pointer to the EUDC font collection object, or NULL 
        /// in case of failure.
        /// </param>
        /// <param name="checkForUpdates">
        /// If this parameter is nonzero, the function performs an immediate 
        /// check for changes to the set of EUDC fonts. If this parameter is 
        /// FALSE, the function will still detect changes, but there may be 
        /// some latency. For example, an application might specify TRUE if 
        /// it has itself just modified a font and wants to be sure the font 
        /// collection contains that font.
        /// </param>
        /// <remarks>
        /// Querying via IDWriteFontCollection::FindFamilyName for a specific
        /// family (like MS Gothic) will return the matching family-specific EUDC
        /// font if one exists. Querying for "" will return the global EUDC font.
        /// For example, if you were matching an EUDC character within a run of
        /// the base font PMingLiu, you would retrieve the corresponding EUDC font
        /// face using GetEudcFontCollection, then FindFamilyName with "PMingLiu",
        /// followed by GetFontFamily and CreateFontFace.
        ///
        /// Be aware that eudcedit.exe can create placeholder empty glyphs that
        /// have zero advance width and no glyph outline. Although they are present
        /// in the font (HasCharacter returns true), you are best to ignore
        /// these and continue on with font fallback in your layout if the metrics
        /// for the glyph are zero.
        /// </remarks>
        void GetEudcFontCollection(_COM_Outptr_ IDWriteFontCollection** fontCollection, BOOL checkForUpdates = FALSE ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetEudcFontCollection( fontCollection, checkForUpdates );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets a font collection representing the set of end-user defined
        /// custom fonts.
        /// </summary>
        /// <param name="checkForUpdates">
        /// If this parameter is nonzero, the function performs an immediate 
        /// check for changes to the set of EUDC fonts. If this parameter is 
        /// FALSE, the function will still detect changes, but there may be 
        /// some latency. For example, an application might specify TRUE if 
        /// it has itself just modified a font and wants to be sure the font 
        /// collection contains that font.
        /// </param>
        /// <returns>
        /// A FontCollection object representing the set of end-user defined
        /// custom fonts.
        /// </returns>
        FontCollection GetEudcFontCollection( bool checkForUpdates = false ) const
        {
            IDWriteFontCollection* fontCollection = nullptr;
            GetEudcFontCollection( &fontCollection, checkForUpdates? TRUE : FALSE );
            FontCollection result( fontCollection );
            return result;
        }



        /// <summary>
        /// Creates a rendering parameters object with the specified properties.
        /// </summary>
        /// <param name="gamma">The gamma value used for gamma correction, which must be greater than zero and cannot exceed 256.</param>
        /// <param name="enhancedContrast">The amount of contrast enhancement, zero or greater.</param>
        /// <param name="enhancedContrastGrayscale">The amount of contrast enhancement to use for grayscale antialiasing, zero or greater.</param>
        /// <param name="clearTypeLevel">The degree of ClearType level, from 0.0f (no ClearType) to 1.0f (full ClearType).</param>
        /// <param name="pixelGeometry">The geometry of a device pixel.</param>
        /// <param name="renderingMode">Method of rendering glyphs. In most cases, this should be DWRITE_RENDERING_MODE_DEFAULT to automatically use an appropriate mode.</param>
        /// <param name="renderingParams">Holds the newly created rendering parameters object, or NULL in case of failure.</param>
        void CreateCustomRenderingParams(
                    FLOAT gamma,
                    FLOAT enhancedContrast,
                    FLOAT enhancedContrastGrayscale,
                    FLOAT clearTypeLevel,
                    DWRITE_PIXEL_GEOMETRY pixelGeometry,
                    DWRITE_RENDERING_MODE renderingMode,
                    _COM_Outptr_ IDWriteRenderingParams1** renderingParams) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->CreateCustomRenderingParams( gamma, enhancedContrast, enhancedContrastGrayscale, clearTypeLevel, pixelGeometry, renderingMode, renderingParams );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        using Base::CreateCustomRenderingParams;

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
