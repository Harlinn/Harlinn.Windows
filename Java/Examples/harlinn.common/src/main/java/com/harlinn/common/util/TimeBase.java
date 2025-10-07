package com.harlinn.common.util;

public abstract class TimeBase {
	public static final long TicksPerMicrosecond = 10;
	public static final long TicksPerMillisecond = 10000;
	public static final long TicksPerSecond = TicksPerMillisecond * 1000;
	public static final long TicksPerMinute = TicksPerSecond * 60;
	public static final long TicksPerHour = TicksPerMinute * 60;

	public static final long TicksPerDay = TicksPerHour * 24;

	public static final long TicksPerYear = TicksPerDay * 365;

	public static final double MillisecondsPerTick = 1.0 / TicksPerMillisecond;

	public static final double SecondsPerTick = 1.0 / TicksPerSecond;

	public static final double MinutesPerTick = 1.0 / TicksPerMinute;

	public static final double HoursPerTick = 1.0 / TicksPerHour;

	public static final double DaysPerTick = 1.0 / TicksPerDay;

	public static final double OADateMinAsDouble =  -657435.0;

	public static final double OADateMaxAsDouble = 2958466.0;

	public static final int[] DaysToMonth365 = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

	public static final int[] DaysToMonth366 = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };


	public static final int MillisPerSecond = 1000;

	public static final int MillisPerMinute = MillisPerSecond * 60;

	public static final int MillisPerHour = MillisPerMinute * 60;

	public static final int MillisPerDay = MillisPerHour * 24;


	public static final long MaxSeconds = Long.MAX_VALUE / TicksPerSecond;

	public static final long MinSeconds = Long.MIN_VALUE / TicksPerSecond;


	public static final long MaxMilliSeconds = Long.MAX_VALUE / TicksPerMillisecond;

	public static final long MinMilliSeconds = Long.MIN_VALUE / TicksPerMillisecond;

	public static final long UnixEpoch = 621355968000000000L;
	public static final long NtpEpoch = UnixEpoch - ( 2208988800L * TicksPerSecond );


	public static final int DaysPerYear= 365;

	public static final int DaysPer4Years = DaysPerYear * 4 + 1;

	public static final int DaysPer100Years = DaysPer4Years * 25 - 1;

	public static final int DaysPer400Years = DaysPer100Years * 4 + 1;


	public static final int DaysTo1601 = DaysPer400Years * 4;

	public static final int DaysTo1899 = DaysPer400Years * 4 + DaysPer100Years * 3 - 367;

	public static final int DaysTo10000 = DaysPer400Years * 25 - 366;


	public static final long MinTicks = 0;

	public static final long MaxTicks = DaysTo10000 * TicksPerDay - 1;

	public static final long MaxMillis = ((long)DaysTo10000 )* MillisPerDay;


	public static final long FileTimeOffset = ((long)DaysTo1601 ) * TicksPerDay;

	public static final long DoubleDateOffset = ((long)DaysTo1899 ) * TicksPerDay;

	public static final long OADateMinAsTicks = (((long)DaysPer100Years ) - DaysPerYear ) * TicksPerDay;
}
