#pragma once
#ifndef __HOCIFUNCTIONS_H__
#define __HOCIFUNCTIONS_H__
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

#include <HOCITypes.h>

namespace Harlinn::OCI
{
    HO_EXPORT void DateTimeAssign( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* from, OCIDateTime* to );
    HO_EXPORT void DateTimeCheck( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* date, DateTimeErrorFlag* errors );
    HO_EXPORT void DateTimeCompare( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* date1, const OCIDateTime* date2, Int32* result );
    HO_EXPORT void DateTimeConstruct( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* datetime, Int16 year, Byte month, Byte day, Byte hour, Byte min, Byte sec, UInt32 fsec, wchar_t* timezone, size_t timezoneLength );
    HO_EXPORT void DateTimeConstruct( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* datetime, const Common::Core::DateTime& source );
    HO_EXPORT void DateTimeConvert( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* indate, OCIDateTime* outdate );
    HO_EXPORT void DateTimeFromArray( const OCI::HandleBase& handle, const ErrorHandle& error, const Byte* inarray, UInt32 len, Byte type, OCIDateTime* datetime, const OCIInterval* reftz, Byte fsprec );
    HO_EXPORT void DateTimeFromText( const OCI::HandleBase& handle, const ErrorHandle& error, const wchar_t* date_str, size_t dstr_length, const wchar_t* fmt, Byte fmt_length, const wchar_t* lang_name, size_t lang_length, OCIDateTime* datetime );
    inline void DateTimeFromText( const OCI::HandleBase& handle, const ErrorHandle& error, const WideString& dateStr, const WideString& fmtStr, const WideString& langNameStr, OCIDateTime* datetime )
    {
        DateTimeFromText( handle, error, dateStr.c_str( ), dateStr.length( ) * sizeof( wchar_t ), fmtStr.c_str( ), static_cast<Byte>( fmtStr.length( ) * sizeof( wchar_t ) ), langNameStr.c_str( ), langNameStr.length( ) * sizeof( wchar_t ), datetime );
    }
    inline void DateTimeFromText( const OCI::HandleBase& handle, const ErrorHandle& error, const WideString& dateStr, const WideString& fmtStr, OCIDateTime* datetime )
    {
        DateTimeFromText( handle, error, dateStr.c_str( ), dateStr.length( ) * sizeof( wchar_t ), fmtStr.c_str( ), static_cast<Byte>( fmtStr.length( ) * sizeof( wchar_t ) ), nullptr, 0, datetime );
    }
    inline void DateTimeFromText( const OCI::HandleBase& handle, const ErrorHandle& error, const WideString& dateStr, OCIDateTime* datetime )
    {
        DateTimeFromText( handle, error, dateStr.c_str( ), dateStr.length( ) * sizeof( wchar_t ), nullptr, 0, nullptr, 0, datetime );
    }

    HO_EXPORT void DateTimeGetDate( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* datetime, Int16* year, Byte* month, Byte* day );
    HO_EXPORT void DateTimeGetTime( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* datetime, Byte* hour, Byte* min, Byte* sec, UInt32* fsec );
    HO_EXPORT void DateTimeGetDateTime( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* source, Common::Core::DateTime& target );
    inline Common::Core::DateTime DateTimeGetDateTime( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* source )
    {
        Common::Core::DateTime result;
        DateTimeGetDateTime( handle, error, source, result );
        return result;
    }
    HO_EXPORT void DateTimeGetTimeZoneName( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* datetime, wchar_t* buf, UInt32* buflen );
    HO_EXPORT void DateTimeGetTimeZoneOffset( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* datetime, char* hour, char* min );
    HO_EXPORT void DateTimeIntervalAdd( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* datetime, OCIInterval* inter, OCIDateTime* outdatetime );
    HO_EXPORT void DateTimeIntervalSub( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* datetime, OCIInterval* inter, OCIDateTime* outdatetime );
    HO_EXPORT void DateTimeSubtract( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* indate1, OCIDateTime* indate2, OCIInterval* inter );
    HO_EXPORT void DateTimeSysTimeStamp( const OCI::HandleBase& handle, const ErrorHandle& error, OCIDateTime* sys_date );
    HO_EXPORT void DateTimeToArray( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* datetime, const OCIInterval* reftz, Byte* outarray, UInt32* len, Byte fsprec );
    HO_EXPORT void DateTimeToText( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* date, const wchar_t* fmt, Byte fmt_length, Byte fsprec, const wchar_t* lang_name, size_t lang_length, UInt32* buf_size, wchar_t* buf );
    HO_EXPORT WideString DateTimeToText( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* date, const wchar_t* fmt, Byte fmt_length, Byte fsprec, const wchar_t* lang_name, size_t lang_length );
    inline WideString DateTimeToText( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* date, const WideString& fmt, Byte fsprec, const WideString& langName )
    {
        return DateTimeToText( handle, error, date, fmt.c_str( ), static_cast<Byte>( fmt.length( ) * sizeof( wchar_t ) ), fsprec, langName.c_str( ), langName.length( ) * sizeof( wchar_t ) );
    }

    inline WideString DateTimeToText( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* date, const WideString& fmt, Byte fsprec )
    {
        return DateTimeToText( handle, error, date, fmt.c_str( ), static_cast<Byte>( fmt.length( ) * sizeof( wchar_t ) ), fsprec, nullptr, static_cast<size_t>( 0 ) );
    }

    inline WideString DateTimeToText( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIDateTime* date, Byte fsprec = 2 )
    {
        return DateTimeToText( handle, error, date, nullptr, 0, fsprec, nullptr, static_cast<size_t>( 0 ) );
    }


    // Interval functions
    HO_EXPORT void IntervalSubtract( const OCI::HandleBase& handle, const ErrorHandle& error, OCIInterval* minuend, OCIInterval* subtrahend, OCIInterval* result );
    HO_EXPORT void IntervalAdd( const OCI::HandleBase& handle, const ErrorHandle& error, OCIInterval* addend1, OCIInterval* addend2, OCIInterval* result );
    HO_EXPORT void IntervalMultiply( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIInterval* inter, OCI::Number* nfactor, OCIInterval* result );
    HO_EXPORT void IntervalDivide( const OCI::HandleBase& handle, const ErrorHandle& error, OCIInterval* dividend, OCI::Number* divisor, OCIInterval* result );
    HO_EXPORT void IntervalCompare( const OCI::HandleBase& handle, const ErrorHandle& error, OCIInterval* inter1, OCIInterval* inter2, Int32* result );
    HO_EXPORT void IntervalFromNumber( const OCI::HandleBase& handle, const ErrorHandle& error, OCIInterval* inter, OCI::Number* number );
    HO_EXPORT void IntervalFromText( const OCI::HandleBase& handle, const ErrorHandle& error, const wchar_t* inpstr, size_t str_len, OCIInterval* result );
    HO_EXPORT void IntervalToText( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIInterval* inter, Byte lfprec, Byte fsprec, wchar_t* buffer, size_t buflen, size_t* resultlen );
    inline WideString IntervalToText( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIInterval* inter, Byte lfprec, Byte fsprec )
    {
        wchar_t buffer[256] = {}; 
        size_t buflen = 512; 
        size_t resultlen = 0;
        IntervalToText( handle, error, inter, lfprec, fsprec, buffer, buflen, &resultlen );
        return WideString( buffer, resultlen );
    }
    HO_EXPORT void IntervalToNumber( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIInterval* inter, OCI::Number* number );
    HO_EXPORT void IntervalCheck( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIInterval* interval, UInt32* valid );
    HO_EXPORT void IntervalAssign( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIInterval* ininter, OCIInterval* outinter );
    HO_EXPORT void IntervalSetYearMonth( const OCI::HandleBase& handle, const ErrorHandle& error, Int32 yr, Int32 mnth, OCIInterval* result );
    HO_EXPORT void IntervalGetYearMonth( const OCI::HandleBase& handle, const ErrorHandle& error, Int32* yr, Int32* mnth, const OCIInterval* result );
    HO_EXPORT void IntervalSetDaySecond( const OCI::HandleBase& handle, const ErrorHandle& error, Int32 dy, Int32 hr, Int32 mm, Int32 ss, Int32 fsec, OCIInterval* result );
    HO_EXPORT void IntervalGetDaySecond( const OCI::HandleBase& handle, const ErrorHandle& error, Int32* dy, Int32* hr, Int32* mm, Int32* ss, Int32* fsec, const OCIInterval* result );
    inline TimeSpan IntervalGetTimeSpan( const OCI::HandleBase& handle, const ErrorHandle& error, const OCIInterval* interval )
    {
        Int32 dy, hr, mm, ss, fsec;
        IntervalGetDaySecond( handle, error, &dy, &hr, &mm, &ss, &fsec, interval );
        auto ticks = static_cast<Int64>( dy ) * TimeSpan::TicksPerDay;
        ticks += static_cast<Int64>( hr ) * TimeSpan::TicksPerHour;
        ticks += static_cast<Int64>( mm ) * TimeSpan::TicksPerMinute;
        ticks += static_cast<Int64>( ss ) * TimeSpan::TicksPerSecond;
        ticks += static_cast<Int64>( fsec / 100 );
        return TimeSpan( ticks );
    }
    inline void IntervalSetTimeSpan( const OCI::HandleBase& handle, const ErrorHandle& error, const TimeSpan& timeSpan, OCIInterval* result )
    {
        Int32 dy = static_cast<Int32>( timeSpan.TotalDays( ) );
        Int32 hr = timeSpan.Hours( );
        Int32 mm = timeSpan.Minutes( );  
        Int32 ss = timeSpan.Seconds( ); 
        Int32 fsec = (timeSpan.Ticks() % TimeSpan::TicksPerSecond)*100;
        IntervalSetDaySecond( handle, error, dy, hr, mm, ss, fsec, result );
    }



    HO_EXPORT void IntervalFromTZ( const OCI::HandleBase& handle, const ErrorHandle& error, const wchar_t* inpstring, size_t str_len, OCIInterval* result );

    /// <summary>
/// Append the given element to the end of the given collection.
/// </summary>
/// <param name="elem">pointer to the element which is appended to the end of the given collection</param>
/// <param name="elemind">pointer to the element's null indicator information; if (elemind == NULL) then the null indicator information of the appended element will be set to non-null.</param>
/// <param name="coll">collection</param>
    HO_EXPORT void CollectionAppend( const Environment& environment, const ErrorHandle& error, const void* elem, const void* elemind, OCIColl* coll );
    /// <summary>
    /// Assign 'rhs' to 'lhs'.
    /// </summary>
    /// <param name="rhs">collection to be assigned from</param>
    /// <param name="lhs">collection to be assigned to</param>
    /// <remarks>
    /// The 'lhs' collection may be decreased or 
    /// increased depending upon the size of 'rhs'.If the 'lhs' contains
    /// any elements then the elements will be deleted prior to the
    /// assignment.This function performs a deep - copy.The memory for the
    /// elements comes from the object cache.
    /// </remarks>
    HO_EXPORT void CollectionAssign( const Environment& environment, const ErrorHandle& error, const OCIColl* rhs, OCIColl* lhs );
    /// <summary>
    /// Assign the given element value 'elem' to the element at coll[index]
    /// </summary>
    /// <param name="index">index of the element whose is assigned to</param>
    /// <param name="elem">element which is assigned from (source element)</param>
    /// <param name="elemind">pointer to the element's null indicator  information; if ( elemind == NULL ) then the null indicator information of the assigned element will be set to non - null.</param>
    /// <param name="coll">collection to be updated</param>
    /// <remarks>
    /// If the collection is of type nested table, the element at the given
    /// index may not exist( i.e.may have been deleted ).In this case, the
    /// given element is inserted at index 'index'.
    /// Otherwise, the element at index 'index' is updated with the value
    /// of 'elem'.
    /// 
    /// Note: The given element is deep-copied and 'elem' is strictly an input parameter.
    /// </remarks>
    HO_EXPORT void CollectionAssignElement( const Environment& environment, const ErrorHandle& error, Int32 index, const void* elem, const void* elemind, OCIColl* coll );
    /// <summary>
    /// Get the address of the element at the given position. Optionally
    /// this function also returns the address of the element's null indicator
    /// information.
    /// </summary>
    /// <param name="coll">pointer to the element in this collection is returned</param>
    /// <param name="index">index of the element whose pointer is returned</param>
    /// <param name="exists">set to FALSE if element at the specified index does not exist else TRUE</param>
    /// <param name="elem">address of the desired element is returned</param>
    /// <param name="elemind">address of the null indicator information  is returned; if ( elemind == NULL ) then the null indicator information will NOT be returned</param>
    HO_EXPORT void CollectionGetElement( const Environment& environment, const ErrorHandle& error, const OCIColl* coll, Int32 index, bool* exists, void** elem, void** elemind );
    /// <summary>
    /// Get the address of the elements from the given position. Optionally
    /// this function also returns the address of the element's null indicator
    /// information.
    /// </summary>
    /// <param name="coll"></param>
    /// <param name="index"></param>
    /// <param name="exists"></param>
    /// <param name="elem"></param>
    /// <param name="elemind"></param>
    /// <param name="nelems"></param>
    /// <returns></returns>
    HO_EXPORT void CollectionGetElementArray( const Environment& environment, const ErrorHandle& error, const OCIColl* coll, Int32 index, bool* exists, void** elem, void** elemind, UInt32* nelems );
    HO_EXPORT void CollectionIsLocator( const Environment& environment, const ErrorHandle& error, const OCIColl* coll, bool* result );
    HO_EXPORT Int32 CollectionMax( const Environment& environment, const OCIColl* coll );
    HO_EXPORT void CollectionSize( const Environment& environment, const ErrorHandle& error, const OCIColl* coll, Int32* size );
    HO_EXPORT void CollectionTrim( const Environment& environment, const ErrorHandle& error, Int32 trim_num, OCIColl* coll );

    HO_EXPORT void IteratorCreate( const Environment& environment, const ErrorHandle& error, const OCIColl* coll, OCIIter** itr );
    HO_EXPORT void IteratorDelete( const Environment& environment, const ErrorHandle& error, OCIIter** itr );
    HO_EXPORT void IteratorGetCurrent( const Environment& environment, const ErrorHandle& error, const OCIIter* itr, void** elem, void** elemind );
    HO_EXPORT void IteratorInit( const Environment& environment, const ErrorHandle& error, const OCIColl* coll, OCIIter* itr );
    HO_EXPORT void IteratorNext( const Environment& environment, const ErrorHandle& error, OCIIter* itr, void** elem, void** elemind, bool* eoc );
    HO_EXPORT void IteratorPrev( const Environment& environment, const ErrorHandle& error, OCIIter* itr, void** elem, void** elemind, bool* boc );


    HO_EXPORT void RawAllocSize( const Environment& environment, const ErrorHandle& error, const OCIRaw* raw, UInt32* allocsize );
    HO_EXPORT void RawAssignBytes( const Environment& environment, const ErrorHandle& error, const Byte* bytes, UInt32 bytesLength, OCIRaw** lhs );
    HO_EXPORT void RawAssignRaw( const Environment& environment, const ErrorHandle& error, const OCIRaw* rhs, OCIRaw** lhs );
    HO_EXPORT Byte* RawPtr( const Environment& environment, const OCIRaw* raw );
    HO_EXPORT void RawResize( const Environment& environment, const ErrorHandle& error, UInt32 newSize, OCIRaw** raw );
    HO_EXPORT UInt32 RawSize( const Environment& environment, const OCIRaw* raw );

    HO_EXPORT void RefAssign( const Environment& environment, const ErrorHandle& error, const OCIRef* source, OCIRef** target );
    HO_EXPORT void RefClear( const Environment& environment, OCIRef* ref );
    HO_EXPORT void RefFromHex( const Environment& environment, const ErrorHandle& error, const OCISvcCtx* svc, const wchar_t* hex, UInt32 length, OCIRef** ref );
    HO_EXPORT UInt32 RefHexSize( const Environment& environment, const OCIRef* ref );
    HO_EXPORT bool RefIsEqual( const Environment& environment, const OCIRef* x, const OCIRef* y );
    HO_EXPORT bool RefIsNull( const Environment& environment, const OCIRef* ref );
    HO_EXPORT void RefToHex( const Environment& environment, const ErrorHandle& error, const OCIRef* ref, wchar_t* hex, UInt32* hexLength );

    HO_EXPORT void StringAllocSize( const Environment& environment, const ErrorHandle& error, const OCIString* vs, UInt32* allocsize );
    HO_EXPORT void StringAssign( const Environment& environment, const ErrorHandle& error, const OCIString* rhs, OCIString** lhs );
    HO_EXPORT void StringAssignText( const Environment& environment, const ErrorHandle& error, const wchar_t* rhs, UInt32 rhs_len, OCIString** lhs );
    HO_EXPORT wchar_t* StringPtr( const Environment& environment, const OCIString* vs );
    HO_EXPORT void StringResize( const Environment& environment, const ErrorHandle& error, UInt32 newSize, OCIString** str );
    HO_EXPORT UInt32 StringSize( const Environment& environment, const OCIString* vs );

    HO_EXPORT void TableDelete( const Environment& environment, const ErrorHandle& error, Int32 index, OCITable* tbl );
    HO_EXPORT bool TableExists( const Environment& environment, const ErrorHandle& error, const OCITable* tbl, Int32 index );
    HO_EXPORT bool TableFirst( const Environment& environment, const ErrorHandle& error, const OCITable* tbl, Int32* index );
    HO_EXPORT bool TableLast( const Environment& environment, const ErrorHandle& error, const OCITable* tbl, Int32* index );
    HO_EXPORT bool TableNext( const Environment& environment, const ErrorHandle& error, Int32 index, const OCITable* tbl, Int32* nextIndex );
    HO_EXPORT bool TablePrev( const Environment& environment, const ErrorHandle& error, Int32 index, const OCITable* tbl, Int32* prevIndex );
    HO_EXPORT void TableSize( const Environment& environment, const ErrorHandle& error, const OCITable* tbl, Int32* size );


    HO_EXPORT void LobAssign( const Environment& environment, const ErrorHandle& error, const OCILobLocator* src_locp, OCILobLocator** dst_locpp );
    HO_EXPORT void LobCharSetForm( const Environment& environment, const ErrorHandle& error, const OCILobLocator* locp, Byte* csfrm );
    HO_EXPORT void LobCharSetId( const Environment& environment, const ErrorHandle& error, const OCILobLocator* locp, UInt16* csid );
    HO_EXPORT void LobFileSetName( const Environment& environment, const ErrorHandle& error, OCILobLocator** filepp, const wchar_t* dir_alias, UInt16 d_length, const wchar_t* filename, UInt16 f_length );
    HO_EXPORT void LobIsEqual( const Environment& environment, const OCILobLocator* x, const OCILobLocator* y, bool* is_equal );
    HO_EXPORT void LobIsTemporary( const Environment& environment, const ErrorHandle& error, OCILobLocator* locp, bool* is_temporary );
    HO_EXPORT void LobLocatorIsInit( const Environment& environment, const ErrorHandle& error, const OCILobLocator* locp, bool* is_initialized );
    HO_EXPORT void LobFileGetName( const Environment& environment, const ErrorHandle& error, const OCILobLocator* filep, wchar_t* dir_alias, UInt16* d_length, wchar_t* filename, UInt16* f_length );

    HO_EXPORT void NumberInc( const ErrorHandle& error, OCI::Number* number );
    HO_EXPORT void NumberDec( const ErrorHandle& error, OCI::Number* number );
    HO_EXPORT void NumberSetZero( const ErrorHandle& error, OCI::Number* num );
    HO_EXPORT void NumberSetPi( const ErrorHandle& error, OCI::Number* num );
    HO_EXPORT void NumberAdd( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, OCI::Number* result );
    HO_EXPORT void NumberSub( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, OCI::Number* result );
    HO_EXPORT void NumberMul( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, OCI::Number* result );
    HO_EXPORT void NumberDiv( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, OCI::Number* result );
    HO_EXPORT void NumberMod( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, OCI::Number* result );
    HO_EXPORT void NumberIntPower( const ErrorHandle& error, const OCI::Number* base, const Int32 exp, OCI::Number* result );
    HO_EXPORT void NumberShift( const ErrorHandle& error, const OCI::Number* number, const Int32 nDig, OCI::Number* result );
    HO_EXPORT void NumberNeg( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberToText( const ErrorHandle& error, const OCI::Number* number, const wchar_t* fmt, UInt32 fmt_length, const wchar_t* nls_params, UInt32 nls_p_length, UInt32* buf_size, wchar_t* buf );
    HO_EXPORT void NumberFromText( const ErrorHandle& error, const wchar_t* str, UInt32 str_length, const wchar_t* fmt, UInt32 fmt_length, const wchar_t* nls_params, UInt32 nls_p_length, OCI::Number* number );
    HO_EXPORT void NumberToInt( const ErrorHandle& error, const OCI::Number* number, UInt32 rsl_length, NumberToIntFlags rsl_flag, void* rsl );
    HO_EXPORT void NumberFromInt( const ErrorHandle& error, const void* inum, UInt32 inum_length, NumberToIntFlags inum_s_flag, OCI::Number* number );
    HO_EXPORT void NumberToReal( const ErrorHandle& error, const OCI::Number* number, UInt32 rsl_length, void* rsl );
    HO_EXPORT void NumberToRealArray( const ErrorHandle& error, const OCI::Number** number, UInt32 elems, UInt32 rsl_length, void* rsl );
    HO_EXPORT void NumberFromReal( const ErrorHandle& error, const void* rnum, UInt32 rnum_length, OCI::Number* number );
    HO_EXPORT void NumberCmp( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, Int32* result );
    HO_EXPORT void NumberSign( const ErrorHandle& error, const OCI::Number* number, Int32* result );
    HO_EXPORT void NumberIsZero( const ErrorHandle& error, const OCI::Number* number, bool* result );
    HO_EXPORT void NumberIsInt( const ErrorHandle& error, const OCI::Number* number, bool* result );
    HO_EXPORT void NumberAbs( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberAssign( const ErrorHandle& error, const OCI::Number* from, OCI::Number* to );
    HO_EXPORT void NumberCeil( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberFloor( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberSqrt( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberTrunc( const ErrorHandle& error, const OCI::Number* number, Int32 decplace, OCI::Number* result );
    HO_EXPORT void NumberPower( const ErrorHandle& error, const OCI::Number* base, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberRound( const ErrorHandle& error, const OCI::Number* number, Int32 decplace, OCI::Number* result );
    HO_EXPORT void NumberPrec( const ErrorHandle& error, const OCI::Number* number, Int32 nDigs, OCI::Number* result );
    HO_EXPORT void NumberSin( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberArcSin( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberHypSin( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberCos( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberArcCos( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberHypCos( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberTan( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberArcTan( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberArcTan2( const ErrorHandle& error, const OCI::Number* number1, const OCI::Number* number2, OCI::Number* result );
    HO_EXPORT void NumberHypTan( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberExp( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberLn( const ErrorHandle& error, const OCI::Number* number, OCI::Number* result );
    HO_EXPORT void NumberLog( const ErrorHandle& error, const OCI::Number* base, const OCI::Number* number, OCI::Number* result );



    HO_EXPORT void DateAssign( const ErrorHandle& error, const OCI::Date* from, OCI::Date* to );
    HO_EXPORT void DateToText( const ErrorHandle& error, const OCI::Date* date, const wchar_t* fmt, Byte fmt_length, const wchar_t* lang_name, UInt32 lang_length, UInt32* buf_size, wchar_t* buf );
    HO_EXPORT void DateFromText( const ErrorHandle& error, const wchar_t* date_str, UInt32 d_str_length, const wchar_t* fmt, Byte fmt_length, const wchar_t* lang_name, UInt32 lang_length, OCI::Date* date );
    HO_EXPORT void DateCompare( const ErrorHandle& error, const OCI::Date* date1, const OCI::Date* date2, Int32* result );
    HO_EXPORT void DateAddMonths( const ErrorHandle& error, const OCI::Date* date, Int32 num_months, OCI::Date* result );
    HO_EXPORT void DateAddDays( const ErrorHandle& error, const OCI::Date* date, Int32 num_days, OCI::Date* result );
    HO_EXPORT void DateLastDay( const ErrorHandle& error, const OCI::Date* date, OCI::Date* last_day );
    HO_EXPORT void DateDaysBetween( const ErrorHandle& error, const OCI::Date* date1, const OCI::Date* date2, Int32* num_days );
    HO_EXPORT void DateZoneToZone( const ErrorHandle& error, const OCI::Date* date1, const wchar_t* zon1, UInt32 zon1_length, const wchar_t* zon2, UInt32 zon2_length, OCI::Date* date2 );
    HO_EXPORT void DateNextDay( const ErrorHandle& error, const OCI::Date* date, const wchar_t* day_p, UInt32 day_length, OCI::Date* next_day );
    HO_EXPORT void DateSysDate( const ErrorHandle& error, OCI::Date* sys_date );

    HO_EXPORT void TransactionStart( const ServiceContext& serviceContext, const ErrorHandle& error, TransactionStartFlags flags = TransactionStartFlags::None, UInt16 timeoutInSeconds = 0 );
    HO_EXPORT void TransactionStart( const ServiceContext& serviceContext, const ErrorHandle& error, TransactionStartFlags flags, const TimeSpan& timeout );
    HO_EXPORT void TransactionRollback( const ServiceContext& serviceContext, const ErrorHandle& error );
    HO_EXPORT void TransactionCommit( const ServiceContext& serviceContext, const ErrorHandle& error, TransactionEndFlags flags = TransactionEndFlags::None );
    HO_EXPORT void TransactionDetach( const ServiceContext& serviceContext, const ErrorHandle& error );
    HO_EXPORT void TransactionForget( const ServiceContext& serviceContext, const ErrorHandle& error );
    HO_EXPORT void TransactionPrepare( const ServiceContext& serviceContext, const ErrorHandle& error );

    HO_EXPORT void LobAppend( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* dst_locp, OCILobLocator* src_locp );
    HO_EXPORT void LobCopy( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* dst_locp, OCILobLocator* src_locp, UInt32 amount, UInt32 dst_offset, UInt32 src_offset );
    HO_EXPORT void LobCopy2( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* dst_locp, OCILobLocator* src_locp, UInt64 amount, UInt64 dst_offset, UInt64 src_offset );
    HO_EXPORT void LobCreateTemporary( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt16 csid, Byte csfrm, Byte lobtype, bool cache, OCI::Duration duration );
    HO_EXPORT void LobClose( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp );
    HO_EXPORT void LobDisableBuffering( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp );
    HO_EXPORT void LobEnableBuffering( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp );
    HO_EXPORT void LobErase( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32* amount, UInt32 offset );
    HO_EXPORT void LobErase2( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt64* amount, UInt64 offset );
    HO_EXPORT void LobFileClose( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* filep );
    HO_EXPORT void LobFileCloseAll( const ServiceContext& serviceContext, const ErrorHandle& error );
    HO_EXPORT void LobFileExists( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* filep, bool* flag );

    HO_EXPORT void LobFileIsOpen( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* filep, bool* flag );
    HO_EXPORT void LobFileOpen( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* filep, Byte mode );
    HO_EXPORT void LobFlushBuffer( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32 flag );
    HO_EXPORT void LobFreeTemporary( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp );
    HO_EXPORT void LobGetChunkSize( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32* chunksizep );
    HO_EXPORT void LobGetLength( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32* lenp );
    HO_EXPORT void LobGetLength2( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt64* lenp );
    inline UInt64 LobGetLength2( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp )
    {
        UInt64 result = 0;
        LobGetLength2( serviceContext, error, locp, &result );
        return result;
    }
    HO_EXPORT void LobIsOpen( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, bool* flag );
    HO_EXPORT void LobLoadFromFile( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* dst_locp, OCILobLocator* src_filep, UInt32 amount, UInt32 dst_offset, UInt32 src_offset );
    HO_EXPORT void LobLocatorAssign( const ServiceContext& serviceContext, const ErrorHandle& error, const OCILobLocator* src_locp, OCILobLocator** dst_locpp );
    HO_EXPORT void LobOpen( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, Byte mode );
    HO_EXPORT void LobRead( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32* amtp, UInt32 offset, void* bufp, UInt32 bufl, void* ctxp, CallbackLobRead cbfp, UInt16 csid, CharacterSetForm csfrm );
    HO_EXPORT void LobRead2( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt64* byte_amtp, UInt64* char_amtp, UInt64 offset, void* bufp, UInt64 bufl, Piece piece, void* context, CallbackLobRead2 cbfp, UInt16 csid, CharacterSetForm csfrm );
    HO_EXPORT Int64 LobRead( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, Int64 offset, void* buffer, size_t numberOfBytesToRead );

    inline void LobRead2( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt64* byte_amtp, UInt64* char_amtp, UInt64 offset, void* bufp, UInt64 bufl, Piece piece, UInt16 csid, CharacterSetForm csfrm )
    {
        LobRead2( serviceContext, error, locp, byte_amtp, char_amtp, offset, bufp, bufl, piece, nullptr, nullptr, csid, csfrm );
    }




    HO_EXPORT void LobTrim( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32 newlen );
    HO_EXPORT void LobTrim2( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt64 newlen );
    HO_EXPORT void LobWrite( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, UInt32* amtp, UInt32 offset, void* bufp, UInt32 buflen, Byte piece, void* ctxp, CallbackLobWrite cbfp, UInt16 csid, Byte csfrm );
    HO_EXPORT Int64 LobWrite( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, Int64 offset, const void* buffer, size_t numberOfBytesToWrite );
    HO_EXPORT void LobGetDeduplicateRegions( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, OCILobRegion* regp, UInt32* count, Byte piece, void* ctxp, CallbackLobGetDeduplicateRegions cbfp );
    HO_EXPORT void LobWriteAppend( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* lobp, UInt32* amtp, void* bufp, UInt32 bufl, Byte piece, void* ctxp, CallbackLobWrite cbfp, UInt16 csid, Byte csfrm );

    HO_EXPORT WideString LobReadWideString( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp, CharacterSetForm csfrm );
    HO_EXPORT void LobWriteWideString( const ServiceContext& serviceContext, const ErrorHandle& error, const WideString& str, CharacterSetForm csfrm, OCILobLocator* locp );

    HO_EXPORT IO::MemoryStream LobReadMemoryStream( const ServiceContext& serviceContext, const ErrorHandle& error, OCILobLocator* locp );
    HO_EXPORT void LobWriteMemoryStream( const ServiceContext& serviceContext, const ErrorHandle& error, const IO::MemoryStream& stream, OCILobLocator* locp );


    /// <summary>
    /// Performs an immediate (asynchronous) termination of any currently 
    /// executing OCI function that is associated with a server.
    /// </summary>
    /// <param name="serviceContext">The service context</param>
    /// <param name="error">An error for diagnostic information when there is an error</param>
    HO_EXPORT void Break( const ServiceContext& serviceContext, const ErrorHandle& error );
    /// <summary>
    /// Performs an immediate (asynchronous) termination of any currently 
    /// executing OCI function that is associated with a server.
    /// </summary>
    /// <param name="server">The server context</param>
    /// <param name="error">An error for diagnostic information when there is an error</param>
    HO_EXPORT void Break( const Server& server, const ErrorHandle& error );


    HO_EXPORT void Reset( const ServiceContext& serviceContext, const ErrorHandle& error );
    HO_EXPORT void Reset( const Server& server, const ErrorHandle& error );




}

#endif
