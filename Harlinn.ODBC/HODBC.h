#pragma once
#ifndef __HODBC_H__
#define __HODBC_H__
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

#include <HODBCDef.h>
#include <HCCGuid.h>
#include <HCCDateTime.h>
#include <HCCString.h>
#include <HCCCurrency.h>
#include <HCCConcepts.h>

namespace Harlinn::ODBC
{
    class Environment;
    class Connection;
    class Statement;
    class Descriptor;
    class DataReader;

    namespace MsSql
    {
        constexpr const char SQLODBC_PRODUCT_NAME_FULL_VER_ANSI[ ] = "Microsoft ODBC Driver 11 for SQL Server";
        constexpr const char SQLODBC_PRODUCT_NAME_FULL_ANSI[ ] = "Microsoft ODBC Driver for SQL Server";
        constexpr const char SQLODBC_PRODUCT_NAME_SHORT_VER_ANSI[ ] = "ODBC Driver 11 for SQL Server";

        constexpr const char SQLODBC_PRODUCT_NAME_SHORT_ANSI[ ] = "ODBC Driver for SQL Server";

        constexpr const char SQLODBC_FILE_NAME_ANSI[ ] = "msodbcsql";
        constexpr const char SQLODBC_FILE_NAME_VER_ANSI[ ] = "msodbcsql11";
        constexpr const char SQLODBC_FILE_NAME_FULL_ANSI[ ] = "msodbcsql11.dll";

        constexpr const wchar_t SQLODBC_PRODUCT_NAME_FULL_VER_UNICODE[ ] = L"Microsoft ODBC Driver 11 for SQL Server";
        constexpr const wchar_t SQLODBC_PRODUCT_NAME_FULL_UNICODE[ ] = L"Microsoft ODBC Driver for SQL Server";
        constexpr const wchar_t SQLODBC_PRODUCT_NAME_SHORT_VER_UNICODE[ ] = L"ODBC Driver 11 for SQL Server";

        constexpr const wchar_t SQLODBC_PRODUCT_NAME_SHORT_UNICODE[ ] = L"ODBC Driver for SQL Server";

        constexpr const wchar_t SQLODBC_FILE_NAME_UNICODE[ ] = L"msodbcsql";
        constexpr const wchar_t SQLODBC_FILE_NAME_VER_UNICODE[ ] = L"msodbcsql11";
        constexpr const wchar_t SQLODBC_FILE_NAME_FULL_UNICODE[ ] = L"msodbcsql11.dll";

        // define the character type agnostic constants
#if defined(_UNICODE) || defined(UNICODE)

        constexpr const wchar_t* SQLODBC_PRODUCT_NAME_FULL_VER = SQLODBC_PRODUCT_NAME_FULL_VER_UNICODE;
        constexpr const wchar_t* SQLODBC_PRODUCT_NAME_FULL = SQLODBC_PRODUCT_NAME_FULL_UNICODE;
        constexpr const wchar_t* SQLODBC_PRODUCT_NAME_SHORT_VER = SQLODBC_PRODUCT_NAME_SHORT_VER_UNICODE;
        constexpr const wchar_t* SQLODBC_PRODUCT_NAME_SHORT = SQLODBC_PRODUCT_NAME_SHORT_UNICODE;

        constexpr const wchar_t* SQLODBC_FILE_NAME = SQLODBC_FILE_NAME_UNICODE;
        constexpr const wchar_t* SQLODBC_FILE_NAME_VER = SQLODBC_FILE_NAME_VER_UNICODE;
        constexpr const wchar_t* SQLODBC_FILE_NAME_FULL = SQLODBC_FILE_NAME_FULL_UNICODE;

#else   // _UNICODE || UNICODE

        constexpr const char* SQLODBC_PRODUCT_NAME_FULL_VER = SQLODBC_PRODUCT_NAME_FULL_VER_ANSI;
        constexpr const char* SQLODBC_PRODUCT_NAME_FULL = SQLODBC_PRODUCT_NAME_FULL_ANSI;
        constexpr const char* SQLODBC_PRODUCT_NAME_SHORT_VER = SQLODBC_PRODUCT_NAME_SHORT_VER_ANSI;
        constexpr const char* SQLODBC_PRODUCT_NAME_SHORT = SQLODBC_PRODUCT_NAME_SHORT_ANSI;

        constexpr const char* SQLODBC_FILE_NAME = SQLODBC_FILE_NAME_ANSI;
        constexpr const char* SQLODBC_FILE_NAME_VER = SQLODBC_FILE_NAME_VER_ANSI;
        constexpr const char* SQLODBC_FILE_NAME_FULL = SQLODBC_FILE_NAME_FULL_ANSI;

#endif  // _UNICODE || UNICODE

        constexpr auto SQLODBC_DRIVER_NAME = SQLODBC_PRODUCT_NAME_SHORT_VER;

#if !defined(SQLNCLI_VER)
 #define SQLNCLI_VER 1100
#endif
#if SQLNCLI_VER >= 1100

        constexpr char SQLNCLI_PRODUCT_NAME_FULL_VER_ANSI[ ] = "Microsoft SQL Server Native Client 11.0";
        constexpr char SQLNCLI_PRODUCT_NAME_FULL_ANSI[ ] = "Microsoft SQL Server Native Client";
        constexpr char SQLNCLI_PRODUCT_NAME_SHORT_VER_ANSI[ ] = "SQL Server Native Client 11.0";
        constexpr char SQLNCLI_PRODUCT_NAME_SHORT_ANSI[ ] = "SQL Server Native Client";

        constexpr char SQLNCLI_FILE_NAME_ANSI[ ] = "sqlncli";
        constexpr char SQLNCLI_FILE_NAME_VER_ANSI[ ] = "sqlncli11";
        constexpr char SQLNCLI_FILE_NAME_FULL_ANSI[ ] = "sqlncli11.dll";

        constexpr wchar_t SQLNCLI_PRODUCT_NAME_FULL_VER_UNICODE[ ] = L"Microsoft SQL Server Native Client 11.0";
        constexpr wchar_t SQLNCLI_PRODUCT_NAME_FULL_UNICODE[ ] = L"Microsoft SQL Server Native Client";
        constexpr wchar_t SQLNCLI_PRODUCT_NAME_SHORT_VER_UNICODE[ ] = L"SQL Server Native Client 11.0";
        constexpr wchar_t SQLNCLI_PRODUCT_NAME_SHORT_UNICODE[ ] = L"SQL Server Native Client";

        constexpr wchar_t SQLNCLI_FILE_NAME_UNICODE[ ] = L"sqlncli";
        constexpr wchar_t SQLNCLI_FILE_NAME_VER_UNICODE[ ] = L"sqlncli11";
        constexpr wchar_t SQLNCLI_FILE_NAME_FULL_UNICODE[ ] = L"sqlncli11.dll";

#elif SQLNCLI_VER >= 1000

        constexpr char SQLNCLI_PRODUCT_NAME_FULL_VER_ANSI[ ] = "Microsoft SQL Server Native Client 10.0";
        constexpr char SQLNCLI_PRODUCT_NAME_FULL_ANSI[ ] = "Microsoft SQL Server Native Client";
        constexpr char SQLNCLI_PRODUCT_NAME_SHORT_VER_ANSI[ ] = "SQL Server Native Client 10.0";
        constexpr char SQLNCLI_PRODUCT_NAME_SHORT_ANSI[ ] = "SQL Server Native Client";

        constexpr char SQLNCLI_FILE_NAME_ANSI[ ] = "sqlncli";
        constexpr char SQLNCLI_FILE_NAME_VER_ANSI[ ] = "sqlncli10";
        constexpr char SQLNCLI_FILE_NAME_FULL_ANSI[ ] = "sqlncli10.dll";

        constexpr wchar_t SQLNCLI_PRODUCT_NAME_FULL_VER_UNICODE[ ] = L"Microsoft SQL Server Native Client 10.0";
        constexpr wchar_t SQLNCLI_PRODUCT_NAME_FULL_UNICODE[ ] = L"Microsoft SQL Server Native Client";
        constexpr wchar_t SQLNCLI_PRODUCT_NAME_SHORT_VER_UNICODE[ ] = L"SQL Server Native Client 10.0";
        constexpr wchar_t SQLNCLI_PRODUCT_NAME_SHORT_UNICODE[ ] = L"SQL Server Native Client";

        constexpr wchar_t SQLNCLI_FILE_NAME_UNICODE[ ] = L"sqlncli";
        constexpr wchar_t SQLNCLI_FILE_NAME_VER_UNICODE[ ] = L"sqlncli10";
        constexpr wchar_t SQLNCLI_FILE_NAME_FULL_UNICODE[ ] = L"sqlncli10.dll";

#else

        constexpr char SQLNCLI_PRODUCT_NAME_FULL_VER_ANSI[ ] = "Microsoft SQL Server Native Client";
        constexpr char SQLNCLI_PRODUCT_NAME_FULL_ANSI[ ] = "Microsoft SQL Server Native Client";
        constexpr char SQLNCLI_PRODUCT_NAME_SHORT_VER_ANSI[ ] = "SQL Native Client";
        constexpr char SQLNCLI_PRODUCT_NAME_SHORT_ANSI[ ] = "SQL Native Client";

        constexpr char SQLNCLI_FILE_NAME_ANSI[ ] = "sqlncli";
        constexpr char SQLNCLI_FILE_NAME_VER_ANSI[ ] = "sqlncli";
        constexpr char SQLNCLI_FILE_NAME_FULL_ANSI[ ] = "sqlncli.dll";

        constexpr wchar_t SQLNCLI_PRODUCT_NAME_FULL_VER_UNICODE[ ] = L"Microsoft SQL Server Native Client";
        constexpr wchar_t SQLNCLI_PRODUCT_NAME_FULL_UNICODE[ ] = L"Microsoft SQL Server Native Client";
        constexpr wchar_t SQLNCLI_PRODUCT_NAME_SHORT_VER_UNICODE[ ] = L"SQL Native Client";
        constexpr wchar_t SQLNCLI_PRODUCT_NAME_SHORT_UNICODE[ ] = L"SQL Native Client";

        constexpr wchar_t SQLNCLI_FILE_NAME_UNICODE[ ] = L"sqlncli";
        constexpr wchar_t SQLNCLI_FILE_NAME_VER_UNICODE[ ] = L"sqlncli";
        constexpr wchar_t SQLNCLI_FILE_NAME_FULL_UNICODE[ ] = L"sqlncli.dll";

#endif  // SQLNCLI_VER >= 1100

#if defined(_UNICODE) || defined(UNICODE)

        constexpr const wchar_t* SQLNCLI_PRODUCT_NAME_FULL_VER = SQLNCLI_PRODUCT_NAME_FULL_VER_UNICODE;
        constexpr const wchar_t* SQLNCLI_PRODUCT_NAME_FULL = SQLNCLI_PRODUCT_NAME_FULL_UNICODE;
        constexpr const wchar_t* SQLNCLI_PRODUCT_NAME_SHORT_VER = SQLNCLI_PRODUCT_NAME_SHORT_VER_UNICODE;
        constexpr const wchar_t* SQLNCLI_PRODUCT_NAME_SHORT = SQLNCLI_PRODUCT_NAME_SHORT_UNICODE;

        constexpr const wchar_t* SQLNCLI_FILE_NAME = SQLNCLI_FILE_NAME_UNICODE;
        constexpr const wchar_t* SQLNCLI_FILE_NAME_VER = SQLNCLI_FILE_NAME_VER_UNICODE;
        constexpr const wchar_t* SQLNCLI_FILE_NAME_FULL = SQLNCLI_FILE_NAME_FULL_UNICODE;


#else   // _UNICODE || UNICODE

        constexpr const char* SQLNCLI_PRODUCT_NAME_FULL_VER = SQLNCLI_PRODUCT_NAME_FULL_VER_ANSI;
        constexpr const char* SQLNCLI_PRODUCT_NAME_FULL = SQLNCLI_PRODUCT_NAME_FULL_ANSI;
        constexpr const char* SQLNCLI_PRODUCT_NAME_SHORT_VER = SQLNCLI_PRODUCT_NAME_SHORT_VER_ANSI;
        constexpr const char* SQLNCLI_PRODUCT_NAME_SHORT = SQLNCLI_PRODUCT_NAME_SHORT_ANSI;

        constexpr const char* SQLNCLI_FILE_NAME = SQLNCLI_FILE_NAME_ANSI;
        constexpr const char* SQLNCLI_FILE_NAME_VER = SQLNCLI_FILE_NAME_VER_ANSI;
        constexpr const char* SQLNCLI_FILE_NAME_FULL = SQLNCLI_FILE_NAME_FULL_ANSI;

#endif  // _UNICODE || UNICODE
        
        constexpr const auto SQLNCLI_DRIVER_NAME = SQLNCLI_PRODUCT_NAME_SHORT_VER;

        // max SQL Server identifier length
        constexpr const UInt32 SQL_MAX_SQLSERVERNAME = 128;


        // SQLSetConnectAttr driver specific defines.
        // Microsoft has 1200 thru 1249 reserved for Microsoft SQL Server Native Client driver usage.
        // Connection attributes
        constexpr const SQLINTEGER SQL_COPT_SS_BASE = 1200;
        /// <summary>
        /// dbrpwset SQLSetConnectOption only
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_REMOTE_PWD = ( SQL_COPT_SS_BASE + 1 ); 
        /// <summary>
        // Use create proc for SQLPrepare
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_USE_PROC_FOR_PREP = ( SQL_COPT_SS_BASE + 2 ); 
        /// <summary>
        /// Force integrated security on login
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_INTEGRATED_SECURITY = ( SQL_COPT_SS_BASE + 3 ); 
        /// <summary>
        /// Preserve server cursors after SQLTransact
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_PRESERVE_CURSORS = ( SQL_COPT_SS_BASE + 4 ); 
        /// <summary>
        /// dbgetuserdata/dbsetuserdata
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_USER_DATA = ( SQL_COPT_SS_BASE + 5 ); 
        /// <summary>
        /// Enlist in a DTC transaction
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_ENLIST_IN_DTC = SQL_ATTR_ENLIST_IN_DTC; 
        /// <summary>
        /// Enlist in a XA transaction
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_ENLIST_IN_XA = SQL_ATTR_ENLIST_IN_XA; 
        /// <summary>
        /// Enables FallBack connections
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_FALLBACK_CONNECT = ( SQL_COPT_SS_BASE + 10 ); 
        /// <summary>
        /// Used to access SQL Server ODBC driver performance data
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_PERF_DATA = (SQL_COPT_SS_BASE+11); 
        /// <summary>
        /// Used to set the logfile name for the Performance data
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_PERF_DATA_LOG = (SQL_COPT_SS_BASE+12); 
        /// <summary>
        /// Used to set the query logging threshold in milliseconds.
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_PERF_QUERY_INTERVAL = (SQL_COPT_SS_BASE+13); 
        /// <summary>
        /// Used to set the logfile name for saving queryies.
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_PERF_QUERY_LOG = (SQL_COPT_SS_BASE+14); 
        /// <summary>
        /// Used to start and stop query logging.
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_PERF_QUERY = (SQL_COPT_SS_BASE+15); 
        /// <summary>
        /// Used to make a statistics log entry to disk.
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_PERF_DATA_LOG_NOW = (SQL_COPT_SS_BASE+16); 
        /// <summary>
        /// Enable/Disable Quoted Identifiers
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_QUOTED_IDENT = (SQL_COPT_SS_BASE+17); 
        /// <summary>
        /// Enable/Disable ANSI NULL, Padding and Warnings
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_ANSI_NPW = (SQL_COPT_SS_BASE+18); 
        /// <summary>
        /// Allow BCP usage on connection
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_BCP = (SQL_COPT_SS_BASE+19); 
        /// <summary>
        /// Perform code page translation
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_TRANSLATE = (SQL_COPT_SS_BASE+20); 
        /// <summary>
        /// File name to be attached as a database
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_ATTACHDBFILENAME = (SQL_COPT_SS_BASE+21); 
        /// <summary>
        /// Enable/Disable CONCAT_NULL_YIELDS_NULL
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_CONCAT_NULL = (SQL_COPT_SS_BASE+22); 
        /// <summary>
        /// Allow strong encryption for data
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_ENCRYPT = (SQL_COPT_SS_BASE+23); 
        /// <summary>
        /// Multiple active result set per connection
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_MARS_ENABLED = (SQL_COPT_SS_BASE+24); 
        /// <summary>
        /// Failover partner server
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_FAILOVER_PARTNER = (SQL_COPT_SS_BASE+25); 
        /// <summary>
        /// Old Password, used when changing password during login
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_OLDPWD = (SQL_COPT_SS_BASE+26); 
        /// <summary>
        /// Used to set/get any driver-specific or ODBC-defined TXN iso level
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_TXN_ISOLATION = (SQL_COPT_SS_BASE+27); 
        /// <summary>
        /// Trust server certificate
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_TRUST_SERVER_CERTIFICATE = (SQL_COPT_SS_BASE+28); 
        /// <summary>
        /// Server SPN
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_SERVER_SPN = (SQL_COPT_SS_BASE+29); 
        /// <summary>
        /// Failover partner server SPN
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_FAILOVER_PARTNER_SPN = (SQL_COPT_SS_BASE+30); 
        /// <summary>
        /// The integrated authentication method used for the connection
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_INTEGRATED_AUTHENTICATION_METHOD = (SQL_COPT_SS_BASE+31); 
        /// <summary>
        /// Used to decide if the connection is mutually authenticated
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_MUTUALLY_AUTHENTICATED = (SQL_COPT_SS_BASE+32); 
        /// <summary>
        /// Post connection attribute used to get the ConnectionID
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_CLIENT_CONNECTION_ID = (SQL_COPT_SS_BASE+33); 

        // Define old names
        constexpr const SQLINTEGER SQL_REMOTE_PWD = SQL_COPT_SS_REMOTE_PWD;
        constexpr const SQLINTEGER SQL_USE_PROCEDURE_FOR_PREPARE = SQL_COPT_SS_USE_PROC_FOR_PREP;
        constexpr const SQLINTEGER SQL_INTEGRATED_SECURITY = SQL_COPT_SS_INTEGRATED_SECURITY;
        constexpr const SQLINTEGER SQL_PRESERVE_CURSORS = SQL_COPT_SS_PRESERVE_CURSORS;


        // SQLSetStmtAttr SQL Server Native Client driver specific defines.
        // Statement attributes
        constexpr const SQLINTEGER SQL_SOPT_SS_BASE = 1225;
        /// <summary>
        /// Text pointer logging
        /// </summary>
        constexpr const SQLINTEGER SQL_SOPT_SS_TEXTPTR_LOGGING = (SQL_SOPT_SS_BASE+0); 
        /// <summary>
        /// dbcurcmd SQLGetStmtOption only
        /// </summary>
        constexpr const SQLINTEGER SQL_SOPT_SS_CURRENT_COMMAND = (SQL_SOPT_SS_BASE+1);
        /// <summary>
        /// Expose FOR BROWSE hidden columns
        /// </summary>
        constexpr const SQLINTEGER SQL_SOPT_SS_HIDDEN_COLUMNS = (SQL_SOPT_SS_BASE+2);
        /// <summary>
        /// Set NOBROWSETABLE option
        /// </summary>
        constexpr const SQLINTEGER SQL_SOPT_SS_NOBROWSETABLE = (SQL_SOPT_SS_BASE+3); 
        /// <summary>
        /// Regionalize output character conversions
        /// </summary>
        constexpr const SQLINTEGER SQL_SOPT_SS_REGIONALIZE = (SQL_SOPT_SS_BASE+4); 
        /// <summary>
        /// Server cursor options
        /// </summary>
        constexpr const SQLINTEGER SQL_SOPT_SS_CURSOR_OPTIONS = (SQL_SOPT_SS_BASE+5);
        /// <summary>
        /// Real vs. Not Real row count indicator
        /// </summary>
        constexpr const SQLINTEGER SQL_SOPT_SS_NOCOUNT_STATUS = (SQL_SOPT_SS_BASE+6);
        /// <summary>
        /// Defer prepare until necessary
        /// </summary>
        constexpr const SQLINTEGER SQL_SOPT_SS_DEFER_PREPARE = (SQL_SOPT_SS_BASE+7); 
        /// <summary>
        /// Notification timeout
        /// </summary>
        constexpr const SQLINTEGER SQL_SOPT_SS_QUERYNOTIFICATION_TIMEOUT = (SQL_SOPT_SS_BASE+8); 
        /// <summary>
        /// Notification message text
        /// </summary>
        constexpr const SQLINTEGER SQL_SOPT_SS_QUERYNOTIFICATION_MSGTEXT = (SQL_SOPT_SS_BASE+9); 
        /// <summary>
        /// SQL service broker name
        /// </summary>
        constexpr const SQLINTEGER SQL_SOPT_SS_QUERYNOTIFICATION_OPTIONS = (SQL_SOPT_SS_BASE+10);
        /// <summary>
        /// Direct subsequent calls to parameter related methods to set properties on constituent columns/parameters of container types
        /// </summary>
        constexpr const SQLINTEGER SQL_SOPT_SS_PARAM_FOCUS = (SQL_SOPT_SS_BASE+11);
        /// <summary>
        /// Sets name scope for subsequent catalog function calls
        /// </summary>
        constexpr const SQLINTEGER SQL_SOPT_SS_NAME_SCOPE = (SQL_SOPT_SS_BASE+12);
        constexpr const SQLINTEGER SQL_SOPT_SS_MAX_USED = SQL_SOPT_SS_NAME_SCOPE;
        // Define old names
        constexpr const SQLINTEGER SQL_TEXTPTR_LOGGING = SQL_SOPT_SS_TEXTPTR_LOGGING;

        constexpr const SQLINTEGER SQL_COPT_SS_BASE_EX = 1240;
        /// <summary>
        /// Browse connect mode of operation
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_BROWSE_CONNECT = (SQL_COPT_SS_BASE_EX+1); 
        /// <summary>
        /// Single Server browse request.
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_BROWSE_SERVER = (SQL_COPT_SS_BASE_EX+2); 
        /// <summary>
        /// Issues warning when data from the server had a loss during code page conversion.
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_WARN_ON_CP_ERROR = (SQL_COPT_SS_BASE_EX+3);
        /// <summary>
        /// dbdead SQLGetConnectOption only. It will try to ping the server. Expensive connection check
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_CONNECTION_DEAD = (SQL_COPT_SS_BASE_EX+4); 
        /// <summary>
        /// Determines if we should cache browse info. Used when returned buffer is greater then ODBC limit (32K)
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_BROWSE_CACHE_DATA = (SQL_COPT_SS_BASE_EX+5);
        /// <summary>
        /// When this option is set, we will perform connection reset on next packet
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_RESET_CONNECTION = (SQL_COPT_SS_BASE_EX+6); 
        /// <summary>
        /// Application Intent
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_APPLICATION_INTENT = (SQL_COPT_SS_BASE_EX+7); 
        /// <summary>
        /// Multi-subnet Failover
        /// </summary>
        constexpr const SQLINTEGER SQL_COPT_SS_MULTISUBNET_FAILOVER = (SQL_COPT_SS_BASE_EX+8); 
        constexpr const SQLINTEGER SQL_COPT_SS_EX_MAX_USED = SQL_COPT_SS_MULTISUBNET_FAILOVER;

        // SQLColAttributes driver specific defines.
        // SQLSetDescField/SQLGetDescField driver specific defines.
        // Microsoft has 1200 thru 1249 reserved for Microsoft SQL Server Native Client driver usage.
        constexpr const SQLINTEGER SQL_CA_SS_BASE = 1200;
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_SSTYPE = (SQL_CA_SS_BASE+0);   //  dbcoltype/dbalttype
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_UTYPE = (SQL_CA_SS_BASE+1);   //  dbcolutype/dbaltutype
        constexpr const SQLINTEGER SQL_CA_SS_NUM_ORDERS = (SQL_CA_SS_BASE+2);   //  dbnumorders
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_ORDER = (SQL_CA_SS_BASE+3);   //  dbordercol
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_VARYLEN = (SQL_CA_SS_BASE+4);   //  dbvarylen
        constexpr const SQLINTEGER SQL_CA_SS_NUM_COMPUTES = (SQL_CA_SS_BASE+5);   //  dbnumcompute
        constexpr const SQLINTEGER SQL_CA_SS_COMPUTE_ID = (SQL_CA_SS_BASE+6);   //  dbnextrow status return
        constexpr const SQLINTEGER SQL_CA_SS_COMPUTE_BYLIST = (SQL_CA_SS_BASE+7);   //  dbbylist
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_ID = (SQL_CA_SS_BASE+8);   //  dbaltcolid
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_OP = (SQL_CA_SS_BASE+9);   //  dbaltop
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_SIZE = (SQL_CA_SS_BASE+10);  //  dbcollen
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_HIDDEN = (SQL_CA_SS_BASE+11);  //  Column is hidden (FOR BROWSE)
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_KEY = (SQL_CA_SS_BASE+12);  //  Column is key column (FOR BROWSE)
        
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_COLLATION = (SQL_CA_SS_BASE+14);  //  Column collation (only for chars)
        constexpr const SQLINTEGER SQL_CA_SS_VARIANT_TYPE = (SQL_CA_SS_BASE+15);
        constexpr const SQLINTEGER SQL_CA_SS_VARIANT_SQL_TYPE = (SQL_CA_SS_BASE+16);
        constexpr const SQLINTEGER SQL_CA_SS_VARIANT_SERVER_TYPE = (SQL_CA_SS_BASE+17);

        // XML, CLR UDT, and table valued parameter related metadata
        constexpr const SQLINTEGER SQL_CA_SS_UDT_CATALOG_NAME = (SQL_CA_SS_BASE+18); //  UDT catalog name
        constexpr const SQLINTEGER SQL_CA_SS_UDT_SCHEMA_NAME = (SQL_CA_SS_BASE+19); //  UDT schema name
        constexpr const SQLINTEGER SQL_CA_SS_UDT_TYPE_NAME = (SQL_CA_SS_BASE+20); //  UDT type name
        constexpr const SQLINTEGER SQL_CA_SS_UDT_ASSEMBLY_TYPE_NAME = (SQL_CA_SS_BASE+21); //  Qualified name of the assembly containing the UDT class
        constexpr const SQLINTEGER SQL_CA_SS_XML_SCHEMACOLLECTION_CATALOG_NAME = (SQL_CA_SS_BASE+22); //  Name of the catalog that contains XML Schema collection
        constexpr const SQLINTEGER SQL_CA_SS_XML_SCHEMACOLLECTION_SCHEMA_NAME = (SQL_CA_SS_BASE+23); //  Name of the schema that contains XML Schema collection
        constexpr const SQLINTEGER SQL_CA_SS_XML_SCHEMACOLLECTION_NAME = (SQL_CA_SS_BASE+24); //  Name of the XML Schema collection
        constexpr const SQLINTEGER SQL_CA_SS_CATALOG_NAME = (SQL_CA_SS_BASE+25); //  Catalog name
        constexpr const SQLINTEGER SQL_CA_SS_SCHEMA_NAME = (SQL_CA_SS_BASE+26); //  Schema name
        constexpr const SQLINTEGER SQL_CA_SS_TYPE_NAME = (SQL_CA_SS_BASE+27); //  Type name

        // table valued parameter related metadata
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_COMPUTED = (SQL_CA_SS_BASE+29); //  column is computed
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_IN_UNIQUE_KEY = (SQL_CA_SS_BASE+30); //  column is part of a unique key
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_SORT_ORDER = (SQL_CA_SS_BASE+31); //  column sort order
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_SORT_ORDINAL = (SQL_CA_SS_BASE+32); //  column sort ordinal
        constexpr const SQLINTEGER SQL_CA_SS_COLUMN_HAS_DEFAULT_VALUE = (SQL_CA_SS_BASE+33); //  column has default value for all rows of the table valued parameter

        // sparse column related metadata
        constexpr const SQLINTEGER SQL_CA_SS_IS_COLUMN_SET = ( SQL_CA_SS_BASE + 34 ); //  column is a column-set column for sparse columns

        // Legacy datetime related metadata
        constexpr const SQLINTEGER SQL_CA_SS_SERVER_TYPE = ( SQL_CA_SS_BASE + 35 ); //  column type to send on the wire for datetime types

        constexpr const SQLINTEGER SQL_CA_SS_MAX_USED = ( SQL_CA_SS_BASE + 36 );

        // Defines returned by SQL_ATTR_CURSOR_TYPE/SQL_CURSOR_TYPE
        constexpr const SQLINTEGER SQL_CURSOR_FAST_FORWARD_ONLY = 8;            //  Only returned by SQLGetStmtAttr/Option
        // Defines for use with SQL_COPT_SS_USE_PROC_FOR_PREP
        constexpr const SQLINTEGER SQL_UP_OFF = 0L;           //  Procedures won't be used for prepare
        constexpr const SQLINTEGER SQL_UP_ON = 1L;           //  Procedures will be used for prepare
        constexpr const SQLINTEGER SQL_UP_ON_DROP = 2L;           //  Temp procedures will be explicitly dropped
        constexpr const SQLINTEGER SQL_UP_DEFAULT = SQL_UP_ON;
        // Defines for use with SQL_COPT_SS_INTEGRATED_SECURITY - Pre-Connect Option only
        constexpr const SQLINTEGER SQL_IS_OFF                          = 0L;           //  Integrated security isn't used
        constexpr const SQLINTEGER SQL_IS_ON                           = 1L;           //  Integrated security is used
        constexpr const SQLINTEGER SQL_IS_DEFAULT                      = SQL_IS_OFF;
        // Defines for use with SQL_COPT_SS_PRESERVE_CURSORS
        constexpr const SQLINTEGER SQL_PC_OFF                          = 0L;           //  Cursors are closed on SQLTransact
        constexpr const SQLINTEGER SQL_PC_ON                           = 1L;           //  Cursors remain open on SQLTransact
        constexpr const SQLINTEGER SQL_PC_DEFAULT                      = SQL_PC_OFF;
        // Defines for use with SQL_COPT_SS_USER_DATA
        constexpr const nullptr_t SQL_UD_NOTSET = nullptr;         //  No user data pointer set
        // Defines for use with SQL_COPT_SS_TRANSLATE
        constexpr const SQLINTEGER SQL_XL_OFF                          = 0L;           //  Code page translation is not performed
        constexpr const SQLINTEGER SQL_XL_ON                           = 1L;           //  Code page translation is performed
        constexpr const SQLINTEGER SQL_XL_DEFAULT                      = SQL_XL_ON;
        // Defines for use with SQL_COPT_SS_FALLBACK_CONNECT - Pre-Connect Option only
        constexpr const SQLINTEGER SQL_FB_OFF                          = 0L;           //  FallBack connections are disabled
        constexpr const SQLINTEGER SQL_FB_ON                           = 1L;           //  FallBack connections are enabled
        constexpr const SQLINTEGER SQL_FB_DEFAULT                      = SQL_FB_OFF;
        // Defines for use with SQL_COPT_SS_BCP - Pre-Connect Option only
        constexpr const SQLINTEGER SQL_BCP_OFF                         = 0L;           //  BCP is not allowed on connection
        constexpr const SQLINTEGER SQL_BCP_ON                          = 1L;           //  BCP is allowed on connection
        constexpr const SQLINTEGER SQL_BCP_DEFAULT                     = SQL_BCP_OFF;
        // Defines for use with SQL_COPT_SS_QUOTED_IDENT
        constexpr const SQLINTEGER SQL_QI_OFF                          = 0L;           //  Quoted identifiers are enable
        constexpr const SQLINTEGER SQL_QI_ON                           = 1L;           //  Quoted identifiers are disabled
        constexpr const SQLINTEGER SQL_QI_DEFAULT                      = SQL_QI_ON;
        // Defines for use with SQL_COPT_SS_ANSI_NPW - Pre-Connect Option only
        constexpr const SQLINTEGER SQL_AD_OFF                          = 0L;           //  ANSI NULLs, Padding and Warnings are enabled
        constexpr const SQLINTEGER SQL_AD_ON                           = 1L;           //  ANSI NULLs, Padding and Warnings are disabled
        constexpr const SQLINTEGER SQL_AD_DEFAULT                      = SQL_AD_ON;
        // Defines for use with SQL_COPT_SS_CONCAT_NULL - Pre-Connect Option only
        constexpr const SQLINTEGER SQL_CN_OFF                          = 0L;           //  CONCAT_NULL_YIELDS_NULL is off
        constexpr const SQLINTEGER SQL_CN_ON                           = 1L;           //  CONCAT_NULL_YIELDS_NULL is on
        constexpr const SQLINTEGER SQL_CN_DEFAULT                      = SQL_CN_ON;
        // Defines for use with SQL_SOPT_SS_TEXTPTR_LOGGING
        constexpr const SQLINTEGER SQL_TL_OFF                          = 0L;           //  No logging on text pointer ops
        constexpr const SQLINTEGER SQL_TL_ON                           = 1L;           //  Logging occurs on text pointer ops
        constexpr const SQLINTEGER SQL_TL_DEFAULT                      = SQL_TL_ON;
        // Defines for use with SQL_SOPT_SS_HIDDEN_COLUMNS
        constexpr const SQLINTEGER SQL_HC_OFF                          = 0L;           //  FOR BROWSE columns are hidden
        constexpr const SQLINTEGER SQL_HC_ON                           = 1L;           //  FOR BROWSE columns are exposed
        constexpr const SQLINTEGER SQL_HC_DEFAULT                      = SQL_HC_OFF;
        // Defines for use with SQL_SOPT_SS_NOBROWSETABLE
        constexpr const SQLINTEGER SQL_NB_OFF                          = 0L;           //  NO_BROWSETABLE is off
        constexpr const SQLINTEGER SQL_NB_ON                           = 1L;           //  NO_BROWSETABLE is on
        constexpr const SQLINTEGER SQL_NB_DEFAULT                      = SQL_NB_OFF;
        // Defines for use with SQL_SOPT_SS_REGIONALIZE
        constexpr const SQLINTEGER SQL_RE_OFF                          = 0L;           //  No regionalization occurs on output character conversions
        constexpr const SQLINTEGER SQL_RE_ON                           = 1L;           //  Regionalization occurs on output character conversions
        constexpr const SQLINTEGER SQL_RE_DEFAULT                      = SQL_RE_OFF;
        // Defines for use with SQL_SOPT_SS_CURSOR_OPTIONS
        constexpr const SQLINTEGER SQL_CO_OFF                          = 0L;           //  Clear all cursor options
        constexpr const SQLINTEGER SQL_CO_FFO                          = 1L;           //  Fast-forward cursor will be used
        constexpr const SQLINTEGER SQL_CO_AF                           = 2L;           //  Autofetch on cursor open
        constexpr const SQLINTEGER SQL_CO_FFO_AF = ( SQL_CO_FFO | SQL_CO_AF );  //  Fast-forward cursor with autofetch
        constexpr const SQLINTEGER SQL_CO_FIREHOSE_AF                  = 4L;           //  Auto fetch on fire-hose cursors
        constexpr const SQLINTEGER SQL_CO_DEFAULT                      = SQL_CO_OFF;
        //SQL_SOPT_SS_NOCOUNT_STATUS 
        constexpr const SQLINTEGER SQL_NC_OFF                          = 0L;
        constexpr const SQLINTEGER SQL_NC_ON                           = 1L;
        //SQL_SOPT_SS_DEFER_PREPARE 
        constexpr const SQLINTEGER SQL_DP_OFF                          = 0L;
        constexpr const SQLINTEGER SQL_DP_ON                           = 1L;
        //SQL_SOPT_SS_NAME_SCOPE
        constexpr const SQLINTEGER SQL_SS_NAME_SCOPE_TABLE             = 0L;
        constexpr const SQLINTEGER SQL_SS_NAME_SCOPE_TABLE_TYPE        = 1L;
        constexpr const SQLINTEGER SQL_SS_NAME_SCOPE_EXTENDED          = 2L;
        constexpr const SQLINTEGER SQL_SS_NAME_SCOPE_SPARSE_COLUMN_SET = 3L;
        constexpr const SQLINTEGER SQL_SS_NAME_SCOPE_DEFAULT           = SQL_SS_NAME_SCOPE_TABLE;
        //SQL_COPT_SS_ENCRYPT 
        constexpr const SQLINTEGER SQL_EN_OFF                          = 0L;
        constexpr const SQLINTEGER SQL_EN_ON                           = 1L;
        //SQL_COPT_SS_TRUST_SERVER_CERTIFICATE
        constexpr const SQLINTEGER SQL_TRUST_SERVER_CERTIFICATE_NO     = 0L;
        constexpr const SQLINTEGER SQL_TRUST_SERVER_CERTIFICATE_YES    = 1L;
        //SQL_COPT_SS_BROWSE_CONNECT 
        constexpr const SQLINTEGER SQL_MORE_INFO_NO                    = 0L;
        constexpr const SQLINTEGER SQL_MORE_INFO_YES                   = 1L;
        //SQL_COPT_SS_BROWSE_CACHE_DATA 
        constexpr const SQLINTEGER SQL_CACHE_DATA_NO                   = 0L;
        constexpr const SQLINTEGER SQL_CACHE_DATA_YES                  = 1L;
        //SQL_COPT_SS_RESET_CONNECTION 
        constexpr const SQLINTEGER SQL_RESET_YES                       = 1L;
        //SQL_COPT_SS_WARN_ON_CP_ERROR 
        constexpr const SQLINTEGER SQL_WARN_NO                         = 0L;
        constexpr const SQLINTEGER SQL_WARN_YES                        = 1L;
        //SQL_COPT_SS_MARS_ENABLED 
        constexpr const SQLINTEGER SQL_MARS_ENABLED_NO                 = 0L;
        constexpr const SQLINTEGER SQL_MARS_ENABLED_YES                = 1L;
        /* SQL_TXN_ISOLATION_OPTION bitmasks */
        constexpr const SQLINTEGER SQL_TXN_SS_SNAPSHOT                 = 0x00000020L;

        // The following are defines for SQL_CA_SS_COLUMN_SORT_ORDER
        constexpr const SQLINTEGER SQL_SS_ORDER_UNSPECIFIED            = 0L;
        constexpr const SQLINTEGER SQL_SS_DESCENDING_ORDER             = 1L;
        constexpr const SQLINTEGER SQL_SS_ASCENDING_ORDER              = 2L;
        constexpr const SQLINTEGER SQL_SS_ORDER_DEFAULT                = SQL_SS_ORDER_UNSPECIFIED;

        // Driver specific SQL data type defines.
        // Microsoft has -150 thru -199 reserved for Microsoft SQL Server Native Client driver usage.
        constexpr const SQLINTEGER SQL_SS_VARIANT                      = (-150);
        constexpr const SQLINTEGER SQL_SS_UDT                          = (-151);
        constexpr const SQLINTEGER SQL_SS_XML                          = (-152);
        constexpr const SQLINTEGER SQL_SS_TABLE                        = (-153);
        constexpr const SQLINTEGER SQL_SS_TIME2                        = (-154);
        constexpr const SQLINTEGER SQL_SS_TIMESTAMPOFFSET              = (-155);

        // Local types to be used with SQL_CA_SS_SERVER_TYPE
        constexpr const SQLINTEGER SQL_SS_TYPE_DEFAULT = 0L;
        constexpr const SQLINTEGER SQL_SS_TYPE_SMALLDATETIME = 1L;
        constexpr const SQLINTEGER SQL_SS_TYPE_DATETIME = 2L;

        // Extended C Types range 4000 and above. Range of -100 thru 200 is reserved by Driver Manager.
        constexpr const SQLINTEGER SQL_C_TYPES_EXTENDED= 0x04000L;
        constexpr const SQLINTEGER SQL_C_SS_TIME2 = ( SQL_C_TYPES_EXTENDED + 0 );
        constexpr const SQLINTEGER SQL_C_SS_TIMESTAMPOFFSET = ( SQL_C_TYPES_EXTENDED + 1 );

        // SQL Server Data Type defines.
        // New types for SQL 6.0 and later servers
        constexpr const SQLINTEGER SQLTEXT                             = 0x23;
        constexpr const SQLINTEGER SQLVARBINARY                        = 0x25;
        constexpr const SQLINTEGER SQLINTN                             = 0x26;
        constexpr const SQLINTEGER SQLVARCHAR                          = 0x27;
        constexpr const SQLINTEGER SQLBINARY                           = 0x2d;
        constexpr const SQLINTEGER SQLIMAGE                            = 0x22;
        constexpr const SQLINTEGER SQLCHARACTER                        = 0x2f;
        constexpr const SQLINTEGER SQLINT1                             = 0x30;
        constexpr const SQLINTEGER SQLBIT                              = 0x32;
        constexpr const SQLINTEGER SQLINT2                             = 0x34;
        constexpr const SQLINTEGER SQLINT4                             = 0x38;
        constexpr const SQLINTEGER SQLMONEY                            = 0x3c;
        constexpr const SQLINTEGER SQLDATETIME                         = 0x3d;
        constexpr const SQLINTEGER SQLFLT8                             = 0x3e;
        constexpr const SQLINTEGER SQLFLTN                             = 0x6d;
        constexpr const SQLINTEGER SQLMONEYN                           = 0x6e;
        constexpr const SQLINTEGER SQLDATETIMN                         = 0x6f;
        constexpr const SQLINTEGER SQLFLT4                             = 0x3b;
        constexpr const SQLINTEGER SQLMONEY4                           = 0x7a;
        constexpr const SQLINTEGER SQLDATETIM4                         = 0x3a;
        // New types for SQL 6.0 and later servers
        constexpr const SQLINTEGER SQLDECIMAL                          = 0x6a;
        constexpr const SQLINTEGER SQLNUMERIC                          = 0x6c;
        // New types for SQL 7.0 and later servers
        constexpr const SQLINTEGER SQLUNIQUEID                         = 0x24;
        constexpr const SQLINTEGER SQLBIGCHAR                          = 0xaf;
        constexpr const SQLINTEGER SQLBIGVARCHAR                       = 0xa7;
        constexpr const SQLINTEGER SQLBIGBINARY                        = 0xad;
        constexpr const SQLINTEGER SQLBIGVARBINARY                     = 0xa5;
        constexpr const SQLINTEGER SQLBITN                             = 0x68;
        constexpr const SQLINTEGER SQLNCHAR                            = 0xef;
        constexpr const SQLINTEGER SQLNVARCHAR                         = 0xe7;
        constexpr const SQLINTEGER SQLNTEXT                            = 0x63;
        // New types for SQL 2000 and later servers
        constexpr const SQLINTEGER SQLINT8                             = 0x7f;
        constexpr const SQLINTEGER SQLVARIANT                          = 0x62;
        // New types for SQL 2005 and later servers
        constexpr const SQLINTEGER SQLUDT = 0xf0;
        constexpr const SQLINTEGER SQLXML                              = 0xf1;
        // New types for SQL 2008 and later servers
        constexpr const SQLINTEGER SQLTABLE                            = 0xf3;
        constexpr const SQLINTEGER SQLDATEN                            = 0x28;
        constexpr const SQLINTEGER SQLTIMEN                            = 0x29;
        constexpr const SQLINTEGER SQLDATETIME2N                       = 0x2a;
        constexpr const SQLINTEGER SQLDATETIMEOFFSETN                  = 0x2b;
        // Define old names
        constexpr const SQLINTEGER SQLDECIMALN                         = 0x6a;
        constexpr const SQLINTEGER SQLNUMERICN                         = 0x6c;

        // SQL_SS_LENGTH_UNLIMITED is used to describe the max length of
        // VARCHAR(max), VARBINARY(max), NVARCHAR(max), and XML columns
        constexpr const SQLINTEGER SQL_SS_LENGTH_UNLIMITED             = 0;

        // User Data Type definitions.
        // Returned by SQLColAttributes/SQL_CA_SS_COLUMN_UTYPE.
        constexpr const SQLINTEGER SQLudtBINARY                        = 3;
        constexpr const SQLINTEGER SQLudtBIT                           = 16;
        constexpr const SQLINTEGER SQLudtBITN                          = 0;
        constexpr const SQLINTEGER SQLudtCHAR                          = 1;
        constexpr const SQLINTEGER SQLudtDATETIM4                      = 22;
        constexpr const SQLINTEGER SQLudtDATETIME                      = 12;
        constexpr const SQLINTEGER SQLudtDATETIMN                      = 15;
        constexpr const SQLINTEGER SQLudtDECML                         = 24;
        constexpr const SQLINTEGER SQLudtDECMLN                        = 26;
        constexpr const SQLINTEGER SQLudtFLT4                          = 23;
        constexpr const SQLINTEGER SQLudtFLT8                          = 8;
        constexpr const SQLINTEGER SQLudtFLTN                          = 14;
        constexpr const SQLINTEGER SQLudtIMAGE                         = 20;
        constexpr const SQLINTEGER SQLudtINT1                          = 5;
        constexpr const SQLINTEGER SQLudtINT2                          = 6;
        constexpr const SQLINTEGER SQLudtINT4                          = 7;
        constexpr const SQLINTEGER SQLudtINTN                          = 13;
        constexpr const SQLINTEGER SQLudtMONEY                         = 11;
        constexpr const SQLINTEGER SQLudtMONEY4                        = 21;
        constexpr const SQLINTEGER SQLudtMONEYN                        = 17;
        constexpr const SQLINTEGER SQLudtNUM                           = 10;
        constexpr const SQLINTEGER SQLudtNUMN                          = 25;
        constexpr const SQLINTEGER SQLudtSYSNAME                       = 18;
        constexpr const SQLINTEGER SQLudtTEXT                          = 19;
        constexpr const SQLINTEGER SQLudtTIMESTAMP                     = 80;
        constexpr const SQLINTEGER SQLudtUNIQUEIDENTIFIER              = 0;
        constexpr const SQLINTEGER SQLudtVARBINARY                     = 4;
        constexpr const SQLINTEGER SQLudtVARCHAR                       = 2;
        constexpr const SQLINTEGER MIN_USER_DATATYPE                   = 256;
        // Aggregate operator types.
        // Returned by SQLColAttributes/SQL_CA_SS_COLUMN_OP.
        constexpr const SQLINTEGER SQLAOPSTDEV                         = 0x30;    // Standard deviation
        constexpr const SQLINTEGER SQLAOPSTDEVP                        = 0x31;    // Standard deviation population
        constexpr const SQLINTEGER SQLAOPVAR                           = 0x32;    // Variance
        constexpr const SQLINTEGER SQLAOPVARP                          = 0x33;    // Variance population
        constexpr const SQLINTEGER SQLAOPCNT                           = 0x4b;    // Count
        constexpr const SQLINTEGER SQLAOPSUM                           = 0x4d;    // Sum
        constexpr const SQLINTEGER SQLAOPAVG                           = 0x4f;    // Average
        constexpr const SQLINTEGER SQLAOPMIN                           = 0x51;    // Min
        constexpr const SQLINTEGER SQLAOPMAX                           = 0x52;    // Max
        constexpr const SQLINTEGER SQLAOPANY                           = 0x53;    // Any
        constexpr const SQLINTEGER SQLAOPNOOP                          = 0x56;    // None
        // SQLGetInfo driver specific defines.
        // Microsoft has 1151 thru 1200 reserved for Microsoft SQL Server Native Client driver usage.
        constexpr const SQLINTEGER SQL_INFO_SS_FIRST = 1199;
        constexpr const SQLINTEGER SQL_INFO_SS_NETLIB_NAMEW            = (SQL_INFO_SS_FIRST+0); //  dbprocinfo
        constexpr const SQLINTEGER SQL_INFO_SS_NETLIB_NAMEA            = (SQL_INFO_SS_FIRST+1); //  dbprocinfo
        constexpr const SQLINTEGER SQL_INFO_SS_MAX_USED                = SQL_INFO_SS_NETLIB_NAMEA;
#ifdef UNICODE
        constexpr const auto SQL_INFO_SS_NETLIB_NAME = SQL_INFO_SS_NETLIB_NAMEW;
#else
        constexpr const auto SQL_INFO_SS_NETLIB_NAME = SQL_INFO_SS_NETLIB_NAMEA;
#endif

        // SQLGetDiagField driver specific defines.
        // Microsoft has -1150 thru -1199 reserved for Microsoft SQL Server Native Client driver usage.
        constexpr const SQLINTEGER SQL_DIAG_SS_BASE                    = (-1150);
        constexpr const SQLINTEGER SQL_DIAG_SS_MSGSTATE                = (SQL_DIAG_SS_BASE);
        constexpr const SQLINTEGER SQL_DIAG_SS_SEVERITY                = (SQL_DIAG_SS_BASE-1);
        constexpr const SQLINTEGER SQL_DIAG_SS_SRVNAME                 = (SQL_DIAG_SS_BASE-2);
        constexpr const SQLINTEGER SQL_DIAG_SS_PROCNAME                = (SQL_DIAG_SS_BASE-3);
        constexpr const SQLINTEGER SQL_DIAG_SS_LINE                    = (SQL_DIAG_SS_BASE-4);
        // SQLGetDiagField/SQL_DIAG_DYNAMIC_FUNCTION_CODE driver specific defines.
        // Microsoft has -200 thru -299 reserved for Microsoft SQL Server Native Client driver usage.
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_BASE                = (-200);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_ALTER_DATABASE      = (SQL_DIAG_DFC_SS_BASE-0);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CHECKPOINT          = (SQL_DIAG_DFC_SS_BASE-1);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CONDITION           = (SQL_DIAG_DFC_SS_BASE-2);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CREATE_DATABASE     = (SQL_DIAG_DFC_SS_BASE-3);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CREATE_DEFAULT      = (SQL_DIAG_DFC_SS_BASE-4);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CREATE_PROCEDURE    = (SQL_DIAG_DFC_SS_BASE-5);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CREATE_RULE         = (SQL_DIAG_DFC_SS_BASE-6);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CREATE_TRIGGER      = (SQL_DIAG_DFC_SS_BASE-7);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CURSOR_DECLARE      = (SQL_DIAG_DFC_SS_BASE-8);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CURSOR_OPEN         = (SQL_DIAG_DFC_SS_BASE-9);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CURSOR_FETCH        = (SQL_DIAG_DFC_SS_BASE-10);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CURSOR_CLOSE        = (SQL_DIAG_DFC_SS_BASE-11);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DEALLOCATE_CURSOR   = (SQL_DIAG_DFC_SS_BASE-12);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DBCC                = (SQL_DIAG_DFC_SS_BASE-13);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DISK                = (SQL_DIAG_DFC_SS_BASE-14);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DROP_DATABASE       = (SQL_DIAG_DFC_SS_BASE-15);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DROP_DEFAULT        = (SQL_DIAG_DFC_SS_BASE-16);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DROP_PROCEDURE      = (SQL_DIAG_DFC_SS_BASE-17);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DROP_RULE           = (SQL_DIAG_DFC_SS_BASE-18);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DROP_TRIGGER        = (SQL_DIAG_DFC_SS_BASE-19);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DUMP_DATABASE       = (SQL_DIAG_DFC_SS_BASE-20);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_BACKUP_DATABASE     = (SQL_DIAG_DFC_SS_BASE-20);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DUMP_TABLE          = (SQL_DIAG_DFC_SS_BASE-21);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DUMP_TRANSACTION    = (SQL_DIAG_DFC_SS_BASE-22);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_BACKUP_TRANSACTION  = (SQL_DIAG_DFC_SS_BASE-22);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_GOTO                = (SQL_DIAG_DFC_SS_BASE-23);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_INSERT_BULK         = (SQL_DIAG_DFC_SS_BASE-24);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_KILL                = (SQL_DIAG_DFC_SS_BASE-25);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_LOAD_DATABASE       = (SQL_DIAG_DFC_SS_BASE-26);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_RESTORE_DATABASE    = (SQL_DIAG_DFC_SS_BASE-26);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_LOAD_HEADERONLY     = (SQL_DIAG_DFC_SS_BASE-27);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_RESTORE_HEADERONLY  = (SQL_DIAG_DFC_SS_BASE-27);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_LOAD_TABLE          = (SQL_DIAG_DFC_SS_BASE-28);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_LOAD_TRANSACTION    = (SQL_DIAG_DFC_SS_BASE-29);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_RESTORE_TRANSACTION = (SQL_DIAG_DFC_SS_BASE-29);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_PRINT               = (SQL_DIAG_DFC_SS_BASE-30);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_RAISERROR           = (SQL_DIAG_DFC_SS_BASE-31);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_READTEXT            = (SQL_DIAG_DFC_SS_BASE-32);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_RECONFIGURE         = (SQL_DIAG_DFC_SS_BASE-33);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_RETURN              = (SQL_DIAG_DFC_SS_BASE-34);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SELECT_INTO         = (SQL_DIAG_DFC_SS_BASE-35);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SET                 = (SQL_DIAG_DFC_SS_BASE-36);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SET_IDENTITY_INSERT = (SQL_DIAG_DFC_SS_BASE-37);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SET_ROW_COUNT       = (SQL_DIAG_DFC_SS_BASE-38);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SET_STATISTICS      = (SQL_DIAG_DFC_SS_BASE-39);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SET_TEXTSIZE        = (SQL_DIAG_DFC_SS_BASE-40);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SETUSER             = (SQL_DIAG_DFC_SS_BASE-41);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SHUTDOWN            = (SQL_DIAG_DFC_SS_BASE-42);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_TRANS_BEGIN         = (SQL_DIAG_DFC_SS_BASE-43);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_TRANS_COMMIT        = (SQL_DIAG_DFC_SS_BASE-44);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_TRANS_PREPARE       = (SQL_DIAG_DFC_SS_BASE-45);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_TRANS_ROLLBACK      = (SQL_DIAG_DFC_SS_BASE-46);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_TRANS_SAVE          = (SQL_DIAG_DFC_SS_BASE-47);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_TRUNCATE_TABLE      = (SQL_DIAG_DFC_SS_BASE-48);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_UPDATE_STATISTICS   = (SQL_DIAG_DFC_SS_BASE-49);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_UPDATETEXT          = (SQL_DIAG_DFC_SS_BASE-50);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_USE                 = (SQL_DIAG_DFC_SS_BASE-51);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_WAITFOR             = (SQL_DIAG_DFC_SS_BASE-52);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_WRITETEXT           = (SQL_DIAG_DFC_SS_BASE-53);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DENY                = (SQL_DIAG_DFC_SS_BASE-54);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SET_XCTLVL          = (SQL_DIAG_DFC_SS_BASE-55);
        constexpr const SQLINTEGER SQL_DIAG_DFC_SS_MERGE               = (SQL_DIAG_DFC_SS_BASE-56);

        // Severity codes for SQL_DIAG_SS_SEVERITY
        constexpr const SQLINTEGER EX_ANY          = 0;
        constexpr const SQLINTEGER EX_INFO         = 10;
        constexpr const SQLINTEGER EX_MAXISEVERITY = EX_INFO;
        constexpr const SQLINTEGER EX_MISSING      = 11;
        constexpr const SQLINTEGER EX_TYPE         = 12;
        constexpr const SQLINTEGER EX_DEADLOCK     = 13;
        constexpr const SQLINTEGER EX_PERMIT       = 14;
        constexpr const SQLINTEGER EX_SYNTAX       = 15;
        constexpr const SQLINTEGER EX_USER         = 16;
        constexpr const SQLINTEGER EX_RESOURCE     = 17;
        constexpr const SQLINTEGER EX_INTOK        = 18;
        constexpr const SQLINTEGER MAXUSEVERITY    = EX_INTOK;
        constexpr const SQLINTEGER EX_LIMIT        = 19;
        constexpr const SQLINTEGER EX_CMDFATAL     = 20;
        constexpr const SQLINTEGER MINFATALERR     = EX_CMDFATAL;
        constexpr const SQLINTEGER EX_DBFATAL      = 21;
        constexpr const SQLINTEGER EX_TABCORRUPT   = 22;
        constexpr const SQLINTEGER EX_DBCORRUPT    = 23;
        constexpr const SQLINTEGER EX_HARDWARE     = 24;
        constexpr const SQLINTEGER EX_CONTROL      = 25;
        // Internal server datatypes - used when binding to SQL_C_BINARY

        // DB-Library datatypes
        constexpr const SQLINTEGER DBMAXCHAR       = (8000+1);                    // Max length of DBVARBINARY and DBVARCHAR, etc. +1 for zero byte
        constexpr const SQLINTEGER MAXNAME         = (SQL_MAX_SQLSERVERNAME+1);   // Max server identifier length including zero byte
#ifdef UNICODE
        typedef wchar_t  DBCHAR;
#else
        typedef char DBCHAR;

#endif

        typedef short SQLSMALLINT;

        typedef unsigned short SQLUSMALLINT;

        typedef unsigned char DBBINARY;

        typedef unsigned char DBTINYINT;

        typedef short DBSMALLINT;

        typedef unsigned short DBUSMALLINT;

        typedef double DBFLT8;

        typedef unsigned char DBBIT;

        typedef unsigned char DBBOOL;

        typedef float DBFLT4;

        typedef DBFLT4 DBREAL;

        typedef UINT DBUBOOL;

        typedef struct dbmoney
        {
            LONG mnyhigh;
            ULONG mnylow;
        } 	DBMONEY;

        typedef struct dbdatetime
        {
            LONG dtdays;
            ULONG dttime;
        } 	DBDATETIME;

        typedef struct dbdatetime4
        {
            USHORT numdays;
            USHORT nummins;
        } 	DBDATETIM4;

        typedef LONG DBMONEY4;

        // New Date Time Structures
        // New Structure for TIME2
        typedef struct tagSS_TIME2_STRUCT
        {
            SQLUSMALLINT   hour;
            SQLUSMALLINT   minute;
            SQLUSMALLINT   second;
            SQLUINTEGER    fraction;
        } SQL_SS_TIME2_STRUCT;
        // New Structure for TIMESTAMPOFFSET
        typedef struct tagSS_TIMESTAMPOFFSET_STRUCT
        {
            SQLSMALLINT    year;
            SQLUSMALLINT   month;
            SQLUSMALLINT   day;
            SQLUSMALLINT   hour;
            SQLUSMALLINT   minute;
            SQLUSMALLINT   second;
            SQLUINTEGER    fraction;
            SQLSMALLINT    timezone_hour;
            SQLSMALLINT    timezone_minute;
        } SQL_SS_TIMESTAMPOFFSET_STRUCT;

        typedef struct tagDBTIME2
        {
            USHORT hour;
            USHORT minute;
            USHORT second;
            ULONG fraction;
        }   DBTIME2;

        typedef struct tagDBTIMESTAMPOFFSET
        {
            SHORT year;
            USHORT month;
            USHORT day;
            USHORT hour;
            USHORT minute;
            USHORT second;
            ULONG fraction;
            SHORT timezone_hour;
            SHORT timezone_minute;
        }   DBTIMESTAMPOFFSET;


        using DBNUM_PREC_TYPE = BYTE;
        using DBNUM_SCALE_TYPE = BYTE;
        using DBNUM_VAL_TYPE = BYTE;

    }


    enum class HandleType : SQLSMALLINT
    {
        Environment = SQL_HANDLE_ENV,
        Connection = SQL_HANDLE_DBC,
        Statement = SQL_HANDLE_STMT,
        Descriptor = SQL_HANDLE_DESC
    };


    enum class Result : SQLRETURN
    {
        InvalidHandle = SQL_INVALID_HANDLE,
        Error = SQL_ERROR,
        Success = SQL_SUCCESS,
        SuccessWithInfo = SQL_SUCCESS_WITH_INFO,
        StillExecuting = SQL_STILL_EXECUTING,
        NeedData = SQL_NEED_DATA,
        NoData = SQL_NO_DATA,
        ParameterDataAvailable = SQL_PARAM_DATA_AVAILABLE
    };

    // test for not Result::InvalidHandle and not Result::Error
    inline constexpr bool Succeeded( Result result )
    {
        return SQL_SUCCEEDED( static_cast<SQLRETURN>( result ) );
    }

    inline constexpr bool Failed( Result result )
    {
        return Succeeded( result ) == false;
    }


    enum class BulkOperation : SQLSMALLINT
    {
        Add = SQL_ADD, 
        UpdateByBookmark = SQL_UPDATE_BY_BOOKMARK,
        DeleteByBookmark = SQL_DELETE_BY_BOOKMARK,
        FetchByBookmark = SQL_FETCH_BY_BOOKMARK
    };

    enum class ConnectionPooling : UInt32
    {
        Off = SQL_CP_OFF,
        Default = SQL_CP_DEFAULT,
        OnePerDriver = SQL_CP_ONE_PER_DRIVER,
        OnePerEnvironment = SQL_CP_ONE_PER_HENV,
        DriverAware = SQL_CP_DRIVER_AWARE
    };

    enum class Version : UInt32
    {
        Version2 = SQL_OV_ODBC2,
        Version3 = SQL_OV_ODBC3,
        Version3_80 = SQL_OV_ODBC3_80
    };


    enum class Fetch : SQLUSMALLINT
    {
        Next = SQL_FETCH_NEXT,
        First = SQL_FETCH_FIRST,
        Last = SQL_FETCH_LAST,
        Prior = SQL_FETCH_PRIOR,
        Absolute = SQL_FETCH_ABSOLUTE,
        Relative = SQL_FETCH_RELATIVE,
        FirstForUser = SQL_FETCH_FIRST_USER,
        FirstForSystem =SQL_FETCH_FIRST_SYSTEM
    };

    enum class Nullable : SQLSMALLINT
    {
        No = SQL_NO_NULLS,
        Yes = SQL_NULLABLE,
        Unknown = SQL_NULLABLE_UNKNOWN
    };

    enum class AccessMode : SQLUINTEGER
    {
        Default = SQL_MODE_DEFAULT,
        ReadWrite = SQL_MODE_READ_WRITE,
        ReadOnly = SQL_MODE_READ_ONLY,
    };

    enum class ParameterDirection : SQLSMALLINT
    {
        Unknown = SQL_PARAM_TYPE_UNKNOWN,
        Input = SQL_PARAM_INPUT,
        InputOutput = SQL_PARAM_INPUT_OUTPUT,
        ResultColumn = SQL_RESULT_COL,
        Output = SQL_PARAM_OUTPUT,
        ReturnValue = SQL_RETURN_VALUE,
        InputOutputStream = SQL_PARAM_INPUT_OUTPUT_STREAM,
        OutputStream = SQL_PARAM_OUTPUT_STREAM
    };

    



    namespace SqlType
    {
        constexpr SQLSMALLINT Unknown = SQL_UNKNOWN_TYPE;
        constexpr SQLSMALLINT Char = SQL_CHAR;
        constexpr SQLSMALLINT Numeric = SQL_NUMERIC;
        constexpr SQLSMALLINT Decimal = SQL_DECIMAL;
        constexpr SQLSMALLINT Integer = SQL_INTEGER;
        constexpr SQLSMALLINT SmallInt = SQL_SMALLINT;
        constexpr SQLSMALLINT VarChar = SQL_VARCHAR;
        constexpr SQLSMALLINT LongVarChar = SQL_LONGVARCHAR;
        constexpr SQLSMALLINT WChar = SQL_WCHAR;
        constexpr SQLSMALLINT WVarChar = SQL_WVARCHAR;
        constexpr SQLSMALLINT WLongVarChar = SQL_WLONGVARCHAR;
        constexpr SQLSMALLINT Real = SQL_REAL;
        constexpr SQLSMALLINT Float = SQL_FLOAT;
        constexpr SQLSMALLINT Double = SQL_DOUBLE;
        constexpr SQLSMALLINT Bit = SQL_BIT;
        constexpr SQLSMALLINT TinyInt = SQL_TINYINT;
        constexpr SQLSMALLINT BigInt = SQL_BIGINT;
        constexpr SQLSMALLINT Binary = SQL_BINARY;
        constexpr SQLSMALLINT VarBinary = SQL_VARBINARY;
        constexpr SQLSMALLINT LongVarBinary = SQL_LONGVARBINARY;
        constexpr SQLSMALLINT Date = SQL_TYPE_DATE;
        constexpr SQLSMALLINT Time = SQL_TYPE_TIME;
        constexpr SQLSMALLINT TimeStamp = SQL_TYPE_TIMESTAMP;
        //constexpr SQLSMALLINT UTCDateTime = SQL_TYPE_UTCDATETIME;
        //constexpr SQLSMALLINT UTCTime = SQL_TYPE_UTCTIME;
        constexpr SQLSMALLINT IntervalMonth = SQL_INTERVAL_MONTH;
        constexpr SQLSMALLINT IntervalYear = SQL_INTERVAL_YEAR;
        constexpr SQLSMALLINT IntervalYearToMonth = SQL_INTERVAL_YEAR_TO_MONTH;
        constexpr SQLSMALLINT IntervalDay = SQL_INTERVAL_DAY;
        constexpr SQLSMALLINT IntervalHour = SQL_INTERVAL_HOUR;
        constexpr SQLSMALLINT IntervalMinute = SQL_INTERVAL_MINUTE;
        constexpr SQLSMALLINT IntervalSecond = SQL_INTERVAL_SECOND;
        constexpr SQLSMALLINT IntervalDayToHour = SQL_INTERVAL_DAY_TO_HOUR;
        constexpr SQLSMALLINT IntervalDayToMinute = SQL_INTERVAL_DAY_TO_MINUTE;
        constexpr SQLSMALLINT IntervalDayToSecond = SQL_INTERVAL_DAY_TO_SECOND;
        constexpr SQLSMALLINT IntervalHourToMinute = SQL_INTERVAL_HOUR_TO_MINUTE;
        constexpr SQLSMALLINT IntervalHourToSecond = SQL_INTERVAL_HOUR_TO_SECOND;
        constexpr SQLSMALLINT IntervalMinuteToSecond = SQL_INTERVAL_MINUTE_TO_SECOND;
        constexpr SQLSMALLINT Guid = SQL_GUID;

        // Values specific to MS SQL Server:
        constexpr SQLSMALLINT TimeStampOffset = MsSql::SQL_SS_TIMESTAMPOFFSET;
        constexpr SQLSMALLINT Time2 = MsSql::SQL_SS_TIME2;
    }
    namespace NativeType
    {
        constexpr SQLSMALLINT Char = SQL_C_CHAR;
        constexpr SQLSMALLINT WideChar = SQL_C_WCHAR;
        constexpr SQLSMALLINT Long = SQL_C_LONG;
        constexpr SQLSMALLINT Short = SQL_C_SHORT;
        constexpr SQLSMALLINT Single = SQL_C_FLOAT;
        constexpr SQLSMALLINT Double = SQL_C_DOUBLE;
        constexpr SQLSMALLINT Numeric = SQL_C_NUMERIC;
        constexpr SQLSMALLINT Default = SQL_C_DEFAULT;
        constexpr SQLSMALLINT SignedOffset = SQL_SIGNED_OFFSET;
        constexpr SQLSMALLINT UnsignedOffset = SQL_UNSIGNED_OFFSET;
        constexpr SQLSMALLINT Date = SQL_C_DATE;
        constexpr SQLSMALLINT Time = SQL_C_TIME;
        constexpr SQLSMALLINT TimeStamp = SQL_C_TIMESTAMP;
        constexpr SQLSMALLINT TypeDate = SQL_C_TYPE_DATE;
        constexpr SQLSMALLINT TypeTime = SQL_C_TYPE_TIME;
        constexpr SQLSMALLINT TypeTimeStamp = SQL_C_TYPE_TIMESTAMP;
        constexpr SQLSMALLINT IntervalYear = SQL_C_INTERVAL_YEAR;
        constexpr SQLSMALLINT IntervalMonth = SQL_C_INTERVAL_MONTH;
        constexpr SQLSMALLINT IntervalDay = SQL_C_INTERVAL_DAY;
        constexpr SQLSMALLINT IntervalHour = SQL_C_INTERVAL_HOUR;
        constexpr SQLSMALLINT IntervalMinute = SQL_C_INTERVAL_MINUTE;
        constexpr SQLSMALLINT IntervalSecond = SQL_C_INTERVAL_SECOND;
        constexpr SQLSMALLINT IntervalYearToMonth = SQL_C_INTERVAL_YEAR_TO_MONTH;
        constexpr SQLSMALLINT IntervalDayToHour = SQL_C_INTERVAL_DAY_TO_HOUR;
        constexpr SQLSMALLINT IntervalDayToMinute = SQL_C_INTERVAL_DAY_TO_MINUTE;
        constexpr SQLSMALLINT IntervalDayToSecond = SQL_C_INTERVAL_DAY_TO_SECOND;
        constexpr SQLSMALLINT IntervalHourToMinute = SQL_C_INTERVAL_HOUR_TO_MINUTE;
        constexpr SQLSMALLINT IntervalHourToSecond = SQL_C_INTERVAL_HOUR_TO_SECOND;
        constexpr SQLSMALLINT IntervalMinuteToSecond = SQL_C_INTERVAL_MINUTE_TO_SECOND;
        constexpr SQLSMALLINT Binary = SQL_C_BINARY;
        constexpr SQLSMALLINT Bit = SQL_C_BIT;
        constexpr SQLSMALLINT Boolean = SQL_C_BIT;
        constexpr SQLSMALLINT Int64 = SQL_C_SBIGINT;
        constexpr SQLSMALLINT UInt64 = SQL_C_UBIGINT;
        constexpr SQLSMALLINT TinyInt = SQL_C_TINYINT;
        constexpr SQLSMALLINT Int32 = SQL_C_SLONG;
        constexpr SQLSMALLINT Int16 = SQL_C_SSHORT;
        constexpr SQLSMALLINT SByte = SQL_C_STINYINT;
        constexpr SQLSMALLINT UInt32 = SQL_C_ULONG;
        constexpr SQLSMALLINT UInt16 = SQL_C_USHORT;
        constexpr SQLSMALLINT Byte = SQL_C_UTINYINT;
        constexpr SQLSMALLINT Bookmark = SQL_C_BOOKMARK;
        constexpr SQLSMALLINT Guid = SQL_C_GUID;
    }



    enum class DriverCompletion : SQLUSMALLINT
    {
        None = SQL_DRIVER_NOPROMPT,
        Complete = SQL_DRIVER_COMPLETE,
        Prompt = SQL_DRIVER_PROMPT,
        CompleteRequired = SQL_DRIVER_COMPLETE_REQUIRED
    };


    enum class TransactionCompletionType : SQLSMALLINT
    {
        Commit = SQL_COMMIT,
        Rollback = SQL_ROLLBACK
    };


    struct Driver
    {
        WideString Description;
        WideString Attributes;
    };

    struct DataSource
    {
        WideString Name;
        WideString Description;
    };


    struct SqlState
    {
        SQLWCHAR Value[ 6 ] = {};

        SqlState( )
        { }

        explicit SqlState( const SQLWCHAR* sqlState )
        {
            wmemcpy( Value, sqlState, 5 );
        }

        bool operator == ( const SQLWCHAR* sqlState )
        {
            return wmemcmp( Value, sqlState, 5 ) == 0;
        }
        bool operator != ( const SQLWCHAR* sqlState )
        {
            return wmemcmp( Value, sqlState, 5 ) != 0;
        }
        bool operator == ( const SqlState& other )
        {
            return wmemcmp( Value, other.Value, 5 ) == 0;
        }
        bool operator != ( const SqlState& other )
        {
            return wmemcmp( Value, other.Value, 5 ) != 0;
        }


        size_t size( ) const
        {
            return 5;
        }

        const wchar_t* c_str( ) const
        {
            return Value;
        }

    };

    struct DiagnosticRecord
    {
        size_t RecordNumber = 0; 
        SQLWCHAR SqlState[ 6 ] = {};
        SQLINTEGER NativeError = 0; 
        SQLWCHAR Message[ SQL_MAX_MESSAGE_LENGTH ] = {};
        SQLSMALLINT MessageLength = 0;
    };




    namespace Internal
    {
        HODBC_EXPORT void ThrowColumnNullException( SQLSMALLINT columnNumber, const wchar_t* function, const wchar_t* file, int line );
        HODBC_EXPORT void ThrowException( SQLRETURN sqlReturn, ODBC::HandleType handleType, SQLHANDLE sqlHandle, const wchar_t* function, const wchar_t* file, int line );
        HODBC_EXPORT void ThrowException( SQLRETURN sqlReturn, ODBC::HandleType handleType, SQLHANDLE sqlHandle );
        HODBC_EXPORT void ThrowExceptionNoDiagnostic( SQLRETURN sqlReturn, ODBC::HandleType handleType, SQLHANDLE sqlHandle, const wchar_t* function, const wchar_t* file, int line );
        HODBC_EXPORT void ThrowExceptionNoDiagnostic( SQLRETURN sqlReturn, ODBC::HandleType handleType, SQLHANDLE sqlHandle );

        inline Result GetDiagnosticFieldW( ODBC::HandleType handleType, SQLHANDLE handle,
            SQLSMALLINT recordNumber,
            SQLSMALLINT diagnosticFieldId,
            SQLPOINTER  diagnosticInfo,
            SQLSMALLINT diagnosticInfoMaxLength,
            SQLSMALLINT* diagnosticInfoActualLength )
        {
            auto rc = SQLGetDiagFieldW( static_cast<SQLSMALLINT>( handleType ), handle, recordNumber, diagnosticFieldId, diagnosticInfo, diagnosticInfoMaxLength, diagnosticInfoActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowExceptionNoDiagnostic( rc, handleType, handle, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        inline Result GetDiagnosticFieldA( ODBC::HandleType handleType, SQLHANDLE handle,
            SQLSMALLINT recordNumber,
            SQLSMALLINT diagnosticFieldId,
            SQLPOINTER  diagnosticInfo,
            SQLSMALLINT diagnosticInfoMaxLength,
            SQLSMALLINT* diagnosticInfoActualLength )
        {
            auto rc = SQLGetDiagFieldA( static_cast<SQLSMALLINT>( handleType ), handle, recordNumber, diagnosticFieldId, diagnosticInfo, diagnosticInfoMaxLength, diagnosticInfoActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowExceptionNoDiagnostic( rc, handleType, handle, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        inline Result GetDiagnosticRecord( ODBC::HandleType handleType, SQLHANDLE handle, SQLSMALLINT recordNumber, SQLWCHAR* sqlState, SQLINTEGER* nativeError, SQLWCHAR* message, SQLSMALLINT messageMaxLength, SQLSMALLINT* messageActualLength )
        {
            auto rc = SQLGetDiagRecW( static_cast<SQLSMALLINT>( handleType ), handle, recordNumber, sqlState, nativeError, message, messageMaxLength, messageActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowExceptionNoDiagnostic( rc, handleType, handle, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        inline Result GetDiagnosticRecord( ODBC::HandleType handleType, SQLHANDLE handle, SQLSMALLINT recordNumber, SQLCHAR* sqlState, SQLINTEGER* nativeError, SQLCHAR* message, SQLSMALLINT messageMaxLength, SQLSMALLINT* messageActualLength )
        {
            auto rc = SQLGetDiagRecA( static_cast<SQLSMALLINT>( handleType ), handle, recordNumber, sqlState, nativeError, message, messageMaxLength, messageActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowExceptionNoDiagnostic( rc, handleType, handle, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        inline DiagnosticRecord GetDiagnosticRecord( ODBC::HandleType handleType, SQLHANDLE handle, SQLSMALLINT recordNumber )
        {
            DiagnosticRecord result;
            GetDiagnosticRecord( handleType, handle, recordNumber, result.SqlState, &result.NativeError, result.Message, SQL_MAX_MESSAGE_LENGTH, &result.MessageLength );
            result.RecordNumber = recordNumber;
            return result;
        }

        inline SQLLEN GetDiagnosticRecordRecordCount( ODBC::HandleType handleType, SQLHANDLE handle )
        {
            SQLLEN result = 0;
            SQLGetDiagFieldW( static_cast<SQLSMALLINT>(handleType), handle, 0, SQL_DIAG_NUMBER, &result, 0, 0 );
            return result;
        }

        
        inline SqlState GetSqlState( ODBC::HandleType handleType, SQLHANDLE handle, SQLSMALLINT recordNumber = 1)
        {
            auto recordCount = GetDiagnosticRecordRecordCount( handleType, handle );
            if ( recordNumber > 0 && recordNumber <= recordCount )
            {
                DiagnosticRecord diagnosticRecord = GetDiagnosticRecord( handleType, handle, recordNumber );
                return SqlState(diagnosticRecord.SqlState);
            }
            return {};
        }

    }


    class TimeStamp : public SQL_TIMESTAMP_STRUCT
    {
    public:
        using Base = SQL_TIMESTAMP_STRUCT;
        static constexpr size_t Size = sizeof( SQL_TIMESTAMP_STRUCT );


        TimeStamp()
            : Base{}
        { }


        DateTime ToDateTime( ) const
        {
            auto ticks = DateTime::ToTicks( year, month, day, hour, minute, second, 0 ) + ( fraction / 100 );
            return DateTime( ticks );
        }

        TimeStamp& operator = ( const DateTime& dateTime )
        {
            int y, m, d;
            dateTime.GetYearMonthDay( y, m, d );
            year = y;
            month = m; 
            day = d;
            hour = dateTime.Hour( );
            minute = dateTime.Minute( );
            second = dateTime.Second( );
            fraction = ( dateTime.Ticks( ) % DateTime::TicksPerSecond ) * 100;
            return *this;
        }


    };

    class Date : public SQL_DATE_STRUCT
    {
    public:
        using Base = SQL_DATE_STRUCT;
        Date( )
            : Base{}
        {
        }

        DateTime ToDateTime( ) const
        {
            auto ticks = DateTime::DateToTicks( year, month, day );
            return DateTime( ticks );
        }

        Date& operator = ( const DateTime& dateTime )
        {
            int y, m, d;
            dateTime.GetYearMonthDay( y, m, d );
            year = y;
            month = m;
            day = d;
            return *this;
        }


    };

    class Time : public SQL_TIME_STRUCT
    {
    public:
        using Base = SQL_TIME_STRUCT;
        Time( )
            : Base{}
        {
        }

        DateTime ToDateTime( ) const
        {
            auto ticks = DateTime::TimeToTicks( hour, minute, second );
            return DateTime( ticks );
        }
        TimeSpan ToTimeSpan( ) const
        {
            auto ticks = DateTime::TimeToTicks( hour, minute, second );
            return TimeSpan( ticks );
        }

        Time& operator = ( const DateTime& dateTime )
        {
            hour = dateTime.Hour( );
            minute = dateTime.Minute( );
            second = dateTime.Second( );
            return *this;
        }
    };


    enum class IntervalType
    {
        Year = SQL_IS_YEAR,
        Month = SQL_IS_MONTH,
        Day = SQL_IS_DAY,
        Hour = SQL_IS_HOUR,
        Minute = SQL_IS_MINUTE,
        Second = SQL_IS_SECOND,
        YearToMonth = SQL_IS_YEAR_TO_MONTH,
        DayToHour = SQL_IS_DAY_TO_HOUR,
        DayToMinute = SQL_IS_DAY_TO_MINUTE,
        DayToSecond = SQL_IS_DAY_TO_SECOND,
        HourToMinute = SQL_IS_HOUR_TO_MINUTE,
        HourToSecond = SQL_IS_HOUR_TO_SECOND,
        MinuteToSecond = SQL_IS_MINUTE_TO_SECOND
    };


    class Interval : public SQL_INTERVAL_STRUCT
    {
    public:
        using Base = SQL_INTERVAL_STRUCT;

        Interval()
            : Base{}
        {
        }

        bool IsNegative( ) const
        {
            return Base::interval_sign != 0;
        }

        IntervalType Type( ) const
        {
            return static_cast< IntervalType >( Base::interval_type );
        }


        TimeSpan ToTimeSpan( ) const
        {
            auto type = Type( );
            switch ( type )
            {
                case IntervalType::DayToSecond:
                {
                    Int64 ticks = ( ( Base::intval.day_second.day * TimeSpan::TicksPerDay )
                        + ( Base::intval.day_second.hour * TimeSpan::TicksPerHour )
                        + ( Base::intval.day_second.minute * TimeSpan::TicksPerMinute )
                        + ( Base::intval.day_second.second * TimeSpan::TicksPerSecond )
                        + ( Base::intval.day_second.fraction / 100 ) );
                    if ( IsNegative( ) )
                    {
                        return TimeSpan( -ticks );
                    }
                    else
                    {
                        return TimeSpan( ticks );
                    }
                }
                break;
            }

        }


    };

    struct TimestampOffset
    {
        SQLSMALLINT year = 0;
        SQLUSMALLINT month = 0;
        SQLUSMALLINT day = 0;
        SQLUSMALLINT hour = 0;
        SQLUSMALLINT minute = 0;
        SQLUSMALLINT second = 0;
        SQLUINTEGER fraction = 0;
        SQLSMALLINT timezoneHour = 0;
        SQLSMALLINT timezoneMinute = 0;
    };


    class Numeric : public SQL_NUMERIC_STRUCT
    {
    public:
        using Base = SQL_NUMERIC_STRUCT;

        Numeric( )
            : Base{}
        {
        }
    };

    struct Money
    {
        LONG moneyHigh = 0;
        ULONG moneyLow = 0;
    };

    struct RowVersion
    {
        Byte value[ 8 ] = {};

        bool operator==( const RowVersion& other ) const
        {
            return *reinterpret_cast< const Int64* >( &value[ 0 ] ) == *reinterpret_cast< const Int64* >( &other.value[ 0 ] );
        }

        bool operator!=( const RowVersion& other ) const
        {
            return *reinterpret_cast< const Int64* >( &value[ 0 ] ) != *reinterpret_cast< const Int64* >( &other.value[ 0 ] );
        }
    };


    /// <summary>
    /// This template implements functionality common to
    /// the ODBC handle wrapper classes
    /// </summary>
    template<ODBC::HandleType handleType>
    class SqlHandle
    {
    public:
        static constexpr ODBC::HandleType HandleType = handleType;
        static constexpr SQLHANDLE InvalidHandle = ( SQLHANDLE )SQL_INVALID_HANDLE;
    private:
        SQLHANDLE sqlHandle_ = InvalidHandle;
        bool destructorClosesHandle_ = true;
    public:
        constexpr SqlHandle() noexcept
        { 

        }
    protected:
        constexpr SqlHandle( SQLHANDLE sqlHandle, bool destructorClosesHandle ) noexcept
            : sqlHandle_( sqlHandle ), destructorClosesHandle_( destructorClosesHandle )
        {

        }
    public:

        SqlHandle( const SqlHandle& other ) = delete;
        constexpr SqlHandle( SqlHandle&& other ) noexcept
            : sqlHandle_( other.sqlHandle_ ), destructorClosesHandle_( other.destructorClosesHandle_ )
        {
            other.sqlHandle_ = nullptr;
            other.destructorClosesHandle_ = false;
        }

        ~SqlHandle( )
        {
            if ( destructorClosesHandle_ )
            {
                Close( );
            }
        }


        SqlHandle& operator = ( const SqlHandle& other ) = delete;
        constexpr SqlHandle& operator = ( SqlHandle&& other ) noexcept
        {
            std::swap( sqlHandle_, other.sqlHandle_ );
            std::swap( destructorClosesHandle_, other.destructorClosesHandle_ );
            return *this;
        }

        constexpr SQLHANDLE Handle( ) const noexcept
        {
            return sqlHandle_;
        }

    protected:
        void ThrowException( SQLRETURN sqlReturn ) const
        {
            if ( sqlReturn < SQL_SUCCESS )
            {
                Internal::ThrowException( sqlReturn, HandleType, sqlHandle_ );
            }
        }

        void ThrowException( SQLRETURN sqlReturn, const wchar_t* function, const wchar_t* file, int line ) const
        {
            if ( sqlReturn < SQL_SUCCESS )
            {
                Internal::ThrowException( sqlReturn, HandleType, sqlHandle_, function, file, line );
            }
        }

        static SQLHANDLE AllocateHandle( SQLHANDLE inputHandle = SQL_NULL_HANDLE )
        {
            SQLHANDLE result = InvalidHandle;
            auto rc = SQLAllocHandle( static_cast<SQLSMALLINT>(HandleType), inputHandle, &result );
            if ( rc != SQL_SUCCESS )
            {
                Internal::ThrowException( rc, HandleType, inputHandle, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return result;
        }


    public:
        void Close( ) noexcept
        {
            if ( sqlHandle_ != InvalidHandle )
            {
                if constexpr ( HandleType == ODBC::HandleType::Connection )
                {
                    auto rc = SQLDisconnect( sqlHandle_ );
                    if ( Failed( static_cast<Result>( rc ) ) )
                    {
                        auto sqlState = Internal::GetSqlState( HandleType, sqlHandle_ );
                        if ( sqlState != L"08003" )
                        {
                            Internal::ThrowException( rc, HandleType, sqlHandle_, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
                        }
                    }
                }
                auto rc = SQLFreeHandle( static_cast<SQLSMALLINT>( HandleType ), sqlHandle_ );
                if ( Failed( static_cast< Result >( rc ) ) )
                {
                    Internal::ThrowException( rc, HandleType, sqlHandle_, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
                }
                sqlHandle_ = InvalidHandle;
            }
        }

        Result Cancel( ) const
        {
            auto rc = SQLCancelHandle( static_cast<SQLSMALLINT>( HandleType ), sqlHandle_ );
            if ( Failed(static_cast<Result>(rc)) )
            {
                Internal::ThrowException( rc, HandleType, Handle( ), CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result CompleteAsync( RETCODE* asyncRetCode ) const
        {
            auto rc = SQLCompleteAsync( static_cast<SQLSMALLINT>( HandleType ), sqlHandle_, asyncRetCode );
            if ( Failed(static_cast<Result>(rc)) )
            {
                Internal::ThrowException( rc, HandleType, Handle( ), CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

    };

    /// <summary>
    /// A descriptor is a collection of metadata that describes the parameters of 
    /// an SQL statement or the columns of a result set, as seen by the application 
    /// or driver.
    /// </summary>
    class Descriptor : public SqlHandle<ODBC::HandleType::Descriptor>
    {
        friend class Statement;
    public:
        using Base = SqlHandle<ODBC::HandleType::Descriptor>;

        

        constexpr Descriptor( )
        {
        }
    private:
        constexpr explicit Descriptor( SQLHANDLE sqlHandle, bool destructorClosesHandle = true )
            : Base( sqlHandle, destructorClosesHandle )
        {
        }
    public:
        /// <summary>
        /// Copies the descriptor information to another descriptor
        /// </summary>
        /// <param name="other">Destination descriptor handle</param>
        /// <returns>Result::Success or Result::SuccessWithInfo</returns>
        Result CopyTo( const Descriptor& other ) const
        {
            auto rc = SQLCopyDesc( Handle( ), other.Handle( ) );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        /// <summary>
        /// Copies the descriptor information from another descriptor
        /// </summary>
        /// <param name="other">Source descriptor handle</param>
        /// <returns>Result::Success or Result::SuccessWithInfo</returns>
        Result CopyFrom( const Descriptor& other ) const
        {
            auto rc = SQLCopyDesc( other.Handle( ), Handle( ) );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        /// <summary>
        /// Retrieves the current value of a single field of a descriptor record
        /// </summary>
        /// <param name="recordNumber">Identifies the descriptor record from which the application seeks information</param>
        /// <param name="fieldIdentifier">Identifies the field of the descriptor whose value is to be returned</param>
        /// <param name="value">Pointer to a buffer that will recieve the value of the requested field</param>
        /// <param name="valueMaxLength"></param>
        /// <param name="valueActualLength"></param>
        /// <returns></returns>
        Result GetFieldW( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier, SQLPOINTER value, SQLINTEGER valueMaxLength, SQLINTEGER* valueActualLength ) const
        {
            auto rc = SQLGetDescFieldW( Handle( ), recordNumber, fieldIdentifier, value, valueMaxLength, valueActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result GetFieldA( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier, SQLPOINTER value, SQLINTEGER valueMaxLength, SQLINTEGER* valueActualLength ) const
        {
            auto rc = SQLGetDescFieldA( Handle( ), recordNumber, fieldIdentifier, value, valueMaxLength, valueActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result GetRecord( SQLSMALLINT recordNumber, SQLWCHAR* name, SQLSMALLINT nameMaxLength, SQLSMALLINT* nameActualLength, SQLSMALLINT* type, SQLSMALLINT* subType, SQLLEN* length, SQLSMALLINT* precision, SQLSMALLINT* scale, SQLSMALLINT* nullable ) const
        {
            auto rc = SQLGetDescRecW( Handle( ), recordNumber, name, nameMaxLength, nameActualLength, type, subType, length, precision, scale, nullable );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result GetRecord( SQLSMALLINT recordNumber, SQLCHAR* name, SQLSMALLINT nameMaxLength, SQLSMALLINT* nameActualLength, SQLSMALLINT* type, SQLSMALLINT* subType, SQLLEN* length, SQLSMALLINT* precision, SQLSMALLINT* scale, SQLSMALLINT* nullable ) const
        {
            auto rc = SQLGetDescRecA( Handle( ), recordNumber, name, nameMaxLength, nameActualLength, type, subType, length, precision, scale, nullable );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SetFieldW( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier, SQLPOINTER value, SQLINTEGER valueLength ) const
        {
            auto rc = SQLSetDescFieldW( Handle( ), recordNumber, fieldIdentifier, value, valueLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result SetFieldA( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier, SQLPOINTER value, SQLINTEGER valueLength ) const
        {
#ifdef SQLSetDescField
#pragma push_macro("SQLSetDescField")
#undef SQLSetDescField
#define SQLSetDescFieldUndeffed
#endif
            auto rc = SQLSetDescField( Handle( ), recordNumber, fieldIdentifier, value, valueLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
#ifdef SQLSetDescFieldUndeffed
#pragma pop_macro("SQLSetDescField")
#endif
        }

        Result SetRecord( SQLSMALLINT recordNumber, SQLSMALLINT type, SQLSMALLINT subType, SQLLEN length, SQLSMALLINT precision, SQLSMALLINT scale, SQLPOINTER data, SQLLEN* dataLength, SQLLEN* indicator ) const
        {
            auto rc = SQLSetDescRec( Handle( ), recordNumber, type, subType, length, precision, scale, data, dataLength, indicator );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
    };



    /// <summary>
    /// <para>
    /// The DataReader class implements an API that is similar to .Net data readers. 
    /// </para>
    /// <para>
    /// It is often used as a base class for classes that contains variables that are bound
    /// to the statement.
    /// </para>
    /// </summary>
    class DataReader
    {
        const Statement* statement_;
    public:
        constexpr DataReader( const Statement* statement ) noexcept
            : statement_( statement )
        { }

        DataReader( const DataReader& other ) = delete;
        DataReader( DataReader&& other ) = delete;
        DataReader& operator = ( const DataReader& other ) = delete;
        DataReader& operator = ( DataReader&& other ) = delete;

        bool Read( ) const
        {
            auto rc = Fetch( );
            return rc != ODBC::Result::NoData;
        }

        [[nodiscard]] SQLHANDLE Handle( ) const noexcept;
        inline Result GetData( SQLUSMALLINT columnOrParameterNumber, SQLSMALLINT targetValueDataType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrTargetValueActualLength ) const;

    protected:
        inline Result Fetch( ) const;
        inline Result FetchScroll( ODBC::Fetch fetchOrientation, SQLLEN fetchOffset ) const;
        
        inline Result BindColumn( SQLUSMALLINT columnNumber, SQLSMALLINT targetType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrLength ) const;


        Result BindBoolean( SQLUSMALLINT columnNumber, bool* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Boolean, targetAddress, sizeof( bool ), nullIndicatorOrActualLength );
        }

        Result BindSByte( SQLUSMALLINT columnNumber, SByte* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::SByte, targetAddress, sizeof( SByte ), nullIndicatorOrActualLength );
        }
        Result BindByte( SQLUSMALLINT columnNumber, Byte* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Byte, targetAddress, sizeof( Byte ), nullIndicatorOrActualLength );
        }

        Result BindInt16( SQLUSMALLINT columnNumber, Int16* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Int16, targetAddress, sizeof( Int16 ), nullIndicatorOrActualLength );
        }
        Result BindUInt16( SQLUSMALLINT columnNumber, UInt16* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::UInt16, targetAddress, sizeof( UInt16 ), nullIndicatorOrActualLength );
        }

        Result BindInt32( SQLUSMALLINT columnNumber, Int32* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Int32, targetAddress, sizeof( Int32 ), nullIndicatorOrActualLength );
        }
        Result BindUInt32( SQLUSMALLINT columnNumber, UInt32* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::UInt32, targetAddress, sizeof( UInt32 ), nullIndicatorOrActualLength );
        }

        Result BindInt64( SQLUSMALLINT columnNumber, Int64* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Int64, targetAddress, sizeof( Int64 ), nullIndicatorOrActualLength );
        }
        Result BindUInt64( SQLUSMALLINT columnNumber, UInt64* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::UInt64, targetAddress, sizeof( UInt64 ), nullIndicatorOrActualLength = nullptr );
        }

        Result BindSingle( SQLUSMALLINT columnNumber, Double* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Single, targetAddress, sizeof( Double ), nullIndicatorOrActualLength );
        }

        Result BindDouble( SQLUSMALLINT columnNumber, Double* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Double, targetAddress, sizeof( Double ), nullIndicatorOrActualLength );
        }

        Result BindString( SQLUSMALLINT columnNumber, SQLPOINTER targetAddress, SQLLEN targetAddressMaxLength, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Char, targetAddress, targetAddressMaxLength, nullIndicatorOrActualLength );
        }
        
        
        Result BindGuid( SQLUSMALLINT columnNumber, Guid* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Guid, targetAddress, sizeof( Guid ), nullIndicatorOrActualLength );
        }
        Result BindTimeStamp( SQLUSMALLINT columnNumber, ODBC::TimeStamp* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::TimeStamp, targetAddress, sizeof( ODBC::TimeStamp ), nullIndicatorOrActualLength );
        }
    public:
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;bool&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] 
        inline std::optional<bool> GetNullableBoolean( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;Byte&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] 
        inline std::optional<Byte> GetNullableByte( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;SByte&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<SByte> GetNullableSByte( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;Int16&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<Int16> GetNullableInt16( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;UInt16&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<UInt16> GetNullableUInt16( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;Int32&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<Int32> GetNullableInt32( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;UInt32&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<UInt32> GetNullableUInt32( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;Int64&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<Int64> GetNullableInt64( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;UInt64&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<UInt64> GetNullableUInt64( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;Numeric&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<Numeric> GetNullableNumeric( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;Numeric&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<Numeric> GetNullableDecimal( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;float&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<float> GetNullableSingle( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;double&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<double> GetNullableDouble( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;Currency&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<Currency> GetNullableCurrency( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;DateTime&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<DateTime> GetNullableDateTime( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;TimestampOffset&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<TimestampOffset> GetNullableTimestampOffset( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;Date&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<Date> GetNullableDate( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;Time&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<Time> GetNullableTime( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;TimeSpan&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<TimeSpan> GetNullableTimeSpan( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;WideString&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<WideString> GetNullableWideString( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;AnsiString&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<AnsiString> GetNullableAnsiString( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;std::vector&ltByte&gt;&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<std::vector<Byte>> GetNullableBinary( SQLUSMALLINT columnNumber ) const;

        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;Guid&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<Guid> GetNullableGuid( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;RowVersion&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline std::optional<RowVersion> GetNullableRowVersion( SQLUSMALLINT columnNumber ) const;

        /// <summary>
        /// Gets the value of the specified column as a bool.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline bool GetBoolean( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a Byte.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline Byte GetByte( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a SByte.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline SByte GetSByte( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as an Int16.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline Int16 GetInt16( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as an UInt16.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline UInt16 GetUInt16( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as an Int32.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline Int32 GetInt32( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as an UInt32.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline UInt32 GetUInt32( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as an Int64.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline Int64 GetInt64( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as an UInt64.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline UInt64 GetUInt64( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a Numeric.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline Numeric GetNumeric( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a Numeric.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline Numeric GetDecimal( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a float.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline float GetSingle( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a double.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline double GetDouble( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a Currency.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline Currency GetCurrency( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DateTime.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline DateTime GetDateTime( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a TimestampOffset.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline TimestampOffset GetTimestampOffset( SQLUSMALLINT columnNumber ) const;

        /// <summary>
        /// Gets the value of the specified column as a Date.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline Date GetDate( SQLUSMALLINT columnNumber ) const;

        /// <summary>
        /// Gets the value of the specified column as a Time.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline Time GetTime( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a TimeSpan.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline TimeSpan GetTimeSpan( SQLUSMALLINT columnNumber ) const;

        /// <summary>
        /// Gets the value of the specified column as a WideString.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline WideString GetWideString( SQLUSMALLINT columnNumber ) const;

        /// <summary>
        /// Gets the value of the specified column as an AnsiString.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline AnsiString GetAnsiString( SQLUSMALLINT columnNumber ) const;

        /// <summary>
        /// Gets the value of the specified column as a std::vector&lt;Byte&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline std::vector<Byte> GetBinary( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a Guid.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline Guid GetGuid( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a RowVersion.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        inline RowVersion GetRowVersion( SQLUSMALLINT columnNumber ) const;
    };


    /// <summary>
    /// <para>
    /// The Statement class is a wrapper for the ODBC statement handle.
    /// </para>
    /// <para>
    /// A statement is most easily thought of as an SQL statement, such as SELECT * FROM Employee. 
    /// However, a statement is more than just an SQL statement - it consists of all of the information 
    /// associated with that SQL statement, such as any result sets created by the statement and 
    /// parameters used in the execution of the statement. A statement does not even need to have an 
    /// application-defined SQL statement. For example, when a catalog function such as SQLTables is 
    /// executed on a statement, it executes a predefined SQL statement that returns a list of table names.
    /// </para>
    /// <para>
    /// Each statement is identified by a statement handle. A statement is associated with a single 
    /// connection, and there can be multiple statements on that connection. Some drivers limit the number 
    /// of active statements they support; the SQL_MAX_CONCURRENT_ACTIVITIES option in SQLGetInfo specifies 
    /// how many active statements a driver supports on a single connection. A statement is defined to be 
    /// active if it has results pending, where results are either a result set or the count of rows affected 
    /// by an INSERT, UPDATE, or DELETE statement, or data is being sent with multiple calls to SQLPutData.
    /// </para>
    /// <para>
    /// Within a piece of code that implements ODBC (the Driver Manager or a driver), the statement handle 
    /// identifies a structure that contains statement information, such as:
    /// </para>
    /// <list type="bullet">
    /// <item>
    /// The statement's state
    /// </item>
    /// <item>
    /// The current statement-level diagnostics
    /// </item>
    /// <item>
    /// The addresses of the application variables bound to the statement's parameters and result set columns
    /// </item>
    /// <item>
    /// The current settings of each statement attribute
    /// </item>
    /// </list>
    /// <para>
    /// Statement handles are used in most ODBC functions. Notably, they are used in the functions to bind 
    /// parameters and result set columns (SQLBindParameter and SQLBindCol), prepare and execute statements 
    /// (SQLPrepare, SQLExecute, and SQLExecDirect), retrieve metadata (SQLColAttribute and SQLDescribeCol), 
    /// fetch results (SQLFetch), and retrieve diagnostics (SQLGetDiagField and SQLGetDiagRec). They are 
    /// also used in catalog functions (SQLColumns, SQLTables, and so on) and a number of other functions.
    /// </para>
    /// <para>
    /// Statement handles are allocated with SQLAllocHandle and freed with SQLFreeHandle.
    /// </para>
    /// </summary>
    class Statement : public SqlHandle<ODBC::HandleType::Statement>
    {
        friend class Connection;
    public:
        using Base = SqlHandle<ODBC::HandleType::Statement>;

        Statement( )
        {
        }
    private:
        constexpr explicit Statement( SQLHANDLE sqlHandle, bool destructorClosesHandle = true )
            : Base( sqlHandle, destructorClosesHandle )
        {
        }
    public:
        Result BindColumn( SQLUSMALLINT columnNumber, SQLSMALLINT targetType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrLength ) const
        {
            auto rc = SQLBindCol( Handle( ), columnNumber, targetType, targetValue, targetValueMaxLength, nullIndicatorOrLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        Result BindCharColumn( SQLUSMALLINT columnNumber, SQLPOINTER targetAddress, SQLLEN targetAddressMaxLength, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Char, targetAddress, targetAddressMaxLength, nullIndicatorOrActualLength );
        }

        Result BindLongColumn( SQLUSMALLINT columnNumber, Int32* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Long, targetAddress, sizeof( Int32 ), nullIndicatorOrActualLength );
        }
        Result BindShortColumn( SQLUSMALLINT columnNumber, Int16* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Short, targetAddress, sizeof( Int16 ), nullIndicatorOrActualLength );
        }
        Result BindSingleColumn( SQLUSMALLINT columnNumber, Double* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Single, targetAddress, sizeof( Double ), nullIndicatorOrActualLength );
        }
        Result BindDoubleColumn( SQLUSMALLINT columnNumber, Double* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Double, targetAddress, sizeof( Double ), nullIndicatorOrActualLength );
        }
        Result BindBooleanColumn( SQLUSMALLINT columnNumber, Byte* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Boolean, targetAddress, sizeof( Byte ), nullIndicatorOrActualLength );
        }
        Result BindInt64Column( SQLUSMALLINT columnNumber, Int64* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Int64, targetAddress, sizeof( Int64 ), nullIndicatorOrActualLength );
        }
        Result BindUInt64Column( SQLUSMALLINT columnNumber, UInt64* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::UInt64, targetAddress, sizeof( UInt64 ), nullIndicatorOrActualLength );
        }
        Result BindInt32Column( SQLUSMALLINT columnNumber, Int32* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Int32, targetAddress, sizeof( Int32 ), nullIndicatorOrActualLength );
        }
        Result BindUInt32Column( SQLUSMALLINT columnNumber, UInt32* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::UInt32, targetAddress, sizeof( UInt32 ), nullIndicatorOrActualLength );
        }
        Result BindInt16Column( SQLUSMALLINT columnNumber, Int16* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Int16, targetAddress, sizeof( Int16 ), nullIndicatorOrActualLength );
        }
        Result BindUInt16Column( SQLUSMALLINT columnNumber, UInt16* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::UInt16, targetAddress, sizeof( UInt16 ), nullIndicatorOrActualLength );
        }
        Result BindSByteColumn( SQLUSMALLINT columnNumber, SByte* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::SByte, targetAddress, sizeof( SByte ), nullIndicatorOrActualLength );
        }
        Result BindByteColumn( SQLUSMALLINT columnNumber, Byte* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Byte, targetAddress, sizeof( Byte ), nullIndicatorOrActualLength );
        }
        Result BindGuidColumn( SQLUSMALLINT columnNumber, Guid* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Guid, targetAddress, sizeof( Guid ), nullIndicatorOrActualLength );
        }
        Result BindTimeStampColumn( SQLUSMALLINT columnNumber, ODBC::TimeStamp* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::TypeTimeStamp, targetAddress, sizeof( ODBC::TimeStamp ), nullIndicatorOrActualLength );
        }


        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, SQLSMALLINT valueType, SQLSMALLINT parameterType, SQLULEN columnSize, SQLSMALLINT decimalDigits, SQLPOINTER parameterValue, SQLLEN parameterValueBufferLength, SQLLEN* lengthOrIndicator ) const
        {
            auto rc = SQLBindParameter( Handle( ), parameterNumber, static_cast<SQLSMALLINT>( parameterDirection ), valueType, parameterType, columnSize, decimalDigits, parameterValue, parameterValueBufferLength, lengthOrIndicator );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result BindBooleanParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, bool* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Boolean, SqlType::Bit, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindSByteParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, SByte* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::SByte, SqlType::TinyInt, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }
        Result BindByteParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Byte* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Byte, SqlType::TinyInt, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindInt16Parameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Int16* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Int16, SqlType::SmallInt, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindUInt16Parameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, UInt16* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::UInt16, SqlType::SmallInt, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindInt32Parameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Int32* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Int32, SqlType::Integer, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindUInt32Parameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, UInt32* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::UInt32, SqlType::Integer, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindInt64Parameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Int64* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Int64, SqlType::BigInt, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindUInt64Parameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, UInt64* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::UInt64, SqlType::BigInt, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, SQLULEN columnSize, char* parameterValue, SQLLEN parameterValueBufferLength, SQLLEN* lengthOrIndicator ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Char, SqlType::Char, columnSize, 0, parameterValue, parameterValueBufferLength, lengthOrIndicator );
            return rc;
        }

        Result BindLongParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, UInt32* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Long, SqlType::Integer, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }
        Result BindShortParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, UInt16* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Long, SqlType::Integer, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindSingleParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Double* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Single, SqlType::Real, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindDoubleParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Double* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Double, SqlType::Double, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        
        Result BindGuidParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Guid* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Guid, SqlType::Guid, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindTimeStampParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, SQLSMALLINT precisionOfFraction, ODBC::TimeStamp* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            SQLSMALLINT columnSize = static_cast<SQLSMALLINT>( 20 ) + precisionOfFraction;
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::TypeTimeStamp, SqlType::TimeStamp, columnSize, precisionOfFraction, parameterValue, 0, lengthOrIndicator );
            return rc;
        }


        Result BulkOperations( ODBC::BulkOperation bulkOperation ) const
        {
            auto rc = SQLBulkOperations( Handle( ), static_cast<SQLSMALLINT>( bulkOperation ) );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result CloseCursor( )
        {
            auto rc = SQLCloseCursor( Handle( ) );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        Result GetColumnAttribute( SQLUSMALLINT columnNumber, SQLUSMALLINT fieldIdentifier, SQLPOINTER value, SQLSMALLINT valueMaxLength, SQLSMALLINT* valueActualLength, SQLLEN* numericAttributeValue ) const
        {
            auto rc = SQLColAttributeW( Handle( ), columnNumber, fieldIdentifier, value, valueMaxLength, valueActualLength, numericAttributeValue );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result GetColumnAttributeAnsi( SQLUSMALLINT columnNumber, SQLUSMALLINT fieldIdentifier, SQLPOINTER value, SQLSMALLINT valueMaxLength, SQLSMALLINT* valueActualLength, SQLLEN* numericAttributeValue ) const
        {
            auto rc = SQLColAttributeA( Handle( ), columnNumber, fieldIdentifier, value, valueMaxLength, valueActualLength, numericAttributeValue );
            if ( Failed( static_cast< Result >( rc ) ) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast< Result >( rc );
        }


        Int64 GetInt64ColumnAttribute( SQLUSMALLINT columnNumber, SQLUSMALLINT fieldIdentifier ) const
        {
            Int64 value = 0;
            GetColumnAttribute( columnNumber, fieldIdentifier, nullptr, 0, nullptr, &value );
            return value;
        }

        bool GetBooleanColumnAttribute( SQLUSMALLINT columnNumber, SQLUSMALLINT fieldIdentifier ) const
        {
            Int64 value = GetInt64ColumnAttribute( columnNumber, fieldIdentifier );
            return value != 0;
        }

        WideString GetWideStringColumnAttribute( SQLUSMALLINT columnNumber, SQLUSMALLINT fieldIdentifier ) const
        {
            wchar_t buffer[ 1024 ];
            buffer[ 0 ] = L'\x0';
            SQLSMALLINT valueActualLength = 0;
            GetColumnAttribute( columnNumber, fieldIdentifier, buffer, sizeof( buffer ), &valueActualLength, nullptr );
            if ( valueActualLength <= sizeof( buffer ) )
            {
                return WideString( buffer, static_cast<size_t>(valueActualLength/sizeof(wchar_t)) );
            }
            WideString result;
            result.SetLength( static_cast< size_t >( valueActualLength / sizeof( wchar_t ) ) );
            GetColumnAttribute( columnNumber, fieldIdentifier, result.data(), valueActualLength, &valueActualLength, nullptr );
            return result;
        }




        /// <summary>
        /// <para>
        /// Returns true if the column is an autoincrementing column, otherwise false.
        /// </para>
        /// This function is valid for numeric data type columns only. An application can insert values
        /// into a row containing an autoincrement column, but typically cannot update values in the column.
        /// </summary>
        /// <para>
        /// When an insert is made into an autoincrement column, a unique value is inserted into the column at 
        /// insert time. The increment is not defined, but is data source-specific. An application should not 
        /// assume that an autoincrement column starts at any particular point or increments by any particular value.
        /// </para>
        /// <para>
        /// </para>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>true if the column is an autoincrementing column, otherwise false.</returns>
        bool ColumnIsAutoIncrement( SQLUSMALLINT columnNumber ) const
        {
            return GetBooleanColumnAttribute( columnNumber, SQL_DESC_AUTO_UNIQUE_VALUE );
        }

        /// <summary>
        /// <para>
        /// Returns the base column name for the result set column. If a base column name does not 
        /// exist (as in the case of columns that are expressions), then this variable contains an empty string.
        /// </para>
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>the base column name for the result set column</returns>
        WideString ColumnBaseName( SQLUSMALLINT columnNumber ) const
        {
            return GetWideStringColumnAttribute( columnNumber, SQL_DESC_BASE_COLUMN_NAME );
        }

        /// <summary>
        /// Returns the name of the base table that contains the column. If the base table name 
        /// cannot be defined or is not applicable, then this variable contains an empty string.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The name of the base table that contains the column.</returns>
        WideString ColumnBaseTableName( SQLUSMALLINT columnNumber ) const
        {
            return GetWideStringColumnAttribute( columnNumber, SQL_DESC_BASE_TABLE_NAME );
        }

        /// <summary>
        /// Returns true if the column is treated as case-sensitive for collations and comparisons,
        /// otherwise false.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>true if the column is treated as case-sensitive.</returns>
        bool ColumnIsCaseSensitive( SQLUSMALLINT columnNumber ) const
        {
            return GetBooleanColumnAttribute( columnNumber, SQL_DESC_CASE_SENSITIVE );
        }

        /// <summary>
        /// The catalog of the table that contains the column. The returned value is 
        /// implementation-defined if the column is an expression or if the column is 
        /// part of a view. If the data source does not support catalogs or the catalog 
        /// name cannot be determined, an empty string is returned.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The name of catalog of the table that contains the column.</returns>
        WideString ColumnCatalogName( SQLUSMALLINT columnNumber ) const
        {
            return GetWideStringColumnAttribute( columnNumber, SQL_DESC_CATALOG_NAME );
        }

        /// <summary>
        /// Returns the concise data type.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>the concise data type.</returns>
        SQLSMALLINT ColumnConciseType( SQLUSMALLINT columnNumber ) const
        {
            return static_cast< SQLSMALLINT >( GetInt64ColumnAttribute( columnNumber, SQL_DESC_CONCISE_TYPE ) );
        }

        /// <summary>
        /// Returns the number of columns available in the result set. This returns 0 if there are no columns in the result set. 
        /// </summary>
        /// <returns>the number of columns available in the result set.</returns>
        size_t ColumnCount( ) const
        {
            return static_cast< size_t >( GetInt64ColumnAttribute( 0, SQL_DESC_COUNT ) );
        }

        /// <summary>
        /// Returns the maximum number of characters required to display data from the column.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The maximum number of characters required to display data from the column.</returns>
        SQLLEN ColumnDisplaySize( SQLUSMALLINT columnNumber ) const
        {
            return GetInt64ColumnAttribute( columnNumber, SQL_DESC_DISPLAY_SIZE );
        }

        /// <summary>
        /// Returns true if the column has a fixed precision and nonzero scale that are data source-specific.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>true if the column has a fixed precision and nonzero scale.</returns>
        bool ColumnHasFixedPrecisionAndScale( SQLUSMALLINT columnNumber ) const
        {
            return GetBooleanColumnAttribute( columnNumber, SQL_DESC_FIXED_PREC_SCALE );
        }

        /// <summary>
        /// <para>
        /// Returns the column label or title.
        /// </para>
        /// <para>
        /// If a column does not have a label, the column name is returned. If the 
        /// column is unlabeled and unnamed, an empty string is returned.
        /// </para>
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The column label or title.</returns>
        WideString ColumnLabel( SQLUSMALLINT columnNumber ) const
        {
            return GetWideStringColumnAttribute( columnNumber, SQL_DESC_LABEL );
        }


        /// <summary>
        /// Returns a numeric value that is either the maximum or actual character length of a character 
        /// string or binary data type. It is the maximum character length for a fixed-length data type, 
        /// or the actual character length for a variable-length data type. Its value always excludes 
        /// the null-termination byte that ends the character string.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The length of the column value.</returns>
        SQLLEN ColumnLength( SQLUSMALLINT columnNumber ) const
        {
            return GetInt64ColumnAttribute( columnNumber, SQL_DESC_LENGTH );
        }


        /// <summary>
        /// Returns the character or characters that the driver recognizes as a prefix for a literal of 
        /// this data type. This field contains an empty string for a data type for which a literal prefix 
        /// is not applicable.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The literal prefix.</returns>
        WideString ColumnLiteralPrefix( SQLUSMALLINT columnNumber ) const
        {
            return GetWideStringColumnAttribute( columnNumber, SQL_DESC_LITERAL_PREFIX );
        }

        /// <summary>
        /// Returns the character or characters that the driver recognizes as a suffix for a 
        /// literal of this data type. This field contains an empty string for a data type 
        /// for which a literal suffix is not applicable.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The literal suffix.</returns>
        WideString ColumnLiteralSuffix( SQLUSMALLINT columnNumber ) const
        {
            return GetWideStringColumnAttribute( columnNumber, SQL_DESC_LITERAL_SUFFIX );
        }

        /// <summary>
        /// Returns the localized (native language) name for the data type that may be 
        /// different from the regular name of the data type. If there is no localized name, 
        /// then an empty string is returned. This field is for display purposes only. 
        /// The character set of the string is locale-dependent and is typically the 
        /// default character set of the server.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The localized (native language) name for the data type.</returns>
        WideString ColumnLocalTypeName( SQLUSMALLINT columnNumber ) const
        {
            return GetWideStringColumnAttribute( columnNumber, SQL_DESC_LOCAL_TYPE_NAME );
        }

        /// <summary>
        /// The column alias, if it applies. If the column alias does not apply, the column name is returned.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The column alias or name.</returns>
        WideString ColumnName( SQLUSMALLINT columnNumber ) const
        {
            return GetWideStringColumnAttribute( columnNumber, SQL_DESC_NAME );
        }


        Result ColumnPrivileges( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameMaxLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameMaxLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameMaxLength, const SQLWCHAR* columnName, SQLSMALLINT columnNameMaxLength ) const
        {
            auto rc = SQLColumnPrivilegesW( Handle( ), const_cast<SQLWCHAR*>(catalogName), catalogNameMaxLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameMaxLength, const_cast<SQLWCHAR*>( tableName ), tableNameMaxLength, const_cast<SQLWCHAR*>( columnName ), columnNameMaxLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result ColumnPrivileges( const SQLCHAR* catalogName, SQLSMALLINT catalogNameMaxLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameMaxLength, const SQLCHAR* tableName, SQLSMALLINT tableNameMaxLength, const SQLCHAR* columnName, SQLSMALLINT columnNameMaxLength ) const
        {
            auto rc = SQLColumnPrivilegesA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameMaxLength, const_cast<SQLCHAR*>( schemaName ), schemaNameMaxLength, const_cast<SQLCHAR*>( tableName ), tableNameMaxLength, const_cast<SQLCHAR*>( columnName ), columnNameMaxLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Columns( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameMaxLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameMaxLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameMaxLength, const SQLWCHAR* columnName, SQLSMALLINT columnNameMaxLength ) const
        {
            auto rc = SQLColumnsW( Handle( ), const_cast<SQLWCHAR*>( catalogName ), catalogNameMaxLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameMaxLength, const_cast<SQLWCHAR*>( tableName ), tableNameMaxLength, const_cast<SQLWCHAR*>( columnName ), columnNameMaxLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result Columns( const SQLCHAR* catalogName, SQLSMALLINT catalogNameMaxLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameMaxLength, const SQLCHAR* tableName, SQLSMALLINT tableNameMaxLength, const SQLCHAR* columnName, SQLSMALLINT columnNameMaxLength ) const
        {
            auto rc = SQLColumnsA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameMaxLength, const_cast<SQLCHAR*>( schemaName ), schemaNameMaxLength, const_cast<SQLCHAR*>( tableName ), tableNameMaxLength, const_cast<SQLCHAR*>( columnName ), columnNameMaxLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result DescribeColumn( SQLUSMALLINT columnNumber, SQLWCHAR* columnName, SQLSMALLINT columnNameMaxLength, SQLSMALLINT* columnNameActualLength, SQLSMALLINT* dataType, SQLULEN* columnSize, SQLSMALLINT* decimalDigits, ODBC::Nullable* nullable ) const
        {
            auto rc = SQLDescribeColW( Handle( ), columnNumber, columnName, columnNameMaxLength, columnNameActualLength, dataType, columnSize, decimalDigits, (SQLSMALLINT*)nullable );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result DescribeColumn( SQLUSMALLINT columnNumber, SQLCHAR* columnName, SQLSMALLINT columnNameMaxLength, SQLSMALLINT* columnNameActualLength, SQLSMALLINT* dataType, SQLULEN* columnSize, SQLSMALLINT* decimalDigits, ODBC::Nullable* nullable ) const
        {
            auto rc = SQLDescribeColA( Handle( ), columnNumber, columnName, columnNameMaxLength, columnNameActualLength, dataType, columnSize, decimalDigits, (SQLSMALLINT*)nullable );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result DescribeParameter( SQLUSMALLINT parameterNumber, SQLSMALLINT* dataType, SQLULEN *parameterSize, SQLSMALLINT* decimalDigits, ODBC::Nullable* nullable ) const
        {
            auto rc = SQLDescribeParam( Handle( ), parameterNumber, dataType, parameterSize, decimalDigits, (SQLSMALLINT*)nullable );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result ExecDirect( const SQLWCHAR* statementText, SQLINTEGER statementTextLength = SQL_NTS ) const
        {
            auto rc = SQLExecDirectW( Handle( ), const_cast<SQLWCHAR*>( statementText ), statementTextLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result ExecDirect( const SQLCHAR* statementText, SQLINTEGER statementTextLength = SQL_NTS ) const
        {
            auto rc = SQLExecDirectA( Handle( ), const_cast<SQLCHAR*>( statementText ), statementTextLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Execute( ) const
        {
            auto rc = SQLExecute( Handle( ) );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        template<typename ReaderType>
        requires std::is_base_of_v<DataReader, ReaderType>
            std::unique_ptr<ReaderType> CreateReader( ) const
        {
            auto result = std::make_unique<ReaderType>( this );
            return result;
        }


        template<typename ReaderType = DataReader>
        requires std::is_base_of_v<DataReader, ReaderType>
            std::unique_ptr<ReaderType> ExecuteReader( ) const
        {
            auto result = CreateReader<ReaderType>( );
            Execute( );
            return result;
        }
        template<typename ReaderType = DataReader>
        requires std::is_base_of_v<DataReader, ReaderType>
            std::unique_ptr<ReaderType> ExecuteReader( const SQLWCHAR* statementText, SQLINTEGER statementTextLength = SQL_NTS ) const
        {
            auto result = CreateReader<ReaderType>( );
            ExecDirect( statementText, statementTextLength );
            return result;
        }
        template<typename ReaderType = DataReader>
        requires std::is_base_of_v<DataReader, ReaderType>
            std::unique_ptr<ReaderType> ExecuteReader( const SQLCHAR* statementText, SQLINTEGER statementTextLength = SQL_NTS ) const
        {
            auto result = CreateReader<ReaderType>( );
            ExecDirect( statementText, statementTextLength );
            return result;
        }



        Result Fetch( ) const
        {
            auto rc = SQLFetch( Handle( ) );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result FetchScroll( ODBC::Fetch fetchOrientation, SQLLEN fetchOffset ) const
        {
            auto rc = SQLFetchScroll( Handle( ), static_cast<SQLSMALLINT>( fetchOrientation ), fetchOffset );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result ForeignKeys( const SQLWCHAR* primaryKeyCatalogName, SQLSMALLINT primaryKeyCatalogNameLength,
                            const SQLWCHAR* primaryKeySchemaName, SQLSMALLINT primaryKeySchemaNameLength,
                            const SQLWCHAR* primaryKeyTableName, SQLSMALLINT primaryKeyTableNameLength,
                            const SQLWCHAR* foreignKeyCatalogName, SQLSMALLINT foreignKeyCatalogNameLength,
                            const SQLWCHAR* foreignKeySchemaName, SQLSMALLINT foreignKeySchemaNameLength,
                            const SQLWCHAR* foreignKeyTableName, SQLSMALLINT foreignKeyTableNameLength ) const
        {
            auto rc = SQLForeignKeysW( Handle( ), const_cast<SQLWCHAR*>( primaryKeyCatalogName ), primaryKeyCatalogNameLength,
                const_cast<SQLWCHAR*>( primaryKeySchemaName ), primaryKeySchemaNameLength,
                const_cast<SQLWCHAR*>( primaryKeyTableName ), primaryKeyTableNameLength,
                const_cast<SQLWCHAR*>( foreignKeyCatalogName ), foreignKeyCatalogNameLength,
                const_cast<SQLWCHAR*>( foreignKeySchemaName ), foreignKeySchemaNameLength,
                const_cast<SQLWCHAR*>( foreignKeyTableName ), foreignKeyTableNameLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result ForeignKeys( const SQLCHAR* primaryKeyCatalogName, SQLSMALLINT primaryKeyCatalogNameLength,
            const SQLCHAR* primaryKeySchemaName, SQLSMALLINT primaryKeySchemaNameLength,
            const SQLCHAR* primaryKeyTableName, SQLSMALLINT primaryKeyTableNameLength,
            const SQLCHAR* foreignKeyCatalogName, SQLSMALLINT foreignKeyCatalogNameLength,
            const SQLCHAR* foreignKeySchemaName, SQLSMALLINT foreignKeySchemaNameLength,
            const SQLCHAR* foreignKeyTableName, SQLSMALLINT foreignKeyTableNameLength ) const
        {
            auto rc = SQLForeignKeysA( Handle( ), const_cast<SQLCHAR*>( primaryKeyCatalogName ), primaryKeyCatalogNameLength,
                const_cast<SQLCHAR*>( primaryKeySchemaName ), primaryKeySchemaNameLength,
                const_cast<SQLCHAR*>( primaryKeyTableName ), primaryKeyTableNameLength,
                const_cast<SQLCHAR*>( foreignKeyCatalogName ), foreignKeyCatalogNameLength,
                const_cast<SQLCHAR*>( foreignKeySchemaName ), foreignKeySchemaNameLength,
                const_cast<SQLCHAR*>( foreignKeyTableName ), foreignKeyTableNameLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

    private:
        Result FreeStmt( SQLUSMALLINT option ) const
        {
            auto rc = SQLFreeStmt( Handle( ), option );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
    public:
        /// <summary>
        /// Sets the SQL_DESC_COUNT field of the ARD to 0, releasing all column 
        /// buffers bound by BindColumn for the statement. 
        /// </summary>
        /// <remarks>
        /// This does not unbind the bookmark column; to do that, the SQL_DESC_DATA_PTR 
        /// field of the ARD for the bookmark column is set to NULL. Notice that if 
        /// this operation is performed on an explicitly allocated descriptor 
        /// that is shared by more than one statement, the operation will affect the 
        /// bindings of all statements that share the descriptor.
        /// </remarks>
        Result Unbind( ) const
        {
            return FreeStmt( SQL_UNBIND );
        }

        /// <summary>
        /// Sets the SQL_DESC_COUNT field of the APD to 0, releasing all parameter buffers 
        /// set by BindParameter for the statement. 
        /// </summary>
        /// <remarks>
        /// If this operation is performed on an explicitly allocated descriptor that is 
        /// shared by more than one statement, this operation will affect the bindings of 
        /// all the statements that share the descriptor.
        /// </remarks>
        Result ResetParameters( ) const
        {
            return FreeStmt( SQL_RESET_PARAMS );
        }


        Result CursorName( SQLWCHAR* cursorName, SQLSMALLINT cursorNameMaxLength, SQLSMALLINT* cursorNameActualLength ) const
        {
            auto rc = SQLGetCursorNameW( Handle(), cursorName, cursorNameMaxLength, cursorNameActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result CursorName( SQLCHAR* cursorName, SQLSMALLINT cursorNameMaxLength, SQLSMALLINT* cursorNameActualLength ) const
        {
            auto rc = SQLGetCursorNameA( Handle( ), cursorName, cursorNameMaxLength, cursorNameActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result GetData( SQLUSMALLINT columnOrParameterNumber, SQLSMALLINT targetValueDataType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrTargetValueActualLength ) const
        {
            auto rc = SQLGetData( Handle( ), columnOrParameterNumber, targetValueDataType, targetValue, targetValueMaxLength, nullIndicatorOrTargetValueActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        [[nodiscard]]
        std::optional<bool> GetNullableBoolean( SQLUSMALLINT columnNumber ) const
        {
            bool value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Boolean, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }
        [[nodiscard]]
        std::optional<Byte> GetNullableByte( SQLUSMALLINT columnNumber ) const
        {
            Byte value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Byte, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<SByte> GetNullableSByte( SQLUSMALLINT columnNumber ) const
        {
            SByte value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::SByte, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<Int16> GetNullableInt16( SQLUSMALLINT columnNumber ) const
        {
            Int16 value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Int16, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<UInt16> GetNullableUInt16( SQLUSMALLINT columnNumber ) const
        {
            Int16 value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::UInt16, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<Int32> GetNullableInt32( SQLUSMALLINT columnNumber ) const
        {
            Int32 value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Int32, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<UInt32> GetNullableUInt32( SQLUSMALLINT columnNumber ) const
        {
            UInt32 value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::UInt32, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<Int64> GetNullableInt64( SQLUSMALLINT columnNumber ) const
        {
            Int64 value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Int64, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<UInt64> GetNullableUInt64( SQLUSMALLINT columnNumber ) const
        {
            UInt64 value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::UInt64, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<Numeric> GetNullableNumeric( SQLUSMALLINT columnNumber ) const
        {
            Numeric value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Numeric, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<Numeric> GetNullableDecimal( SQLUSMALLINT columnNumber ) const
        {
            return GetNullableNumeric( columnNumber );
        }


        [[nodiscard]]
        std::optional<float> GetNullableSingle( SQLUSMALLINT columnNumber ) const
        {
            float value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Single, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<double> GetNullableDouble( SQLUSMALLINT columnNumber ) const
        {
            double value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Double, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<Currency> GetNullableCurrency( SQLUSMALLINT columnNumber ) const
        {
            Money value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Binary, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            if ( indicator == 8 )
            {
                return std::bit_cast< Currency >( ( static_cast< Int64 >( value.moneyHigh ) << 32 ) + static_cast< Int64 >( value.moneyLow ) );
            }
            else
            {
                return std::bit_cast< Currency >( static_cast< Int64 >( value.moneyHigh ) );
            }
        }

        [[nodiscard]]
        std::optional<DateTime> GetNullableDateTime( SQLUSMALLINT columnNumber ) const
        {
            TimeStamp value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::TypeTimeStamp, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value.ToDateTime( );
        }

        [[nodiscard]]
        std::optional<TimestampOffset> GetNullableTimestampOffset( SQLUSMALLINT columnNumber ) const
        {
            TimestampOffset value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Binary, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<Date> GetNullableDate( SQLUSMALLINT columnNumber ) const
        {
            Date value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Date, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<Time> GetNullableTime( SQLUSMALLINT columnNumber ) const
        {
            Time value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Time, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<TimeSpan> GetNullableTimeSpan( SQLUSMALLINT columnNumber ) const
        {
            Interval value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::IntervalDayToSecond, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value.ToTimeSpan( );
        }

        [[nodiscard]]
        std::optional<WideString> GetNullableWideString( SQLUSMALLINT columnNumber ) const
        {
            SQLLEN indicator;
            wchar_t buffer[ 4096 ];
            GetData( columnNumber, NativeType::WideChar, &buffer, sizeof( buffer ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            if ( indicator == 0 )
            {
                return WideString( );
            }
            if ( indicator != SQL_NO_TOTAL )
            {
                WideString result( buffer, static_cast< size_t >( indicator / 2 ) );
                return result;
            }
            else
            {
                WideString result( buffer, sizeof( buffer ) / 2 );
                for ( ;;)
                {
                    auto rc = GetData( columnNumber, NativeType::WideChar, &buffer, sizeof( buffer ), &indicator );

                    size_t charCount = ( indicator == SQL_NO_TOTAL ) ? ( sizeof( buffer ) / sizeof( wchar_t ) ) - 1 : indicator / 2;
                    result.Append( buffer, charCount );
                    if ( rc == Result::Success )
                    {
                        break;
                    }
                }
                return result;
            }
        }

        [[nodiscard]]
        std::optional<AnsiString> GetNullableAnsiString( SQLUSMALLINT columnNumber ) const
        {
            SQLLEN indicator;
            char buffer[ 8192 ];
            GetData( columnNumber, NativeType::Char, &buffer, sizeof( buffer ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            if ( indicator == 0 )
            {
                return AnsiString( );
            }
            if ( indicator != SQL_NO_TOTAL )
            {
                AnsiString result( buffer, static_cast< size_t >( indicator ) );
                return result;
            }
            else
            {
                AnsiString result( buffer, sizeof( buffer ) );
                for ( ;;)
                {
                    auto rc = GetData( columnNumber, NativeType::Char, &buffer, sizeof( buffer ), &indicator );

                    size_t charCount = ( indicator == SQL_NO_TOTAL ) ? sizeof( buffer ) - 1 : indicator;
                    result.Append( buffer, charCount );
                    if ( rc == Result::Success )
                    {
                        break;
                    }
                }
                return result;
            }
        }

        [[nodiscard]]
        std::optional<std::vector<Byte>> GetNullableBinary( SQLUSMALLINT columnNumber ) const
        {
            SQLLEN indicator;
            Byte buffer[ 8192 ];
            GetData( columnNumber, NativeType::Binary, &buffer, sizeof( buffer ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            if ( indicator == 0 )
            {
                return std::vector<Byte>( );
            }
            if ( indicator != SQL_NO_TOTAL )
            {
                std::vector<Byte> result( buffer, buffer + static_cast< size_t >( indicator ) );
                return result;
            }
            else
            {
                std::vector<Byte> result( buffer, buffer + sizeof( buffer ) );
                for ( ;;)
                {
                    auto rc = GetData( columnNumber, NativeType::Binary, &buffer, sizeof( buffer ), &indicator );

                    size_t byteCount = ( indicator == SQL_NO_TOTAL ) ? sizeof( buffer ) : indicator;
                    result.insert( result.end( ), buffer, buffer + byteCount );
                    if ( rc == Result::Success )
                    {
                        break;
                    }
                }
                return result;
            }
        }


        [[nodiscard]]
        std::optional<Guid> GetNullableGuid( SQLUSMALLINT columnNumber ) const
        {
            Guid value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Guid, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }

        [[nodiscard]]
        std::optional<RowVersion> GetNullableRowVersion( SQLUSMALLINT columnNumber ) const
        {
            RowVersion value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Binary, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            return value;
        }


        [[nodiscard]]
        bool GetBoolean( SQLUSMALLINT columnNumber ) const
        {
            bool value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Boolean, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }
        [[nodiscard]]
        Byte GetByte( SQLUSMALLINT columnNumber ) const
        {
            Byte value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Byte, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        SByte GetSByte( SQLUSMALLINT columnNumber ) const
        {
            SByte value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::SByte, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        Int16 GetInt16( SQLUSMALLINT columnNumber ) const
        {
            Int16 value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Int16, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        UInt16 GetUInt16( SQLUSMALLINT columnNumber ) const
        {
            Int16 value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::UInt16, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        Int32 GetInt32( SQLUSMALLINT columnNumber ) const
        {
            Int32 value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Int32, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        UInt32 GetUInt32( SQLUSMALLINT columnNumber ) const
        {
            UInt32 value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::UInt32, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        Int64 GetInt64( SQLUSMALLINT columnNumber ) const
        {
            Int64 value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Int64, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        UInt64 GetUInt64( SQLUSMALLINT columnNumber ) const
        {
            UInt64 value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::UInt64, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        Numeric GetNumeric( SQLUSMALLINT columnNumber ) const
        {
            Numeric value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Numeric, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        Numeric GetDecimal( SQLUSMALLINT columnNumber ) const
        {
            return GetNumeric( columnNumber );
        }


        [[nodiscard]]
        float GetSingle( SQLUSMALLINT columnNumber ) const
        {
            float value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Single, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        double GetDouble( SQLUSMALLINT columnNumber ) const
        {
            double value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Double, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        Currency GetCurrency( SQLUSMALLINT columnNumber ) const
        {
            Money value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Binary, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            if ( indicator == 8 )
            {
                return std::bit_cast< Currency >( ( static_cast< Int64 >( value.moneyHigh ) << 32 ) + static_cast< Int64 >( value.moneyLow ) );
            }
            else
            {
                return std::bit_cast< Currency >( static_cast< Int64 >( value.moneyHigh ) );
            }
        }


        [[nodiscard]]
        DateTime GetDateTime( SQLUSMALLINT columnNumber ) const
        {
            TimeStamp value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::TypeTimeStamp, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value.ToDateTime( );
        }

        [[nodiscard]]
        TimestampOffset GetTimestampOffset( SQLUSMALLINT columnNumber ) const
        {
            TimestampOffset value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Binary, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }



        [[nodiscard]]
        Date GetDate( SQLUSMALLINT columnNumber ) const
        {
            Date value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Date, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        Time GetTime( SQLUSMALLINT columnNumber ) const
        {
            Time value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Time, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        TimeSpan GetTimeSpan( SQLUSMALLINT columnNumber ) const
        {
            Interval value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::IntervalDayToSecond, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value.ToTimeSpan( );
        }

        [[nodiscard]]
        WideString GetWideString( SQLUSMALLINT columnNumber ) const
        {
            SQLLEN indicator;
            wchar_t buffer[ 4096 ];
            GetData( columnNumber, NativeType::WideChar, &buffer, sizeof( buffer ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            if ( indicator == 0 )
            {
                return WideString( );
            }
            if ( indicator != SQL_NO_TOTAL )
            {
                WideString result( buffer, static_cast< size_t >( indicator / 2 ) );
                return result;
            }
            else
            {
                WideString result( buffer, sizeof( buffer ) / 2 );
                for ( ;;)
                {
                    auto rc = GetData( columnNumber, NativeType::WideChar, &buffer, sizeof( buffer ), &indicator );

                    size_t charCount = ( indicator == SQL_NO_TOTAL ) ? ( sizeof( buffer ) / sizeof( wchar_t ) ) - 1 : indicator / 2;
                    result.Append( buffer, charCount );
                    if ( rc == Result::Success )
                    {
                        break;
                    }
                }
                return result;
            }
        }

        [[nodiscard]]
        AnsiString GetAnsiString( SQLUSMALLINT columnNumber ) const
        {
            SQLLEN indicator;
            char buffer[ 8192 ];
            GetData( columnNumber, NativeType::Char, &buffer, sizeof( buffer ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            if ( indicator == 0 )
            {
                return AnsiString( );
            }
            if ( indicator != SQL_NO_TOTAL )
            {
                AnsiString result( buffer, static_cast< size_t >( indicator ) );
                return result;
            }
            else
            {
                AnsiString result( buffer, sizeof( buffer ) );
                for ( ;;)
                {
                    auto rc = GetData( columnNumber, NativeType::Char, &buffer, sizeof( buffer ), &indicator );

                    size_t charCount = ( indicator == SQL_NO_TOTAL ) ? sizeof( buffer ) - 1 : indicator;
                    result.Append( buffer, charCount );
                    if ( rc == Result::Success )
                    {
                        break;
                    }
                }
                return result;
            }
        }

        [[nodiscard]]
        std::vector<Byte> GetBinary( SQLUSMALLINT columnNumber ) const
        {
            SQLLEN indicator;
            Byte buffer[ 8192 ];
            GetData( columnNumber, NativeType::Binary, &buffer, sizeof( buffer ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            if ( indicator == 0 )
            {
                return std::vector<Byte>( );
            }
            if ( indicator != SQL_NO_TOTAL )
            {
                std::vector<Byte> result( buffer, buffer + static_cast< size_t >( indicator ) );
                return result;
            }
            else
            {
                std::vector<Byte> result( buffer, buffer + sizeof( buffer ) );
                for ( ;;)
                {
                    auto rc = GetData( columnNumber, NativeType::Binary, &buffer, sizeof( buffer ), &indicator );

                    size_t byteCount = ( indicator == SQL_NO_TOTAL ) ? sizeof( buffer ) : indicator;
                    result.insert( result.end( ), buffer, buffer + byteCount );
                    if ( rc == Result::Success )
                    {
                        break;
                    }
                }
                return result;
            }
        }


        [[nodiscard]]
        Guid GetGuid( SQLUSMALLINT columnNumber ) const
        {
            Guid value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Guid, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        [[nodiscard]]
        RowVersion GetRowVersion( SQLUSMALLINT columnNumber ) const
        {
            RowVersion value;
            SQLLEN indicator;
            GetData( columnNumber, NativeType::Binary, &value, sizeof( value ), &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }



        Result GetAttributeW( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueBufferLength, SQLINTEGER* valueActualLength ) const
        {
            auto rc = SQLGetStmtAttrW( Handle( ), attributeId, value, valueBufferLength, valueActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result GetAttributeA( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueBufferLength, SQLINTEGER* valueActualLength ) const
        {
            auto rc = SQLGetStmtAttrA( Handle( ), attributeId, value, valueBufferLength, valueActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SetAttributeW( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueLength ) const
        {
            auto rc = SQLSetStmtAttrW( Handle( ), attributeId, value, valueLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result SetAttributeA( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueLength ) const
        {
#ifdef SQLSetStmtAttr
#pragma push_macro("SQLSetStmtAttr")
#define SQLSetStmtAttrUndeffed
#undef SQLSetStmtAttr
#endif
            auto rc = SQLSetStmtAttr( Handle( ), attributeId, value, valueLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
#ifdef SQLSetStmtAttrUndeffed
#pragma pop_macro("SQLSetStmtAttr")
#endif
        }

        Result SetApplicationParameterDescriptor( const Descriptor& applicationParameterDescriptor ) const
        {
            auto rc = SetAttributeW( SQL_ATTR_APP_PARAM_DESC, applicationParameterDescriptor.Handle(), 0 );
            return rc;
        }
        Descriptor ApplicationParameterDescriptor( ) const
        {
            SQLHANDLE applicationParameterDescriptor = nullptr;
            GetAttributeW( SQL_ATTR_APP_PARAM_DESC, &applicationParameterDescriptor, SQL_IS_POINTER, nullptr );
            return Descriptor( applicationParameterDescriptor, false );
        }

        Result SetApplicationRowDescriptor( const Descriptor& applicationRowDescriptor ) const
        {
            auto rc = SetAttributeW( SQL_ATTR_APP_ROW_DESC, applicationRowDescriptor.Handle( ), 0 );
            return rc;
        }
        Descriptor ApplicationRowDescriptor( ) const
        {
            SQLHANDLE applicationRowDescriptor = nullptr;
            GetAttributeW( SQL_ATTR_APP_ROW_DESC, &applicationRowDescriptor, SQL_IS_POINTER, nullptr );
            return Descriptor( applicationRowDescriptor, false );
        }




        Result SetBindByColumn( ) const
        {
            auto rc = SetAttributeW( SQL_ATTR_PARAM_BIND_TYPE, SQL_PARAM_BIND_BY_COLUMN, 0 );
            return rc;
        }


        Result SetParameterArraySize( UInt64 parameterArraySize ) const
        {
            auto rc = SetAttributeW( SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)parameterArraySize, 0 );
            return rc;
        }

        Result GetParameterArraySize( UInt64* parameterArraySize ) const
        {
            auto rc = GetAttributeW( SQL_ATTR_PARAMSET_SIZE, parameterArraySize, 0, nullptr );
            return rc;
        }

        UInt64 ParameterArraySize( ) const
        {
            UInt64 parameterArraySize;
            GetParameterArraySize( &parameterArraySize );
            return parameterArraySize;
        }


        Result SetParameterStatusArray( SQLUSMALLINT* parameterStatusArray ) const
        {
            auto rc = SetAttributeW( SQL_ATTR_PARAM_STATUS_PTR, (SQLPOINTER)parameterStatusArray, 0 );
            return rc;
        }

        Result SetParametersProcessed( SQLULEN* parametersProcessed ) const
        {
            auto rc = SetAttributeW( SQL_ATTR_PARAMS_PROCESSED_PTR, (SQLPOINTER)parametersProcessed, 0 );
            return rc;
        }
        


        Result SetRowArraySize( UInt64 rowArraySize ) const
        {
            auto rc = SetAttributeW( SQL_ATTR_ROW_ARRAY_SIZE, (SQLPOINTER)rowArraySize, 0 );
            return rc;
        }

        Result SetRowsFetched( SQLULEN* rowsFetched ) const
        {
            auto rc = SetAttributeW( SQL_ATTR_ROWS_FETCHED_PTR, (SQLPOINTER)rowsFetched, 0 );
            return rc;
        }



        Result GetTypeInfoW( SQLSMALLINT dataType ) const
        {
            auto rc = SQLGetTypeInfoW( Handle( ), dataType );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result GetTypeInfoA( SQLSMALLINT dataType ) const
        {
            auto rc = SQLGetTypeInfoA( Handle( ), dataType );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result MoreResults( ) const
        {
            auto rc = SQLMoreResults( Handle( ) );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result NumParams( SQLSMALLINT* result ) const
        {
            auto rc = SQLNumParams( Handle( ), result );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result NumResultCols( SQLSMALLINT* result ) const
        {
            auto rc = SQLNumResultCols( Handle( ), result );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result ParamData( SQLPOINTER* valuePointer ) const
        {
            auto rc = SQLParamData( Handle( ), valuePointer );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Prepare( const SQLWCHAR* statement, SQLINTEGER statementLength = SQL_NTS ) const
        {
            auto rc = SQLPrepareW( Handle( ), const_cast<SQLWCHAR*>( statement ), statementLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Prepare( const SQLCHAR* statement, SQLINTEGER statementLength = SQL_NTS ) const
        {
            auto rc = SQLPrepareA( Handle( ), const_cast<SQLCHAR*>( statement ), statementLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        Result PrimaryKeys( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameLength ) const
        {
            auto rc = SQLPrimaryKeysW( Handle( ), const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( tableName ), tableNameLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result PrimaryKeys( const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* tableName, SQLSMALLINT tableNameLength ) const
        {
            auto rc = SQLPrimaryKeysA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( tableName ), tableNameLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result ProcedureColumns( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* procedureName, SQLSMALLINT procedureNameLength, const SQLWCHAR* columnName, SQLSMALLINT columnNameLength ) const
        {
            auto rc = SQLProcedureColumnsW( Handle( ), const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( procedureName ), procedureNameLength, const_cast<SQLWCHAR*>( columnName ), columnNameLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result ProcedureColumns( const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* procedureName, SQLSMALLINT procedureNameLength, const SQLCHAR* columnName, SQLSMALLINT columnNameLength ) const
        {
            auto rc = SQLProcedureColumnsA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( procedureName ), procedureNameLength, const_cast<SQLCHAR*>( columnName ), columnNameLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Procedures( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* procedureName, SQLSMALLINT procedureNameLength ) const
        {
            auto rc = SQLProceduresW( Handle(), const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( procedureName ), procedureNameLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result Procedures( const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* procedureName, SQLSMALLINT procedureNameLength ) const
        {
            auto rc = SQLProceduresA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( procedureName ), procedureNameLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result PutData( SQLPOINTER data, SQLLEN nullIndicatorOrDataLength ) const
        {
            auto rc = SQLPutData( Handle(), data, nullIndicatorOrDataLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        Result RowCount( SQLLEN* result ) const
        {
            auto rc = SQLRowCount( Handle( ), result );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SetCursorName( const SQLWCHAR* cursorName, SQLSMALLINT cursorNameLength ) const
        {
            auto rc = SQLSetCursorNameW( Handle( ), const_cast<SQLWCHAR*>( cursorName ), cursorNameLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SetCursorName( const SQLCHAR* cursorName, SQLSMALLINT cursorNameLength ) const
        {
            auto rc = SQLSetCursorNameA( Handle( ), const_cast<SQLCHAR*>( cursorName ), cursorNameLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SetPosition( SQLSETPOSIROW rowNumber, SQLUSMALLINT operation, SQLUSMALLINT lockType ) const
        {
            auto rc = SQLSetPos( Handle( ), rowNumber, operation, lockType );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SpecialColumns( SQLSMALLINT identifierType, const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameLength, SQLSMALLINT scope, SQLSMALLINT nullable ) const
        {
            auto rc = SQLSpecialColumnsW( Handle( ), identifierType, const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( tableName ), tableNameLength, scope, nullable );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result SpecialColumns( SQLSMALLINT identifierType, const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* tableName, SQLSMALLINT tableNameLength, SQLSMALLINT scope, SQLSMALLINT nullable ) const
        {
            auto rc = SQLSpecialColumnsA( Handle( ), identifierType, const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( tableName ), tableNameLength, scope, nullable );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Statistics( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameLength, SQLSMALLINT unique, SQLSMALLINT options ) const
        {
            auto rc = SQLStatisticsW( Handle( ), const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( tableName ), tableNameLength, unique, options );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result Statistics( const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* tableName, SQLSMALLINT tableNameLength, SQLSMALLINT unique, SQLSMALLINT options ) const
        {
            auto rc = SQLStatisticsA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( tableName ), tableNameLength, unique, options );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result TablePrivileges( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameLength ) const
        {
            auto rc = SQLTablePrivilegesW( Handle( ), const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( tableName ), tableNameLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result TablePrivileges( const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* tableName, SQLSMALLINT tableNameLength ) const
        {
            auto rc = SQLTablePrivilegesA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( tableName ), tableNameLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Tables( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameLength, const SQLWCHAR* tableTypes, SQLSMALLINT tableTypesLength ) const
        {
            auto rc = SQLTablesW( Handle( ), const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( tableName ), tableNameLength, const_cast<SQLWCHAR*>( tableTypes ), tableTypesLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result Tables( const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* tableName, SQLSMALLINT tableNameLength, const SQLCHAR* tableTypes, SQLSMALLINT tableTypesLength ) const
        {
            auto rc = SQLTablesA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( tableName ), tableNameLength, const_cast<SQLCHAR*>( tableTypes ), tableTypesLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
    };



    inline Result DataReader::Fetch( ) const
    {
        return statement_->Fetch( );
    }
    inline Result DataReader::FetchScroll( ODBC::Fetch fetchOrientation, SQLLEN fetchOffset ) const
    {
        return statement_->FetchScroll( fetchOrientation, fetchOffset );
    }
    inline Result DataReader::BindColumn( SQLUSMALLINT columnNumber, SQLSMALLINT targetType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrLength ) const
    {
        return statement_->BindColumn( columnNumber, targetType, targetValue, targetValueMaxLength, nullIndicatorOrLength );
    }

    [[nodiscard]] 
    inline SQLHANDLE DataReader::Handle( ) const noexcept
    {
        return statement_->Handle( );
    }

    inline Result DataReader::GetData( SQLUSMALLINT columnOrParameterNumber, SQLSMALLINT targetValueDataType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrTargetValueActualLength ) const
    {
        return statement_->GetData( columnOrParameterNumber, targetValueDataType, targetValue, targetValueMaxLength, nullIndicatorOrTargetValueActualLength );
    }

    [[nodiscard]]
    inline std::optional<bool> DataReader::GetNullableBoolean( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableBoolean( columnNumber );
    }
    [[nodiscard]]
    inline std::optional<Byte> DataReader::GetNullableByte( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableByte( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<SByte> DataReader::GetNullableSByte( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableSByte( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<Int16> DataReader::GetNullableInt16( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableInt16( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<UInt16> DataReader::GetNullableUInt16( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableUInt16( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<Int32> DataReader::GetNullableInt32( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableInt32( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<UInt32> DataReader::GetNullableUInt32( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableUInt32( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<Int64> DataReader::GetNullableInt64( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableInt64( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<UInt64> DataReader::GetNullableUInt64( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableUInt64( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<Numeric> DataReader::GetNullableNumeric( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableNumeric( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<Numeric> DataReader::GetNullableDecimal( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableDecimal( columnNumber );
    }


    [[nodiscard]]
    inline std::optional<float> DataReader::GetNullableSingle( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableSingle( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<double> DataReader::GetNullableDouble( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableDouble( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<Currency> DataReader::GetNullableCurrency( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableCurrency( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<DateTime> DataReader::GetNullableDateTime( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableDateTime( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<TimestampOffset> DataReader::GetNullableTimestampOffset( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableTimestampOffset( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<Date> DataReader::GetNullableDate( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableDate( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<Time> DataReader::GetNullableTime( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableTime( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<TimeSpan> DataReader::GetNullableTimeSpan( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableTimeSpan( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<WideString> DataReader::GetNullableWideString( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableWideString( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<AnsiString> DataReader::GetNullableAnsiString( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableAnsiString( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<std::vector<Byte>> DataReader::GetNullableBinary( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableBinary( columnNumber );
    }


    [[nodiscard]]
    inline std::optional<Guid> DataReader::GetNullableGuid( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableGuid( columnNumber );
    }

    [[nodiscard]]
    inline std::optional<RowVersion> DataReader::GetNullableRowVersion( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNullableRowVersion( columnNumber );
    }

    [[nodiscard]]
    inline bool DataReader::GetBoolean( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetBoolean( columnNumber );
    }
    [[nodiscard]]
    inline Byte DataReader::GetByte( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetByte( columnNumber );
    }

    [[nodiscard]]
    inline SByte DataReader::GetSByte( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetSByte( columnNumber );
    }

    [[nodiscard]]
    inline Int16 DataReader::GetInt16( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetInt16( columnNumber );
    }

    [[nodiscard]]
    inline UInt16 DataReader::GetUInt16( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetUInt16( columnNumber );
    }

    [[nodiscard]]
    inline Int32 DataReader::GetInt32( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetInt32( columnNumber );
    }

    [[nodiscard]]
    inline UInt32 DataReader::GetUInt32( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetUInt32( columnNumber );
    }

    [[nodiscard]]
    inline Int64 DataReader::GetInt64( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetInt64( columnNumber );
    }

    [[nodiscard]]
    inline UInt64 DataReader::GetUInt64( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetUInt64( columnNumber );
    }

    [[nodiscard]]
    inline Numeric DataReader::GetNumeric( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetNumeric( columnNumber );
    }

    [[nodiscard]]
    inline Numeric DataReader::GetDecimal( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDecimal( columnNumber );
    }


    [[nodiscard]]
    inline float DataReader::GetSingle( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetSingle( columnNumber );
    }

    [[nodiscard]]
    inline double DataReader::GetDouble( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDouble( columnNumber );
    }

    [[nodiscard]]
    inline Currency DataReader::GetCurrency( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetCurrency( columnNumber );
    }


    [[nodiscard]]
    inline DateTime DataReader::GetDateTime( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDateTime( columnNumber );
    }

    [[nodiscard]]
    inline TimestampOffset DataReader::GetTimestampOffset( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetTimestampOffset( columnNumber );
    }



    [[nodiscard]]
    inline Date DataReader::GetDate( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDate( columnNumber );
    }

    [[nodiscard]]
    inline Time DataReader::GetTime( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetTime( columnNumber );
    }

    [[nodiscard]]
    inline TimeSpan DataReader::GetTimeSpan( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetTimeSpan( columnNumber );
    }

    [[nodiscard]]
    inline WideString DataReader::GetWideString( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetWideString( columnNumber );
    }

    [[nodiscard]]
    inline AnsiString DataReader::GetAnsiString( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetAnsiString( columnNumber );
    }

    [[nodiscard]]
    inline std::vector<Byte> DataReader::GetBinary( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetBinary( columnNumber );
    }


    [[nodiscard]]
    inline Guid DataReader::GetGuid( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetGuid( columnNumber );
    }

    [[nodiscard]]
    inline RowVersion DataReader::GetRowVersion( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetRowVersion( columnNumber );
    }



    /// <summary>
    /// <para>
    /// The Connection class is a wrapper for the ODBC connection handle.
    /// </para>
    /// <para>
    /// A connection consists of a driver and a data source. A connection handle identifies each 
    /// connection. The connection handle defines not only which driver to use but which data source 
    /// to use with that driver. Within a segment of code that implements ODBC (the Driver Manager 
    /// or a driver), the connection handle identifies a structure that contains connection 
    /// information, such as the following:
    /// </para>
    /// <list type="bullet">
    /// <item>
    /// The state of the connection
    /// </item>
    /// <item>
    /// The current connection-level diagnostics
    /// </item>
    /// <item>
    /// The handles of statements and descriptors currently allocated on the connection
    /// </item>
    /// <item>
    /// The current settings of each connection attribute
    /// </item>
    /// </list>
    /// <para>
    /// ODBC does not prevent multiple simultaneous connections, if the driver supports them. 
    /// Therefore, in a particular ODBC environment, multiple connection handles might point 
    /// to a variety of drivers and data sources, to the same driver and a variety of data sources, 
    /// or even to multiple connections to the same driver and data source. Some drivers limit the 
    /// number of active connections they support; the SQL_MAX_DRIVER_CONNECTIONS option in 
    /// SQLGetInfo specifies how many active connections a particular driver supports.
    /// </para>
    /// <para>
    /// Connection handles are primarily used when connecting to the data source (SQLConnect, SQLDriverConnect, 
    /// or SQLBrowseConnect), disconnecting from the data source (SQLDisconnect), getting information about the 
    /// driver and data source (SQLGetInfo), retrieving diagnostics (SQLGetDiagField and SQLGetDiagRec), and 
    /// performing transactions (SQLEndTran). They are also used when setting and getting connection attributes 
    /// (SQLSetConnectAttr and SQLGetConnectAttr) and when getting the native format of an SQL statement (SQLNativeSql).
    /// </para>
    /// <para>
    /// Connection handles are allocated with SQLAllocHandle and freed with SQLFreeHandle.
    /// </para>
    /// </summary>
    class Connection : public SqlHandle<ODBC::HandleType::Connection>
    {
        friend class Environment;
    public:
        using Base = SqlHandle<ODBC::HandleType::Connection>;

        constexpr Connection( ) noexcept
        {
        }
    private:
        constexpr explicit Connection( SQLHANDLE sqlHandle, bool destructorClosesHandle = true ) noexcept
            : Base( sqlHandle, destructorClosesHandle )
        {
        }
    public:
        void BrowseConnect( const SQLWCHAR* inputConnectionString, SQLSMALLINT inputConnectionStringLength, SQLWCHAR* resultConnectionString, SQLSMALLINT resultConnectionStringMaxLength, SQLSMALLINT* resultConnectionStringActualLength ) const
        {
            auto rc = SQLBrowseConnectW( Handle( ), const_cast<SQLWCHAR*>(inputConnectionString), inputConnectionStringLength, resultConnectionString, resultConnectionStringMaxLength, resultConnectionStringActualLength );
            if ( rc != SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
        }
        void BrowseConnect( const SQLCHAR* inputConnectionString, SQLSMALLINT inputConnectionStringLength, SQLCHAR* resultConnectionString, SQLSMALLINT resultConnectionStringMaxLength, SQLSMALLINT* resultConnectionStringActualLength ) const
        {
            auto rc = SQLBrowseConnectA( Handle( ), const_cast<SQLCHAR*>( inputConnectionString ), inputConnectionStringLength, resultConnectionString, resultConnectionStringMaxLength, resultConnectionStringActualLength );
            if ( rc != SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
        }

        Result Connect( const SQLWCHAR* datasourceName, SQLSMALLINT datasourceNameLength, const SQLWCHAR* userName, SQLSMALLINT userNameLength, const SQLWCHAR* authenticationString, SQLSMALLINT authenticationStringLength ) const
        {
            auto rc = SQLConnectW( Handle( ), const_cast<SQLWCHAR*>( datasourceName ), datasourceNameLength, const_cast<SQLWCHAR*>( userName ), userNameLength, const_cast<SQLWCHAR*>( authenticationString ), authenticationStringLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        template<typename T1, typename T2, typename T3>
            requires std::is_same_v<T1, WideString> || std::is_same_v<T1, std::wstring> || std::is_same_v<T1, std::wstring_view> ||
            std::is_same_v<T2, WideString> || std::is_same_v<T2, std::wstring> || std::is_same_v<T2, std::wstring_view>
        Result Connect( const T1& datasourceName ) const
        {
            return Connect( datasourceName.data( ), static_cast< SQLSMALLINT >( datasourceName.length( ) ), nullptr, 0, nullptr, 0 );
        }


        template<typename T1, typename T2, typename T3>
            requires std::is_same_v<T1, WideString> || std::is_same_v<T1, std::wstring> || std::is_same_v<T1, std::wstring_view> ||
                    std::is_same_v<T2, WideString> || std::is_same_v<T2, std::wstring> || std::is_same_v<T2, std::wstring_view>
        Result Connect( const T1& datasourceName, const T2& userName ) const
        {
            return Connect( datasourceName.data( ), static_cast< SQLSMALLINT >( datasourceName.length( ) ),
                            userName.data( ), static_cast< SQLSMALLINT >( userName.length( ) ),
                            nullptr, 0 );
        }

        template<typename T1, typename T2, typename T3>
        requires std::is_same_v<T1,WideString> || std::is_same_v<T1, std::wstring> || std::is_same_v<T1, std::wstring_view> ||
                    std::is_same_v<T2, WideString> || std::is_same_v<T2, std::wstring> || std::is_same_v<T2, std::wstring_view> ||
                    std::is_same_v<T3, WideString> || std::is_same_v<T3, std::wstring> || std::is_same_v<T3, std::wstring_view> 
        Result Connect( const T1& datasourceName, const T2& userName, const T3& authenticationString ) const
        {
            return Connect( datasourceName.data(), static_cast< SQLSMALLINT >( datasourceName.length() ),
                            userName.data( ), static_cast< SQLSMALLINT >( userName.length( ) ), 
                            authenticationString.data( ), static_cast< SQLSMALLINT >( authenticationString.length( ) ) );
        }


        Result Connect( const SQLCHAR* datasourceName, SQLSMALLINT datasourceNameLength, const SQLCHAR* userName, SQLSMALLINT userNameLength, const SQLCHAR* authenticationString, SQLSMALLINT authenticationStringLength ) const
        {
            auto rc = SQLConnectA( Handle( ), const_cast<SQLCHAR*>( datasourceName ), datasourceNameLength, const_cast<SQLCHAR*>( userName ), userNameLength, const_cast<SQLCHAR*>( authenticationString ), authenticationStringLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        ODBC::Statement CreateStatement( ) const
        {
            auto connectionHandle = ODBC::Statement::AllocateHandle( Handle( ) );
            ODBC::Statement result( connectionHandle );
            return result;
        }


        Result Disconnect( ) const
        {
            auto rc = SQLDisconnect( Handle() );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result DriverConnect( SQLHWND windowHandle, const SQLWCHAR* initialConnectionString, SQLSMALLINT initialConnectionStringLength, SQLWCHAR* resultConnectionString, SQLSMALLINT resultConnectionStringMaxLength, SQLSMALLINT* resultConnectionStringActualLength, ODBC::DriverCompletion driverCompletion ) const
        {
            auto rc = SQLDriverConnectW( Handle( ), windowHandle, const_cast<SQLWCHAR*>( initialConnectionString ), initialConnectionStringLength, resultConnectionString, resultConnectionStringMaxLength, resultConnectionStringActualLength, static_cast<SQLSMALLINT>( driverCompletion ) );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result DriverConnect( SQLHWND windowHandle, const SQLCHAR* initialConnectionString, SQLSMALLINT initialConnectionStringLength, SQLCHAR* resultConnectionString, SQLSMALLINT resultConnectionStringMaxLength, SQLSMALLINT* resultConnectionStringActualLength, ODBC::DriverCompletion driverCompletion ) const
        {
            auto rc = SQLDriverConnectA( Handle( ), windowHandle, const_cast<SQLCHAR*>( initialConnectionString ), initialConnectionStringLength, resultConnectionString, resultConnectionStringMaxLength, resultConnectionStringActualLength, static_cast<SQLSMALLINT>( driverCompletion ) );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result EndTransaction( ODBC::TransactionCompletionType completionType ) const
        {
            auto rc = SQLEndTran( static_cast<SQLSMALLINT>( Base::HandleType ), Handle( ), static_cast<SQLSMALLINT>( completionType ) );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Commit( ) const
        {
            return EndTransaction( ODBC::TransactionCompletionType::Commit );
        }
        Result Rollback( ) const
        {
            return EndTransaction( ODBC::TransactionCompletionType::Rollback );
        }

        Result GetAttributeW( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueBufferLength, SQLINTEGER* valueActualLength ) const
        {
            auto rc = SQLGetConnectAttrW( Handle( ), attributeId, value, valueBufferLength, valueActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result GetAttribute( SQLINTEGER attributeId, WideString& result ) const
        {
            constexpr SQLINTEGER bufferSize = 1024;
            SQLINTEGER actualLength = 0;
            wchar_t buffer[bufferSize];
            auto rc = GetAttributeW( attributeId, buffer, bufferSize*sizeof(wchar_t), &actualLength );
            result.assign( buffer, static_cast<size_t>( actualLength/sizeof(wchar_t) ) );
            return rc;
        }

        Result GetAttribute( SQLINTEGER attributeId, SQLINTEGER& result ) const
        {
            SQLINTEGER actualLength = 0;
            auto rc = GetAttributeW( attributeId, &result, SQL_IS_INTEGER, &actualLength );
            return rc;
        }
        Result GetAttribute( SQLINTEGER attributeId, SQLUINTEGER& result ) const
        {
            SQLINTEGER actualLength = 0;
            auto rc = GetAttributeW( attributeId, &result, SQL_IS_UINTEGER, &actualLength );
            return rc;
        }


        Result GetAttributeA( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueBufferLength, SQLINTEGER* valueActualLength ) const
        {
            auto rc = SQLGetConnectAttrW( Handle( ), attributeId, value, valueBufferLength, valueActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SetAttributeW( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueLength ) const
        {
            auto rc = SQLSetConnectAttrW( Handle( ), attributeId, value, valueLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SetAttribute( SQLINTEGER attributeId, const WideString& value ) const
        {
            auto rc = SetAttributeW( attributeId, const_cast<wchar_t*>(value.c_str( )), static_cast<SQLINTEGER>( value.length( )*sizeof(wchar_t) ) );
            return rc;
        }

        Result SetAttribute( SQLINTEGER attributeId, SQLINTEGER value ) const
        {
            auto rc = SetAttributeW( attributeId, ( SQLPOINTER )static_cast<ptrdiff_t>( value ), SQL_IS_INTEGER );
            return rc;
        }
        Result SetAttribute( SQLINTEGER attributeId, SQLUINTEGER value ) const
        {
            auto rc = SetAttributeW( attributeId, ( SQLPOINTER )static_cast<size_t>( value ), SQL_IS_UINTEGER );
            return rc;
        }



        Result SetAttributeA( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueLength ) const
        {
            auto rc = SQLSetConnectAttrA( Handle( ), attributeId, value, valueLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }




        Result GetCurrentCatalog( WideString& result ) const
        {
            auto rc = GetAttribute( SQL_ATTR_CURRENT_CATALOG, result );
            return rc;
        }

        WideString CurrentCatalog( ) const
        {
            WideString result;
            GetCurrentCatalog( result );
            return result;
        }

        Result SetCurrentCatalog( const WideString& currentCatalog ) const
        {
            auto rc = SetAttribute( SQL_ATTR_CURRENT_CATALOG, currentCatalog );
            return rc;
        }


        Result SetAutoCommitMode( bool enabled )
        {
            Result rc = Result::Success;
            if ( enabled )
            {
                rc = SetAttribute( SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_ON );
            }
            else
            {
                rc = SetAttribute( SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF );
            }
            return rc;
        }




        Result GetFunctions( SQLUSMALLINT functionId, SQLUSMALLINT* supported ) const
        {
            auto rc = SQLGetFunctions( Handle( ), functionId, supported );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result GetInfoW( SQLUSMALLINT infoType, SQLPOINTER infoValue, SQLSMALLINT infoValueMaxLength, SQLSMALLINT* infoValueActualLength ) const
        {
            auto rc = SQLGetInfoW( Handle( ), infoType, infoValue, infoValueMaxLength, infoValueActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result GetInfoA( SQLUSMALLINT infoType, SQLPOINTER infoValue, SQLSMALLINT infoValueMaxLength, SQLSMALLINT* infoValueActualLength ) const
        {
            auto rc = SQLGetInfoA( Handle( ), infoType, infoValue, infoValueMaxLength, infoValueActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        Result NativeSql( const SQLWCHAR* inStatement, SQLINTEGER inStatementLength, SQLWCHAR* outStatement, SQLINTEGER outStatementMaxLength, SQLINTEGER* outStatementActualLength ) const
        {
            auto rc = SQLNativeSqlW( Handle( ), const_cast<SQLWCHAR*>( inStatement ), inStatementLength, outStatement, outStatementMaxLength, outStatementActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result NativeSql( const SQLCHAR* inStatement, SQLINTEGER inStatementLength, SQLCHAR* outStatement, SQLINTEGER outStatementMaxLength, SQLINTEGER* outStatementActualLength ) const
        {
            auto rc = SQLNativeSqlA( Handle( ), const_cast<SQLCHAR*>( inStatement ), inStatementLength, outStatement, outStatementMaxLength, outStatementActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }






    };


    /// <summary>
    /// <para>
    /// The Environment class is a wrapper for the ODBC environment handle.
    /// </para>
    /// <para>
    /// An environment is a global context in which to access data; associated with an environment 
    /// is any information that is global in nature, such as:
    /// </para>
    /// <list type="bullet">
    /// <item>
    /// The environment's state
    /// </item>
    /// <item>
    /// The current environment-level diagnostics
    /// </item>
    /// <item>
    /// The handles of connections currently allocated on the environment
    /// </item>
    /// <item>
    /// The current settings of each environment attribute
    /// </item>
    /// </list>
    /// <para>
    /// Within a piece of code that implements ODBC (the Driver Manager or a driver), an environment handle 
    /// identifies a structure to contain this information.
    /// </para>
    /// <para>
    /// Environment handles are not frequently used in ODBC applications. They are always used in calls to 
    /// SQLDataSources and SQLDrivers and sometimes used in calls to SQLAllocHandle, SQLEndTran, 
    /// SQLFreeHandle, SQLGetDiagField, and SQLGetDiagRec.
    /// </para>
    /// <para>
    /// Each piece of code that implements ODBC (the Driver Manager or a driver) contains one or more 
    /// environment handles. For example, the Driver Manager maintains a separate environment handle 
    /// for each application that is connected to it. Environment handles are allocated with SQLAllocHandle 
    /// and freed with SQLFreeHandle.
    /// </para>
    /// </summary>
    class Environment : public SqlHandle<ODBC::HandleType::Environment>
    {
    public:
        using Base = SqlHandle<ODBC::HandleType::Environment>;

        constexpr Environment( ) noexcept
        {
        }
    private:
        constexpr explicit Environment( SQLHANDLE sqlHandle, bool destructorClosesHandle = true ) noexcept
            : Base( sqlHandle, destructorClosesHandle )
        {
        }
    public:
        static Environment Create( ODBC::Version version = ODBC::Version::Version3_80 )
        {
            auto sqlHandle = AllocateHandle( );
            Environment result( sqlHandle );
            result.SetVersion( version );
            return result;
        }
    protected:
        void SetAttribute( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueLength ) const
        {
            auto rc = SQLSetEnvAttr( Handle( ), attributeId, value, valueLength );
            if ( rc != SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
        }

        void GetAttribute( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER allocatedLength, SQLINTEGER* valueLength ) const
        {
            auto rc = SQLGetEnvAttr( Handle( ), attributeId, value, allocatedLength, valueLength );
            if ( rc != SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
        }

        void SetUInt32Attribute( SQLINTEGER attributeId, UInt32 value ) const
        {
            SetAttribute( attributeId, ( SQLPOINTER ) static_cast< size_t >( value ), 0 );
        }

        UInt32 GetUInt32Attribute( SQLINTEGER attributeId ) const
        {
            SQLINTEGER valueLength;
            UInt32 result = 0;
            GetAttribute( attributeId, &result, sizeof( UInt32 ), &valueLength );
            return result;
        }

        static void SetGlobalAttribute( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueLength )
        {
            auto rc = SQLSetEnvAttr( nullptr, attributeId, value, valueLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                Internal::ThrowException( rc, ODBC::HandleType::Environment, nullptr, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
        }

        static void GetGlobalAttribute( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER allocatedLength, SQLINTEGER* valueLength )
        {
            auto rc = SQLGetEnvAttr( nullptr, attributeId, value, allocatedLength, valueLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                Internal::ThrowException( rc, ODBC::HandleType::Environment, nullptr, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
        }



        static void SetGlobalUInt32Attribute( SQLINTEGER attributeId, UInt32 value )
        {
            SetGlobalAttribute( attributeId, (SQLPOINTER) static_cast<size_t>( value ), 0 );
        }

        static UInt32 GetGlobalUInt32Attribute( SQLINTEGER attributeId )
        {
            SQLINTEGER valueLength;
            UInt32 result = 0;
            GetGlobalAttribute( attributeId, &result, sizeof( UInt32 ), &valueLength );
            return result;
        }




    public:
        ODBC::Version Version( ) const
        {
            return static_cast<ODBC::Version>( GetUInt32Attribute( SQL_ATTR_ODBC_VERSION ) );
        }
        void SetVersion( ODBC::Version version ) const
        {
            SetUInt32Attribute( SQL_ATTR_ODBC_VERSION, static_cast<UInt32>( version ) );
        }

        


        static ODBC::ConnectionPooling GlobalConnectionPooling( )
        {
            return static_cast< ODBC::ConnectionPooling >( GetGlobalUInt32Attribute( SQL_ATTR_CONNECTION_POOLING ) );
        }
        static void SetGlobalConnectionPooling( ODBC::ConnectionPooling connectionPooling )
        {
            SetGlobalUInt32Attribute( SQL_ATTR_CONNECTION_POOLING, static_cast< UInt32 >( connectionPooling ) );
        }

        ODBC::ConnectionPooling ConnectionPooling( ) const
        {
            return static_cast< ODBC::ConnectionPooling >( GetUInt32Attribute( SQL_ATTR_CONNECTION_POOLING ) );
        }
        void SetConnectionPooling( ODBC::ConnectionPooling connectionPooling ) const
        {
            SetUInt32Attribute( SQL_ATTR_CONNECTION_POOLING, static_cast< UInt32 >( connectionPooling ) );
        }

        Result DataSources( ODBC::Fetch direction, SQLWCHAR* datasourceName, SQLSMALLINT datasourceNameMaxLength, SQLSMALLINT* datasourceNameActualLength, SQLWCHAR* datasourceDescription, SQLSMALLINT datasourceDescriptionMaxLength, SQLSMALLINT* datasourceDescriptionActualLength ) const
        {
            auto rc = SQLDataSourcesW( Handle( ), static_cast< SQLUSMALLINT >( direction ), datasourceName, datasourceNameMaxLength, datasourceNameActualLength, datasourceDescription, datasourceDescriptionMaxLength, datasourceDescriptionActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast< Result >( rc );
        }


        Result DataSources( ODBC::Fetch direction, SQLCHAR* datasourceName, SQLSMALLINT datasourceNameMaxLength, SQLSMALLINT* datasourceNameActualLength, SQLCHAR* datasourceDescription, SQLSMALLINT datasourceDescriptionMaxLength, SQLSMALLINT* datasourceDescriptionActualLength ) const
        {
            auto rc = SQLDataSourcesA( Handle( ), static_cast<SQLUSMALLINT>( direction ), datasourceName, datasourceNameMaxLength, datasourceNameActualLength, datasourceDescription, datasourceDescriptionMaxLength, datasourceDescriptionActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        std::vector<ODBC::DataSource> DataSources( ODBC::Fetch direction = ODBC::Fetch::First )
        {
            SQLWCHAR dataSourceName[1024];
            SQLSMALLINT dataSourceNameLength = 0;
            SQLWCHAR dataSourceDescription[1024];
            SQLSMALLINT dataSourceDescriptionLength = 0;
            std::vector<ODBC::DataSource> result;

            auto rc = DataSources( direction, dataSourceName, 1024, &dataSourceNameLength, dataSourceDescription, 1024, &dataSourceDescriptionLength );
            while ( rc == Result::Success )
            {
                result.emplace_back( ODBC::DataSource{ WideString{dataSourceName,static_cast<size_t>( dataSourceNameLength )},WideString{dataSourceDescription,static_cast<size_t>( dataSourceDescriptionLength )} } );
                rc = DataSources( ODBC::Fetch::Next, dataSourceName, 1024, &dataSourceNameLength, dataSourceDescription, 1024, &dataSourceDescriptionLength );
            }

            return result;
        }


        Result Drivers( ODBC::Fetch direction, SQLWCHAR* driverDescription, SQLSMALLINT driverDescriptionMaxLength, SQLSMALLINT* driverDescriptionActualLength, SQLWCHAR* driverAttributes, SQLSMALLINT driverAttributesMaxLength, SQLSMALLINT* driverAttributesActualLength ) const
        {
            auto rc = SQLDriversW( Handle( ), static_cast<SQLUSMALLINT>( direction ), driverDescription, driverDescriptionMaxLength, driverDescriptionActualLength, driverAttributes, driverAttributesMaxLength, driverAttributesActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        std::vector<ODBC::Driver> Drivers( ODBC::Fetch direction )
        {
            SQLWCHAR driverDescription[1024];
            SQLSMALLINT driverDescriptionLength = 0;
            SQLWCHAR driverAttributes[1024];
            SQLSMALLINT driverAttributesLength = 0;
            std::vector<ODBC::Driver> result;

            auto rc = Drivers( direction, driverDescription, 1024, &driverDescriptionLength, driverAttributes, 1024, &driverAttributesLength );
            while ( rc == Result::Success )
            {
                result.emplace_back( ODBC::Driver{ WideString{driverDescription,static_cast<size_t>( driverDescriptionLength )},WideString{driverAttributes,static_cast<size_t>( driverAttributesLength )} } );
                rc = Drivers( ODBC::Fetch::Next, driverDescription, 1024, &driverDescriptionLength, driverAttributes, 1024, &driverAttributesLength );
            }

            return result;
        }



        Result EndTransaction( ODBC::TransactionCompletionType completionType ) const
        {
            auto rc = SQLEndTran( static_cast<SQLSMALLINT>( Base::HandleType ), Handle( ), static_cast<SQLSMALLINT>( completionType ) );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result Commit( ) const
        {
            return EndTransaction( ODBC::TransactionCompletionType::Commit );
        }
        Result Rollback( ) const
        {
            return EndTransaction( ODBC::TransactionCompletionType::Rollback );
        }


        ODBC::Connection CreateConnection( )
        {
            auto connectionHandle = ODBC::Connection::AllocateHandle( Handle( ) );
            ODBC::Connection result( connectionHandle );
            return result;
        }


        ODBC::Connection Connect( const WideString& datasourceName )
        {
            auto connection = CreateConnection( );
            connection.Connect( datasourceName.c_str( ), static_cast<SQLSMALLINT>( datasourceName.length( ) ), nullptr, 0, nullptr, 0 );
            return connection;
        }

        ODBC::Connection Connect( const WideString& datasourceName, const WideString& userName )
        {
            auto connection = CreateConnection( );
            connection.Connect( datasourceName.c_str( ), static_cast<SQLSMALLINT>( datasourceName.length( ) ), userName.c_str( ), static_cast<SQLSMALLINT>( userName.length( ) ), nullptr, 0 );
            return connection;
        }

        ODBC::Connection Connect( const WideString& datasourceName, const WideString& userName, const WideString& authenticationString )
        {
            auto connection = CreateConnection( );
            connection.Connect( datasourceName.c_str( ), static_cast<SQLSMALLINT>( datasourceName.length( ) ), userName.c_str( ), static_cast<SQLSMALLINT>( userName.length( ) ), authenticationString.c_str( ), static_cast<SQLSMALLINT>( authenticationString.length( ) ) );
            return connection;
        }
    };


}

#endif
