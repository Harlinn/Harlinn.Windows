#pragma once
/**********************************************************************
 * $Id$
 *
 * Name:     cpl_string.h
 * Project:  CPL - Common Portability Library
 * Purpose:  String and StringList functions.
 * Author:   Daniel Morissette, dmorissette@mapgears.com
 *
 **********************************************************************
 * Copyright (c) 1998, Daniel Morissette
 * Copyright (c) 2008-2014, Even Rouault <even dot rouault at spatialys.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#ifndef CPL_STRING_H_INCLUDED
#define CPL_STRING_H_INCLUDED

#include <port/cpl_error.h>
#include <port/cpl_conv.h>
#include <port/cpl_vsi.h>

/**
 * \file cpl_string.h
 *
 * Various convenience functions for working with strings and string lists.
 *
 * A StringList is just an array of strings with the last pointer being
 * NULL.  An empty StringList may be either a NULL pointer, or a pointer to
 * a pointer memory location with a NULL value.
 *
 * A common convention for StringLists is to use them to store name/value
 * lists.  In this case the contents are treated like a dictionary of
 * name/value pairs.  The actual data is formatted with each string having
 * the format "<name>:<value>" (though "=" is also an acceptable separator).
 * A number of the functions in the file operate on name/value style
 * string lists (such as CSLSetNameValue(), and CSLFetchNameValue()).
 *
 * To some extent the CPLStringList C++ class can be used to abstract
 * managing string lists a bit but still be able to return them from C
 * functions.
 *
 */

CPL_C_START

HGDAL_EXPORT char **CSLAddString(char **papszStrList,
                            const char *pszNewString) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT char **CSLAddStringMayFail(
    char **papszStrList, const char *pszNewString) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT int CSLCount(CSLConstList papszStrList);
HGDAL_EXPORT const char *CSLGetField( CSLConstList, int );
HGDAL_EXPORT void CPL_STDCALL CSLDestroy(char **papszStrList);
HGDAL_EXPORT char **CSLDuplicate(CSLConstList papszStrList) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT char **CSLMerge( char **papszOrig,
                         CSLConstList papszOverride ) CPL_WARN_UNUSED_RESULT;

HGDAL_EXPORT char **CSLTokenizeString(const char *pszString ) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT char **CSLTokenizeStringComplex(
    const char *pszString, const char *pszDelimiter, int bHonourStrings,
    int bAllowEmptyTokens ) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT char **CSLTokenizeString2( const char *pszString,
                                   const char *pszDelimiter,
                                   int nCSLTFlags ) CPL_WARN_UNUSED_RESULT;

/** Flag for CSLTokenizeString2() to honour strings */
#define CSLT_HONOURSTRINGS      0x0001
/** Flag for CSLTokenizeString2() to allow empty tokens */
#define CSLT_ALLOWEMPTYTOKENS   0x0002
/** Flag for CSLTokenizeString2() to preserve quotes */
#define CSLT_PRESERVEQUOTES     0x0004
/** Flag for CSLTokenizeString2() to preserve escape characters */
#define CSLT_PRESERVEESCAPES    0x0008
/** Flag for CSLTokenizeString2() to strip leading spaces */
#define CSLT_STRIPLEADSPACES    0x0010
/** Flag for CSLTokenizeString2() to strip trailaing spaces */
#define CSLT_STRIPENDSPACES     0x0020

HGDAL_EXPORT int CSLPrint(CSLConstList papszStrList, FILE *fpOut);
HGDAL_EXPORT char **CSLLoad(const char *pszFname) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT char **CSLLoad2(
    const char *pszFname, int nMaxLines, int nMaxCols,
    CSLConstList papszOptions) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT int CSLSave(CSLConstList papszStrList, const char *pszFname);

HGDAL_EXPORT char **CSLInsertStrings(char **papszStrList, int nInsertAtLineNo,
                        CSLConstList papszNewLines) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT char **CSLInsertString(char **papszStrList, int nInsertAtLineNo,
                               const char *pszNewLine) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT char **CSLRemoveStrings(
    char **papszStrList, int nFirstLineToDelete,
    int nNumToRemove, char ***ppapszRetStrings) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT int CSLFindString( CSLConstList papszList, const char *pszTarget );
HGDAL_EXPORT int CSLFindStringCaseSensitive( CSLConstList papszList,
                                        const char *pszTarget );
HGDAL_EXPORT int CSLPartialFindString( CSLConstList papszHaystack,
                                  const char *pszNeedle );
HGDAL_EXPORT int CSLFindName(CSLConstList papszStrList, const char *pszName);
HGDAL_EXPORT int CSLFetchBoolean( CSLConstList papszStrList, const char *pszKey,
                             int bDefault );

/* TODO: Deprecate CSLTestBoolean.  Remove in GDAL 3.x. */
HGDAL_EXPORT int CSLTestBoolean( const char *pszValue );
/* Do not use CPLTestBoolean in C++ code.  Use CPLTestBool. */
HGDAL_EXPORT int CPLTestBoolean( const char *pszValue );

#if defined(__cplusplus) && !defined(CPL_SUPRESS_CPLUSPLUS)
#ifdef DO_NOT_USE_DEBUG_BOOL
#define CPLTestBool(x) CPL_TO_BOOL(CPLTestBoolean(x))
#define CPLFetchBool(list,key,default) \
    CPL_TO_BOOL(CSLFetchBoolean(list,key,default))
#else /* DO_NOT_USE_DEBUG_BOOL */
/* Prefer these for C++ code. */
#ifdef DEBUG_BOOL
extern "C++" {
#endif
HGDAL_EXPORT bool CPLTestBool( const char *pszValue );
HGDAL_EXPORT bool CPLFetchBool( CSLConstList papszStrList, const char *pszKey,
                           bool bDefault );
#ifdef DEBUG_BOOL
}
#endif
#endif
#endif  /* __cplusplus */

HGDAL_EXPORT const char *
      CPLParseNameValue( const char *pszNameValue, char **ppszKey );

HGDAL_EXPORT const char*
      CSLFetchNameValue( CSLConstList papszStrList, const char *pszName);
HGDAL_EXPORT const char*
      CSLFetchNameValueDef( CSLConstList papszStrList,
                            const char *pszName,
                            const char *pszDefault );
HGDAL_EXPORT char**
      CSLFetchNameValueMultiple(CSLConstList papszStrList, const char *pszName);
HGDAL_EXPORT char**
      CSLAddNameValue(char **papszStrList,
                      const char *pszName,
                      const char *pszValue) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT char**
      CSLSetNameValue(char **papszStrList,
                      const char *pszName,
                      const char *pszValue) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT void CSLSetNameValueSeparator( char ** papszStrList,
                                       const char *pszSeparator );

HGDAL_EXPORT char** CSLParseCommandLine(const char* pszCommandLine);

/** Scheme for CPLEscapeString()/CPLUnescapeString() for backlash quoting */
#define CPLES_BackslashQuotable 0
/** Scheme for CPLEscapeString()/CPLUnescapeString() for XML */
#define CPLES_XML               1
/** Scheme for CPLEscapeString()/CPLUnescapeString() for URL */
#define CPLES_URL               2
/** Scheme for CPLEscapeString()/CPLUnescapeString() for SQL */
#define CPLES_SQL               3
/** Scheme for CPLEscapeString()/CPLUnescapeString() for CSV */
#define CPLES_CSV               4
/** Scheme for CPLEscapeString()/CPLUnescapeString() for XML (preserves quotes) */
#define CPLES_XML_BUT_QUOTES    5
/** Scheme for CPLEscapeString()/CPLUnescapeString() for CSV (forced quoting) */
#define CPLES_CSV_FORCE_QUOTING 6
/** Scheme for CPLEscapeString()/CPLUnescapeString() for SQL identifiers */
#define CPLES_SQLI              7

HGDAL_EXPORT char *CPLEscapeString( const char *pszString, int nLength,
                               int nScheme ) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT char *CPLUnescapeString( const char *pszString, int *pnLength,
                                 int nScheme ) CPL_WARN_UNUSED_RESULT;

HGDAL_EXPORT char *CPLBinaryToHex( int nBytes,
                              const GByte *pabyData ) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT GByte *CPLHexToBinary( const char *pszHex,
                               int *pnBytes ) CPL_WARN_UNUSED_RESULT;

HGDAL_EXPORT char *CPLBase64Encode( int nBytes,
                               const GByte *pabyData ) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT int CPLBase64DecodeInPlace( GByte* pszBase64 ) CPL_WARN_UNUSED_RESULT;

/** Type of value */
typedef enum
{
    CPL_VALUE_STRING,  /**< String */
    CPL_VALUE_REAL,    /**< Real number */
    CPL_VALUE_INTEGER  /**< Integer */
} CPLValueType;

HGDAL_EXPORT CPLValueType CPLGetValueType(const char* pszValue);

HGDAL_EXPORT size_t CPLStrlcpy(char* pszDest, const char* pszSrc, size_t nDestSize);
HGDAL_EXPORT size_t CPLStrlcat(char* pszDest, const char* pszSrc, size_t nDestSize);
HGDAL_EXPORT size_t CPLStrnlen(const char *pszStr, size_t nMaxLen);

/* -------------------------------------------------------------------- */
/*      Locale independent formatting functions.                        */
/* -------------------------------------------------------------------- */
HGDAL_EXPORT int CPLvsnprintf( char *str, size_t size,
                          CPL_FORMAT_STRING(const char* fmt),
                          va_list args )
    CPL_PRINT_FUNC_FORMAT(3, 0 );

/* ALIAS_CPLSNPRINTF_AS_SNPRINTF might be defined to enable GCC 7 */
/* -Wformat-truncation= warnings, but shouldn't be set for normal use */
#if defined(ALIAS_CPLSNPRINTF_AS_SNPRINTF)
#define CPLsnprintf snprintf
#else
HGDAL_EXPORT int CPLsnprintf( char *str, size_t size,
                         CPL_FORMAT_STRING(const char* fmt), ... )
    CPL_PRINT_FUNC_FORMAT(3, 4);
#endif

/*! @cond Doxygen_Suppress */
#if defined(GDAL_COMPILATION) && !defined(DONT_DEPRECATE_SPRINTF)
HGDAL_EXPORT int CPLsprintf( char *str, CPL_FORMAT_STRING(const char* fmt), ... )
    CPL_PRINT_FUNC_FORMAT(2, 3)
    CPL_WARN_DEPRECATED("Use CPLsnprintf instead");
#else
int CPL_DLL CPLsprintf( char *str, CPL_FORMAT_STRING(const char* fmt), ... )
    CPL_PRINT_FUNC_FORMAT(2, 3);
#endif
/*! @endcond */
HGDAL_EXPORT int CPLprintf( CPL_FORMAT_STRING(const char* fmt), ... )
    CPL_PRINT_FUNC_FORMAT(1, 2);

/* For some reason Doxygen_Suppress is needed to avoid warning. Not sure why */
/*! @cond Doxygen_Suppress */
/* caution: only works with limited number of formats */
HGDAL_EXPORT int CPLsscanf( const char* str,
                       CPL_SCANF_FORMAT_STRING(const char* fmt), ... )
    CPL_SCAN_FUNC_FORMAT(2, 3);
/*! @endcond */

HGDAL_EXPORT const char *CPLSPrintf( CPL_FORMAT_STRING(const char *fmt), ... )
    CPL_PRINT_FUNC_FORMAT(1, 2) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT char **CSLAppendPrintf( char **papszStrList,
                                CPL_FORMAT_STRING(const char *fmt), ... )
    CPL_PRINT_FUNC_FORMAT(2, 3) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT int CPLVASPrintf( char **buf,
                          CPL_FORMAT_STRING(const char *fmt), va_list args )
    CPL_PRINT_FUNC_FORMAT(2, 0);

/* -------------------------------------------------------------------- */
/*      RFC 23 character set conversion/recoding API (cpl_recode.cpp).  */
/* -------------------------------------------------------------------- */
/** Encoding of the current locale */
#define CPL_ENC_LOCALE     ""
/** UTF-8 encoding */
#define CPL_ENC_UTF8       "UTF-8"
/** UTF-16 encoding */
#define CPL_ENC_UTF16      "UTF-16"
/** UCS-2 encoding */
#define CPL_ENC_UCS2       "UCS-2"
/** UCS-4 encoding */
#define CPL_ENC_UCS4       "UCS-4"
/** ASCII encoding */
#define CPL_ENC_ASCII      "ASCII"
/** ISO-8859-1 (LATIN1) encoding */
#define CPL_ENC_ISO8859_1  "ISO-8859-1"

HGDAL_EXPORT int CPLEncodingCharSize( const char *pszEncoding );
/*! @cond Doxygen_Suppress */
HGDAL_EXPORT void CPLClearRecodeWarningFlags( void );
/*! @endcond */
HGDAL_EXPORT char *CPLRecode(
    const char *pszSource, const char *pszSrcEncoding,
    const char *pszDstEncoding ) CPL_WARN_UNUSED_RESULT CPL_RETURNS_NONNULL;
HGDAL_EXPORT char *CPLRecodeFromWChar(
    const wchar_t *pwszSource, const char *pszSrcEncoding,
    const char *pszDstEncoding ) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT wchar_t *CPLRecodeToWChar(
    const char *pszSource, const char *pszSrcEncoding,
    const char *pszDstEncoding ) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT int CPLIsUTF8( const char* pabyData, int nLen );
HGDAL_EXPORT char *CPLForceToASCII(
    const char* pabyData, int nLen,
    char chReplacementChar ) CPL_WARN_UNUSED_RESULT;
HGDAL_EXPORT int CPLStrlenUTF8( const char *pszUTF8Str );
HGDAL_EXPORT int CPLCanRecode(
    const char *pszTestStr, const char *pszSrcEncoding,
    const char *pszDstEncoding) CPL_WARN_UNUSED_RESULT;
CPL_C_END

/************************************************************************/
/*                              CPLString                               */
/************************************************************************/

#if defined(__cplusplus) && !defined(CPL_SUPRESS_CPLUSPLUS)

extern "C++"
{
#ifndef DOXYGEN_SKIP
#include <string>
#endif

// VC++ implicitly applies __declspec(dllexport) to template base classes
// of classes marked with __declspec(dllexport).
// Hence, if marked with CPL_DLL, VC++ would export symbols for the specialization
// of std::basic_string<char>, since it is a base class of CPLString.
// As a result, if an application linked both gdal.dll and a static library that
// (implicitly) instantiates std::string (almost all do!), then the linker would
// emit an error concerning duplicate symbols for std::string.
// The least intrusive solution is to not mark the whole class with
// __declspec(dllexport) for VC++, but only its non-inline methods.
#ifdef _MSC_VER
#  define CPLSTRING_CLASS_DLL
#  define CPLSTRING_METHOD_DLL CPL_DLL
#else
/*! @cond Doxygen_Suppress */
#  define CPLSTRING_CLASS_DLL CPL_DLL
#  define CPLSTRING_METHOD_DLL
/*! @endcond */
#endif

//! Convenient string class based on std::string.
class CPLString : public std::string
{
public:

    /** Constructor */
    CPLString(void) {}
    /** Constructor */
    // cppcheck-suppress noExplicitConstructor
    CPLString( const std::string &oStr ) : std::string( oStr ) {}
    /** Constructor */
    // cppcheck-suppress noExplicitConstructor
    CPLString( const char *pszStr ) : std::string( pszStr ) {}
    /** Constructor */
    CPLString( const char *pszStr, size_t n ) : std::string( pszStr, n ) {}

    /** Return string as zero terminated character array */
    operator const char* (void) const { return c_str(); }

    /** Return character at specified index */
    char& operator[](std::string::size_type i)
    {
        return std::string::operator[](i);
    }

    /** Return character at specified index */
    const char& operator[](std::string::size_type i) const
    {
        return std::string::operator[](i);
    }

    /** Return character at specified index */
    char& operator[](int i)
    {
        return std::string::operator[](
            static_cast<std::string::size_type>(i));
    }

    /** Return character at specified index */
    const char& operator[](int i) const
    {
        return std::string::operator[](
            static_cast<std::string::size_type>(i));
    }

    /** Clear the string */
    void Clear() { resize(0); }

    /** Assign specified string and take ownership of it (assumed to be
     * allocated with CPLMalloc()). NULL can be safely passed to clear the
     * string. */
    void Seize( char *pszValue )
    {
        if (pszValue == nullptr )
            Clear();
        else
        {
            *this = pszValue;
            CPLFree(pszValue);
        }
    }

    /* There seems to be a bug in the way the compiler count indices...
     * Should be CPL_PRINT_FUNC_FORMAT (1, 2) */
    HGDAL_EXPORT CPLString &Printf(
        CPL_FORMAT_STRING(const char *pszFormat), ... )
        CPL_PRINT_FUNC_FORMAT (2, 3);
    HGDAL_EXPORT CPLString &vPrintf(
        CPL_FORMAT_STRING(const char *pszFormat), va_list args )
        CPL_PRINT_FUNC_FORMAT(2, 0);
    HGDAL_EXPORT CPLString &FormatC( double dfValue, const char *pszFormat = nullptr );
    HGDAL_EXPORT CPLString &Trim();
    HGDAL_EXPORT CPLString &Recode( const char *pszSrcEncoding, const char *pszDstEncoding );
    HGDAL_EXPORT CPLString &replaceAll(
        const std::string &osBefore, const std::string& osAfter );
    HGDAL_EXPORT CPLString &replaceAll( const std::string &osBefore, char chAfter );
    HGDAL_EXPORT CPLString &replaceAll( char chBefore, const std::string &osAfter );
    HGDAL_EXPORT CPLString &replaceAll( char chBefore, char chAfter );

    /* case insensitive find alternates */
    HGDAL_EXPORT size_t    ifind( const std::string & str, size_t pos = 0 ) const;
    HGDAL_EXPORT size_t    ifind( const char * s, size_t pos = 0 ) const;
    HGDAL_EXPORT CPLString &toupper( void );
    HGDAL_EXPORT CPLString &tolower( void );

    HGDAL_EXPORT bool      endsWith( const std::string& osStr ) const;
};

#undef CPLSTRING_CLASS_DLL
#undef CPLSTRING_METHOD_DLL

HGDAL_EXPORT CPLString CPLOPrintf(CPL_FORMAT_STRING(const char *pszFormat), ... )
    CPL_PRINT_FUNC_FORMAT (1, 2);
HGDAL_EXPORT CPLString CPLOvPrintf(
    CPL_FORMAT_STRING(const char *pszFormat), va_list args)
    CPL_PRINT_FUNC_FORMAT (1, 0);
HGDAL_EXPORT CPLString CPLQuotedSQLIdentifier(const char *pszIdent);

/* -------------------------------------------------------------------- */
/*      URL processing functions, here since they depend on CPLString.  */
/* -------------------------------------------------------------------- */
HGDAL_EXPORT CPLString CPLURLGetValue(const char* pszURL, const char* pszKey);
HGDAL_EXPORT CPLString CPLURLAddKVP(const char* pszURL, const char* pszKey,
                               const char* pszValue);

/************************************************************************/
/*                            CPLStringList                             */
/************************************************************************/

//! String list class designed around our use of C "char**" string lists.
class CPLStringList
{
    char **papszList = nullptr;
    mutable int nCount = 0;
    mutable int nAllocation = 0;
    bool   bOwnList = false;
    bool   bIsSorted = false;

    void   MakeOurOwnCopy();
    void   EnsureAllocation( int nMaxLength );
    int    FindSortedInsertionPoint( const char *pszLine );

  public:
    HGDAL_EXPORT CPLStringList();
    HGDAL_EXPORT explicit CPLStringList( char **papszList, int bTakeOwnership=TRUE );
    HGDAL_EXPORT explicit CPLStringList( CSLConstList papszList );
    HGDAL_EXPORT CPLStringList( const CPLStringList& oOther );
    HGDAL_EXPORT ~CPLStringList();

    HGDAL_EXPORT CPLStringList &Clear();

    /** Return size of list */
    int    size() const { return Count(); }
    HGDAL_EXPORT int    Count() const;

    /** Return whether the list is empty. */
    bool   empty() const { return Count() == 0; }

    HGDAL_EXPORT CPLStringList &AddString( const char *pszNewString );
    HGDAL_EXPORT CPLStringList &AddStringDirectly( char *pszNewString );

    CPLStringList &InsertString( int nInsertAtLineNo, const char *pszNewLine )
    { return InsertStringDirectly( nInsertAtLineNo, CPLStrdup(pszNewLine) ); }
    HGDAL_EXPORT CPLStringList &InsertStringDirectly( int nInsertAtLineNo, char *pszNewLine);

    // CPLStringList &InsertStrings( int nInsertAtLineNo, char **papszNewLines );
    // CPLStringList &RemoveStrings( int nFirstLineToDelete, int nNumToRemove=1 );

    /** Return index of pszTarget in the list, or -1 */
    int    FindString( const char *pszTarget ) const
    { return CSLFindString( papszList, pszTarget ); }
    /** Return index of pszTarget in the list (using partial search), or -1 */
    int    PartialFindString( const char *pszNeedle ) const
    { return CSLPartialFindString( papszList, pszNeedle ); }

    HGDAL_EXPORT int    FindName( const char *pszName ) const;
    HGDAL_EXPORT bool   FetchBool( const char *pszKey, bool bDefault ) const;
    // Deprecated.
    HGDAL_EXPORT int    FetchBoolean( const char *pszKey, int bDefault ) const;
    HGDAL_EXPORT const char *FetchNameValue( const char *pszKey ) const;
    HGDAL_EXPORT const char *FetchNameValueDef(
        const char *pszKey, const char *pszDefault ) const;
    HGDAL_EXPORT CPLStringList &AddNameValue( const char *pszKey, const char *pszValue );
    HGDAL_EXPORT CPLStringList &SetNameValue( const char *pszKey, const char *pszValue );

    HGDAL_EXPORT CPLStringList &Assign( char **papszListIn, int bTakeOwnership=TRUE );
    /** Assignment operator */
    CPLStringList &operator=(char **papszListIn) {
      return Assign( papszListIn, TRUE ); }
    /** Assignment operator */
    HGDAL_EXPORT CPLStringList &operator=(const CPLStringList& oOther);
    /** Assignment operator */
    HGDAL_EXPORT CPLStringList &operator=(CSLConstList papszListIn);
    /** Move assignment operator */
    HGDAL_EXPORT CPLStringList &operator=(CPLStringList&& oOther);

    /** Return string at specified index */
    HGDAL_EXPORT char * operator[](int i);
    /** Return string at specified index */
    char * operator[](size_t i) { return (*this)[static_cast<int>(i)]; }
    /** Return string at specified index */
    HGDAL_EXPORT const char * operator[](int i) const;
    /** Return string at specified index */
    const char * operator[](size_t i) const {
      return (*this)[static_cast<int>(i)]; }
    /** Return value corresponding to pszKey, or nullptr */
    const char * operator[](const char* pszKey) const {
        return FetchNameValue(pszKey); }

    /** Return list. Ownership remains to the object */
    char** List() { return papszList; }
    /** Return list. Ownership remains to the object */
    CSLConstList List() const { return papszList; }
    HGDAL_EXPORT char **StealList();

    HGDAL_EXPORT CPLStringList &Sort();
    /** Returns whether the list is sorted */
    int    IsSorted() const { return bIsSorted; }

    /** Return lists */
    operator char**(void) { return List(); }
    /** Return lists */
    operator CSLConstList(void) const { return List(); }
};

#ifdef GDAL_COMPILATION

#include <memory>

/*! @cond Doxygen_Suppress */
struct CSLDestroyReleaser
{
    void operator()(char** papszStr) const { CSLDestroy(papszStr); }
};
/*! @endcond */

/** Unique pointer type to use with CSL functions returning a char** */
using CSLUniquePtr = std::unique_ptr< char*, CSLDestroyReleaser>;

/*! @cond Doxygen_Suppress */
struct CPL_DLL CPLFreeReleaser
{
    void operator()(void* p) const { CPLFree(p); }
};
/*! @endcond */

/** Unique pointer type to use with functions returning a char* to release with CPLFree */
using CPLCharUniquePtr = std::unique_ptr<char, CPLFreeReleaser>;

#endif

} // extern "C++"

#endif /* def __cplusplus && !CPL_SUPRESS_CPLUSPLUS */

#endif /* CPL_STRING_H_INCLUDED */
