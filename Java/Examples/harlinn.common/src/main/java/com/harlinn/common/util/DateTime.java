package com.harlinn.common.util;

import java.io.Serializable;
import java.time.Instant;
import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.util.TimeZone;

/**
 * This class represents a date and time using a long that stores the
 * date and time as the number of 100 nanosecond intervals since
 * 12:00 AM January 1, year 1 A.D. in the proleptic Gregorian Calendar.
 * <p>
 * It is intended to be fairly compatible with the DateTime struct
 * as implemented by the .Net platform, as ticks have the same duration.
 * </p>
 */
public class DateTime extends TimeBase implements Comparable<DateTime>, Serializable, Cloneable {
	/**
	 * 
	 */
	private static final long serialVersionUID = -8570919241185163390L;
	long ticks;
	
	public DateTime() {
	}
	
	public DateTime(long ticks) {
		this.ticks = ticks;
	}
	
	public DateTime(int year, int month, int day) {
		this.ticks = dateToTicks(year, month, day);
	}
	
	public DateTime(int year, int month, int day, int hour, int minute, int second) {
		this.ticks = toTicks(year, month, day, hour, minute, second, 0);
	}
	
	public DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond) {
		this.ticks = toTicks(year, month, day, hour, minute, second, millisecond);
	} 
	
	public DateTime(LocalDateTime localDateTime) {
		var instant = localDateTime.toInstant(ZoneOffset.ofTotalSeconds(0));
		this.ticks = toTicks(instant.getEpochSecond(),instant.getNano());
	}
	
	public DateTime(Instant instant) {
		this.ticks = toTicks(instant.getEpochSecond(),instant.getNano());
	}
	
	public DateTime(java.util.Date date) {
		this.ticks = (date.getTime()*TicksPerMillisecond) + UnixEpoch;
	}
	
	public DateTime(java.sql.Date date) {
		this.ticks = (date.getTime()*TicksPerMillisecond) + UnixEpoch;
	}
	
	@Override
	public boolean equals(Object obj) {
		if ( this == obj ) {
			return true;
		}
		if(obj == null ) {
			return false;
		}
		if ((obj instanceof DateTime) == false ) {
            return false;
        }
		var other = (DateTime)obj;
		return other.ticks == this.ticks; 
	}

	@Override
	public DateTime clone() throws CloneNotSupportedException {
		return new DateTime(ticks);
	}
	
	public final long hash() {
		var x = ( ticks ^ ( ticks >>> 30 ) ) * 0xbf58476d1ce4e5b9L;
		x = ( x ^ ( x >> 27 ) ) * 0x94d049bb133111ebL;
		x = x ^ ( x >> 31 );
		return x;
	}
	
	@Override
	public int hashCode() {
		return (int)hash();
	}

	public static long getRawOfset() {
		return (((long)TimeZone.getDefault().getRawOffset())*TicksPerMillisecond);
	}
	
	
	public static long toLocalTicks( long ticksInUtc ) {
		return com.harlinn.common.platform.Kernel32.FileTimeToLocalFileTime(ticksInUtc - FileTimeOffset) + FileTimeOffset;
	}
	public static long toUniversalTicks( long ticksInLocalTime ) {
		return com.harlinn.common.platform.Kernel32.LocalFileTimeToFileTime(ticksInLocalTime - FileTimeOffset) + FileTimeOffset;
	}
	
	public static long toTicks( long secondsSince1970, int nanoSeconds ) {
		return (secondsSince1970 * TicksPerSecond + nanoSeconds / 100) + UnixEpoch;
	}
	
	private static boolean isLeapYear( int year ) {
	    if ( year < 1 || year > 9999 ) {
	        throw new IllegalArgumentException( "year" );
	    }
	    return year % 4 == 0 && ( year % 100 != 0 || year % 400 == 0 );
	}
	
	private static long dateToTicks( int year, int month, int day )	{
	    if ( year >= 1 && year <= 9999 && month >= 1 && month <= 12 ) {
	        var days = isLeapYear( year ) ? DaysToMonth366 : DaysToMonth365;
	        long daysUntilNextMonth = days[month];
	        long daysUntilMonth = days[month - 1];
	        if ( day >= 1 && day <= daysUntilNextMonth - daysUntilMonth ) {
	            long y = year - 1;
	            long n = y * 365 + y / 4 - y / 100 + y / 400 + daysUntilMonth + day - 1;
	            return n * TicksPerDay;
	        }
	    }
	    var message = String.format( "Argument out of range. Year: {}, Month: {}, Day: {}", year, month, day );
	    throw new IllegalArgumentException( message );
	}
	
	private static int daysInMonth( int year, int month ) {
	    if ( month < 1 || month > 12 ) {
	        throw new IllegalArgumentException( "month" );
	    }
	    var days = isLeapYear( year ) ? DaysToMonth366 : DaysToMonth365;
	    return days[month] - days[month - 1];
	}
	
	static long timeToTicks( int hour, int minute, int second )	{
	    if ( hour >= 0 && hour < 24 && minute >= 0 && minute < 60 && second >= 0 && second < 60 ) {
	        return TimeSpan.timeToTicks( 0, hour, minute, second, 0 );
	    }
	    throw new IllegalArgumentException( );
	}
	
	static long toTicks( int year, int month, int day, int hour, int minute, int second, int millisecond )
	{
	    if ( millisecond < 0 || millisecond >= MillisPerSecond ) {
	        throw new IllegalArgumentException( "millisecond" );
	    }
	    long ticks = dateToTicks( year, month, day ) + timeToTicks( hour, minute, second );
	    ticks += millisecond * TicksPerMillisecond;
	    if ( ticks < MinTicks || ticks > MaxTicks ) {
	        throw new IllegalArgumentException( );
	    }
	    return ticks;
	}
	
	public record YearMonthDay(int year, int month, int day)
	{}
	
	public static YearMonthDay getYearMonthDay(long ticks) {
		int n = (int)( ticks / TicksPerDay );
		int periodsOf400years = n / DaysPer400Years;
		n -= periodsOf400years * DaysPer400Years;
		int periodsOf100years = n / DaysPer100Years;
		if ( periodsOf100years == 4 ) {
		    periodsOf100years = 3;
		}
		n -= periodsOf100years * DaysPer100Years;
		int periodsOf4years = n / DaysPer4Years;
		n -= periodsOf4years * DaysPer4Years;
		int y1 = n / DaysPerYear;
		if ( y1 == 4 ) {
		    y1 = 3;
		}

		int year = periodsOf400years * 400 + periodsOf100years * 100 + periodsOf4years * 4 + y1 + 1;

		n -= y1 * DaysPerYear;

		boolean leapYear = y1 == 3 && ( periodsOf4years != 24 || periodsOf100years == 3 );

		var days = leapYear ? DaysToMonth366 : DaysToMonth365;

		int month = ( n >> 5 ) + 1;

		while ( n >= days[month] ) {
			month++;
		}

		int day = (n - days[month - 1] + 1);
		return new YearMonthDay(year, month, day);
	}
	
	public YearMonthDay getYearMonthDay() {
		return getYearMonthDay(ticks);
	}
	
	public static int datePart( long ticks, DatePart part ) {
	    int n = (int)( ticks / TicksPerDay );
	    int periodsOf400years = n / DaysPer400Years;
	    n -= periodsOf400years * DaysPer400Years;
	    int periodsOf100years = n / DaysPer100Years;
	    if ( periodsOf100years == 4 ) {
	        periodsOf100years = 3;
	    }
	    n -= periodsOf100years * DaysPer100Years;
	    int periodsOf4years = n / DaysPer4Years;
	    n -= periodsOf4years * DaysPer4Years;
	    int y1 = n / DaysPerYear;
	    if ( y1 == 4 ) {
	        y1 = 3;
	    }

	    if ( part == DatePart.Year ) {
	        return periodsOf400years * 400 + periodsOf100years * 100 + periodsOf4years * 4 + y1 + 1;
	    }
	    n -= y1 * DaysPerYear;
	    if ( part == DatePart.DayOfYear ) {
	        return n + 1;
	    }

	    boolean leapYear = y1 == 3 && ( periodsOf4years != 24 || periodsOf100years == 3 );

	    var days = leapYear ? DaysToMonth366 : DaysToMonth365;

	    int m = ( n >> 5 ) + 1;

	    while ( n >= days[m] ) {
	        m++;
	    }
	    if ( part == DatePart.Month )
	    {
	        return m;
	    }
	    return n - days[m - 1] + 1;
	}
	
	public int datePart( DatePart part ) {
		return datePart(ticks, part);
	}
	
	
	public static DateTime now() {
		return new DateTime(com.harlinn.common.platform.Kernel32.GetSystemTimePreciseAsFileTime() + FileTimeOffset);
	}
	
	public DateTime toLocalTime() {
		return new DateTime(com.harlinn.common.platform.Kernel32.FileTimeToLocalFileTime(ticks - FileTimeOffset) + FileTimeOffset);
	}
	
	public DateTime toUniversalTime() {
		return new DateTime(com.harlinn.common.platform.Kernel32.LocalFileTimeToFileTime(ticks - FileTimeOffset) + FileTimeOffset);
	}
	
	
	
	public java.util.Date toDate() {
		return new java.util.Date((ticks - UnixEpoch)/TicksPerMillisecond);
	}
	
	public java.sql.Date toSqlDate() {
		return new java.sql.Date((ticks - UnixEpoch)/TicksPerMillisecond);
	}
	
	public java.sql.Timestamp toSqlTimestamp() {
		var milliseconds = (ticks - UnixEpoch)/TicksPerMillisecond;
		return new java.sql.Timestamp(milliseconds);
	}
	
	public Instant toInstant() {
		long secondsSince1970 = (ticks - UnixEpoch)/TicksPerSecond;
		int nanoSeconds = (int)((ticks % TicksPerSecond)*100L);
		return Instant.ofEpochSecond(secondsSince1970,nanoSeconds);
	}
	
	public LocalDateTime toLocalDateTime() {
		var instant = toInstant();
		return LocalDateTime.ofEpochSecond(instant.getEpochSecond(),instant.getNano(), ZoneOffset.UTC );
	}
	
	public LocalDateTime toLocalDateTime(ZoneOffset zoneOffset) {
		var instant = toInstant();
		return LocalDateTime.ofEpochSecond(instant.getEpochSecond(),instant.getNano(), zoneOffset );
	}
	
	public long toTicks() {
		return ticks;
	}
	public long getTicks() {
		return ticks;
	}
	
	
	
	public static int compare( DateTime first, DateTime second)	{
	    if ( first.ticks < second.ticks ) {
	        return -1;
	    }
	    else if ( first.ticks > second.ticks ) {
	        return 1;
	    }
	    else {
	        return 0;
	    }
	}
	public int compareTo( DateTime other ) {
	    if ( ticks < other.ticks ) {
	        return -1;
	    }
	    else if ( ticks > other.ticks ) {
	        return 1;
	    }
	    else {
	        return 0;
	    }
	}
	
	public DateTime addTicks( long value ) {
	    if ( value > MaxTicks - ticks || value < MinTicks - ticks ) {
	        throw new IllegalArgumentException( "value" );
	    }
	    return new DateTime( ticks + value );
	}
	
	public DateTime add( TimeSpan value ) {
	    return addTicks( value.getTicks() );
	}
	
	public DateTime addYears( int value ) 
	{
	    if ( value < -10000 || value > 10000 )
	    {
	        throw new IllegalArgumentException( "years" );
	    }
	    return addMonths( value * 12 );
	}
	
	
	public DateTime addMonths( int months ) {
	    if ( months < -120000 || months > 120000 ) {
	        throw new IllegalArgumentException( "months" );
	    }

	    var ymd = getYearMonthDay( );
	    int y = ymd.year;
	    int m = ymd.month;
	    int d = ymd.day;

	    int i = m - 1 + months;
	    if ( i >= 0 ) {
	        m = i % 12 + 1;
	        y = y + i / 12;
	    }
	    else {
	        m = 12 + ( i + 1 ) % 12;
	        y = y + ( i - 11 ) / 12;
	    }
	    if ( y < 1 || y > 9999 ) {
	        throw new IllegalArgumentException( "months" );
	    }
	    int days = daysInMonth( y, m );
	    if ( d > days ) {
	        d = days;
	    }
	    return new DateTime( dateToTicks( y, m, d ) + ticks % TicksPerDay );
	}
	
	public DateTime add( double value, int scale ) {
	    long millis = (long)( value * scale + ( value >= 0 ? 0.5 : -0.5 ) );
	    if ( millis <= -MaxMillis || millis >= MaxMillis ) {
	        throw new IllegalArgumentException( "value" );
	    }
	    return addTicks( millis * TicksPerMillisecond );
	}
	
	public DateTime addDays( double value ) {
	    return add( value, MillisPerDay );
	}

	public DateTime addHours( double value ) {
	    return add( value, MillisPerHour );
	}

	public DateTime addMinutes( double value ) {
	    return add( value, MillisPerMinute );
	}
	
	public DateTime addSeconds( double value ) {
	    return add( value, MillisPerSecond );
	}
	
	public DateTime addMilliseconds( double value ) {
	    return add( value, 1 );
	}
	
	
	public DateTime getDate( ) {
	    return new DateTime( ticks - ( ticks % TicksPerDay ) );
	}

	public int getYear( ) {
	    return datePart( DatePart.Year );
	}
	public int getMonth( ) {
	    return datePart( DatePart.Month );
	}
	public int getDay( ) {
	    return datePart( DatePart.Day );
	}
	public DayOfWeek getDayOfWeek( ) {
	    return DayOfWeek.fromValue( (int)(( ticks / TicksPerDay + 1 ) % 7) );
	}
	public int getDayOfYear( ) {
	    return datePart( DatePart.DayOfYear );
	}

	public int getHour( ) {
	    return (int)( ( ticks / TicksPerHour ) % 24 );
	}

	public int getMinute( ) {
	    return (int)( ( ticks / TicksPerMinute ) % 60 );
	}

	public int getSecond( ) {
	    return (int)( ( ticks / TicksPerSecond ) % 60 );
	}
	public int getMillisecond( ) {
	    return (int)( ( ticks / TicksPerMillisecond ) % 1000 );
	}

	public TimeSpan getTimeOfDay( ) {
	    return new TimeSpan( ticks % TicksPerDay );
	}
	
	
	
}
