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
package com.harlinn.common.io;

import java.sql.Time;
import java.time.Instant;
import java.time.Duration;
import java.util.Date;
import java.util.UUID;

import com.harlinn.common.util.Currency;
import com.harlinn.common.util.DateTime;
import com.harlinn.common.util.TimeSpan;
import com.harlinn.common.util.Guid;

public interface BinaryWriter {
	void writeBoolean( boolean value);
	void writeNullableBoolean(Boolean value);
	
	void writeChar( char value );
	void writeNullableChar( Character value );
	
	void writeUInt8( byte value );
	void writeNullableUInt8( Byte value );
	
	void writeInt8( byte value );
	void writeNullableInt8( Byte value );
	
	void writeUInt16( short value );
	void writeNullableUInt16( Short value );
	
	void writeInt16( short value );
	void writeNullableInt16( Short value );
	
	void writeUInt32( int value );
	void writeNullableUInt32( Integer value );
	
	void writeInt32( int value );
	void writeNullableInt32( Integer value );
	
	void writeUInt64( long value );
	void writeNullableUInt64( Long value );
	
	void writeInt64( long value );
	void writeNullableInt64( Long value );
	
	void writeSingle( float value );
	void writeNullableSingle( Float value );
	
	void writeDouble( double value );
	void writeNullableDouble( Double value );
	
	void writeCurrency( Currency value );
	void writeNullableCurrency( Currency value );
	
	void writeDateTime( DateTime value );
	void writeNullableDateTime( DateTime value );
	
	void writeInstant( Instant value );
	void writeNullableInstant( Instant value );
	
	void writeDate( Date value );
	void writeNullableDate( Date value );
	
	void writeTimeSpan( TimeSpan value );
	void writeNullableTimeSpan( TimeSpan value );
	
	void writeDuration( Duration value );
	void writeNullableDuration( Duration value );
	
	void writeTime( Time value );
	void writeNullableTime( Time value );
	
	void writeGuid( Guid value );
	void writeNullableGuid( Guid value );
	
	void writeUUID( UUID value );
	void writeNullableUUID( UUID value );
	
	void writeStringUtf8( String value );
	void writeNullableStringUtf8( String value );
	
	void writeStringUtf16( String value );
	void writeNullableStringUtf16( String value );
	
	void writeBooleanArray(boolean[] values );
	void writeNullableBooleanArray(boolean[] values );
	
	void writeCharArray(char[] values );
	void writeNullableCharArray(char[] values );
	
	void writeUInt8Array(byte[] values );
	void writeNullableUInt8Array(byte[] values );
	
	void writeInt8Array(byte[] values );
	void writeNullableInt8Array(byte[] values );
	
	void writeUInt16Array(short[] values );
	void writeNullableUInt16Array(short[] values );
	
	void writeInt16Array(short[] values );
	void writeNullableInt16Array(short[] values );
	
	void writeUInt32Array(int[] values );
	void writeNullableUInt32Array(int[] values );
	
	void writeInt32Array(int[] values );
	void writeNullableInt32Array(int[] values );
	
	void writeUInt64Array(long[] values );
	void writeNullableUInt64Array(long[] values );
	
	void writeInt64Array(long[] values );
	void writeNullableInt64Array(long[] values );
	
	void writeSingleArray(float[] values );
	void writeNullableSingleArray(float[] values );
	
	void writeDoubleArray(double[] values );
	void writeNullableDoubleArray(double[] values );
	
	void writeDateTimeArray(DateTime[] values );
	void writeNullableDateTimeArray(DateTime[] values );
	
	void writeTimeSpanArray(TimeSpan[] values );
	void writeNullableTimeSpanArray(TimeSpan[] values );
	
	void writeGuidArray(Guid[] values );
	void writeNullableGuidArray(Guid[] values );
	
	void writeStringArray(String[] values );
	void writeNullableStringArray(String[] values );
	
	void writeUInt8ListArray(byte[][] values );
	void writeNullableUInt8ListArray(byte[][] values );
	
}
