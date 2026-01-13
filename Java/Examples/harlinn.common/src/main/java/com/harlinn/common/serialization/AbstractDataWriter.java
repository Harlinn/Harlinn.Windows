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
package com.harlinn.common.serialization;

import java.io.ByteArrayOutputStream;
import java.nio.charset.StandardCharsets;
import java.sql.Time;
import java.time.Instant;
import java.time.Duration;
import java.util.Date;
import java.util.UUID;


import com.harlinn.common.io.BinaryWriter;
import com.harlinn.common.util.Currency;
import com.harlinn.common.util.DateTime;
import com.harlinn.common.util.TimeBase;
import com.harlinn.common.util.TimeSpan;
import com.harlinn.common.util.Guid;


public abstract class AbstractDataWriter implements BinaryWriter {

	private final byte[] zeroBytes = new byte[0];
	private final byte[] oneByte = new byte[1];
	private final byte[] twoBytes = new byte[2];
	private final byte[] threeBytes = new byte[3];
	private final byte[] fourBytes = new byte[4];
	private final byte[] fiveBytes = new byte[5];
	private final byte[] nineBytes = new byte[9];
	private final byte[] seventeenBytes = new byte[17];
	
	protected AbstractDataWriter() {
		
	}
	
	//public abstract void writeByte(byte value);
	public abstract void writeBytes( byte[] buffer, int offset, int count );
	
	public void writeBytes( byte[] buffer ) {
		writeBytes(buffer,0,buffer.length);
	}
	public void writeBytes( byte[] buffer, int count ) {
		writeBytes(buffer,0,count);
	}
	
	void Write7BitEncodedUInt64( long value )
	{
		int count = 1;
		var dest = nineBytes;
	    // Loop manually unrolled for performance:
		dest[0] = (byte)(value & 0x7F);
	    if ( value > 127 ) {
	    	count++;
	        dest[0] |= 0x80;
	        value >>>= 7;
	        dest[1] = (byte)(value & 0x7F);
	        if ( value > 127 ) {
	        	count++;
	            dest[1] |= 0x80;
	            value >>>= 7;
	            dest[2] = (byte)(value & 0x7F);

	            if ( value > 127 ) {
	            	count++;
	                dest[2] |= 0x80;
	                value >>>= 7;
	                dest[3] = (byte)(value & 0x7F);

	                if ( value > 127 ) {
	                	count++;
	                    dest[3] |= 0x80;
	                    value >>>= 7;
	                    dest[4] = (byte)(value & 0x7F);

	                    if ( value > 127 ) {
	                    	count++;
	                        dest[4] |= 0x80;
	                        value >>>= 7;
	                        dest[5] = (byte)(value & 0x7F);

	                        if ( value > 127 ) {
	                        	count++;
	                            dest[5] |= 0x80;
	                            value >>>= 7;
	                            dest[6] = (byte)(value & 0x7F);

	                            if ( value > 127 ) {
	                            	count++;
	                                dest[6] |= 0x80;
	                                value >>>= 7;
	                                dest[7] = (byte)(value & 0x7F);

	                                if ( value > 127 ) {
	                                	count++;
	                                    dest[7] |= 0x80;
	                                    value >>>= 7;
	                                    dest[8] = (byte)(value & 0xFF);
	                                }
	                            }
	                        }
	                    }
	                }
	            }
	        }
	    }
	    writeBytes(dest, count);
	}
	
	void Write7BitEncodedUInt64( long value, java.io.OutputStream stream )
	{
		int count = 1;
		var dest = nineBytes;
	    // Loop manually unrolled for performance:
		dest[0] = (byte)(value & 0x7F);
	    if ( value > 127 ) {
	    	count++;
	        dest[0] |= 0x80;
	        value >>>= 7;
	        dest[1] = (byte)(value & 0x7F);
	        if ( value > 127 ) {
	        	count++;
	            dest[1] |= 0x80;
	            value >>>= 7;
	            dest[2] = (byte)(value & 0x7F);

	            if ( value > 127 ) {
	            	count++;
	                dest[2] |= 0x80;
	                value >>>= 7;
	                dest[3] = (byte)(value & 0x7F);

	                if ( value > 127 ) {
	                	count++;
	                    dest[3] |= 0x80;
	                    value >>>= 7;
	                    dest[4] = (byte)(value & 0x7F);

	                    if ( value > 127 ) {
	                    	count++;
	                        dest[4] |= 0x80;
	                        value >>>= 7;
	                        dest[5] = (byte)(value & 0x7F);

	                        if ( value > 127 ) {
	                        	count++;
	                            dest[5] |= 0x80;
	                            value >>>= 7;
	                            dest[6] = (byte)(value & 0x7F);

	                            if ( value > 127 ) {
	                            	count++;
	                                dest[6] |= 0x80;
	                                value >>>= 7;
	                                dest[7] = (byte)(value & 0x7F);

	                                if ( value > 127 ) {
	                                	count++;
	                                    dest[7] |= 0x80;
	                                    value >>>= 7;
	                                    dest[8] = (byte)(value & 0xFF);
	                                }
	                            }
	                        }
	                    }
	                }
	            }
	        }
	    }
	    try {
		    stream.write(dest, 0, count);
	    }
	    catch(java.io.IOException exc) {
	    	throw new java.io.UncheckedIOException(exc);
	    }
	}
	
	void Write7BitEncodedInt64( long value ) {
		Write7BitEncodedUInt64( (value << 1) | (value >>> 1) );
	}
	
	
	final void writeDataType(byte value) {
		oneByte[0] = value;
		writeBytes(oneByte);
	}
	
	final void writeNull() {
		oneByte[0] = DataType.Null;
		writeBytes(oneByte);
	}
	
	final void writeByte(byte dataType, byte value) {
		twoBytes[0] = dataType;
		twoBytes[1] = value;
		writeBytes(twoBytes);
	}
	final void writeShort(byte dataType, short value) {
		threeBytes[0] = dataType;
		threeBytes[1] = (byte) (value & 0xFF);
		threeBytes[2] = (byte) ((value >>> 8) & 0xFF);
		writeBytes(threeBytes);
	}
	final void writeInt(byte dataType, int value) {
		fiveBytes[0] = dataType;
		fiveBytes[1] = (byte) (value & 0xFF);
		fiveBytes[2] = (byte) ((value >>> 8) & 0xFF);
		fiveBytes[3] = (byte) ((value >>> 16) & 0xFF);
		fiveBytes[4] = (byte) ((value >>> 24) & 0xFF);
		writeBytes(fiveBytes);
	}
	final void writeLong(byte dataType, long value) {
		nineBytes[0] = dataType;
		nineBytes[1] = (byte) (value & 0xFF);
		nineBytes[2] = (byte) ((value >>> 8) & 0xFF);
		nineBytes[3] = (byte) ((value >>> 16) & 0xFF);
		nineBytes[4] = (byte) ((value >>> 24) & 0xFF);
		nineBytes[5] = (byte) ((value >>> 32) & 0xFF);
		nineBytes[6] = (byte) ((value >>> 40) & 0xFF);
		nineBytes[7] = (byte) ((value >>> 48) & 0xFF);
		nineBytes[8] = (byte) ((value >>> 56) & 0xFF);
		writeBytes(nineBytes);
	}
	
	
	public final void writeBoolean( boolean value) {
		writeDataType( (value == false) ? DataType.BooleanFalse : DataType.BooleanTrue );
	}
	public final void writeNullableBoolean(Boolean value) {
		writeDataType( value == null? DataType.Null : (value == false ? DataType.BooleanFalse : DataType.BooleanTrue) );
	}
	
	public final void writeChar( char value ) {
		switch((short)value) {
			case 0:
				writeDataType( DataType.ZeroChar );
				break;
			case 1:
				writeDataType( DataType.OneChar );
				break;
			case (short)0xFFFF:
				writeDataType( DataType.MaxChar );
				break;
			default:
				writeShort(DataType.Char,(short)value);
				break;
				
		}
	}
	public final void writeNullableChar( Character value ) {
		if(value != null) {
			writeChar( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeUInt8( byte value ) {
		switch(value) {
			case 0:
				writeDataType( DataType.ZeroByte );
				break;
			case 1:
				writeDataType( DataType.OneByte );
				break;
			case (byte)0xFF:
				writeDataType( DataType.MaxByte );
				break;
			default:
				writeByte(DataType.Byte, value);
				break;
		}
	}
	public final void writeNullableUInt8( Byte value ) {
		if(value != null) {
			writeUInt8( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeInt8( byte value ) {
		switch(value) {
			case Byte.MIN_VALUE:
				writeDataType( DataType.MinSByte );
				break;
			case -1:
				writeDataType( DataType.MinusOneSByte );
				break;
			case 0:
				writeDataType( DataType.ZeroSByte );
				break;
			case 1:
				writeDataType( DataType.OneSByte );
				break;
			case Byte.MAX_VALUE:
				writeDataType( DataType.MaxSByte );
				break;
			default:
				writeByte( DataType.SByte, value );
				break;
		}
	}
	public final void writeNullableInt8( Byte value ) {
		if(value != null) {
			writeInt8( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeUInt16( short value ) {
		switch(value) {
			case 0:
				writeDataType( DataType.ZeroUInt16 );
				break;
			case 1:
				writeDataType( DataType.OneUInt16 );
				break;
			case (short)0xFFFF:
				writeDataType( DataType.MaxUInt16 );
				break;
			default:
				writeShort(DataType.UInt16,value );
				break;
		}
	}
	public final void writeNullableUInt16( Short value ) {
		if(value != null) {
			writeUInt16( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeInt16( short value ) {
		switch(value) {
			case Short.MIN_VALUE:
				writeDataType( DataType.MinInt16 );
				break;
			case -1:
				writeDataType( DataType.MinusOneInt16 );
				break;
			case 0:
				writeDataType( DataType.ZeroInt16 );
				break;
			case 1:
				writeDataType( DataType.OneInt16 );
				break;
			case Short.MAX_VALUE:
				writeDataType( DataType.MaxInt16 );
				break;
			default:
				writeShort(DataType.Int16,value );
				break;
		}
	}
	public final void writeNullableInt16( Short value ) {
		if(value != null) {
			writeInt16( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeUInt32( int value ) {
		switch(value) {
			case 0:
				writeDataType( DataType.ZeroUInt32 );
				break;
			case 1:
				writeDataType( DataType.OneUInt32 );
				break;
			case 0xFFFFFFFF:
				writeDataType( DataType.MaxUInt32 );
				break;
			default:
				writeInt(DataType.UInt32,value );
				break;
		}
	}
	public final void writeNullableUInt32( Integer value ) {
		if(value != null) {
			writeUInt32( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeInt32( int value ) {
		switch(value) {
			case Integer.MIN_VALUE:
				writeDataType( DataType.MinInt32 );
				break;
			case -1:
				writeDataType( DataType.MinusOneInt32 );
				break;
			case 0:
				writeDataType( DataType.ZeroInt32 );
				break;
			case 1:
				writeDataType( DataType.OneInt32 );
				break;
			case Integer.MAX_VALUE:
				writeDataType( DataType.MaxInt32 );
				break;
			default:
				writeInt(DataType.Int32,value );
				break;
		}
	}
	public final void writeNullableInt32( Integer value ) {
		if(value != null) {
			writeInt32( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeUInt64( long value ) {
		if(value == 0) {
			writeDataType( DataType.ZeroUInt64 );
		}
		else if(value == 1) {
			writeDataType( DataType.OneUInt64 );
		}
		else if(value == 0xFFFFFFFFFFFFFFFFL) {
			writeDataType( DataType.MaxUInt64 );
		}
		else {
			writeLong(DataType.UInt64, value);
		}
	}
	public final void writeNullableUInt64( Long value ) {
		if(value != null) {
			writeUInt64( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeInt64( long value ) {
		if(value == Long.MIN_VALUE) {
			writeDataType( DataType.MinInt64 );
		}
		else if(value == -1) {
			writeDataType( DataType.MinusOneInt64 );
		}
		else if(value == 0) {
			writeDataType( DataType.ZeroInt64 );
		}
		else if(value == 1) {
			writeDataType( DataType.OneInt64 );
		}
		else if(value == Long.MAX_VALUE) {
			writeDataType( DataType.MaxInt64 );
		}
		else {
			writeLong(DataType.Int64, value);
		}
	}
	public final void writeNullableInt64( Long value ) {
		if(value != null) {
			writeInt64( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeSingle( float value ) {
		if(Float.isNaN(value)) {
			writeDataType( DataType.SingleNaN );
		}
		else if(value == Float.NEGATIVE_INFINITY) {
			writeDataType( DataType.SingleNegativeInfinity );
		}
		else if(value == -Float.MAX_VALUE) {
			writeDataType( DataType.MinSingle );
		}
		else if(value == -1.f) {
			writeDataType( DataType.MinusOneSingle );
		}
		else if(value == 0.f) {
			writeDataType( DataType.ZeroSingle );
		}
		else if(value == 1.f) {
			writeDataType( DataType.OneSingle );
		}
		else if(value == Float.MAX_VALUE) {
			writeDataType( DataType.MaxSingle );
		}
		else if(value == Float.POSITIVE_INFINITY) {
			writeDataType( DataType.SinglePositiveInfinity );
		}
		else {
			writeInt(DataType.Single, Float.floatToIntBits(value));
		}
	}
	public final void writeNullableSingle( Float value ) {
		if(value != null) {
			writeSingle( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeDouble( double value ) {
		if(Double.isNaN(value)) {
			writeDataType( DataType.DoubleNaN );
		}
		else if(value == Double.NEGATIVE_INFINITY) {
			writeDataType( DataType.DoubleNegativeInfinity );
		}
		else if(value == -Double.MAX_VALUE) {
			writeDataType( DataType.MinDouble );
		}
		else if(value == -1.) {
			writeDataType( DataType.MinusOneDouble );
		}
		else if(value == 0.) {
			writeDataType( DataType.ZeroDouble );
		}
		else if(value == 1.) {
			writeDataType( DataType.OneDouble );
		}
		else if(value == Double.MAX_VALUE) {
			writeDataType( DataType.MaxDouble );
		}
		else if(value == Double.POSITIVE_INFINITY) {
			writeDataType( DataType.DoublePositiveInfinity );
		}
		else {
			writeLong(DataType.Double, Double.doubleToLongBits(value));
		}
	}
	public final void writeNullableDouble( Double value ) {
		if(value != null) {
			writeDouble( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeCurrency( Currency currencyValue ) {
		if(currencyValue == null) {
			throw new IllegalArgumentException("currencyValue cannot be null.");
		}
		var value = currencyValue.getValue();
		if(value == Long.MIN_VALUE) {
			writeDataType( DataType.MinCurrency );
		}
		else if(value == -Currency.Scale) {
			writeDataType( DataType.MinusOneCurrency );
		}
		else if(value == 0) {
			writeDataType( DataType.ZeroCurrency );
		}
		else if(value == Currency.Scale) {
			writeDataType( DataType.OneCurrency );
		}
		else if(value == Long.MAX_VALUE) {
			writeDataType( DataType.MaxCurrency );
		}
		else {
			writeLong(DataType.Currency, value);
		}
	}
	public final void writeNullableCurrency( Currency value ) {
		if(value != null) {
			writeCurrency( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeDateTime( DateTime dateTimeValue ) {
		if(dateTimeValue == null) {
			throw new IllegalArgumentException("dateTimeValue cannot be null.");
		}
		var ticks = dateTimeValue.getTicks();
		if(ticks == 0L) {
			writeDataType( DataType.ZeroDateTime );
		}
		else {
			writeLong(DataType.DateTime, ticks);
		}
	}
	public final void writeNullableDateTime( DateTime value ) {
		if(value != null) {
			writeDateTime( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeInstant( Instant instantValue ) {
		if(instantValue == null) {
			throw new IllegalArgumentException("instantValue cannot be null.");
		}
		var ticks = DateTime.toTicks(instantValue.getEpochSecond(), instantValue.getNano());
		if(ticks == 0L) {
			writeDataType( DataType.ZeroDateTime );
		}
		else {
			writeLong(DataType.DateTime, ticks);
		}
	}
	public final void writeNullableInstant( Instant value ) {
		if(value != null) {
			writeInstant( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeDate( Date dateValue ) {
		if(dateValue == null) {
			throw new IllegalArgumentException("dateValue cannot be null.");
		}
		var ticks = (dateValue.getTime() * TimeBase.TicksPerMillisecond) + TimeBase.UnixEpoch;
		if(ticks == 0L) {
			writeDataType( DataType.ZeroDateTime );
		}
		else {
			writeLong(DataType.DateTime, ticks);
		}
	}
	public final void writeNullableDate( Date value ) {
		if(value != null) {
			writeDate( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeTimeSpan( TimeSpan timeSpanValue ) {
		if(timeSpanValue == null) {
			throw new IllegalArgumentException("dateTimeValue cannot be null.");
		}
		var ticks = timeSpanValue.getTicks();
		if(ticks == 0L) {
			writeDataType( DataType.ZeroTimeSpan );
		}
		else {
			writeLong(DataType.TimeSpan, ticks);
		}
	}
	public final void writeNullableTimeSpan( TimeSpan value ) {
		if(value != null) {
			writeTimeSpan( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeDuration( Duration durationValue ) {
		if(durationValue == null) {
			throw new IllegalArgumentException("durationValue cannot be null.");
		}
		var ticks = durationValue.getSeconds() * TimeBase.TicksPerSecond + durationValue.getNano() / 100;
		if(ticks == 0L) {
			writeDataType( DataType.ZeroTimeSpan );
		}
		else {
			writeLong(DataType.TimeSpan, ticks);
		}
	}
	public final void writeNullableDuration( Duration value ) {
		if(value != null) {
			writeDuration( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeTime( Time timeValue ) {
		if(timeValue == null) {
			throw new IllegalArgumentException("timeValue cannot be null.");
		}
		var ticks = timeValue.getTime() * TimeBase.TicksPerMillisecond;
		if(ticks == 0L) {
			writeDataType( DataType.ZeroTimeSpan );
		}
		else {
			writeLong(DataType.TimeSpan, ticks);
		}
	}
	public final void writeNullableTime( Time value ) {
		if(value != null) {
			writeTime( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeGuid( Guid guidValue ) {
		if(guidValue == null) {
			throw new IllegalArgumentException("guidValue cannot be null.");
		}
		if(guidValue.isEmpty()) {
			writeDataType( DataType.EmptyGuid );
		}
		else {
			seventeenBytes[0] = DataType.Guid;
			guidValue.copyTo(seventeenBytes, 1);
			writeBytes(seventeenBytes);
		}
		
	}
	public final void writeNullableGuid( Guid value ) {
		if(value != null) {
			writeGuid( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeUUID( UUID uuidValue ) {
		if(uuidValue == null) {
			throw new IllegalArgumentException("uuidValue cannot be null.");
		}
		if(uuidValue.getMostSignificantBits() == 0L && uuidValue.getLeastSignificantBits() == 0L) {
			writeDataType( DataType.EmptyGuid );
		}
		else {
			seventeenBytes[0] = DataType.Guid;
			Guid.copyTo(uuidValue,seventeenBytes, 1);
			writeBytes(seventeenBytes);
		}
	}
	public final void writeNullableUUID( UUID value ) {
		if(value != null) {
			writeUUID( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeStringUtf8( String stringValue ) {
		if(stringValue == null) {
			throw new IllegalArgumentException("stringValue cannot be null.");
		}
		if(stringValue.length() == 0) {
			writeDataType( DataType.EmptyString );
		}
		else {
			writeDataType( DataType.StringUTF8 );
			var bytes = stringValue.getBytes(StandardCharsets.UTF_8);
			Write7BitEncodedUInt64(bytes.length);
			writeBytes(bytes);
		}
	}
	public final void writeNullableStringUtf8( String value ) {
		if(value != null) {
			writeStringUtf8( value );
		}
		else {
			writeNull();
		}
	}
	
	public final void writeStringUtf16( String stringValue ) {
		if(stringValue == null) {
			throw new IllegalArgumentException("stringValue cannot be null.");
		}
		if(stringValue.length() == 0) {
			writeDataType( DataType.EmptyString );
		}
		else {
			writeDataType( DataType.StringUTF16LE );
			var bytes = stringValue.getBytes(StandardCharsets.UTF_16LE);
			Write7BitEncodedUInt64(bytes.length);
			writeBytes(bytes);
		}
	}
	public final void writeNullableStringUtf16( String value ) {
		if(value != null) {
			writeStringUtf16( value );
		}
		else {
			writeNull();
		}
	}
	
	private final <T> void writeSize(int count, byte smallArrayDataType) {
		if(count == 0 ) {
			writeDataType((byte)(smallArrayDataType+3));
		}
		else if(count <= 0xFF) {
			writeByte(smallArrayDataType,(byte)count);
		}
		else if(count <= 0xFFFF) {
			writeShort((byte)(smallArrayDataType+1),(short)count);
		}
		else {
			writeInt((byte)(smallArrayDataType+2),count);
		}
	}
	
	
	public final void writeBooleanArray(boolean[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallBooleanArray);
		var bytes = new byte[count];
		for(int i = 0; i < count; i++) {
			bytes[i] = values[i] ? (byte)1 : (byte)0;
		}
		writeBytes(bytes);
	}
	public final void writeNullableBooleanArray(boolean[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeBooleanArray(values);
		}
	}
	
	public final void writeCharArray(char[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallCharArray);
		var bytes = new byte[count*Character.BYTES];
		for(int i = 0; i < count; i++) {
			var value = (short)values[i];
			int byteOffset = Character.BYTES * i;
			bytes[byteOffset] = (byte) (value & 0xFF);
	        bytes[byteOffset + 1] = (byte) ((value >>> 8) & 0xFF);
		}
		writeBytes(bytes);
	}
	public final void writeNullableCharArray(char[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeCharArray(values);
		}
	}
	
	public final void writeUInt8Array(byte[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallByteArray);
		writeBytes(values);
	}
	public final void writeNullableUInt8Array(byte[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeUInt8Array(values);
		}
	}
	
	public final void writeInt8Array(byte[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallSByteArray);
		writeBytes(values);
	}
	public final void writeNullableInt8Array(byte[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeInt8Array(values);
		}
	}
	
	public final void writeUInt16Array(short[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallUInt16Array);
		var bytes = new byte[count*Short.BYTES];
		for(int i = 0; i < count; i++) {
			var value = values[i];
			int byteOffset = Short.BYTES * i;
			bytes[byteOffset] = (byte) (value & 0xFF);
	        bytes[byteOffset + 1] = (byte) ((value >>> 8) & 0xFF);
		}
		writeBytes(bytes);
	}
	public final void writeNullableUInt16Array(short[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeUInt16Array(values);
		}
	}
	
	public final void writeInt16Array(short[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallInt16Array);
		var bytes = new byte[count*Short.BYTES];
		for(int i = 0; i < count; i++) {
			var value = values[i];
			int byteOffset = Short.BYTES * i;
			bytes[byteOffset] = (byte) (value & 0xFF);
	        bytes[byteOffset + 1] = (byte) ((value >>> 8) & 0xFF);
		}
		writeBytes(bytes);
	}
	public final void writeNullableInt16Array(short[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeInt16Array(values);
		}
	}
	
	public final void writeUInt32Array(int[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallUInt32Array);
		var bytes = new byte[count*Integer.BYTES];
		for(int i = 0; i < count; i++) {
			var value = values[i];
			int byteOffset = Integer.BYTES * i;
			bytes[byteOffset] = (byte) (value & 0xFF);
	        bytes[byteOffset + 1] = (byte) ((value >>> 8) & 0xFF);
	        bytes[byteOffset + 2] = (byte) ((value >>> 16) & 0xFF);
	        bytes[byteOffset + 3] = (byte) ((value >>> 24) & 0xFF);
		}
		writeBytes(bytes);
	}
	public final void writeNullableUInt32Array(int[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeUInt32Array(values);
		}
	}
	
	public final void writeInt32Array(int[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallInt32Array);
		var bytes = new byte[count*Integer.BYTES];
		for(int i = 0; i < count; i++) {
			var value = values[i];
			int byteOffset = Integer.BYTES * i;
			bytes[byteOffset] = (byte) (value & 0xFF);
	        bytes[byteOffset + 1] = (byte) ((value >>> 8) & 0xFF);
	        bytes[byteOffset + 2] = (byte) ((value >>> 16) & 0xFF);
	        bytes[byteOffset + 3] = (byte) ((value >>> 24) & 0xFF);
		}
		writeBytes(bytes);
	}
	public final void writeNullableInt32Array(int[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeInt32Array(values);
		}
	}
	
	public final void writeUInt64Array(long[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallUInt64Array);
		var bytes = new byte[count*Long.BYTES];
		for(int i = 0; i < count; i++) {
			var value = values[i];
			int byteOffset = Long.BYTES * i;
			bytes[byteOffset] = (byte) (value & 0xFF);
	        bytes[byteOffset + 1] = (byte) ((value >>> 8) & 0xFF);
	        bytes[byteOffset + 2] = (byte) ((value >>> 16) & 0xFF);
	        bytes[byteOffset + 3] = (byte) ((value >>> 24) & 0xFF);
	        bytes[byteOffset + 4] = (byte) ((value >>> 32) & 0xFF);
	        bytes[byteOffset + 5] = (byte) ((value >>> 40) & 0xFF);
	        bytes[byteOffset + 6] = (byte) ((value >>> 48) & 0xFF);
	        bytes[byteOffset + 7] = (byte) ((value >>> 56) & 0xFF);
		}
		writeBytes(bytes);
	}
	public final void writeNullableUInt64Array(long[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeUInt64Array(values);
		}
	}
	
	public final void writeInt64Array(long[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallInt64Array);
		var bytes = new byte[count*Long.BYTES];
		for(int i = 0; i < count; i++) {
			var value = values[i];
			int byteOffset = Long.BYTES * i;
			bytes[byteOffset] = (byte) (value & 0xFF);
	        bytes[byteOffset + 1] = (byte) ((value >>> 8) & 0xFF);
	        bytes[byteOffset + 2] = (byte) ((value >>> 16) & 0xFF);
	        bytes[byteOffset + 3] = (byte) ((value >>> 24) & 0xFF);
	        bytes[byteOffset + 4] = (byte) ((value >>> 32) & 0xFF);
	        bytes[byteOffset + 5] = (byte) ((value >>> 40) & 0xFF);
	        bytes[byteOffset + 6] = (byte) ((value >>> 48) & 0xFF);
	        bytes[byteOffset + 7] = (byte) ((value >>> 56) & 0xFF);
		}
		writeBytes(bytes);
	}
	public final void writeNullableInt64Array(long[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeInt64Array(values);
		}
	}
	
	public final void writeSingleArray(float[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallSingleArray);
		var bytes = new byte[count*Integer.BYTES];
		for(int i = 0; i < count; i++) {
			var value = Float.floatToIntBits( values[i] );
			int byteOffset = Float.BYTES * i;
			bytes[byteOffset] = (byte) (value & 0xFF);
	        bytes[byteOffset + 1] = (byte) ((value >>> 8) & 0xFF);
	        bytes[byteOffset + 2] = (byte) ((value >>> 16) & 0xFF);
	        bytes[byteOffset + 3] = (byte) ((value >>> 24) & 0xFF);
		}
		writeBytes(bytes);
	}
	public final void writeNullableSingleArray(float[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeSingleArray(values);
		}
	}
	
	public final void writeDoubleArray(double[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallDoubleArray);
		var bytes = new byte[count*Double.BYTES];
		for(int i = 0; i < count; i++) {
			var value = Double.doubleToLongBits( values[i] );
			int byteOffset = Double.BYTES * i;
			bytes[byteOffset] = (byte) (value & 0xFF);
	        bytes[byteOffset + 1] = (byte) ((value >>> 8) & 0xFF);
	        bytes[byteOffset + 2] = (byte) ((value >>> 16) & 0xFF);
	        bytes[byteOffset + 3] = (byte) ((value >>> 24) & 0xFF);
	        bytes[byteOffset + 4] = (byte) ((value >>> 32) & 0xFF);
	        bytes[byteOffset + 5] = (byte) ((value >>> 40) & 0xFF);
	        bytes[byteOffset + 6] = (byte) ((value >>> 48) & 0xFF);
	        bytes[byteOffset + 7] = (byte) ((value >>> 56) & 0xFF);
		}
		writeBytes(bytes);
	}
	public final void writeNullableDoubleArray(double[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeDoubleArray(values);
		}
	}
	
	public final void writeDateTimeArray(DateTime[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallDateTimeArray);
		var bytes = new byte[count*DateTime.BYTES];
		for(int i = 0; i < count; i++) {
			
			var value = values[i] != null ? values[i].getTicks() : 0L;
			int byteOffset = DateTime.BYTES * i;
			bytes[byteOffset] = (byte) (value & 0xFF);
	        bytes[byteOffset + 1] = (byte) ((value >>> 8) & 0xFF);
	        bytes[byteOffset + 2] = (byte) ((value >>> 16) & 0xFF);
	        bytes[byteOffset + 3] = (byte) ((value >>> 24) & 0xFF);
	        bytes[byteOffset + 4] = (byte) ((value >>> 32) & 0xFF);
	        bytes[byteOffset + 5] = (byte) ((value >>> 40) & 0xFF);
	        bytes[byteOffset + 6] = (byte) ((value >>> 48) & 0xFF);
	        bytes[byteOffset + 7] = (byte) ((value >>> 56) & 0xFF);
		}
		writeBytes(bytes);
	}
	public final void writeNullableDateTimeArray(DateTime[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeDateTimeArray(values);
		}
	}
	
	public final void writeTimeSpanArray(TimeSpan[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallTimeSpanArray);
		var bytes = new byte[count*TimeSpan.BYTES];
		for(int i = 0; i < count; i++) {
			
			var value = values[i] != null ? values[i].getTicks() : 0L;
			int byteOffset = TimeSpan.BYTES * i;
			bytes[byteOffset] = (byte) (value & 0xFF);
	        bytes[byteOffset + 1] = (byte) ((value >>> 8) & 0xFF);
	        bytes[byteOffset + 2] = (byte) ((value >>> 16) & 0xFF);
	        bytes[byteOffset + 3] = (byte) ((value >>> 24) & 0xFF);
	        bytes[byteOffset + 4] = (byte) ((value >>> 32) & 0xFF);
	        bytes[byteOffset + 5] = (byte) ((value >>> 40) & 0xFF);
	        bytes[byteOffset + 6] = (byte) ((value >>> 48) & 0xFF);
	        bytes[byteOffset + 7] = (byte) ((value >>> 56) & 0xFF);
		}
		writeBytes(bytes);
	}
	public final void writeNullableTimeSpanArray(TimeSpan[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeTimeSpanArray(values);
		}
	}
	
	public final void writeGuidArray(Guid[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallGuidArray);
		var bytes = new byte[count*Guid.BYTES];
		for(int i = 0; i < count; i++) {
			var value = values[i];
			if(value != null) {
				int byteOffset = Guid.BYTES * i;
				var a = value.getA();
				bytes[byteOffset] = (byte) (a & 0xFF);
		        bytes[byteOffset + 1] = (byte) ((a >>> 8) & 0xFF);
		        bytes[byteOffset + 2] = (byte) ((a >>> 16) & 0xFF);
		        bytes[byteOffset + 3] = (byte) ((a >>> 24) & 0xFF);
		        
		        var b = value.getB();
		        bytes[byteOffset + 4] = (byte) (b & 0xFF);
		        bytes[byteOffset + 5] = (byte) ((b >>> 8) & 0xFF);
		        
		        var c = value.getC();
		        bytes[byteOffset + 6] = (byte) (c & 0xFF);
		        bytes[byteOffset + 7] = (byte) ((c >>> 8) & 0xFF);
		        
		        bytes[byteOffset + 8] = value.getD();
		        bytes[byteOffset + 9] = value.getE();
		        bytes[byteOffset + 10] = value.getF();
		        bytes[byteOffset + 11] = value.getG();
		        bytes[byteOffset + 12] = value.getH();
		        bytes[byteOffset + 13] = value.getI();
		        bytes[byteOffset + 14] = value.getJ();
		        bytes[byteOffset + 15] = value.getK();
			}
		}
		writeBytes(bytes);
	}
	public final void writeNullableGuidArray(Guid[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeGuidArray(values);
		}
	}
	
	public final void writeStringArray(String[] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallStringArray);
		ByteArrayOutputStream stream = new ByteArrayOutputStream();
		try {
			for(int i = 0; i < count; i++) {
				var value = values[i];
				if(value != null) {
					var bytes = value.getBytes(StandardCharsets.UTF_8);
					Write7BitEncodedUInt64(bytes.length,stream);
					stream.write(bytes);
				}
				else {
					oneByte[0] = 0;
					stream.write(oneByte);
				}
				
			}
		}
		catch(java.io.IOException exc) {
			throw new java.io.UncheckedIOException(exc);
		}
		writeBytes(stream.toByteArray());
	}
	public final void writeNullableStringArray(String[] values ) {
		if(values == null) {
			writeNull();
		}
		else {
			writeStringArray(values);
		}
	}
	
	// zeroBytes
	public final void writeUInt8ListArray(byte[][] values ) {
		assert values != null : "values cannot be null";
		var count = values.length; 
		writeSize(count, DataType.SmallByteArrayList);
		
		for(int i = 0; i < count; i++) {
			var value = values[i];
			if(value != null) {
				writeUInt8Array(value);
			}
			else {
				writeUInt8Array(zeroBytes);
			}
		}
	}
	public final void writeNullableUInt8ListArray(byte[][] values) {
		if(values == null) {
			writeNull();
		}
		else {
			writeUInt8ListArray(values);
		}
	}
}
