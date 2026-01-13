/*
    Copyright 2024-2026 Espen Harlinn
 
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
