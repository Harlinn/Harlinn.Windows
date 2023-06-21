#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    void DateTimeAssign( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* from, OCIDateTime* to )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeAssign( handle.Handle( ), errorHandle, from, to );
        error.CheckResult( rc );
    }
    void DateTimeCheck( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* date, DateTimeErrorFlag* errors )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeCheck( handle.Handle( ), errorHandle, date, (UInt32*)errors );
        error.CheckResult( rc );
    }
    void DateTimeCompare( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* date1, const OCIDateTime* date2, Int32* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeCompare( handle.Handle( ), errorHandle, date1, date2, result );
        error.CheckResult( rc );
    }
    void DateTimeConstruct( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* datetime, Int16 year, Byte month, Byte day, Byte hour, Byte min, Byte sec, UInt32 fsec, wchar_t* timezone, size_t timezoneLength )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeConstruct( handle.Handle( ), errorHandle, datetime, year, month, day, hour, min, sec, fsec, (OraText*)timezone, timezoneLength );
        error.CheckResult( rc );
    }

    void DateTimeConstruct( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* datetime, const Common::Core::DateTime& source )
    {
        Int32 year, month, day;
        source.GetYearMonthDay( year, month, day );
        auto hour = static_cast<Byte>( source.Hour( ) );
        auto min = static_cast<Byte>( source.Minute( ) );
        auto sec = static_cast<Byte>( source.Second( ) );
        UInt32 fractional = static_cast<UInt32>( ( source.Ticks( ) % DateTime::TicksPerSecond ) * 100 );

        DateTimeConstruct( handle, error, datetime, static_cast<Int16>( year ), static_cast<Byte>( month ), static_cast<Byte>( day ), hour, min, sec, fractional, nullptr, 0 );
    }


    void DateTimeConvert( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* indate, OCIDateTime* outdate )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeConvert( handle.Handle( ), errorHandle, indate, outdate );
        error.CheckResult( rc );
    }
    void DateTimeFromArray( const OCI::HandleBase& handle, const ErrorHandle& error, const Byte* inarray, UInt32 len, Byte type, OCIDateTime* datetime, const OCIInterval* reftz, Byte fsprec )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeFromArray( handle.Handle( ), errorHandle, (Byte*)inarray, len, type, datetime, reftz, fsprec );
        error.CheckResult( rc );
    }
    void DateTimeFromText( const OCI::HandleBase& handle, const ErrorHandle& error, const wchar_t* date_str, size_t dstr_length, const wchar_t* fmt, Byte fmt_length, const wchar_t* lang_name, size_t lang_length, OCIDateTime* datetime )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeFromText( handle.Handle( ), errorHandle, (const OraText*)date_str, dstr_length, (OraText*)fmt, fmt_length, (OraText*)lang_name, lang_length, datetime );
        error.CheckResult( rc );
    }
    void DateTimeGetDate( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* datetime, Int16* year, Byte* month, Byte* day )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeGetDate( handle.Handle( ), errorHandle, datetime, year, month, day );
        error.CheckResult( rc );
    }
    void DateTimeGetTime( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* datetime, Byte* hour, Byte* min, Byte* sec, UInt32* fsec )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeGetTime( handle.Handle( ), errorHandle, datetime, hour, min, sec, fsec );
        error.CheckResult( rc );
    }

    void DateTimeGetDateTime( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* source, DateTime& target )
    {
        Int16 year;
        Byte month, day, hour, min, sec;
        UInt32 fractional;

        DateTimeGetDate( handle, error, source, &year, &month, &day );
        DateTimeGetTime( handle, error, source, &hour, &min, &sec, &fractional );

        auto ticks = TimeSpan( fractional / 100 );
        target = DateTime( year, month, day, hour, min, sec ) + ticks;
    }

    void DateTimeGetTimeZoneName( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* datetime, wchar_t* buf, UInt32* buflen )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeGetTimeZoneName( handle.Handle( ), errorHandle, datetime, (OraText*)buf, buflen );
        error.CheckResult( rc );
    }
    void DateTimeGetTimeZoneOffset( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* datetime, char* hour, char* min )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeGetTimeZoneOffset( handle.Handle( ), errorHandle, datetime, (sb1*)hour, (sb1*)min );
        error.CheckResult( rc );
    }
    void DateTimeIntervalAdd( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* datetime, OCIInterval* inter, OCIDateTime* outdatetime )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeIntervalAdd( handle.Handle( ), errorHandle, datetime, inter, outdatetime );
        error.CheckResult( rc );
    }
    void DateTimeIntervalSub( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* datetime, OCIInterval* inter, OCIDateTime* outdatetime )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeIntervalSub( handle.Handle( ), errorHandle, datetime, inter, outdatetime );
        error.CheckResult( rc );
    }
    void DateTimeSubtract( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* indate1, OCIDateTime* indate2, OCIInterval* inter )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeSubtract( handle.Handle( ), errorHandle, indate1, indate2, inter );
        error.CheckResult( rc );
    }
    void DateTimeSysTimeStamp( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* sys_date )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeSysTimeStamp( handle.Handle( ), errorHandle, sys_date );
        error.CheckResult( rc );
    }
    void DateTimeToArray( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* datetime, const OCIInterval* reftz, Byte* outarray, UInt32* len, Byte fsprec )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeToArray( handle.Handle( ), errorHandle, datetime, reftz, outarray, len, fsprec );
        error.CheckResult( rc );
    }
    void DateTimeToText( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* date, const wchar_t* fmt, Byte fmt_length, Byte fsprec, const wchar_t* lang_name, size_t lang_length, UInt32* buf_size, wchar_t* buf )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateTimeToText( handle.Handle( ), errorHandle, date, (OraText*)fmt, fmt_length, fsprec, (OraText*)lang_name, lang_length, buf_size, (OraText*)buf );
        error.CheckResult( rc );
    }

    WideString DateTimeToText( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* date, const wchar_t* fmt, Byte fmt_length, Byte fsprec, const wchar_t* lang_name, size_t lang_length )
    {
        wchar_t buffer[512];
        UInt32 bufferSize = sizeof( buffer );
        DateTimeToText( handle, error, date, fmt, fmt_length, fsprec, lang_name, lang_length, &bufferSize, buffer );
        return WideString( buffer, bufferSize / sizeof( wchar_t ) );
    }

    void IntervalSubtract( const OCI::HandleBase& handle, const ErrorHandle& error, OCIInterval* minuend, OCIInterval* subtrahend, OCIInterval* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalSubtract( handle.Handle( ), errorHandle, minuend, subtrahend, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }

    void IntervalAdd( const OCI::HandleBase& handle, const ErrorHandle& error, OCIInterval* addend1, OCIInterval* addend2, OCIInterval* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalAdd( handle.Handle( ), errorHandle, addend1, addend2, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }

    void IntervalMultiply( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIInterval* inter, OCI::Number* nfactor, OCIInterval* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalMultiply( handle.Handle( ), errorHandle, inter, (OCINumber*)nfactor, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }

    void IntervalDivide( const OCI::HandleBase& handle, const ErrorHandle& error, OCIInterval* dividend, OCI::Number* divisor, OCIInterval* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalDivide( handle.Handle( ), errorHandle, dividend, (OCINumber*)divisor, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }

    void IntervalCompare( const OCI::HandleBase& handle, const ErrorHandle& error, OCIInterval* inter1, OCIInterval* inter2, Int32* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalCompare( handle.Handle( ), errorHandle, inter1, inter2, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void IntervalFromNumber( const OCI::HandleBase& handle, const ErrorHandle& error, OCIInterval* inter, OCI::Number* number )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalFromNumber( handle.Handle( ), errorHandle, inter, (OCINumber*)number );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void IntervalFromText( const OCI::HandleBase& handle, const ErrorHandle& error, const wchar_t* inpstr, size_t str_len, OCIInterval* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalFromText( handle.Handle( ), errorHandle, (const OraText*)inpstr, str_len, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void IntervalToText( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIInterval* inter, Byte lfprec, Byte fsprec, wchar_t* buffer, size_t buflen, size_t* resultlen )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalToText( handle.Handle( ), errorHandle, inter, lfprec, fsprec, (OraText*)buffer, buflen, resultlen );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void IntervalToNumber( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIInterval* inter, OCI::Number* number )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalToNumber( handle.Handle( ), errorHandle, inter, (OCINumber*)number );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void IntervalCheck( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIInterval* interval, UInt32* valid )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalCheck( handle.Handle( ), errorHandle, interval, valid );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void IntervalAssign( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIInterval* ininter, OCIInterval* outinter )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalAssign( handle.Handle( ), errorHandle, ininter, outinter );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void IntervalSetYearMonth( const OCI::HandleBase& handle, const ErrorHandle& error, Int32 yr, Int32 mnth, OCIInterval* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalSetYearMonth( handle.Handle( ), errorHandle, yr, mnth, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void IntervalGetYearMonth( const OCI::HandleBase& handle, const ErrorHandle& error, Int32* yr, Int32* mnth, const OCIInterval* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalGetYearMonth( handle.Handle( ), errorHandle, yr, mnth, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void IntervalSetDaySecond( const OCI::HandleBase& handle, const ErrorHandle& error, Int32 dy, Int32 hr, Int32 mm, Int32 ss, Int32 fsec, OCIInterval* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalSetDaySecond( handle.Handle( ), errorHandle, dy, hr, mm, ss, fsec, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void IntervalGetDaySecond( const OCI::HandleBase& handle, const ErrorHandle& error, Int32* dy, Int32* hr, Int32* mm, Int32* ss, Int32* fsec, const OCIInterval* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalGetDaySecond( handle.Handle( ), errorHandle, dy, hr, mm, ss, fsec, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void IntervalFromTZ( const OCI::HandleBase& handle, const ErrorHandle& error, const wchar_t* inpstring, size_t str_len, OCIInterval* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIntervalFromTZ( handle.Handle( ), errorHandle, (const oratext*)inpstring, str_len, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }


    // Collection and Iterator Functions
    void CollectionAppend( const Environment& environment, const ErrorHandle& error, const void* elem, const void* elemind, OCIColl* coll )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCICollAppend( environmentHandle, errorHandle, elem, elemind, coll );
        error.CheckResult( rc );
    }
    void CollectionAssign( const Environment& environment, const ErrorHandle& error, const OCIColl* rhs, OCIColl* lhs )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCICollAssign( environmentHandle, errorHandle, rhs, lhs );
        error.CheckResult( rc );
    }
    void CollectionAssignElement( const Environment& environment, const ErrorHandle& error, Int32 index, const void* elem, const void* elemind, OCIColl* coll )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCICollAssignElem( environmentHandle, errorHandle, index, elem, elemind, coll );
        error.CheckResult( rc );
    }
    void CollectionGetElement( const Environment& environment, const ErrorHandle& error, const OCIColl* coll, Int32 index, bool* exists, void** elem, void** elemind )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        boolean exsts = *exists ? TRUE : FALSE;
        auto rc = OCICollGetElem( environmentHandle, errorHandle, coll, static_cast<sb4>( index ), &exsts, elem, elemind );
        error.CheckResult( rc );
        *exists = exsts ? true : false;
    }
    void CollectionGetElementArray( const Environment& environment, const ErrorHandle& error, const OCIColl* coll, Int32 index, bool* exists, void** elem, void** elemind, UInt32* nelems )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        boolean exsts = *exists ? TRUE : FALSE;
        auto rc = OCICollGetElemArray( environmentHandle, errorHandle, coll, static_cast<sb4>( index ), &exsts, elem, elemind, nelems );
        error.CheckResult( rc );
        *exists = exsts ? true : false;
    }
    void CollectionIsLocator( const Environment& environment, const ErrorHandle& error, const OCIColl* coll, bool* result )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        boolean rslt = *result ? TRUE : FALSE;
        auto rc = OCICollIsLocator( environmentHandle, errorHandle, coll, &rslt );
        error.CheckResult( rc );
        *result = rslt ? true : false;
    }
    Int32 CollectionMax( const Environment& environment, const OCIColl* coll )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto result = OCICollMax( environmentHandle, coll );
        return result;
    }
    void CollectionSize( const Environment& environment, const ErrorHandle& error, const OCIColl* coll, Int32* size )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCICollSize( environmentHandle, errorHandle, coll, size );
        error.CheckResult( rc );
    }
    void CollectionTrim( const Environment& environment, const ErrorHandle& error, Int32 trim_num, OCIColl* coll )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCICollTrim( environmentHandle, errorHandle, trim_num, coll );
        error.CheckResult( rc );
    }

    void IteratorCreate( const Environment& environment, const ErrorHandle& error, const OCIColl* coll, OCIIter** itr )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIterCreate( environmentHandle, errorHandle, coll, itr );
        error.CheckResult( rc );
    }
    void IteratorDelete( const Environment& environment, const ErrorHandle& error, OCIIter** itr )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIterDelete( environmentHandle, errorHandle, itr );
        error.CheckResult( rc );
    }
    void IteratorGetCurrent( const Environment& environment, const ErrorHandle& error, const OCIIter* itr, void** elem, void** elemind )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIterGetCurrent( environmentHandle, errorHandle, itr, elem, elemind );
        error.CheckResult( rc );
    }
    void IteratorInit( const Environment& environment, const ErrorHandle& error, const OCIColl* coll, OCIIter* itr )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIIterInit( environmentHandle, errorHandle, coll, itr );
        error.CheckResult( rc );
    }
    void IteratorNext( const Environment& environment, const ErrorHandle& error, OCIIter* itr, void** elem, void** elemind, bool* eoc )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        boolean endOfCollection = *eoc ? TRUE : FALSE;
        auto rc = OCIIterNext( environmentHandle, errorHandle, itr, elem, elemind, &endOfCollection );
        error.CheckResult( rc );
        *eoc = endOfCollection ? true : false;
    }
    void IteratorPrev( const Environment& environment, const ErrorHandle& error, OCIIter* itr, void** elem, void** elemind, bool* boc )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        boolean startOfCollection = *boc ? TRUE : FALSE;
        auto rc = OCIIterPrev( environmentHandle, errorHandle, itr, elem, elemind, &startOfCollection );
        error.CheckResult( rc );
        *boc = startOfCollection ? true : false;
    }


    void RawAllocSize( const Environment& environment, const ErrorHandle& error, const OCIRaw* raw, UInt32* allocsize )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIRawAllocSize( environmentHandle, errorHandle, raw, allocsize );
        error.CheckResult( rc );
    }

    void RawAssignBytes( const Environment& environment, const ErrorHandle& error, const Byte* bytes, UInt32 bytesLength, OCIRaw** lhs )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIRawAssignBytes( environmentHandle, errorHandle, bytes, bytesLength, lhs );
        error.CheckResult( rc );
    }

    void RawAssignRaw( const Environment& environment, const ErrorHandle& error, const OCIRaw* rhs, OCIRaw** lhs )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIRawAssignRaw( environmentHandle, errorHandle, rhs, lhs );
        error.CheckResult( rc );
    }

    Byte* RawPtr( const Environment& environment, const OCIRaw* raw )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto result = OCIRawPtr( environmentHandle, raw );
        return result;
    }

    void RawResize( const Environment& environment, const ErrorHandle& error, UInt32 newSize, OCIRaw** raw )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIRawResize( environmentHandle, errorHandle, newSize, raw );
        error.CheckResult( rc );
    }

    UInt32 RawSize( const Environment& environment, const OCIRaw* raw )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto result = OCIRawSize( environmentHandle, raw );
        return result;
    }

    void RefAssign( const Environment& environment, const ErrorHandle& error, const OCIRef* source, OCIRef** target )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIRefAssign( environmentHandle, errorHandle, source, target );
        error.CheckResult( rc );
    }
    void RefClear( const Environment& environment, OCIRef* ref )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        OCIRefClear( environmentHandle, ref );
    }
    void RefFromHex( const Environment& environment, const ErrorHandle& error, const OCISvcCtx* svc, const wchar_t* hex, UInt32 length, OCIRef** ref )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIRefFromHex( environmentHandle, errorHandle, svc, (const oratext*)hex, length, ref );
        error.CheckResult( rc );
    }
    UInt32 RefHexSize( const Environment& environment, const OCIRef* ref )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto result = OCIRefHexSize( environmentHandle, ref );
        return result;
    }
    bool RefIsEqual( const Environment& environment, const OCIRef* x, const OCIRef* y )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto result = OCIRefIsEqual( environmentHandle, x, y );
        return result ? true : false;
    }
    bool RefIsNull( const Environment& environment, const OCIRef* ref )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto result = OCIRefIsNull( environmentHandle, ref );
        return result ? true : false;
    }

    void RefToHex( const Environment& environment, const ErrorHandle& error, const OCIRef* ref, wchar_t* hex, UInt32* hexLength )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIRefToHex( environmentHandle, errorHandle, ref, (oratext*)hex, hexLength );
        error.CheckResult( rc );
    }

    void StringAllocSize( const Environment& environment, const ErrorHandle& error, const OCIString* vs, UInt32* allocsize )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIStringAllocSize( environmentHandle, errorHandle, vs, allocsize );
        error.CheckResult( rc );
    }
    void StringAssign( const Environment& environment, const ErrorHandle& error, const OCIString* rhs, OCIString** lhs )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIStringAssign( environmentHandle, errorHandle, rhs, lhs );
        error.CheckResult( rc );
    }
    void StringAssignText( const Environment& environment, const ErrorHandle& error, const wchar_t* rhs, UInt32 rhs_len, OCIString** lhs )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIStringAssignText( environmentHandle, errorHandle, (const oratext*)rhs, rhs_len, lhs );
        error.CheckResult( rc );
    }
    wchar_t* StringPtr( const Environment& environment, const OCIString* vs )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto result = (wchar_t*)OCIStringPtr( environmentHandle, vs );
        return result;
    }
    void StringResize( const Environment& environment, const ErrorHandle& error, UInt32 newSize, OCIString** str )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIStringResize( environmentHandle, errorHandle, newSize, str );
        error.CheckResult( rc );
    }
    UInt32 StringSize( const Environment& environment, const OCIString* vs )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto result = OCIStringSize( environmentHandle, vs );
        return result;
    }

    void TableDelete( const Environment& environment, const ErrorHandle& error, Int32 index, OCITable* tbl )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCITableDelete( environmentHandle, errorHandle, index, tbl );
        error.CheckResult( rc );
    }
    bool TableExists( const Environment& environment, const ErrorHandle& error, const OCITable* tbl, Int32 index )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        boolean exists = FALSE;
        auto rc = OCITableExists( environmentHandle, errorHandle, tbl, index, &exists );
        error.CheckResult( rc );
        return exists ? true : false;
    }
    bool TableFirst( const Environment& environment, const ErrorHandle& error, const OCITable* tbl, Int32* index )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCITableFirst( environmentHandle, errorHandle, tbl, index );
        error.CheckResult( rc );
        return true;
    }
    bool TableLast( const Environment& environment, const ErrorHandle& error, const OCITable* tbl, Int32* index )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCITableLast( environmentHandle, errorHandle, tbl, index );
        error.CheckResult( rc );
        return true;
    }
    bool TableNext( const Environment& environment, const ErrorHandle& error, Int32 index, const OCITable* tbl, Int32* nextIndex )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        boolean exists = FALSE;
        auto rc = OCITableNext( environmentHandle, errorHandle, index, tbl, nextIndex, &exists );
        error.CheckResult( rc );
        return exists ? true : false;
    }
    bool TablePrev( const Environment& environment, const ErrorHandle& error, Int32 index, const OCITable* tbl, Int32* prevIndex )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        boolean exists = FALSE;
        auto rc = OCITablePrev( environmentHandle, errorHandle, index, tbl, prevIndex, &exists );
        error.CheckResult( rc );
        return exists ? true : false;
    }
    void TableSize( const Environment& environment, const ErrorHandle& error, const OCITable* tbl, Int32* size )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCITableSize( environmentHandle, errorHandle, tbl, size );
        error.CheckResult( rc );
    }


    void LobAssign( const Environment& environment, const ErrorHandle& error, const OCILobLocator* src_locp, OCILobLocator** dst_locpp )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobAssign( environmentHandle, errorHandle, src_locp, dst_locpp );
        error.CheckResult( rc );
    }
    void LobCharSetForm( const Environment& environment, const ErrorHandle& error, const OCILobLocator* locp, Byte* csfrm )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobCharSetForm( environmentHandle, errorHandle, locp, csfrm );
        error.CheckResult( rc );
    }
    void LobCharSetId( const Environment& environment, const ErrorHandle& error, const OCILobLocator* locp, UInt16* csid )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobCharSetId( environmentHandle, errorHandle, locp, csid );
        error.CheckResult( rc );
    }

    void LobFileSetName( const Environment& environment, const ErrorHandle& error, OCILobLocator** filepp, const wchar_t* dir_alias, UInt16 d_length, const wchar_t* filename, UInt16 f_length )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobFileSetName( environmentHandle, errorHandle, filepp, (OraText*)dir_alias, d_length, (const OraText*)filename, f_length );
        error.CheckResult( rc );
    }
    void LobIsEqual( const Environment& environment, const OCILobLocator* x, const OCILobLocator* y, bool* is_equal )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        boolean res = FALSE;
        OCILobIsEqual( environmentHandle, x, y, &res );
        *is_equal = res ? true : false;
    }
    void LobIsTemporary( const Environment& environment, const ErrorHandle& error, OCILobLocator* locp, bool* is_temporary )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        boolean res = FALSE;
        auto rc = OCILobIsTemporary( environmentHandle, errorHandle, locp, &res );
        error.CheckResult( rc );
        *is_temporary = res ? true : false;
    }
    void LobLocatorIsInit( const Environment& environment, const ErrorHandle& error, const OCILobLocator* locp, bool* is_initialized )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        boolean res = FALSE;
        auto rc = OCILobLocatorIsInit( environmentHandle, errorHandle, locp, &res );
        error.CheckResult( rc );
        *is_initialized = res ? true : false;
    }

    void LobFileGetName( const Environment& environment, const ErrorHandle& error, const OCILobLocator* filep, wchar_t* dir_alias, UInt16* d_length, wchar_t* filename, UInt16* f_length )
    {
        auto environmentHandle = (OCIEnv*)environment.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobFileGetName( environmentHandle, errorHandle, filep, (OraText*)dir_alias, d_length, (OraText*)filename, f_length );
        error.CheckResult( rc );
    }

    void NumberInc( const ErrorHandle& error, OCI::Number* number )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberInc( errorHandle, (OCINumber*)number );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberDec( const ErrorHandle& error, OCI::Number* number )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberDec( errorHandle, (OCINumber*)number );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberSetZero( const ErrorHandle& error, OCI::Number* num )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        OCINumberSetZero( errorHandle, (OCINumber*)num );
    }
    void NumberSetPi( const ErrorHandle& error, OCI::Number* num )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        OCINumberSetPi( errorHandle, (OCINumber*)num );
    }
    void NumberAdd( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberAdd( errorHandle, (OCINumber*)number1, (OCINumber*)number2, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberSub( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberSub( errorHandle, (OCINumber*)number1, (OCINumber*)number2, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberMul( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberMul( errorHandle, (OCINumber*)number1, (OCINumber*)number2, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberDiv( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberDiv( errorHandle, (OCINumber*)number1, (OCINumber*)number2, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberMod( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberMod( errorHandle, (OCINumber*)number1, (OCINumber*)number2, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberIntPower( const ErrorHandle& error, const OCI::Number* base, const Int32 exp, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberIntPower( errorHandle, (OCINumber*)base, exp, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberShift( const ErrorHandle& error, const OCI::Number* number, const Int32 nDig, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberShift( errorHandle, (OCINumber*)number, nDig, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberNeg( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberNeg( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberToText( const ErrorHandle& error, const OCI::Number* number, const wchar_t* fmt, UInt32 fmt_length, const wchar_t* nls_params, UInt32 nls_p_length, UInt32* buf_size, wchar_t* buf )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberToText( errorHandle, (OCINumber*)number, (const oratext*)fmt, fmt_length, (const oratext*)nls_params, nls_p_length, buf_size, (oratext*)buf );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberFromText( const ErrorHandle& error, const wchar_t* str, UInt32 str_length, const wchar_t* fmt, UInt32 fmt_length, const wchar_t* nls_params, UInt32 nls_p_length, OCI::Number* number )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberFromText( errorHandle, (const oratext*)str, str_length, (const oratext*)fmt, fmt_length, (const oratext*)nls_params, nls_p_length, (OCINumber*)number );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberToInt( const ErrorHandle& error, const OCI::Number* number, UInt32 rsl_length, NumberToIntFlags rsl_flag, void* rsl )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberToInt( errorHandle, (OCINumber*)number, rsl_length, static_cast<UInt32>(rsl_flag), rsl );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberFromInt( const ErrorHandle& error, const void* inum, UInt32 inum_length, NumberToIntFlags inum_s_flag, OCI::Number* number )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberFromInt( errorHandle, inum, inum_length, static_cast<UInt32>(inum_s_flag), (OCINumber*)number );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberToReal( const ErrorHandle& error, const OCI::Number* number, UInt32 rsl_length, void* rsl )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberToReal( errorHandle, (OCINumber*)number, rsl_length, rsl );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberToRealArray( const ErrorHandle& error, const OCI::Number** number, UInt32 elems, UInt32 rsl_length, void* rsl )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberToRealArray( errorHandle, (const OCINumber**)number, elems, rsl_length, rsl );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberFromReal( const ErrorHandle& error, const void* rnum, UInt32 rnum_length, OCI::Number* number )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberFromReal( errorHandle, rnum, rnum_length, (OCINumber*)number );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberCmp( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, Int32* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberCmp( errorHandle, (OCINumber*)number1, (OCINumber*)number2, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberSign( const ErrorHandle& error, const OCI::Number* number, Int32* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberSign( errorHandle, (OCINumber*)number, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberIsZero( const ErrorHandle& error, const OCI::Number* number, bool* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberIsZero( errorHandle, (OCINumber*)number, (Int32*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberIsInt( const ErrorHandle& error, const OCI::Number* number, bool* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberIsInt( errorHandle, (OCINumber*)number, (Int32*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }

    void NumberAbs( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberAbs( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }

    void NumberAssign( const ErrorHandle& error, const OCI::Number* from, OCI::Number* to )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberAssign( errorHandle, (OCINumber*)from, (OCINumber*)to );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberCeil( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberCeil( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberFloor( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberFloor( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberSqrt( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberSqrt( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberTrunc( const ErrorHandle& error, const OCI::Number* number, Int32 decplace, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberTrunc( errorHandle, (OCINumber*)number, decplace, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberPower( const ErrorHandle& error, const OCI::Number* base, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberPower( errorHandle, (OCINumber*)base, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberRound( const ErrorHandle& error, const OCI::Number* number, Int32 decplace, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberRound( errorHandle, (OCINumber*)number, decplace, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberPrec( const ErrorHandle& error, const OCI::Number* number, Int32 nDigs, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberPrec( errorHandle, (OCINumber*)number, nDigs, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberSin( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberSin( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberArcSin( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberArcSin( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberHypSin( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberHypSin( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberCos( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberCos( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberArcCos( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberArcCos( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberHypCos( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberHypCos( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberTan( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberTan( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberArcTan( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberArcTan( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberArcTan2( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberArcTan2( errorHandle, (OCINumber*)number1, (OCINumber*)number2, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberHypTan( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberHypTan( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberExp( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberExp( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberLn( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberLn( errorHandle, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void NumberLog( const ErrorHandle& error, const OCI::Number* base, const OCI::Number* number, OCI::Number* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCINumberLog( errorHandle, (OCINumber*)base, (OCINumber*)number, (OCINumber*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }



    void DateAssign( const ErrorHandle& error, const OCI::Date* from, OCI::Date* to )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateAssign( errorHandle, (OCIDate*)from, (OCIDate*)to );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void DateToText( const ErrorHandle& error, const OCI::Date* date, const wchar_t* fmt, Byte fmt_length, const wchar_t* lang_name, UInt32 lang_length, UInt32* buf_size, wchar_t* buf )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateToText( errorHandle, (const OCIDate*)date, (const oratext*)fmt, fmt_length, (const oratext*)lang_name, lang_length, buf_size, (oratext*)buf );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void DateFromText( const ErrorHandle& error, const wchar_t* date_str, UInt32 d_str_length, const wchar_t* fmt, Byte fmt_length, const wchar_t* lang_name, UInt32 lang_length, OCI::Date* date )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateFromText( errorHandle, (const oratext*)date_str, d_str_length, (const oratext*)fmt, fmt_length, (const oratext*)lang_name, lang_length, (OCIDate*)date );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void DateCompare( const ErrorHandle& error, const OCI::Date* date1, const OCI::Date* date2, Int32* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateCompare( errorHandle, (const OCIDate*)date1, (const OCIDate*)date2, result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void DateAddMonths( const ErrorHandle& error, const OCI::Date* date, Int32 num_months, OCI::Date* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateAddMonths( errorHandle, (const OCIDate*)date, num_months, (OCIDate*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void DateAddDays( const ErrorHandle& error, const OCI::Date* date, Int32 num_days, OCI::Date* result )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateAddDays( errorHandle, (const OCIDate*)date, num_days, (OCIDate*)result );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void DateLastDay( const ErrorHandle& error, const OCI::Date* date, OCI::Date* last_day )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateLastDay( errorHandle, (const OCIDate*)date, (OCIDate*)last_day );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void DateDaysBetween( const ErrorHandle& error, const OCI::Date* date1, const OCI::Date* date2, Int32* num_days )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateDaysBetween( errorHandle, (const OCIDate*)date1, (OCIDate*)date2, num_days );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void DateZoneToZone( const ErrorHandle& error, const OCI::Date* date1, const wchar_t* zon1, UInt32 zon1_length, const wchar_t* zon2, UInt32 zon2_length, OCI::Date* date2 )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateZoneToZone( errorHandle, (const OCIDate*)date1, (const oratext*)zon1, zon1_length, (const oratext*)zon2, zon2_length, (OCIDate*)date2 );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void DateNextDay( const ErrorHandle& error, const OCI::Date* date, const wchar_t* day_p, UInt32 day_length, OCI::Date* next_day )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateNextDay( errorHandle, (const OCIDate*)date, (const oratext*)day_p, day_length, (OCIDate*)next_day );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }
    void DateSysDate( const ErrorHandle& error, OCI::Date* sys_date )
    {
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIDateSysDate( errorHandle, (OCIDate*)sys_date );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }

    void TransactionStart( const ServiceContext& serviceContext, const ErrorHandle& error, TransactionStartFlags flags, UInt16 timeoutInSeconds )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCITransStart( handle, errorHandle, timeoutInSeconds, static_cast<UInt32>( flags ) );
        error.CheckResult( rc );
    }


    void TransactionStart( const ServiceContext& serviceContext, const ErrorHandle& error, TransactionStartFlags flags, const TimeSpan& timeout )
    {
        TransactionStart( serviceContext, error, flags, static_cast<UInt16>( timeout.Duration( ).TotalSeconds( ) ) );
    }

    void TransactionRollback( const ServiceContext& serviceContext, const ErrorHandle& error )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCITransRollback( handle, errorHandle, OCI_DEFAULT );
        error.CheckResult( rc );
    }
    void TransactionCommit( const ServiceContext& serviceContext, const ErrorHandle& error, TransactionEndFlags flags )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCITransCommit( handle, errorHandle, static_cast<UInt32>( flags ) );
        error.CheckResult( rc );
    }
    void TransactionDetach( const ServiceContext& serviceContext, const ErrorHandle& error )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCITransDetach( handle, errorHandle, OCI_DEFAULT );
        error.CheckResult( rc );
    }
    void TransactionForget( const ServiceContext& serviceContext, const ErrorHandle& error )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCITransForget( handle, errorHandle, OCI_DEFAULT );
        error.CheckResult( rc );
    }
    void TransactionPrepare( const ServiceContext& serviceContext, const ErrorHandle& error )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCITransPrepare( handle, errorHandle, OCI_DEFAULT );
        error.CheckResult( rc );
    }


    void LobAppend( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* dst_locp, OCILobLocator* src_locp )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobAppend( handle, errorHandle, dst_locp, src_locp );
        error.CheckResult( rc );
    }
    void LobCopy( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* dst_locp, OCILobLocator* src_locp, UInt32 amount, UInt32 dst_offset, UInt32 src_offset )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobCopy( handle, errorHandle, dst_locp, src_locp, amount, dst_offset, src_offset );
        error.CheckResult( rc );

    }
    void LobCopy2( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* dst_locp, OCILobLocator* src_locp, UInt64 amount, UInt64 dst_offset, UInt64 src_offset )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobCopy2( handle, errorHandle, dst_locp, src_locp, amount, dst_offset, src_offset );
        error.CheckResult( rc );

    }


    void LobCreateTemporary( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt16 csid, Byte csfrm, Byte lobtype, bool cache, OCI::Duration duration )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobCreateTemporary( handle, errorHandle, locp, csid, csfrm, lobtype, cache, static_cast<OCIDuration>( duration ) );
        error.CheckResult( rc );
    }
    void LobClose( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobClose( handle, errorHandle, locp );
        error.CheckResult( rc );
    }
    void LobDisableBuffering( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobDisableBuffering( handle, errorHandle, locp );
        error.CheckResult( rc );
    }
    void LobEnableBuffering( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobEnableBuffering( handle, errorHandle, locp );
        error.CheckResult( rc );
    }
    void LobErase( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32* amount, UInt32 offset )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobErase( handle, errorHandle, locp, amount, offset );
        error.CheckResult( rc );
    }
    void LobErase2( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt64* amount, UInt64 offset )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobErase2( handle, errorHandle, locp, amount, offset );
        error.CheckResult( rc );
    }

    void LobFileClose( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* filep )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobFileClose( handle, errorHandle, filep );
        error.CheckResult( rc );
    }
    void LobFileCloseAll( const ServiceContext& serviceContext, const ErrorHandle& error )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobFileCloseAll( handle, errorHandle );
        error.CheckResult( rc );
    }
    void LobFileExists( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* filep, bool* flag )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        boolean fl = *flag ? TRUE : FALSE;
        auto rc = OCILobFileExists( handle, errorHandle, filep, &fl );
        error.CheckResult( rc );
        *flag = fl ? true : false;
    }

    void LobFileIsOpen( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* filep, bool* flag )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        boolean fl = *flag ? TRUE : FALSE;
        auto rc = OCILobFileIsOpen( handle, errorHandle, filep, &fl );
        error.CheckResult( rc );
        *flag = fl ? true : false;
    }
    void LobFileOpen( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* filep, Byte mode )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobFileOpen( handle, errorHandle, filep, mode );
        error.CheckResult( rc );
    }
    void LobFlushBuffer( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32 flag )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobFlushBuffer( handle, errorHandle, locp, flag );
        error.CheckResult( rc );
    }
    void LobFreeTemporary( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobFreeTemporary( handle, errorHandle, locp );
        error.CheckResult( rc );
    }
    void LobGetChunkSize( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32* chunksizep )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobGetChunkSize( handle, errorHandle, locp, chunksizep );
        error.CheckResult( rc );
    }
    void LobGetLength( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32* lenp )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobGetLength( handle, errorHandle, locp, lenp );
        error.CheckResult( rc );
    }
    void LobGetLength2( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt64* lenp )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobGetLength2( handle, errorHandle, locp, lenp );
        error.CheckResult( rc );
    }

    void LobIsOpen( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, bool* flag )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        boolean fl = *flag ? TRUE : FALSE;
        auto rc = OCILobIsOpen( handle, errorHandle, locp, &fl );
        error.CheckResult( rc );
        *flag = fl ? true : false;
    }
    void LobLoadFromFile( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* dst_locp, OCILobLocator* src_filep, UInt32 amount, UInt32 dst_offset, UInt32 src_offset )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobLoadFromFile( handle, errorHandle, dst_locp, src_filep, amount, dst_offset, src_offset );
        error.CheckResult( rc );
    }
    void LobLocatorAssign( const ServiceContext& serviceContext, const ErrorHandle& error, const OCILobLocator* src_locp, OCILobLocator** dst_locpp )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobLocatorAssign( handle, errorHandle, src_locp, dst_locpp );
        error.CheckResult( rc );
    }
    void LobOpen( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, Byte mode )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobOpen( handle, errorHandle, locp, mode );
        error.CheckResult( rc );
    }
    void LobRead( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32* amtp, UInt32 offset, void* bufp, UInt32 bufl, void* ctxp, CallbackLobRead cbfp, UInt16 csid, CharacterSetForm csfrm )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobRead( handle, errorHandle, locp, amtp, offset, bufp, bufl, ctxp, cbfp, csid, static_cast<Byte>( csfrm ) );
        error.CheckResult( rc );
    }

    void LobRead2( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt64* byte_amtp, UInt64* char_amtp, UInt64 offset, void* bufp, UInt64 bufl, Piece piece, void* context, CallbackLobRead2 cbfp, UInt16 csid, CharacterSetForm csfrm )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobRead2( handle, errorHandle, locp, byte_amtp, char_amtp, offset, bufp, bufl, static_cast<Byte>(piece), context, (OCICallbackLobRead2)cbfp, csid, static_cast<Byte>( csfrm ) );
        error.CheckResult( rc );
    }

    Int64 LobRead( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, Int64 offset, void* buffer, size_t numberOfBytesToRead )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        UInt32 count = 0;
        UInt32 ociOffset = static_cast<UInt32>( offset );

        auto rc = OCILobRead( handle, errorHandle, locp, &count, ociOffset + 1, buffer, static_cast<UInt32>( numberOfBytesToRead ), nullptr, nullptr, 0, 0 );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        return static_cast<Int64>( count );;
    }


    void LobTrim( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32 newlen )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobTrim( handle, errorHandle, locp, newlen );
        error.CheckResult( rc );
    }
    void LobTrim2( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt64 newlen )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobTrim2( handle, errorHandle, locp, newlen );
        error.CheckResult( rc );
    }
    void LobWrite( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32* amtp, UInt32 offset, void* bufp, UInt32 buflen, Byte piece, void* ctxp, CallbackLobWrite cbfp, UInt16 csid, Byte csfrm )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobWrite( handle, errorHandle, locp, amtp, offset, bufp, buflen, piece, ctxp, cbfp, csid, csfrm );
        error.CheckResult( rc );
    }

    long long LobWrite( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, Int64 offset, const void* buffer, size_t numberOfBytesToWrite )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        UInt64 count = numberOfBytesToWrite;
        UInt64 ociOffset = static_cast<UInt64>( offset );

        auto rc = OCILobWrite2( handle, errorHandle, locp, &count, nullptr, ociOffset + 1, (void*)buffer, numberOfBytesToWrite, OCI_ONE_PIECE, nullptr, nullptr, 0, 0 );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
        return static_cast<long long>( count );
    }


    void LobGetDeduplicateRegions( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, OCILobRegion* regp, UInt32* count, Byte piece, void* ctxp, CallbackLobGetDeduplicateRegions cbfp )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobGetDeduplicateRegions( handle, errorHandle, locp, regp, count, piece, ctxp, reinterpret_cast<OCICallbackLobGetDeduplicateRegions>( cbfp ) );
        error.CheckResult( rc );
    }
    void LobWriteAppend( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* lobp, UInt32* amtp, void* bufp, UInt32 bufl, Byte piece, void* ctxp, CallbackLobWrite cbfp, UInt16 csid, Byte csfrm )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCILobWriteAppend( handle, errorHandle, lobp, amtp, bufp, bufl, piece, ctxp, cbfp, csid, csfrm );
        error.CheckResult( rc );
    }

    WideString LobReadWideString( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, CharacterSetForm csfrm )
    {
        auto length = LobGetLength2( serviceContext, error, locp );
        WideString result;
        result.resize( length );
        auto charLength = length;
        auto byteLength = length * sizeof( wchar_t );
        LobRead2( serviceContext, error, locp, nullptr, &charLength, 1, result.data( ), byteLength, Piece::Single, 0, csfrm );
        return result;

    }
    void LobWriteWideString( const ServiceContext& serviceContext, const ErrorHandle& error, const WideString& str, CharacterSetForm csfrm, OCILobLocator* locp )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        UInt64 count = str.length();
        auto numberOfBytesToWrite = count * sizeof( wchar_t );

        auto rc = OCILobWrite2( handle, errorHandle, locp, nullptr, &count, 1, (void*)str.data(), numberOfBytesToWrite, OCI_ONE_PIECE, nullptr, nullptr, 0, static_cast<Byte>( csfrm ) );
        if ( rc < OCI_SUCCESS )
        {
            error.CheckResult( rc );
        }
    }

    IO::MemoryStream LobReadMemoryStream( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp )
    {
        auto length = LobGetLength2( serviceContext, error, locp );
        IO::MemoryStream result;
        result.SetSize( length );
        auto byteLength = length;
        LobRead2( serviceContext, error, locp, &byteLength, nullptr, 1, result.Buffer( ), byteLength, Piece::Single, 0, CharacterSetForm::Unspecified );
        return result;
    }
    void LobWriteMemoryStream( const ServiceContext& serviceContext, const ErrorHandle& error, const IO::MemoryStream& stream, OCILobLocator* locp )
    {

    }


    void Break( const ServiceContext& serviceContext, const ErrorHandle& error )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIBreak( handle, errorHandle );
        error.CheckResult( rc );
    }
    void Break( const Server& server, const ErrorHandle& error )
    {
        auto handle = (OCIServer*)server.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIBreak( handle, errorHandle );
        error.CheckResult( rc );
    }

    void Reset( const ServiceContext& serviceContext, const ErrorHandle& error )
    {
        auto handle = (OCISvcCtx*)serviceContext.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIReset( handle, errorHandle );
        error.CheckResult( rc );
    }
    void Reset( const Server& server, const ErrorHandle& error )
    {
        auto handle = (OCIServer*)server.Handle( );
        auto errorHandle = (OCIError*)error.Handle( );
        auto rc = OCIReset( handle, errorHandle );
        error.CheckResult( rc );
    }

}