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

namespace Harlinn::ODBC
{
    class Environment;
    class Connection;
    class Statement;
    class Descriptor;
    class DataReader;
    struct ParameterDescription;

    template<typename CharT, size_t maxSize>
        requires std::is_same_v<CharT, char> || std::is_same_v<CharT, wchar_t>
    class FixedDBString : public Harlinn::Common::Core::FixedString<CharT, maxSize, true>
    {
        
    public:
        using Base = Harlinn::Common::Core::FixedString<CharT, maxSize, true>;
    private:
        using Base::size_;
    public:
        using CharType = CharT;
        using Base::size;
        using Base::data;
        using Base::CheckSize;
    public:
        constexpr FixedDBString( ) noexcept = default;

        explicit FixedDBString( const CharType* str, size_t size )
            : Base( str, size )
        { }

        FixedDBString( const CharType* str )
            : Base( str )
        { }

        template<SimpleSpanLike T>
            requires std::is_same_v<typename T::value_type, CharType>
        explicit FixedDBString( const T& str )
            : Base( str )
        { }


        template<SimpleSpanLike T>
            requires std::is_same_v<typename T::value_type, CharT>
        FixedDBString& operator = ( const T& str )
        {
            Base::Assign( str.data( ), str.size( ) );
            return *this;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<typename T::value_type, CharT>
        FixedDBString& operator = ( const std::optional<T>& str )
        {
            if ( str.has_value( ) )
            {
                const auto& value = str.value( );
                Base::Assign( value.data( ), value.size( ) );
            }
            else
            {
                data( )[ 0 ] = static_cast< CharT >( 0 );
                Base::size_ = std::bit_cast<size_t>(SQL_NULL_DATA);
            }
            return *this;
        }

        SQLLEN* Indicator( )
        {
            auto* ptr = &size_;
            return reinterpret_cast< SQLLEN* >( ptr );
        }

        [[nodiscard]] constexpr bool IsNull( ) const
        {
            return std::bit_cast< SQLLEN >( Base::size_ ) == SQL_NULL_DATA;
        }

        template<IO::StreamWriter StreamT>
        void WriteTo( IO::BinaryWriter<StreamT>& destination ) const
        {
            bool notNull = IsNull( ) == false;
            destination.Write( notNull );
            if ( notNull )
            {
                auto sz = size( ) * sizeof( CharT );
                destination.Write7BitEncoded( sz );
                destination.Write( data( ), sz );
            }
        }
        template<IO::StreamReader StreamT>
        void ReadFrom( IO::BinaryReader<StreamT>& source )
        {
            bool notNull = source.Read<bool>( );
            if ( notNull )
            {
                auto sz = source.Read7BitEncoded( );
                size_ = CheckSize(sz / sizeof( CharT ));
                source.Read( data( ), sz );
                data( )[ size_ ] = static_cast< CharT >( 0 );
            }
            else
            {
                data( )[ 0 ] = static_cast< CharT >( 0 );
                size_ = SQL_NULL_DATA;
            }
        }

    };

    template<size_t maxSize>
    using FixedDBWideString = FixedDBString<wchar_t, maxSize>;
    template<size_t maxSize>
    using FixedDBAnsiString = FixedDBString<char, maxSize>;


    template<size_t maxSize>
    class FixedDBBinary : public Harlinn::Common::Core::FixedBinary<maxSize>
    {
    public:
        using Base = Harlinn::Common::Core::FixedBinary<maxSize>;
    private:
        using Base::size_;
    public:
        using Base::size;
        using Base::data;
        using Base::CheckSize;
    public:
        SQLLEN* Indicator( )
        {
            auto* ptr = &size_;
            return reinterpret_cast< SQLLEN* >( ptr );
        }

        [[nodiscard]] constexpr bool IsNull( ) const
        {
            return std::bit_cast< SQLLEN >( Base::size_ ) == SQL_NULL_DATA;
        }

        template<SimpleSpanLike T>
            requires std::is_same_v<typename T::value_type, Byte>
        FixedDBBinary& operator = ( const std::optional<T>& str )
        {
            if ( str.has_value( ) )
            {
                const auto& value = str.value( );
                Base::Assign( value.data( ), value.size( ) );
            }
            else
            {
                data( )[ 0 ] = static_cast< Byte >( 0 );
                Base::size_ = std::bit_cast< size_t >( SQL_NULL_DATA );
            }
            return *this;
        }


        template<IO::StreamWriter StreamT>
        void WriteTo( IO::BinaryWriter<StreamT>& destination ) const
        {
            bool notNull = IsNull( ) == false;
            destination.Write( notNull );
            if ( notNull )
            {
                auto sz = size( );
                destination.WriteSize( sz );
                destination.Write( data( ), sz );
            }
        }
        template<IO::StreamReader StreamT>
        void ReadFrom( IO::BinaryReader<StreamT>& source )
        {
            bool notNull = source.Read<bool>( );
            if ( notNull )
            {
                auto sz = source.ReadSize( );
                size_ = CheckSize( sz );
                source.Read( data( ), sz );
                data( )[ size_ ] = 0;
            }
            else
            {
                data( )[ 0 ] = 0;
                size_ = SQL_NULL_DATA;
            }
        }

    };

    namespace Internal
    {
        template <typename T>
        class DBValue
        {
        public:
            using value_type = T;
        private:
            mutable SQLLEN indicator_ = SQL_NULL_DATA;
            mutable T value_ = {};
        public:
            constexpr DBValue( ) = default;

            DBValue(const value_type& value) noexcept
                : indicator_(0), value_( value )
            { }

            DBValue( const std::optional<value_type>& value ) noexcept
                : indicator_( value.has_value( ) ? 0 : SQL_NULL_DATA ), value_( value.has_value( ) ? value.value( ) : value_type{} )
            {
            }

            DBValue( nullptr_t ) noexcept
                : indicator_( SQL_NULL_DATA ), value_{}
            { }

            constexpr void reset( ) noexcept
            {
                indicator_ = SQL_NULL_DATA;
                value_ = {};
            }

            constexpr DBValue& operator=( nullptr_t ) noexcept
            {
                reset( );
                return *this;
            }

            constexpr DBValue& operator = ( const value_type& value ) noexcept
            {
                indicator_ = 0;
                value_ = value;
                return *this;
            }

            constexpr DBValue& operator = ( const std::optional<value_type>& value ) noexcept
            {
                if ( value.has_value( ) )
                {
                    indicator_ = 0;
                    value_ = value.value();
                }
                else
                {
                    reset( );
                }
                return *this;
            }


            bool operator == ( const DBValue& other ) const
            {
                return indicator_ == other.indicator_ && value_ == other.value_;
            }

            bool operator != ( const DBValue& other ) const
            {
                return indicator_ != other.indicator_ || value_ != other.value_;
            }

            operator std::optional<T> ( ) const
            {
                if ( has_value( ) )
                {
                    return value_;
                }
                return {};
            }


            [[nodiscard]] 
            SQLLEN* Indicator( ) const noexcept
            {
                return &indicator_;
            }
            [[nodiscard]]
            const T* data( ) const noexcept
            {
                return &value_;
            }
            [[nodiscard]]
            T* data( ) noexcept
            {
                return &value_;
            }


            [[nodiscard]] 
            constexpr bool IsNull( ) const noexcept
            {
                return indicator_ == SQL_NULL_DATA;
            }

            [[nodiscard]]
            bool has_value( ) const noexcept
            {
                return indicator_ != SQL_NULL_DATA;
            }

            [[nodiscard]]
            const value_type& value( ) const
            {
                if ( has_value( ) )
                {
                    return value_;
                }
                throw std::bad_optional_access{};
            }

            template<IO::StreamWriter StreamT>
            void WriteTo( IO::BinaryWriter<StreamT>& destination ) const
            {
                bool notNull = IsNull( ) == false;
                destination.Write( notNull );
                if ( notNull )
                {
                    destination.Write( value_ );
                }
            }
            template<IO::StreamReader StreamT>
            void ReadFrom( IO::BinaryReader<StreamT>& source )
            {
                bool notNull = source.Read<bool>( );
                if ( notNull )
                {
                    value_ = source.Read<value_type>( );
                    indicator_ = 0;
                }
                else
                {
                    reset( );
                }
            }

        };
    }

    using DBBoolean = Internal::DBValue<bool>;
    using DBSByte = Internal::DBValue<SByte>;
    using DBByte = Internal::DBValue<Byte>;
    using DBInt16 = Internal::DBValue<Int16>;
    using DBUInt16 = Internal::DBValue<UInt16>;
    using DBInt32 = Internal::DBValue<Int32>;
    using DBUInt32 = Internal::DBValue<UInt32>;
    using DBInt64 = Internal::DBValue<Int64>;
    using DBUInt64 = Internal::DBValue<UInt64>;

    template<typename T>
        requires std::is_enum_v<T>
    using DBEnum = Internal::DBValue<T>;

    using DBSingle = Internal::DBValue<float>;
    using DBDouble = Internal::DBValue<double>;
    using DBDateTime = Internal::DBValue<DateTime>;
    using DBTimeSpan = Internal::DBValue<TimeSpan>;
    using DBGuid = Internal::DBValue<Guid>;
    using DBCurrency = Internal::DBValue<Currency>;
    using DBWideString = Internal::DBValue<WideString>;
    using DBAnsiString = Internal::DBValue<AnsiString>;
    using DBBinary = Internal::DBValue<Binary>;




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


    enum class FetchOrientation : SQLUSMALLINT
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

    enum class SearchPredicates : SQLSMALLINT
    {
        None = SQL_PRED_NONE,
        Unsearchable = SQL_UNSEARCHABLE,
        Char = SQL_PRED_CHAR,
        LikeOnly = SQL_LIKE_ONLY,
        Basic = SQL_PRED_BASIC,
        AllExceptLike = SQL_ALL_EXCEPT_LIKE,
        Searchable = SQL_PRED_SEARCHABLE
    };

    enum class CursorSensitivity : SQLULEN
    {
        /// <summary>
        /// It is unspecified what the cursor type is and whether cursors on the statement 
        /// handle make visible the changes made to a result set by another cursor. Cursors 
        /// on the statement handle may make visible none, some, or all such changes. 
        /// 
        /// This is the default.
        /// </summary>
        Unspecified = SQL_UNSPECIFIED,
        /// <summary>
        /// All cursors on the statement handle show the result set without reflecting any 
        /// changes made to it by any other cursor. Insensitive cursors are read-only. 
        /// This corresponds to a static cursor, which has a concurrency that is read-only.
        /// </summary>
        Insensitive = SQL_INSENSITIVE,
        /// <summary>
        /// All cursors on the statement handle make visible all changes made to a result 
        /// set by another cursor.
        /// </summary>
        Sensitive = SQL_SENSITIVE
    };

    enum class CursorType : SQLULEN
    {
        /// <summary>
        /// The cursor only scrolls forward.
        /// </summary>
        ForwardOnly = SQL_CURSOR_FORWARD_ONLY,
        /// <summary>
        /// The driver saves and uses the keys for the number of rows specified in the 
        /// KeysetSize( ) (SQL_ATTR_KEYSET_SIZE) statement attribute.
        /// </summary>
        KeysetDriven = SQL_CURSOR_KEYSET_DRIVEN,
        /// <summary>
        /// The driver saves and uses only the keys for the rows in the rowset.
        /// </summary>
        Dynamic = SQL_CURSOR_DYNAMIC,
        /// <summary>
        /// The data in the result set is static.
        /// </summary>
        Static = SQL_CURSOR_STATIC,
        /// <summary>
        /// The default is ForwardOnly
        /// </summary>
        Default = ForwardOnly
    };

    enum class SimulateCursor : UInt64
    {
        /// <summary>
        /// The driver does not guarantee that simulated positioned update or delete 
        /// statements will affect only one row; it is the application's responsibility 
        /// to do so.
        /// </summary>
        NonInique = SQL_SC_NON_UNIQUE,
        /// <summary>
        /// The driver attempts to guarantee that simulated positioned update or delete 
        /// statements affect only one row. The driver always executes such statements, 
        /// even if they might affect more than one row, such as when there is no unique key. 
        /// </summary>
        TryUnique = SQL_SC_TRY_UNIQUE,
        /// <summary>
        /// The driver guarantees that simulated positioned update or delete statements affect 
        /// only one row.
        /// </summary>
        Unique = SQL_SC_UNIQUE,
        Default = Unique
    };







    enum class SqlType : SQLSMALLINT
    {
        Unknown = SQL_UNKNOWN_TYPE,
        Char = SQL_CHAR,
        Numeric = SQL_NUMERIC,
        Decimal = SQL_DECIMAL,
        Integer = SQL_INTEGER,
        SmallInt = SQL_SMALLINT,
        VarChar = SQL_VARCHAR,
        LongVarChar = SQL_LONGVARCHAR,
        WChar = SQL_WCHAR,
        WVarChar = SQL_WVARCHAR,
        WLongVarChar = SQL_WLONGVARCHAR,
        Real = SQL_REAL,
        Float = SQL_FLOAT,
        Double = SQL_DOUBLE,
        Bit = SQL_BIT,
        TinyInt = SQL_TINYINT,
        BigInt = SQL_BIGINT,
        Binary = SQL_BINARY,
        VarBinary = SQL_VARBINARY,
        LongVarBinary = SQL_LONGVARBINARY,
        Date = SQL_TYPE_DATE,
        DateTime = SQL_DATETIME,
        Time = SQL_TYPE_TIME,
        TimeStamp = SQL_TYPE_TIMESTAMP,
        //UTCDateTime = SQL_TYPE_UTCDATETIME,
        //UTCTime = SQL_TYPE_UTCTIME,
        IntervalMonth = SQL_INTERVAL_MONTH,
        IntervalYear = SQL_INTERVAL_YEAR,
        IntervalYearToMonth = SQL_INTERVAL_YEAR_TO_MONTH,
        IntervalDay = SQL_INTERVAL_DAY,
        IntervalHour = SQL_INTERVAL_HOUR,
        IntervalMinute = SQL_INTERVAL_MINUTE,
        IntervalSecond = SQL_INTERVAL_SECOND,
        IntervalDayToHour = SQL_INTERVAL_DAY_TO_HOUR,
        IntervalDayToMinute = SQL_INTERVAL_DAY_TO_MINUTE,
        IntervalDayToSecond = SQL_INTERVAL_DAY_TO_SECOND,
        IntervalHourToMinute = SQL_INTERVAL_HOUR_TO_MINUTE,
        IntervalHourToSecond = SQL_INTERVAL_HOUR_TO_SECOND,
        IntervalMinuteToSecond = SQL_INTERVAL_MINUTE_TO_SECOND,
        Guid = SQL_GUID,

        // Values specific to MS SQL Server:
        TimeStampOffset = MsSql::SQL_SS_TIMESTAMPOFFSET,
        Time2 = MsSql::SQL_SS_TIME2,
        //SmallMoney = MsSql::SQL_SS_SM;
    };
    enum class NativeType : SQLSMALLINT
    {
        Char = SQL_C_CHAR,
        WideChar = SQL_C_WCHAR,
        Long = SQL_C_LONG,
        Short = SQL_C_SHORT,
        Single = SQL_C_FLOAT,
        Double = SQL_C_DOUBLE,
        Numeric = SQL_C_NUMERIC,
        Default = SQL_C_DEFAULT,
        SignedOffset = SQL_SIGNED_OFFSET,
        UnsignedOffset = SQL_UNSIGNED_OFFSET,
        Date = SQL_C_DATE,
        Time = SQL_C_TIME,
        TimeStamp = SQL_C_TIMESTAMP,
        TypeDate = SQL_C_TYPE_DATE,
        TypeTime = SQL_C_TYPE_TIME,
        TypeTimeStamp = SQL_C_TYPE_TIMESTAMP,
        IntervalYear = SQL_C_INTERVAL_YEAR,
        IntervalMonth = SQL_C_INTERVAL_MONTH,
        IntervalDay = SQL_C_INTERVAL_DAY,
        IntervalHour = SQL_C_INTERVAL_HOUR,
        IntervalMinute = SQL_C_INTERVAL_MINUTE,
        IntervalSecond = SQL_C_INTERVAL_SECOND,
        IntervalYearToMonth = SQL_C_INTERVAL_YEAR_TO_MONTH,
        IntervalDayToHour = SQL_C_INTERVAL_DAY_TO_HOUR,
        IntervalDayToMinute = SQL_C_INTERVAL_DAY_TO_MINUTE,
        IntervalDayToSecond = SQL_C_INTERVAL_DAY_TO_SECOND,
        IntervalHourToMinute = SQL_C_INTERVAL_HOUR_TO_MINUTE,
        IntervalHourToSecond = SQL_C_INTERVAL_HOUR_TO_SECOND,
        IntervalMinuteToSecond = SQL_C_INTERVAL_MINUTE_TO_SECOND,
        Binary = SQL_C_BINARY,
        Bit = SQL_C_BIT,
        Boolean = SQL_C_BIT,
        Int64 = SQL_C_SBIGINT,
        UInt64 = SQL_C_UBIGINT,
        TinyInt = SQL_C_TINYINT,
        Int32 = SQL_C_SLONG,
        Int16 = SQL_C_SSHORT,
        SByte = SQL_C_STINYINT,
        UInt32 = SQL_C_ULONG,
        UInt16 = SQL_C_USHORT,
        Byte = SQL_C_UTINYINT,
        Bookmark = SQL_C_BOOKMARK,
        Guid = SQL_C_GUID,
    };


    enum class Concurrency
    {
        Unknown,
        /// <summary>
        /// Cursor is read-only. No updates are allowed.
        /// </summary>
        ReadOnly = SQL_CONCUR_READ_ONLY,
        /// <summary>
        /// Cursor uses the lowest level of locking sufficient to ensure that the row can be updated.
        /// </summary>
        Lock = SQL_CONCUR_LOCK,
        /// <summary>
        /// Cursor uses optimistic concurrency control, comparing row versions.
        /// </summary>
        RowVersion = SQL_CONCUR_ROWVER,
        /// <summary>
        /// Cursor uses optimistic concurrency control, comparing values.
        /// </summary>
        Values = SQL_CONCUR_VALUES,
        Default = ReadOnly
    };


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

    using DBTimeStamp = Internal::DBValue<TimeStamp>;


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

    using DBDate = Internal::DBValue<Date>;

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


    using DBTime = Internal::DBValue<Time>;


    class Time2 : public MsSql::DBTIME2
    {
    public:
        using Base = MsSql::DBTIME2;
        Time2( )
            : Base{}
        {
        }

        DateTime ToDateTime( ) const
        {
            auto ticks = DateTime::TimeToTicks( hour, minute, second ) + ( fraction / 100 );
            return DateTime( ticks );
        }
        TimeSpan ToTimeSpan( ) const
        {
            auto ticks = DateTime::TimeToTicks( hour, minute, second ) + ( fraction / 100 );
            return TimeSpan( ticks );
        }

        Time2& operator = ( const DateTime& dateTime )
        {
            hour = dateTime.Hour( );
            minute = dateTime.Minute( );
            second = dateTime.Second( );
            fraction = ( dateTime.Ticks( ) % DateTime::TicksPerSecond ) * 100;
            return *this;
        }
    };

    using DBTime2 = Internal::DBValue<Time2>;


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

    using DBInterval = Internal::DBValue<Interval>;

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

    using DBTimestampOffset = Internal::DBValue<TimestampOffset>;


    class Numeric : public SQL_NUMERIC_STRUCT
    {
    public:
        using Base = SQL_NUMERIC_STRUCT;

        Numeric( )
            : Base{}
        {
        }
    };

    using DBNumeric = Internal::DBValue<Numeric>;
    using DBDecimal = Internal::DBValue<Numeric>;

    struct Money
    {
        LONG moneyHigh = 0;
        ULONG moneyLow = 0;
    };

    using DBMoney = Internal::DBValue<Money>;

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

    using DBRowVersion = Internal::DBValue<RowVersion>;


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

        static SQLHANDLE AllocateHandle( SQLHANDLE inputHandle = SQL_NULL_HANDLE, ODBC::HandleType handleType = HandleType )
        {
            SQLHANDLE result = InvalidHandle;
            auto rc = SQLAllocHandle( static_cast<SQLSMALLINT>( handleType ), inputHandle, &result );
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
        friend class Connection;
        friend class Environment;
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



        UInt16 GetUInt16Field( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier ) const
        {
            UInt16 value = 0;
            SQLINTEGER actualLength = 0;
            GetFieldW( recordNumber, fieldIdentifier, &value, SQL_IS_USMALLINT, &actualLength );
            return value;
        }

        Int16 GetInt16Field( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier ) const
        {
            Int16 value = 0;
            SQLINTEGER actualLength = 0;
            GetFieldW( recordNumber, fieldIdentifier, &value, SQL_IS_SMALLINT, &actualLength );
            return value;
        }

        UInt64 GetUInt64Field( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier ) const
        {
            UInt64 value = 0;
            SQLINTEGER actualLength = 0;
            GetFieldW( recordNumber, fieldIdentifier, &value, SQL_IS_UINTEGER, &actualLength );
            return value;
        }

        Int64 GetInt64Field( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier ) const
        {
            Int64 value = 0;
            SQLINTEGER actualLength = 0;
            GetFieldW( recordNumber, fieldIdentifier, &value, SQL_IS_INTEGER, &actualLength );
            return value;
        }

        SQLPOINTER GetPointerField( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier ) const
        {
            SQLPOINTER value = nullptr;
            SQLINTEGER actualLength = 0;
            GetFieldW( recordNumber, fieldIdentifier, &value, SQL_IS_INTEGER, &actualLength );
            return value;
        }

        WideString GetWideStringField( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier ) const
        {
            wchar_t value[ 1024 ] = {};
            SQLINTEGER actualLength = 0;
            GetFieldW( recordNumber, fieldIdentifier, &value, sizeof( value ), &actualLength );
            WideString result( value, static_cast< size_t >( actualLength ) );
            return result;
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

        Result SetUInt16Field( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier, UInt16 value ) const
        {
            return SetFieldW( recordNumber, fieldIdentifier, reinterpret_cast< SQLPOINTER >(value), SQL_IS_USMALLINT );
        }
        Result SetInt16Field( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier, Int16 value ) const
        {
            return SetFieldW( recordNumber, fieldIdentifier, reinterpret_cast< SQLPOINTER >( value ), SQL_IS_SMALLINT );
        }
        Result SetUInt64Field( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier, UInt64 value ) const
        {
            return SetFieldW( recordNumber, fieldIdentifier, reinterpret_cast< SQLPOINTER >( value ), SQL_IS_UINTEGER );
        }
        Result SetInt64Field( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier, Int64 value ) const
        {
            return SetFieldW( recordNumber, fieldIdentifier, reinterpret_cast< SQLPOINTER >( value ), SQL_IS_INTEGER );
        }

        Result SetPointerField( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier, SQLPOINTER value ) const
        {
            return SetFieldW( recordNumber, fieldIdentifier, value, SQL_IS_POINTER );
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

        // Access to the header fields


        bool UserAllocated( ) const
        {
            SQLSMALLINT userAllocated = GetUInt16Field( 0, SQL_DESC_ALLOC_TYPE );
            return userAllocated == SQL_DESC_ALLOC_USER;
        }


        Result SetArraySize( size_t arraySize ) const
        {
            return SetUInt64Field( 0, SQL_DESC_ARRAY_SIZE, arraySize );
        }

        size_t ArraySize( ) const
        {
            return GetUInt64Field( 0, SQL_DESC_ARRAY_SIZE );
        }

        Result SetStatusArrayPointer( SQLUSMALLINT* statusArray ) const
        {
            return SetPointerField( 0, SQL_DESC_ARRAY_STATUS_PTR, statusArray );
        }

        SQLUSMALLINT* StatusArrayPointer( ) const
        {
            return static_cast< SQLUSMALLINT* >( GetPointerField( 0, SQL_DESC_ARRAY_STATUS_PTR) );
        }

        Result SetBindOffsetPointer( SQLLEN* bindOffsetPointer ) const
        {
            return SetPointerField( 0, SQL_DESC_BIND_OFFSET_PTR, bindOffsetPointer );
        }

        SQLLEN* BindOffsetPointer( ) const
        {
            return static_cast< SQLLEN* >( GetPointerField( 0, SQL_DESC_BIND_OFFSET_PTR ) );
        }

        Result SetBindByColumn( ) const
        {
            return SetUInt64Field( 0, SQL_DESC_BIND_TYPE, SQL_BIND_BY_COLUMN );
        }
        bool BindByColumn( ) const
        {
            return GetUInt64Field( 0, SQL_DESC_BIND_TYPE ) == SQL_BIND_BY_COLUMN;
        }

        Int16 RecordCount( ) const
        {
            return GetInt16Field( 0, SQL_DESC_COUNT );
        }

        Result SetRowsProcessedPointer( SQLULEN* bindOffsetPointer ) const
        {
            return SetPointerField( 0, SQL_DESC_ROWS_PROCESSED_PTR, bindOffsetPointer );
        }

        SQLULEN* RowsProcessedPointer( ) const
        {
            return static_cast< SQLULEN* >( GetPointerField( 0, SQL_DESC_ROWS_PROCESSED_PTR ) );
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

        const Statement& Statement( ) const
        {
            return *statement_;
        }

        bool Read( )
        {
            auto rc = Fetch( );
            if ( rc != ODBC::Result::NoData )
            {
                this->AfterFetch( );
                return true;
            }
            return false;
        }

        [[nodiscard]] SQLHANDLE Handle( ) const noexcept;
        inline Result GetData( SQLUSMALLINT columnOrParameterNumber, NativeType targetValueDataType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrTargetValueActualLength ) const;

    protected:
        virtual void AfterFetch( )
        {

        }
        inline Result Fetch( ) const;
        inline Result FetchScroll( ODBC::FetchOrientation fetchOrientation, SQLLEN fetchOffset ) const;
        
        inline Result BindColumn( SQLUSMALLINT columnNumber, NativeType targetType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrLength ) const;


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

        template<size_t maxSize>
        Result BindBinary( SQLUSMALLINT columnNumber, FixedDBBinary<maxSize>* targetAddress ) const
        {
            return BindColumn( columnNumber, NativeType::Binary, targetAddress->data( ), maxSize, targetAddress->Indicator( ) );
        }
        template<size_t maxSize>
        Result BindWideString( SQLUSMALLINT columnNumber, FixedDBWideString<maxSize>* targetAddress ) const
        {
            return BindColumn( columnNumber, NativeType::WideChar, targetAddress->data( ), ( maxSize + 1 )* sizeof( wchar_t ), targetAddress->Indicator( ) );
        }
        template<size_t maxSize>
        Result BindAnsiString( SQLUSMALLINT columnNumber, FixedDBAnsiString<maxSize>* targetAddress ) const
        {
            return BindColumn( columnNumber, NativeType::Char, targetAddress->data( ), maxSize + 1, targetAddress->Indicator( ) );
        }

    public:
        /// <summary>
        /// Gets the value of the specified column as a DBBoolean.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] 
        inline DBBoolean GetDBBoolean( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBByte.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]] 
        inline DBByte GetDBByte( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBSByte.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBSByte GetDBSByte( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBInt16.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBInt16 GetDBInt16( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBUInt16.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBUInt16 GetDBUInt16( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBInt32.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBInt32 GetDBInt32( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBUInt32.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBUInt32 GetDBUInt32( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBInt64.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBInt64 GetDBInt64( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBUInt64.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBUInt64 GetDBUInt64( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBNumeric.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBNumeric GetDBNumeric( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBDecimal.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBDecimal GetDBDecimal( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBSingle.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBSingle GetDBSingle( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBDouble.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBDouble GetDBDouble( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBCurrency.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBCurrency GetDBCurrency( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBDateTime.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBDateTime GetDBDateTime( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBTimestampOffset.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBTimestampOffset GetDBTimestampOffset( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBDate.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBDate GetDBDate( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBTime.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBTime GetDBTime( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBTimeSpan.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBTimeSpan GetDBTimeSpan( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBWideString.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBWideString GetDBWideString( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBAnsiString.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBAnsiString GetDBAnsiString( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBBinary.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBBinary GetDBBinary( SQLUSMALLINT columnNumber ) const;

        /// <summary>
        /// Gets the value of the specified column as a DBGuid.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBGuid GetDBGuid( SQLUSMALLINT columnNumber ) const;
        /// <summary>
        /// Gets the value of the specified column as a DBRowVersion.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        inline DBRowVersion GetDBRowVersion( SQLUSMALLINT columnNumber ) const;

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
        inline Binary GetBinary( SQLUSMALLINT columnNumber ) const;
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
        Result BindColumn( SQLUSMALLINT columnNumber, NativeType targetType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrLength ) const
        {
            auto rc = SQLBindCol( Handle( ), columnNumber, static_cast<SQLSMALLINT>(targetType), targetValue, targetValueMaxLength, nullIndicatorOrLength );
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
        Result BindSingleColumn( SQLUSMALLINT columnNumber, float* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Single, targetAddress, sizeof( float ), nullIndicatorOrActualLength );
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

        template<size_t maxSize>
        Result BindBinaryColumn( SQLUSMALLINT columnNumber, FixedDBBinary<maxSize>* targetAddress ) const
        {
            return BindColumn( columnNumber, NativeType::Binary, targetAddress->data(), maxSize, targetAddress->Indicator() );
        }
        template<size_t maxSize>
        Result BindWideStringColumn( SQLUSMALLINT columnNumber, FixedDBWideString<maxSize>* targetAddress ) const
        {
            return BindColumn( columnNumber, NativeType::WideChar, targetAddress->data( ), (maxSize + 1) * sizeof(wchar_t), targetAddress->Indicator( ) );
        }
        template<size_t maxSize>
        Result BindAnsiStringColumn( SQLUSMALLINT columnNumber, FixedDBAnsiString<maxSize>* targetAddress ) const
        {
            return BindColumn( columnNumber, NativeType::Char, targetAddress->data( ), maxSize + 1, targetAddress->Indicator( ) );
        }



        /// <summary>
        /// Binds a buffer to a parameter marker in an SQL statement. BindParameter supports 
        /// binding to a Unicode C data type, even if the underlying driver does not support 
        /// Unicode data.
        /// </summary>
        /// <param name="parameterNumber">
        /// Parameter number, ordered sequentially in increasing parameter order, starting at 1.
        /// </param>
        /// <param name="parameterDirection">
        /// The direction of the parameter
        /// </param>
        /// <param name="valueType">
        /// The native C data type of the parameter.
        /// </param>
        /// <param name="parameterType">
        /// The SQL data type of the parameter.
        /// </param>
        /// <param name="columnSize">
        /// The size of the column or expression of the corresponding parameter marker. 
        /// </param>
        /// <param name="decimalDigits">
        /// The decimal digits of the column or expression of the corresponding parameter marker.
        /// </param>
        /// <param name="parameterValue">
        /// A pointer to a buffer for the parameter's data.
        /// </param>
        /// <param name="parameterValueBufferLength">
        /// Length of the ParameterValuePtr buffer in bytes.
        /// </param>
        /// <param name="lengthOrIndicator">
        /// A pointer to a buffer for the parameter's length.
        /// </param>
        /// <returns></returns>
        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, NativeType valueType, SqlType parameterType, SQLULEN columnSize, SQLSMALLINT decimalDigits, SQLPOINTER parameterValue, SQLLEN parameterValueBufferLength, SQLLEN* lengthOrIndicator ) const
        {
            auto rc = SQLBindParameter( Handle( ), parameterNumber, static_cast<SQLSMALLINT>( parameterDirection ), static_cast< SQLSMALLINT >(valueType), static_cast< SQLSMALLINT >( parameterType ), columnSize, decimalDigits, parameterValue, parameterValueBufferLength, lengthOrIndicator );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result BindBooleanParameter( SQLUSMALLINT parameterNumber, bool* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection) const
        {
            return BindParameter( parameterNumber, parameterDirection, NativeType::Boolean, SqlType::Bit, 0, 0, parameterValue, 0, nullIndicator );
        }

        Result BindBooleanParameter( SQLUSMALLINT parameterNumber, const bool* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindBooleanParameter( parameterNumber, const_cast<bool*>( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindBooleanParameter( SQLUSMALLINT parameterNumber, bool* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindBooleanParameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindBooleanParameter( SQLUSMALLINT parameterNumber, const bool* parameterValue ) const
        {
            return BindBooleanParameter( parameterNumber, const_cast< bool* >(parameterValue), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindBooleanParameter( SQLUSMALLINT parameterNumber, DBBoolean& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindBooleanParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindBooleanParameter( SQLUSMALLINT parameterNumber, const DBBoolean& parameterValue ) const
        {
            return BindBooleanParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }



        Result BindSByteParameter( SQLUSMALLINT parameterNumber, SByte* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::SByte, SqlType::TinyInt, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }

        Result BindSByteParameter( SQLUSMALLINT parameterNumber, const SByte* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindSByteParameter( parameterNumber, const_cast< SByte* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindSByteParameter( SQLUSMALLINT parameterNumber, SByte* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindSByteParameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindSByteParameter( SQLUSMALLINT parameterNumber, const SByte* parameterValue ) const
        {
            return BindSByteParameter( parameterNumber, const_cast< SByte* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindSByteParameter( SQLUSMALLINT parameterNumber, DBSByte& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindSByteParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindSByteParameter( SQLUSMALLINT parameterNumber, const DBSByte& parameterValue ) const
        {
            return BindSByteParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }


        Result BindByteParameter( SQLUSMALLINT parameterNumber, Byte* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Byte, SqlType::TinyInt, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }

        Result BindByteParameter( SQLUSMALLINT parameterNumber, const Byte* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindByteParameter( parameterNumber, const_cast< Byte* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindByteParameter( SQLUSMALLINT parameterNumber, Byte* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindByteParameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindByteParameter( SQLUSMALLINT parameterNumber, const Byte* parameterValue ) const
        {
            return BindByteParameter( parameterNumber, const_cast< Byte* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindByteParameter( SQLUSMALLINT parameterNumber, DBByte& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindByteParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindByteParameter( SQLUSMALLINT parameterNumber, const DBByte& parameterValue ) const
        {
            return BindByteParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }

        Result BindInt16Parameter( SQLUSMALLINT parameterNumber, Int16* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Int16, SqlType::SmallInt, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindInt16Parameter( SQLUSMALLINT parameterNumber, const Int16* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindInt16Parameter( parameterNumber, const_cast< Int16* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindInt16Parameter( SQLUSMALLINT parameterNumber, Int16* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindInt16Parameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindInt16Parameter( SQLUSMALLINT parameterNumber, const Int16* parameterValue ) const
        {
            return BindInt16Parameter( parameterNumber, const_cast< Int16* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindInt16Parameter( SQLUSMALLINT parameterNumber, DBInt16& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindInt16Parameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindInt16Parameter( SQLUSMALLINT parameterNumber, const DBInt16& parameterValue ) const
        {
            return BindInt16Parameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }



        Result BindUInt16Parameter( SQLUSMALLINT parameterNumber, UInt16* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::UInt16, SqlType::SmallInt, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindUInt16Parameter( SQLUSMALLINT parameterNumber, const UInt16* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindUInt16Parameter( parameterNumber, const_cast< UInt16* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindUInt16Parameter( SQLUSMALLINT parameterNumber, UInt16* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindUInt16Parameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindUInt16Parameter( SQLUSMALLINT parameterNumber, const UInt16* parameterValue ) const
        {
            return BindUInt16Parameter( parameterNumber, const_cast< UInt16* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindUInt16Parameter( SQLUSMALLINT parameterNumber, DBUInt16& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindUInt16Parameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindUInt16Parameter( SQLUSMALLINT parameterNumber, const DBUInt16& parameterValue ) const
        {
            return BindUInt16Parameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }



        Result BindInt32Parameter( SQLUSMALLINT parameterNumber, Int32* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Int32, SqlType::Integer, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindInt32Parameter( SQLUSMALLINT parameterNumber, const Int32* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindInt32Parameter( parameterNumber, const_cast< Int32* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindInt32Parameter( SQLUSMALLINT parameterNumber, Int32* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindInt32Parameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindInt32Parameter( SQLUSMALLINT parameterNumber, const Int32* parameterValue ) const
        {
            return BindInt32Parameter( parameterNumber, const_cast< Int32* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindInt32Parameter( SQLUSMALLINT parameterNumber, DBInt32& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindInt32Parameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindInt32Parameter( SQLUSMALLINT parameterNumber, const DBInt32& parameterValue ) const
        {
            return BindInt32Parameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }


        Result BindUInt32Parameter( SQLUSMALLINT parameterNumber, UInt32* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::UInt32, SqlType::Integer, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindUInt32Parameter( SQLUSMALLINT parameterNumber, const UInt32* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindUInt32Parameter( parameterNumber, const_cast< UInt32* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindUInt32Parameter( SQLUSMALLINT parameterNumber, UInt32* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindUInt32Parameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindUInt32Parameter( SQLUSMALLINT parameterNumber, const UInt32* parameterValue ) const
        {
            return BindUInt32Parameter( parameterNumber, const_cast< UInt32* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindUInt32Parameter( SQLUSMALLINT parameterNumber, DBUInt32& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindUInt32Parameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindUInt32Parameter( SQLUSMALLINT parameterNumber, const DBUInt32& parameterValue ) const
        {
            return BindUInt32Parameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }

        Result BindInt64Parameter( SQLUSMALLINT parameterNumber, Int64* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Int64, SqlType::BigInt, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindInt64Parameter( SQLUSMALLINT parameterNumber, const Int64* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindInt64Parameter( parameterNumber, const_cast< Int64* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindInt64Parameter( SQLUSMALLINT parameterNumber, Int64* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindInt64Parameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindInt64Parameter( SQLUSMALLINT parameterNumber, const Int64* parameterValue ) const
        {
            return BindInt64Parameter( parameterNumber, const_cast< Int64* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindInt64Parameter( SQLUSMALLINT parameterNumber, DBInt64& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindInt64Parameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindInt64Parameter( SQLUSMALLINT parameterNumber, const DBInt64& parameterValue ) const
        {
            return BindInt64Parameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }

        Result BindUInt64Parameter( SQLUSMALLINT parameterNumber, UInt64* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::UInt64, SqlType::BigInt, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindUInt64Parameter( SQLUSMALLINT parameterNumber, const UInt64* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindUInt64Parameter( parameterNumber, const_cast< UInt64* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindUInt64Parameter( SQLUSMALLINT parameterNumber, UInt64* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindUInt64Parameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindUInt64Parameter( SQLUSMALLINT parameterNumber, const UInt64* parameterValue ) const
        {
            return BindUInt64Parameter( parameterNumber, const_cast< UInt64* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindUInt64Parameter( SQLUSMALLINT parameterNumber, DBUInt64& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindUInt64Parameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindUInt64Parameter( SQLUSMALLINT parameterNumber, const DBUInt64& parameterValue ) const
        {
            return BindUInt64Parameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }

        

        template<typename T>
            requires std::is_enum_v<T>
        Result BindEnumParameter( SQLUSMALLINT parameterNumber, T* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            using IntegerType = std::underlying_type_t<T>;
            if constexpr ( std::is_same_v<IntegerType, bool> )
            {
                return BindParameter( parameterNumber, parameterDirection, NativeType::Boolean, SqlType::Bit, 0, 0, parameterValue, 0, nullIndicator );
            }
            else if constexpr ( std::is_same_v<IntegerType, SByte> || std::is_same_v<IntegerType, char> )
            {
                return BindParameter( parameterNumber, parameterDirection, NativeType::SByte, SqlType::TinyInt, 0, 0, parameterValue, 0, nullIndicator );
            }
            else if constexpr ( std::is_same_v<IntegerType, Byte> )
            {
                return BindParameter( parameterNumber, parameterDirection, NativeType::Byte, SqlType::TinyInt, 0, 0, parameterValue, 0, nullIndicator );
            }
            else if constexpr ( std::is_same_v<IntegerType, Int16> )
            {
                return BindParameter( parameterNumber, parameterDirection, NativeType::Int16, SqlType::SmallInt, 0, 0, parameterValue, 0, nullIndicator );
            }
            else if constexpr ( std::is_same_v<IntegerType, UInt16> )
            {
                return BindParameter( parameterNumber, parameterDirection, NativeType::UInt16, SqlType::SmallInt, 0, 0, parameterValue, 0, nullIndicator );
            }
            else if constexpr ( std::is_same_v<IntegerType, Int32> || std::is_same_v<IntegerType, long> )
            {
                return BindParameter( parameterNumber, parameterDirection, NativeType::Int32, SqlType::Integer, 0, 0, parameterValue, 0, nullIndicator );
            }
            else if constexpr ( std::is_same_v<IntegerType, UInt32> || std::is_same_v<IntegerType, unsigned long> )
            {
                return BindParameter( parameterNumber, parameterDirection, NativeType::UInt32, SqlType::Integer, 0, 0, parameterValue, 0, nullIndicator );
            }
            else if constexpr ( std::is_same_v<IntegerType, Int64> )
            {
                return BindParameter( parameterNumber, parameterDirection, NativeType::Int64, SqlType::BigInt, 0, 0, parameterValue, 0, nullIndicator );
            }
            else 
            {
                return BindParameter( parameterNumber, parameterDirection, NativeType::UInt64, SqlType::BigInt, 0, 0, parameterValue, 0, nullIndicator );
            }
        }

        template<typename T>
            requires std::is_enum_v<T>
        Result BindEnumParameter( SQLUSMALLINT parameterNumber, const T* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindEnumParameter( parameterNumber, const_cast< T* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        template<typename T>
            requires std::is_enum_v<T>
        Result BindEnumParameter( SQLUSMALLINT parameterNumber, T* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindEnumParameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        template<typename T>
            requires std::is_enum_v<T>
        Result BindEnumParameter( SQLUSMALLINT parameterNumber, const T* parameterValue ) const
        {
            return BindEnumParameter( parameterNumber, const_cast< T* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        template<typename T>
            requires std::is_enum_v<T>
        Result BindEnumParameter( SQLUSMALLINT parameterNumber, DBEnum<T>& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindEnumParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        template<typename T>
            requires std::is_enum_v<T>
        Result BindEnumParameter( SQLUSMALLINT parameterNumber, const DBEnum<T>& parameterValue ) const
        {
            return BindEnumParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }



        Result BindParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, char* parameterValue, SQLLEN parameterValueBufferLength, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::Input ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Char, SqlType::Char, columnSize, 0, parameterValue, parameterValueBufferLength, nullIndicator );
            return rc;
        }

        Result BindLongParameter( SQLUSMALLINT parameterNumber, UInt32* parameterValue, SQLLEN* nullIndicator = nullptr, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::Input ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Long, SqlType::Integer, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindShortParameter( SQLUSMALLINT parameterNumber, UInt16* parameterValue, SQLLEN* nullIndicator = nullptr, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::Input ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Long, SqlType::Integer, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }

        Result BindSingleParameter( SQLUSMALLINT parameterNumber, float* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Single, SqlType::Real, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindSingleParameter( SQLUSMALLINT parameterNumber, const float* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindSingleParameter( parameterNumber, const_cast< float* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindSingleParameter( SQLUSMALLINT parameterNumber, float* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindSingleParameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindSingleParameter( SQLUSMALLINT parameterNumber, const float* parameterValue ) const
        {
            return BindSingleParameter( parameterNumber, const_cast< float* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindSingleParameter( SQLUSMALLINT parameterNumber, DBSingle& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindSingleParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindSingleParameter( SQLUSMALLINT parameterNumber, const DBSingle& parameterValue ) const
        {
            return BindSingleParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }

        Result BindDoubleParameter( SQLUSMALLINT parameterNumber, Double* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Double, SqlType::Double, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindDoubleParameter( SQLUSMALLINT parameterNumber, const double* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindDoubleParameter( parameterNumber, const_cast< double* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindDoubleParameter( SQLUSMALLINT parameterNumber, double* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindDoubleParameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindDoubleParameter( SQLUSMALLINT parameterNumber, const double* parameterValue ) const
        {
            return BindDoubleParameter( parameterNumber, const_cast< double* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindDoubleParameter( SQLUSMALLINT parameterNumber, DBDouble& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindDoubleParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindDoubleParameter( SQLUSMALLINT parameterNumber, const DBDouble& parameterValue ) const
        {
            return BindDoubleParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }

        
        Result BindGuidParameter( SQLUSMALLINT parameterNumber, Guid* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Guid, SqlType::Guid, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindGuidParameter( SQLUSMALLINT parameterNumber, const Guid* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindGuidParameter( parameterNumber, const_cast< Guid* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindGuidParameter( SQLUSMALLINT parameterNumber, Guid* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindGuidParameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindGuidParameter( SQLUSMALLINT parameterNumber, const Guid* parameterValue ) const
        {
            return BindGuidParameter( parameterNumber, const_cast< Guid* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindGuidParameter( SQLUSMALLINT parameterNumber, DBGuid& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindGuidParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindGuidParameter( SQLUSMALLINT parameterNumber, const DBGuid& parameterValue ) const
        {
            return BindGuidParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }


        Result BindDateTimeParameter( SQLUSMALLINT parameterNumber, DateTime* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Int64, SqlType::BigInt, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindDateTimeParameter( SQLUSMALLINT parameterNumber, const DateTime* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindDateTimeParameter( parameterNumber, const_cast< DateTime* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindDateTimeParameter( SQLUSMALLINT parameterNumber, DateTime* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindDateTimeParameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindDateTimeParameter( SQLUSMALLINT parameterNumber, const DateTime* parameterValue ) const
        {
            return BindDateTimeParameter( parameterNumber, const_cast< DateTime* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindDateTimeParameter( SQLUSMALLINT parameterNumber, DBDateTime& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindDateTimeParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindDateTimeParameter( SQLUSMALLINT parameterNumber, const DBDateTime& parameterValue ) const
        {
            return BindDateTimeParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }

        Result BindTimeSpanParameter( SQLUSMALLINT parameterNumber, TimeSpan* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Int64, SqlType::BigInt, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindTimeSpanParameter( SQLUSMALLINT parameterNumber, const TimeSpan* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindTimeSpanParameter( parameterNumber, const_cast< TimeSpan* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindTimeSpanParameter( SQLUSMALLINT parameterNumber, TimeSpan* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindTimeSpanParameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindTimeSpanParameter( SQLUSMALLINT parameterNumber, const TimeSpan* parameterValue ) const
        {
            return BindTimeSpanParameter( parameterNumber, const_cast< TimeSpan* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindTimeSpanParameter( SQLUSMALLINT parameterNumber, DBTimeSpan& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindTimeSpanParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindTimeSpanParameter( SQLUSMALLINT parameterNumber, const DBTimeSpan& parameterValue ) const
        {
            return BindTimeSpanParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }

        Result BindCurrencyParameter( SQLUSMALLINT parameterNumber, Currency* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Int64, SqlType::BigInt, 0, 0, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindCurrencyParameter( SQLUSMALLINT parameterNumber, const Currency* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindCurrencyParameter( parameterNumber, const_cast< Currency* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindCurrencyParameter( SQLUSMALLINT parameterNumber, Currency* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindCurrencyParameter( parameterNumber, parameterValue, nullptr, parameterDirection );
        }
        Result BindCurrencyParameter( SQLUSMALLINT parameterNumber, const Currency* parameterValue ) const
        {
            return BindCurrencyParameter( parameterNumber, const_cast< Currency* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindCurrencyParameter( SQLUSMALLINT parameterNumber, DBCurrency& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindCurrencyParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindCurrencyParameter( SQLUSMALLINT parameterNumber, const DBCurrency& parameterValue ) const
        {
            return BindCurrencyParameter( parameterNumber, parameterValue.data( ), parameterValue.Indicator( ) );
        }



        Result BindTimeStampParameter( SQLUSMALLINT parameterNumber, SQLSMALLINT precisionOfFraction, ODBC::TimeStamp* parameterValue, SQLLEN* nullIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLSMALLINT columnSize = static_cast<SQLSMALLINT>( 20 ) + precisionOfFraction;
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::TypeTimeStamp, SqlType::TimeStamp, columnSize, precisionOfFraction, parameterValue, 0, nullIndicator );
            return rc;
        }
        Result BindTimeStampParameter( SQLUSMALLINT parameterNumber, SQLSMALLINT precisionOfFraction, const TimeStamp* parameterValue, SQLLEN* nullIndicator ) const
        {
            return BindTimeStampParameter( parameterNumber, precisionOfFraction, const_cast< TimeStamp* >( parameterValue ), nullIndicator, ODBC::ParameterDirection::Input );
        }
        Result BindTimeStampParameter( SQLUSMALLINT parameterNumber, SQLSMALLINT precisionOfFraction, TimeStamp* parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            return BindTimeStampParameter( parameterNumber, precisionOfFraction, parameterValue, nullptr, parameterDirection );
        }
        Result BindTimeStampParameter( SQLUSMALLINT parameterNumber, SQLSMALLINT precisionOfFraction, const TimeStamp* parameterValue ) const
        {
            return BindTimeStampParameter( parameterNumber, precisionOfFraction, const_cast< TimeStamp* >( parameterValue ), nullptr, ODBC::ParameterDirection::Input );
        }
        Result BindTimeStampParameter( SQLUSMALLINT parameterNumber, SQLSMALLINT precisionOfFraction, DBTimeStamp& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::InputOutput ) const
        {
            return BindTimeStampParameter( parameterNumber, precisionOfFraction, parameterValue.data( ), parameterValue.Indicator( ), parameterDirection );
        }
        Result BindTimeStampParameter( SQLUSMALLINT parameterNumber, SQLSMALLINT precisionOfFraction, const DBTimeStamp& parameterValue ) const
        {
            return BindTimeStampParameter( parameterNumber, precisionOfFraction, parameterValue.data( ), parameterValue.Indicator( ) );
        }

        Result BindVarCharParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, char* parameterValue, SQLLEN parameterValueBufferLength, SQLLEN* lengthOrIndicator, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::Input ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Char, SqlType::VarChar, columnSize, 0, parameterValue, parameterValueBufferLength, lengthOrIndicator );
            return rc;
        }
        Result BindVarCharParameter( SQLUSMALLINT parameterNumber, const AnsiString& parameterValue, SQLLEN* lengthOrIndicator = nullptr, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::Input ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Char, SqlType::VarChar, 0, 0, const_cast< char* >( parameterValue.data() ), parameterValue.size(), lengthOrIndicator );
            return rc;
        }

        template<size_t maxSize>
        Result BindVarCharParameter( SQLUSMALLINT parameterNumber, FixedDBAnsiString<maxSize>& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::Input ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Char, SqlType::VarChar, maxSize + 1, 0, parameterValue.data( ), parameterValue.size( ), parameterValue.Indicator( ) );
            return rc;
        }

        template<size_t maxSize>
        Result BindFixedDBAnsiStringParameter( SQLUSMALLINT parameterNumber, FixedDBAnsiString<maxSize>& parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Char, SqlType::VarChar, maxSize + 1, 0, parameterValue.data( ), parameterValue.size( ), parameterValue.Indicator( ) );
            return rc;
        }
        template<size_t maxSize>
        Result BindFixedDBAnsiStringParameter( SQLUSMALLINT parameterNumber, const FixedDBAnsiString<maxSize>& parameterValue ) const
        {
            auto rc = BindParameter( parameterNumber, ODBC::ParameterDirection::Input, NativeType::Char, SqlType::VarChar, maxSize + 1, 0, const_cast<char*>(parameterValue.data( )), parameterValue.size( ), const_cast< FixedDBAnsiString<maxSize>& >(parameterValue).Indicator( ) );
            return rc;
        }


        Result BindNVarCharParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, wchar_t* parameterValue, SQLLEN parameterValueBufferLength, SQLLEN* lengthOrIndicator, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::Input ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::WideChar, SqlType::WVarChar, columnSize, 0, parameterValue, parameterValueBufferLength, lengthOrIndicator );
            return rc;
        }

        template<size_t maxSize>
        Result BindNVarCharParameter( SQLUSMALLINT parameterNumber, FixedDBWideString<maxSize>& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::Input ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::WideChar, SqlType::WVarChar, maxSize + 1, 0, parameterValue.data(), parameterValue.size(), parameterValue.Indicator() );
            return rc;
        }
        template<size_t maxSize>
        Result BindFixedDBWideStringParameter( SQLUSMALLINT parameterNumber, FixedDBWideString<maxSize>& parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::WideChar, SqlType::WVarChar, maxSize + 1, 0, parameterValue.data( ), parameterValue.size( ), parameterValue.Indicator( ) );
            return rc;
        }
        template<size_t maxSize>
        Result BindFixedDBWideStringParameter( SQLUSMALLINT parameterNumber, const FixedDBWideString<maxSize>& parameterValue ) const
        {
            auto rc = BindParameter( parameterNumber, ODBC::ParameterDirection::Input, NativeType::WideChar, SqlType::WVarChar, maxSize + 1, 0, const_cast<wchar_t*>(parameterValue.data( )), parameterValue.size( )*sizeof(wchar_t), const_cast<FixedDBWideString<maxSize>&>( parameterValue ).Indicator( ) );
            return rc;
        }




        Result BindNVarCharParameter( SQLUSMALLINT parameterNumber, const WideString& parameterValue, SQLLEN* lengthOrIndicator = nullptr, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::Input ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::WideChar, SqlType::WVarChar, 0, 0, const_cast<wchar_t*>(parameterValue.data()), parameterValue.size(), lengthOrIndicator );
            return rc;
        }
        Result BindVarBinaryParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, Byte* parameterValue, SQLLEN parameterValueBufferLength, SQLLEN* lengthOrIndicator, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::Input ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Binary, SqlType::VarBinary, columnSize, 0, parameterValue, parameterValueBufferLength, lengthOrIndicator );
            return rc;
        }
        Result BindVarBinaryParameter( SQLUSMALLINT parameterNumber, std::vector<Byte>& parameterValue, SQLLEN* lengthOrIndicator = nullptr, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::Input ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Binary, SqlType::VarBinary, 0, 0, const_cast<Byte*>(parameterValue.data()), parameterValue.size(), lengthOrIndicator );
            return rc;
        }

        template<size_t maxSize>
        Result BindVarBinaryParameter( SQLUSMALLINT parameterNumber, FixedDBBinary<maxSize>& parameterValue, ODBC::ParameterDirection parameterDirection = ODBC::ParameterDirection::Input ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Binary, SqlType::VarBinary, maxSize, 0, parameterValue.data( ), parameterValue.size( ), parameterValue.Indicator() );
            return rc;
        }

        template<size_t maxSize>
        Result BindFixedDBBinaryParameter( SQLUSMALLINT parameterNumber, FixedDBBinary<maxSize>& parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Binary, SqlType::VarBinary, maxSize, 0, parameterValue.data( ), parameterValue.size( ), parameterValue.Indicator( ) );
            return rc;
        }
        template<size_t maxSize>
        Result BindFixedDBBinaryParameter( SQLUSMALLINT parameterNumber, const FixedDBBinary<maxSize>& parameterValue ) const
        {
            auto rc = BindParameter( parameterNumber, ODBC::ParameterDirection::Input, NativeType::Binary, SqlType::VarBinary, maxSize, 0, const_cast<Byte*>(parameterValue.data( )), parameterValue.size( ), const_cast< FixedDBBinary<maxSize>& >(parameterValue).Indicator( ) );
            return rc;
        }

        Result BindBinaryParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, Binary& parameterValue, SQLLEN* lengthOrIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( );
            auto rc = BindVarBinaryParameter( parameterNumber, columnSize, parameterValue.data( ), parameterValueBufferLength, lengthOrIndicator, parameterDirection );
            return rc;
        }
        Result BindBinaryParameter( SQLUSMALLINT parameterNumber, Binary& parameterValue, SQLLEN* lengthOrIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( );
            auto rc = BindVarBinaryParameter( parameterNumber, 0, parameterValue.data( ), parameterValueBufferLength, lengthOrIndicator, parameterDirection );
            return rc;
        }
        Result BindBinaryParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, const Binary& parameterValue, SQLLEN* lengthOrIndicator ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( );
            auto rc = BindVarBinaryParameter( parameterNumber, columnSize, const_cast<Byte*>( parameterValue.data( ) ), parameterValueBufferLength, lengthOrIndicator, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindBinaryParameter( SQLUSMALLINT parameterNumber, const Binary& parameterValue, SQLLEN* lengthOrIndicator = nullptr) const
        {
            return BindBinaryParameter( parameterNumber, 0, parameterValue, lengthOrIndicator );
        }

        Result BindBinaryParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, const Binary& parameterValue ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( );
            auto rc = BindVarBinaryParameter( parameterNumber, columnSize, const_cast< Byte* >( parameterValue.data( ) ), parameterValueBufferLength, nullptr, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindBinaryParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, const DBBinary& parameterValue ) const
        {
            if ( parameterValue.IsNull( ) )
            {
                return BindVarBinaryParameter( parameterNumber, columnSize, nullptr,0, parameterValue.Indicator( ), ODBC::ParameterDirection::Input );
            }
            else
            {
                const auto& binary = parameterValue.value( );
                return BindBinaryParameter( parameterNumber, columnSize, binary, parameterValue.Indicator() );
            }
        }
        Result BindBinaryParameter( SQLUSMALLINT parameterNumber, const DBBinary& parameterValue ) const
        {
            return BindBinaryParameter( parameterNumber, 0, parameterValue );
        }

        Result BindAnsiStringParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, AnsiString& parameterValue, SQLLEN* lengthOrIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindVarCharParameter( parameterNumber, columnSize, parameterValue.data(), static_cast<SQLLEN>(parameterValue.size()), lengthOrIndicator, parameterDirection );
            return rc;
        }
        Result BindAnsiStringParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, const AnsiString& parameterValue, SQLLEN* lengthOrIndicator ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindVarCharParameter( parameterNumber, columnSize, const_cast<char*>(parameterValue.data( )), parameterValueBufferLength, lengthOrIndicator, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindAnsiStringParameter( SQLUSMALLINT parameterNumber, AnsiString& parameterValue, SQLLEN* lengthOrIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindVarCharParameter( parameterNumber, 0, parameterValue.data( ), parameterValueBufferLength, lengthOrIndicator, parameterDirection );
            return rc;
        }
        Result BindAnsiStringParameter( SQLUSMALLINT parameterNumber, const AnsiString& parameterValue, SQLLEN* lengthOrIndicator ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindVarCharParameter( parameterNumber, 0, const_cast< char* >( parameterValue.data( ) ), parameterValueBufferLength, lengthOrIndicator, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindAnsiStringParameter( SQLUSMALLINT parameterNumber, AnsiString& parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindVarCharParameter( parameterNumber, 0, parameterValue.data( ), parameterValueBufferLength, nullptr, parameterDirection );
            return rc;
        }
        Result BindAnsiStringParameter( SQLUSMALLINT parameterNumber, const AnsiString& parameterValue ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindVarCharParameter( parameterNumber, 0, const_cast< char* >( parameterValue.data( ) ), parameterValueBufferLength, nullptr, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindAnsiStringParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, const DBAnsiString& parameterValue ) const
        {
            if ( parameterValue.IsNull( ) )
            {
                return BindVarCharParameter( parameterNumber, columnSize, nullptr, 0, parameterValue.Indicator(), ODBC::ParameterDirection::Input );
            }
            else
            {
                const auto& str = parameterValue.value( );
                SQLLEN parameterValueBufferLength = str.Length( ) + 1;
                return BindVarCharParameter( parameterNumber, columnSize, const_cast< char* >( str.data( ) ), parameterValueBufferLength, parameterValue.Indicator( ), ODBC::ParameterDirection::Input );
            }
        }
        Result BindAnsiStringParameter( SQLUSMALLINT parameterNumber, const DBAnsiString& parameterValue ) const
        {
            return BindAnsiStringParameter( parameterNumber, 0, parameterValue );
        }

        Result BindWideStringParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, WideString& parameterValue, SQLLEN* lengthOrIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindNVarCharParameter( parameterNumber, columnSize, parameterValue.data( ), parameterValueBufferLength, lengthOrIndicator, parameterDirection );
            return rc;
        }
        Result BindWideStringParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, const WideString& parameterValue, SQLLEN* lengthOrIndicator ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindNVarCharParameter( parameterNumber, columnSize, const_cast< wchar_t* >( parameterValue.data( ) ), parameterValueBufferLength, lengthOrIndicator, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindWideStringParameter( SQLUSMALLINT parameterNumber, WideString& parameterValue, SQLLEN* lengthOrIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindNVarCharParameter( parameterNumber, 0, parameterValue.data( ), parameterValueBufferLength, lengthOrIndicator, parameterDirection );
            return rc;
        }
        Result BindWideStringParameter( SQLUSMALLINT parameterNumber, const WideString& parameterValue, SQLLEN* lengthOrIndicator ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindNVarCharParameter( parameterNumber, 0, const_cast< wchar_t* >( parameterValue.data( ) ), parameterValueBufferLength, lengthOrIndicator, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindWideStringParameter( SQLUSMALLINT parameterNumber, WideString& parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindNVarCharParameter( parameterNumber, 0, parameterValue.data( ), parameterValueBufferLength, nullptr, parameterDirection );
            return rc;
        }
        Result BindWideStringParameter( SQLUSMALLINT parameterNumber, const WideString& parameterValue ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindNVarCharParameter( parameterNumber, 0, const_cast< wchar_t* >( parameterValue.data( ) ), parameterValueBufferLength, nullptr, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindWideStringParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, const DBWideString& parameterValue ) const
        {
            if ( parameterValue.IsNull( ) )
            {
                return BindNVarCharParameter( parameterNumber, columnSize, nullptr, 0, parameterValue.Indicator( ), ODBC::ParameterDirection::Input );
            }
            else
            {
                const auto& str = parameterValue.value( );
                SQLLEN parameterValueBufferLength = str.Length( ) + 1;
                return BindNVarCharParameter( parameterNumber, columnSize, const_cast< wchar_t* >( str.data( ) ), parameterValueBufferLength, parameterValue.Indicator( ), ODBC::ParameterDirection::Input );
            }
        }
        Result BindWideStringParameter( SQLUSMALLINT parameterNumber, const DBWideString& parameterValue ) const
        {
            return BindWideStringParameter( parameterNumber, 0, parameterValue );
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
        ODBC::SqlType ColumnConciseType( SQLUSMALLINT columnNumber ) const
        {
            return static_cast< ODBC::SqlType >( GetInt64ColumnAttribute( columnNumber, SQL_DESC_CONCISE_TYPE ) );
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
        /// <para>
        /// Returns a numeric value that is either the maximum or actual character length of a character 
        /// string or binary data type. It is the maximum character length for a fixed-length data type, 
        /// or the actual character length for a variable-length data type. Its value always excludes 
        /// the null-termination byte that ends the character string.
        /// </para>
        /// <para>
        /// For the decimal and numeric types, it returns the precision of the column.
        /// </para>
        /// <para>
        /// The return values for other column types appears consistent, like the function returning 53 
        /// for a nullable float column; which is the precision, in bits, for a 64-bit floating point value.  
        /// </para>
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

        /// <summary>
        /// Returns a std::optional&lt;bool&gt; object indicating whether the column accepts NULL values 
        /// or not. If has_value() returns false, it is not known whether the column accepts NULL values 
        /// or not. When has_value() returns true, value() returns true if the column accepts NULL values,
        /// otherwise value() returns false, indicating that the column does not accept null values.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>A std::optional&lt;bool&gt; object indicating whether the column accepts NULL values or not.</returns>
        std::optional<bool> ColumnIsNullable( SQLUSMALLINT columnNumber ) const
        {
            auto value = GetInt64ColumnAttribute( columnNumber, SQL_DESC_NULLABLE );
            if ( value == SQL_NULLABLE )
            {
                return true;
            }
            else if ( value == SQL_NO_NULLS )
            {
                return false;
            }
            else
            {
                return {};
            }
        }

        /// <summary>
        /// If the column is an approximate numeric this function returns the value 2,
        /// if the column is an exact numeric data type, this field contains a value of 10,
        /// for all other types this function returns 0.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>A value indicating whether the column is an exact numeric type, an approximate numeric type, or something else.</returns>
        Int64 ColumnNumericPrecisionRadix( SQLUSMALLINT columnNumber ) const
        {
            return GetInt64ColumnAttribute( columnNumber, SQL_DESC_NUM_PREC_RADIX );
        }


        /// <summary>
        /// Returns the length, in bytes, of a character string or binary data type. For fixed-length 
        /// character or binary types, this is the actual length in bytes. For variable-length character 
        /// or binary types, this is the maximum length in bytes. This value does not include the null terminator.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The length, in bytes, of a character string or binary data type.</returns>
        Int64 ColumnBinaryLength( SQLUSMALLINT columnNumber ) const
        {
            return GetInt64ColumnAttribute( columnNumber, SQL_DESC_OCTET_LENGTH );
        }

        /// <summary>
        /// Returns a numeric value that for a numeric data type denotes the applicable precision. For data 
        /// types SqlType::Time, SqlType::TimeStamp, and all the interval data types that represent a time 
        /// interval, its value is the applicable precision of the fractional seconds component.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The precision of the column.</returns>
        Int64 ColumnPrecision( SQLUSMALLINT columnNumber ) const
        {
            return GetInt64ColumnAttribute( columnNumber, SQL_DESC_PRECISION );
        }

        /// <summary>
        /// Returns a numeric value that is the applicable scale for a numeric data type. 
        /// For SqlType::Decimal and SqlType::Numeric data types, this is the defined scale. 
        /// It is undefined for all other data types.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The scale of the column.</returns>
        Int64 ColumnScale( SQLUSMALLINT columnNumber ) const
        {
            return GetInt64ColumnAttribute( columnNumber, SQL_DESC_SCALE );
        }

        /// <summary>
        /// Returns the schema of the table that contains the column. The returned value is 
        /// implementation-defined if the column is an expression or if the column is part 
        /// of a view. If the data source does not support schemas or the schema name cannot 
        /// be determined, an empty string is returned.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The schema of the table that contains the column.</returns>
        WideString ColumnSchemaName( SQLUSMALLINT columnNumber ) const
        {
            return GetWideStringColumnAttribute( columnNumber, SQL_DESC_SCHEMA_NAME );
        }

        /// <summary>
        /// <para>
        /// Returns a value indicating the predicates that can be applied to the column in a WHERE clause.
        /// </para>
        /// <para>
        /// Returns SearchPredicates::None if the column cannot be used in a WHERE clause.
        /// </para>
        /// <para>
        /// Returns SearchPredicates::Char if the column can be used in a WHERE clause but only with the LIKE predicate.
        /// </para>
        /// <para>
        /// Returns SearchPredicates::Basic if the column can be used in a WHERE clause with all the comparison operators except LIKE. 
        /// </para>
        /// <para>
        /// Returns SearchPredicates::Searchable if the column can be used in a WHERE clause with any comparison operator.
        /// </para>
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>A value indicating the predicates that can be applied to the column.</returns>
        SearchPredicates ColumnSearchPredicates( SQLUSMALLINT columnNumber ) const
        {
            return static_cast< SearchPredicates >( GetInt64ColumnAttribute( columnNumber, SQL_DESC_SEARCHABLE ) );
        }

        /// <summary>
        /// Returns the name of the table that contains the column. The returned value is 
        /// implementation-defined if the column is an expression or if the column 
        /// is part of a view.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The name of the table that contains the column.</returns>
        WideString ColumnTableName( SQLUSMALLINT columnNumber ) const
        {
            return GetWideStringColumnAttribute( columnNumber, SQL_DESC_TABLE_NAME );
        }

        /// <summary>
        /// Returns a numeric value that specifies the SQL data type.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>A numeric value that specifies the SQL data type.</returns>
        ODBC::SqlType ColumnType( SQLUSMALLINT columnNumber ) const
        {
            return static_cast< ODBC::SqlType >( GetInt64ColumnAttribute( columnNumber, SQL_DESC_TYPE ) );
        }

        /// <summary>
        /// Returns the data source-dependent data type name.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>The data source-dependent data type name.</returns>
        WideString ColumnTypeName( SQLUSMALLINT columnNumber ) const
        {
            return GetWideStringColumnAttribute( columnNumber, SQL_DESC_TYPE_NAME );
        }

        /// <summary>
        /// Returns true if the column is unnamed, otherwise false.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>true if the column is unnamed, otherwise false.</returns>
        bool ColumnIsUnnamed( SQLUSMALLINT columnNumber ) const
        {
            return GetBooleanColumnAttribute( columnNumber, SQL_DESC_UNNAMED );
        }

        /// <summary>
        /// Returns true if the column is unsigned, or not numeric, otherwise false.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>true if the column is unsigned, or not numeric, otherwise false.</returns>
        bool ColumnIsUnsigned( SQLUSMALLINT columnNumber ) const
        {
            return GetBooleanColumnAttribute( columnNumber, SQL_DESC_UNSIGNED );
        }

        /// <summary>
        /// Returns a std::optional&lt;bool&gt; object indicating whether the column can be updated or not.
        /// </summary>
        /// <param name="columnNumber">The one-based column number.</param>
        /// <returns>A std::optional&lt;bool&gt; object indicating whether the column can be updated or not.</returns>
        std::optional<bool> ColumnIsUpdatable( SQLUSMALLINT columnNumber ) const
        {
            auto value = GetInt64ColumnAttribute( columnNumber, SQL_DESC_UPDATABLE );
            if ( value == SQL_ATTR_READONLY )
            {
                return true;
            }
            else if ( value == SQL_ATTR_WRITE )
            {
                return false;
            }
            else
            {
                return {};
            }
        }


        /// <summary>
        /// Returns a list of columns and associated privileges for the specified table. The driver 
        /// returns the information as a result set on the Statement.
        /// </summary>
        /// <param name="catalogName">
        /// </param>
        /// <param name="catalogNameMaxLength">
        /// </param>
        /// <param name="schemaName">
        /// </param>
        /// <param name="schemaNameMaxLength">
        /// </param>
        /// <param name="tableName">
        /// </param>
        /// <param name="tableNameMaxLength">
        /// </param>
        /// <param name="columnName">
        /// </param>
        /// <param name="columnNameMaxLength">
        /// </param>
        /// <returns></returns>
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

        Result DescribeParameter( SQLUSMALLINT parameterNumber, SqlType* dataType, SQLULEN *parameterSize, SQLSMALLINT* decimalDigits, ODBC::Nullable* nullable ) const
        {
            auto rc = SQLDescribeParam( Handle( ), parameterNumber, reinterpret_cast< SQLSMALLINT *>( dataType ), parameterSize, decimalDigits, (SQLSMALLINT*)nullable );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        inline ParameterDescription DescribeParameter( SQLUSMALLINT parameterNumber ) const;


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

        template<typename ReaderType = DataReader, SimpleStringLike StringT>
            requires std::is_base_of_v<DataReader, ReaderType>
        std::unique_ptr<ReaderType> ExecuteReader( const StringT& str ) const
        {
            return ExecuteReader<ReaderType>( str.c_str( ), static_cast< SQLINTEGER >( str.size( ) ) );
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

        Result FetchScroll( ODBC::FetchOrientation fetchOrientation, SQLLEN fetchOffset ) const
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

        Result GetData( SQLUSMALLINT columnOrParameterNumber, NativeType targetValueDataType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrTargetValueActualLength ) const
        {
            auto rc = SQLGetData( Handle( ), columnOrParameterNumber, static_cast< SQLSMALLINT >(targetValueDataType), targetValue, targetValueMaxLength, nullIndicatorOrTargetValueActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        /// <summary>
        /// Gets the value of the specified column as a DBBoolean.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBBoolean GetDBBoolean( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a DBByte.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBByte GetDBByte( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a DBSByte.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBSByte GetDBSByte( SQLUSMALLINT columnNumber ) const
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

        /// <summary>
        /// Gets the value of the specified column as a DBInt16.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBInt16 GetDBInt16( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a DBUInt16.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBUInt16 GetDBUInt16( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a DBInt32.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBInt32 GetDBInt32( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a DBUInt32.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBUInt32 GetDBUInt32( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a DBInt64.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBInt64 GetDBInt64( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a DBUInt64.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBUInt64 GetDBUInt64( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;Numeric&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBNumeric GetDBNumeric( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a DBDecimal.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBDecimal GetDBDecimal( SQLUSMALLINT columnNumber ) const
        {
            return GetDBNumeric( columnNumber );
        }

        /// <summary>
        /// Gets the value of the specified column as a DBSingle.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBSingle GetDBSingle( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a DBDouble.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBDouble GetDBDouble( SQLUSMALLINT columnNumber ) const
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

        /// <summary>
        /// Gets the value of the specified column as a DBCurrency.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBCurrency GetDBCurrency( SQLUSMALLINT columnNumber ) const
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

        /// <summary>
        /// Gets the value of the specified column as a DBDateTime.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBDateTime GetDBDateTime( SQLUSMALLINT columnNumber ) const
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

        /// <summary>
        /// Gets the value of the specified column as a DBTimestampOffset.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBTimestampOffset GetDBTimestampOffset( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a DBDate.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBDate GetDBDate( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a DBTime.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBTime GetDBTime( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a DBTimeSpan.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBTimeSpan GetDBTimeSpan( SQLUSMALLINT columnNumber ) const
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
        /// <summary>
        /// Gets the value of the specified column as a DBWideString.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBWideString GetDBWideString( SQLUSMALLINT columnNumber ) const
        {
            SQLLEN indicator;
            constexpr size_t BufferSize = 8192;
            constexpr size_t MaxCharsInBuffer = ( BufferSize / sizeof( wchar_t ) ) - 1;
            constexpr size_t MaxBytesInBuffer = MaxCharsInBuffer * sizeof( wchar_t );
            wchar_t buffer[ MaxCharsInBuffer + 1 ];
            GetData( columnNumber, NativeType::WideChar, &buffer, BufferSize, &indicator );
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
                if ( indicator > MaxBytesInBuffer )
                {
                    size_t numberOfCharacters = indicator / sizeof( wchar_t );
                    WideString result;
                    result.SetLength( numberOfCharacters );
                    wmemcpy_s( result.data( ), numberOfCharacters + 1, buffer, MaxCharsInBuffer );
                    auto ptr = result.data( ) + MaxCharsInBuffer;
                    size_t remaining = static_cast< size_t >( indicator ) - MaxBytesInBuffer + 2;
                    GetData( columnNumber, NativeType::WideChar, ptr, remaining, &indicator );
                    return result;
                }
                else
                {
                    WideString result( buffer, static_cast< size_t >( indicator / 2 ) );
                    return result;
                }
            }
            else
            {
                WideString result( buffer, MaxCharsInBuffer );
                for ( ;;)
                {
                    auto rc = GetData( columnNumber, NativeType::WideChar, &buffer, BufferSize, &indicator );

                    size_t charCount = ( indicator == SQL_NO_TOTAL ) ? MaxCharsInBuffer : indicator / 2;
                    result.Append( buffer, charCount );
                    if ( rc == Result::Success )
                    {
                        break;
                    }
                }
                return result;
            }
        }

        /// <summary>
        /// Gets the value of the specified column as a DBAnsiString.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBAnsiString GetDBAnsiString( SQLUSMALLINT columnNumber ) const
        {
            SQLLEN indicator;
            constexpr size_t BufferSize = 8192;
            constexpr size_t MaxCharsInBuffer = BufferSize - 1;
            char buffer[ BufferSize ];
            GetData( columnNumber, NativeType::Char, &buffer, BufferSize, &indicator );
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
                AnsiString result( buffer, MaxCharsInBuffer );
                for ( ;;)
                {
                    auto rc = GetData( columnNumber, NativeType::Char, &buffer, BufferSize, &indicator );

                    size_t charCount = ( indicator == SQL_NO_TOTAL ) ? MaxCharsInBuffer : indicator;
                    result.Append( buffer, charCount );
                    if ( rc == Result::Success )
                    {
                        break;
                    }
                }
                return result;
            }
        }

        /// <summary>
        /// Gets the value of the specified column as a DBBinary.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBBinary GetDBBinary( SQLUSMALLINT columnNumber ) const
        {
            SQLLEN indicator;
            constexpr size_t BufferSize = 8192;
            Byte buffer[ BufferSize ];
            GetData( columnNumber, NativeType::Binary, &buffer, BufferSize, &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                return {};
            }
            if ( indicator == 0 )
            {
                return Binary( );
            }
            if ( indicator != SQL_NO_TOTAL )
            {
                if ( indicator > BufferSize )
                {
                    Binary result;
                    result.resize( indicator );
                    memcpy_s( result.data( ), indicator, buffer, BufferSize );
                    auto ptr = result.data( ) + BufferSize;
                    size_t remaining = static_cast< size_t >( indicator ) - BufferSize;
                    GetData( columnNumber, NativeType::Binary, ptr, remaining, &indicator );
                    return result;
                }
                else
                {
                    Binary result( buffer, buffer + static_cast< size_t >( indicator ) );
                    return result;
                }
            }
            else
            {
                Binary result( buffer, buffer + sizeof( buffer ) );
                for ( ;;)
                {
                    auto rc = GetData( columnNumber, NativeType::Binary, &buffer, sizeof( buffer ), &indicator );

                    size_t byteCount = ( indicator == SQL_NO_TOTAL ) ? sizeof( buffer ) : indicator;
                    result.Append( buffer, byteCount );
                    if ( rc == Result::Success )
                    {
                        break;
                    }
                }
                return result;
            }
        }

        /// <summary>
        /// Gets the value of the specified column as a DBGuid.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBGuid GetDBGuid( SQLUSMALLINT columnNumber ) const
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

        /// <summary>
        /// Gets the value of the specified column as a std::optional&lt;RowVersion&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        [[nodiscard]]
        DBRowVersion GetDBRowVersion( SQLUSMALLINT columnNumber ) const
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

        /// <summary>
        /// Gets the value of the specified column as a bool.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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
        /// <summary>
        /// Gets the value of the specified column as a Byte.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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
        /// <summary>
        /// Gets the value of the specified column as a SByte.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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
        /// <summary>
        /// Gets the value of the specified column as an Int16.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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
        /// <summary>
        /// Gets the value of the specified column as an UInt16.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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
        /// <summary>
        /// Gets the value of the specified column as an Int32.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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
        /// <summary>
        /// Gets the value of the specified column as an UInt32.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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
        /// <summary>
        /// Gets the value of the specified column as an Int64.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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
        /// <summary>
        /// Gets the value of the specified column as an UInt64.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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
        /// <summary>
        /// Gets the value of the specified column as a Numeric.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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
        /// <summary>
        /// Gets the value of the specified column as a Numeric.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        Numeric GetDecimal( SQLUSMALLINT columnNumber ) const
        {
            return GetNumeric( columnNumber );
        }

        /// <summary>
        /// Gets the value of the specified column as a float.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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

        /// <summary>
        /// Gets the value of the specified column as a double.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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

        /// <summary>
        /// Gets the value of the specified column as a Currency.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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

        /// <summary>
        /// Gets the value of the specified column as a DateTime.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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

        /// <summary>
        /// Gets the value of the specified column as a TimestampOffset.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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


        /// <summary>
        /// Gets the value of the specified column as a Date.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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

        /// <summary>
        /// Gets the value of the specified column as a Time.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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
        /// <summary>
        /// Gets the value of the specified column as a TimeSpan.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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

        /// <summary>
        /// Gets the value of the specified column as a WideString.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        WideString GetWideString( SQLUSMALLINT columnNumber ) const
        {
            SQLLEN indicator;
            constexpr size_t BufferSize = 8192;
            constexpr size_t MaxCharsInBuffer = (BufferSize / sizeof( wchar_t )) - 1;
            constexpr size_t MaxBytesInBuffer = MaxCharsInBuffer * sizeof( wchar_t );
            wchar_t buffer[ MaxCharsInBuffer + 1 ];
            GetData( columnNumber, NativeType::WideChar, &buffer, BufferSize, &indicator );
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
                if ( indicator > MaxBytesInBuffer )
                {
                    size_t numberOfCharacters = indicator / sizeof( wchar_t );
                    WideString result;
                    result.SetLength( numberOfCharacters );
                    wmemcpy_s( result.data( ), numberOfCharacters + 1, buffer, MaxCharsInBuffer );
                    auto ptr = result.data( ) + MaxCharsInBuffer;
                    size_t remaining = static_cast< size_t >( indicator ) - MaxBytesInBuffer + 2;
                    GetData( columnNumber, NativeType::WideChar, ptr, remaining, &indicator );
                    return result;
                }
                else
                {
                    WideString result( buffer, static_cast< size_t >( indicator / 2 ) );
                    return result;
                }
            }
            else
            {
                WideString result( buffer, MaxCharsInBuffer );
                for ( ;;)
                {
                    auto rc = GetData( columnNumber, NativeType::WideChar, &buffer, BufferSize, &indicator );

                    size_t charCount = ( indicator == SQL_NO_TOTAL ) ? MaxCharsInBuffer : indicator / 2;
                    result.Append( buffer, charCount );
                    if ( rc == Result::Success )
                    {
                        break;
                    }
                }
                return result;
            }
        }

        /// <summary>
        /// Gets the value of the specified column as an AnsiString.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        AnsiString GetAnsiString( SQLUSMALLINT columnNumber ) const
        {
            SQLLEN indicator;
            constexpr size_t BufferSize = 8192;
            constexpr size_t MaxCharsInBuffer = BufferSize - 1;
            char buffer[ BufferSize ];
            GetData( columnNumber, NativeType::Char, &buffer, BufferSize, &indicator );
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
                if ( indicator > MaxCharsInBuffer )
                {
                    AnsiString result;
                    result.SetLength( indicator );
                    memcpy_s( result.data( ), indicator + 1, buffer, MaxCharsInBuffer );
                    auto ptr = result.data( ) + MaxCharsInBuffer;
                    size_t remaining = static_cast< size_t >( indicator ) - MaxCharsInBuffer + 1;
                    GetData( columnNumber, NativeType::Char, ptr, remaining, &indicator );
                    return result;
                }
                else
                {
                    AnsiString result( buffer, static_cast< size_t >( indicator ) );
                    return result;
                }
            }
            else
            {
                AnsiString result( buffer, MaxCharsInBuffer );
                for ( ;;)
                {
                    auto rc = GetData( columnNumber, NativeType::Char, &buffer, BufferSize, &indicator );

                    size_t charCount = ( indicator == SQL_NO_TOTAL ) ? MaxCharsInBuffer : indicator;
                    result.Append( buffer, charCount );
                    if ( rc == Result::Success )
                    {
                        break;
                    }
                }
                return result;
            }
        }
        /// <summary>
        /// Gets the value of the specified column as a std::vector&lt;Byte&gt;.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
        [[nodiscard]]
        Binary GetBinary( SQLUSMALLINT columnNumber ) const
        {
            SQLLEN indicator;
            constexpr size_t BufferSize = 8192;
            Byte buffer[ BufferSize ];
            GetData( columnNumber, NativeType::Binary, &buffer, BufferSize, &indicator );
            if ( indicator == SQL_NULL_DATA )
            {
                Internal::ThrowColumnNullException( columnNumber, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            if ( indicator == 0 )
            {
                return Binary( );
            }
            if ( indicator != SQL_NO_TOTAL )
            {
                if ( indicator > BufferSize )
                {
                    Binary result;
                    result.resize( indicator );
                    memcpy_s( result.data( ), indicator, buffer, BufferSize );
                    auto ptr = result.data( ) + BufferSize;
                    size_t remaining = static_cast< size_t >( indicator ) - BufferSize;
                    GetData( columnNumber, NativeType::Binary, ptr, remaining, &indicator );
                    return result;
                }
                else
                {
                    Binary result( buffer, buffer + static_cast< size_t >( indicator ) );
                    return result;
                }
            }
            else
            {
                Binary result( buffer, buffer + sizeof( buffer ) );
                for ( ;;)
                {
                    auto rc = GetData( columnNumber, NativeType::Binary, &buffer, sizeof( buffer ), &indicator );

                    size_t byteCount = ( indicator == SQL_NO_TOTAL ) ? sizeof( buffer ) : indicator;
                    result.Append( buffer, byteCount );
                    if ( rc == Result::Success )
                    {
                        break;
                    }
                }
                return result;
            }
        }

        /// <summary>
        /// Gets the value of the specified column as a Guid.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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
        /// <summary>
        /// Gets the value of the specified column as a RowVersion.
        /// </summary>
        /// <param name="columnNumber">The one-based column ordinal.</param>
        /// <returns>The value of the column.</returns>
        /// <remarks>
        /// The implementation throws an exception if the column value is NULL.
        /// </remarks>
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


        /// <summary>
        /// Retrieves the current setting of a statement attribute.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to retrieve.</param>
        /// <param name="value">
        /// <para>
        /// Pointer to a buffer in which to return the value of the attribute specified in Attribute.
        /// </para>
        /// <para>
        /// If value is nullptr, valueActualLength will still return the total number of bytes (excluding 
        /// the null-termination character for character data) available to return in the buffer pointed to 
        /// by value.
        /// </para>
        /// </param>
        /// <param name="valueBufferLength">
        /// <para>
        /// If attributeId is an ODBC-defined attribute and value *points to a character string or a 
        /// binary buffer, this argument should be the length of *value. If attributeId is an 
        /// ODBC-defined attribute and *value is an integer, valueBufferLength is ignored. If the 
        /// value returned in *value is a Unicode string, the valueBufferLength argument must be an even number.
        /// </para>
        /// <para>
        /// If attributeId is a driver-defined attribute, the application indicates the nature of the 
        /// attribute to the Driver Manager by setting the BufferLength argument. valueBufferLength can 
        /// have the following values:
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// If *value is a pointer to a character string, then valueBufferLength is the length of the string or SQL_NTS.
        /// </item>
        /// <item>
        /// If *value is a pointer to a binary buffer, then the application places the result of the 
        /// SQL_LEN_BINARY_ATTR(length) macro in valueBufferLength. This places a negative value in 
        /// valueBufferLength.
        /// </item>
        /// <item>
        /// If *value is a pointer to a value other than a character string or binary string, then 
        /// valueBufferLength should have the value SQL_IS_POINTER.
        /// </item>
        /// <item>
        /// If *value contains a fixed-length data type, then valueBufferLength is either SQL_IS_INTEGER or 
        /// SQL_IS_UINTEGER, as appropriate.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="valueActualLength"></param>
        /// <returns></returns>
        Result GetAttributeW( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueBufferLength, SQLINTEGER* valueActualLength ) const
        {
            auto rc = SQLGetStmtAttrW( Handle( ), attributeId, value, valueBufferLength, valueActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        /// <summary>
        /// Retrieves the current setting of a UInt64 valued statement attribute.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to retrieve.</param>
        /// <returns>The value of the attribute.</returns>
        UInt64 GetUInt64Attribute( SQLINTEGER attributeId ) const
        {
            UInt64 value;
            auto rc = SQLGetStmtAttrW( Handle( ), attributeId, &value, SQL_IS_UINTEGER, nullptr );
            if ( Failed( static_cast< Result >( rc ) ) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }
        /// <summary>
        /// Retrieves the current setting of a Int64 valued statement attribute.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to retrieve.</param>
        /// <returns>The value of the attribute.</returns>
        Int64 GetInt64Attribute( SQLINTEGER attributeId ) const
        {
            Int64 value;
            auto rc = SQLGetStmtAttrW( Handle( ), attributeId, &value, SQL_IS_INTEGER, nullptr );
            if ( Failed( static_cast< Result >( rc ) ) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        /// <summary>
        /// Retrieves the current setting of a pointer valued statement attribute.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to retrieve.</param>
        /// <returns>The value of the attribute.</returns>
        SQLPOINTER GetPointerAttribute( SQLINTEGER attributeId ) const
        {
            SQLPOINTER value;
            auto rc = SQLGetStmtAttrW( Handle( ), attributeId, &value, SQL_IS_POINTER, nullptr );
            if ( Failed( static_cast< Result >( rc ) ) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }

        /// <summary>
        /// Retrieves the current setting of a boolean valued statement attribute.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to retrieve.</param>
        /// <returns>The value of the attribute.</returns>
        bool GetBooleanAttribute( SQLINTEGER attributeId ) const
        {
            return GetUInt64Attribute( attributeId ) != 0;
        }

        /// <summary>
        /// Retrieves the current setting of a descriptor valued statement attribute.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to retrieve.</param>
        /// <returns>The value of the attribute.</returns>
        Descriptor GetDescriptorAttribute( SQLINTEGER attributeId ) const
        {
            SQLHANDLE descriptor = nullptr;
            GetAttributeW( attributeId, &descriptor, SQL_IS_POINTER, nullptr );
            return Descriptor( descriptor, false );
        }

        /// <summary>
        /// Retrieves the current setting of a UInt64 valued statement attribute as an enum value.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to retrieve.</param>
        /// <returns>The value of the attribute.</returns>
        template<typename T>
            requires std::is_enum_v<T>
        T GetEnumAttribute( SQLINTEGER attributeId ) const
        {
            UInt64 value;
            auto rc = SQLGetStmtAttrW( Handle( ), attributeId, &value, SQL_IS_UINTEGER, nullptr );
            if ( Failed( static_cast< Result >( rc ) ) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<T>(value);
        }


        /// <summary>
        /// Retrieves the current setting of a statement attribute.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to retrieve.</param>
        /// <param name="value">
        /// <para>
        /// Pointer to a buffer in which to return the value of the attribute specified in Attribute.
        /// </para>
        /// <para>
        /// If value is nullptr, valueActualLength will still return the total number of bytes (excluding 
        /// the null-termination character for character data) available to return in the buffer pointed to 
        /// by value.
        /// </para>
        /// </param>
        /// <param name="valueBufferLength">
        /// <para>
        /// If attributeId is an ODBC-defined attribute and value *points to a character string or a 
        /// binary buffer, this argument should be the length of *value. If attributeId is an 
        /// ODBC-defined attribute and *value is an integer, valueBufferLength is ignored. If the 
        /// value returned in *value is a Unicode string, the valueBufferLength argument must be an even number.
        /// </para>
        /// <para>
        /// If attributeId is a driver-defined attribute, the application indicates the nature of the 
        /// attribute to the Driver Manager by setting the BufferLength argument. valueBufferLength can 
        /// have the following values:
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// If *value is a pointer to a character string, then valueBufferLength is the length of the string or SQL_NTS.
        /// </item>
        /// <item>
        /// If *value is a pointer to a binary buffer, then the application places the result of the 
        /// SQL_LEN_BINARY_ATTR(length) macro in valueBufferLength. This places a negative value in 
        /// valueBufferLength.
        /// </item>
        /// <item>
        /// If *value is a pointer to a value other than a character string or binary string, then 
        /// valueBufferLength should have the value SQL_IS_POINTER.
        /// </item>
        /// <item>
        /// If *value contains a fixed-length data type, then valueBufferLength is either SQL_IS_INTEGER or 
        /// SQL_IS_UINTEGER, as appropriate.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="valueActualLength"></param>
        /// <returns></returns>
        Result GetAttributeA( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueBufferLength, SQLINTEGER* valueActualLength ) const
        {
            auto rc = SQLGetStmtAttrA( Handle( ), attributeId, value, valueBufferLength, valueActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        /// <summary>
        /// Sets attributes related to a statement.
        /// </summary>
        /// <param name="attributeId">
        /// Identifier of the attribute to set.
        /// </param>
        /// <param name="value">
        /// <para>
        /// Value to be associated with the attribute. Depending on the value of attributeId, value will be one of the following:
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// An ODBC descriptor handle.
        /// </item>
        /// <item>
        /// A SQLUINTEGER value.
        /// </item>
        /// <item>
        /// A SQLULEN value.
        /// </item>
        /// <item>
        /// A pointer to one of the following:
        /// <list type="bullet"> 
        /// <item>
        /// A null-terminated character string.
        /// </item>
        /// <item>
        /// A binary buffer.
        /// </item>
        /// <item>
        /// A value or array of type SQLLEN, SQLULEN, or SQLUSMALLINT.
        /// </item>
        /// <item>
        /// A driver-defined value.
        /// </item>
        /// </list>
        /// If the attribute is a driver-specific value, value may be a signed integer.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="valueLength">
        /// <para>
        /// If attributeId is an ODBC-defined attribute and value points to a character string or 
        /// a binary buffer, this argument should be the length of value. If attributeId is an 
        /// ODBC-defined attribute and valuePtr is an integer, valueLength is ignored.
        /// </para>
        /// <para>
        /// If attributeId is a driver-defined attribute, the application indicates the nature of 
        /// the attribute to the Driver Manager by setting the valueLength argument. valueLength 
        /// can have the following values:
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// If value is a pointer to a character string, then valueLength is the length of the 
        /// string or SQL_NTS.
        /// </item>
        /// <item>
        /// If value is a pointer to a binary buffer, then the application places the result of 
        /// the SQL_LEN_BINARY_ATTR(length) macro in valueLength. This places a negative 
        /// value in valueLength.
        /// </item>
        /// <item>
        /// If value is a pointer to a value other than a character string or a binary string, 
        /// then valueLength should have the value SQL_IS_POINTER.
        /// </item>
        /// <item>
        /// If value contains a fixed-length value, then valueLength is either SQL_IS_INTEGER or 
        /// SQL_IS_UINTEGER, as appropriate.
        /// </item>
        /// </list>
        /// </param>
        /// <returns>
        /// Result::Success or Result::SuccessWithInfo
        /// </returns>
        Result SetAttributeW( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueLength ) const
        {
            auto rc = SQLSetStmtAttrW( Handle( ), attributeId, value, valueLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        /// <summary>
        /// Sets an UInt64 valued attribute.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to set.</param>
        /// <param name="value">The value to assign to the attribute.</param>
        /// <returns>
        /// Result::Success or Result::SuccessWithInfo
        /// </returns>
        Result SetUInt64Attribute( SQLINTEGER attributeId, UInt64 value ) const
        {
            return SetAttributeW( attributeId, reinterpret_cast< SQLPOINTER >( value ), SQL_IS_UINTEGER );
        }

        /// <summary>
        /// Sets an Int64 valued attribute.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to set.</param>
        /// <param name="value">The value to assign to the attribute.</param>
        /// <returns>
        /// Result::Success or Result::SuccessWithInfo
        /// </returns>
        Result SetInt64Attribute( SQLINTEGER attributeId, Int64 value ) const
        {
            return SetAttributeW( attributeId, reinterpret_cast< SQLPOINTER >( value ), SQL_IS_INTEGER );
        }


        /// <summary>
        /// Sets an boolean valued attribute.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to set.</param>
        /// <param name="value">The value to assign to the attribute.</param>
        /// <returns>
        /// Result::Success or Result::SuccessWithInfo
        /// </returns>
        Result SetBooleanAttribute( SQLINTEGER attributeId, bool value ) const
        {
            return SetAttributeW( attributeId, reinterpret_cast< SQLPOINTER >( value? 1ULL : 0ULL ), SQL_IS_UINTEGER );
        }


        /// <summary>
        /// Sets an pointer valued attribute.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to set.</param>
        /// <param name="value">The value to assign to the attribute.</param>
        /// <returns>
        /// Result::Success or Result::SuccessWithInfo
        /// </returns>
        Result SetPointerAttribute( SQLINTEGER attributeId, SQLPOINTER value ) const
        {
            return SetAttributeW( attributeId, value , SQL_IS_POINTER );
        }


        /// <summary>
        /// Sets a descriptor valued attribute.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to set.</param>
        /// <param name="value">The value to assign to the attribute.</param>
        /// <returns>
        /// Result::Success or Result::SuccessWithInfo
        /// </returns>
        Result SetDescriptorAttribute( SQLINTEGER attributeId, SQLHANDLE value ) const
        {
            return SetAttributeW( attributeId, value, SQL_IS_POINTER );
        }
        /// <summary>
        /// Sets a descriptor valued attribute.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to set.</param>
        /// <param name="value">The value to assign to the attribute.</param>
        /// <returns>
        /// Result::Success or Result::SuccessWithInfo
        /// </returns>
        Result SetDescriptorAttribute( SQLINTEGER attributeId, const Descriptor& value ) const
        {
            return SetAttributeW( attributeId, value.Handle(), SQL_IS_POINTER );
        }

        /// <summary>
        /// Sets an UInt64 valued attribute valued attribute to the value from an enumeration.
        /// </summary>
        /// <param name="attributeId">Identifier of the attribute to set.</param>
        /// <param name="value">The value to assign to the attribute.</param>
        /// <returns>
        /// Result::Success or Result::SuccessWithInfo
        /// </returns>
        template<typename T> 
            requires std::is_enum_v<T>
        Result SetEnumAttribute( SQLINTEGER attributeId, T value ) const
        {
            return SetAttributeW( attributeId, reinterpret_cast< SQLPOINTER >( value ), SQL_IS_UINTEGER );
        }


        /// <summary>
        /// Sets attributes related to a statement.
        /// </summary>
        /// <param name="attributeId">
        /// Identifier of the attribute to set.
        /// </param>
        /// <param name="value">
        /// <para>
        /// Value to be associated with the attribute. Depending on the value of attributeId, value will be one of the following:
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// An ODBC descriptor handle.
        /// </item>
        /// <item>
        /// A SQLUINTEGER value.
        /// </item>
        /// <item>
        /// A SQLULEN value.
        /// </item>
        /// <item>
        /// A pointer to one of the following:
        /// <list type="bullet"> 
        /// <item>
        /// A null-terminated character string.
        /// </item>
        /// <item>
        /// A binary buffer.
        /// </item>
        /// <item>
        /// A value or array of type SQLLEN, SQLULEN, or SQLUSMALLINT.
        /// </item>
        /// <item>
        /// A driver-defined value.
        /// </item>
        /// </list>
        /// If the attribute is a driver-specific value, value may be a signed integer.
        /// </item>
        /// </list>
        /// </param>
        /// <param name="valueLength">
        /// <para>
        /// If attributeId is an ODBC-defined attribute and value points to a character string or 
        /// a binary buffer, this argument should be the length of value. If attributeId is an 
        /// ODBC-defined attribute and valuePtr is an integer, valueLength is ignored.
        /// </para>
        /// <para>
        /// If attributeId is a driver-defined attribute, the application indicates the nature of 
        /// the attribute to the Driver Manager by setting the valueLength argument. valueLength 
        /// can have the following values:
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// If value is a pointer to a character string, then valueLength is the length of the 
        /// string or SQL_NTS.
        /// </item>
        /// <item>
        /// If value is a pointer to a binary buffer, then the application places the result of 
        /// the SQL_LEN_BINARY_ATTR(length) macro in valueLength. This places a negative 
        /// value in valueLength.
        /// </item>
        /// <item>
        /// If value is a pointer to a value other than a character string or a binary string, 
        /// then valueLength should have the value SQL_IS_POINTER.
        /// </item>
        /// <item>
        /// If value contains a fixed-length value, then valueLength is either SQL_IS_INTEGER or 
        /// SQL_IS_UINTEGER, as appropriate.
        /// </item>
        /// </list>
        /// </param>
        /// <returns>
        /// Result::Success or Result::SuccessWithInfo
        /// </returns>
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

        /// <summary>
        /// <para>
        /// Sets the handle to the APD for subsequent calls to SQLExecute and SQLExecDirect on 
        /// the statement handle. The initial value of this attribute is the descriptor implicitly 
        /// allocated when the statement was initially allocated. If the value of this attribute 
        /// is set to SQL_NULL_DESC or the handle originally allocated for the descriptor, an 
        /// explicitly allocated APD handle that was previously associated with the statement 
        /// handle is dissociated from it and the statement handle reverts to the implicitly 
        /// allocated APD handle.
        /// </para>
        /// <para>
        /// This attribute cannot be set to a descriptor handle that was implicitly allocated for 
        /// another statement or to another descriptor handle that was implicitly set on the same 
        /// statement; implicitly allocated descriptor handles cannot be associated with more than 
        /// one statement or descriptor handle.
        /// </para>
        /// </summary>
        /// <param name="applicationParameterDescriptor">The application parameter descriptor</param>
        /// <returns>Result::Success or Result::SuccessWithInfo</returns>
        Result SetApplicationParameterDescriptor( const Descriptor& applicationParameterDescriptor ) const
        {
            auto rc = SetDescriptorAttribute( SQL_ATTR_APP_PARAM_DESC, applicationParameterDescriptor.Handle() );
            return rc;
        }
        Result SetApplicationParameterDescriptor( SQLHANDLE applicationParameterDescriptor ) const
        {
            auto rc = SetDescriptorAttribute( SQL_ATTR_APP_PARAM_DESC, applicationParameterDescriptor );
            return rc;
        }
        /// <summary>
        /// Retrieves the application parameter descriptor.
        /// </summary>
        /// <returns>The application parameter descriptor</returns>
        Descriptor ApplicationParameterDescriptor( ) const
        {
            return GetDescriptorAttribute( SQL_ATTR_APP_PARAM_DESC );
        }

        /// <summary>
        /// <para>
        /// Sets the handle to the ARD for subsequent fetches on the statement handle. The 
        /// initial value of this attribute is the descriptor implicitly allocated when the 
        /// statement was initially allocated. If the value of this attribute is set to 
        /// SQL_NULL_DESC or the handle originally allocated for the descriptor, an explicitly 
        /// allocated ARD handle that was previously associated with the statement handle is 
        /// dissociated from it and the statement handle reverts to the implicitly allocated 
        /// ARD handle.
        /// </para>
        /// <para>
        /// This attribute cannot be set to a descriptor handle that was implicitly allocated 
        /// for another statement or to another descriptor handle that was implicitly set on 
        /// the same statement; implicitly allocated descriptor handles cannot be associated 
        /// with more than one statement or descriptor handle.
        /// </para>
        /// </summary>
        /// <param name="applicationRowDescriptor">The application row descriptor</param>
        /// <returns>Result::Success or Result::SuccessWithInfo</returns>
        Result SetApplicationRowDescriptor( const Descriptor& applicationRowDescriptor ) const
        {
            auto rc = SetDescriptorAttribute( SQL_ATTR_APP_ROW_DESC, applicationRowDescriptor.Handle( ) );
            return rc;
        }
        Result SetApplicationRowDescriptor( SQLHANDLE applicationRowDescriptor ) const
        {
            auto rc = SetDescriptorAttribute( SQL_ATTR_APP_ROW_DESC, applicationRowDescriptor );
            return rc;
        }
        /// <summary>
        /// Retrieves the application row descriptor.
        /// </summary>
        /// <returns>The application row descriptor.</returns>
        Descriptor ApplicationRowDescriptor( ) const
        {
            return GetDescriptorAttribute( SQL_ATTR_APP_ROW_DESC );
        }

        /// <summary>
        /// Enables or disables asynchronous statement execution.
        /// </summary>
        /// <param name="asyncEnable">true to enable asynchronous statement execution, otherwise false.</param>
        /// <returns>Result::Success or Result::SuccessWithInfo</returns>
        Result SetAsyncEnabled( bool asyncEnable ) const
        {
            auto rc = SetBooleanAttribute( SQL_ATTR_ASYNC_ENABLE, asyncEnable );
            return rc;
        }

        /// <summary>
        /// Returns true if asynchronous statement execution is enabled, otherwise false.
        /// </summary>
        /// <returns></returns>
        bool AsyncEnabled( ) const
        {
            return GetBooleanAttribute( SQL_ATTR_ASYNC_ENABLE );
        }

        /// <summary>
        /// Assigns the Windows event handle that will get notified on asynchronous completion.
        /// </summary>
        /// <param name="asyncEventHandle">A windows event handle.</param>
        /// <returns>Result::Success or Result::SuccessWithInfo</returns>
        Result SetAsyncEventHandle( HANDLE asyncEventHandle ) const
        {
            auto rc = SetPointerAttribute( SQL_ATTR_ASYNC_STMT_EVENT, asyncEventHandle );
            return rc;
        }

        /// <summary>
        /// Assigns the Windows event handle that will get notified on asynchronous completion.
        /// </summary>
        /// <param name="asyncEventHandle">A windows event handle.</param>
        /// <returns>Result::Success or Result::SuccessWithInfo</returns>
        Result SetAsyncEventHandle( const EventWaitHandle& asyncEventHandle ) const
        {
            auto rc = SetPointerAttribute( SQL_ATTR_ASYNC_STMT_EVENT, asyncEventHandle.GetHandle() );
            return rc;
        }

        /// <summary>
        /// Retrieves the Windows event handle assigned to the SQL_ATTR_ASYNC_STMT_EVENT attribute,
        /// or nullptr if no event handle has previously been assigned to this attribute.
        /// </summary>
        /// <returns>The event handle, or nullptr if none has been set on the statement.</returns>
        HANDLE AsyncEventHandle( ) const
        {
            return GetPointerAttribute( SQL_ATTR_ASYNC_STMT_EVENT );
        }

        /// <summary>
        /// Assigns the cursor concurrency model to be used with the statement. 
        /// </summary>
        /// <param name="concurrency"></param>
        /// <returns>Result::Success or Result::SuccessWithInfo</returns>
        Result SetConcurrency( ODBC::Concurrency concurrency ) const
        {
            auto rc = SetEnumAttribute( SQL_ATTR_CONCURRENCY, concurrency );
            return rc;
        }
        /// <summary>
        /// Retrieves the cursor concurrency model that will be used with this statement.
        /// </summary>
        /// <returns>A value from the ODBC::Concurrency enumeration</returns>
        ODBC::Concurrency Concurrency( ) const
        {
            return GetEnumAttribute<ODBC::Concurrency>( SQL_ATTR_CONCURRENCY );
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="cursorScrollable">
        /// <para>
        /// Set to true if scrollable cursors are required on the statement handle. When 
        /// calling FetchScroll, the application may specify any valid value of FetchOrientation, 
        /// achieving cursor positioning in modes other than the sequential mode.
        /// </para>
        /// <para>
        /// Set to false if scrollable cursors are not required on the statement handle. If the 
        /// application calls FetchScroll on this handle, the only valid value of FetchOrientation is FetchOrientation::Next. 
        /// This is the default.
        /// </para>
        /// </param>
        /// <returns></returns>
        Result SetCursorScrollable( bool cursorScrollable ) const
        {
            return SetBooleanAttribute( SQL_ATTR_CURSOR_SCROLLABLE, cursorScrollable );
        }
        bool CursorScrollable( ) const
        {
            return GetBooleanAttribute( SQL_ATTR_CURSOR_SCROLLABLE );
        }

        Result SetCursorSensitivity( ODBC::CursorSensitivity cursorSensitivity ) const
        {
            return SetEnumAttribute( SQL_ATTR_CURSOR_SENSITIVITY, cursorSensitivity );
        }

        ODBC::CursorSensitivity CursorSensitivity( ) const
        {
            return GetEnumAttribute<ODBC::CursorSensitivity>( SQL_ATTR_CURSOR_SENSITIVITY );
        }

        Result SetCursorType( ODBC::CursorType cursorType ) const
        {
            return SetEnumAttribute( SQL_ATTR_CURSOR_TYPE, cursorType );
        }

        ODBC::CursorType CursorType( ) const
        {
            return GetEnumAttribute<ODBC::CursorType>( SQL_ATTR_CURSOR_TYPE );
        }


        Result SetAutoPopulateImplementationParameterDescriptor( bool autoPopulateImplementationParameterDescriptor ) const
        {
            return SetBooleanAttribute( SQL_ATTR_ENABLE_AUTO_IPD, autoPopulateImplementationParameterDescriptor );
        }
        bool AutoPopulateImplementationParameterDescriptor( ) const
        {
            return GetBooleanAttribute( SQL_ATTR_ENABLE_AUTO_IPD );
        }

        SQLULEN* FetchBookmarkPointer( ) const
        {
            SQLULEN* bookmarkPtr = reinterpret_cast< SQLULEN* >( GetPointerAttribute( SQL_ATTR_FETCH_BOOKMARK_PTR ) );
            return bookmarkPtr;
        }

        ODBC::Descriptor ImplementationParameterDescriptor( ) const
        {
            return GetDescriptorAttribute( SQL_ATTR_IMP_PARAM_DESC );
        }

        ODBC::Descriptor ImplementationRowDescriptor( ) const
        {
            return GetDescriptorAttribute( SQL_ATTR_IMP_ROW_DESC );
        }


        Result SetKeysetSize( SQLULEN keysetSize ) const
        {
            return SetUInt64Attribute( SQL_ATTR_KEYSET_SIZE, keysetSize );
        }
        SQLULEN KeysetSize( ) const
        {
            return GetUInt64Attribute( SQL_ATTR_KEYSET_SIZE );
        }

        Result SetMaxColumnLength( SQLULEN maxColumnLength ) const
        {
            return SetUInt64Attribute( SQL_ATTR_MAX_LENGTH, maxColumnLength );
        }
        SQLULEN MaxColumnLength( ) const
        {
            return GetUInt64Attribute( SQL_ATTR_MAX_LENGTH );
        }

        Result SetMaxRows( SQLULEN maxRows ) const
        {
            return SetUInt64Attribute( SQL_ATTR_MAX_ROWS, maxRows );
        }
        SQLULEN MaxRows( ) const
        {
            return GetUInt64Attribute( SQL_ATTR_MAX_ROWS );
        }

        Result SetMetadataIdentifiers( bool metadataIdentifiers ) const
        {
            return SetBooleanAttribute( SQL_ATTR_METADATA_ID, metadataIdentifiers );
        }
        bool MetadataIdentifiers( ) const
        {
            return GetBooleanAttribute( SQL_ATTR_METADATA_ID );
        }


        Result SetNoScan( bool noScan ) const
        {
            return SetBooleanAttribute( SQL_ATTR_NOSCAN, noScan );
        }
        bool NoScan( ) const
        {
            return GetBooleanAttribute( SQL_ATTR_NOSCAN );
        }


        Result SetParameterBindOffsetPointer( SQLULEN* paramBindOffsetPointer ) const
        {
            return SetPointerAttribute( SQL_ATTR_PARAM_BIND_OFFSET_PTR, paramBindOffsetPointer );
        }
        SQLULEN* ParameterBindOffsetPointer( ) const
        {
            return static_cast< SQLULEN* >( GetPointerAttribute( SQL_ATTR_PARAM_BIND_OFFSET_PTR ) );
        }


        Result SetParameterBindByColumn( ) const
        {
            return SetUInt64Attribute( SQL_ATTR_PARAM_BIND_TYPE, SQL_PARAM_BIND_BY_COLUMN );
        }
        bool ParameterBindByColumn( ) const
        {
            return ParameterRowSize( ) == 0;
        }

        Result SetParameterRowSize( SQLULEN rowSize ) const
        {
            return SetUInt64Attribute( SQL_ATTR_PARAM_BIND_TYPE, rowSize );
        }
        bool ParameterRowSize( ) const
        {
            return GetUInt64Attribute( SQL_ATTR_PARAM_BIND_TYPE );
        }

        Result SetParameterOperationPointer( SQLULEN* paramOperationPointer ) const
        {
            return SetPointerAttribute( SQL_ATTR_PARAM_OPERATION_PTR, paramOperationPointer );
        }
        SQLULEN* ParameterOperationPointer( ) const
        {
            return static_cast< SQLULEN* >( GetPointerAttribute( SQL_ATTR_PARAM_OPERATION_PTR ) );
        }



        Result SetParameterArraySize( UInt64 parameterArraySize ) const
        {
            return SetUInt64Attribute( SQL_ATTR_PARAMSET_SIZE, parameterArraySize );
        }

        UInt64 ParameterArraySize( ) const
        {
            return GetUInt64Attribute( SQL_ATTR_PARAMSET_SIZE );
        }


        Result SetParameterStatusArray( SQLUSMALLINT* parameterStatusArray ) const
        {
            return SetPointerAttribute( SQL_ATTR_PARAM_STATUS_PTR, parameterStatusArray );
        }

        SQLUSMALLINT* ParameterStatusArray( ) const
        {
            return static_cast< SQLUSMALLINT* >( GetPointerAttribute( SQL_ATTR_PARAM_STATUS_PTR ) );
        }

        Result SetParametersProcessedPointer( SQLULEN* parametersProcessed ) const
        {
            return SetPointerAttribute( SQL_ATTR_PARAMS_PROCESSED_PTR, parametersProcessed );
        }
        SQLULEN* ParametersProcessedPointer( ) const
        {
            return static_cast< SQLULEN* >( GetPointerAttribute( SQL_ATTR_PARAMS_PROCESSED_PTR ) );
        }

        Result SetParameterSetSize( SQLULEN parameterSetSize ) const
        {
            return SetUInt64Attribute( SQL_ATTR_PARAMSET_SIZE, parameterSetSize );
        }
        SQLULEN ParameterSetSize( ) const
        {
            return GetUInt64Attribute( SQL_ATTR_PARAMSET_SIZE );
        }

        Result SetQueryTimeout( const TimeSpan& timeout ) const
        {
            return SetUInt64Attribute( SQL_ATTR_QUERY_TIMEOUT, static_cast< UInt64 >( timeout.Ticks( ) / TimeSpan::TicksPerSecond ) );
        }
        Result SetQueryTimeout( const UInt64 timeout ) const
        {
            return SetUInt64Attribute( SQL_ATTR_QUERY_TIMEOUT, timeout );
        }

        TimeSpan QueryTimeout( ) const
        {
            return TimeSpan( GetUInt64Attribute( SQL_ATTR_QUERY_TIMEOUT ) * TimeSpan::TicksPerSecond );
        }

        Result SetRetrieveData( bool retrieveData ) const
        {
            return SetBooleanAttribute( SQL_ATTR_QUERY_TIMEOUT, retrieveData );
        }

        bool RetrieveData( ) const
        {
            return GetBooleanAttribute( SQL_ATTR_RETRIEVE_DATA );
        }

        Result SetRowArraySize( UInt64 rowArraySize ) const
        {
            return SetUInt64Attribute( SQL_ATTR_ROW_ARRAY_SIZE, rowArraySize );
        }
        UInt64 RowArraySize( ) const
        {
            return GetUInt64Attribute( SQL_ATTR_ROW_ARRAY_SIZE );
        }

        Result SetRowBindOffsetPointer( SQLULEN* rowBindOffsetPointer ) const
        {
            return SetPointerAttribute( SQL_ATTR_ROW_BIND_OFFSET_PTR, rowBindOffsetPointer );
        }

        SQLULEN* RowBindOffsetPointer( ) const
        {
            return static_cast< SQLULEN* >( GetPointerAttribute( SQL_ATTR_ROW_BIND_OFFSET_PTR ) );
        }

        Result SetRowBindByColumn( ) const
        {
            return SetUInt64Attribute( SQL_ATTR_ROW_BIND_TYPE, SQL_BIND_BY_COLUMN );
        }
        bool RowBindByColumn( ) const
        {
            return GetUInt64Attribute( SQL_ATTR_ROW_BIND_TYPE ) == SQL_BIND_BY_COLUMN;
        }

        Result SetRowSize( SQLULEN rowSize ) const
        {
            return SetUInt64Attribute( SQL_ATTR_ROW_BIND_TYPE, rowSize );
        }
        SQLULEN RowSize( ) const
        {
            return GetUInt64Attribute( SQL_ATTR_ROW_BIND_TYPE );
        }

        SQLULEN RowNumber( ) const
        {
            return GetUInt64Attribute( SQL_ATTR_ROW_NUMBER );
        }

        Result SetRowOperationPointer( SQLULEN* paramOperationPointer ) const
        {
            return SetPointerAttribute( SQL_ATTR_ROW_OPERATION_PTR, paramOperationPointer );
        }
        SQLULEN* RowOperationPointer( ) const
        {
            return static_cast< SQLULEN* >( GetPointerAttribute( SQL_ATTR_ROW_OPERATION_PTR ) );
        }

        Result SetRowStatusPointer( SQLUSMALLINT* rowStatusPointer ) const
        {
            return SetPointerAttribute( SQL_ATTR_ROW_STATUS_PTR, rowStatusPointer );
        }
        SQLUSMALLINT* RowStatusPointer( ) const
        {
            return static_cast< SQLUSMALLINT* >( GetPointerAttribute( SQL_ATTR_ROW_STATUS_PTR ) );
        }


        Result SetRowsFetchedPointer( SQLULEN* rowsFetched ) const
        {
            return SetPointerAttribute( SQL_ATTR_ROWS_FETCHED_PTR, rowsFetched );
        }
        SQLULEN* RowsFetchedPointer( ) const
        {
            return static_cast< SQLULEN* >( GetPointerAttribute( SQL_ATTR_ROWS_FETCHED_PTR ) );
        }

        Result SetSimulateCursor( ODBC::SimulateCursor simulateCursor ) const
        {
            return SetEnumAttribute( SQL_ATTR_SIMULATE_CURSOR, simulateCursor );
        }
        ODBC::SimulateCursor SimulateCursor( ) const
        {
            return GetEnumAttribute<ODBC::SimulateCursor>( SQL_ATTR_SIMULATE_CURSOR );
        }

        Result SetUseBookmarks( bool useBookmarks ) const
        {
            return SetBooleanAttribute( SQL_ATTR_USE_BOOKMARKS, useBookmarks );
        }
        bool UseBookmarks( ) const
        {
            return GetBooleanAttribute( SQL_ATTR_USE_BOOKMARKS );
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
        SQLSMALLINT NumParams( ) const
        {
            SQLSMALLINT result = 0;
            NumParams( &result );
            return result;
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
    inline Result DataReader::FetchScroll( ODBC::FetchOrientation fetchOrientation, SQLLEN fetchOffset ) const
    {
        return statement_->FetchScroll( fetchOrientation, fetchOffset );
    }
    inline Result DataReader::BindColumn( SQLUSMALLINT columnNumber, NativeType targetType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrLength ) const
    {
        return statement_->BindColumn( columnNumber, targetType, targetValue, targetValueMaxLength, nullIndicatorOrLength );
    }

    [[nodiscard]] 
    inline SQLHANDLE DataReader::Handle( ) const noexcept
    {
        return statement_->Handle( );
    }

    inline Result DataReader::GetData( SQLUSMALLINT columnOrParameterNumber, NativeType targetValueDataType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrTargetValueActualLength ) const
    {
        return statement_->GetData( columnOrParameterNumber, targetValueDataType, targetValue, targetValueMaxLength, nullIndicatorOrTargetValueActualLength );
    }

    [[nodiscard]]
    inline DBBoolean DataReader::GetDBBoolean( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBBoolean( columnNumber );
    }
    [[nodiscard]]
    inline DBByte DataReader::GetDBByte( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBByte( columnNumber );
    }

    [[nodiscard]]
    inline DBSByte DataReader::GetDBSByte( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBSByte( columnNumber );
    }

    [[nodiscard]]
    inline DBInt16 DataReader::GetDBInt16( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBInt16( columnNumber );
    }

    [[nodiscard]]
    inline DBUInt16 DataReader::GetDBUInt16( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBUInt16( columnNumber );
    }

    [[nodiscard]]
    inline DBInt32 DataReader::GetDBInt32( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBInt32( columnNumber );
    }

    [[nodiscard]]
    inline DBUInt32 DataReader::GetDBUInt32( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBUInt32( columnNumber );
    }

    [[nodiscard]]
    inline DBInt64 DataReader::GetDBInt64( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBInt64( columnNumber );
    }

    [[nodiscard]]
    inline DBUInt64 DataReader::GetDBUInt64( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBUInt64( columnNumber );
    }

    [[nodiscard]]
    inline DBNumeric DataReader::GetDBNumeric( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBNumeric( columnNumber );
    }

    [[nodiscard]]
    inline DBDecimal DataReader::GetDBDecimal( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBDecimal( columnNumber );
    }


    [[nodiscard]]
    inline DBSingle DataReader::GetDBSingle( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBSingle( columnNumber );
    }

    [[nodiscard]]
    inline DBDouble DataReader::GetDBDouble( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBDouble( columnNumber );
    }

    [[nodiscard]]
    inline DBCurrency DataReader::GetDBCurrency( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBCurrency( columnNumber );
    }

    [[nodiscard]]
    inline DBDateTime DataReader::GetDBDateTime( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBDateTime( columnNumber );
    }

    [[nodiscard]]
    inline DBTimestampOffset DataReader::GetDBTimestampOffset( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBTimestampOffset( columnNumber );
    }

    [[nodiscard]]
    inline DBDate DataReader::GetDBDate( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBDate( columnNumber );
    }

    [[nodiscard]]
    inline DBTime DataReader::GetDBTime( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBTime( columnNumber );
    }

    [[nodiscard]]
    inline DBTimeSpan DataReader::GetDBTimeSpan( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBTimeSpan( columnNumber );
    }

    [[nodiscard]]
    inline DBWideString DataReader::GetDBWideString( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBWideString( columnNumber );
    }

    [[nodiscard]]
    inline DBAnsiString DataReader::GetDBAnsiString( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBAnsiString( columnNumber );
    }

    [[nodiscard]]
    inline DBBinary DataReader::GetDBBinary( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBBinary( columnNumber );
    }


    [[nodiscard]]
    inline DBGuid DataReader::GetDBGuid( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBGuid( columnNumber );
    }

    [[nodiscard]]
    inline DBRowVersion DataReader::GetDBRowVersion( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBRowVersion( columnNumber );
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
    inline Binary DataReader::GetBinary( SQLUSMALLINT columnNumber ) const
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


    struct ParameterDescription
    {
        const ODBC::Statement& Statement;
        SQLUSMALLINT ParameterNumber;
        ODBC::SqlType DataType;
        SQLULEN ParameterSize;
        SQLSMALLINT DecimalDigits;
        ODBC::Nullable Nullable;

        ParameterDescription( const ODBC::Statement& statement, SQLUSMALLINT parameterNumber, ODBC::SqlType dataType, SQLULEN parameterSize, SQLSMALLINT decimalDigits, ODBC::Nullable nullable )
            : Statement( statement ), ParameterNumber( parameterNumber ), DataType( dataType ), ParameterSize( parameterSize ), DecimalDigits( decimalDigits ), Nullable( nullable )
        {
        }


    };

    inline ParameterDescription Statement::DescribeParameter( SQLUSMALLINT parameterNumber ) const
    {
        ODBC::SqlType dataType = {};
        SQLULEN parameterSize = 0;
        SQLSMALLINT decimalDigits = 0;
        ODBC::Nullable nullable = ODBC::Nullable::Unknown;
        DescribeParameter( parameterNumber, &dataType, &parameterSize, &decimalDigits, &nullable );

        ParameterDescription result(*this, parameterNumber, dataType, parameterSize, decimalDigits, nullable );
        return result;
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
        Descriptor CreateDescriptor( ) const
        {
            auto sqlHandle = AllocateHandle( Handle( ), ODBC::HandleType::Descriptor );
            return Descriptor( sqlHandle );
        }

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


        UInt64 GetUInt64Attribute( SQLINTEGER attributeId ) const
        {
            UInt64 value;
            auto rc = SQLGetConnectAttrW( Handle( ), attributeId, &value, SQL_IS_UINTEGER, nullptr );
            if ( Failed( static_cast< Result >( rc ) ) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }
        Int64 GetInt64Attribute( SQLINTEGER attributeId ) const
        {
            Int64 value;
            auto rc = SQLGetConnectAttrW( Handle( ), attributeId, &value, SQL_IS_INTEGER, nullptr );
            if ( Failed( static_cast< Result >( rc ) ) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }
        SQLPOINTER GetPointerAttribute( SQLINTEGER attributeId ) const
        {
            SQLPOINTER value;
            auto rc = SQLGetConnectAttrW( Handle( ), attributeId, &value, SQL_IS_POINTER, nullptr );
            if ( Failed( static_cast< Result >( rc ) ) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return value;
        }
        bool GetBooleanAttribute( SQLINTEGER attributeId ) const
        {
            return GetUInt64Attribute( attributeId ) != 0;
        }
        ODBC::Descriptor GetDescriptorAttribute( SQLINTEGER attributeId ) const
        {
            SQLHANDLE descriptor = nullptr;
            GetAttributeW( attributeId, &descriptor, SQL_IS_POINTER, nullptr );
            return ODBC::Descriptor( descriptor, false );
        }
        template<typename T>
            requires std::is_enum_v<T>
        T GetEnumAttribute( SQLINTEGER attributeId ) const
        {
            UInt64 value;
            auto rc = SQLGetConnectAttrW( Handle( ), attributeId, &value, SQL_IS_UINTEGER, nullptr );
            if ( Failed( static_cast< Result >( rc ) ) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast< T >( value );
        }


        WideString GetWideStringAttribute( SQLINTEGER attributeId ) const
        {
            constexpr SQLINTEGER bufferSize = 1024;
            SQLINTEGER actualLength = 0;
            wchar_t buffer[bufferSize];
            auto rc = GetAttributeW( attributeId, buffer, bufferSize*sizeof(wchar_t), &actualLength );
            WideString result;
            result.assign( buffer, static_cast<size_t>( actualLength/sizeof(wchar_t) ) );
            return result;
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

        Result SetUInt64Attribute( SQLINTEGER attributeId, UInt64 value ) const
        {
            return SetAttributeW( attributeId, reinterpret_cast< SQLPOINTER >( value ), SQL_IS_UINTEGER );
        }
        Result SetInt64Attribute( SQLINTEGER attributeId, Int64 value ) const
        {
            return SetAttributeW( attributeId, reinterpret_cast< SQLPOINTER >( value ), SQL_IS_INTEGER );
        }
        Result SetBooleanAttribute( SQLINTEGER attributeId, bool value ) const
        {
            return SetAttributeW( attributeId, reinterpret_cast< SQLPOINTER >( value ? 1ULL : 0ULL ), SQL_IS_UINTEGER );
        }

        Result SetPointerAttribute( SQLINTEGER attributeId, SQLPOINTER value ) const
        {
            return SetAttributeW( attributeId, value, SQL_IS_POINTER );
        }

        Result SetDescriptorAttribute( SQLINTEGER attributeId, SQLHANDLE value ) const
        {
            return SetAttributeW( attributeId, value, SQL_IS_POINTER );
        }
        Result SetDescriptorAttribute( SQLINTEGER attributeId, const Descriptor& value ) const
        {
            return SetAttributeW( attributeId, value.Handle( ), SQL_IS_POINTER );
        }

        template<typename T>
            requires std::is_enum_v<T>
        Result SetEnumAttribute( SQLINTEGER attributeId, T value ) const
        {
            return SetAttributeW( attributeId, reinterpret_cast< SQLPOINTER >( value ), SQL_IS_UINTEGER );
        }

        Result SetWideStringAttribute( SQLINTEGER attributeId, const WideString& value ) const
        {
            auto rc = SetAttributeW( attributeId, const_cast<wchar_t*>(value.c_str( )), static_cast<SQLINTEGER>( value.length( )*sizeof(wchar_t) ) );
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


        Result SetAccessMode( ODBC::AccessMode accessMode ) const
        {
            return SetEnumAttribute( SQL_ATTR_ACCESS_MODE, accessMode );
        }

        ODBC::AccessMode AccessMode( ) const
        {
            return GetEnumAttribute<ODBC::AccessMode>( SQL_ATTR_ACCESS_MODE );
        }

        Result SetAsyncEvent( const EventWaitHandle& eventWaitHandle ) const
        {
            return SetPointerAttribute( SQL_ATTR_ASYNC_DBC_EVENT, eventWaitHandle.GetHandle() );
        }
        Result SetAsyncEvent( HANDLE eventWaitHandle ) const
        {
            return SetPointerAttribute( SQL_ATTR_ASYNC_DBC_EVENT, eventWaitHandle );
        }
        HANDLE AsyncEvent( ) const
        {
            return GetPointerAttribute( SQL_ATTR_ASYNC_DBC_EVENT );
        }

        Result SetAsyncConnectionFunctionsEnabled( bool asyncEnable ) const
        {
            auto rc = SetBooleanAttribute( SQL_ATTR_ASYNC_DBC_FUNCTIONS_ENABLE, asyncEnable );
            return rc;
        }

        bool AsyncConnectionFunctionsEnabled( ) const
        {
            return GetBooleanAttribute( SQL_ATTR_ASYNC_DBC_FUNCTIONS_ENABLE );
        }

        Result SetAsyncEnabled( bool asyncEnable ) const
        {
            auto rc = SetBooleanAttribute( SQL_ATTR_ASYNC_ENABLE, asyncEnable );
            return rc;
        }

        bool AsyncEnabled( ) const
        {
            return GetBooleanAttribute( SQL_ATTR_ASYNC_ENABLE );
        }

        bool SupportsAutoPopulateImplementationParameterDescriptor( ) const
        {
            return GetBooleanAttribute( SQL_ATTR_AUTO_IPD );
        }

        Result SetAutoCommit( bool autoCommit ) const
        {
            return SetBooleanAttribute( SQL_ATTR_AUTOCOMMIT, autoCommit );
        }

        bool AutoCommit( ) const
        {
            return GetBooleanAttribute( SQL_ATTR_AUTOCOMMIT );
        }

        bool ConnectionDead( ) const
        {
            return GetBooleanAttribute( SQL_ATTR_CONNECTION_DEAD );
        }
        bool Connected( ) const
        {
            return ConnectionDead( ) == false;
        }

        Result SetDTCTransaction( ITransaction* transaction ) const
        {
            return SetPointerAttribute( SQL_ATTR_ENLIST_IN_DTC, transaction );
        }


        Result SetCurrentCatalog( const WideString& currentCatalog ) const
        {
            auto rc = SetWideStringAttribute( SQL_ATTR_CURRENT_CATALOG, currentCatalog );
            return rc;
        }

        WideString CurrentCatalog( ) const
        {
            return GetWideStringAttribute( SQL_ATTR_CURRENT_CATALOG );
        }


        Result SetAutoCommitMode( bool enabled ) const
        {
            return SetBooleanAttribute( SQL_ATTR_AUTOCOMMIT, enabled );
        }

        bool AutoCommitMode( bool enabled ) const
        {
            return GetBooleanAttribute( SQL_ATTR_AUTOCOMMIT );
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

        Result DataSources( ODBC::FetchOrientation direction, SQLWCHAR* datasourceName, SQLSMALLINT datasourceNameMaxLength, SQLSMALLINT* datasourceNameActualLength, SQLWCHAR* datasourceDescription, SQLSMALLINT datasourceDescriptionMaxLength, SQLSMALLINT* datasourceDescriptionActualLength ) const
        {
            auto rc = SQLDataSourcesW( Handle( ), static_cast< SQLUSMALLINT >( direction ), datasourceName, datasourceNameMaxLength, datasourceNameActualLength, datasourceDescription, datasourceDescriptionMaxLength, datasourceDescriptionActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast< Result >( rc );
        }


        Result DataSources( ODBC::FetchOrientation direction, SQLCHAR* datasourceName, SQLSMALLINT datasourceNameMaxLength, SQLSMALLINT* datasourceNameActualLength, SQLCHAR* datasourceDescription, SQLSMALLINT datasourceDescriptionMaxLength, SQLSMALLINT* datasourceDescriptionActualLength ) const
        {
            auto rc = SQLDataSourcesA( Handle( ), static_cast<SQLUSMALLINT>( direction ), datasourceName, datasourceNameMaxLength, datasourceNameActualLength, datasourceDescription, datasourceDescriptionMaxLength, datasourceDescriptionActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        std::vector<ODBC::DataSource> DataSources( ODBC::FetchOrientation direction = ODBC::FetchOrientation::First )
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
                rc = DataSources( ODBC::FetchOrientation::Next, dataSourceName, 1024, &dataSourceNameLength, dataSourceDescription, 1024, &dataSourceDescriptionLength );
            }

            return result;
        }


        Result Drivers( ODBC::FetchOrientation direction, SQLWCHAR* driverDescription, SQLSMALLINT driverDescriptionMaxLength, SQLSMALLINT* driverDescriptionActualLength, SQLWCHAR* driverAttributes, SQLSMALLINT driverAttributesMaxLength, SQLSMALLINT* driverAttributesActualLength ) const
        {
            auto rc = SQLDriversW( Handle( ), static_cast<SQLUSMALLINT>( direction ), driverDescription, driverDescriptionMaxLength, driverDescriptionActualLength, driverAttributes, driverAttributesMaxLength, driverAttributesActualLength );
            if ( Failed(static_cast<Result>(rc)) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        std::vector<ODBC::Driver> Drivers( ODBC::FetchOrientation direction )
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
                rc = Drivers( ODBC::FetchOrientation::Next, driverDescription, 1024, &driverDescriptionLength, driverAttributes, 1024, &driverAttributesLength );
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

