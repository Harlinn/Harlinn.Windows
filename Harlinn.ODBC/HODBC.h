#pragma once
#ifndef __HODBC_H__
#define __HODBC_H__
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

#include <HODBCMsSql.h>

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
                return IsNull( ) == false ? &value_ : nullptr;
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
        /// <summary>
        ///  Connection pooling is turned off. This is the default.
        /// </summary>
        Off = SQL_CP_OFF,
        /// <summary>
        ///  Connection pooling is turned off. This is the default.
        /// </summary>
        Default = SQL_CP_DEFAULT,
        /// <summary>
        /// A single connection pool is supported for each driver. Every connection 
        /// in a pool is associated with one driver.
        /// </summary>
        OnePerDriver = SQL_CP_ONE_PER_DRIVER,
        /// <summary>
        ///  A single connection pool is supported for each environment. Every 
        /// connection in a pool is associated with one environment.
        /// </summary>
        OnePerEnvironment = SQL_CP_ONE_PER_HENV,
        /// <summary>
        /// Use the connection-pool awareness feature of the driver, if it is available. 
        /// If the driver does not support connection-pool awareness, DriverAware is ignored and 
        /// OnePerEnvironment is used. For more information, see Driver-Aware Connection Pooling. 
        /// In an environment where some drivers support and some drivers do not support connection-pool 
        /// awareness, DriverAware can enable the connection-pool awareness feature on those supporting 
        /// drivers, but it is equivalent to setting to OnePerEnvironment on those drivers that do not 
        /// support connection-pool awareness feature.
        /// </summary>
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

    struct TimeStampOffset
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

    using DBTimeStampOffset = Internal::DBValue<TimeStampOffset>;


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
        void SetHandle( SQLHANDLE sqlHandle, bool destructorClosesHandle )
        {
            if ( sqlHandle != sqlHandle_ )
            {
                if ( destructorClosesHandle_ )
                {
                    Close( );
                }
                sqlHandle_ = sqlHandle;
                destructorClosesHandle_ = destructorClosesHandle;
            }
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
        inline DBTimeStampOffset GetDBTimeStampOffset( SQLUSMALLINT columnNumber ) const;
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
        inline TimeStampOffset GetTimeStampOffset( SQLUSMALLINT columnNumber ) const;

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


        Result BindBooleanColumn( SQLUSMALLINT columnNumber, bool* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Boolean, targetAddress, sizeof( Byte ), nullIndicatorOrActualLength );
        }
        Result BindBooleanColumn( SQLUSMALLINT columnNumber, DBBoolean& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::Boolean, dbValue.data(), sizeof( Byte ), dbValue.Indicator() );
        }
        Result BindSByteColumn( SQLUSMALLINT columnNumber, SByte* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::SByte, targetAddress, sizeof( SByte ), nullIndicatorOrActualLength );
        }
        Result BindSByteColumn( SQLUSMALLINT columnNumber, DBSByte& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::SByte, dbValue.data( ), sizeof( SByte ), dbValue.Indicator( ) );
        }

        Result BindByteColumn( SQLUSMALLINT columnNumber, Byte* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Byte, targetAddress, sizeof( Byte ), nullIndicatorOrActualLength );
        }
        Result BindByteColumn( SQLUSMALLINT columnNumber, DBByte& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::Byte, dbValue.data( ), sizeof( Byte ), dbValue.Indicator( ) );
        }

        Result BindInt16Column( SQLUSMALLINT columnNumber, Int16* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Int16, targetAddress, sizeof( Int16 ), nullIndicatorOrActualLength );
        }
        Result BindInt16Column( SQLUSMALLINT columnNumber, DBInt16& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::Int16, dbValue.data( ), sizeof( Int16 ), dbValue.Indicator( ) );
        }

        Result BindUInt16Column( SQLUSMALLINT columnNumber, UInt16* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::UInt16, targetAddress, sizeof( UInt16 ), nullIndicatorOrActualLength );
        }
        Result BindUInt16Column( SQLUSMALLINT columnNumber, DBUInt16& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::UInt16, dbValue.data( ), sizeof( UInt16 ), dbValue.Indicator( ) );
        }

        Result BindInt32Column( SQLUSMALLINT columnNumber, Int32* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Int32, targetAddress, sizeof( Int32 ), nullIndicatorOrActualLength );
        }
        Result BindInt32Column( SQLUSMALLINT columnNumber, DBInt32& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::Int32, dbValue.data( ), sizeof( Int32 ), dbValue.Indicator( ) );
        }


        Result BindUInt32Column( SQLUSMALLINT columnNumber, UInt32* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::UInt32, targetAddress, sizeof( UInt32 ), nullIndicatorOrActualLength );
        }
        Result BindUInt32Column( SQLUSMALLINT columnNumber, DBUInt32& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::UInt32, dbValue.data( ), sizeof( UInt32 ), dbValue.Indicator( ) );
        }

        Result BindInt64Column( SQLUSMALLINT columnNumber, Int64* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Int64, targetAddress, sizeof( Int64 ), nullIndicatorOrActualLength );
        }
        Result BindInt64Column( SQLUSMALLINT columnNumber, DBInt64& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::Int64, dbValue.data( ), sizeof( Int64 ), dbValue.Indicator( ) );
        }
        Result BindUInt64Column( SQLUSMALLINT columnNumber, UInt64* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::UInt64, targetAddress, sizeof( UInt64 ), nullIndicatorOrActualLength );
        }
        Result BindUInt64Column( SQLUSMALLINT columnNumber, DBUInt64& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::UInt64, dbValue.data( ), sizeof( UInt64 ), dbValue.Indicator( ) );
        }

        Result BindSingleColumn( SQLUSMALLINT columnNumber, float* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Single, targetAddress, sizeof( float ), nullIndicatorOrActualLength );
        }
        Result BindSingleColumn( SQLUSMALLINT columnNumber, DBSingle& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::Single, dbValue.data( ), sizeof( float ), dbValue.Indicator( ) );
        }

        Result BindDoubleColumn( SQLUSMALLINT columnNumber, double* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Double, targetAddress, sizeof( double ), nullIndicatorOrActualLength );
        }
        Result BindDoubleColumn( SQLUSMALLINT columnNumber, DBDouble& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::Double, dbValue.data( ), sizeof( double ), dbValue.Indicator( ) );
        }

        Result BindDateTimeColumn( SQLUSMALLINT columnNumber, DateTime* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Int64, targetAddress, sizeof( Int64 ), nullIndicatorOrActualLength );
        }
        Result BindDateTimeColumn( SQLUSMALLINT columnNumber, DBDateTime& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::Int64, dbValue.data( ), sizeof( Int64 ), dbValue.Indicator( ) );
        }

        Result BindTimeSpanColumn( SQLUSMALLINT columnNumber, TimeSpan* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Int64, targetAddress, sizeof( Int64 ), nullIndicatorOrActualLength );
        }
        Result BindTimeSpanColumn( SQLUSMALLINT columnNumber, DBTimeSpan& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::Int64, dbValue.data( ), sizeof( Int64 ), dbValue.Indicator( ) );
        }


        Result BindGuidColumn( SQLUSMALLINT columnNumber, Guid* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Guid, targetAddress, sizeof( Guid ), nullIndicatorOrActualLength );
        }
        Result BindGuidColumn( SQLUSMALLINT columnNumber, DBGuid& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::Guid, dbValue.data( ), sizeof( Guid ), dbValue.Indicator( ) );
        }

        Result BindCurrencyColumn( SQLUSMALLINT columnNumber, Currency* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Int64, targetAddress, sizeof( Int64 ), nullIndicatorOrActualLength );
        }
        Result BindCurrencyColumn( SQLUSMALLINT columnNumber, DBCurrency& dbValue ) const
        {
            return BindColumn( columnNumber, NativeType::Int64, dbValue.data( ), sizeof( Int64 ), dbValue.Indicator( ) );
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
        
        Result BindTimeColumn( SQLUSMALLINT columnNumber, ODBC::Time* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::TypeTime, targetAddress, sizeof( ODBC::Time ), nullIndicatorOrActualLength );
        }

        Result BindTime2Column( SQLUSMALLINT columnNumber, ODBC::Time2* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Binary, targetAddress, sizeof( ODBC::Time2 ), nullIndicatorOrActualLength );
        }

        Result BindIntervalColumn( SQLUSMALLINT columnNumber, ODBC::Interval* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::IntervalDayToSecond, targetAddress, sizeof( ODBC::Interval ), nullIndicatorOrActualLength );
        }
        
        
        Result BindTimeStampColumn( SQLUSMALLINT columnNumber, ODBC::TimeStamp* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::TypeTimeStamp, targetAddress, sizeof( ODBC::TimeStamp ), nullIndicatorOrActualLength );
        }

        Result BindTimeStampOffsetColumn( SQLUSMALLINT columnNumber, ODBC::TimeStampOffset* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Binary, targetAddress, sizeof( ODBC::TimeStampOffset ), nullIndicatorOrActualLength );
        }

        Result BindNumericColumn( SQLUSMALLINT columnNumber, ODBC::Numeric* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Numeric, targetAddress, sizeof( ODBC::Numeric ), nullIndicatorOrActualLength );
        }

        Result BindMoneyColumn( SQLUSMALLINT columnNumber, ODBC::Money* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Binary, targetAddress, sizeof( ODBC::Money ), nullIndicatorOrActualLength );
        }

        Result BindRowVersionColumn( SQLUSMALLINT columnNumber, ODBC::RowVersion* targetAddress, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Binary, targetAddress, sizeof( ODBC::RowVersion ), nullIndicatorOrActualLength );
        }


        template<size_t maxSize>
        Result BindBinaryColumn( SQLUSMALLINT columnNumber, FixedDBBinary<maxSize>* targetAddress ) const
        {
            return BindColumn( columnNumber, NativeType::Binary, targetAddress->data(), maxSize, targetAddress->Indicator() );
        }
        template<size_t maxSize>
        Result BindStringColumn( SQLUSMALLINT columnNumber, FixedDBWideString<maxSize>* targetAddress ) const
        {
            return BindColumn( columnNumber, NativeType::WideChar, targetAddress->data( ), (maxSize + 1) * sizeof(wchar_t), targetAddress->Indicator( ) );
        }
        template<size_t maxSize>
        Result BindStringColumn( SQLUSMALLINT columnNumber, FixedDBAnsiString<maxSize>* targetAddress ) const
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
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Short, SqlType::Integer, 0, 0, parameterValue, 0, nullIndicator );
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

        Result BindStringParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, AnsiString& parameterValue, SQLLEN* lengthOrIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindVarCharParameter( parameterNumber, columnSize, parameterValue.data(), static_cast<SQLLEN>(parameterValue.size()), lengthOrIndicator, parameterDirection );
            return rc;
        }
        Result BindStringParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, const AnsiString& parameterValue, SQLLEN* lengthOrIndicator ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindVarCharParameter( parameterNumber, columnSize, const_cast<char*>(parameterValue.data( )), parameterValueBufferLength, lengthOrIndicator, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindStringParameter( SQLUSMALLINT parameterNumber, AnsiString& parameterValue, SQLLEN* lengthOrIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindVarCharParameter( parameterNumber, 0, parameterValue.data( ), parameterValueBufferLength, lengthOrIndicator, parameterDirection );
            return rc;
        }
        Result BindStringParameter( SQLUSMALLINT parameterNumber, const AnsiString& parameterValue, SQLLEN* lengthOrIndicator ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindVarCharParameter( parameterNumber, 0, const_cast< char* >( parameterValue.data( ) ), parameterValueBufferLength, lengthOrIndicator, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindStringParameter( SQLUSMALLINT parameterNumber, AnsiString& parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindVarCharParameter( parameterNumber, 0, parameterValue.data( ), parameterValueBufferLength, nullptr, parameterDirection );
            return rc;
        }
        Result BindStringParameter( SQLUSMALLINT parameterNumber, const AnsiString& parameterValue ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindVarCharParameter( parameterNumber, 0, const_cast< char* >( parameterValue.data( ) ), parameterValueBufferLength, nullptr, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindStringParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, const DBAnsiString& parameterValue ) const
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
        Result BindStringParameter( SQLUSMALLINT parameterNumber, const DBAnsiString& parameterValue ) const
        {
            return BindStringParameter( parameterNumber, 0, parameterValue );
        }

        Result BindStringParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, WideString& parameterValue, SQLLEN* lengthOrIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindNVarCharParameter( parameterNumber, columnSize, parameterValue.data( ), parameterValueBufferLength, lengthOrIndicator, parameterDirection );
            return rc;
        }
        Result BindStringParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, const WideString& parameterValue, SQLLEN* lengthOrIndicator ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindNVarCharParameter( parameterNumber, columnSize, const_cast< wchar_t* >( parameterValue.data( ) ), parameterValueBufferLength, lengthOrIndicator, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindStringParameter( SQLUSMALLINT parameterNumber, WideString& parameterValue, SQLLEN* lengthOrIndicator, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindNVarCharParameter( parameterNumber, 0, parameterValue.data( ), parameterValueBufferLength, lengthOrIndicator, parameterDirection );
            return rc;
        }
        Result BindStringParameter( SQLUSMALLINT parameterNumber, const WideString& parameterValue, SQLLEN* lengthOrIndicator ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindNVarCharParameter( parameterNumber, 0, const_cast< wchar_t* >( parameterValue.data( ) ), parameterValueBufferLength, lengthOrIndicator, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindStringParameter( SQLUSMALLINT parameterNumber, WideString& parameterValue, ODBC::ParameterDirection parameterDirection ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindNVarCharParameter( parameterNumber, 0, parameterValue.data( ), parameterValueBufferLength, nullptr, parameterDirection );
            return rc;
        }
        Result BindStringParameter( SQLUSMALLINT parameterNumber, const WideString& parameterValue ) const
        {
            SQLLEN parameterValueBufferLength = parameterValue.Length( ) + 1;
            auto rc = BindNVarCharParameter( parameterNumber, 0, const_cast< wchar_t* >( parameterValue.data( ) ), parameterValueBufferLength, nullptr, ODBC::ParameterDirection::Input );
            return rc;
        }
        Result BindStringParameter( SQLUSMALLINT parameterNumber, SQLULEN columnSize, const DBWideString& parameterValue ) const
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
        Result BindStringParameter( SQLUSMALLINT parameterNumber, const DBWideString& parameterValue ) const
        {
            return BindStringParameter( parameterNumber, 0, parameterValue );
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
        DBTimeStampOffset GetDBTimeStampOffset( SQLUSMALLINT columnNumber ) const
        {
            TimeStampOffset value;
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
        TimeStampOffset GetTimeStampOffset( SQLUSMALLINT columnNumber ) const
        {
            TimeStampOffset value;
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

        void ConsumeResults( ) const
        {
            while( MoreResults( ) != Result::NoData)
            { }
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
        SQLLEN RowCount( ) const
        {
            SQLLEN result = 0;
            RowCount( &result );
            return result;
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
    inline DBTimeStampOffset DataReader::GetDBTimeStampOffset( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetDBTimeStampOffset( columnNumber );
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
    inline TimeStampOffset DataReader::GetTimeStampOffset( SQLUSMALLINT columnNumber ) const
    {
        return statement_->GetTimeStampOffset( columnNumber );
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

        Result Connect( const SQLCHAR* datasourceName, SQLSMALLINT datasourceNameLength, const SQLCHAR* userName, SQLSMALLINT userNameLength, const SQLCHAR* authenticationString, SQLSMALLINT authenticationStringLength ) const
        {
            auto rc = SQLConnectA( Handle( ), const_cast< SQLCHAR* >( datasourceName ), datasourceNameLength, const_cast< SQLCHAR* >( userName ), userNameLength, const_cast< SQLCHAR* >( authenticationString ), authenticationStringLength );
            if ( Failed( static_cast< Result >( rc ) ) )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast< Result >( rc );
        }

        template<SimpleStringLike StringT>
        Result Connect( const StringT& datasourceName ) const
        {
            return Connect( datasourceName.c_str( ), static_cast< SQLSMALLINT >( datasourceName.size( ) ), nullptr, 0, nullptr, 0 );
        }


        template<SimpleStringLike StringT1, SimpleStringLike StringT2>
        Result Connect( const StringT1& datasourceName, const StringT2& userName ) const
        {
            return Connect( datasourceName.c_str( ), static_cast< SQLSMALLINT >( datasourceName.size( ) ),
                            userName.c_str( ), static_cast< SQLSMALLINT >( userName.size( ) ),
                            nullptr, 0 );
        }

        template<SimpleStringLike StringT1, SimpleStringLike StringT2, SimpleStringLike StringT3>
        Result Connect( const StringT1& datasourceName, const StringT2& userName, const StringT3& authenticationString ) const
        {
            return Connect( datasourceName.c_str(), static_cast< SQLSMALLINT >( datasourceName.size() ),
                            userName.c_str( ), static_cast< SQLSMALLINT >( userName.size( ) ),
                            authenticationString.c_str( ), static_cast< SQLSMALLINT >( authenticationString.size( ) ) );
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

        template<SimpleWideStringLike StringT>
        Result SetWideStringAttribute( SQLINTEGER attributeId, const StringT& value ) const
        {
            auto rc = SetAttributeW( attributeId, const_cast<wchar_t*>(value.c_str( )), static_cast<SQLINTEGER>( value.size( )*sizeof(wchar_t) ) );
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


        template<SimpleWideStringLike StringT>
        Result SetCurrentCatalog( const StringT& currentCatalog ) const
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

        explicit Environment( ODBC::Version version ) noexcept
        {
            auto sqlHandle = AllocateHandle( );
            SetHandle( sqlHandle, true );
            SetVersion( version );
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


        std::vector<ODBC::DataSource> DataSources( ODBC::FetchOrientation direction = ODBC::FetchOrientation::First ) const
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

        std::vector<ODBC::Driver> Drivers( ODBC::FetchOrientation direction ) const
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


        ODBC::Connection CreateConnection( ) const
        {
            auto connectionHandle = ODBC::Connection::AllocateHandle( Handle( ) );
            ODBC::Connection result( connectionHandle );
            return result;
        }

        template<SimpleWideStringLike StringT>
        ODBC::Connection Connect( const StringT& datasourceName ) const
        {
            auto connection = CreateConnection( );
            connection.Connect( datasourceName.c_str( ), static_cast<SQLSMALLINT>( datasourceName.size( ) ), nullptr, 0, nullptr, 0 );
            return connection;
        }

        template<SimpleWideStringLike StringT1, SimpleWideStringLike StringT2>
        ODBC::Connection Connect( const StringT1& datasourceName, const StringT2& userName ) const
        {
            auto connection = CreateConnection( );
            connection.Connect( datasourceName.c_str( ), static_cast<SQLSMALLINT>( datasourceName.size( ) ), userName.c_str( ), static_cast<SQLSMALLINT>( userName.size( ) ), nullptr, 0 );
            return connection;
        }

        template<SimpleWideStringLike StringT1, SimpleWideStringLike StringT2, SimpleWideStringLike StringT3>
        ODBC::Connection Connect( const StringT1& datasourceName, const StringT2& userName, const StringT3& authenticationString ) const
        {
            auto connection = CreateConnection( );
            connection.Connect( datasourceName.c_str( ), static_cast<SQLSMALLINT>( datasourceName.size( ) ), userName.c_str( ), static_cast<SQLSMALLINT>( userName.size( ) ), authenticationString.c_str( ), static_cast<SQLSMALLINT>( authenticationString.size( ) ) );
            return connection;
        }
    };


}

#endif

