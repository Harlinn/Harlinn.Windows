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

namespace Harlinn::ODBC
{
    class Environment;
    class Connection;
    class Statement;
    class Descriptor;
    class DataReaderBase;

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
    constexpr bool Succeeded( Result result )
    {
        return SQL_SUCCEEDED( static_cast<SQLRETURN>( result ) );
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



    namespace Internal
    {
        HODBC_EXPORT void ThrowException( SQLRETURN sqlReturn, ODBC::HandleType handleType, SQLHANDLE sqlHandle, const wchar_t* function, const wchar_t* file, int line );
        HODBC_EXPORT void ThrowException( SQLRETURN sqlReturn, ODBC::HandleType handleType, SQLHANDLE sqlHandle );
        HODBC_EXPORT void ThrowExceptionNoDiagnostic( SQLRETURN sqlReturn, ODBC::HandleType handleType, SQLHANDLE sqlHandle, const wchar_t* function, const wchar_t* file, int line );
        HODBC_EXPORT void ThrowExceptionNoDiagnostic( SQLRETURN sqlReturn, ODBC::HandleType handleType, SQLHANDLE sqlHandle );

        Result GetDiagnosticFieldW( ODBC::HandleType handleType, SQLHANDLE handle,
            SQLSMALLINT recordNumber,
            SQLSMALLINT diagnosticFieldId,
            SQLPOINTER  diagnosticInfo,
            SQLSMALLINT diagnosticInfoMaxLength,
            SQLSMALLINT* diagnosticInfoActualLength )
        {
            auto rc = SQLGetDiagFieldW( static_cast<SQLSMALLINT>( handleType ), handle, recordNumber, diagnosticFieldId, diagnosticInfo, diagnosticInfoMaxLength, diagnosticInfoActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowExceptionNoDiagnostic( rc, handleType, handle, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result GetDiagnosticFieldA( ODBC::HandleType handleType, SQLHANDLE handle,
            SQLSMALLINT recordNumber,
            SQLSMALLINT diagnosticFieldId,
            SQLPOINTER  diagnosticInfo,
            SQLSMALLINT diagnosticInfoMaxLength,
            SQLSMALLINT* diagnosticInfoActualLength )
        {
            auto rc = SQLGetDiagFieldA( static_cast<SQLSMALLINT>( handleType ), handle, recordNumber, diagnosticFieldId, diagnosticInfo, diagnosticInfoMaxLength, diagnosticInfoActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowExceptionNoDiagnostic( rc, handleType, handle, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result GetDiagnosticRecord( ODBC::HandleType handleType, SQLHANDLE handle, SQLSMALLINT recordNumber, SQLWCHAR* sqlState, SQLINTEGER* nativeError, SQLWCHAR* message, SQLSMALLINT messageMaxLength, SQLSMALLINT* messageActualLength )
        {
            auto rc = SQLGetDiagRecW( static_cast<SQLSMALLINT>( handleType ), handle, recordNumber, sqlState, nativeError, message, messageMaxLength, messageActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowExceptionNoDiagnostic( rc, handleType, handle, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result GetDiagnosticRecord( ODBC::HandleType handleType, SQLHANDLE handle, SQLSMALLINT recordNumber, SQLCHAR* sqlState, SQLINTEGER* nativeError, SQLCHAR* message, SQLSMALLINT messageMaxLength, SQLSMALLINT* messageActualLength )
        {
            auto rc = SQLGetDiagRecA( static_cast<SQLSMALLINT>( handleType ), handle, recordNumber, sqlState, nativeError, message, messageMaxLength, messageActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowExceptionNoDiagnostic( rc, handleType, handle, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
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


    /// <summary>
    /// This template implements functionality common to
    /// the ODBC handle wrapper classes
    /// </summary>
    template<ODBC::HandleType handleType>
    class SqlHandle
    {
    public:
        static constexpr ODBC::HandleType HandleType = handleType;
    private:
        SQLHANDLE sqlHandle_;
    public:
        constexpr SqlHandle() noexcept
            : sqlHandle_( SQL_NULL_HANDLE )
        { 

        }
    protected:
        constexpr SqlHandle( SQLHANDLE sqlHandle ) noexcept
            : sqlHandle_( sqlHandle )
        {

        }
    public:

        SqlHandle( const SqlHandle& other ) = delete;
        constexpr SqlHandle( SqlHandle&& other ) noexcept
            : sqlHandle_( other.sqlHandle_ )
        {
            other.sqlHandle_ = nullptr;
        }


        SqlHandle& operator = ( const SqlHandle& other ) = delete;
        constexpr SqlHandle& operator = ( SqlHandle&& other ) noexcept
        {
            std::swap( sqlHandle_, other.sqlHandle_ );
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
            SQLHANDLE result = SQL_NULL_HANDLE;
            auto rc = SQLAllocHandle( static_cast<SQLSMALLINT>(HandleType), inputHandle, &result );
            if ( rc != SQL_SUCCESS )
            {
                Internal::ThrowException( rc, HandleType, result, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return result;
        }


    public:
        void Close( ) noexcept
        {
            if ( sqlHandle_ )
            {
                SQLFreeHandle( static_cast<SQLSMALLINT>( HandleType ), sqlHandle_ );
                sqlHandle_ = SQL_NULL_HANDLE;
            }
        }

        Result Cancel( ) const
        {
            auto rc = SQLCancelHandle( static_cast<SQLSMALLINT>( HandleType ), sqlHandle_ );
            if ( rc < SQL_SUCCESS )
            {
                Internal::ThrowException( rc, HandleType, Handle( ), CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result CompleteAsync( RETCODE* asyncRetCode ) const
        {
            auto rc = SQLCompleteAsync( static_cast<SQLSMALLINT>( HandleType ), sqlHandle_, asyncRetCode );
            if ( rc < SQL_SUCCESS )
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
    public:
        using Base = SqlHandle<ODBC::HandleType::Descriptor>;

        Descriptor( )
            : Base( )
        {
        }
    private:
        Descriptor( SQLHANDLE sqlHandle )
            : Base( sqlHandle )
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
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result GetFieldA( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier, SQLPOINTER value, SQLINTEGER valueMaxLength, SQLINTEGER* valueActualLength ) const
        {
            auto rc = SQLGetDescFieldA( Handle( ), recordNumber, fieldIdentifier, value, valueMaxLength, valueActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result GetRecord( SQLSMALLINT recordNumber, SQLWCHAR* name, SQLSMALLINT nameMaxLength, SQLSMALLINT* nameActualLength, SQLSMALLINT* type, SQLSMALLINT* subType, SQLLEN* length, SQLSMALLINT* precision, SQLSMALLINT* scale, SQLSMALLINT* nullable ) const
        {
            auto rc = SQLGetDescRecW( Handle( ), recordNumber, name, nameMaxLength, nameActualLength, type, subType, length, precision, scale, nullable );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result GetRecord( SQLSMALLINT recordNumber, SQLCHAR* name, SQLSMALLINT nameMaxLength, SQLSMALLINT* nameActualLength, SQLSMALLINT* type, SQLSMALLINT* subType, SQLLEN* length, SQLSMALLINT* precision, SQLSMALLINT* scale, SQLSMALLINT* nullable ) const
        {
            auto rc = SQLGetDescRecA( Handle( ), recordNumber, name, nameMaxLength, nameActualLength, type, subType, length, precision, scale, nullable );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SetFieldW( SQLSMALLINT recordNumber, SQLSMALLINT fieldIdentifier, SQLPOINTER value, SQLINTEGER valueLength ) const
        {
            auto rc = SQLSetDescFieldW( Handle( ), recordNumber, fieldIdentifier, value, valueLength );
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
    };


    class ColumnBase
    {
    protected:
        SQLLEN nullIndicatorOrLength_;
    public:
        constexpr ColumnBase( SQLLEN nullIndicatorOrLength = SQL_NULL_DATA ) noexcept
            : nullIndicatorOrLength_( nullIndicatorOrLength )
        { }
    };

    template<typename ValueT, SQLSMALLINT targetType>
    class ColumnBaseT : public ColumnBase
    {
    public:
        using Base = ColumnBase;
        using ValueType = ValueT;
        static constexpr SQLSMALLINT TargetType = targetType;
    private:
        ValueType value_{};
    public:
        constexpr ColumnBaseT( ) noexcept
            : Base( ), value_{}
        {
        }

        constexpr ColumnBaseT( ValueType value ) noexcept
            : Base( ), value_( value )
        {
        }

        constexpr ColumnBaseT( ValueType value, SQLLEN nullIndicatorOrLength ) noexcept
            : Base( nullIndicatorOrLength ), value_( value )
        {
        }

    };


    template<>
    class ColumnBaseT<bool,NativeType::Boolean> : public ColumnBase
    {
    public:
        using Base = ColumnBase;
        using ValueType = bool;
        static constexpr SQLSMALLINT TargetType = NativeType::Boolean;

    };








    // Derived classes *must* implement:
    // void BindColumns( ) 
    class DataReaderBase
    {
        const Statement* statement_;
    public:
        constexpr DataReaderBase( const Statement* statement ) noexcept
            : statement_( statement )
        { }

        DataReaderBase( const DataReaderBase& other ) = delete;
        DataReaderBase( DataReaderBase&& other ) = delete;
        DataReaderBase& operator = ( const DataReaderBase& other ) = delete;
        DataReaderBase& operator = ( DataReaderBase&& other ) = delete;

        bool Read( ) const
        {
            auto rc = Fetch( );
            return rc != ODBC::Result::NoData;
        }

    protected:
        Result Fetch( ) const;
        Result FetchScroll( ODBC::Fetch fetchOrientation, SQLLEN fetchOffset ) const;
        
        Result BindColumn( SQLUSMALLINT columnNumber, SQLSMALLINT targetType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrLength ) const;


        Result Bind( SQLUSMALLINT columnNumber, SQLPOINTER targetAddress, SQLLEN targetAddressMaxLength, SQLLEN* nullIndicatorOrActualLength ) const
        {
            return BindColumn( columnNumber, NativeType::Char, targetAddress, targetAddressMaxLength, nullIndicatorOrActualLength );
        }

        Result Bind( SQLUSMALLINT columnNumber, Double* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Double, targetAddress, sizeof( Double ), nullIndicatorOrActualLength );
        }
        Result Bind( SQLUSMALLINT columnNumber, bool* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Boolean, targetAddress, sizeof( bool ), nullIndicatorOrActualLength );
        }
        Result Bind( SQLUSMALLINT columnNumber, Int64* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Int64, targetAddress, sizeof( Int64 ), nullIndicatorOrActualLength );
        }
        Result Bind( SQLUSMALLINT columnNumber, UInt64* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::UInt64, targetAddress, sizeof( UInt64 ), nullIndicatorOrActualLength = nullptr );
        }
        Result Bind( SQLUSMALLINT columnNumber, Int32* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Int32, targetAddress, sizeof( Int32 ), nullIndicatorOrActualLength );
        }
        Result Bind( SQLUSMALLINT columnNumber, UInt32* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::UInt32, targetAddress, sizeof( UInt32 ), nullIndicatorOrActualLength );
        }
        Result Bind( SQLUSMALLINT columnNumber, Int16* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Int16, targetAddress, sizeof( Int16 ), nullIndicatorOrActualLength );
        }
        Result Bind( SQLUSMALLINT columnNumber, UInt16* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::UInt16, targetAddress, sizeof( UInt16 ), nullIndicatorOrActualLength );
        }
        Result Bind( SQLUSMALLINT columnNumber, SByte* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::SByte, targetAddress, sizeof( SByte ), nullIndicatorOrActualLength );
        }
        Result Bind( SQLUSMALLINT columnNumber, Byte* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Byte, targetAddress, sizeof( Byte ), nullIndicatorOrActualLength );
        }
        Result Bind( SQLUSMALLINT columnNumber, Guid* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::Guid, targetAddress, sizeof( Guid ), nullIndicatorOrActualLength );
        }
        Result Bind( SQLUSMALLINT columnNumber, ODBC::TimeStamp* targetAddress, SQLLEN* nullIndicatorOrActualLength = nullptr ) const
        {
            return BindColumn( columnNumber, NativeType::TimeStamp, targetAddress, sizeof( ODBC::TimeStamp ), nullIndicatorOrActualLength );
        }
    };


    class Statement : public SqlHandle<ODBC::HandleType::Statement>
    {
        friend class Connection;
    public:
        using Base = SqlHandle<ODBC::HandleType::Statement>;

        Statement( )
            : Base( )
        {
        }
    private:
        Statement( SQLHANDLE sqlHandle )
            : Base( sqlHandle )
        {
        }
    public:
        Result BindColumn( SQLUSMALLINT columnNumber, SQLSMALLINT targetType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrLength ) const
        {
            auto rc = SQLBindCol( Handle( ), columnNumber, targetType, targetValue, targetValueMaxLength, nullIndicatorOrLength );
            if ( rc < SQL_SUCCESS )
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
            return BindColumn( columnNumber, NativeType::TimeStamp, targetAddress, sizeof( ODBC::TimeStamp ), nullIndicatorOrActualLength );
        }


        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, SQLSMALLINT valueType, SQLSMALLINT parameterType, SQLULEN columnSize, SQLSMALLINT decimalDigits, SQLPOINTER parameterValue, SQLLEN parameterValueBufferLength, SQLLEN* lengthOrIndicator ) const
        {
            auto rc = SQLBindParameter( Handle( ), parameterNumber, static_cast<SQLSMALLINT>( parameterDirection ), valueType, parameterType, columnSize, decimalDigits, parameterValue, parameterValueBufferLength, lengthOrIndicator );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
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

        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Double* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Double, SqlType::Double, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindBooleanParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Byte* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Boolean, SqlType::Bit, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Int64* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Int64, SqlType::BigInt, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, UInt64* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::UInt64, SqlType::BigInt, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Int32* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Int32, SqlType::Integer, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, UInt32* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::UInt32, SqlType::Integer, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Int16* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Int16, SqlType::SmallInt, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, UInt16* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::UInt16, SqlType::SmallInt, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, SByte* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::SByte, SqlType::TinyInt, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }
        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Byte* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Byte, SqlType::TinyInt, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }
        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, Guid* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::Guid, SqlType::Guid, 0, 0, parameterValue, 0, lengthOrIndicator );
            return rc;
        }

        Result BindParameter( SQLUSMALLINT parameterNumber, ODBC::ParameterDirection parameterDirection, SQLSMALLINT precisionOfFraction, ODBC::TimeStamp* parameterValue, SQLLEN* lengthOrIndicator = nullptr ) const
        {
            SQLSMALLINT columnSize = static_cast<SQLSMALLINT>( 20 ) + precisionOfFraction;
            auto rc = BindParameter( parameterNumber, parameterDirection, NativeType::TimeStamp, SqlType::TimeStamp, columnSize, precisionOfFraction, parameterValue, 0, lengthOrIndicator );
            return rc;
        }


        Result BulkOperations( ODBC::BulkOperation bulkOperation ) const
        {
            auto rc = SQLBulkOperations( Handle( ), static_cast<SQLSMALLINT>( bulkOperation ) );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result CloseCursor( )
        {
            auto rc = SQLCloseCursor( Handle( ) );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        Result ColumnAttribute( SQLUSMALLINT columnNumber, SQLUSMALLINT fieldIdentifier, SQLPOINTER value, SQLSMALLINT valueMaxLength, SQLSMALLINT* valueActualLength, SQLLEN* numericAttributeValue ) const
        {
            auto rc = SQLColAttributeW( Handle( ), columnNumber, fieldIdentifier, value, valueMaxLength, valueActualLength, numericAttributeValue );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        Result ColumnPrivileges( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameMaxLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameMaxLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameMaxLength, const SQLWCHAR* columnName, SQLSMALLINT columnNameMaxLength ) const
        {
            auto rc = SQLColumnPrivilegesW( Handle( ), const_cast<SQLWCHAR*>(catalogName), catalogNameMaxLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameMaxLength, const_cast<SQLWCHAR*>( tableName ), tableNameMaxLength, const_cast<SQLWCHAR*>( columnName ), columnNameMaxLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result ColumnPrivileges( const SQLCHAR* catalogName, SQLSMALLINT catalogNameMaxLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameMaxLength, const SQLCHAR* tableName, SQLSMALLINT tableNameMaxLength, const SQLCHAR* columnName, SQLSMALLINT columnNameMaxLength ) const
        {
            auto rc = SQLColumnPrivilegesA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameMaxLength, const_cast<SQLCHAR*>( schemaName ), schemaNameMaxLength, const_cast<SQLCHAR*>( tableName ), tableNameMaxLength, const_cast<SQLCHAR*>( columnName ), columnNameMaxLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Columns( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameMaxLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameMaxLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameMaxLength, const SQLWCHAR* columnName, SQLSMALLINT columnNameMaxLength ) const
        {
            auto rc = SQLColumnsW( Handle( ), const_cast<SQLWCHAR*>( catalogName ), catalogNameMaxLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameMaxLength, const_cast<SQLWCHAR*>( tableName ), tableNameMaxLength, const_cast<SQLWCHAR*>( columnName ), columnNameMaxLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result Columns( const SQLCHAR* catalogName, SQLSMALLINT catalogNameMaxLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameMaxLength, const SQLCHAR* tableName, SQLSMALLINT tableNameMaxLength, const SQLCHAR* columnName, SQLSMALLINT columnNameMaxLength ) const
        {
            auto rc = SQLColumnsA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameMaxLength, const_cast<SQLCHAR*>( schemaName ), schemaNameMaxLength, const_cast<SQLCHAR*>( tableName ), tableNameMaxLength, const_cast<SQLCHAR*>( columnName ), columnNameMaxLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result DescribeColumn( SQLUSMALLINT columnNumber, SQLWCHAR* columnName, SQLSMALLINT columnNameMaxLength, SQLSMALLINT* columnNameActualLength, SQLSMALLINT* dataType, SQLULEN* columnSize, SQLSMALLINT* decimalDigits, ODBC::Nullable* nullable ) const
        {
            auto rc = SQLDescribeColW( Handle( ), columnNumber, columnName, columnNameMaxLength, columnNameActualLength, dataType, columnSize, decimalDigits, (SQLSMALLINT*)nullable );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result DescribeColumn( SQLUSMALLINT columnNumber, SQLCHAR* columnName, SQLSMALLINT columnNameMaxLength, SQLSMALLINT* columnNameActualLength, SQLSMALLINT* dataType, SQLULEN* columnSize, SQLSMALLINT* decimalDigits, ODBC::Nullable* nullable ) const
        {
            auto rc = SQLDescribeColA( Handle( ), columnNumber, columnName, columnNameMaxLength, columnNameActualLength, dataType, columnSize, decimalDigits, (SQLSMALLINT*)nullable );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result DescribeParameter( SQLUSMALLINT parameterNumber, SQLSMALLINT* dataType, SQLULEN *parameterSize, SQLSMALLINT* decimalDigits, ODBC::Nullable* nullable ) const
        {
            auto rc = SQLDescribeParam( Handle( ), parameterNumber, dataType, parameterSize, decimalDigits, (SQLSMALLINT*)nullable );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result ExecDirect( const SQLWCHAR* statementText, SQLINTEGER statementTextLength = SQL_NTS ) const
        {
            auto rc = SQLExecDirectW( Handle( ), const_cast<SQLWCHAR*>( statementText ), statementTextLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result ExecDirect( const SQLCHAR* statementText, SQLINTEGER statementTextLength = SQL_NTS ) const
        {
            auto rc = SQLExecDirectA( Handle( ), const_cast<SQLCHAR*>( statementText ), statementTextLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Execute( ) const
        {
            auto rc = SQLExecute( Handle( ) );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        template<typename ReaderType>
        requires std::is_base_of_v<DataReaderBase, ReaderType>
            std::unique_ptr<ReaderType> CreateReader( ) const
        {
            auto result = std::make_unique<ReaderType>( this );
            return result;
        }


        template<typename ReaderType>
        requires std::is_base_of_v<DataReaderBase, ReaderType>
            std::unique_ptr<ReaderType> ExecuteReader( ) const
        {
            auto result = CreateReader<ReaderType>( );
            Execute( );
            return result;
        }
        template<typename ReaderType>
        requires std::is_base_of_v<DataReaderBase, ReaderType>
            std::unique_ptr<ReaderType> ExecuteReader( const SQLWCHAR* statementText, SQLINTEGER statementTextLength = SQL_NTS ) const
        {
            auto result = CreateReader<ReaderType>( );
            ExecDirect( statementText, statementTextLength );
            return result;
        }
        template<typename ReaderType>
        requires std::is_base_of_v<DataReaderBase, ReaderType>
            std::unique_ptr<ReaderType> ExecuteReader( const SQLCHAR* statementText, SQLINTEGER statementTextLength = SQL_NTS ) const
        {
            auto result = CreateReader<ReaderType>( );
            ExecDirect( statementText, statementTextLength );
            return result;
        }



        Result Fetch( ) const
        {
            auto rc = SQLFetch( Handle( ) );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result FetchScroll( ODBC::Fetch fetchOrientation, SQLLEN fetchOffset ) const
        {
            auto rc = SQLFetchScroll( Handle( ), static_cast<SQLSMALLINT>( fetchOrientation ), fetchOffset );
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

    private:
        Result FreeStmt( SQLUSMALLINT option ) const
        {
            auto rc = SQLFreeStmt( Handle( ), option );
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result CursorName( SQLCHAR* cursorName, SQLSMALLINT cursorNameMaxLength, SQLSMALLINT* cursorNameActualLength ) const
        {
            auto rc = SQLGetCursorNameA( Handle( ), cursorName, cursorNameMaxLength, cursorNameActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result GetData( SQLUSMALLINT columnOrParameterNumber, SQLSMALLINT targetValueDataType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrTargetValueActualLength ) const
        {
            auto rc = SQLGetData( Handle( ), columnOrParameterNumber, targetValueDataType, targetValue, targetValueMaxLength, nullIndicatorOrTargetValueActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        bool GetBoolean( SQLUSMALLINT columnOrParameterNumber ) const
        {
            Byte value = 0;
            SQLLEN nullIndicator = 0;
            GetData( columnOrParameterNumber, NativeType::Boolean, &value, sizeof( value ), &nullIndicator );
            if ( nullIndicator != SQL_NULL_DATA )
            {
                return value != SQL_FALSE;
            }
        }




        Result GetAttributeW( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueBufferLength, SQLINTEGER* valueActualLength ) const
        {
            auto rc = SQLGetStmtAttrW( Handle( ), attributeId, value, valueBufferLength, valueActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result GetAttributeA( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueBufferLength, SQLINTEGER* valueActualLength ) const
        {
            auto rc = SQLGetStmtAttrA( Handle( ), attributeId, value, valueBufferLength, valueActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SetAttributeW( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueLength ) const
        {
            auto rc = SQLSetStmtAttrW( Handle( ), attributeId, value, valueLength );
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
#ifdef SQLSetStmtAttrUndeffed
#pragma pop_macro("SQLSetStmtAttr")
#endif
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
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result GetTypeInfoA( SQLSMALLINT dataType ) const
        {
            auto rc = SQLGetTypeInfoA( Handle( ), dataType );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result MoreResults( ) const
        {
            auto rc = SQLMoreResults( Handle( ) );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result NumParams( SQLSMALLINT* result ) const
        {
            auto rc = SQLNumParams( Handle( ), result );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result NumResultCols( SQLSMALLINT* result ) const
        {
            auto rc = SQLNumResultCols( Handle( ), result );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result ParamData( SQLPOINTER* valuePointer ) const
        {
            auto rc = SQLParamData( Handle( ), valuePointer );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Prepare( const SQLWCHAR* statement, SQLINTEGER statementLength = SQL_NTS ) const
        {
            auto rc = SQLPrepareW( Handle( ), const_cast<SQLWCHAR*>( statement ), statementLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Prepare( const SQLCHAR* statement, SQLINTEGER statementLength = SQL_NTS ) const
        {
            auto rc = SQLPrepareA( Handle( ), const_cast<SQLCHAR*>( statement ), statementLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        Result PrimaryKeys( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameLength ) const
        {
            auto rc = SQLPrimaryKeysW( Handle( ), const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( tableName ), tableNameLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result PrimaryKeys( const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* tableName, SQLSMALLINT tableNameLength ) const
        {
            auto rc = SQLPrimaryKeysA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( tableName ), tableNameLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result ProcedureColumns( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* procedureName, SQLSMALLINT procedureNameLength, const SQLWCHAR* columnName, SQLSMALLINT columnNameLength ) const
        {
            auto rc = SQLProcedureColumnsW( Handle( ), const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( procedureName ), procedureNameLength, const_cast<SQLWCHAR*>( columnName ), columnNameLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result ProcedureColumns( const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* procedureName, SQLSMALLINT procedureNameLength, const SQLCHAR* columnName, SQLSMALLINT columnNameLength ) const
        {
            auto rc = SQLProcedureColumnsA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( procedureName ), procedureNameLength, const_cast<SQLCHAR*>( columnName ), columnNameLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Procedures( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* procedureName, SQLSMALLINT procedureNameLength ) const
        {
            auto rc = SQLProceduresW( Handle(), const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( procedureName ), procedureNameLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result Procedures( const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* procedureName, SQLSMALLINT procedureNameLength ) const
        {
            auto rc = SQLProceduresA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( procedureName ), procedureNameLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result PutData( SQLPOINTER data, SQLLEN nullIndicatorOrDataLength ) const
        {
            auto rc = SQLPutData( Handle(), data, nullIndicatorOrDataLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        Result RowCount( SQLLEN* result ) const
        {
            auto rc = SQLRowCount( Handle( ), result );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SetCursorName( const SQLWCHAR* cursorName, SQLSMALLINT cursorNameLength ) const
        {
            auto rc = SQLSetCursorNameW( Handle( ), const_cast<SQLWCHAR*>( cursorName ), cursorNameLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SetCursorName( const SQLCHAR* cursorName, SQLSMALLINT cursorNameLength ) const
        {
            auto rc = SQLSetCursorNameA( Handle( ), const_cast<SQLCHAR*>( cursorName ), cursorNameLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SetPosition( SQLSETPOSIROW rowNumber, SQLUSMALLINT operation, SQLUSMALLINT lockType ) const
        {
            auto rc = SQLSetPos( Handle( ), rowNumber, operation, lockType );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SpecialColumns( SQLSMALLINT identifierType, const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameLength, SQLSMALLINT scope, SQLSMALLINT nullable ) const
        {
            auto rc = SQLSpecialColumnsW( Handle( ), identifierType, const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( tableName ), tableNameLength, scope, nullable );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result SpecialColumns( SQLSMALLINT identifierType, const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* tableName, SQLSMALLINT tableNameLength, SQLSMALLINT scope, SQLSMALLINT nullable ) const
        {
            auto rc = SQLSpecialColumnsA( Handle( ), identifierType, const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( tableName ), tableNameLength, scope, nullable );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Statistics( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameLength, SQLSMALLINT unique, SQLSMALLINT options ) const
        {
            auto rc = SQLStatisticsW( Handle( ), const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( tableName ), tableNameLength, unique, options );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result Statistics( const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* tableName, SQLSMALLINT tableNameLength, SQLSMALLINT unique, SQLSMALLINT options ) const
        {
            auto rc = SQLStatisticsA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( tableName ), tableNameLength, unique, options );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result TablePrivileges( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameLength ) const
        {
            auto rc = SQLTablePrivilegesW( Handle( ), const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( tableName ), tableNameLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result TablePrivileges( const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* tableName, SQLSMALLINT tableNameLength ) const
        {
            auto rc = SQLTablePrivilegesA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( tableName ), tableNameLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Tables( const SQLWCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLWCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLWCHAR* tableName, SQLSMALLINT tableNameLength, const SQLWCHAR* tableTypes, SQLSMALLINT tableTypesLength ) const
        {
            auto rc = SQLTablesW( Handle( ), const_cast<SQLWCHAR*>( catalogName ), catalogNameLength, const_cast<SQLWCHAR*>( schemaName ), schemaNameLength, const_cast<SQLWCHAR*>( tableName ), tableNameLength, const_cast<SQLWCHAR*>( tableTypes ), tableTypesLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result Tables( const SQLCHAR* catalogName, SQLSMALLINT catalogNameLength, const SQLCHAR* schemaName, SQLSMALLINT schemaNameLength, const SQLCHAR* tableName, SQLSMALLINT tableNameLength, const SQLCHAR* tableTypes, SQLSMALLINT tableTypesLength ) const
        {
            auto rc = SQLTablesA( Handle( ), const_cast<SQLCHAR*>( catalogName ), catalogNameLength, const_cast<SQLCHAR*>( schemaName ), schemaNameLength, const_cast<SQLCHAR*>( tableName ), tableNameLength, const_cast<SQLCHAR*>( tableTypes ), tableTypesLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
    };



    inline Result DataReaderBase::Fetch( ) const
    {
        return statement_->Fetch( );
    }
    inline Result DataReaderBase::FetchScroll( ODBC::Fetch fetchOrientation, SQLLEN fetchOffset ) const
    {
        return statement_->FetchScroll( fetchOrientation, fetchOffset );
    }
    inline Result DataReaderBase::BindColumn( SQLUSMALLINT columnNumber, SQLSMALLINT targetType, SQLPOINTER targetValue, SQLLEN targetValueMaxLength, SQLLEN* nullIndicatorOrLength ) const
    {
        return statement_->BindColumn( columnNumber, targetType, targetValue, targetValueMaxLength, nullIndicatorOrLength );
    }




    class Connection : public SqlHandle<ODBC::HandleType::Connection>
    {
        friend class Environment;
    public:
        using Base = SqlHandle<ODBC::HandleType::Connection>;

        constexpr Connection( ) noexcept
            : Base( )
        {
        }
    private:
        constexpr Connection( SQLHANDLE sqlHandle ) noexcept
            : Base( sqlHandle )
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
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result Connect( const WideString& datasourceName )
        {
            return Connect( datasourceName.c_str(), static_cast<SQLSMALLINT>( datasourceName.length() ), nullptr, 0, nullptr, 0 );
        }

        Result Connect( const WideString& datasourceName, const WideString& userName )
        {
            return Connect( datasourceName.c_str( ), static_cast<SQLSMALLINT>( datasourceName.length( ) ), userName.c_str(), static_cast<SQLSMALLINT>( userName.length( ) ), nullptr, 0 );
        }

        Result Connect( const WideString& datasourceName, const WideString& userName, const WideString& authenticationString )
        {
            return Connect( datasourceName.c_str( ), static_cast<SQLSMALLINT>( datasourceName.length( ) ), userName.c_str( ), static_cast<SQLSMALLINT>( userName.length( ) ), authenticationString.c_str( ), static_cast<SQLSMALLINT>( authenticationString.length( ) ) );
        }



        Result Connect( const SQLCHAR* datasourceName, SQLSMALLINT datasourceNameLength, const SQLCHAR* userName, SQLSMALLINT userNameLength, const SQLCHAR* authenticationString, SQLSMALLINT authenticationStringLength ) const
        {
            auto rc = SQLConnectA( Handle( ), const_cast<SQLCHAR*>( datasourceName ), datasourceNameLength, const_cast<SQLCHAR*>( userName ), userNameLength, const_cast<SQLCHAR*>( authenticationString ), authenticationStringLength );
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result DriverConnect( SQLHWND windowHandle, const SQLWCHAR* initialConnectionString, SQLSMALLINT initialConnectionStringLength, SQLWCHAR* resultConnectionString, SQLSMALLINT resultConnectionStringMaxLength, SQLSMALLINT* resultConnectionStringActualLength, ODBC::DriverCompletion driverCompletion ) const
        {
            auto rc = SQLDriverConnectW( Handle( ), windowHandle, const_cast<SQLWCHAR*>( initialConnectionString ), initialConnectionStringLength, resultConnectionString, resultConnectionStringMaxLength, resultConnectionStringActualLength, static_cast<SQLSMALLINT>( driverCompletion ) );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result DriverConnect( SQLHWND windowHandle, const SQLCHAR* initialConnectionString, SQLSMALLINT initialConnectionStringLength, SQLCHAR* resultConnectionString, SQLSMALLINT resultConnectionStringMaxLength, SQLSMALLINT* resultConnectionStringActualLength, ODBC::DriverCompletion driverCompletion ) const
        {
            auto rc = SQLDriverConnectA( Handle( ), windowHandle, const_cast<SQLCHAR*>( initialConnectionString ), initialConnectionStringLength, resultConnectionString, resultConnectionStringMaxLength, resultConnectionStringActualLength, static_cast<SQLSMALLINT>( driverCompletion ) );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result EndTransaction( ODBC::TransactionCompletionType completionType ) const
        {
            auto rc = SQLEndTran( static_cast<SQLSMALLINT>( Base::HandleType ), Handle( ), static_cast<SQLSMALLINT>( completionType ) );
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result SetAttributeW( SQLINTEGER attributeId, SQLPOINTER value, SQLINTEGER valueLength ) const
        {
            auto rc = SQLSetConnectAttrW( Handle( ), attributeId, value, valueLength );
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result GetInfoW( SQLUSMALLINT infoType, SQLPOINTER infoValue, SQLSMALLINT infoValueMaxLength, SQLSMALLINT* infoValueActualLength ) const
        {
            auto rc = SQLGetInfoW( Handle( ), infoType, infoValue, infoValueMaxLength, infoValueActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result GetInfoA( SQLUSMALLINT infoType, SQLPOINTER infoValue, SQLSMALLINT infoValueMaxLength, SQLSMALLINT* infoValueActualLength ) const
        {
            auto rc = SQLGetInfoA( Handle( ), infoType, infoValue, infoValueMaxLength, infoValueActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        Result NativeSql( const SQLWCHAR* inStatement, SQLINTEGER inStatementLength, SQLWCHAR* outStatement, SQLINTEGER outStatementMaxLength, SQLINTEGER* outStatementActualLength ) const
        {
            auto rc = SQLNativeSqlW( Handle( ), const_cast<SQLWCHAR*>( inStatement ), inStatementLength, outStatement, outStatementMaxLength, outStatementActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }
        Result NativeSql( const SQLCHAR* inStatement, SQLINTEGER inStatementLength, SQLCHAR* outStatement, SQLINTEGER outStatementMaxLength, SQLINTEGER* outStatementActualLength ) const
        {
            auto rc = SQLNativeSqlA( Handle( ), const_cast<SQLCHAR*>( inStatement ), inStatementLength, outStatement, outStatementMaxLength, outStatementActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }






    };


    class Environment : public SqlHandle<ODBC::HandleType::Environment>
    {
    public:
        using Base = SqlHandle<ODBC::HandleType::Environment>;

        constexpr Environment( ) noexcept
            : Base( )
        {
        }
    private:
        constexpr Environment( SQLHANDLE sqlHandle ) noexcept
            : Base( sqlHandle )
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
            SetAttribute( attributeId, (SQLPOINTER) static_cast<size_t>( value ), 0 );
        }

        UInt32 GetUInt32Attribute( SQLINTEGER attributeId ) const
        {
            SQLINTEGER valueLength;
            UInt32 result = 0;
            GetAttribute( attributeId, &result, sizeof( UInt32 ), &valueLength );
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

        Result DataSources( ODBC::Fetch direction, SQLWCHAR* datasourceName, SQLSMALLINT datasourceNameMaxLength, SQLSMALLINT *datasourceNameActualLength, SQLWCHAR* datasourceDescription, SQLSMALLINT datasourceDescriptionMaxLength, SQLSMALLINT* datasourceDescriptionActualLength ) const
        {
            auto rc = SQLDataSourcesW( Handle( ), static_cast<SQLUSMALLINT>( direction ), datasourceName, datasourceNameMaxLength, datasourceNameActualLength, datasourceDescription, datasourceDescriptionMaxLength, datasourceDescriptionActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }

        Result DataSources( ODBC::Fetch direction, SQLCHAR* datasourceName, SQLSMALLINT datasourceNameMaxLength, SQLSMALLINT* datasourceNameActualLength, SQLCHAR* datasourceDescription, SQLSMALLINT datasourceDescriptionMaxLength, SQLSMALLINT* datasourceDescriptionActualLength ) const
        {
            auto rc = SQLDataSourcesA( Handle( ), static_cast<SQLUSMALLINT>( direction ), datasourceName, datasourceNameMaxLength, datasourceNameActualLength, datasourceDescription, datasourceDescriptionMaxLength, datasourceDescriptionActualLength );
            if ( rc < SQL_SUCCESS )
            {
                ThrowException( rc, CURRENT_FUNCTION, CURRENT_FILE, __LINE__ );
            }
            return static_cast<Result>( rc );
        }


        std::vector<ODBC::DataSource> DataSources( ODBC::Fetch direction )
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
            if ( rc < SQL_SUCCESS )
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
            if ( rc < SQL_SUCCESS )
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
