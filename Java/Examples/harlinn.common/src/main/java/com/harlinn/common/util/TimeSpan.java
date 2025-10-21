package com.harlinn.common.util;

import java.io.Serializable;

/**
 * Represents a time interval.
 */
public class TimeSpan extends TimeBase implements Comparable<TimeSpan>, Serializable, Cloneable {
	public static final int BYTES = 8;
	
	private static final long serialVersionUID = 4876775050401345933L;
	
	long ticks;
	
	public TimeSpan() {
	}
	
	public TimeSpan(long ticks) {
		this.ticks = ticks;
	}
	
	TimeSpan( int hours, int minutes, int seconds ) {
		this.ticks = timeToTicks( 0, hours, minutes, seconds, 0 );
    }

	TimeSpan( int days, int hours, int minutes, int seconds ) {
		this.ticks = timeToTicks( days, hours, minutes, seconds, 0 );
	}
	
	TimeSpan( int days, int hours, int minutes, int seconds, int milliseconds )	{
		this.ticks = timeToTicks( days, hours, minutes, seconds, milliseconds );
	}
	
	@Override
	public boolean equals(Object obj) {
		if ( this == obj ) {
			return true;
		}
		if(obj == null ) {
			return false;
		}
		if ((obj instanceof TimeSpan) == false ) {
            return false;
        }
		var other = (TimeSpan)obj;
		return other.ticks == this.ticks; 
	}
	

	@Override
	public Object clone() throws CloneNotSupportedException {
		return new TimeSpan(ticks);
	}
	
	
	static long timeToTicks( int days, int hours, int minutes, int seconds, int milliseconds ) {
		long totalMilliSeconds = (((long)days) * 3600L * 24L +
				((long) hours ) * 3600L +
						((long)minutes ) * 60L + seconds)  * 1000L + milliseconds;

		if ( totalMilliSeconds > MaxMilliSeconds || totalMilliSeconds < MinMilliSeconds )
		{
		    throw new IllegalArgumentException();
		}
		long result = totalMilliSeconds * TicksPerMillisecond;
		return result;
	}
	
	static TimeSpan interval( double value, int scale ) {
	    if ( Double.isNaN( value ) )
	    {
	        throw new IllegalArgumentException( );
	    }
	    double milliSeconds = value * scale;
	    milliSeconds = milliSeconds + ( value >= 0 ? 0.5 : -0.5 );

	    if ( ( milliSeconds > (double)(Long.MAX_VALUE / TicksPerMillisecond) ) || ( milliSeconds < (double)(Long.MIN_VALUE / TicksPerMillisecond) ) )
	    {
	        throw new ArithmeticException( );
	    }
	    return new TimeSpan( (long)milliSeconds * TicksPerMillisecond );
	}
	
	
	public long hash() {
		var x = ( ticks ^ ( ticks >>> 30 ) ) * 0xbf58476d1ce4e5b9L;
		x = ( x ^ ( x >>> 27 ) ) * 0x94d049bb133111ebL;
		x = x ^ ( x >>> 31 );
		return x;
	}
	
	@Override
	public int hashCode() {
		return (int)hash();
	}
	
	public long getTicks( ) {
	    return ticks;
	}

	public int getDays( ) {
	    return (int)( ticks / TicksPerDay );
	}

	public int getHours( ) {
	    return (int)( ( ticks / TicksPerHour ) % 24 );
	}

	public int getMilliseconds( ) {
	    return (int)( ( ticks / TicksPerMillisecond ) % 1000 );
	}

	public int getMinutes( ) {
	    return (int)( ( ticks / TicksPerMinute ) % 60 );
	}

	public int getSeconds( ) {
	    return (int)( ( ticks / TicksPerSecond ) % 60 );
	}

	public long toSeconds( ) {
	    return ticks / TicksPerSecond;
	}

	public double totalDays( ) {
	    return ( (double) ticks ) / ( (double) TicksPerDay );
	}

	public double totalHours( ) {
		return ( (double) ticks ) / ( (double) TicksPerHour );
	}

	public long toMilliseconds( ) {
	    return ticks / TicksPerMillisecond;
	}

	public double totalMilliseconds( ) {
	    var result = ticks / TicksPerMillisecond;
	    if ( result > MaxMilliSeconds ) {
	        return (double)MaxMilliSeconds;
	    }

	    if ( result < MinMilliSeconds ) {
	    	return (double)MinMilliSeconds;
	    }

	    return (double)result;
	}

	public long toMicroseconds( ) {
	    return ticks / TicksPerMicrosecond;
	}


	public double totalMinutes( ) {
		return ( (double) ticks ) / ( (double) TicksPerMinute );
	}

	public double totalSeconds( ) 
	{
		return ( (double) ticks ) / ( (double) TicksPerSecond );
	}

	public TimeSpan add( TimeSpan other ) {
	    return new TimeSpan( ticks + other.ticks );
	}

	public static int compare( TimeSpan t1, TimeSpan t2 ) {
	    if ( t1.ticks > t2.ticks ) {
	        return 1;
	    }
	    if ( t1.ticks < t2.ticks ) {
	        return -1;
	    }
	    return 0;
	}

	public int compareTo( TimeSpan other ) {
	    if ( ticks > other.ticks ) {
	        return 1;
	    }
	    if ( ticks < other.ticks ) {
	        return -1;
	    }
	    return 0;
	}

	public static TimeSpan fromDays( double value )
	{
	    return interval( value, MillisPerDay );
	}

	public TimeSpan duration( ) {
		return ticks >= 0 ? this : new TimeSpan(-ticks); 
	}


	public static TimeSpan fromHours( double value ) {
	    return interval( value, MillisPerHour );
	}

	public static TimeSpan fromMilliseconds( double value )	{
	    return interval( value, 1 );
	}

	public static TimeSpan fromMinutes( double value ) {
	    return interval( value, MillisPerMinute );
	}

	public TimeSpan negate( ) {
	    return new TimeSpan( -ticks );
	}

	public static TimeSpan fromSeconds( double value ) {
	    return interval( value, MillisPerSecond );
	}

	public TimeSpan subtract( TimeSpan other ) {
	    return new TimeSpan( ticks - other.ticks );
	}

	public static TimeSpan fromTicks( long value )
	{
	    return new TimeSpan( value );
	}
	
	
}
