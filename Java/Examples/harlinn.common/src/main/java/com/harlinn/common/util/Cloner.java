package com.harlinn.common.util;

public class Cloner {
	public static boolean Clone( boolean value ) {
		return value;
	}
	public static Boolean Clone( Boolean value ) {
		return value;
	}
	public static char Clone( char value ) {
		return value;
	}
	public static Character Clone( Character value ) {
		return value;
	}
	public static byte Clone( byte value ) {
		return value;
	}
	public static Byte Clone( Byte value ) {
		return value;
	}
	public static short Clone( short value ) {
		return value;
	}
	public static int Clone( int value ) {
		return value;
	}
	public static Integer Clone( Integer value ) {
		return value;
	}
	public static long Clone( long value ) {
		return value;
	}
	public static Long Clone( Long value ) {
		return value;
	}
	public static float Clone( float value ) {
		return value;
	}
	public static Float Clone( Float value ) {
		return value;
	}
	public static Double Clone( Double value ) {
		return value;
	}
	public static DateTime Clone( DateTime value ) {
		return value;
	}
	public static TimeSpan Clone( TimeSpan value ) {
		return value;
	}
	public static Guid Clone( Guid value ) {
		return value;
	}
	public static Currency Clone( Currency value ) {
		return value;
	}
	public static String Clone( String value ) {
		return value;
	}
	public static byte[] Clone( byte[] value ) {
		if(value != null) {
			return value.clone();
		}
		return value;
	}
	
}
