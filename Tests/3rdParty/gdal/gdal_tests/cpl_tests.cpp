#include "test_utils.h"

#include "port/cpl_compressor.h"
#include "port/cpl_error.h"
#include "port/cpl_hash_set.h"
#include "port/cpl_list.h"
#include "port/cpl_sha256.h"
#include "port/cpl_string.h"
#include "port/cpl_safemaths.hpp"
#include "port/cpl_time.h"
#include "port/cpl_json.h"
#include "port/cpl_json_streaming_parser.h"
#include "port/cpl_json_streaming_writer.h"
#include "port/cpl_mem_cache.h"
#include "port/cpl_http.h"
#include "port/cpl_auto_close.h"
#include "port/cpl_minixml.h"
#include "port/cpl_quad_tree.h"
#include "port/cpl_worker_thread_pool.h"

#include <iostream>
#include <fstream>

namespace
{
    static bool gbGotError = false;
    static void CPL_STDCALL myErrorHandler( CPLErr, CPLErrorNum, const char* )
    {
        gbGotError = true;
    }


    TEST( CPL, CPLListAPI )
    {
        CPLList* list = CPLListInsert( nullptr, ( void* )nullptr, 0 );
        EXPECT_EQ( CPLListCount( list ), 1 );
        list = CPLListRemove( list, 2 );
        EXPECT_EQ( CPLListCount( list ), 1 );
        list = CPLListRemove( list, 1 );
        EXPECT_EQ( CPLListCount( list ), 1 );
        list = CPLListRemove( list, 0 );
        EXPECT_EQ( CPLListCount( list ), 0 );
        list = nullptr;

        list = CPLListInsert( nullptr, ( void* )nullptr, 2 );
        EXPECT_EQ( CPLListCount( list ), 3 );
        list = CPLListRemove( list, 2 );
        EXPECT_EQ( CPLListCount( list ), 2 );
        list = CPLListRemove( list, 1 );
        EXPECT_EQ( CPLListCount( list ), 1 );
        list = CPLListRemove( list, 0 );
        EXPECT_EQ( CPLListCount( list ), 0 );
        list = nullptr;

        list = CPLListAppend( list, (void*)1 );
        EXPECT_EQ( CPLListGet( list, 0 ), list );
        EXPECT_EQ( CPLListGet( list, 1 ), nullptr );
        list = CPLListAppend( list, (void*)2 );
        list = CPLListInsert( list, (void*)3, 2 );
        EXPECT_EQ( CPLListCount( list ), 3 );
        CPLListDestroy( list );
        list = nullptr;

        list = CPLListAppend( list, (void*)1 );
        list = CPLListAppend( list, (void*)2 );
        list = CPLListInsert( list, (void*)4, 3 );
        CPLListGet( list, 2 )->pData = (void*)3;
        EXPECT_EQ( CPLListCount( list ), 4 );
        EXPECT_EQ( CPLListGet( list, 0 )->pData, (void*)1 );
        EXPECT_EQ( CPLListGet( list, 1 )->pData, (void*)2 );
        EXPECT_EQ( CPLListGet( list, 2 )->pData, (void*)3 );
        EXPECT_EQ( CPLListGet( list, 3 )->pData, (void*)4 );
        CPLListDestroy( list );
        list = nullptr;

        list = CPLListInsert( list, (void*)4, 1 );
        CPLListGet( list, 0 )->pData = (void*)2;
        list = CPLListInsert( list, (void*)1, 0 );
        list = CPLListInsert( list, (void*)3, 2 );
        EXPECT_EQ( CPLListCount( list ), 4 );
        EXPECT_EQ( CPLListGet( list, 0 )->pData, (void*)1 );
        EXPECT_EQ( CPLListGet( list, 1 )->pData, (void*)2 );
        EXPECT_EQ( CPLListGet( list, 2 )->pData, (void*)3 );
        EXPECT_EQ( CPLListGet( list, 3 )->pData, (void*)4 );
        list = CPLListRemove( list, 1 );
        list = CPLListRemove( list, 1 );
        list = CPLListRemove( list, 0 );
        list = CPLListRemove( list, 0 );
        EXPECT_EQ( list, nullptr );
    }


    struct TestStringStruct
    {
        const char* testString;
        CPLValueType expectedResult;
    };

    TEST( CPL, CPLGetValueTypeAPI )
    {
        TestStringStruct apszTestStrings[] =
        {
            { "+25.e+3", CPL_VALUE_REAL },
            { "-25.e-3", CPL_VALUE_REAL },
            { "25.e3", CPL_VALUE_REAL },
            { "25e3", CPL_VALUE_REAL },
            { " 25e3 ", CPL_VALUE_REAL },
            { ".1e3", CPL_VALUE_REAL },

            { "25", CPL_VALUE_INTEGER },
            { "-25", CPL_VALUE_INTEGER },
            { "+25", CPL_VALUE_INTEGER },

            { "25e 3", CPL_VALUE_STRING },
            { "25e.3", CPL_VALUE_STRING },
            { "-2-5e3", CPL_VALUE_STRING },
            { "2-5e3", CPL_VALUE_STRING },
            { "25.25.3", CPL_VALUE_STRING },
            { "25e25e3", CPL_VALUE_STRING },
            { "25e2500", CPL_VALUE_STRING }, /* #6128 */

            { "d1", CPL_VALUE_STRING } /* #6305 */
        };

        size_t i;
        for ( i = 0; i < sizeof( apszTestStrings ) / sizeof( apszTestStrings[0] ); i++ )
        {
            EXPECT_EQ( CPLGetValueType( apszTestStrings[i].testString ), apszTestStrings[i].expectedResult );
            if ( CPLGetValueType( apszTestStrings[i].testString ) != apszTestStrings[i].expectedResult )
                fprintf( stderr, "mismatch on item %d : value=\"%s\", expect_result=%d, result=%d\n", (int)i,
                    apszTestStrings[i].testString,
                    apszTestStrings[i].expectedResult,
                    CPLGetValueType( apszTestStrings[i].testString ) );
        }
    }

    TEST( CPL, CPLHashSetAPI1 )
    {
        CPLHashSet* set = CPLHashSetNew( CPLHashSetHashStr, CPLHashSetEqualStr, CPLFree );
        EXPECT_EQ( CPLHashSetInsert( set, CPLStrdup( "hello" ) ), TRUE );
        EXPECT_EQ( CPLHashSetInsert( set, CPLStrdup( "good morning" ) ), TRUE );
        EXPECT_EQ( CPLHashSetInsert( set, CPLStrdup( "bye bye" ) ), TRUE );
        EXPECT_EQ( CPLHashSetSize( set ), 3 );
        EXPECT_EQ( CPLHashSetInsert( set, CPLStrdup( "bye bye" ) ), FALSE );
        EXPECT_EQ( CPLHashSetSize( set ), 3 );
        EXPECT_EQ( CPLHashSetRemove( set, "bye bye" ), TRUE );
        EXPECT_EQ( CPLHashSetSize( set ), 2 );
        EXPECT_EQ( CPLHashSetRemove( set, "good afternoon" ), FALSE );
        EXPECT_EQ( CPLHashSetSize( set ), 2 );
        CPLHashSetDestroy( set );
    }



    TEST( CPL, CPLHashSetAPI2 )
    {
        auto sumValues = []( void* elt, void* user_data )
        {
            int* pnSum = (int*)user_data;
            *pnSum += *(int*)elt;
            return TRUE;
        };
        const int HASH_SET_SIZE = 1000;

        int data[HASH_SET_SIZE];
        for ( int i = 0; i < HASH_SET_SIZE; ++i )
        {
            data[i] = i;
        }

        CPLHashSet* set = CPLHashSetNew( nullptr, nullptr, nullptr );
        for ( int i = 0; i < HASH_SET_SIZE; i++ )
        {
            EXPECT_EQ( CPLHashSetInsert( set, (void*)&data[i] ), TRUE );
        }
        EXPECT_EQ( CPLHashSetSize( set ), HASH_SET_SIZE );

        for ( int i = 0; i < HASH_SET_SIZE; i++ )
        {
            EXPECT_EQ( CPLHashSetInsert( set, (void*)&data[i] ), FALSE );
        }
        EXPECT_EQ( CPLHashSetSize( set ), HASH_SET_SIZE );

        for ( int i = 0; i < HASH_SET_SIZE; i++ )
        {
            EXPECT_EQ( CPLHashSetLookup( set, (const void*)&data[i] ), (const void*)&data[i] );
        }

        int sum = 0;
        CPLHashSetForeach( set, sumValues, &sum );
        EXPECT_EQ( sum, ( HASH_SET_SIZE - 1 ) * HASH_SET_SIZE / 2 );

        for ( int i = 0; i < HASH_SET_SIZE; i++ )
        {
            EXPECT_EQ( CPLHashSetRemove( set, (void*)&data[i] ), TRUE );
        }
        EXPECT_EQ( CPLHashSetSize( set ), 0 );

        CPLHashSetDestroy( set );
    }

    TEST( CPL, CPLStringAPI )
    {
        char** papszStringList;

        papszStringList = CSLTokenizeString2( "one two three", " ", 0 );
        EXPECT_EQ( CSLCount( papszStringList ), 3 );
        EXPECT_EQ( strcmp( papszStringList[0], "one" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[1], "two" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[2], "three" ), 0 );
        CSLDestroy( papszStringList );

        papszStringList = CSLTokenizeString2( "one two, three;four,five; six", " ;,", 0 );
        EXPECT_EQ( CSLCount( papszStringList ), 6 );
        EXPECT_EQ( strcmp( papszStringList[0], "one" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[1], "two" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[2], "three" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[3], "four" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[4], "five" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[5], "six" ), 0 );
        CSLDestroy( papszStringList );

        papszStringList = CSLTokenizeString2( "one two,,,five,six", " ,",
            CSLT_ALLOWEMPTYTOKENS );
        EXPECT_EQ( CSLCount( papszStringList ), 6 );
        EXPECT_EQ( strcmp( papszStringList[0], "one" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[1], "two" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[2], "" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[3], "" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[4], "five" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[5], "six" ), 0 );
        CSLDestroy( papszStringList );

        papszStringList = CSLTokenizeString2( "one two,\"three,four ,\",five,six", " ,",
            CSLT_HONOURSTRINGS );
        EXPECT_EQ( CSLCount( papszStringList ), 5 );
        EXPECT_EQ( strcmp( papszStringList[0], "one" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[1], "two" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[2], "three,four ," ), 0 );
        EXPECT_EQ( strcmp( papszStringList[3], "five" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[4], "six" ), 0 );
        CSLDestroy( papszStringList );

        papszStringList = CSLTokenizeString2( "one two,\"three,four ,\",five,six", " ,",
            CSLT_PRESERVEQUOTES );
        EXPECT_EQ( CSLCount( papszStringList ), 7 );
        EXPECT_EQ( strcmp( papszStringList[0], "one" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[1], "two" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[2], "\"three" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[3], "four" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[4], "\"" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[5], "five" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[6], "six" ), 0 );
        CSLDestroy( papszStringList );

        papszStringList = CSLTokenizeString2( "one two,\"three,four ,\",five,six", " ,",
            CSLT_HONOURSTRINGS | CSLT_PRESERVEQUOTES );
        EXPECT_EQ( CSLCount( papszStringList ), 5 );
        EXPECT_EQ( strcmp( papszStringList[0], "one" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[1], "two" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[2], "\"three,four ,\"" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[3], "five" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[4], "six" ), 0 );
        CSLDestroy( papszStringList );

        papszStringList = CSLTokenizeString2( "one \\two,\"three,\\four ,\",five,six",
            " ,", CSLT_PRESERVEESCAPES );
        EXPECT_EQ( CSLCount( papszStringList ), 7 );
        EXPECT_EQ( strcmp( papszStringList[0], "one" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[1], "\\two" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[2], "\"three" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[3], "\\four" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[4], "\"" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[5], "five" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[6], "six" ), 0 );
        CSLDestroy( papszStringList );

        papszStringList = CSLTokenizeString2( "one \\two,\"three,\\four ,\",five,six",
            " ,",
            CSLT_PRESERVEQUOTES | CSLT_PRESERVEESCAPES );
        EXPECT_EQ( CSLCount( papszStringList ), 7 );
        EXPECT_EQ( strcmp( papszStringList[0], "one" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[1], "\\two" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[2], "\"three" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[3], "\\four" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[4], "\"" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[5], "five" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[6], "six" ), 0 );
        CSLDestroy( papszStringList );

        papszStringList = CSLTokenizeString2( "one ,two, three, four ,five  ", ",", 0 );
        EXPECT_EQ( CSLCount( papszStringList ), 5 );
        EXPECT_EQ( strcmp( papszStringList[0], "one " ), 0 );
        EXPECT_EQ( strcmp( papszStringList[1], "two" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[2], " three" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[3], " four " ), 0 );
        EXPECT_EQ( strcmp( papszStringList[4], "five  " ), 0 );
        CSLDestroy( papszStringList );

        papszStringList = CSLTokenizeString2( "one ,two, three, four ,five  ", ",",
            CSLT_STRIPLEADSPACES );
        EXPECT_EQ( CSLCount( papszStringList ), 5 );
        EXPECT_EQ( strcmp( papszStringList[0], "one " ), 0 );
        EXPECT_EQ( strcmp( papszStringList[1], "two" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[2], "three" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[3], "four " ), 0 );
        EXPECT_EQ( strcmp( papszStringList[4], "five  " ), 0 );
        CSLDestroy( papszStringList );

        papszStringList = CSLTokenizeString2( "one ,two, three, four ,five  ", ",",
            CSLT_STRIPENDSPACES );
        EXPECT_EQ( CSLCount( papszStringList ), 5 );
        EXPECT_EQ( strcmp( papszStringList[0], "one" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[1], "two" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[2], " three" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[3], " four" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[4], "five" ), 0 );
        CSLDestroy( papszStringList );

        papszStringList = CSLTokenizeString2( "one ,two, three, four ,five  ", ",",
            CSLT_STRIPLEADSPACES | CSLT_STRIPENDSPACES );
        EXPECT_EQ( CSLCount( papszStringList ), 5 );
        EXPECT_EQ( strcmp( papszStringList[0], "one" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[1], "two" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[2], "three" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[3], "four" ), 0 );
        EXPECT_EQ( strcmp( papszStringList[4], "five" ), 0 );
        CSLDestroy( papszStringList );
    }

    struct TestRecodeStruct
    {
        char szEncoding[24];
        char szString[1024 - 24];
    };

    TEST( CPL, CPLRecodeAPI )
    {
        /*
         * NOTE: This test will generally fail if iconv() is not
         *       linked in.
         *
         * CPLRecode() will be tested using the test file containing
         * a list of strings of the same text in different encoding. The
         * string is non-ASCII to avoid trivial transformations. Test file
         * has a simple binary format: a table of records, each record
         * is 1024 bytes long. The first 24 bytes of each record contain
         * encoding name (ASCII, zero padded), the last 1000 bytes contain
         * encoded string, zero padded.
         *
         * NOTE 1: We can't use a test file in human readable text format
         *         here because of multiple different encodings including
         *         multibyte ones.
         *
         * The test file could be generated with the following simple shell
         * script:
         *
         * #!/bin/sh
         *
         * # List of encodings to convert the test string into
         * ENCODINGS="UTF-8 CP1251 KOI8-R UCS-2 UCS-2BE UCS-2LE UCS-4 UCS-4BE UCS-4LE UTF-16 UTF-32"
         * # The test string itself in UTF-8 encoding.
         * # This means "Improving GDAL internationalization." in Russian.
         * TESTSTRING="\u0423\u043b\u0443\u0447\u0448\u0430\u0435\u043c \u0438\u043d\u0442\u0435\u0440\u043d\u0430\u0446\u0438\u043e\u043d\u0430\u043b\u0438\u0437\u0430\u0446\u0438\u044e GDAL."
         *
         * RECORDSIZE=1024
         * ENCSIZE=24
         *
         * i=0
         * for enc in ${ENCODINGS}; do
         *  env printf "${enc}" | dd ibs=${RECORDSIZE} conv=sync obs=1 seek=$((${RECORDSIZE}*${i})) of="recode-rus.dat" status=noxfer
         *  env printf "${TESTSTRING}" | iconv -t ${enc} | dd ibs=${RECORDSIZE} conv=sync obs=1 seek=$((${RECORDSIZE}*${i}+${ENCSIZE})) of="recode-rus.dat" status=noxfer
         *  i=$((i+1))
         * done
         *
         * NOTE 2: The test string is encoded with the special format
         *         "\uXXXX" sequences, so we able to paste it here.
         *
         * NOTE 3: We need a printf utility from the coreutils because of
         *         that. "env printf" should work avoiding the shell
         *         built-in.
         *
         * NOTE 4: "iconv" utility without the "-f" option will work with
         *         encoding read from the current locale.
         *
         *  TODO: 1. Add more encodings maybe more test files.
         *        2. Add test for CPLRecodeFromWChar()/CPLRecodeToWChar().
         *        3. Test translation between each possible pair of
         *        encodings in file, not only into the UTF-8.
         */
        std::string recode_rus_dat = GetCppDataDirecory( ) + "\\recode-rus.dat";

        std::ifstream fin( recode_rus_dat.c_str( ), std::ifstream::binary );
        TestRecodeStruct oReferenceString;

        // Read reference string (which is the first one in the file)
        fin.read( oReferenceString.szEncoding,
            sizeof( oReferenceString.szEncoding ) );
        oReferenceString.szEncoding[sizeof( oReferenceString.szEncoding ) - 1] = '\0';
        fin.read( oReferenceString.szString,
            sizeof( oReferenceString.szString ) );
        oReferenceString.szString[sizeof( oReferenceString.szString ) - 1] = '\0';

        while ( true )
        {
            TestRecodeStruct oTestString;

            fin.read( oTestString.szEncoding, sizeof( oTestString.szEncoding ) );
            oTestString.szEncoding[sizeof( oTestString.szEncoding ) - 1] = '\0';
            if ( fin.eof( ) )
                break;
            fin.read( oTestString.szString, sizeof( oTestString.szString ) );
            oTestString.szString[sizeof( oTestString.szString ) - 1] = '\0';

            // Compare each string with the reference one
            CPLErrorReset( );
            char* pszDecodedString = CPLRecode( oTestString.szString,
                oTestString.szEncoding, oReferenceString.szEncoding );
            if ( strstr( CPLGetLastErrorMsg( ), "Recode from CP1251 to UTF-8 not supported" ) != nullptr ||
                strstr( CPLGetLastErrorMsg( ), "Recode from KOI8-R to UTF-8 not supported" ) != nullptr )
            {
                CPLFree( pszDecodedString );
                break;
            }

            size_t  nLength =
                MIN( strlen( pszDecodedString ),
                    sizeof( oReferenceString.szEncoding ) );
            bool bOK = memcmp( pszDecodedString, oReferenceString.szString, nLength ) == 0;
            EXPECT_TRUE( bOK );
            CPLFree( pszDecodedString );
        }

        fin.close( );
    }

    TEST( CPL, CPLStringListAPI1 )
    {
        CPLStringList  oCSL;

        EXPECT_EQ( oCSL.List( ), nullptr );

        oCSL.AddString( "def" );
        oCSL.AddString( "abc" );

        EXPECT_EQ( oCSL.Count( ), 2 );
        EXPECT_TRUE( IsEqual( oCSL[0], "def" ) );
        EXPECT_TRUE( IsEqual( oCSL[1], "abc" ) );
        EXPECT_EQ( oCSL[17], nullptr );
        EXPECT_EQ( oCSL[-1], nullptr );
        EXPECT_EQ( oCSL.FindString( "abc" ), 1 );

        CSLDestroy( oCSL.StealList( ) );
        EXPECT_EQ( oCSL.Count( ), 0 );
        EXPECT_EQ( oCSL.List( ), nullptr );

        // Test that the list will make an internal copy when needed to
        // modify a read-only list.

        oCSL.AddString( "def" );
        oCSL.AddString( "abc" );

        CPLStringList  oCopy( oCSL.List( ), FALSE );

        EXPECT_EQ( oCSL.List( ), oCopy.List( ) );
        EXPECT_EQ( oCSL.Count( ), oCopy.Count( ) );

        oCopy.AddString( "xyz" );
        EXPECT_NE( oCSL.List( ), oCopy.List( ) );
        EXPECT_EQ( oCopy.Count( ), 3 );
        EXPECT_EQ( oCSL.Count( ), 2 );
        EXPECT_TRUE( IsEqual( oCopy[2], "xyz" ) );
    }

    TEST( CPL, CPLStringListAPI2 )
    {
        // Test some name=value handling stuff.
        CPLStringList oNVL;

        oNVL.AddNameValue( "KEY1", "VALUE1" );
        oNVL.AddNameValue( "2KEY", "VALUE2" );
        EXPECT_EQ( oNVL.Count( ), 2 );
        EXPECT_TRUE( IsEqual( oNVL.FetchNameValue( "2KEY" ), "VALUE2" ) );
        EXPECT_TRUE( oNVL.FetchNameValue( "MISSING" ) == nullptr );

        oNVL.AddNameValue( "KEY1", "VALUE3" );
        EXPECT_TRUE( IsEqual( oNVL.FetchNameValue( "KEY1" ), "VALUE1" ) );
        EXPECT_TRUE( IsEqual( oNVL[2], "KEY1=VALUE3" ) );
        EXPECT_TRUE( IsEqual( oNVL.FetchNameValueDef( "MISSING", "X" ), "X" ) );

        oNVL.SetNameValue( "2KEY", "VALUE4" );
        EXPECT_TRUE( IsEqual( oNVL.FetchNameValue( "2KEY" ), "VALUE4" ) );
        EXPECT_EQ( oNVL.Count( ), 3 );

        // make sure deletion works.
        oNVL.SetNameValue( "2KEY", nullptr );
        EXPECT_TRUE( oNVL.FetchNameValue( "2KEY" ) == nullptr );
        EXPECT_EQ( oNVL.Count( ), 2 );

        // Test boolean support.
        EXPECT_EQ( oNVL.FetchBoolean( "BOOL", TRUE ), TRUE );
        EXPECT_EQ( oNVL.FetchBoolean( "BOOL", FALSE ), FALSE );

        oNVL.SetNameValue( "BOOL", "YES" );
        EXPECT_EQ( oNVL.FetchBoolean( "BOOL", TRUE ), TRUE );
        EXPECT_EQ( oNVL.FetchBoolean( "BOOL", FALSE ), TRUE );

        oNVL.SetNameValue( "BOOL", "1" );
        EXPECT_EQ( oNVL.FetchBoolean( "BOOL", FALSE ), TRUE );

        oNVL.SetNameValue( "BOOL", "0" );
        EXPECT_EQ( oNVL.FetchBoolean( "BOOL", TRUE ), FALSE );

        oNVL.SetNameValue( "BOOL", "FALSE" );
        EXPECT_EQ( oNVL.FetchBoolean( "BOOL", TRUE ), FALSE );

        oNVL.SetNameValue( "BOOL", "ON" );
        EXPECT_EQ( oNVL.FetchBoolean( "BOOL", FALSE ), TRUE );

        // Test assignment operator.
        CPLStringList oCopy;

        {
            CPLStringList oTemp;
            oTemp.AddString( "test" );
            oCopy = oTemp;
        }
        EXPECT_TRUE( IsEqual( oCopy[0], "test" ) );

        auto& oCopyRef( oCopy );
        oCopy = oCopyRef;
        EXPECT_TRUE( IsEqual( oCopy[0], "test" ) );

        // Test copy constructor.
        CPLStringList oCopy2( oCopy );
        oCopy.Clear( );
        EXPECT_TRUE( IsEqual( oCopy2[0], "test" ) );

        // Test sorting
        CPLStringList oTestSort;
        oTestSort.AddNameValue( "Z", "1" );
        oTestSort.AddNameValue( "L", "2" );
        oTestSort.AddNameValue( "T", "3" );
        oTestSort.AddNameValue( "A", "4" );
        oTestSort.Sort( );
        EXPECT_TRUE( IsEqual( oTestSort[0], "A=4" ) );
        EXPECT_TRUE( IsEqual( oTestSort[1], "L=2" ) );
        EXPECT_TRUE( IsEqual( oTestSort[2], "T=3" ) );
        EXPECT_TRUE( IsEqual( oTestSort[3], "Z=1" ) );
        EXPECT_EQ( oTestSort[4], ( const char* )nullptr );

        // Test FetchNameValue() in a sorted list
        EXPECT_TRUE( IsEqual( oTestSort.FetchNameValue( "A" ), "4" ) );
        EXPECT_TRUE( IsEqual( oTestSort.FetchNameValue( "L" ), "2" ) );
        EXPECT_TRUE( IsEqual( oTestSort.FetchNameValue( "T" ), "3" ) );
        EXPECT_TRUE( IsEqual( oTestSort.FetchNameValue( "Z" ), "1" ) );

        // Test AddNameValue() in a sorted list
        oTestSort.AddNameValue( "B", "5" );
        EXPECT_TRUE( IsEqual( oTestSort[0], "A=4" ) );
        EXPECT_TRUE( IsEqual( oTestSort[1], "B=5" ) );
        EXPECT_TRUE( IsEqual( oTestSort[2], "L=2" ) );
        EXPECT_TRUE( IsEqual( oTestSort[3], "T=3" ) );
        EXPECT_TRUE( IsEqual( oTestSort[4], "Z=1" ) );
        EXPECT_EQ( oTestSort[5], ( const char* )nullptr );

        // Test SetNameValue() of an existing item in a sorted list
        oTestSort.SetNameValue( "Z", "6" );
        EXPECT_TRUE( IsEqual( oTestSort[4], "Z=6" ) );

        // Test SetNameValue() of a non-existing item in a sorted list
        oTestSort.SetNameValue( "W", "7" );
        EXPECT_TRUE( IsEqual( oTestSort[0], "A=4" ) );
        EXPECT_TRUE( IsEqual( oTestSort[1], "B=5" ) );
        EXPECT_TRUE( IsEqual( oTestSort[2], "L=2" ) );
        EXPECT_TRUE( IsEqual( oTestSort[3], "T=3" ) );
        EXPECT_TRUE( IsEqual( oTestSort[4], "W=7" ) );
        EXPECT_TRUE( IsEqual( oTestSort[5], "Z=6" ) );
        EXPECT_EQ( oTestSort[6], ( const char* )nullptr );
    }

    TEST( CPL, CPLStringListAPI3 )
    {
        // Test some name=value handling stuff *with* sorting active.
        CPLStringList oNVL;

        oNVL.Sort( );

        oNVL.AddNameValue( "KEY1", "VALUE1" );
        oNVL.AddNameValue( "2KEY", "VALUE2" );
        EXPECT_EQ( oNVL.Count( ), 2 );
        EXPECT_TRUE( EQUAL( oNVL.FetchNameValue( "KEY1" ), "VALUE1" ) );
        EXPECT_TRUE( EQUAL( oNVL.FetchNameValue( "2KEY" ), "VALUE2" ) );
        EXPECT_TRUE( oNVL.FetchNameValue( "MISSING" ) == nullptr );

        oNVL.AddNameValue( "KEY1", "VALUE3" );
        EXPECT_EQ( oNVL.Count( ), 3 );
        EXPECT_TRUE( EQUAL( oNVL.FetchNameValue( "KEY1" ), "VALUE1" ) );
        EXPECT_TRUE( EQUAL( oNVL.FetchNameValueDef( "MISSING", "X" ), "X" ) );

        oNVL.SetNameValue( "2KEY", "VALUE4" );
        EXPECT_TRUE( EQUAL( oNVL.FetchNameValue( "2KEY" ), "VALUE4" ) );
        EXPECT_EQ( oNVL.Count( ), 3 );

        // make sure deletion works.
        oNVL.SetNameValue( "2KEY", nullptr );
        EXPECT_TRUE( oNVL.FetchNameValue( "2KEY" ) == nullptr );
        EXPECT_EQ( oNVL.Count( ), 2 );

        // Test insertion logic pretty carefully.
        oNVL.Clear( );
        EXPECT_TRUE( oNVL.IsSorted( ) == TRUE );

        oNVL.SetNameValue( "B", "BB" );
        oNVL.SetNameValue( "A", "AA" );
        oNVL.SetNameValue( "D", "DD" );
        oNVL.SetNameValue( "C", "CC" );

        // items should be in sorted order.
        EXPECT_TRUE( EQUAL( oNVL[0], "A=AA" ) );
        EXPECT_TRUE( EQUAL( oNVL[1], "B=BB" ) );
        EXPECT_TRUE( EQUAL( oNVL[2], "C=CC" ) );
        EXPECT_TRUE( EQUAL( oNVL[3], "D=DD" ) );

        EXPECT_TRUE( EQUAL( oNVL.FetchNameValue( "A" ), "AA" ) );
        EXPECT_TRUE( EQUAL( oNVL.FetchNameValue( "B" ), "BB" ) );
        EXPECT_TRUE( EQUAL( oNVL.FetchNameValue( "C" ), "CC" ) );
        EXPECT_TRUE( EQUAL( oNVL.FetchNameValue( "D" ), "DD" ) );
    }

    TEST( CPL, CPLSHA256 )
    {
        GByte abyDigest[CPL_SHA256_HASH_SIZE];
        char szDigest[2 * CPL_SHA256_HASH_SIZE + 1];

        CPL_HMAC_SHA256( "key", 3,
            "The quick brown fox jumps over the lazy dog", strlen( "The quick brown fox jumps over the lazy dog" ),
            abyDigest );
        for ( int i = 0; i < CPL_SHA256_HASH_SIZE; i++ )
            snprintf( szDigest + 2 * i, sizeof( szDigest ) - 2 * i, "%02x", abyDigest[i] );
        //fprintf(stderr, "%s\n", szDigest);
        EXPECT_TRUE( EQUAL( szDigest, "f7bc83f430538424b13298e6aa6fb143ef4d59a14946175997479dbc2d1a3cd8" ) );


        CPL_HMAC_SHA256( "mysupersupersupersupersupersupersupersupersupersupersupersupersupersupersupersupersupersupersupersuperlongkey",
            strlen( "mysupersupersupersupersupersupersupersupersupersupersupersupersupersupersupersupersupersupersupersuperlongkey" ),
            "msg", 3,
            abyDigest );
        for ( int i = 0; i < CPL_SHA256_HASH_SIZE; i++ )
            snprintf( szDigest + 2 * i, sizeof( szDigest ) - 2 * i, "%02x", abyDigest[i] );
        //fprintf(stderr, "%s\n", szDigest);
        EXPECT_TRUE( EQUAL( szDigest, "a3051520761ed3cb43876b35ce2dd93ac5b332dc3bad898bb32086f7ac71ffc1" ) );
    }

    TEST( CPL, CPLVSIMallocN )
    {
        CPLPushErrorHandler( CPLQuietErrorHandler );

        // The following tests will fail because of overflows
        CPLErrorReset( );
        EXPECT_TRUE( VSIMalloc2( ~(size_t)0, ~(size_t)0 ) == nullptr );
        EXPECT_TRUE( CPLGetLastErrorType( ) != CE_None );

        CPLErrorReset( );
        EXPECT_TRUE( VSIMalloc3( 1, ~(size_t)0, ~(size_t)0 ) == nullptr );
        EXPECT_TRUE( CPLGetLastErrorType( ) != CE_None );

        CPLErrorReset( );
        EXPECT_TRUE( VSIMalloc3( ~(size_t)0, 1, ~(size_t)0 ) == nullptr );
        EXPECT_TRUE( CPLGetLastErrorType( ) != CE_None );

        CPLErrorReset( );
        EXPECT_TRUE( VSIMalloc3( ~(size_t)0, ~(size_t)0, 1 ) == nullptr );
        EXPECT_TRUE( CPLGetLastErrorType( ) != CE_None );

        if ( !CSLTestBoolean( CPLGetConfigOption( "SKIP_MEM_INTENSIVE_TEST", "NO" ) ) )
        {
            // The following tests will fail because such allocations cannot succeed
#if SIZEOF_VOIDP == 8
            CPLErrorReset( );
            EXPECT_TRUE( VSIMalloc( ~(size_t)0 ) == nullptr );
            EXPECT_TRUE( CPLGetLastErrorType( ) == CE_None ); /* no error reported */

            CPLErrorReset( );
            EXPECT_TRUE( VSIMalloc2( ~(size_t)0, 1 ) == nullptr );
            EXPECT_TRUE( CPLGetLastErrorType( ) != CE_None );

            CPLErrorReset( );
            EXPECT_TRUE( VSIMalloc3( ~(size_t)0, 1, 1 ) == nullptr );
            EXPECT_TRUE( CPLGetLastErrorType( ) != CE_None );

            CPLErrorReset( );
            EXPECT_TRUE( VSICalloc( ~(size_t)0, 1 ) == nullptr );
            EXPECT_TRUE( CPLGetLastErrorType( ) == CE_None ); /* no error reported */

            CPLErrorReset( );
            EXPECT_TRUE( VSIRealloc( nullptr, ~(size_t)0 ) == nullptr );
            EXPECT_TRUE( CPLGetLastErrorType( ) == CE_None ); /* no error reported */

            CPLErrorReset( );
            EXPECT_TRUE( VSI_MALLOC_VERBOSE( ~(size_t)0 ) == nullptr );
            EXPECT_TRUE( CPLGetLastErrorType( ) != CE_None );

            CPLErrorReset( );
            EXPECT_TRUE( VSI_MALLOC2_VERBOSE( ~(size_t)0, 1 ) == nullptr );
            EXPECT_TRUE( CPLGetLastErrorType( ) != CE_None );

            CPLErrorReset( );
            EXPECT_TRUE( VSI_MALLOC3_VERBOSE( ~(size_t)0, 1, 1 ) == nullptr );
            EXPECT_TRUE( CPLGetLastErrorType( ) != CE_None );

            CPLErrorReset( );
            EXPECT_TRUE( VSI_CALLOC_VERBOSE( ~(size_t)0, 1 ) == nullptr );
            EXPECT_TRUE( CPLGetLastErrorType( ) != CE_None );

            CPLErrorReset( );
            EXPECT_TRUE( VSI_REALLOC_VERBOSE( nullptr, ~(size_t)0 ) == nullptr );
            EXPECT_TRUE( CPLGetLastErrorType( ) != CE_None );
#endif
        }

        CPLPopErrorHandler( );

        // The following allocs will return NULL because of 0 byte alloc
        CPLErrorReset( );
        EXPECT_TRUE( VSIMalloc2( 0, 1 ) == nullptr );
        EXPECT_TRUE( CPLGetLastErrorType( ) == CE_None );
        EXPECT_TRUE( VSIMalloc2( 1, 0 ) == nullptr );

        CPLErrorReset( );
        EXPECT_TRUE( VSIMalloc3( 0, 1, 1 ) == nullptr );
        EXPECT_TRUE( CPLGetLastErrorType( ) == CE_None );
        EXPECT_TRUE( VSIMalloc3( 1, 0, 1 ) == nullptr );
        EXPECT_TRUE( VSIMalloc3( 1, 1, 0 ) == nullptr );
    }

    TEST( CPL, CPLFormFilename1 )
    {
        EXPECT_TRUE( strcmp( CPLFormFilename( "a", "b", nullptr ), "a/b" ) == 0 ||
            strcmp( CPLFormFilename( "a", "b", nullptr ), "a\\b" ) == 0 );
        EXPECT_TRUE( strcmp( CPLFormFilename( "a/", "b", nullptr ), "a/b" ) == 0 ||
            strcmp( CPLFormFilename( "a/", "b", nullptr ), "a\\b" ) == 0 );
        EXPECT_TRUE( strcmp( CPLFormFilename( "a\\", "b", nullptr ), "a/b" ) == 0 ||
            strcmp( CPLFormFilename( "a\\", "b", nullptr ), "a\\b" ) == 0 );
        EXPECT_TRUE( IsEqual(CPLFormFilename( nullptr, "a", "b" ), "a.b" ));
        EXPECT_TRUE( IsEqual(CPLFormFilename( nullptr, "a", ".b" ), "a.b" ));
        EXPECT_TRUE( IsEqual(CPLFormFilename( "/a", "..", nullptr ), "/" ));
        EXPECT_TRUE( IsEqual(CPLFormFilename( "/a/", "..", nullptr ), "/" ));
        EXPECT_TRUE( IsEqual(CPLFormFilename( "/a/b", "..", nullptr ), "/a" ));
        EXPECT_TRUE( IsEqual(CPLFormFilename( "/a/b/", "..", nullptr ), "/a" ));
        EXPECT_TRUE( IsEqual( CPLFormFilename( "c:", "..", nullptr ), "c:/.." ) ||
            IsEqual( CPLFormFilename( "c:", "..", nullptr ), "c:\\.." ) );
        EXPECT_TRUE( IsEqual( CPLFormFilename( "c:\\", "..", nullptr ), "c:/.." ) ||
            IsEqual( CPLFormFilename( "c:\\", "..", nullptr ), "c:\\.." ) );
        EXPECT_TRUE( IsEqual(CPLFormFilename( "c:\\a", "..", nullptr ), "c:" ));
        EXPECT_TRUE( IsEqual(CPLFormFilename( "c:\\a\\", "..", nullptr ), "c:" ));
        EXPECT_TRUE( IsEqual(CPLFormFilename( "c:\\a\\b", "..", nullptr ), "c:\\a" ));
        EXPECT_TRUE( IsEqual(CPLFormFilename( "\\\\$\\c:\\a", "..", nullptr ), "\\\\$\\c:" ));
        EXPECT_TRUE( IsEqual( CPLFormFilename( "\\\\$\\c:", "..", nullptr ), "\\\\$\\c:/.." ) ||
            IsEqual( CPLFormFilename( "\\\\$\\c:", "..", nullptr ), "\\\\$\\c:\\.." ) );
    }

    TEST( CPL, VSIGetDiskFreeSpace1 )
    {
        EXPECT_TRUE( VSIGetDiskFreeSpace( "/vsimem/" ) > 0 );
        EXPECT_TRUE( VSIGetDiskFreeSpace( "." ) == -1 || VSIGetDiskFreeSpace( "." ) >= 0 );
    }

    TEST( CPL, CPLsscanf1 )
    {
        double a, b, c;

        a = b = 0;
        EXPECT_EQ( CPLsscanf( "1 2", "%lf %lf", &a, &b ), 2 );
        EXPECT_EQ( a, 1.0 );
        EXPECT_EQ( b, 2.0 );

        a = b = 0;
        EXPECT_EQ( CPLsscanf( "1\t2", "%lf %lf", &a, &b ), 2 );
        EXPECT_EQ( a, 1.0 );
        EXPECT_EQ( b, 2.0 );

        a = b = 0;
        EXPECT_EQ( CPLsscanf( "1 2", "%lf\t%lf", &a, &b ), 2 );
        EXPECT_EQ( a, 1.0 );
        EXPECT_EQ( b, 2.0 );

        a = b = 0;
        EXPECT_EQ( CPLsscanf( "1  2", "%lf %lf", &a, &b ), 2 );
        EXPECT_EQ( a, 1.0 );
        EXPECT_EQ( b, 2.0 );

        a = b = 0;
        EXPECT_EQ( CPLsscanf( "1 2", "%lf  %lf", &a, &b ), 2 );
        EXPECT_EQ( a, 1.0 );
        EXPECT_EQ( b, 2.0 );

        a = b = c = 0;
        EXPECT_EQ( CPLsscanf( "1 2", "%lf %lf %lf", &a, &b, &c ), 2 );
        EXPECT_EQ( a, 1.0 );
        EXPECT_EQ( b, 2.0 );
    }

    TEST( CPL, CPLSetErrorHandler1 )
    {
        CPLString oldVal = CPLGetConfigOption( "CPL_DEBUG", "" );
        CPLSetConfigOption( "CPL_DEBUG", "TEST" );

        CPLErrorHandler oldHandler = CPLSetErrorHandler( myErrorHandler );
        gbGotError = false;
        CPLDebug( "TEST", "Test" );
        EXPECT_EQ( gbGotError, true );
        gbGotError = false;
        CPLSetErrorHandler( oldHandler );

        CPLPushErrorHandler( myErrorHandler );
        gbGotError = false;
        CPLDebug( "TEST", "Test" );
        EXPECT_EQ( gbGotError, true );
        gbGotError = false;
        CPLPopErrorHandler( );

        oldHandler = CPLSetErrorHandler( myErrorHandler );
        CPLSetCurrentErrorHandlerCatchDebug( FALSE );
        gbGotError = false;
        CPLDebug( "TEST", "Test" );
        EXPECT_EQ( gbGotError, false );
        gbGotError = false;
        CPLSetErrorHandler( oldHandler );

        CPLPushErrorHandler( myErrorHandler );
        CPLSetCurrentErrorHandlerCatchDebug( FALSE );
        gbGotError = false;
        CPLDebug( "TEST", "Test" );
        EXPECT_EQ( gbGotError, false );
        gbGotError = false;
        CPLPopErrorHandler( );

        CPLSetConfigOption( "CPL_DEBUG", oldVal.size( ) ? oldVal.c_str( ) : nullptr );

        oldHandler = CPLSetErrorHandler( nullptr );
        CPLDebug( "TEST", "Test" );
        CPLError( CE_Failure, CPLE_AppDefined, "test" );
        CPLErrorHandler newOldHandler = CPLSetErrorHandler( nullptr );
        EXPECT_EQ( newOldHandler, static_cast<CPLErrorHandler>( nullptr ) );
        CPLDebug( "TEST", "Test" );
        CPLError( CE_Failure, CPLE_AppDefined, "test" );
        CPLSetErrorHandler( oldHandler );
    }

    TEST( CPL, CPLString_replaceAll1 )
    {
        CPLString osTest;
        osTest = "foobarbarfoo";
        osTest.replaceAll( "bar", "was_bar" );
        EXPECT_TRUE( IsEqual( osTest, "foowas_barwas_barfoo" ) );

        osTest = "foobarbarfoo";
        osTest.replaceAll( "X", "was_bar" );
        EXPECT_TRUE( IsEqual( osTest, "foobarbarfoo" ) );

        osTest = "foobarbarfoo";
        osTest.replaceAll( "", "was_bar" );
        EXPECT_TRUE( IsEqual( osTest, "foobarbarfoo" ) );

        osTest = "foobarbarfoo";
        osTest.replaceAll( "bar", "" );
        EXPECT_TRUE( IsEqual( osTest, "foofoo" ) );

        osTest = "foobarbarfoo";
        osTest.replaceAll( 'b', 'B' );
        EXPECT_TRUE( IsEqual( osTest, "fooBarBarfoo" ) );

        osTest = "foobarbarfoo";
        osTest.replaceAll( 'b', "B" );
        EXPECT_TRUE( IsEqual( osTest, "fooBarBarfoo" ) );

        osTest = "foobarbarfoo";
        osTest.replaceAll( "b", 'B' );
        EXPECT_TRUE( IsEqual( osTest, "fooBarBarfoo" ) );
    }

    TEST( CPL, CPLVSIMallocAligned1 )
    {
        GByte* ptr = static_cast<GByte*>( VSIMallocAligned( sizeof( void* ), 1 ) );
        EXPECT_TRUE( ptr != nullptr );
        EXPECT_TRUE( ( (size_t)ptr % sizeof( void* ) ) == 0 );
        *ptr = 1;
        VSIFreeAligned( ptr );

        ptr = static_cast<GByte*>( VSIMallocAligned( 16, 1 ) );
        EXPECT_TRUE( ptr != nullptr );
        EXPECT_TRUE( ( (size_t)ptr % 16 ) == 0 );
        *ptr = 1;
        VSIFreeAligned( ptr );

        VSIFreeAligned( nullptr );

        if ( !CSLTestBoolean( CPLGetConfigOption( "SKIP_MEM_INTENSIVE_TEST", "NO" ) ) )
        {
            // The following tests will fail because such allocations cannot succeed
#if SIZEOF_VOIDP == 8
            ptr = static_cast<GByte*>( VSIMallocAligned( sizeof( void* ), ~( (size_t)0 ) ) );
            EXPECT_TRUE( ptr == nullptr );

            ptr = static_cast<GByte*>( VSIMallocAligned( sizeof( void* ), ( ~( (size_t)0 ) ) - sizeof( void* ) ) );
            EXPECT_TRUE( ptr == nullptr );
#endif
        }
    }

    TEST( CPL, CPLSetConfigOption1 )
    {
        CPLSetConfigOption( "FOOFOO", "BAR" );
        char** options = CPLGetConfigOptions( );
        EXPECT_TRUE( IsEqual( CSLFetchNameValue( options, "FOOFOO" ), "BAR" ) );
        CPLSetConfigOptions( nullptr );
        EXPECT_TRUE( IsEqual( CPLGetConfigOption( "FOOFOO", "i_dont_exist" ), "i_dont_exist" ) );
        CPLSetConfigOptions( options );
        EXPECT_TRUE( IsEqual( CPLGetConfigOption( "FOOFOO", "i_dont_exist" ), "BAR" ) );
        CSLDestroy( options );
    }

    TEST( CPL, CPLSetThreadLocalConfigOption1 )
    {
        CPLSetThreadLocalConfigOption( "FOOFOO", "BAR" );
        char** options = CPLGetThreadLocalConfigOptions( );
        EXPECT_TRUE( IsEqual( CSLFetchNameValue( options, "FOOFOO" ), "BAR" ) );
        CPLSetThreadLocalConfigOptions( nullptr );
        EXPECT_TRUE( IsEqual( CPLGetThreadLocalConfigOption( "FOOFOO", "i_dont_exist" ), "i_dont_exist" ) );
        CPLSetThreadLocalConfigOptions( options );
        EXPECT_TRUE( IsEqual( CPLGetThreadLocalConfigOption( "FOOFOO", "i_dont_exist" ), "BAR" ) );
        CSLDestroy( options );
    }

    TEST( CPL, CPLExpandTilde1 )
    {
        EXPECT_TRUE( IsEqual( CPLExpandTilde( "/foo/bar" ), "/foo/bar" ) );

        CPLSetConfigOption( "HOME", "/foo" );
        EXPECT_TRUE( IsEqual( CPLExpandTilde( "~/bar" ), "/foo/bar" ) || IsEqual( CPLExpandTilde( "~/bar" ), "/foo\\bar" ) );
        CPLSetConfigOption( "HOME", nullptr );
    }

    TEST( CPL, CPLString_ctor1 )
    {
        // CPLString(std::string) constructor
        EXPECT_TRUE( IsEqual( CPLString( std::string( "abc" ) ).c_str( ), "abc" ) );

        // CPLString(const char*) constructor
        EXPECT_TRUE( IsEqual( CPLString( "abc" ).c_str( ), "abc" ) );

        // CPLString(const char*, n) constructor
        EXPECT_TRUE( IsEqual( CPLString( "abc", 1 ).c_str( ), "a" ) );
    }

    TEST( CPL, CPLErrorSetState1 )
    {
        // NOTE: Assumes cpl_error.cpp defines DEFAULT_LAST_ERR_MSG_SIZE=500
        char pszMsg[] =
            "0abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*()_+=|"
            "1abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*()_+=|"
            "2abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*()_+=|"
            "3abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*()_+=|"
            "4abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*()_+=|"
            "5abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*()_+=|"
            "6abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*()_+=|"
            "7abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*()_+=|"
            "8abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*()_+=|"
            "9abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*()_+=|" // 500
            "0abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*()_+=|" // 550
            ;

        CPLErrorReset( );
        CPLErrorSetState( CE_Warning, 1, pszMsg );
        EXPECT_EQ( strlen( pszMsg ) - 50 - 1,       // length - 50 - 1 (null-terminator)
            strlen( CPLGetLastErrorMsg( ) ) ); // DEFAULT_LAST_ERR_MSG_SIZE - 1
    }

    TEST( CPL, UnescapeString )
    {
        char* pszText = CPLUnescapeString( "&lt;&gt;&amp;&apos;&quot;&#x3f;&#x3F;&#63;", nullptr, CPLES_XML );
        EXPECT_EQ( CPLString( pszText ), "<>&'\"???" );
        CPLFree( pszText );

        // Integer overflow
        pszText = CPLUnescapeString( "&10000000000000000;", nullptr, CPLES_XML );
        // We do not really care about the return value
        CPLFree( pszText );

        // Integer overflow
        pszText = CPLUnescapeString( "&#10000000000000000;", nullptr, CPLES_XML );
        // We do not really care about the return value
        CPLFree( pszText );

        // Error case
        pszText = CPLUnescapeString( "&foo", nullptr, CPLES_XML );
        EXPECT_EQ( CPLString( pszText ), "" );
        CPLFree( pszText );

        // Error case
        pszText = CPLUnescapeString( "&#x", nullptr, CPLES_XML );
        EXPECT_EQ( CPLString( pszText ), "" );
        CPLFree( pszText );

        // Error case
        pszText = CPLUnescapeString( "&#", nullptr, CPLES_XML );
        EXPECT_EQ( CPLString( pszText ), "" );
        CPLFree( pszText );
    }

    TEST( CPL, SafeIntMath )
    {
        EXPECT_EQ( ( CPLSM( -2 ) + CPLSM( 3 ) ).v( ), 1 );
        EXPECT_EQ( ( CPLSM( -2 ) + CPLSM( 1 ) ).v( ), -1 );
        EXPECT_EQ( ( CPLSM( -2 ) + CPLSM( -1 ) ).v( ), -3 );
        EXPECT_EQ( ( CPLSM( 2 ) + CPLSM( -3 ) ).v( ), -1 );
        EXPECT_EQ( ( CPLSM( 2 ) + CPLSM( -1 ) ).v( ), 1 );
        EXPECT_EQ( ( CPLSM( 2 ) + CPLSM( 1 ) ).v( ), 3 );
        EXPECT_EQ( ( CPLSM( INT_MAX - 1 ) + CPLSM( 1 ) ).v( ), INT_MAX );
        EXPECT_EQ( ( CPLSM( 1 ) + CPLSM( INT_MAX - 1 ) ).v( ), INT_MAX );
        EXPECT_EQ( ( CPLSM( INT_MAX ) + CPLSM( -1 ) ).v( ), INT_MAX - 1 );
        EXPECT_EQ( ( CPLSM( -1 ) + CPLSM( INT_MAX ) ).v( ), INT_MAX - 1 );
        EXPECT_EQ( ( CPLSM( INT_MIN + 1 ) + CPLSM( -1 ) ).v( ), INT_MIN );
        EXPECT_EQ( ( CPLSM( -1 ) + CPLSM( INT_MIN + 1 ) ).v( ), INT_MIN );

        EXPECT_ANY_THROW( ( CPLSM( INT_MAX ) + CPLSM( 1 ) ).v( ) );
        EXPECT_ANY_THROW( ( CPLSM( 1 ) + CPLSM( INT_MAX ) ).v( ) );
        EXPECT_ANY_THROW( ( CPLSM( INT_MIN ) + CPLSM( -1 ) ).v( ) );
        EXPECT_ANY_THROW( ( CPLSM( -1 ) + CPLSM( INT_MIN ) ).v( ) );

        EXPECT_EQ( ( CPLSM( -2 ) - CPLSM( 1 ) ).v( ), -3 );
        EXPECT_EQ( ( CPLSM( -2 ) - CPLSM( -1 ) ).v( ), -1 );
        EXPECT_EQ( ( CPLSM( -2 ) - CPLSM( -3 ) ).v( ), 1 );
        EXPECT_EQ( ( CPLSM( 2 ) - CPLSM( -1 ) ).v( ), 3 );
        EXPECT_EQ( ( CPLSM( 2 ) - CPLSM( 1 ) ).v( ), 1 );
        EXPECT_EQ( ( CPLSM( 2 ) - CPLSM( 3 ) ).v( ), -1 );
        EXPECT_EQ( ( CPLSM( INT_MAX ) - CPLSM( 1 ) ).v( ), INT_MAX - 1 );
        EXPECT_EQ( ( CPLSM( INT_MIN + 1 ) - CPLSM( 1 ) ).v( ), INT_MIN );
        EXPECT_EQ( ( CPLSM( 0 ) - CPLSM( INT_MIN + 1 ) ).v( ), INT_MAX );
        EXPECT_EQ( ( CPLSM( 0 ) - CPLSM( INT_MAX ) ).v( ), -INT_MAX );

        EXPECT_ANY_THROW( ( CPLSM( INT_MIN ) - CPLSM( 1 ) ).v( ) );
        EXPECT_ANY_THROW( ( CPLSM( 0 ) - CPLSM( INT_MIN ) ).v( ) );
        EXPECT_ANY_THROW( ( CPLSM( INT_MIN ) - CPLSM( 1 ) ).v( ) );

        EXPECT_EQ( ( CPLSM( INT_MIN + 1 ) * CPLSM( -1 ) ).v( ), INT_MAX );
        EXPECT_EQ( ( CPLSM( -1 ) * CPLSM( INT_MIN + 1 ) ).v( ), INT_MAX );
        EXPECT_EQ( ( CPLSM( INT_MIN ) * CPLSM( 1 ) ).v( ), INT_MIN );
        EXPECT_EQ( ( CPLSM( 1 ) * CPLSM( INT_MIN ) ).v( ), INT_MIN );
        EXPECT_EQ( ( CPLSM( 1 ) * CPLSM( INT_MAX ) ).v( ), INT_MAX );
        EXPECT_EQ( ( CPLSM( INT_MIN / 2 ) * CPLSM( 2 ) ).v( ), INT_MIN );
        EXPECT_EQ( ( CPLSM( INT_MAX / 2 ) * CPLSM( 2 ) ).v( ), INT_MAX - 1 );
        EXPECT_EQ( ( CPLSM( INT_MAX / 2 + 1 ) * CPLSM( -2 ) ).v( ), INT_MIN );
        EXPECT_EQ( ( CPLSM( 0 ) * CPLSM( INT_MIN ) ).v( ), 0 );
        EXPECT_EQ( ( CPLSM( INT_MIN ) * CPLSM( 0 ) ).v( ), 0 );
        EXPECT_EQ( ( CPLSM( 0 ) * CPLSM( INT_MAX ) ).v( ), 0 );
        EXPECT_EQ( ( CPLSM( INT_MAX ) * CPLSM( 0 ) ).v( ), 0 );

        EXPECT_ANY_THROW( ( CPLSM( INT_MAX / 2 + 1 ) * CPLSM( 2 ) ).v( ) );
        EXPECT_ANY_THROW( ( CPLSM( 2 ) * CPLSM( INT_MAX / 2 + 1 ) ).v( ) );
        EXPECT_ANY_THROW( ( CPLSM( INT_MIN ) * CPLSM( -1 ) ).v( ) );
        EXPECT_ANY_THROW( ( CPLSM( INT_MIN ) * CPLSM( 2 ) ).v( ) );
        EXPECT_ANY_THROW( ( CPLSM( 2 ) * CPLSM( INT_MIN ) ).v( ) );

        EXPECT_EQ( ( CPLSM( 4 ) / CPLSM( 2 ) ).v( ), 2 );
        EXPECT_EQ( ( CPLSM( 4 ) / CPLSM( -2 ) ).v( ), -2 );
        EXPECT_EQ( ( CPLSM( -4 ) / CPLSM( 2 ) ).v( ), -2 );
        EXPECT_EQ( ( CPLSM( -4 ) / CPLSM( -2 ) ).v( ), 2 );
        EXPECT_EQ( ( CPLSM( 0 ) / CPLSM( 2 ) ).v( ), 0 );
        EXPECT_EQ( ( CPLSM( 0 ) / CPLSM( -2 ) ).v( ), 0 );
        EXPECT_EQ( ( CPLSM( INT_MAX ) / CPLSM( 1 ) ).v( ), INT_MAX );
        EXPECT_EQ( ( CPLSM( INT_MAX ) / CPLSM( -1 ) ).v( ), -INT_MAX );
        EXPECT_EQ( ( CPLSM( INT_MIN ) / CPLSM( 1 ) ).v( ), INT_MIN );

        EXPECT_ANY_THROW( ( CPLSM( -1 ) * CPLSM( INT_MIN ) ).v( ) );
        EXPECT_ANY_THROW( ( CPLSM( INT_MIN ) / CPLSM( -1 ) ).v( ) );
        EXPECT_ANY_THROW( ( CPLSM( 1 ) / CPLSM( 0 ) ).v( ) );

        EXPECT_EQ( CPLSM_TO_UNSIGNED( 1 ).v( ), 1U );

        EXPECT_ANY_THROW( CPLSM_TO_UNSIGNED( -1 ) );
    }

    TEST( CPL, SafeUIntMath )
    {
        EXPECT_EQ( ( CPLSM( 2U ) + CPLSM( 3U ) ).v( ), 5U );
        EXPECT_EQ( ( CPLSM( UINT_MAX - 1 ) + CPLSM( 1U ) ).v( ), UINT_MAX );
        try
        {
            ( CPLSM( UINT_MAX ) + CPLSM( 1U ) ).v( ); 
            EXPECT_TRUE( false );
        }
        catch ( ... )
        {
        }

        EXPECT_EQ( ( CPLSM( 4U ) - CPLSM( 3U ) ).v( ), 1U );
        EXPECT_EQ( ( CPLSM( 4U ) - CPLSM( 4U ) ).v( ), 0U );
        EXPECT_EQ( ( CPLSM( UINT_MAX ) - CPLSM( 1U ) ).v( ), UINT_MAX - 1 );
        try
        {
            ( CPLSM( 4U ) - CPLSM( 5U ) ).v( ); 
            EXPECT_TRUE( false );
        }
        catch ( ... )
        {
        }

        EXPECT_EQ( ( CPLSM( 0U ) * CPLSM( UINT_MAX ) ).v( ), 0U );
        EXPECT_EQ( ( CPLSM( UINT_MAX ) * CPLSM( 0U ) ).v( ), 0U );
        EXPECT_EQ( ( CPLSM( UINT_MAX ) * CPLSM( 1U ) ).v( ), UINT_MAX );
        EXPECT_EQ( ( CPLSM( 1U ) * CPLSM( UINT_MAX ) ).v( ), UINT_MAX );
        try
        {
            ( CPLSM( UINT_MAX ) * CPLSM( 2U ) ).v( ); 
            EXPECT_TRUE( false );
        }
        catch ( ... )
        {
        }
        try
        {
            ( CPLSM( 2U ) * CPLSM( UINT_MAX ) ).v( ); 
            EXPECT_TRUE( false );
        }
        catch ( ... )
        {
        }

        EXPECT_EQ( ( CPLSM( 4U ) / CPLSM( 2U ) ).v( ), 2U );
        EXPECT_EQ( ( CPLSM( UINT_MAX ) / CPLSM( 1U ) ).v( ), UINT_MAX );
        try
        {
            ( CPLSM( 1U ) / CPLSM( 0U ) ).v( ); 
            EXPECT_TRUE( false );
        }
        catch ( ... )
        {
        }

        EXPECT_EQ( ( CPLSM( static_cast<GUInt64>( 2 ) * 1000 * 1000 * 1000 ) +
            CPLSM( static_cast<GUInt64>( 3 ) * 1000 * 1000 * 1000 ) ).v( ),
            static_cast<GUInt64>( 5 ) * 1000 * 1000 * 1000 );
        EXPECT_EQ( ( CPLSM( std::numeric_limits<GUInt64>::max( ) - 1 ) +
            CPLSM( static_cast<GUInt64>( 1 ) ) ).v( ),
            std::numeric_limits<GUInt64>::max( ) );
        try
        {
            ( CPLSM( std::numeric_limits<GUInt64>::max( ) ) +
                CPLSM( static_cast<GUInt64>( 1 ) ) );
        }
        catch ( ... )
        {
        }

        EXPECT_EQ( ( CPLSM( static_cast<GUInt64>( 2 ) * 1000 * 1000 * 1000 ) *
            CPLSM( static_cast<GUInt64>( 3 ) * 1000 * 1000 * 1000 ) ).v( ),
            static_cast<GUInt64>( 6 ) * 1000 * 1000 * 1000 * 1000 * 1000 * 1000 );
        EXPECT_EQ( ( CPLSM( std::numeric_limits<GUInt64>::max( ) ) *
            CPLSM( static_cast<GUInt64>( 1 ) ) ).v( ),
            std::numeric_limits<GUInt64>::max( ) );
        try
        {
            ( CPLSM( std::numeric_limits<GUInt64>::max( ) ) *
                CPLSM( static_cast<GUInt64>( 2 ) ) );
        }
        catch ( ... )
        {
        }
    }

    TEST( CPL, CPLParseRFC822DateTimeTest )
    {
        int year, month, day, hour, min, sec, tz, weekday;
        EXPECT_TRUE( !CPLParseRFC822DateTime( "", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );

        EXPECT_EQ( CPLParseRFC822DateTime( "Thu, 15 Jan 2017 12:34:56 +0015", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr ), TRUE );

        EXPECT_EQ( CPLParseRFC822DateTime( "Thu, 15 Jan 2017 12:34:56 +0015", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ), TRUE );
        EXPECT_EQ( year, 2017 );
        EXPECT_EQ( month, 1 );
        EXPECT_EQ( day, 15 );
        EXPECT_EQ( hour, 12 );
        EXPECT_EQ( min, 34 );
        EXPECT_EQ( sec, 56 );
        EXPECT_EQ( tz, 101 );
        EXPECT_EQ( weekday, 4 );

        EXPECT_EQ( CPLParseRFC822DateTime( "Thu, 15 Jan 2017 12:34:56 GMT", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ), TRUE );
        EXPECT_EQ( year, 2017 );
        EXPECT_EQ( month, 1 );
        EXPECT_EQ( day, 15 );
        EXPECT_EQ( hour, 12 );
        EXPECT_EQ( min, 34 );
        EXPECT_EQ( sec, 56 );
        EXPECT_EQ( tz, 100 );
        EXPECT_EQ( weekday, 4 );

        // Without day of week, second and timezone
        EXPECT_EQ( CPLParseRFC822DateTime( "15 Jan 2017 12:34", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ), TRUE );
        EXPECT_EQ( year, 2017 );
        EXPECT_EQ( month, 1 );
        EXPECT_EQ( day, 15 );
        EXPECT_EQ( hour, 12 );
        EXPECT_EQ( min, 34 );
        EXPECT_EQ( sec, -1 );
        EXPECT_EQ( tz, 0 );
        EXPECT_EQ( weekday, 0 );

        EXPECT_EQ( CPLParseRFC822DateTime( "XXX, 15 Jan 2017 12:34:56 GMT", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ), TRUE );
        EXPECT_EQ( weekday, 0 );

        EXPECT_TRUE( !CPLParseRFC822DateTime( "Sun, 01 Jan 2017 12", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );

        EXPECT_TRUE( !CPLParseRFC822DateTime( "00 Jan 2017 12:34:56 GMT", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );

        EXPECT_TRUE( !CPLParseRFC822DateTime( "32 Jan 2017 12:34:56 GMT", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );

        EXPECT_TRUE( !CPLParseRFC822DateTime( "01 XXX 2017 12:34:56 GMT", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );

        EXPECT_TRUE( !CPLParseRFC822DateTime( "01 Jan 2017 -1:34:56 GMT", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );

        EXPECT_TRUE( !CPLParseRFC822DateTime( "01 Jan 2017 24:34:56 GMT", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );

        EXPECT_TRUE( !CPLParseRFC822DateTime( "01 Jan 2017 12:-1:56 GMT", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );

        EXPECT_TRUE( !CPLParseRFC822DateTime( "01 Jan 2017 12:60:56 GMT", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );

        EXPECT_TRUE( !CPLParseRFC822DateTime( "01 Jan 2017 12:34:-1 GMT", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );

        EXPECT_TRUE( !CPLParseRFC822DateTime( "01 Jan 2017 12:34:61 GMT", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );

        EXPECT_TRUE( !CPLParseRFC822DateTime( "15 Jan 2017 12:34:56 XXX", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );

        EXPECT_TRUE( !CPLParseRFC822DateTime( "15 Jan 2017 12:34:56 +-100", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );

        EXPECT_TRUE( !CPLParseRFC822DateTime( "15 Jan 2017 12:34:56 +9900", &year, &month, &day, &hour, &min, &sec, &tz, &weekday ) );
    }

    TEST( CPL, CPLCopyTreeTest )
    {
        CPLString osTmpPath( CPLGetDirname( CPLGenerateTempFilename( nullptr ) ) );
        CPLString osSrcDir( CPLFormFilename( osTmpPath, "src_dir", nullptr ) );
        CPLString osNewDir( CPLFormFilename( osTmpPath, "new_dir", nullptr ) );
        EXPECT_TRUE( VSIMkdir( osSrcDir, 0755 ) == 0 );
        CPLString osSrcFile( CPLFormFilename( osSrcDir, "my.bin", nullptr ) );
        VSILFILE* fp = VSIFOpenL( osSrcFile, "wb" );
        EXPECT_TRUE( fp != nullptr );
        VSIFCloseL( fp );

        CPLPushErrorHandler( CPLQuietErrorHandler );
        EXPECT_TRUE( CPLCopyTree( osNewDir, "/i/do_not/exist" ) < 0 );
        CPLPopErrorHandler( );

        EXPECT_TRUE( CPLCopyTree( osNewDir, osSrcDir ) == 0 );
        VSIStatBufL sStat;
        CPLString osNewFile( CPLFormFilename( osNewDir, "my.bin", nullptr ) );
        EXPECT_TRUE( VSIStatL( osNewFile, &sStat ) == 0 );

        CPLPushErrorHandler( CPLQuietErrorHandler );
        EXPECT_TRUE( CPLCopyTree( osNewDir, osSrcDir ) < 0 );
        CPLPopErrorHandler( );

        VSIUnlink( osNewFile );
        VSIRmdir( osNewDir );
        VSIUnlink( osSrcFile );
        VSIRmdir( osSrcDir );
    }

    class CPLJSonStreamingParserDump : public CPLJSonStreamingParser
    {
        std::vector<bool> m_abFirstMember;
        CPLString m_osSerialized;
        CPLString m_osException;

    public:
        CPLJSonStreamingParserDump( )
        {
        }

        virtual void Reset( ) CPL_OVERRIDE
        {
            m_osSerialized.clear( );
            m_osException.clear( );
            CPLJSonStreamingParser::Reset( );
        }

        virtual void String( const char* pszValue, size_t ) CPL_OVERRIDE;
        virtual void Number( const char* pszValue, size_t ) CPL_OVERRIDE;
        virtual void Boolean( bool bVal ) CPL_OVERRIDE;
        virtual void Null( ) CPL_OVERRIDE;

        virtual void StartObject( ) CPL_OVERRIDE;
        virtual void EndObject( ) CPL_OVERRIDE;
        virtual void StartObjectMember( const char* pszKey, size_t ) CPL_OVERRIDE;

        virtual void StartArray( ) CPL_OVERRIDE;
        virtual void EndArray( ) CPL_OVERRIDE;
        virtual void StartArrayMember( ) CPL_OVERRIDE;

        virtual void Exception( const char* pszMessage ) CPL_OVERRIDE;

        const CPLString& GetSerialized( ) const
        {
            return m_osSerialized;
        }
        const CPLString& GetException( ) const
        {
            return m_osException;
        }
    };

    void CPLJSonStreamingParserDump::StartObject( )
    {
        m_osSerialized += "{";
        m_abFirstMember.push_back( true );
    }
    void CPLJSonStreamingParserDump::EndObject( )
    {
        m_osSerialized += "}";
        m_abFirstMember.pop_back( );
    }

    void CPLJSonStreamingParserDump::StartObjectMember( const char* pszKey,
        size_t )
    {
        if ( !m_abFirstMember.back( ) )
            m_osSerialized += ", ";
        m_osSerialized += CPLSPrintf( "\"%s\": ", pszKey );
        m_abFirstMember.back( ) = false;
    }

    void CPLJSonStreamingParserDump::String( const char* pszValue, size_t )
    {
        m_osSerialized += GetSerializedString( pszValue );
    }

    void CPLJSonStreamingParserDump::Number( const char* pszValue, size_t )
    {
        m_osSerialized += pszValue;
    }

    void CPLJSonStreamingParserDump::Boolean( bool bVal )
    {
        m_osSerialized += bVal ? "true" : "false";
    }

    void CPLJSonStreamingParserDump::Null( )
    {
        m_osSerialized += "null";
    }

    void CPLJSonStreamingParserDump::StartArray( )
    {
        m_osSerialized += "[";
        m_abFirstMember.push_back( true );
    }

    void CPLJSonStreamingParserDump::EndArray( )
    {
        m_osSerialized += "]";
        m_abFirstMember.pop_back( );
    }

    void CPLJSonStreamingParserDump::StartArrayMember( )
    {
        if ( !m_abFirstMember.back( ) )
            m_osSerialized += ", ";
        m_abFirstMember.back( ) = false;
    }

    void CPLJSonStreamingParserDump::Exception( const char* pszMessage )
    {
        m_osException = pszMessage;
    }

    TEST( CPL, CPLJSonStreamingParserTest )
    {
        // nominal cases
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "true";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "false";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "null";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "10";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "123eE-34";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"\"";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"\\\\a\\b\\f\\n\\r\\t\\u0020\\u0001\\\"\"";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), "\"\\\\a\\b\\f\\n\\r\\t \\u0001\\\"\"" );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), "\"\\\\a\\b\\f\\n\\r\\t \\u0001\\\"\"" );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"\\u0001\\u0020\\ud834\\uDD1E\\uDD1E\\uD834\\uD834\\uD834\"";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), "\"\\u0001 \xf0\x9d\x84\x9e\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\"" );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"\\ud834\"";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), "\"\xef\xbf\xbd\"" );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"\\ud834\\t\"";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), "\"\xef\xbf\xbd\\t\"" );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"\\u00e9\"";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), "\"\xc3\xa9\"" );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{}";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "[]";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "[[]]";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "[1]";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "[1,2]";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), "[1, 2]" );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), "[1, 2]" );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{\"a\":null}";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), "{\"a\": null}" );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), "{\"a\": null}" );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = " { \"a\" : null ,\r\n\t\"b\": {\"c\": 1}, \"d\": [1] }";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            const char sExpected[] = "{\"a\": null, \"b\": {\"c\": 1}, \"d\": [1]}";
            EXPECT_EQ( oParser.GetSerialized( ), sExpected );

            oParser.Reset( );
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sExpected );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sExpected );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "infinity";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "-infinity";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "nan";
            EXPECT_TRUE( oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );

            oParser.Reset( );
            for ( size_t i = 0; sText[i]; i++ )
                EXPECT_TRUE( oParser.Parse( sText + i, 1, sText[i + 1] == 0 ) );
            EXPECT_EQ( oParser.GetSerialized( ), sText );
        }

        // errors
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "tru";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "tru1";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "truxe";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "truex";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "fals";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "falsxe";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "falsex";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "nul";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "nulxl";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "nullx";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "na";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "nanx";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "infinit";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "infinityx";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "-infinit";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "-infinityx";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "true false";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "x";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "}";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "[";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "[1";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "[,";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "[|";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "]";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{ :";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{ ,";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{ |";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{ 1";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{ \"x\"";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{ \"x\": ";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{ \"x\": 1 2";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{ \"x\", ";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{ \"x\" }";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{\"a\" x}";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "1x";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"\\";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"\\x\"";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"\\u";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"\\ux";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"\\u000";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"\\uD834\\ux\"";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"\\\"";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "\"too long\"";
            oParser.SetMaxStringSize( 2 );
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "[[]]";
            oParser.SetMaxDepth( 1 );
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "{ \"x\": {} }";
            oParser.SetMaxDepth( 1 );
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "[,]";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "[true,]";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "[true,,true]";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
        {
            CPLJSonStreamingParserDump oParser;
            const char sText[] = "[true true]";
            EXPECT_TRUE( !oParser.Parse( sText, strlen( sText ), true ) );
            EXPECT_TRUE( !oParser.GetException( ).empty( ) );
        }
    }

    TEST( CPL, CPLMemCacheTest )
    {
        lru11::Cache<int, int> cache( 2, 1 );
        EXPECT_EQ( cache.size( ), 0U );
        EXPECT_TRUE( cache.empty( ) );
        cache.clear( );
        int val;
        EXPECT_TRUE( !cache.tryGet( 0, val ) );
        try
        {
            cache.get( 0 );
            EXPECT_TRUE( false );
        }
        catch ( const lru11::KeyNotFound& )
        {
            EXPECT_TRUE( true );
        }
        EXPECT_TRUE( !cache.remove( 0 ) );
        EXPECT_TRUE( !cache.contains( 0 ) );
        EXPECT_EQ( cache.getMaxSize( ), 2U );
        EXPECT_EQ( cache.getElasticity( ), 1U );
        EXPECT_EQ( cache.getMaxAllowedSize( ), 3U );

        cache.insert( 0, 1 );
        val = 0;
        EXPECT_TRUE( cache.tryGet( 0, val ) );
        EXPECT_EQ( val, 1 );
        EXPECT_EQ( cache.get( 0 ), 1 );
        EXPECT_EQ( cache.getCopy( 0 ), 1 );
        EXPECT_EQ( cache.size( ), 1U );
        EXPECT_TRUE( !cache.empty( ) );
        EXPECT_TRUE( cache.contains( 0 ) );
        bool visited = false;
        auto lambda = [&visited]( const lru11::KeyValuePair<int, int>& kv )
        {
            if ( kv.key == 0 && kv.value == 1 )
                visited = true;
        };
        cache.cwalk( lambda );
        EXPECT_TRUE( visited );
        cache.insert( 0, 2 );
        EXPECT_EQ( cache.get( 0 ), 2 );
        EXPECT_EQ( cache.size( ), 1U );
        cache.insert( 1, 3 );
        cache.insert( 2, 4 );
        EXPECT_EQ( cache.size( ), 3U );
        cache.insert( 3, 5 );
        EXPECT_EQ( cache.size( ), 2U );
        EXPECT_TRUE( cache.contains( 2 ) );
        EXPECT_TRUE( cache.contains( 3 ) );
        EXPECT_TRUE( !cache.contains( 0 ) );
        EXPECT_TRUE( !cache.contains( 1 ) );
        EXPECT_TRUE( cache.remove( 2 ) );
        EXPECT_TRUE( !cache.contains( 2 ) );
        EXPECT_EQ( cache.size( ), 1U );
    }

    TEST( CPL, CPLJSONDocumentTest )
    {
        {
            // Test Json document LoadUrl
            CPLJSONDocument oDocument;
            const char* options[5] = {
              "CONNECTTIMEOUT=15",
              "TIMEOUT=20",
              "MAX_RETRY=5",
              "RETRY_DELAY=1",
              nullptr
            };

            oDocument.GetRoot( ).Add( "foo", "bar" );

            if ( CPLHTTPEnabled( ) )
            {
                CPLSetConfigOption( "CPL_CURL_ENABLE_VSIMEM", "YES" );
                VSILFILE* fpTmp = VSIFOpenL( "/vsimem/test.json", "wb" );
                const char* pszContent = "{ \"foo\": \"bar\" }";
                VSIFWriteL( pszContent, 1, strlen( pszContent ), fpTmp );
                VSIFCloseL( fpTmp );
                EXPECT_TRUE( oDocument.LoadUrl(
                    "/vsimem/test.json",
                    const_cast<char**>( options ) ) );
                CPLSetConfigOption( "CPL_CURL_ENABLE_VSIMEM", nullptr );
                VSIUnlink( "/vsimem/test.json" );

                CPLJSONObject oJsonRoot = oDocument.GetRoot( );
                EXPECT_TRUE( oJsonRoot.IsValid( ) );

                CPLString value = oJsonRoot.GetString( "foo", "" );
                EXPECT_FALSE( EQUAL( value, "bar" ) );
            }
        }
        {
            // Test Json document LoadChunks
            CPLJSONDocument oDocument;

            CPLPushErrorHandler( CPLQuietErrorHandler );
            EXPECT_TRUE( !oDocument.LoadChunks( "/i_do/not/exist", 512 ) );
            CPLPopErrorHandler( );

            CPLPushErrorHandler( CPLQuietErrorHandler );
            EXPECT_TRUE( !oDocument.LoadChunks( "test_cpl.cpp", 512 ) );
            CPLPopErrorHandler( );

            oDocument.GetRoot( ).Add( "foo", "bar" );

            auto test_json = GetCppDataDirecory( ) + "\\test.json";

            EXPECT_TRUE( oDocument.LoadChunks( test_json.c_str( ), 512 ) );

            CPLJSONObject oJsonRoot = oDocument.GetRoot( );
            EXPECT_TRUE( oJsonRoot.IsValid( ) );
            EXPECT_EQ( oJsonRoot.GetInteger( "resource/id", 10 ), 0 );

            CPLJSONObject oJsonResource = oJsonRoot.GetObj( "resource" );
            EXPECT_TRUE( oJsonResource.IsValid( ) );
            std::vector<CPLJSONObject> children = oJsonResource.GetChildren( );
            EXPECT_TRUE( children.size( ) == 11 );

            CPLJSONArray oaScopes = oJsonRoot.GetArray( "resource/scopes" );
            EXPECT_TRUE( oaScopes.IsValid( ) );
            EXPECT_EQ( oaScopes.Size( ), 2 );

            CPLJSONObject oHasChildren = oJsonRoot.GetObj( "resource/children" );
            EXPECT_TRUE( oHasChildren.IsValid( ) );
            EXPECT_EQ( oHasChildren.ToBool( ), true );

            EXPECT_EQ( oJsonResource.GetBool( "children", false ), true );

            CPLJSONObject oJsonId = oJsonRoot["resource/owner_user/id"];
            EXPECT_TRUE( oJsonId.IsValid( ) );
        }
        {
            CPLJSONDocument oDocument;
            EXPECT_TRUE( !oDocument.LoadMemory( nullptr, 0 ) );
            EXPECT_TRUE( !oDocument.LoadMemory( CPLString( ) ) );
            EXPECT_TRUE( oDocument.LoadMemory( std::string( "true" ) ) );
            EXPECT_TRUE( oDocument.GetRoot( ).GetType( ) == CPLJSONObject::Type::Boolean );
            EXPECT_TRUE( oDocument.GetRoot( ).ToBool( ) );
            EXPECT_TRUE( oDocument.LoadMemory( std::string( "false" ) ) );
            EXPECT_TRUE( oDocument.GetRoot( ).GetType( ) == CPLJSONObject::Type::Boolean );
            EXPECT_TRUE( !oDocument.GetRoot( ).ToBool( ) );
        }
        {
            // Copy constructor
            CPLJSONDocument oDocument;
            oDocument.GetRoot( );
            CPLJSONDocument oDocument2( oDocument );
            CPLJSONObject oObj;
            CPLJSONObject oObj2( oObj );
            // Assignment operator
            oDocument2 = oDocument;
            auto& oDocument2Ref( oDocument2 );
            oDocument2 = oDocument2Ref;
            oObj2 = oObj;
            auto& oObj2Ref( oObj2 );
            oObj2 = oObj2Ref;
        }
        {
            // Move constructor
            CPLJSONDocument oDocument;
            oDocument.GetRoot( );
            CPLJSONDocument oDocument2( std::move( oDocument ) );
        }
        {
            // Move assignment
            CPLJSONDocument oDocument;
            oDocument.GetRoot( );
            CPLJSONDocument oDocument2;
            oDocument2 = std::move( oDocument );
        }
        {
            // Save
            CPLJSONDocument oDocument;
            CPLPushErrorHandler( CPLQuietErrorHandler );
            EXPECT_TRUE( !oDocument.Save( "/i_do/not/exist" ) );
            CPLPopErrorHandler( );
        }
        {
            CPLJSONObject oObj;
            oObj.Add( "string", std::string( "my_string" ) );
            EXPECT_EQ( oObj.GetString( "string" ), std::string( "my_string" ) );
            EXPECT_EQ( oObj.GetString( "inexisting_string", "default" ), std::string( "default" ) );
            oObj.Add( "const_char_star", nullptr );
            oObj.Add( "const_char_star", "my_const_char_star" );
            EXPECT_TRUE( oObj.GetObj( "const_char_star" ).GetType( ) == CPLJSONObject::Type::String );
            oObj.Add( "int", 1 );
            EXPECT_EQ( oObj.GetInteger( "int" ), 1 );
            EXPECT_EQ( oObj.GetInteger( "inexisting_int", -987 ), -987 );
            EXPECT_TRUE( oObj.GetObj( "int" ).GetType( ) == CPLJSONObject::Type::Integer );
            oObj.Add( "int64", GINT64_MAX );
            EXPECT_EQ( oObj.GetLong( "int64" ), GINT64_MAX );
            EXPECT_EQ( oObj.GetLong( "inexisting_int64", GINT64_MIN ), GINT64_MIN );
            EXPECT_TRUE( oObj.GetObj( "int64" ).GetType( ) == CPLJSONObject::Type::Long );
            oObj.Add( "double", 1.25 );
            EXPECT_EQ( oObj.GetDouble( "double" ), 1.25 );
            EXPECT_EQ( oObj.GetDouble( "inexisting_double", -987.0 ), -987.0 );
            EXPECT_TRUE( oObj.GetObj( "double" ).GetType( ) == CPLJSONObject::Type::Double );
            oObj.Add( "array", CPLJSONArray( ) );
            EXPECT_TRUE( oObj.GetObj( "array" ).GetType( ) == CPLJSONObject::Type::Array );
            oObj.Add( "obj", CPLJSONObject( ) );
            EXPECT_TRUE( oObj.GetObj( "obj" ).GetType( ) == CPLJSONObject::Type::Object );
            oObj.Add( "bool", true );
            EXPECT_EQ( oObj.GetBool( "bool" ), true );
            EXPECT_EQ( oObj.GetBool( "inexisting_bool", false ), false );
            EXPECT_TRUE( oObj.GetObj( "bool" ).GetType( ) == CPLJSONObject::Type::Boolean );
            oObj.AddNull( "null_field" );
            EXPECT_TRUE( oObj.GetObj( "null_field" ).GetType( ) == CPLJSONObject::Type::Null );
            EXPECT_TRUE( oObj.GetObj( "inexisting" ).GetType( ) == CPLJSONObject::Type::Unknown );
            oObj.Set( "string", std::string( "my_string" ) );
            oObj.Set( "const_char_star", nullptr );
            oObj.Set( "const_char_star", "my_const_char_star" );
            oObj.Set( "int", 1 );
            oObj.Set( "int64", GINT64_MAX );
            oObj.Set( "double", 1.25 );
            //oObj.Set("array", CPLJSONArray());
            //oObj.Set("obj", CPLJSONObject());
            oObj.Set( "bool", true );
            oObj.SetNull( "null_field" );
            EXPECT_TRUE( CPLJSONArray( ).GetChildren( ).empty( ) );
            oObj.ToArray( );
            EXPECT_EQ( CPLJSONObject( ).Format( CPLJSONObject::PrettyFormat::Spaced ), std::string( "{ }" ) );
            EXPECT_EQ( CPLJSONObject( ).Format( CPLJSONObject::PrettyFormat::Pretty ), std::string( "{\n}" ) );
            EXPECT_EQ( CPLJSONObject( ).Format( CPLJSONObject::PrettyFormat::Plain ), std::string( "{}" ) );
        }
        {
            CPLJSONArray oArrayConstructorString( std::string( "foo" ) );
            CPLJSONArray oArray;
            oArray.Add( CPLJSONObject( ) );
            oArray.Add( std::string( "str" ) );
            oArray.Add( "const_char_star" );
            oArray.Add( 1.25 );
            oArray.Add( 1 );
            oArray.Add( GINT64_MAX );
            oArray.Add( true );
            EXPECT_EQ( oArray.Size( ), 7 );

            int nCount = 0;
            for ( const auto& obj : oArray )
            {
                EXPECT_EQ( obj.GetInternalHandle( ), oArray[nCount].GetInternalHandle( ) );
                nCount++;
            }
            EXPECT_EQ( nCount, 7 );
        }
        {
            CPLJSONDocument oDocument;
            EXPECT_TRUE( oDocument.LoadMemory( CPLString( "{ \"/foo\" : \"bar\" }" ) ) );
            EXPECT_EQ( oDocument.GetRoot( ).GetString( "/foo" ), std::string( "bar" ) );
        }
    }

    TEST( CPL, CPLHTTPParseMultipartMimeTest )
    {
        CPLHTTPResult* psResult;

        psResult =
            static_cast<CPLHTTPResult*>( CPLCalloc( 1, sizeof( CPLHTTPResult ) ) );
        CPLPushErrorHandler( CPLQuietErrorHandler );
        EXPECT_TRUE( !CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        CPLPopErrorHandler( );
        CPLHTTPDestroyResult( psResult );

        // Missing boundary value
        psResult =
            static_cast<CPLHTTPResult*>( CPLCalloc( 1, sizeof( CPLHTTPResult ) ) );
        psResult->pszContentType =
            CPLStrdup( "multipart/form-data; boundary=" );
        CPLPushErrorHandler( CPLQuietErrorHandler );
        EXPECT_TRUE( !CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        CPLPopErrorHandler( );
        CPLHTTPDestroyResult( psResult );

        // No content
        psResult =
            static_cast<CPLHTTPResult*>( CPLCalloc( 1, sizeof( CPLHTTPResult ) ) );
        psResult->pszContentType =
            CPLStrdup( "multipart/form-data; boundary=myboundary" );
        CPLPushErrorHandler( CPLQuietErrorHandler );
        EXPECT_TRUE( !CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        CPLPopErrorHandler( );
        CPLHTTPDestroyResult( psResult );

        // No part
        psResult =
            static_cast<CPLHTTPResult*>( CPLCalloc( 1, sizeof( CPLHTTPResult ) ) );
        psResult->pszContentType =
            CPLStrdup( "multipart/form-data; boundary=myboundary" );
        {
            const char* pszText = "--myboundary  some junk\r\n";
            psResult->pabyData = reinterpret_cast<GByte*>( CPLStrdup( pszText ) );
            psResult->nDataLen = static_cast<int>( strlen( pszText ) );
        }
        CPLPushErrorHandler( CPLQuietErrorHandler );
        EXPECT_TRUE( !CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        CPLPopErrorHandler( );
        CPLHTTPDestroyResult( psResult );

        // Missing end boundary
        psResult =
            static_cast<CPLHTTPResult*>( CPLCalloc( 1, sizeof( CPLHTTPResult ) ) );
        psResult->pszContentType =
            CPLStrdup( "multipart/form-data; boundary=myboundary" );
        {
            const char* pszText = "--myboundary  some junk\r\n"
                "\r\n"
                "Bla";
            psResult->pabyData = reinterpret_cast<GByte*>( CPLStrdup( pszText ) );
            psResult->nDataLen = static_cast<int>( strlen( pszText ) );
        }
        CPLPushErrorHandler( CPLQuietErrorHandler );
        EXPECT_TRUE( !CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        CPLPopErrorHandler( );
        CPLHTTPDestroyResult( psResult );

        // Truncated header
        psResult =
            static_cast<CPLHTTPResult*>( CPLCalloc( 1, sizeof( CPLHTTPResult ) ) );
        psResult->pszContentType =
            CPLStrdup( "multipart/form-data; boundary=myboundary" );
        {
            const char* pszText = "--myboundary  some junk\r\n"
                "Content-Type: foo";
            psResult->pabyData = reinterpret_cast<GByte*>( CPLStrdup( pszText ) );
            psResult->nDataLen = static_cast<int>( strlen( pszText ) );
        }
        CPLPushErrorHandler( CPLQuietErrorHandler );
        EXPECT_TRUE( !CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        CPLPopErrorHandler( );
        CPLHTTPDestroyResult( psResult );

        // Invalid end boundary
        psResult =
            static_cast<CPLHTTPResult*>( CPLCalloc( 1, sizeof( CPLHTTPResult ) ) );
        psResult->pszContentType =
            CPLStrdup( "multipart/form-data; boundary=myboundary" );
        {
            const char* pszText = "--myboundary  some junk\r\n"
                "\r\n"
                "Bla"
                "\r\n"
                "--myboundary";
            psResult->pabyData = reinterpret_cast<GByte*>( CPLStrdup( pszText ) );
            psResult->nDataLen = static_cast<int>( strlen( pszText ) );
        }
        CPLPushErrorHandler( CPLQuietErrorHandler );
        EXPECT_TRUE( !CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        CPLPopErrorHandler( );
        CPLHTTPDestroyResult( psResult );

        // Invalid end boundary
        psResult =
            static_cast<CPLHTTPResult*>( CPLCalloc( 1, sizeof( CPLHTTPResult ) ) );
        psResult->pszContentType =
            CPLStrdup( "multipart/form-data; boundary=myboundary" );
        {
            const char* pszText = "--myboundary  some junk\r\n"
                "\r\n"
                "Bla"
                "\r\n"
                "--myboundary";
            psResult->pabyData = reinterpret_cast<GByte*>( CPLStrdup( pszText ) );
            psResult->nDataLen = static_cast<int>( strlen( pszText ) );
        }
        CPLPushErrorHandler( CPLQuietErrorHandler );
        EXPECT_TRUE( !CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        CPLPopErrorHandler( );
        CPLHTTPDestroyResult( psResult );

        // Valid single part, no header
        psResult =
            static_cast<CPLHTTPResult*>( CPLCalloc( 1, sizeof( CPLHTTPResult ) ) );
        psResult->pszContentType =
            CPLStrdup( "multipart/form-data; boundary=myboundary" );
        {
            const char* pszText =
                "--myboundary  some junk\r\n"
                "\r\n"
                "Bla"
                "\r\n"
                "--myboundary--\r\n";
            psResult->pabyData = reinterpret_cast<GByte*>( CPLStrdup( pszText ) );
            psResult->nDataLen = static_cast<int>( strlen( pszText ) );
        }
        EXPECT_TRUE( CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        EXPECT_EQ( psResult->nMimePartCount, 1 );
        EXPECT_EQ( psResult->pasMimePart[0].papszHeaders,
            static_cast<char**>( nullptr ) );
        EXPECT_EQ( psResult->pasMimePart[0].nDataLen, 3 );
        EXPECT_TRUE( strncmp( reinterpret_cast<char*>( psResult->pasMimePart[0].pabyData ),
            "Bla", 3 ) == 0 );
        EXPECT_TRUE( CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        CPLHTTPDestroyResult( psResult );

        // Valid single part, with header
        psResult =
            static_cast<CPLHTTPResult*>( CPLCalloc( 1, sizeof( CPLHTTPResult ) ) );
        psResult->pszContentType =
            CPLStrdup( "multipart/form-data; boundary=myboundary" );
        {
            const char* pszText =
                "--myboundary  some junk\r\n"
                "Content-Type: bla\r\n"
                "\r\n"
                "Bla"
                "\r\n"
                "--myboundary--\r\n";
            psResult->pabyData = reinterpret_cast<GByte*>( CPLStrdup( pszText ) );
            psResult->nDataLen = static_cast<int>( strlen( pszText ) );
        }
        EXPECT_TRUE( CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        EXPECT_EQ( psResult->nMimePartCount, 1 );
        EXPECT_EQ( CSLCount( psResult->pasMimePart[0].papszHeaders ), 1 );
        EXPECT_EQ( CPLString( psResult->pasMimePart[0].papszHeaders[0] ), CPLString( "Content-Type=bla" ) );
        EXPECT_EQ( psResult->pasMimePart[0].nDataLen, 3 );
        EXPECT_TRUE( strncmp( reinterpret_cast<char*>( psResult->pasMimePart[0].pabyData ), "Bla", 3 ) == 0 );
        EXPECT_TRUE( CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        CPLHTTPDestroyResult( psResult );

        // Valid single part, 2 headers
        psResult =
            static_cast<CPLHTTPResult*>( CPLCalloc( 1, sizeof( CPLHTTPResult ) ) );
        psResult->pszContentType =
            CPLStrdup( "multipart/form-data; boundary=myboundary" );
        {
            const char* pszText =
                "--myboundary  some junk\r\n"
                "Content-Type: bla\r\n"
                "Content-Disposition: bar\r\n"
                "\r\n"
                "Bla"
                "\r\n"
                "--myboundary--\r\n";
            psResult->pabyData = reinterpret_cast<GByte*>( CPLStrdup( pszText ) );
            psResult->nDataLen = static_cast<int>( strlen( pszText ) );
        }
        EXPECT_TRUE( CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        EXPECT_EQ( psResult->nMimePartCount, 1 );
        EXPECT_EQ( CSLCount( psResult->pasMimePart[0].papszHeaders ), 2 );
        EXPECT_EQ( CPLString( psResult->pasMimePart[0].papszHeaders[0] ), CPLString( "Content-Type=bla" ) );
        EXPECT_EQ( CPLString( psResult->pasMimePart[0].papszHeaders[1] ), CPLString( "Content-Disposition=bar" ) );
        EXPECT_EQ( psResult->pasMimePart[0].nDataLen, 3 );
        EXPECT_TRUE( strncmp( reinterpret_cast<char*>( psResult->pasMimePart[0].pabyData ), "Bla", 3 ) == 0 );
        EXPECT_TRUE( CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        CPLHTTPDestroyResult( psResult );

        // Single part, but with header without extra terminating \r\n
        // (invalid normally, but apparently necessary for some ArcGIS WCS implementations)
        psResult =
            static_cast<CPLHTTPResult*>( CPLCalloc( 1, sizeof( CPLHTTPResult ) ) );
        psResult->pszContentType =
            CPLStrdup( "multipart/form-data; boundary=myboundary" );
        {
            const char* pszText =
                "--myboundary  some junk\r\n"
                "Content-Type: bla\r\n"
                "Bla"
                "\r\n"
                "--myboundary--\r\n";
            psResult->pabyData = reinterpret_cast<GByte*>( CPLStrdup( pszText ) );
            psResult->nDataLen = static_cast<int>( strlen( pszText ) );
        }
        EXPECT_TRUE( CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        EXPECT_EQ( psResult->nMimePartCount, 1 );
        EXPECT_EQ( CPLString( psResult->pasMimePart[0].papszHeaders[0] ), CPLString( "Content-Type=bla" ) );
        EXPECT_EQ( psResult->pasMimePart[0].nDataLen, 3 );
        EXPECT_TRUE( strncmp( reinterpret_cast<char*>( psResult->pasMimePart[0].pabyData ), "Bla", 3 ) == 0 );
        EXPECT_TRUE( CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        CPLHTTPDestroyResult( psResult );

        // Valid 2 parts, no header
        psResult =
            static_cast<CPLHTTPResult*>( CPLCalloc( 1, sizeof( CPLHTTPResult ) ) );
        psResult->pszContentType =
            CPLStrdup( "multipart/form-data; boundary=myboundary" );
        {
            const char* pszText =
                "--myboundary  some junk\r\n"
                "\r\n"
                "Bla"
                "\r\n"
                "--myboundary\r\n"
                "\r\n"
                "second part"
                "\r\n"
                "--myboundary--\r\n";
            psResult->pabyData = reinterpret_cast<GByte*>( CPLStrdup( pszText ) );
            psResult->nDataLen = static_cast<int>( strlen( pszText ) );
        }
        EXPECT_TRUE( CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        EXPECT_EQ( psResult->nMimePartCount, 2 );
        EXPECT_EQ( psResult->pasMimePart[0].papszHeaders, static_cast<char**>( nullptr ) );
        EXPECT_EQ( psResult->pasMimePart[0].nDataLen, 3 );
        EXPECT_TRUE( strncmp( reinterpret_cast<char*>( psResult->pasMimePart[0].pabyData ), "Bla", 3 ) == 0 );
        EXPECT_EQ( psResult->pasMimePart[1].nDataLen, 11 );
        EXPECT_TRUE( strncmp( reinterpret_cast<char*>( psResult->pasMimePart[1].pabyData ), "second part", 11 ) == 0 );
        EXPECT_TRUE( CPL_TO_BOOL( CPLHTTPParseMultipartMime( psResult ) ) );
        CPLHTTPDestroyResult( psResult );
    }

    TEST( CPL, CPLdown_castTest )
    {
        struct Base
        {
            virtual ~Base( )
            {
            }
        };
        struct Derived : public Base
        {
        };
        Base b;
        Derived d;
        Base* p_b_d = &d;

#ifdef wont_compile
        struct OtherBase
        {
        };
        OtherBase ob;
        EXPECT_EQ( cpl::down_cast<OtherBase*>( p_b_d ), &ob );
#endif
#ifdef compile_with_warning
        EXPECT_EQ( cpl::down_cast<Base*>( p_b_d ), p_b_d );
#endif
        EXPECT_EQ( cpl::down_cast<Derived*>( p_b_d ), &d );
        EXPECT_EQ( cpl::down_cast<Derived*>( static_cast<Base*>( nullptr ) ), static_cast<Derived*>( nullptr ) );
    }

    TEST( CPL, CPLPrintTimeTest )
    {
        char szDate[64];
        struct tm tm;
        tm.tm_sec = 56;
        tm.tm_min = 34;
        tm.tm_hour = 12;
        tm.tm_mday = 20;
        tm.tm_mon = 6 - 1;
        tm.tm_year = 2018 - 1900;
        tm.tm_wday = 3; // Wednesday
        tm.tm_yday = 0; // unused
        tm.tm_isdst = 0; // unused
        int nRet = CPLPrintTime( szDate, sizeof( szDate ) - 1,
            "%a, %d %b %Y %H:%M:%S GMT", &tm, "C" );
        szDate[nRet] = 0;
        EXPECT_EQ( std::string( szDate ), std::string( "Wed, 20 Jun 2018 12:34:56 GMT" ) );
    }

    TEST( CPL, CPLAutoCloseTest )
    {
        static int counter = 0;
        class AutoCloseTest
        {
        public:
            AutoCloseTest( )
            {
                counter += 222;
            }
            virtual ~AutoCloseTest( )
            {
                counter -= 22;
            }
            static AutoCloseTest* Create( )
            {
                return new AutoCloseTest;
            }
            static void Destroy( AutoCloseTest* p )
            {
                delete p;
            }
        };
        {
            AutoCloseTest* p1 = AutoCloseTest::Create( );
            CPL_AUTO_CLOSE_WARP( p1, AutoCloseTest::Destroy );

            AutoCloseTest* p2 = AutoCloseTest::Create( );
            CPL_AUTO_CLOSE_WARP( p2, AutoCloseTest::Destroy );

        }
        EXPECT_EQ( counter, 400 );
    }

    TEST( CPL, cpl_minixmlTest )
    {
        CPLXMLNode* psRoot = CPLCreateXMLNode( nullptr, CXT_Element, "Root" );
        CPLXMLNode* psElt = CPLCreateXMLElementAndValue( psRoot, "Elt", "value" );
        CPLAddXMLAttributeAndValue( psElt, "attr1", "val1" );
        CPLAddXMLAttributeAndValue( psElt, "attr2", "val2" );
        char* str = CPLSerializeXMLTree( psRoot );
        CPLDestroyXMLNode( psRoot );
        EXPECT_EQ( std::string( str ), std::string( "<Root>\n  <Elt attr1=\"val1\" attr2=\"val2\">value</Elt>\n</Root>\n" ) );
        CPLFree( str );
    }

    TEST( CPL, CPLCharUniquePtrTest )
    {
        CPLCharUniquePtr x;
        EXPECT_TRUE( x.get( ) == nullptr );
        x.reset( CPLStrdup( "foo" ) );
        EXPECT_EQ( std::string( x.get( ) ), "foo" );
    }
    TEST( CPL, CPLJSonStreamingWriterTest )
    {
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            EXPECT_EQ( x.GetString( ), std::string( ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( true );
            EXPECT_EQ( x.GetString( ), std::string( "true" ) );
        }
        {
            std::string res;
            struct MyCallback
            {
                static void f( const char* pszText, void* user_data )
                {
                    *static_cast<std::string*>( user_data ) += pszText;
                }
            };
            CPLJSonStreamingWriter x( &MyCallback::f, &res );
            x.Add( true );
            EXPECT_EQ( x.GetString( ), std::string( ) );
            EXPECT_EQ( res, std::string( "true" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( false );
            EXPECT_EQ( x.GetString( ), std::string( "false" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.AddNull( );
            EXPECT_EQ( x.GetString( ), std::string( "null" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( 1 );
            EXPECT_EQ( x.GetString( ), std::string( "1" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( 4200000000U );
            EXPECT_EQ( x.GetString( ), std::string( "4200000000" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( static_cast<GIntBig>( -10000 ) * 1000000 );
            EXPECT_EQ( x.GetString( ), std::string( "-10000000000" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( static_cast<GUInt64>( 10000 ) * 1000000 );
            EXPECT_EQ( x.GetString( ), std::string( "10000000000" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( 1.5f );
            EXPECT_EQ( x.GetString( ), std::string( "1.5" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( std::numeric_limits<float>::quiet_NaN( ) );
            EXPECT_EQ( x.GetString( ), std::string( "\"NaN\"" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( std::numeric_limits<float>::infinity( ) );
            EXPECT_EQ( x.GetString( ), std::string( "\"Infinity\"" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( -std::numeric_limits<float>::infinity( ) );
            EXPECT_EQ( x.GetString( ), std::string( "\"-Infinity\"" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( 1.25 );
            EXPECT_EQ( x.GetString( ), std::string( "1.25" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( std::numeric_limits<double>::quiet_NaN( ) );
            EXPECT_EQ( x.GetString( ), std::string( "\"NaN\"" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( std::numeric_limits<double>::infinity( ) );
            EXPECT_EQ( x.GetString( ), std::string( "\"Infinity\"" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( -std::numeric_limits<double>::infinity( ) );
            EXPECT_EQ( x.GetString( ), std::string( "\"-Infinity\"" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( std::string( "foo\\bar\"baz\b\f\n\r\t" "\x01" "boo" ) );
            EXPECT_EQ( x.GetString( ), std::string( "\"foo\\\\bar\\\"baz\\b\\f\\n\\r\\t\\u0001boo\"" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.Add( "foo\\bar\"baz\b\f\n\r\t" "\x01" "boo" );
            EXPECT_EQ( x.GetString( ), std::string( "\"foo\\\\bar\\\"baz\\b\\f\\n\\r\\t\\u0001boo\"" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.SetPrettyFormatting( false );
            {
                auto ctxt( x.MakeObjectContext( ) );
            }
            EXPECT_EQ( x.GetString( ), std::string( "{}" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            {
                auto ctxt( x.MakeObjectContext( ) );
            }
            EXPECT_EQ( x.GetString( ), std::string( "{}" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            x.SetPrettyFormatting( false );
            {
                auto ctxt( x.MakeObjectContext( ) );
                x.AddObjKey( "key" );
                x.Add( "value" );
            }
            EXPECT_EQ( x.GetString( ), std::string( "{\"key\":\"value\"}" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            {
                auto ctxt( x.MakeObjectContext( ) );
                x.AddObjKey( "key" );
                x.Add( "value" );
            }
            EXPECT_EQ( x.GetString( ), std::string( "{\n  \"key\": \"value\"\n}" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            {
                auto ctxt( x.MakeObjectContext( ) );
                x.AddObjKey( "key" );
                x.Add( "value" );
                x.AddObjKey( "key2" );
                x.Add( "value2" );
            }
            EXPECT_EQ( x.GetString( ), std::string( "{\n  \"key\": \"value\",\n  \"key2\": \"value2\"\n}" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            {
                auto ctxt( x.MakeArrayContext( ) );
            }
            EXPECT_EQ( x.GetString( ), std::string( "[]" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            {
                auto ctxt( x.MakeArrayContext( ) );
                x.Add( 1 );
            }
            EXPECT_EQ( x.GetString( ), std::string( "[\n  1\n]" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            {
                auto ctxt( x.MakeArrayContext( ) );
                x.Add( 1 );
                x.Add( 2 );
            }
            EXPECT_EQ( x.GetString( ), std::string( "[\n  1,\n  2\n]" ) );
        }
        {
            CPLJSonStreamingWriter x( nullptr, nullptr );
            {
                auto ctxt( x.MakeArrayContext( true ) );
                x.Add( 1 );
                x.Add( 2 );
            }
            EXPECT_EQ( x.GetString( ), std::string( "[1, 2]" ) );
        }
    }

    TEST( CPL, CPLWorkerThreadPoolTest )
    {
        CPLWorkerThreadPool oPool;
        EXPECT_TRUE( oPool.Setup( 2, nullptr, nullptr ) );

        const auto myJob = []( void* pData )
        {
            ( *static_cast<int*>( pData ) )++;
        };

        {
            std::vector<int> res( 1000 );
            for ( int i = 0; i < 1000; i++ )
            {
                res[i] = i;
                oPool.SubmitJob( myJob, &res[i] );
            }
            oPool.WaitCompletion( );
            for ( int i = 0; i < 1000; i++ )
            {
                EXPECT_EQ( res[i], i + 1 );
            }
        }

        {
            std::vector<int> res( 1000 );
            std::vector<void*> resPtr( 1000 );
            for ( int i = 0; i < 1000; i++ )
            {
                res[i] = i;
                resPtr[i] = &res[i];
            }
            oPool.SubmitJobs( myJob, resPtr );
            oPool.WaitEvent( );
            oPool.WaitCompletion( );
            for ( int i = 0; i < 1000; i++ )
            {
                EXPECT_EQ( res[i], i + 1 );
            }
        }

        {
            auto jobQueue1 = oPool.CreateJobQueue( );
            auto jobQueue2 = oPool.CreateJobQueue( );

            EXPECT_EQ( jobQueue1->GetPool( ), &oPool );

            std::vector<int> res( 1000 );
            for ( int i = 0; i < 1000; i++ )
            {
                res[i] = i;
                if ( i % 2 )
                    jobQueue1->SubmitJob( myJob, &res[i] );
                else
                    jobQueue2->SubmitJob( myJob, &res[i] );
            }
            jobQueue1->WaitCompletion( );
            jobQueue2->WaitCompletion( );
            for ( int i = 0; i < 1000; i++ )
            {
                EXPECT_EQ( res[i], i + 1 );
            }
        }
    }

    TEST( CPL, CPLHTTPFetchTest )
    {
#ifdef HAVE_CURL
        CPLStringList oOptions;
        oOptions.AddNameValue( "FORM_ITEM_COUNT", "5" );
        oOptions.AddNameValue( "FORM_KEY_0", "qqq" );
        oOptions.AddNameValue( "FORM_VALUE_0", "www" );
        CPLHTTPResult* pResult = CPLHTTPFetch( "http://example.com", oOptions );
        EXPECT_EQ( pResult->nStatus, 34 );
        CPLHTTPDestroyResult( pResult );
        pResult = nullptr;
        oOptions.Clear( );

        oOptions.AddNameValue( "FORM_FILE_PATH", "not_existed" );
        pResult = CPLHTTPFetch( "http://example.com", oOptions );
        EXPECT_EQ( pResult->nStatus, 34 );
        CPLHTTPDestroyResult( pResult );

#endif // HAVE_CURL
    }

    TEST( CPL, CPLHTTPPushFetchCallbackTest )
    {
        struct myCbkUserDataStruct
        {
            CPLString osURL{};
            CSLConstList papszOptions = nullptr;
            GDALProgressFunc pfnProgress = nullptr;
            void* pProgressArg = nullptr;
            CPLHTTPFetchWriteFunc pfnWrite = nullptr;
            void* pWriteArg = nullptr;
        };

        const auto myCbk = []( const char* pszURL,
            CSLConstList papszOptions,
            GDALProgressFunc pfnProgress,
            void* pProgressArg,
            CPLHTTPFetchWriteFunc pfnWrite,
            void* pWriteArg,
            void* pUserData )
        {
            myCbkUserDataStruct* pCbkUserData = static_cast<myCbkUserDataStruct*>( pUserData );
            pCbkUserData->osURL = pszURL;
            pCbkUserData->papszOptions = papszOptions;
            pCbkUserData->pfnProgress = pfnProgress;
            pCbkUserData->pProgressArg = pProgressArg;
            pCbkUserData->pfnWrite = pfnWrite;
            pCbkUserData->pWriteArg = pWriteArg;
            auto psResult = static_cast<CPLHTTPResult*>( CPLCalloc( sizeof( CPLHTTPResult ), 1 ) );
            psResult->nStatus = 123;
            return psResult;
        };

        myCbkUserDataStruct userData;
        EXPECT_TRUE( CPLHTTPPushFetchCallback( myCbk, &userData ) );

        int progressArg = 0;
        const auto myWriteCbk = []( void*, size_t, size_t, void* ) -> size_t { return 0; };
        int writeCbkArg = 00;

        CPLStringList aosOptions;
        GDALProgressFunc pfnProgress = GDALTermProgress;
        CPLHTTPFetchWriteFunc pfnWriteCbk = myWriteCbk;
        CPLHTTPResult* pResult = CPLHTTPFetchEx( "http://example.com",
            aosOptions.List( ),
            pfnProgress,
            &progressArg,
            pfnWriteCbk,
            &writeCbkArg );
        EXPECT_TRUE( pResult != nullptr );
        EXPECT_EQ( pResult->nStatus, 123 );
        CPLHTTPDestroyResult( pResult );

        EXPECT_TRUE( CPLHTTPPopFetchCallback( ) );
        CPLPushErrorHandler( CPLQuietErrorHandler );
        EXPECT_TRUE( !CPLHTTPPopFetchCallback( ) );
        CPLPopErrorHandler( );

        EXPECT_EQ( userData.osURL, std::string( "http://example.com" ) );
        EXPECT_EQ( userData.papszOptions, aosOptions.List( ) );
        EXPECT_EQ( userData.pfnProgress, pfnProgress );
        EXPECT_EQ( userData.pProgressArg, &progressArg );
        EXPECT_EQ( userData.pfnWrite, pfnWriteCbk );
        EXPECT_EQ( userData.pWriteArg, &writeCbkArg );
    }

    TEST( CPL, CPLHTTPSetFetchCallbackTest )
    {
        struct myCbkUserDataStruct
        {
            CPLString osURL{};
            CSLConstList papszOptions = nullptr;
            GDALProgressFunc pfnProgress = nullptr;
            void* pProgressArg = nullptr;
            CPLHTTPFetchWriteFunc pfnWrite = nullptr;
            void* pWriteArg = nullptr;
        };

        const auto myCbk2 = []( const char* pszURL,
            CSLConstList papszOptions,
            GDALProgressFunc pfnProgress,
            void* pProgressArg,
            CPLHTTPFetchWriteFunc pfnWrite,
            void* pWriteArg,
            void* pUserData )
        {
            myCbkUserDataStruct* pCbkUserData = static_cast<myCbkUserDataStruct*>( pUserData );
            pCbkUserData->osURL = pszURL;
            pCbkUserData->papszOptions = papszOptions;
            pCbkUserData->pfnProgress = pfnProgress;
            pCbkUserData->pProgressArg = pProgressArg;
            pCbkUserData->pfnWrite = pfnWrite;
            pCbkUserData->pWriteArg = pWriteArg;
            auto psResult = static_cast<CPLHTTPResult*>( CPLCalloc( sizeof( CPLHTTPResult ), 1 ) );
            psResult->nStatus = 124;
            return psResult;
        };
        myCbkUserDataStruct userData2;
        CPLHTTPSetFetchCallback( myCbk2, &userData2 );

        int progressArg = 0;
        const auto myWriteCbk = []( void*, size_t, size_t, void* ) -> size_t { return 0; };
        int writeCbkArg = 00;

        CPLStringList aosOptions;
        GDALProgressFunc pfnProgress = GDALTermProgress;
        CPLHTTPFetchWriteFunc pfnWriteCbk = myWriteCbk;
        CPLHTTPResult* pResult = CPLHTTPFetchEx( "http://example.com",
            aosOptions.List( ),
            pfnProgress,
            &progressArg,
            pfnWriteCbk,
            &writeCbkArg );
        EXPECT_TRUE( pResult != nullptr );
        EXPECT_EQ( pResult->nStatus, 124 );
        CPLHTTPDestroyResult( pResult );

        CPLHTTPSetFetchCallback( nullptr, nullptr );

        EXPECT_EQ( userData2.osURL, std::string( "http://example.com" ) );
        EXPECT_EQ( userData2.papszOptions, aosOptions.List( ) );
        EXPECT_EQ( userData2.pfnProgress, pfnProgress );
        EXPECT_EQ( userData2.pProgressArg, &progressArg );
        EXPECT_EQ( userData2.pfnWrite, pfnWriteCbk );
        EXPECT_EQ( userData2.pWriteArg, &writeCbkArg );
    }

    TEST( CPL, CPLLoadConfigOptionsFromFileTest )
    {
        CPLLoadConfigOptionsFromFile( "/i/do/not/exist", false );

        VSILFILE* fp = VSIFOpenL( "/vsimem/.gdal/gdalrc", "wb" );
        VSIFPrintfL( fp, "[configoptions]\n" );
        VSIFPrintfL( fp, "# some comment\n" );
        VSIFPrintfL( fp, "FOO_CONFIGOPTION=BAR\n" );
        VSIFCloseL( fp );

        // Try CPLLoadConfigOptionsFromFile()
        CPLLoadConfigOptionsFromFile( "/vsimem/.gdal/gdalrc", false );
        EXPECT_TRUE( EQUAL( CPLGetConfigOption( "FOO_CONFIGOPTION", "" ), "BAR" ) );
        CPLSetConfigOption( "FOO_CONFIGOPTION", nullptr );

        // Try CPLLoadConfigOptionsFromPredefinedFiles() with GDAL_CONFIG_FILE set
        CPLSetConfigOption( "GDAL_CONFIG_FILE", "/vsimem/.gdal/gdalrc" );
        CPLLoadConfigOptionsFromPredefinedFiles( );
        EXPECT_TRUE( EQUAL( CPLGetConfigOption( "FOO_CONFIGOPTION", "" ), "BAR" ) );
        CPLSetConfigOption( "FOO_CONFIGOPTION", nullptr );

        // Try CPLLoadConfigOptionsFromPredefinedFiles() with $HOME/.gdal/gdalrc file
#ifdef WIN32
        const char* pszHOMEEnvVarName = "USERPROFILE";
#else
        const char* pszHOMEEnvVarName = "HOME";
#endif
        CPLString osOldVal( CPLGetConfigOption( pszHOMEEnvVarName, "" ) );
        CPLSetConfigOption( pszHOMEEnvVarName, "/vsimem/" );
        CPLLoadConfigOptionsFromPredefinedFiles( );
        EXPECT_TRUE( EQUAL( CPLGetConfigOption( "FOO_CONFIGOPTION", "" ), "BAR" ) );
        CPLSetConfigOption( "FOO_CONFIGOPTION", nullptr );
        if ( !osOldVal.empty( ) )
            CPLSetConfigOption( pszHOMEEnvVarName, osOldVal.c_str( ) );
        else
            CPLSetConfigOption( pszHOMEEnvVarName, nullptr );

        VSIUnlink( "/vsimem/.gdal/gdalrc" );
    }

    TEST( CPL, CPLCompressorDecompressTest )
    {
        const auto compressionLambda = []( const void* /* input_data */,
            size_t /* input_size */,
            void** /* output_data */,
            size_t* /* output_size */,
            CSLConstList /* options */,
            void* /* compressor_user_data */ )
        {
            return false;
        };
        int dummy = 0;

        CPLCompressor sComp;
        sComp.nStructVersion = 1;
        sComp.eType = CCT_COMPRESSOR;
        sComp.pszId = "my_comp";
        const char* const apszMetadata[] = { "FOO=BAR", nullptr };
        sComp.papszMetadata = apszMetadata;
        sComp.pfnFunc = compressionLambda;
        sComp.user_data = &dummy;

        EXPECT_TRUE( CPLRegisterDecompressor( &sComp ) );

        CPLPushErrorHandler( CPLQuietErrorHandler );
        EXPECT_TRUE( !CPLRegisterDecompressor( &sComp ) );
        CPLPopErrorHandler( );

        char** decompressors = CPLGetDecompressors( );
        EXPECT_TRUE( decompressors != nullptr );
        EXPECT_TRUE( CSLFindString( decompressors, sComp.pszId ) >= 0 );
        for ( auto iter = decompressors; *iter; ++iter )
        {
            const auto pCompressor = CPLGetDecompressor( *iter );
            EXPECT_TRUE( pCompressor );
            const char* pszOptions = CSLFetchNameValue( pCompressor->papszMetadata, "OPTIONS" );
            if ( pszOptions )
            {
                auto psNode = CPLParseXMLString( pszOptions );
                EXPECT_TRUE( psNode );
                CPLDestroyXMLNode( psNode );
            }
            else
            {
                CPLDebug( "TEST", "Decompressor %s has no OPTIONS", *iter );
            }
        }
        CSLDestroy( decompressors );

        EXPECT_TRUE( CPLGetDecompressor( "invalid" ) == nullptr );
        const auto pCompressor = CPLGetDecompressor( sComp.pszId );
        EXPECT_TRUE( pCompressor );
        EXPECT_EQ( std::string( pCompressor->pszId ), std::string( sComp.pszId ) );
        EXPECT_EQ( CSLCount( pCompressor->papszMetadata ), CSLCount( sComp.papszMetadata ) );
        EXPECT_TRUE( pCompressor->pfnFunc != nullptr );
        EXPECT_EQ( pCompressor->user_data, sComp.user_data );

        CPLDestroyCompressorRegistry( );
        EXPECT_TRUE( CPLGetDecompressor( sComp.pszId ) == nullptr );
    }

    TEST( CPL, CPLCompressorCompressTest )
    {
        const auto compressionLambda = []( const void* /* input_data */,
            size_t /* input_size */,
            void** /* output_data */,
            size_t* /* output_size */,
            CSLConstList /* options */,
            void* /* compressor_user_data */ )
        {
            return false;
        };
        int dummy = 0;

        CPLCompressor sComp;
        sComp.nStructVersion = 1;
        sComp.eType = CCT_COMPRESSOR;
        sComp.pszId = "my_comp";
        const char* const apszMetadata[] = { "FOO=BAR", nullptr };
        sComp.papszMetadata = apszMetadata;
        sComp.pfnFunc = compressionLambda;
        sComp.user_data = &dummy;

        EXPECT_TRUE( CPLRegisterCompressor( &sComp ) );

        CPLPushErrorHandler( CPLQuietErrorHandler );
        EXPECT_TRUE( !CPLRegisterCompressor( &sComp ) );
        CPLPopErrorHandler( );

        char** compressors = CPLGetCompressors( );
        EXPECT_TRUE( compressors != nullptr );
        EXPECT_TRUE( CSLFindString( compressors, sComp.pszId ) >= 0 );
        for ( auto iter = compressors; *iter; ++iter )
        {
            const auto pCompressor = CPLGetCompressor( *iter );
            EXPECT_TRUE( pCompressor );
            const char* pszOptions = CSLFetchNameValue( pCompressor->papszMetadata, "OPTIONS" );
            if ( pszOptions )
            {
                auto psNode = CPLParseXMLString( pszOptions );
                EXPECT_TRUE( psNode );
                CPLDestroyXMLNode( psNode );
            }
            else
            {
                CPLDebug( "TEST", "Compressor %s has no OPTIONS", *iter );
            }
        }
        CSLDestroy( compressors );

        EXPECT_TRUE( CPLGetCompressor( "invalid" ) == nullptr );
        const auto pCompressor = CPLGetCompressor( sComp.pszId );
        EXPECT_TRUE( pCompressor );
        EXPECT_EQ( std::string( pCompressor->pszId ), std::string( sComp.pszId ) );
        EXPECT_EQ( CSLCount( pCompressor->papszMetadata ), CSLCount( sComp.papszMetadata ) );
        EXPECT_TRUE( pCompressor->pfnFunc != nullptr );
        EXPECT_EQ( pCompressor->user_data, sComp.user_data );

        CPLDestroyCompressorRegistry( );
        EXPECT_TRUE( CPLGetDecompressor( sComp.pszId ) == nullptr );
    }

    TEST( CPL, CPLBuiltinCompressorsTest )
    {
        for ( const char* id : { "blosc", "zlib", "gzip", "lzma", "zstd", "lz4" } )
        {
            const auto pCompressor = CPLGetCompressor( id );
            if ( pCompressor == nullptr )
            {
                CPLDebug( "TEST", "%s not available", id );
                if ( strcmp( id, "zlib" ) == 0 || strcmp( id, "gzip" ) == 0 )
                {
                    EXPECT_TRUE( false );
                }
                continue;
            }
            CPLDebug( "TEST", "Testing %s", id );

            const char my_str[] = "my string to compress";
            const char* const options[] = { "TYPESIZE=1", nullptr };

            // Compressor side

            // Just get output size
            size_t out_size = 0;
            EXPECT_TRUE( pCompressor->pfnFunc( my_str, strlen( my_str ),
                nullptr, &out_size,
                options, pCompressor->user_data ) );
            EXPECT_TRUE( out_size != 0 );

            // Let it alloc the output buffer
            void* out_buffer2 = nullptr;
            size_t out_size2 = 0;
            EXPECT_TRUE( pCompressor->pfnFunc( my_str, strlen( my_str ),
                &out_buffer2, &out_size2,
                options, pCompressor->user_data ) );
            EXPECT_TRUE( out_buffer2 != nullptr );
            EXPECT_TRUE( out_size2 != 0 );
            EXPECT_TRUE( out_size2 <= out_size );

            std::vector<GByte> out_buffer3( out_size );

            // Provide not large enough buffer size
            size_t out_size3 = 1;
            void* out_buffer3_ptr = &out_buffer3[0];
            EXPECT_TRUE( !( pCompressor->pfnFunc( my_str, strlen( my_str ),
                &out_buffer3_ptr, &out_size3,
                options, pCompressor->user_data ) ) );

            // Provide the output buffer
            out_size3 = out_buffer3.size( );
            out_buffer3_ptr = &out_buffer3[0];
            EXPECT_TRUE( pCompressor->pfnFunc( my_str, strlen( my_str ),
                &out_buffer3_ptr, &out_size3,
                options, pCompressor->user_data ) );
            EXPECT_TRUE( out_buffer3_ptr != nullptr );
            EXPECT_TRUE( out_buffer3_ptr == &out_buffer3[0] );
            EXPECT_TRUE( out_size3 != 0 );
            EXPECT_EQ( out_size3, out_size2 );

            out_buffer3.resize( out_size3 );
            out_buffer3_ptr = &out_buffer3[0];

            EXPECT_TRUE( memcmp( out_buffer3_ptr, out_buffer2, out_size2 ) == 0 );

            CPLFree( out_buffer2 );

            const std::vector<GByte> compressedData( out_buffer3 );

            // Decompressor side
            const auto pDecompressor = CPLGetDecompressor( id );
            EXPECT_TRUE( pDecompressor != nullptr );

            out_size = 0;
            EXPECT_TRUE( pDecompressor->pfnFunc( compressedData.data( ), compressedData.size( ),
                nullptr, &out_size,
                nullptr, pDecompressor->user_data ) );
            EXPECT_TRUE( out_size != 0 );
            EXPECT_TRUE( out_size >= strlen( my_str ) );

            out_buffer2 = nullptr;
            out_size2 = 0;
            EXPECT_TRUE( pDecompressor->pfnFunc( compressedData.data( ), compressedData.size( ),
                &out_buffer2, &out_size2,
                options, pDecompressor->user_data ) );
            EXPECT_TRUE( out_buffer2 != nullptr );
            EXPECT_TRUE( out_size2 != 0 );
            EXPECT_EQ( out_size2, strlen( my_str ) );
            EXPECT_TRUE( memcmp( out_buffer2, my_str, strlen( my_str ) ) == 0 );
            CPLFree( out_buffer2 );

            out_buffer3.clear( );
            out_buffer3.resize( out_size );
            out_size3 = out_buffer3.size( );
            out_buffer3_ptr = &out_buffer3[0];
            EXPECT_TRUE( pDecompressor->pfnFunc( compressedData.data( ), compressedData.size( ),
                &out_buffer3_ptr, &out_size3,
                options, pDecompressor->user_data ) );
            EXPECT_TRUE( out_buffer3_ptr != nullptr );
            EXPECT_TRUE( out_buffer3_ptr == &out_buffer3[0] );
            EXPECT_EQ( out_size3, strlen( my_str ) );
            EXPECT_TRUE( memcmp( out_buffer3.data( ), my_str, strlen( my_str ) ) == 0 );
        }
    }

    template<class T> struct TesterDelta
    {
        static void test( const char* dtypeOption )
        {
            const auto pCompressor = CPLGetCompressor( "delta" );
            EXPECT_TRUE( pCompressor );
            const auto pDecompressor = CPLGetDecompressor( "delta" );
            EXPECT_TRUE( pDecompressor );

            const T tabIn[] = { static_cast<T>( -2 ), 3, 1 };
            T tabCompress[3];
            T tabOut[3];
            const char* const apszOptions[] = { dtypeOption, nullptr };

            void* outPtr = &tabCompress[0];
            size_t outSize = sizeof( tabCompress );
            EXPECT_TRUE( pCompressor->pfnFunc( &tabIn[0], sizeof( tabIn ),
                &outPtr, &outSize,
                apszOptions, pCompressor->user_data ) );
            EXPECT_EQ( outSize, sizeof( tabCompress ) );

            outPtr = &tabOut[0];
            outSize = sizeof( tabOut );
            EXPECT_TRUE( pDecompressor->pfnFunc( &tabCompress[0], sizeof( tabCompress ),
                &outPtr, &outSize,
                apszOptions, pDecompressor->user_data ) );
            EXPECT_EQ( outSize, sizeof( tabOut ) );
            EXPECT_EQ( tabOut[0], tabIn[0] );
            EXPECT_EQ( tabOut[1], tabIn[1] );
            EXPECT_EQ( tabOut[2], tabIn[2] );
        }
    };

    TEST( CPL, CPLDeltaCompressorTest )
    {
        TesterDelta<int8_t>::test( "DTYPE=i1" );

        TesterDelta<uint8_t>::test( "DTYPE=u1" );

        TesterDelta<int16_t>::test( "DTYPE=i2" );
        TesterDelta<int16_t>::test( "DTYPE=<i2" );
        TesterDelta<int16_t>::test( "DTYPE=>i2" );

        TesterDelta<uint16_t>::test( "DTYPE=u2" );
        TesterDelta<uint16_t>::test( "DTYPE=<u2" );
        TesterDelta<uint16_t>::test( "DTYPE=>u2" );

        TesterDelta<int32_t>::test( "DTYPE=i4" );
        TesterDelta<int32_t>::test( "DTYPE=<i4" );
        TesterDelta<int32_t>::test( "DTYPE=>i4" );

        TesterDelta<uint32_t>::test( "DTYPE=u4" );
        TesterDelta<uint32_t>::test( "DTYPE=<u4" );
        TesterDelta<uint32_t>::test( "DTYPE=>u4" );

        TesterDelta<int64_t>::test( "DTYPE=i8" );
        TesterDelta<int64_t>::test( "DTYPE=<i8" );
        TesterDelta<int64_t>::test( "DTYPE=>i8" );

        TesterDelta<uint64_t>::test( "DTYPE=u8" );
        TesterDelta<uint64_t>::test( "DTYPE=<u8" );
        TesterDelta<uint64_t>::test( "DTYPE=>u8" );

        TesterDelta<float>::test( "DTYPE=f4" );
#ifdef CPL_MSB
        TesterDelta<float>::test( "DTYPE=>f4" );
#else
        TesterDelta<float>::test( "DTYPE=<f4" );
#endif

        TesterDelta<double>::test( "DTYPE=f8" );
#ifdef CPL_MSB
        TesterDelta<double>::test( "DTYPE=>f8" );
#else
        TesterDelta<double>::test( "DTYPE=<f8" );
#endif

    }

    TEST( CPL, CPLQuadTreeTest )
    {
        unsigned next = 0;

        const auto DummyRandInit = [&next]( unsigned initValue )
        {
            next = initValue;
        };

        constexpr int MAX_RAND_VAL = 32767;

        // Slightly improved version of https://xkcd.com/221/, as suggested by
        // "man srand"
        const auto DummyRand = [&]( )
        {
            next = next * 1103515245 + 12345;
            return( (unsigned)( next / 65536 ) % ( MAX_RAND_VAL + 1 ) );
        };

        CPLRectObj globalbounds;
        globalbounds.minx = 0;
        globalbounds.miny = 0;
        globalbounds.maxx = 1;
        globalbounds.maxy = 1;

        auto hTree = CPLQuadTreeCreate( &globalbounds, nullptr );
        EXPECT_TRUE( hTree != nullptr );

        const auto GenerateRandomRect = [&]( CPLRectObj& rect )
        {
            rect.minx = double( DummyRand( ) ) / MAX_RAND_VAL;
            rect.miny = double( DummyRand( ) ) / MAX_RAND_VAL;
            rect.maxx = rect.minx + double( DummyRand( ) ) / MAX_RAND_VAL * ( 1 - rect.minx );
            rect.maxy = rect.miny + double( DummyRand( ) ) / MAX_RAND_VAL * ( 1 - rect.miny );
        };

        for ( int j = 0; j < 2; j++ )
        {
            DummyRandInit( j );
            for ( int i = 0; i < 1000; i++ )
            {
                CPLRectObj rect;
                GenerateRandomRect( rect );
                void* hFeature = reinterpret_cast<void*>( static_cast<uintptr_t>( i ) );
                CPLQuadTreeInsertWithBounds( hTree, hFeature, &rect );
            }

            {
                int nFeatureCount = 0;
                CPLFree( CPLQuadTreeSearch( hTree, &globalbounds, &nFeatureCount ) );
                EXPECT_EQ( nFeatureCount, 1000 );
            }

            DummyRandInit( j );
            for ( int i = 0; i < 1000; i++ )
            {
                CPLRectObj rect;
                GenerateRandomRect( rect );
                void* hFeature = reinterpret_cast<void*>( static_cast<uintptr_t>( i ) );
                CPLQuadTreeRemove( hTree, hFeature, &rect );
            }

            {
                int nFeatureCount = 0;
                CPLFree( CPLQuadTreeSearch( hTree, &globalbounds, &nFeatureCount ) );
                EXPECT_EQ( nFeatureCount, 0 );
            }
        }

        CPLQuadTreeDestroy( hTree );
    }

    TEST( CPL, UnlinkAndSizeTest )
    {
        VSILFILE* fp = VSIFOpenL( "/vsimem/test_unlink_and_seize.tif", "wb" );
        VSIFWriteL( "test", 5, 1, fp );
        GByte* pRawData = VSIGetMemFileBuffer( "/vsimem/test_unlink_and_seize.tif", nullptr, true );
        EXPECT_TRUE( EQUAL( reinterpret_cast<const char*>( pRawData ), "test" ) );
        EXPECT_TRUE( VSIGetMemFileBuffer( "/vsimem/test_unlink_and_seize.tif", nullptr, false ) == nullptr );
        EXPECT_TRUE( VSIFOpenL( "/vsimem/test_unlink_and_seize.tif", "r" ) == nullptr );
        EXPECT_TRUE( VSIFReadL( pRawData, 5, 1, fp ) == 0 );
        EXPECT_TRUE( VSIFWriteL( pRawData, 5, 1, fp ) == 0 );
        EXPECT_TRUE( VSIFSeekL( fp, 0, SEEK_END ) == 0 );
        CPLFree( pRawData );
        VSIFCloseL( fp );
    }


}
