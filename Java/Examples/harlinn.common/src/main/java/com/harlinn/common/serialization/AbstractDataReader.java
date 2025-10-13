package com.harlinn.common.serialization;


import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.sql.Time;
import java.time.Duration;
import java.time.Instant;
import java.util.Date;
import java.util.UUID;

import com.harlinn.common.util.Currency;
import com.harlinn.common.util.DateTime;
import com.harlinn.common.util.Guid;
import com.harlinn.common.util.TimeBase;
import com.harlinn.common.util.TimeSpan;
import com.harlinn.common.io.BinaryReader;

public abstract class AbstractDataReader implements BinaryReader {
	
	private final byte[] sixteenBytes = new byte[16]; 
	
	protected AbstractDataReader() {
		
	}
	
	protected abstract byte readByte( );
	protected abstract ByteBuffer readBuffer( int size );
	
	public final long Read7BitEncodedUInt64( ) {
	    long resultValue = 0;
	    byte byteValue = readByte( );
	    resultValue = byteValue & 0x7F;
	    if ( (byteValue & (byte)0x80) != 0 ) {
	    	byteValue = readByte( );
	        resultValue |= ((long)( byteValue & 0x7F )) << 7;
	        if ( (byteValue & (byte)0x80) != 0 ) {
	        	byteValue = readByte( );
	            resultValue |= ((long)( byteValue & 0x7F )) << 14;
	            if ( (byteValue & (byte)0x80) != 0 ) {
	            	byteValue = readByte( );
	                resultValue |= ((long)( byteValue & 0x7F )) << 21;
	                if ( (byteValue & (byte)0x80) != 0 ) {
	                	byteValue = readByte( );
	                    resultValue |= ((long)( byteValue & 0x7F )) << 28;
	                    if ( (byteValue & (byte)0x80) != 0 ) {
	                    	byteValue = readByte( );
	                        resultValue |= ((long)( byteValue & 0x7F )) << 35;
	                        if ( (byteValue & (byte)0x80) != 0 ) {
	                        	byteValue = readByte( );
	                            resultValue |= ((long)( byteValue & 0x7F )) << 42;
	                            if ( (byteValue & (byte)0x80) != 0 ) {
	                            	byteValue = readByte( );
	                                resultValue |= ((long)( byteValue & 0x7F )) << 49;
	                                if ( (byteValue & (byte)0x80) != 0 ) {
	                                	byteValue = readByte( );
	                                    resultValue |= ((long)( byteValue & 0x7F )) << 56;
	                                }
	                            }
	                        }
	                    }
	                }
	            }
	        }
	    }
	    return resultValue;
	}
	
	public final long Read7BitEncodedInt64( ) {
	    long resVal = Read7BitEncodedUInt64( );
	    long resultValue = ( resVal >>> 1 ) | ( resVal << 63 );
	    return resultValue;
	}
	
	
	
	
	private final byte readDataType() {
		return readByte( );
	}
	
	public final boolean readBoolean( ) {
		var dataType = readDataType();
		switch (dataType) {
		    case DataType.BooleanFalse:
		        return false;
		    case DataType.BooleanTrue:
		        return true;
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Boolean readNullableBoolean( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
		    case DataType.BooleanFalse:
		        return false;
		    case DataType.BooleanTrue:
		        return true;
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final char readChar( ) {
		var dataType = readDataType();
		switch (dataType) {
		    case DataType.ZeroChar:
		        return (char)0;
		    case DataType.OneChar:
		    	return (char)1;
		    case DataType.MaxChar:
		    	return (char)0xFFFF;
		    case DataType.Char:
		    	var buffer = readBuffer(2);
		    	var charBuffer = buffer.asCharBuffer();
		    	return charBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Character readNullableChar( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
		    case DataType.ZeroChar:
		        return (char)0;
		    case DataType.OneChar:
		    	return Character.valueOf((char)1);
		    case DataType.MaxChar:
		    	return Character.valueOf((char)0xFFFF);
		    case DataType.Char:
		    	var buffer = readBuffer(2);
		    	var charBuffer = buffer.asCharBuffer();
		    	return charBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final byte readUInt8( ) {
		var dataType = readDataType();
		switch (dataType) {
		    case DataType.ZeroByte:
		        return (byte)0;
		    case DataType.OneByte:
		    	return (byte)1;
		    case DataType.MaxByte:
		    	return (byte)0xFF;
		    case DataType.Byte:
		    	var value = readByte( );
		    	return value;
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Byte readNullableUInt8( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
		    case DataType.ZeroByte:
		        return (byte)0;
		    case DataType.OneByte:
		    	return (byte)1;
		    case DataType.MaxByte:
		    	return (byte)0xFF;
		    case DataType.Byte:
		    	var value = readByte( );
		    	return value;
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final byte readInt8( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.MinSByte:
		        return Byte.MIN_VALUE;
			case DataType.MinusOneSByte:
		    	return (byte)-1;
		    case DataType.ZeroSByte:
		        return (byte)0;
		    case DataType.OneSByte:
		    	return (byte)1;
		    case DataType.MaxSByte:
		    	return Byte.MAX_VALUE;
		    case DataType.SByte:
		    	var value = readByte( );
		    	return value;
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Byte readNullableInt8( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
			case DataType.MinSByte:
		        return Byte.MIN_VALUE;
			case DataType.MinusOneSByte:
		    	return (byte)-1;
		    case DataType.ZeroSByte:
		        return (byte)0;
		    case DataType.OneSByte:
		    	return (byte)1;
		    case DataType.MaxSByte:
		    	return Byte.MAX_VALUE;
		    case DataType.SByte:
		    	var value = readByte( );
		    	return value;
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final short readUInt16( ) {
		var dataType = readDataType();
		switch (dataType) {
		    case DataType.ZeroUInt16:
		        return (short)0;
		    case DataType.OneUInt16:
		    	return (short)1;
		    case DataType.MaxUInt16:
		    	return (short)0xFFFF;
		    case DataType.Byte:
		    	var buffer = readBuffer(2);
		    	var shortBuffer = buffer.asShortBuffer();
		    	return shortBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Short readNullableUInt16( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
		    case DataType.ZeroUInt16:
		        return (short)0;
		    case DataType.OneUInt16:
		    	return (short)1;
		    case DataType.MaxUInt16:
		    	return (short)0xFFFF;
		    case DataType.UInt16:
		    	var buffer = readBuffer(2);
		    	var shortBuffer = buffer.asShortBuffer();
		    	return shortBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final short readInt16( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.MinInt16:
		        return Short.MIN_VALUE;
			case DataType.MinusOneInt16:
		    	return (short)-1;
		    case DataType.ZeroInt16:
		        return (short)0;
		    case DataType.OneInt16:
		    	return (short)1;
		    case DataType.MaxInt16:
		    	return Short.MAX_VALUE;
		    case DataType.Int16:
		    	var buffer = readBuffer(2);
		    	var shortBuffer = buffer.asShortBuffer();
		    	return shortBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Short readNullableInt16( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
			case DataType.MinInt16:
		        return Short.MIN_VALUE;
			case DataType.MinusOneInt16:
		    	return (short)-1;
		    case DataType.ZeroInt16:
		        return (short)0;
		    case DataType.OneInt16:
		    	return (short)1;
		    case DataType.MaxInt16:
		    	return Short.MAX_VALUE;
		    case DataType.Int16:
		    	var buffer = readBuffer(2);
		    	var shortBuffer = buffer.asShortBuffer();
		    	return shortBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final int readUInt32( ) {
		var dataType = readDataType();
		switch (dataType) {
		    case DataType.ZeroUInt32:
		        return (int)0;
		    case DataType.OneUInt32:
		    	return (int)1;
		    case DataType.MaxUInt32:
		    	return (int)0xFFFFFFFF;
		    case DataType.Byte:
		    	var buffer = readBuffer(4);
		    	var intBuffer = buffer.asIntBuffer();
		    	return intBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Integer readNullableUInt32( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
		    case DataType.ZeroUInt32:
		        return (int)0;
		    case DataType.OneUInt32:
		    	return (int)1;
		    case DataType.MaxUInt32:
		    	return (int)0xFFFFFFFF;
		    case DataType.UInt32:
		    	var buffer = readBuffer(4);
		    	var intBuffer = buffer.asIntBuffer();
		    	return intBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final int readInt32( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.MinInt32:
		        return Integer.MIN_VALUE;
			case DataType.MinusOneInt32:
		    	return (int)-1;
		    case DataType.ZeroInt32:
		        return (int)0;
		    case DataType.OneInt32:
		    	return (int)1;
		    case DataType.MaxInt32:
		    	return Integer.MAX_VALUE;
		    case DataType.Int32:
		    	var buffer = readBuffer(4);
		    	var intBuffer = buffer.asIntBuffer();
		    	return intBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Integer readNullableInt32( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
			case DataType.MinInt32:
		        return Integer.MIN_VALUE;
			case DataType.MinusOneInt32:
		    	return (int)-1;
		    case DataType.ZeroInt32:
		        return (int)0;
		    case DataType.OneInt32:
		    	return (int)1;
		    case DataType.MaxInt32:
		    	return Integer.MAX_VALUE;
		    case DataType.Int32:
		    	var buffer = readBuffer(4);
		    	var intBuffer = buffer.asIntBuffer();
		    	return intBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	
	public final long readUInt64( ) {
		var dataType = readDataType();
		switch (dataType) {
		    case DataType.ZeroUInt64:
		        return (long)0;
		    case DataType.OneUInt64:
		    	return (long)1;
		    case DataType.MaxUInt64:
		    	return (long)0xFFFFFFFF;
		    case DataType.Byte:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	return longBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Long readNullableUInt64( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
		    case DataType.ZeroUInt64:
		        return (long)0;
		    case DataType.OneUInt64:
		    	return (long)1;
		    case DataType.MaxUInt64:
		    	return (long)0xFFFFFFFF;
		    case DataType.UInt64:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	return longBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final long readInt64( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.MinInt64:
		        return Long.MIN_VALUE;
			case DataType.MinusOneInt64:
		    	return (long)-1;
		    case DataType.ZeroInt64:
		        return (long)0;
		    case DataType.OneInt64:
		    	return (long)1;
		    case DataType.MaxInt64:
		    	return Long.MAX_VALUE;
		    case DataType.Int64:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	return longBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Long readNullableInt64( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
			case DataType.MinInt64:
		        return Long.MIN_VALUE;
			case DataType.MinusOneInt64:
		    	return (long)-1;
		    case DataType.ZeroInt64:
		        return (long)0;
		    case DataType.OneInt64:
		    	return (long)1;
		    case DataType.MaxInt64:
		    	return Long.MAX_VALUE;
		    case DataType.Int64:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	return longBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	
	public final float readSingle( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.SingleNegativeInfinity:
				return Float.NEGATIVE_INFINITY;
			case DataType.MinSingle:
		        return -Float.MAX_VALUE;
			case DataType.MinusOneSingle:
		    	return -1.f;
		    case DataType.ZeroSingle:
		        return 0.f;
		    case DataType.OneSingle:
		    	return 1.f;
		    case DataType.MaxSingle:
		    	return Float.MAX_VALUE;
		    case DataType.SinglePositiveInfinity:
		    	return Float.POSITIVE_INFINITY;
		    case DataType.SingleNaN:
		    	return Float.NaN;
		    case DataType.Single:
		    	var buffer = readBuffer(4);
		    	var floatBuffer = buffer.asFloatBuffer();
		    	return floatBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Float readNullableSingle( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
			case DataType.SingleNegativeInfinity:
				return Float.NEGATIVE_INFINITY;
			case DataType.MinSingle:
		        return -Float.MAX_VALUE;
			case DataType.MinusOneSingle:
		    	return -1.f;
		    case DataType.ZeroSingle:
		        return 0.f;
		    case DataType.OneSingle:
		    	return 1.f;
		    case DataType.MaxSingle:
		    	return Float.MAX_VALUE;
		    case DataType.SinglePositiveInfinity:
		    	return Float.POSITIVE_INFINITY;
		    case DataType.SingleNaN:
		    	return Float.NaN;
		    case DataType.Single:
		    	var buffer = readBuffer(4);
		    	var floatBuffer = buffer.asFloatBuffer();
		    	return floatBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final double readDouble( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.DoubleNegativeInfinity:
				return Double.NEGATIVE_INFINITY;
			case DataType.MinDouble:
		        return -Double.MAX_VALUE;
			case DataType.MinusOneDouble:
		    	return -1.;
		    case DataType.ZeroDouble:
		        return 0.;
		    case DataType.OneDouble:
		    	return 1.;
		    case DataType.MaxDouble:
		    	return Double.MAX_VALUE;
		    case DataType.DoublePositiveInfinity:
		    	return Double.POSITIVE_INFINITY;
		    case DataType.DoubleNaN:
		    	return Double.NaN;
		    case DataType.Double:
		    	var buffer = readBuffer(8);
		    	var doubleBuffer = buffer.asDoubleBuffer();
		    	return doubleBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Double readNullableDouble( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
			case DataType.DoubleNegativeInfinity:
				return Double.NEGATIVE_INFINITY;
			case DataType.MinDouble:
		        return -Double.MAX_VALUE;
			case DataType.MinusOneDouble:
		    	return -1.;
		    case DataType.ZeroDouble:
		        return 0.;
		    case DataType.OneDouble:
		    	return 1.;
		    case DataType.MaxDouble:
		    	return Double.MAX_VALUE;
		    case DataType.DoublePositiveInfinity:
		    	return Double.POSITIVE_INFINITY;
		    case DataType.DoubleNaN:
		    	return Double.NaN;
		    case DataType.Double:
		    	var buffer = readBuffer(8);
		    	var doubleBuffer = buffer.asDoubleBuffer();
		    	return doubleBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	
	public final Currency readCurrency( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.MinCurrency:
		        return Currency.fromValue( Long.MIN_VALUE );
			case DataType.MinusOneCurrency:
		    	return new Currency(-1L);
		    case DataType.ZeroCurrency:
		        return new Currency( 0 );
		    case DataType.OneCurrency:
		    	return new Currency( 1 );
		    case DataType.MaxCurrency:
		    	return Currency.fromValue( Long.MAX_VALUE );
		    case DataType.Currency:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	return Currency.fromValue( longBuffer.get() );
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Currency readNullableCurrency( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
				return null;
			case DataType.MinCurrency:
		        return Currency.fromValue( Long.MIN_VALUE );
			case DataType.MinusOneCurrency:
		    	return new Currency(-1L);
		    case DataType.ZeroCurrency:
		        return new Currency( 0 );
		    case DataType.OneCurrency:
		    	return new Currency( 1 );
		    case DataType.MaxCurrency:
		    	return Currency.fromValue( Long.MAX_VALUE );
		    case DataType.Currency:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	return Currency.fromValue( longBuffer.get() );
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final long readDateTimeAsInt64( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.ZeroDateTime:
				return 0;
		    case DataType.DateTime:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	return longBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final DateTime readDateTime( ) {
		return new DateTime(readDateTimeAsInt64( ));
	}
	
	public final DateTime readNullableDateTime( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
			case DataType.ZeroDateTime:
				return new DateTime();
		    case DataType.DateTime:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	return new DateTime(longBuffer.get());
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final java.time.Instant readInstant( ) {
		var ticks = readDateTimeAsInt64( ) - TimeBase.UnixEpoch;
		var seconds = ticks / TimeBase.TicksPerSecond;
		var nanos = (ticks % TimeBase.TicksPerSecond)*100;
		return java.time.Instant.ofEpochSecond(seconds, nanos);
	}
	
	public final Instant readNullableInstant( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
			case DataType.ZeroDateTime:
				return java.time.Instant.ofEpochSecond(-TimeBase.UnixEpoch/TimeBase.TicksPerSecond, 0);
		    case DataType.DateTime:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	var ticks = longBuffer.get() - TimeBase.UnixEpoch;;
		    	var seconds = ticks / TimeBase.TicksPerSecond;
				var nanos = (ticks % TimeBase.TicksPerSecond)*100;
				return java.time.Instant.ofEpochSecond(seconds, nanos);
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	
	public final Date readDate() {
		var ticks = readDateTimeAsInt64( ) - TimeBase.UnixEpoch;
		var milliSeconds = ticks / TimeBase.TicksPerMillisecond;
		return new Date(milliSeconds);
	}
	
	public final Date readNullableDate( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
			case DataType.ZeroDateTime:
				return new Date(-TimeBase.UnixEpoch/TimeBase.TicksPerSecond);
		    case DataType.DateTime:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	var ticks = longBuffer.get() - TimeBase.UnixEpoch;;
		    	var milliSeconds = ticks / TimeBase.TicksPerMillisecond;
				return new Date(milliSeconds);
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	
	public final long readTimeSpanAsInt64( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.ZeroTimeSpan:
				return 0;
		    case DataType.TimeSpan:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	return longBuffer.get();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final TimeSpan readTimeSpan( ) {
		return new TimeSpan(readTimeSpanAsInt64( ));
	}
	
	public final TimeSpan readNullableTimeSpan( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
			case DataType.ZeroTimeSpan:
				return new TimeSpan();
		    case DataType.TimeSpan:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	return new TimeSpan(longBuffer.get());
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Duration readDuration() {
		var ticks = readTimeSpanAsInt64( );
		var seconds = ticks / TimeBase.TicksPerSecond;
		var nanos = (ticks % TimeBase.TicksPerSecond)*100;
		return Duration.ofSeconds(seconds, nanos);
	}
	
	public final Duration readNullableDuration( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
			case DataType.ZeroTimeSpan:
				return Duration.ofSeconds(0, 0);
		    case DataType.TimeSpan:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	var ticks = longBuffer.get();
		    	var seconds = ticks / TimeBase.TicksPerSecond;
				var nanos = (ticks % TimeBase.TicksPerSecond)*100;
				return Duration.ofSeconds(seconds, nanos);
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Time readTime() {
		var ticks = readTimeSpanAsInt64( );
		var milliSeconds = ticks / TimeBase.TicksPerMillisecond;
		return new Time(milliSeconds);
	}
	
	public final Time readNullableTime( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return null;
			case DataType.ZeroTimeSpan:
				return new Time(0);
		    case DataType.TimeSpan:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	var ticks = longBuffer.get();
		    	var milliSeconds = ticks / TimeBase.TicksPerMillisecond;
				return new Time(milliSeconds);
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final byte[] readGuidAsBytes( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.EmptyGuid:
				return new byte[16];
		    case DataType.Guid:
		    	var buffer = readBuffer(16);
		    	return buffer.array();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Guid readGuid( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.EmptyGuid:
				return new Guid();
		    case DataType.Guid:
		    	var buffer = readBuffer(16);
		    	return new Guid(buffer.array());
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final Guid readNullableGuid( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
				return null;
			case DataType.EmptyGuid:
				return new Guid();
		    case DataType.Guid:
		    	var buffer = readBuffer(16);
		    	return new Guid(buffer.array());
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	
	public final UUID readUUID() {
		var guidBytes = readGuidAsBytes( );
		
		// Reorder the first three components of the GUID to match UUID's expected byte order
        var reorderedBytes = new byte[16];

        // Copy the last two components (clock_seq_and_node) directly
        System.arraycopy(guidBytes, 8, reorderedBytes, 8, 8);

        // Reorder the first three components (time_low, time_mid, time_hi_and_version)
        reorderedBytes[0] = guidBytes[3];
        reorderedBytes[1] = guidBytes[2];
        reorderedBytes[2] = guidBytes[1];
        reorderedBytes[3] = guidBytes[0];

        reorderedBytes[4] = guidBytes[5];
        reorderedBytes[5] = guidBytes[4];

        reorderedBytes[6] = guidBytes[7];
        reorderedBytes[7] = guidBytes[6];

        // Use ByteBuffer to get long values for MSB and LSB
        ByteBuffer byteBuffer = ByteBuffer.wrap(reorderedBytes);
        var msb = byteBuffer.getLong();
        var lsb = byteBuffer.getLong();

        return new UUID(msb, lsb);
	}
	
	public final UUID readNullableUUID() {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
				return null;
			case DataType.EmptyGuid:
				return new UUID(0L,0L);
		    case DataType.Guid:
		    	var buffer = readBuffer(16);
		    	var guidBytes = buffer.array();
		    	// Reorder the first three components of the GUID to match UUID's expected byte order
		        var reorderedBytes = new byte[16];

		        // Copy the last two components (clock_seq_and_node) directly
		        System.arraycopy(guidBytes, 8, reorderedBytes, 8, 8);

		        // Reorder the first three components (time_low, time_mid, time_hi_and_version)
		        reorderedBytes[0] = guidBytes[3];
		        reorderedBytes[1] = guidBytes[2];
		        reorderedBytes[2] = guidBytes[1];
		        reorderedBytes[3] = guidBytes[0];

		        reorderedBytes[4] = guidBytes[5];
		        reorderedBytes[5] = guidBytes[4];

		        reorderedBytes[6] = guidBytes[7];
		        reorderedBytes[7] = guidBytes[6];

		        // Use ByteBuffer to get long values for MSB and LSB
		        ByteBuffer byteBuffer = ByteBuffer.wrap(reorderedBytes);
		        var msb = byteBuffer.getLong();
		        var lsb = byteBuffer.getLong();

		        return new UUID(msb, lsb);
		    	
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	
	public final String readString( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.EmptyString:
				return new String();
		    case DataType.StringUTF8:
		    {
		    	var size = Read7BitEncodedUInt64( );
		    	var buffer = readBuffer((int)size);
		    	return new String(buffer.array(), StandardCharsets.UTF_8);
		    }
		    case DataType.StringUTF16LE:
		    {
		    	var size = Read7BitEncodedUInt64( );
		    	var buffer = readBuffer((int)size);
		    	return new String(buffer.array(), StandardCharsets.UTF_16LE);
		    }
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final String readNullableString( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
				return null;
			case DataType.EmptyString:
				return new String();
		    case DataType.StringUTF8:
		    {
		    	var size = Read7BitEncodedUInt64( );
		    	var buffer = readBuffer((int)size);
		    	return new String(buffer.array(), StandardCharsets.UTF_8);
		    }
		    case DataType.StringUTF16LE:
		    {
		    	var size = Read7BitEncodedUInt64( );
		    	var buffer = readBuffer((int)size);
		    	return new String(buffer.array(), StandardCharsets.UTF_16LE);
		    }
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	private final int readSize(byte smallArrayDataType, byte mediumArrayDataType, byte largeArrayDataType, byte emptyArrayDataType) {
		var dataType = readDataType();
		if(dataType == smallArrayDataType) {
			return readByte();
		}
		else if(dataType == mediumArrayDataType) {
			var buffer = readBuffer(2);
	    	var shortBuffer = buffer.asShortBuffer();
	    	return shortBuffer.get();
		}
		else if(dataType == largeArrayDataType) {
			var buffer = readBuffer(2);
	    	var intBuffer = buffer.asIntBuffer();
	    	return intBuffer.get();
		}
		else if(dataType == emptyArrayDataType) {
			return 0;
		}
		else {
			throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	private final int readSize(byte smallArrayDataType ) {
		return readSize(smallArrayDataType, (byte)(smallArrayDataType+1),(byte)(smallArrayDataType+2),(byte)(smallArrayDataType+3));
	}
	
	private final int readNullableSize(byte smallArrayDataType, byte mediumArrayDataType, byte largeArrayDataType, byte emptyArrayDataType) {
		var dataType = readDataType();
		if(dataType == DataType.Null) {
			return -1;
		}
		else if(dataType == smallArrayDataType) {
			return readByte();
		}
		else if(dataType == mediumArrayDataType) {
			var buffer = readBuffer(2);
	    	var shortBuffer = buffer.asShortBuffer();
	    	return shortBuffer.get();
		}
		else if(dataType == largeArrayDataType) {
			var buffer = readBuffer(2);
	    	var intBuffer = buffer.asIntBuffer();
	    	return intBuffer.get();
		}
		else if(dataType == emptyArrayDataType) {
			return 0;
		}
		else {
			throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	private final int readNullableSize(byte smallArrayDataType ) {
		return readNullableSize(smallArrayDataType, (byte)(smallArrayDataType+1),(byte)(smallArrayDataType+2),(byte)(smallArrayDataType+3));
	}
	
	public final boolean[] readBooleanArray() {
		var count = readSize(DataType.SmallBooleanArray);
		if(count > 0) {
			var buffer = readBuffer(count);
			var result = new boolean[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value != 0; 
			}
			return result;
		}
		else {
			return new boolean[0];
		}
	}
	public final boolean[] readNullableBooleanArray() {
		var count = readNullableSize(DataType.SmallBooleanArray);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var buffer = readBuffer(count);
			var result = new boolean[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value != 0; 
			}
			return result;
		}
		else {
			return new boolean[0];
		}
	}
	
	public final char[] readCharArray() {
		var count = readSize(DataType.SmallCharArray);
		if(count > 0) {
			var byteBuffer = readBuffer(count*Character.BYTES);
			var buffer = byteBuffer.asCharBuffer(); 
			var result = new char[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new char[0];
		}
	}
	public final char[] readNullableCharArray() {
		var count = readNullableSize(DataType.SmallCharArray);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var byteBuffer = readBuffer(count*Character.BYTES);
			var buffer = byteBuffer.asCharBuffer(); 
			var result = new char[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new char[0];
		}
	}
	
	public final byte[] readUInt8Array() {
		var count = readSize(DataType.SmallByteArray);
		if(count > 0) {
			var buffer = readBuffer(count);
			if(buffer.hasArray()) {
				return buffer.array();
			}
			else {
				var result = new byte[count];
				buffer.get(result);
				return result;
			}
		}
		else {
			return new byte[0];
		}
	}
	public final byte[] readNullableUInt8Array() {
		var count = readNullableSize(DataType.SmallByteArray);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var buffer = readBuffer(count);
			if(buffer.hasArray()) {
				return buffer.array();
			}
			else {
				var result = new byte[count];
				buffer.get(result);
				return result;
			}
		}
		else {
			return new byte[0];
		}
	}
	
	public final byte[] readInt8Array() {
		var count = readSize(DataType.SmallSByteArray);
		if(count > 0) {
			var buffer = readBuffer(count);
			if(buffer.hasArray()) {
				return buffer.array();
			}
			else {
				var result = new byte[count];
				buffer.get(result);
				return result;
			}
		}
		else {
			return new byte[0];
		}
	}
	public final byte[] readNullableInt8Array() {
		var count = readNullableSize(DataType.SmallSByteArray);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var buffer = readBuffer(count);
			if(buffer.hasArray()) {
				return buffer.array();
			}
			else {
				var result = new byte[count];
				buffer.get(result);
				return result;
			}
		}
		else {
			return new byte[0];
		}
	}
	
	public final short[] readUInt16Array() {
		var count = readSize(DataType.SmallUInt16Array);
		if(count > 0) {
			var byteBuffer = readBuffer(count*Short.BYTES);
			var buffer = byteBuffer.asShortBuffer(); 
			var result = new short[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new short[0];
		}
	}
	public final short[] readNullableUInt16Array() {
		var count = readNullableSize(DataType.SmallUInt16Array);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var byteBuffer = readBuffer(count*Short.BYTES);
			var buffer = byteBuffer.asShortBuffer(); 
			var result = new short[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new short[0];
		}
	}
	
	public final short[] readInt16Array() {
		var count = readSize(DataType.SmallInt16Array);
		if(count > 0) {
			var byteBuffer = readBuffer(count*Short.BYTES);
			var buffer = byteBuffer.asShortBuffer(); 
			var result = new short[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new short[0];
		}
	}
	public final short[] readNullableInt16Array() {
		var count = readNullableSize(DataType.SmallInt16Array);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var byteBuffer = readBuffer(count*Short.BYTES);
			var buffer = byteBuffer.asShortBuffer(); 
			var result = new short[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new short[0];
		}
	}
	
	public final int[] readUInt32Array() {
		var count = readSize(DataType.SmallUInt32Array);
		if(count > 0) {
			var byteBuffer = readBuffer(count*Integer.BYTES);
			var buffer = byteBuffer.asIntBuffer(); 
			var result = new int[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new int[0];
		}
	}
	public final int[] readNullableUInt32Array() {
		var count = readNullableSize(DataType.SmallUInt32Array);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var byteBuffer = readBuffer(count*Integer.BYTES);
			var buffer = byteBuffer.asIntBuffer(); 
			var result = new int[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new int[0];
		}
	}
	
	public final int[] readInt32Array() {
		var count = readSize(DataType.SmallInt32Array);
		if(count > 0) {
			var byteBuffer = readBuffer(count*Integer.BYTES);
			var buffer = byteBuffer.asIntBuffer(); 
			var result = new int[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new int[0];
		}
	}
	public final int[] readNullableInt32Array() {
		var count = readNullableSize(DataType.SmallInt32Array);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var byteBuffer = readBuffer(count*Integer.BYTES);
			var buffer = byteBuffer.asIntBuffer(); 
			var result = new int[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new int[0];
		}
	}
	
	public final long[] readUInt64Array() {
		var count = readSize(DataType.SmallUInt64Array);
		if(count > 0) {
			var byteBuffer = readBuffer(count*Long.BYTES);
			var buffer = byteBuffer.asLongBuffer(); 
			var result = new long[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new long[0];
		}
	}
	public final long[] readNullableUInt64Array() {
		var count = readNullableSize(DataType.SmallUInt64Array);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var byteBuffer = readBuffer(count*Long.BYTES);
			var buffer = byteBuffer.asLongBuffer(); 
			var result = new long[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new long[0];
		}
	}
	
	public final long[] readInt64Array() {
		var count = readSize(DataType.SmallInt64Array);
		if(count > 0) {
			var byteBuffer = readBuffer(count*Long.BYTES);
			var buffer = byteBuffer.asLongBuffer(); 
			var result = new long[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new long[0];
		}
	}
	public final long[] readNullableInt64Array() {
		var count = readNullableSize(DataType.SmallInt64Array);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var byteBuffer = readBuffer(count*Long.BYTES);
			var buffer = byteBuffer.asLongBuffer(); 
			var result = new long[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new long[0];
		}
	}
	
	public final float[] readSingleArray() {
		var count = readSize(DataType.SmallSingleArray);
		if(count > 0) {
			var byteBuffer = readBuffer(count*Float.BYTES);
			var buffer = byteBuffer.asFloatBuffer(); 
			var result = new float[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new float[0];
		}
	}
	public final float[] readNullableSingleArray() {
		var count = readNullableSize(DataType.SmallSingleArray);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var byteBuffer = readBuffer(count*Float.BYTES);
			var buffer = byteBuffer.asFloatBuffer(); 
			var result = new float[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new float[0];
		}
	}
	
	public final double[] readDoubleArray() {
		var count = readSize(DataType.SmallDoubleArray);
		if(count > 0) {
			var byteBuffer = readBuffer(count*Double.BYTES);
			var buffer = byteBuffer.asDoubleBuffer(); 
			var result = new double[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new double[0];
		}
	}
	public final double[] readNullableDoubleArray() {
		var count = readNullableSize(DataType.SmallDoubleArray);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var byteBuffer = readBuffer(count*Double.BYTES);
			var buffer = byteBuffer.asDoubleBuffer(); 
			var result = new double[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = value; 
			}
			return result;
		}
		else {
			return new double[0];
		}
	}
	
	public final DateTime[] readDateTimeArray() {
		var count = readSize(DataType.SmallDateTimeArray);
		if(count > 0) {
			var byteBuffer = readBuffer(count*Long.BYTES);
			var buffer = byteBuffer.asLongBuffer(); 
			var result = new DateTime[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = new DateTime( value ); 
			}
			return result;
		}
		else {
			return new DateTime[0];
		}
	}
	public final DateTime[] readNullableDateTimeArray() {
		var count = readNullableSize(DataType.SmallDateTimeArray);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var byteBuffer = readBuffer(count*Long.BYTES);
			var buffer = byteBuffer.asLongBuffer(); 
			var result = new DateTime[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = new DateTime( value ); 
			}
			return result;
		}
		else {
			return new DateTime[0];
		}
	}
	
	public final TimeSpan[] readTimeSpanArray() {
		var count = readSize(DataType.SmallTimeSpanArray);
		if(count > 0) {
			var byteBuffer = readBuffer(count*Long.BYTES);
			var buffer = byteBuffer.asLongBuffer(); 
			var result = new TimeSpan[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = new TimeSpan( value ); 
			}
			return result;
		}
		else {
			return new TimeSpan[0];
		}
	}
	public final TimeSpan[] readNullableTimeSpanArray() {
		var count = readNullableSize(DataType.SmallTimeSpanArray);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var byteBuffer = readBuffer(count*Long.BYTES);
			var buffer = byteBuffer.asLongBuffer(); 
			var result = new TimeSpan[count];
			for(int i = 0; i < count; i++) {
				var value = buffer.get();
				result[i] = new TimeSpan( value ); 
			}
			return result;
		}
		else {
			return new TimeSpan[0];
		}
	}
	
	public final Guid[] readGuidArray() {
		var count = readSize(DataType.SmallGuidArray);
		if(count > 0) {
			var buffer = readBuffer(count*Guid.BYTES);
			var result = new Guid[count];
			for(int i = 0; i < count; i++) {
				buffer.get( sixteenBytes );
				result[i] = new Guid( sixteenBytes ); 
			}
			return result;
		}
		else {
			return new Guid[0];
		}
	}
	public final Guid[] readNullableGuidArray() {
		var count = readNullableSize(DataType.SmallGuidArray);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var buffer = readBuffer(count*Guid.BYTES);
			var result = new Guid[count];
			for(int i = 0; i < count; i++) {
				buffer.get( sixteenBytes );
				result[i] = new Guid( sixteenBytes ); 
			}
			return result;
		}
		else {
			return new Guid[0];
		}
	}
	
	public final String[] readStringArray() {
		var count = readSize(DataType.SmallStringArray);
		if(count > 0) {
			var result = new String[count];
			for(int i = 0; i < count; i++) {
				var byteCount = (int)Read7BitEncodedUInt64( );
				var buffer = readBuffer(byteCount);
				if(buffer.hasArray() ) {
					var stringBytes = buffer.array();
					result[i] = new String(stringBytes, StandardCharsets.UTF_8);
				}
				else {
					var stringBytes = new byte[byteCount];
					buffer.get(stringBytes);
					result[i] = new String(stringBytes, StandardCharsets.UTF_8);
				}
			}
			return result;
		}
		else {
			return new String[0];
		}
	}
	public final String[] readNullableStringArray() {
		var count = readNullableSize(DataType.SmallStringArray);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var result = new String[count];
			for(int i = 0; i < count; i++) {
				var byteCount = (int)Read7BitEncodedUInt64( );
				var buffer = readBuffer(byteCount);
				if(buffer.hasArray() ) {
					var stringBytes = buffer.array();
					result[i] = new String(stringBytes, StandardCharsets.UTF_8);
				}
				else {
					var stringBytes = new byte[byteCount];
					buffer.get(stringBytes);
					result[i] = new String(stringBytes, StandardCharsets.UTF_8);
				}
			}
			return result;
		}
		else {
			return new String[0];
		}
	}
	
	public final byte[][] readInt8ListArray() {
		var count = readSize(DataType.SmallByteArrayList);
		if(count > 0) {
			var result = new byte[count][];
			for(int i = 0; i < count; i++) {
				result[i] = readUInt8Array();
			}
			return result;
		}
		else {
			return new byte[0][];
		}
	}
	public final byte[][] readNullableInt8ListArray() {
		var count = readNullableSize(DataType.SmallByteArrayList);
		if(count < 0) {
			return null;
		}
		else if(count > 0) {
			var result = new byte[count][];
			for(int i = 0; i < count; i++) {
				result[i] = readUInt8Array();
			}
			return result;
		}
		else {
			return new byte[0][];
		}
	}
	
}
