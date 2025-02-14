#pragma once
#ifndef HODBCMSSQL_H_
#define HODBCMSSQL_H_
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

#include <HODBCDef.h>

namespace Harlinn::ODBC
{
    class Environment;
    class Connection;
    class Statement;
    class Descriptor;
    class DataReader;
    struct ParameterDescription;
}

namespace Harlinn::ODBC::MsSql
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
    constexpr const SQLINTEGER SQL_COPT_SS_PERF_DATA = ( SQL_COPT_SS_BASE + 11 );
    /// <summary>
    /// Used to set the logfile name for the Performance data
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_PERF_DATA_LOG = ( SQL_COPT_SS_BASE + 12 );
    /// <summary>
    /// Used to set the query logging threshold in milliseconds.
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_PERF_QUERY_INTERVAL = ( SQL_COPT_SS_BASE + 13 );
    /// <summary>
    /// Used to set the logfile name for saving queryies.
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_PERF_QUERY_LOG = ( SQL_COPT_SS_BASE + 14 );
    /// <summary>
    /// Used to start and stop query logging.
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_PERF_QUERY = ( SQL_COPT_SS_BASE + 15 );
    /// <summary>
    /// Used to make a statistics log entry to disk.
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_PERF_DATA_LOG_NOW = ( SQL_COPT_SS_BASE + 16 );
    /// <summary>
    /// Enable/Disable Quoted Identifiers
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_QUOTED_IDENT = ( SQL_COPT_SS_BASE + 17 );
    /// <summary>
    /// Enable/Disable ANSI NULL, Padding and Warnings
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_ANSI_NPW = ( SQL_COPT_SS_BASE + 18 );
    /// <summary>
    /// Allow BCP usage on connection
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_BCP = ( SQL_COPT_SS_BASE + 19 );
    /// <summary>
    /// Perform code page translation
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_TRANSLATE = ( SQL_COPT_SS_BASE + 20 );
    /// <summary>
    /// File name to be attached as a database
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_ATTACHDBFILENAME = ( SQL_COPT_SS_BASE + 21 );
    /// <summary>
    /// Enable/Disable CONCAT_NULL_YIELDS_NULL
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_CONCAT_NULL = ( SQL_COPT_SS_BASE + 22 );
    /// <summary>
    /// Allow strong encryption for data
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_ENCRYPT = ( SQL_COPT_SS_BASE + 23 );
    /// <summary>
    /// Multiple active result set per connection
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_MARS_ENABLED = ( SQL_COPT_SS_BASE + 24 );
    /// <summary>
    /// Failover partner server
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_FAILOVER_PARTNER = ( SQL_COPT_SS_BASE + 25 );
    /// <summary>
    /// Old Password, used when changing password during login
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_OLDPWD = ( SQL_COPT_SS_BASE + 26 );
    /// <summary>
    /// Used to set/get any driver-specific or ODBC-defined TXN iso level
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_TXN_ISOLATION = ( SQL_COPT_SS_BASE + 27 );
    /// <summary>
    /// Trust server certificate
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_TRUST_SERVER_CERTIFICATE = ( SQL_COPT_SS_BASE + 28 );
    /// <summary>
    /// Server SPN
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_SERVER_SPN = ( SQL_COPT_SS_BASE + 29 );
    /// <summary>
    /// Failover partner server SPN
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_FAILOVER_PARTNER_SPN = ( SQL_COPT_SS_BASE + 30 );
    /// <summary>
    /// The integrated authentication method used for the connection
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_INTEGRATED_AUTHENTICATION_METHOD = ( SQL_COPT_SS_BASE + 31 );
    /// <summary>
    /// Used to decide if the connection is mutually authenticated
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_MUTUALLY_AUTHENTICATED = ( SQL_COPT_SS_BASE + 32 );
    /// <summary>
    /// Post connection attribute used to get the ConnectionID
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_CLIENT_CONNECTION_ID = ( SQL_COPT_SS_BASE + 33 );

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
    constexpr const SQLINTEGER SQL_SOPT_SS_TEXTPTR_LOGGING = ( SQL_SOPT_SS_BASE + 0 );
    /// <summary>
    /// dbcurcmd SQLGetStmtOption only
    /// </summary>
    constexpr const SQLINTEGER SQL_SOPT_SS_CURRENT_COMMAND = ( SQL_SOPT_SS_BASE + 1 );
    /// <summary>
    /// Expose FOR BROWSE hidden columns
    /// </summary>
    constexpr const SQLINTEGER SQL_SOPT_SS_HIDDEN_COLUMNS = ( SQL_SOPT_SS_BASE + 2 );
    /// <summary>
    /// Set NOBROWSETABLE option
    /// </summary>
    constexpr const SQLINTEGER SQL_SOPT_SS_NOBROWSETABLE = ( SQL_SOPT_SS_BASE + 3 );
    /// <summary>
    /// Regionalize output character conversions
    /// </summary>
    constexpr const SQLINTEGER SQL_SOPT_SS_REGIONALIZE = ( SQL_SOPT_SS_BASE + 4 );
    /// <summary>
    /// Server cursor options
    /// </summary>
    constexpr const SQLINTEGER SQL_SOPT_SS_CURSOR_OPTIONS = ( SQL_SOPT_SS_BASE + 5 );
    /// <summary>
    /// Real vs. Not Real row count indicator
    /// </summary>
    constexpr const SQLINTEGER SQL_SOPT_SS_NOCOUNT_STATUS = ( SQL_SOPT_SS_BASE + 6 );
    /// <summary>
    /// Defer prepare until necessary
    /// </summary>
    constexpr const SQLINTEGER SQL_SOPT_SS_DEFER_PREPARE = ( SQL_SOPT_SS_BASE + 7 );
    /// <summary>
    /// Notification timeout
    /// </summary>
    constexpr const SQLINTEGER SQL_SOPT_SS_QUERYNOTIFICATION_TIMEOUT = ( SQL_SOPT_SS_BASE + 8 );
    /// <summary>
    /// Notification message text
    /// </summary>
    constexpr const SQLINTEGER SQL_SOPT_SS_QUERYNOTIFICATION_MSGTEXT = ( SQL_SOPT_SS_BASE + 9 );
    /// <summary>
    /// SQL service broker name
    /// </summary>
    constexpr const SQLINTEGER SQL_SOPT_SS_QUERYNOTIFICATION_OPTIONS = ( SQL_SOPT_SS_BASE + 10 );
    /// <summary>
    /// Direct subsequent calls to parameter related methods to set properties on constituent columns/parameters of container types
    /// </summary>
    constexpr const SQLINTEGER SQL_SOPT_SS_PARAM_FOCUS = ( SQL_SOPT_SS_BASE + 11 );
    /// <summary>
    /// Sets name scope for subsequent catalog function calls
    /// </summary>
    constexpr const SQLINTEGER SQL_SOPT_SS_NAME_SCOPE = ( SQL_SOPT_SS_BASE + 12 );
    constexpr const SQLINTEGER SQL_SOPT_SS_MAX_USED = SQL_SOPT_SS_NAME_SCOPE;
    // Define old names
    constexpr const SQLINTEGER SQL_TEXTPTR_LOGGING = SQL_SOPT_SS_TEXTPTR_LOGGING;

    constexpr const SQLINTEGER SQL_COPT_SS_BASE_EX = 1240;
    /// <summary>
    /// Browse connect mode of operation
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_BROWSE_CONNECT = ( SQL_COPT_SS_BASE_EX + 1 );
    /// <summary>
    /// Single Server browse request.
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_BROWSE_SERVER = ( SQL_COPT_SS_BASE_EX + 2 );
    /// <summary>
    /// Issues warning when data from the server had a loss during code page conversion.
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_WARN_ON_CP_ERROR = ( SQL_COPT_SS_BASE_EX + 3 );
    /// <summary>
    /// dbdead SQLGetConnectOption only. It will try to ping the server. Expensive connection check
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_CONNECTION_DEAD = ( SQL_COPT_SS_BASE_EX + 4 );
    /// <summary>
    /// Determines if we should cache browse info. Used when returned buffer is greater then ODBC limit (32K)
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_BROWSE_CACHE_DATA = ( SQL_COPT_SS_BASE_EX + 5 );
    /// <summary>
    /// When this option is set, we will perform connection reset on next packet
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_RESET_CONNECTION = ( SQL_COPT_SS_BASE_EX + 6 );
    /// <summary>
    /// Application Intent
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_APPLICATION_INTENT = ( SQL_COPT_SS_BASE_EX + 7 );
    /// <summary>
    /// Multi-subnet Failover
    /// </summary>
    constexpr const SQLINTEGER SQL_COPT_SS_MULTISUBNET_FAILOVER = ( SQL_COPT_SS_BASE_EX + 8 );
    constexpr const SQLINTEGER SQL_COPT_SS_EX_MAX_USED = SQL_COPT_SS_MULTISUBNET_FAILOVER;

    // SQLColAttributes driver specific defines.
    // SQLSetDescField/SQLGetDescField driver specific defines.
    // Microsoft has 1200 thru 1249 reserved for Microsoft SQL Server Native Client driver usage.
    constexpr const SQLINTEGER SQL_CA_SS_BASE = 1200;
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_SSTYPE = ( SQL_CA_SS_BASE + 0 );   //  dbcoltype/dbalttype
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_UTYPE = ( SQL_CA_SS_BASE + 1 );   //  dbcolutype/dbaltutype
    constexpr const SQLINTEGER SQL_CA_SS_NUM_ORDERS = ( SQL_CA_SS_BASE + 2 );   //  dbnumorders
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_ORDER = ( SQL_CA_SS_BASE + 3 );   //  dbordercol
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_VARYLEN = ( SQL_CA_SS_BASE + 4 );   //  dbvarylen
    constexpr const SQLINTEGER SQL_CA_SS_NUM_COMPUTES = ( SQL_CA_SS_BASE + 5 );   //  dbnumcompute
    constexpr const SQLINTEGER SQL_CA_SS_COMPUTE_ID = ( SQL_CA_SS_BASE + 6 );   //  dbnextrow status return
    constexpr const SQLINTEGER SQL_CA_SS_COMPUTE_BYLIST = ( SQL_CA_SS_BASE + 7 );   //  dbbylist
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_ID = ( SQL_CA_SS_BASE + 8 );   //  dbaltcolid
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_OP = ( SQL_CA_SS_BASE + 9 );   //  dbaltop
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_SIZE = ( SQL_CA_SS_BASE + 10 );  //  dbcollen
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_HIDDEN = ( SQL_CA_SS_BASE + 11 );  //  Column is hidden (FOR BROWSE)
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_KEY = ( SQL_CA_SS_BASE + 12 );  //  Column is key column (FOR BROWSE)

    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_COLLATION = ( SQL_CA_SS_BASE + 14 );  //  Column collation (only for chars)
    constexpr const SQLINTEGER SQL_CA_SS_VARIANT_TYPE = ( SQL_CA_SS_BASE + 15 );
    constexpr const SQLINTEGER SQL_CA_SS_VARIANT_SQL_TYPE = ( SQL_CA_SS_BASE + 16 );
    constexpr const SQLINTEGER SQL_CA_SS_VARIANT_SERVER_TYPE = ( SQL_CA_SS_BASE + 17 );

    // XML, CLR UDT, and table valued parameter related metadata
    constexpr const SQLINTEGER SQL_CA_SS_UDT_CATALOG_NAME = ( SQL_CA_SS_BASE + 18 ); //  UDT catalog name
    constexpr const SQLINTEGER SQL_CA_SS_UDT_SCHEMA_NAME = ( SQL_CA_SS_BASE + 19 ); //  UDT schema name
    constexpr const SQLINTEGER SQL_CA_SS_UDT_TYPE_NAME = ( SQL_CA_SS_BASE + 20 ); //  UDT type name
    constexpr const SQLINTEGER SQL_CA_SS_UDT_ASSEMBLY_TYPE_NAME = ( SQL_CA_SS_BASE + 21 ); //  Qualified name of the assembly containing the UDT class
    constexpr const SQLINTEGER SQL_CA_SS_XML_SCHEMACOLLECTION_CATALOG_NAME = ( SQL_CA_SS_BASE + 22 ); //  Name of the catalog that contains XML Schema collection
    constexpr const SQLINTEGER SQL_CA_SS_XML_SCHEMACOLLECTION_SCHEMA_NAME = ( SQL_CA_SS_BASE + 23 ); //  Name of the schema that contains XML Schema collection
    constexpr const SQLINTEGER SQL_CA_SS_XML_SCHEMACOLLECTION_NAME = ( SQL_CA_SS_BASE + 24 ); //  Name of the XML Schema collection
    constexpr const SQLINTEGER SQL_CA_SS_CATALOG_NAME = ( SQL_CA_SS_BASE + 25 ); //  Catalog name
    constexpr const SQLINTEGER SQL_CA_SS_SCHEMA_NAME = ( SQL_CA_SS_BASE + 26 ); //  Schema name
    constexpr const SQLINTEGER SQL_CA_SS_TYPE_NAME = ( SQL_CA_SS_BASE + 27 ); //  Type name

    // table valued parameter related metadata
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_COMPUTED = ( SQL_CA_SS_BASE + 29 ); //  column is computed
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_IN_UNIQUE_KEY = ( SQL_CA_SS_BASE + 30 ); //  column is part of a unique key
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_SORT_ORDER = ( SQL_CA_SS_BASE + 31 ); //  column sort order
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_SORT_ORDINAL = ( SQL_CA_SS_BASE + 32 ); //  column sort ordinal
    constexpr const SQLINTEGER SQL_CA_SS_COLUMN_HAS_DEFAULT_VALUE = ( SQL_CA_SS_BASE + 33 ); //  column has default value for all rows of the table valued parameter

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
    constexpr const SQLINTEGER SQL_IS_OFF = 0L;           //  Integrated security isn't used
    constexpr const SQLINTEGER SQL_IS_ON = 1L;           //  Integrated security is used
    constexpr const SQLINTEGER SQL_IS_DEFAULT = SQL_IS_OFF;
    // Defines for use with SQL_COPT_SS_PRESERVE_CURSORS
    constexpr const SQLINTEGER SQL_PC_OFF = 0L;           //  Cursors are closed on SQLTransact
    constexpr const SQLINTEGER SQL_PC_ON = 1L;           //  Cursors remain open on SQLTransact
    constexpr const SQLINTEGER SQL_PC_DEFAULT = SQL_PC_OFF;
    // Defines for use with SQL_COPT_SS_USER_DATA
    constexpr const nullptr_t SQL_UD_NOTSET = nullptr;         //  No user data pointer set
    // Defines for use with SQL_COPT_SS_TRANSLATE
    constexpr const SQLINTEGER SQL_XL_OFF = 0L;           //  Code page translation is not performed
    constexpr const SQLINTEGER SQL_XL_ON = 1L;           //  Code page translation is performed
    constexpr const SQLINTEGER SQL_XL_DEFAULT = SQL_XL_ON;
    // Defines for use with SQL_COPT_SS_FALLBACK_CONNECT - Pre-Connect Option only
    constexpr const SQLINTEGER SQL_FB_OFF = 0L;           //  FallBack connections are disabled
    constexpr const SQLINTEGER SQL_FB_ON = 1L;           //  FallBack connections are enabled
    constexpr const SQLINTEGER SQL_FB_DEFAULT = SQL_FB_OFF;
    // Defines for use with SQL_COPT_SS_BCP - Pre-Connect Option only
    constexpr const SQLINTEGER SQL_BCP_OFF = 0L;           //  BCP is not allowed on connection
    constexpr const SQLINTEGER SQL_BCP_ON = 1L;           //  BCP is allowed on connection
    constexpr const SQLINTEGER SQL_BCP_DEFAULT = SQL_BCP_OFF;
    // Defines for use with SQL_COPT_SS_QUOTED_IDENT
    constexpr const SQLINTEGER SQL_QI_OFF = 0L;           //  Quoted identifiers are enable
    constexpr const SQLINTEGER SQL_QI_ON = 1L;           //  Quoted identifiers are disabled
    constexpr const SQLINTEGER SQL_QI_DEFAULT = SQL_QI_ON;
    // Defines for use with SQL_COPT_SS_ANSI_NPW - Pre-Connect Option only
    constexpr const SQLINTEGER SQL_AD_OFF = 0L;           //  ANSI NULLs, Padding and Warnings are enabled
    constexpr const SQLINTEGER SQL_AD_ON = 1L;           //  ANSI NULLs, Padding and Warnings are disabled
    constexpr const SQLINTEGER SQL_AD_DEFAULT = SQL_AD_ON;
    // Defines for use with SQL_COPT_SS_CONCAT_NULL - Pre-Connect Option only
    constexpr const SQLINTEGER SQL_CN_OFF = 0L;           //  CONCAT_NULL_YIELDS_NULL is off
    constexpr const SQLINTEGER SQL_CN_ON = 1L;           //  CONCAT_NULL_YIELDS_NULL is on
    constexpr const SQLINTEGER SQL_CN_DEFAULT = SQL_CN_ON;
    // Defines for use with SQL_SOPT_SS_TEXTPTR_LOGGING
    constexpr const SQLINTEGER SQL_TL_OFF = 0L;           //  No logging on text pointer ops
    constexpr const SQLINTEGER SQL_TL_ON = 1L;           //  Logging occurs on text pointer ops
    constexpr const SQLINTEGER SQL_TL_DEFAULT = SQL_TL_ON;
    // Defines for use with SQL_SOPT_SS_HIDDEN_COLUMNS
    constexpr const SQLINTEGER SQL_HC_OFF = 0L;           //  FOR BROWSE columns are hidden
    constexpr const SQLINTEGER SQL_HC_ON = 1L;           //  FOR BROWSE columns are exposed
    constexpr const SQLINTEGER SQL_HC_DEFAULT = SQL_HC_OFF;
    // Defines for use with SQL_SOPT_SS_NOBROWSETABLE
    constexpr const SQLINTEGER SQL_NB_OFF = 0L;           //  NO_BROWSETABLE is off
    constexpr const SQLINTEGER SQL_NB_ON = 1L;           //  NO_BROWSETABLE is on
    constexpr const SQLINTEGER SQL_NB_DEFAULT = SQL_NB_OFF;
    // Defines for use with SQL_SOPT_SS_REGIONALIZE
    constexpr const SQLINTEGER SQL_RE_OFF = 0L;           //  No regionalization occurs on output character conversions
    constexpr const SQLINTEGER SQL_RE_ON = 1L;           //  Regionalization occurs on output character conversions
    constexpr const SQLINTEGER SQL_RE_DEFAULT = SQL_RE_OFF;
    // Defines for use with SQL_SOPT_SS_CURSOR_OPTIONS
    constexpr const SQLINTEGER SQL_CO_OFF = 0L;           //  Clear all cursor options
    constexpr const SQLINTEGER SQL_CO_FFO = 1L;           //  Fast-forward cursor will be used
    constexpr const SQLINTEGER SQL_CO_AF = 2L;           //  Autofetch on cursor open
    constexpr const SQLINTEGER SQL_CO_FFO_AF = ( SQL_CO_FFO | SQL_CO_AF );  //  Fast-forward cursor with autofetch
    constexpr const SQLINTEGER SQL_CO_FIREHOSE_AF = 4L;           //  Auto fetch on fire-hose cursors
    constexpr const SQLINTEGER SQL_CO_DEFAULT = SQL_CO_OFF;
    //SQL_SOPT_SS_NOCOUNT_STATUS 
    constexpr const SQLINTEGER SQL_NC_OFF = 0L;
    constexpr const SQLINTEGER SQL_NC_ON = 1L;
    //SQL_SOPT_SS_DEFER_PREPARE 
    constexpr const SQLINTEGER SQL_DP_OFF = 0L;
    constexpr const SQLINTEGER SQL_DP_ON = 1L;
    //SQL_SOPT_SS_NAME_SCOPE
    constexpr const SQLINTEGER SQL_SS_NAME_SCOPE_TABLE = 0L;
    constexpr const SQLINTEGER SQL_SS_NAME_SCOPE_TABLE_TYPE = 1L;
    constexpr const SQLINTEGER SQL_SS_NAME_SCOPE_EXTENDED = 2L;
    constexpr const SQLINTEGER SQL_SS_NAME_SCOPE_SPARSE_COLUMN_SET = 3L;
    constexpr const SQLINTEGER SQL_SS_NAME_SCOPE_DEFAULT = SQL_SS_NAME_SCOPE_TABLE;
    //SQL_COPT_SS_ENCRYPT 
    constexpr const SQLINTEGER SQL_EN_OFF = 0L;
    constexpr const SQLINTEGER SQL_EN_ON = 1L;
    //SQL_COPT_SS_TRUST_SERVER_CERTIFICATE
    constexpr const SQLINTEGER SQL_TRUST_SERVER_CERTIFICATE_NO = 0L;
    constexpr const SQLINTEGER SQL_TRUST_SERVER_CERTIFICATE_YES = 1L;
    //SQL_COPT_SS_BROWSE_CONNECT 
    constexpr const SQLINTEGER SQL_MORE_INFO_NO = 0L;
    constexpr const SQLINTEGER SQL_MORE_INFO_YES = 1L;
    //SQL_COPT_SS_BROWSE_CACHE_DATA 
    constexpr const SQLINTEGER SQL_CACHE_DATA_NO = 0L;
    constexpr const SQLINTEGER SQL_CACHE_DATA_YES = 1L;
    //SQL_COPT_SS_RESET_CONNECTION 
    constexpr const SQLINTEGER SQL_RESET_YES = 1L;
    //SQL_COPT_SS_WARN_ON_CP_ERROR 
    constexpr const SQLINTEGER SQL_WARN_NO = 0L;
    constexpr const SQLINTEGER SQL_WARN_YES = 1L;
    //SQL_COPT_SS_MARS_ENABLED 
    constexpr const SQLINTEGER SQL_MARS_ENABLED_NO = 0L;
    constexpr const SQLINTEGER SQL_MARS_ENABLED_YES = 1L;
    /* SQL_TXN_ISOLATION_OPTION bitmasks */
    constexpr const SQLINTEGER SQL_TXN_SS_SNAPSHOT = 0x00000020L;

    // The following are defines for SQL_CA_SS_COLUMN_SORT_ORDER
    constexpr const SQLINTEGER SQL_SS_ORDER_UNSPECIFIED = 0L;
    constexpr const SQLINTEGER SQL_SS_DESCENDING_ORDER = 1L;
    constexpr const SQLINTEGER SQL_SS_ASCENDING_ORDER = 2L;
    constexpr const SQLINTEGER SQL_SS_ORDER_DEFAULT = SQL_SS_ORDER_UNSPECIFIED;

    // Driver specific SQL data type defines.
    // Microsoft has -150 thru -199 reserved for Microsoft SQL Server Native Client driver usage.
    constexpr const SQLINTEGER SQL_SS_VARIANT = ( -150 );
    constexpr const SQLINTEGER SQL_SS_UDT = ( -151 );
    constexpr const SQLINTEGER SQL_SS_XML = ( -152 );
    constexpr const SQLINTEGER SQL_SS_TABLE = ( -153 );
    constexpr const SQLINTEGER SQL_SS_TIME2 = ( -154 );
    constexpr const SQLINTEGER SQL_SS_TIMESTAMPOFFSET = ( -155 );

    // Local types to be used with SQL_CA_SS_SERVER_TYPE
    constexpr const SQLINTEGER SQL_SS_TYPE_DEFAULT = 0L;
    constexpr const SQLINTEGER SQL_SS_TYPE_SMALLDATETIME = 1L;
    constexpr const SQLINTEGER SQL_SS_TYPE_DATETIME = 2L;

    // Extended C Types range 4000 and above. Range of -100 thru 200 is reserved by Driver Manager.
    constexpr const SQLINTEGER SQL_C_TYPES_EXTENDED = 0x04000L;
    constexpr const SQLINTEGER SQL_C_SS_TIME2 = ( SQL_C_TYPES_EXTENDED + 0 );
    constexpr const SQLINTEGER SQL_C_SS_TIMESTAMPOFFSET = ( SQL_C_TYPES_EXTENDED + 1 );

    // SQL Server Data Type defines.
    // New types for SQL 6.0 and later servers
    constexpr const SQLINTEGER SQLTEXT = 0x23;
    constexpr const SQLINTEGER SQLVARBINARY = 0x25;
    constexpr const SQLINTEGER SQLINTN = 0x26;
    constexpr const SQLINTEGER SQLVARCHAR = 0x27;
    constexpr const SQLINTEGER SQLBINARY = 0x2d;
    constexpr const SQLINTEGER SQLIMAGE = 0x22;
    constexpr const SQLINTEGER SQLCHARACTER = 0x2f;
    constexpr const SQLINTEGER SQLINT1 = 0x30;
    constexpr const SQLINTEGER SQLBIT = 0x32;
    constexpr const SQLINTEGER SQLINT2 = 0x34;
    constexpr const SQLINTEGER SQLINT4 = 0x38;
    constexpr const SQLINTEGER SQLMONEY = 0x3c;
    constexpr const SQLINTEGER SQLDATETIME = 0x3d;
    constexpr const SQLINTEGER SQLFLT8 = 0x3e;
    constexpr const SQLINTEGER SQLFLTN = 0x6d;
    constexpr const SQLINTEGER SQLMONEYN = 0x6e;
    constexpr const SQLINTEGER SQLDATETIMN = 0x6f;
    constexpr const SQLINTEGER SQLFLT4 = 0x3b;
    constexpr const SQLINTEGER SQLMONEY4 = 0x7a;
    constexpr const SQLINTEGER SQLDATETIM4 = 0x3a;
    // New types for SQL 6.0 and later servers
    constexpr const SQLINTEGER SQLDECIMAL = 0x6a;
    constexpr const SQLINTEGER SQLNUMERIC = 0x6c;
    // New types for SQL 7.0 and later servers
    constexpr const SQLINTEGER SQLUNIQUEID = 0x24;
    constexpr const SQLINTEGER SQLBIGCHAR = 0xaf;
    constexpr const SQLINTEGER SQLBIGVARCHAR = 0xa7;
    constexpr const SQLINTEGER SQLBIGBINARY = 0xad;
    constexpr const SQLINTEGER SQLBIGVARBINARY = 0xa5;
    constexpr const SQLINTEGER SQLBITN = 0x68;
    constexpr const SQLINTEGER SQLNCHAR = 0xef;
    constexpr const SQLINTEGER SQLNVARCHAR = 0xe7;
    constexpr const SQLINTEGER SQLNTEXT = 0x63;
    // New types for SQL 2000 and later servers
    constexpr const SQLINTEGER SQLINT8 = 0x7f;
    constexpr const SQLINTEGER SQLVARIANT = 0x62;
    // New types for SQL 2005 and later servers
    constexpr const SQLINTEGER SQLUDT = 0xf0;
    constexpr const SQLINTEGER SQLXML = 0xf1;
    // New types for SQL 2008 and later servers
    constexpr const SQLINTEGER SQLTABLE = 0xf3;
    constexpr const SQLINTEGER SQLDATEN = 0x28;
    constexpr const SQLINTEGER SQLTIMEN = 0x29;
    constexpr const SQLINTEGER SQLDATETIME2N = 0x2a;
    constexpr const SQLINTEGER SQLDATETIMEOFFSETN = 0x2b;
    // Define old names
    constexpr const SQLINTEGER SQLDECIMALN = 0x6a;
    constexpr const SQLINTEGER SQLNUMERICN = 0x6c;

    // SQL_SS_LENGTH_UNLIMITED is used to describe the max length of
    // VARCHAR(max), VARBINARY(max), NVARCHAR(max), and XML columns
    constexpr const SQLINTEGER SQL_SS_LENGTH_UNLIMITED = 0;

    // User Data Type definitions.
    // Returned by SQLColAttributes/SQL_CA_SS_COLUMN_UTYPE.
    constexpr const SQLINTEGER SQLudtBINARY = 3;
    constexpr const SQLINTEGER SQLudtBIT = 16;
    constexpr const SQLINTEGER SQLudtBITN = 0;
    constexpr const SQLINTEGER SQLudtCHAR = 1;
    constexpr const SQLINTEGER SQLudtDATETIM4 = 22;
    constexpr const SQLINTEGER SQLudtDATETIME = 12;
    constexpr const SQLINTEGER SQLudtDATETIMN = 15;
    constexpr const SQLINTEGER SQLudtDECML = 24;
    constexpr const SQLINTEGER SQLudtDECMLN = 26;
    constexpr const SQLINTEGER SQLudtFLT4 = 23;
    constexpr const SQLINTEGER SQLudtFLT8 = 8;
    constexpr const SQLINTEGER SQLudtFLTN = 14;
    constexpr const SQLINTEGER SQLudtIMAGE = 20;
    constexpr const SQLINTEGER SQLudtINT1 = 5;
    constexpr const SQLINTEGER SQLudtINT2 = 6;
    constexpr const SQLINTEGER SQLudtINT4 = 7;
    constexpr const SQLINTEGER SQLudtINTN = 13;
    constexpr const SQLINTEGER SQLudtMONEY = 11;
    constexpr const SQLINTEGER SQLudtMONEY4 = 21;
    constexpr const SQLINTEGER SQLudtMONEYN = 17;
    constexpr const SQLINTEGER SQLudtNUM = 10;
    constexpr const SQLINTEGER SQLudtNUMN = 25;
    constexpr const SQLINTEGER SQLudtSYSNAME = 18;
    constexpr const SQLINTEGER SQLudtTEXT = 19;
    constexpr const SQLINTEGER SQLudtTIMESTAMP = 80;
    constexpr const SQLINTEGER SQLudtUNIQUEIDENTIFIER = 0;
    constexpr const SQLINTEGER SQLudtVARBINARY = 4;
    constexpr const SQLINTEGER SQLudtVARCHAR = 2;
    constexpr const SQLINTEGER MIN_USER_DATATYPE = 256;
    // Aggregate operator types.
    // Returned by SQLColAttributes/SQL_CA_SS_COLUMN_OP.
    constexpr const SQLINTEGER SQLAOPSTDEV = 0x30;    // Standard deviation
    constexpr const SQLINTEGER SQLAOPSTDEVP = 0x31;    // Standard deviation population
    constexpr const SQLINTEGER SQLAOPVAR = 0x32;    // Variance
    constexpr const SQLINTEGER SQLAOPVARP = 0x33;    // Variance population
    constexpr const SQLINTEGER SQLAOPCNT = 0x4b;    // Count
    constexpr const SQLINTEGER SQLAOPSUM = 0x4d;    // Sum
    constexpr const SQLINTEGER SQLAOPAVG = 0x4f;    // Average
    constexpr const SQLINTEGER SQLAOPMIN = 0x51;    // Min
    constexpr const SQLINTEGER SQLAOPMAX = 0x52;    // Max
    constexpr const SQLINTEGER SQLAOPANY = 0x53;    // Any
    constexpr const SQLINTEGER SQLAOPNOOP = 0x56;    // None
    // SQLGetInfo driver specific defines.
    // Microsoft has 1151 thru 1200 reserved for Microsoft SQL Server Native Client driver usage.
    constexpr const SQLINTEGER SQL_INFO_SS_FIRST = 1199;
    constexpr const SQLINTEGER SQL_INFO_SS_NETLIB_NAMEW = ( SQL_INFO_SS_FIRST + 0 ); //  dbprocinfo
    constexpr const SQLINTEGER SQL_INFO_SS_NETLIB_NAMEA = ( SQL_INFO_SS_FIRST + 1 ); //  dbprocinfo
    constexpr const SQLINTEGER SQL_INFO_SS_MAX_USED = SQL_INFO_SS_NETLIB_NAMEA;
#ifdef UNICODE
    constexpr const auto SQL_INFO_SS_NETLIB_NAME = SQL_INFO_SS_NETLIB_NAMEW;
#else
    constexpr const auto SQL_INFO_SS_NETLIB_NAME = SQL_INFO_SS_NETLIB_NAMEA;
#endif

    // SQLGetDiagField driver specific defines.
    // Microsoft has -1150 thru -1199 reserved for Microsoft SQL Server Native Client driver usage.
    constexpr const SQLINTEGER SQL_DIAG_SS_BASE = ( -1150 );
    constexpr const SQLINTEGER SQL_DIAG_SS_MSGSTATE = ( SQL_DIAG_SS_BASE );
    constexpr const SQLINTEGER SQL_DIAG_SS_SEVERITY = ( SQL_DIAG_SS_BASE - 1 );
    constexpr const SQLINTEGER SQL_DIAG_SS_SRVNAME = ( SQL_DIAG_SS_BASE - 2 );
    constexpr const SQLINTEGER SQL_DIAG_SS_PROCNAME = ( SQL_DIAG_SS_BASE - 3 );
    constexpr const SQLINTEGER SQL_DIAG_SS_LINE = ( SQL_DIAG_SS_BASE - 4 );
    // SQLGetDiagField/SQL_DIAG_DYNAMIC_FUNCTION_CODE driver specific defines.
    // Microsoft has -200 thru -299 reserved for Microsoft SQL Server Native Client driver usage.
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_BASE = ( -200 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_ALTER_DATABASE = ( SQL_DIAG_DFC_SS_BASE - 0 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CHECKPOINT = ( SQL_DIAG_DFC_SS_BASE - 1 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CONDITION = ( SQL_DIAG_DFC_SS_BASE - 2 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CREATE_DATABASE = ( SQL_DIAG_DFC_SS_BASE - 3 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CREATE_DEFAULT = ( SQL_DIAG_DFC_SS_BASE - 4 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CREATE_PROCEDURE = ( SQL_DIAG_DFC_SS_BASE - 5 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CREATE_RULE = ( SQL_DIAG_DFC_SS_BASE - 6 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CREATE_TRIGGER = ( SQL_DIAG_DFC_SS_BASE - 7 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CURSOR_DECLARE = ( SQL_DIAG_DFC_SS_BASE - 8 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CURSOR_OPEN = ( SQL_DIAG_DFC_SS_BASE - 9 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CURSOR_FETCH = ( SQL_DIAG_DFC_SS_BASE - 10 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_CURSOR_CLOSE = ( SQL_DIAG_DFC_SS_BASE - 11 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DEALLOCATE_CURSOR = ( SQL_DIAG_DFC_SS_BASE - 12 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DBCC = ( SQL_DIAG_DFC_SS_BASE - 13 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DISK = ( SQL_DIAG_DFC_SS_BASE - 14 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DROP_DATABASE = ( SQL_DIAG_DFC_SS_BASE - 15 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DROP_DEFAULT = ( SQL_DIAG_DFC_SS_BASE - 16 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DROP_PROCEDURE = ( SQL_DIAG_DFC_SS_BASE - 17 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DROP_RULE = ( SQL_DIAG_DFC_SS_BASE - 18 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DROP_TRIGGER = ( SQL_DIAG_DFC_SS_BASE - 19 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DUMP_DATABASE = ( SQL_DIAG_DFC_SS_BASE - 20 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_BACKUP_DATABASE = ( SQL_DIAG_DFC_SS_BASE - 20 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DUMP_TABLE = ( SQL_DIAG_DFC_SS_BASE - 21 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DUMP_TRANSACTION = ( SQL_DIAG_DFC_SS_BASE - 22 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_BACKUP_TRANSACTION = ( SQL_DIAG_DFC_SS_BASE - 22 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_GOTO = ( SQL_DIAG_DFC_SS_BASE - 23 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_INSERT_BULK = ( SQL_DIAG_DFC_SS_BASE - 24 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_KILL = ( SQL_DIAG_DFC_SS_BASE - 25 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_LOAD_DATABASE = ( SQL_DIAG_DFC_SS_BASE - 26 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_RESTORE_DATABASE = ( SQL_DIAG_DFC_SS_BASE - 26 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_LOAD_HEADERONLY = ( SQL_DIAG_DFC_SS_BASE - 27 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_RESTORE_HEADERONLY = ( SQL_DIAG_DFC_SS_BASE - 27 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_LOAD_TABLE = ( SQL_DIAG_DFC_SS_BASE - 28 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_LOAD_TRANSACTION = ( SQL_DIAG_DFC_SS_BASE - 29 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_RESTORE_TRANSACTION = ( SQL_DIAG_DFC_SS_BASE - 29 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_PRINT = ( SQL_DIAG_DFC_SS_BASE - 30 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_RAISERROR = ( SQL_DIAG_DFC_SS_BASE - 31 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_READTEXT = ( SQL_DIAG_DFC_SS_BASE - 32 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_RECONFIGURE = ( SQL_DIAG_DFC_SS_BASE - 33 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_RETURN = ( SQL_DIAG_DFC_SS_BASE - 34 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SELECT_INTO = ( SQL_DIAG_DFC_SS_BASE - 35 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SET = ( SQL_DIAG_DFC_SS_BASE - 36 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SET_IDENTITY_INSERT = ( SQL_DIAG_DFC_SS_BASE - 37 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SET_ROW_COUNT = ( SQL_DIAG_DFC_SS_BASE - 38 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SET_STATISTICS = ( SQL_DIAG_DFC_SS_BASE - 39 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SET_TEXTSIZE = ( SQL_DIAG_DFC_SS_BASE - 40 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SETUSER = ( SQL_DIAG_DFC_SS_BASE - 41 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SHUTDOWN = ( SQL_DIAG_DFC_SS_BASE - 42 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_TRANS_BEGIN = ( SQL_DIAG_DFC_SS_BASE - 43 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_TRANS_COMMIT = ( SQL_DIAG_DFC_SS_BASE - 44 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_TRANS_PREPARE = ( SQL_DIAG_DFC_SS_BASE - 45 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_TRANS_ROLLBACK = ( SQL_DIAG_DFC_SS_BASE - 46 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_TRANS_SAVE = ( SQL_DIAG_DFC_SS_BASE - 47 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_TRUNCATE_TABLE = ( SQL_DIAG_DFC_SS_BASE - 48 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_UPDATE_STATISTICS = ( SQL_DIAG_DFC_SS_BASE - 49 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_UPDATETEXT = ( SQL_DIAG_DFC_SS_BASE - 50 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_USE = ( SQL_DIAG_DFC_SS_BASE - 51 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_WAITFOR = ( SQL_DIAG_DFC_SS_BASE - 52 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_WRITETEXT = ( SQL_DIAG_DFC_SS_BASE - 53 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_DENY = ( SQL_DIAG_DFC_SS_BASE - 54 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_SET_XCTLVL = ( SQL_DIAG_DFC_SS_BASE - 55 );
    constexpr const SQLINTEGER SQL_DIAG_DFC_SS_MERGE = ( SQL_DIAG_DFC_SS_BASE - 56 );

    // Severity codes for SQL_DIAG_SS_SEVERITY
    constexpr const SQLINTEGER EX_ANY = 0;
    constexpr const SQLINTEGER EX_INFO = 10;
    constexpr const SQLINTEGER EX_MAXISEVERITY = EX_INFO;
    constexpr const SQLINTEGER EX_MISSING = 11;
    constexpr const SQLINTEGER EX_TYPE = 12;
    constexpr const SQLINTEGER EX_DEADLOCK = 13;
    constexpr const SQLINTEGER EX_PERMIT = 14;
    constexpr const SQLINTEGER EX_SYNTAX = 15;
    constexpr const SQLINTEGER EX_USER = 16;
    constexpr const SQLINTEGER EX_RESOURCE = 17;
    constexpr const SQLINTEGER EX_INTOK = 18;
    constexpr const SQLINTEGER MAXUSEVERITY = EX_INTOK;
    constexpr const SQLINTEGER EX_LIMIT = 19;
    constexpr const SQLINTEGER EX_CMDFATAL = 20;
    constexpr const SQLINTEGER MINFATALERR = EX_CMDFATAL;
    constexpr const SQLINTEGER EX_DBFATAL = 21;
    constexpr const SQLINTEGER EX_TABCORRUPT = 22;
    constexpr const SQLINTEGER EX_DBCORRUPT = 23;
    constexpr const SQLINTEGER EX_HARDWARE = 24;
    constexpr const SQLINTEGER EX_CONTROL = 25;
    // Internal server datatypes - used when binding to SQL_C_BINARY

    // DB-Library datatypes
    constexpr const SQLINTEGER DBMAXCHAR = ( 8000 + 1 );                    // Max length of DBVARBINARY and DBVARCHAR, etc. +1 for zero byte
    constexpr const SQLINTEGER MAXNAME = ( SQL_MAX_SQLSERVERNAME + 1 );   // Max server identifier length including zero byte
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

#endif
