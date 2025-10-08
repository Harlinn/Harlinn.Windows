package com.harlinn.common.serialization;


import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.Optional;
import java.util.UUID;

import com.harlinn.common.util.DateTime;
import com.harlinn.common.util.TimeBase;
import com.harlinn.common.util.TimeSpan;

public abstract class AbstractDataReader {
	
	
	protected AbstractDataReader() {
		
	}
	
	protected abstract byte readByte( );
	protected abstract ByteBuffer readBuffer( int size );
	
	private final long Read7BitEncodedUInt64( ) {
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
	
	private final long Read7BitEncodedInt64( ) {
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
	
	public final Optional<Boolean> readOptionalBoolean( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return Optional.empty();
		    case DataType.BooleanFalse:
		        return Optional.of(false);
		    case DataType.BooleanTrue:
		        return Optional.of(true);
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
	
	public final Optional<Character> readOptionalChar( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return Optional.empty();
		    case DataType.ZeroChar:
		        return Optional.of( Character.valueOf((char)0) );
		    case DataType.OneChar:
		    	return Optional.of( Character.valueOf((char)1) );
		    case DataType.MaxChar:
		    	return Optional.of( Character.valueOf((char)0xFFFF) );
		    case DataType.Char:
		    	var buffer = readBuffer(2);
		    	var charBuffer = buffer.asCharBuffer();
		    	return Optional.of( charBuffer.get() );
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
	
	public final Optional<Byte> readOptionalUInt8( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return Optional.empty();
		    case DataType.ZeroByte:
		        return Optional.of((byte)0);
		    case DataType.OneByte:
		    	return Optional.of((byte)1);
		    case DataType.MaxByte:
		    	return Optional.of((byte)0xFF);
		    case DataType.Byte:
		    	var value = readByte( );
		    	return Optional.of(value);
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
	
	public final Optional<Byte> readOptionalInt8( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return Optional.empty();
			case DataType.MinSByte:
		        return Optional.of(Byte.MIN_VALUE);
			case DataType.MinusOneSByte:
		    	return Optional.of((byte)-1);
		    case DataType.ZeroSByte:
		        return Optional.of((byte)0);
		    case DataType.OneSByte:
		    	return Optional.of((byte)1);
		    case DataType.MaxSByte:
		    	return Optional.of(Byte.MAX_VALUE);
		    case DataType.SByte:
		    	var value = readByte( );
		    	return Optional.of(value);
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
	
	public final Optional<Short> readOptionalUInt16( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return Optional.empty();
		    case DataType.ZeroUInt16:
		        return Optional.of((short)0);
		    case DataType.OneUInt16:
		    	return Optional.of((short)1);
		    case DataType.MaxUInt16:
		    	return Optional.of((short)0xFFFF);
		    case DataType.UInt16:
		    	var buffer = readBuffer(2);
		    	var shortBuffer = buffer.asShortBuffer();
		    	return Optional.of( shortBuffer.get() );
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
	
	public final Optional<Short> readOptionalInt16( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return Optional.empty();
			case DataType.MinInt16:
		        return Optional.of(Short.MIN_VALUE);
			case DataType.MinusOneInt16:
		    	return Optional.of((short)-1);
		    case DataType.ZeroInt16:
		        return Optional.of((short)0);
		    case DataType.OneInt16:
		    	return Optional.of((short)1);
		    case DataType.MaxInt16:
		    	return Optional.of(Short.MAX_VALUE);
		    case DataType.Int16:
		    	var buffer = readBuffer(2);
		    	var shortBuffer = buffer.asShortBuffer();
		    	return Optional.of( shortBuffer.get() );
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
	
	public final Optional<Integer> readOptionalUInt32( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return Optional.empty();
		    case DataType.ZeroUInt32:
		        return Optional.of((int)0);
		    case DataType.OneUInt32:
		    	return Optional.of((int)1);
		    case DataType.MaxUInt32:
		    	return Optional.of((int)0xFFFFFFFF);
		    case DataType.UInt32:
		    	var buffer = readBuffer(4);
		    	var intBuffer = buffer.asIntBuffer();
		    	return Optional.of( intBuffer.get() );
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
	
	public final Optional<Integer> readOptionalInt32( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return Optional.empty();
			case DataType.MinInt32:
		        return Optional.of(Integer.MIN_VALUE);
			case DataType.MinusOneInt32:
		    	return Optional.of((int)-1);
		    case DataType.ZeroInt32:
		        return Optional.of((int)0);
		    case DataType.OneInt32:
		    	return Optional.of((int)1);
		    case DataType.MaxInt32:
		    	return Optional.of(Integer.MAX_VALUE);
		    case DataType.Int32:
		    	var buffer = readBuffer(4);
		    	var intBuffer = buffer.asIntBuffer();
		    	return Optional.of( intBuffer.get() );
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
	
	public final Optional<Long> readOptionalUInt64( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return Optional.empty();
		    case DataType.ZeroUInt64:
		        return Optional.of((long)0);
		    case DataType.OneUInt64:
		    	return Optional.of((long)1);
		    case DataType.MaxUInt64:
		    	return Optional.of((long)0xFFFFFFFF);
		    case DataType.UInt64:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	return Optional.of( longBuffer.get() );
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
	
	public final Optional<Long> readOptionalInt64( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return Optional.empty();
			case DataType.MinInt64:
		        return Optional.of(Long.MIN_VALUE);
			case DataType.MinusOneInt64:
		    	return Optional.of((long)-1);
		    case DataType.ZeroInt64:
		        return Optional.of((long)0);
		    case DataType.OneInt64:
		    	return Optional.of((long)1);
		    case DataType.MaxInt64:
		    	return Optional.of(Long.MAX_VALUE);
		    case DataType.Int64:
		    	var buffer = readBuffer(8);
		    	var longBuffer = buffer.asLongBuffer();
		    	return Optional.of( longBuffer.get() );
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
	
	public final Optional<Float> readOptionalSingle( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return Optional.empty();
			case DataType.SingleNegativeInfinity:
				return Optional.of(Float.NEGATIVE_INFINITY);
			case DataType.MinSingle:
		        return Optional.of(-Float.MAX_VALUE);
			case DataType.MinusOneSingle:
		    	return Optional.of(-1.f);
		    case DataType.ZeroSingle:
		        return Optional.of(0.f);
		    case DataType.OneSingle:
		    	return Optional.of(1.f);
		    case DataType.MaxSingle:
		    	return Optional.of(Float.MAX_VALUE);
		    case DataType.SinglePositiveInfinity:
		    	return Optional.of(Float.POSITIVE_INFINITY);
		    case DataType.SingleNaN:
		    	return Optional.of(Float.NaN);
		    case DataType.Single:
		    	var buffer = readBuffer(4);
		    	var floatBuffer = buffer.asFloatBuffer();
		    	return Optional.of(floatBuffer.get());
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
	
	public final Optional<Double> readOptionalDouble( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.Null:
		        return Optional.empty();
			case DataType.DoubleNegativeInfinity:
				return Optional.of(Double.NEGATIVE_INFINITY);
			case DataType.MinDouble:
		        return Optional.of(-Double.MAX_VALUE);
			case DataType.MinusOneDouble:
		    	return Optional.of(-1.);
		    case DataType.ZeroDouble:
		        return Optional.of(0.);
		    case DataType.OneDouble:
		    	return Optional.of(1.);
		    case DataType.MaxDouble:
		    	return Optional.of(Double.MAX_VALUE);
		    case DataType.DoublePositiveInfinity:
		    	return Optional.of(Double.POSITIVE_INFINITY);
		    case DataType.DoubleNaN:
		    	return Optional.of(Double.NaN);
		    case DataType.Double:
		    	var buffer = readBuffer(8);
		    	var doubleBuffer = buffer.asDoubleBuffer();
		    	return Optional.of(doubleBuffer.get());
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
	
	public final java.time.Instant readInstant( ) {
		var ticks = readDateTimeAsInt64( ) - TimeBase.UnixEpoch;
		var seconds = ticks / TimeBase.TicksPerSecond;
		var nanos = (ticks % TimeBase.TicksPerSecond)*100;
		return java.time.Instant.ofEpochSecond(seconds, nanos);
	}
	
	public final java.util.Date readDate() {
		var ticks = readDateTimeAsInt64( ) - TimeBase.UnixEpoch;
		var milliSeconds = ticks / TimeBase.TicksPerMillisecond;
		return new java.util.Date(milliSeconds);
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
	
	public final java.time.Duration readDuration() {
		var ticks = readTimeSpanAsInt64( );
		var seconds = ticks / TimeBase.TicksPerSecond;
		var nanos = (ticks % TimeBase.TicksPerSecond)*100;
		return java.time.Duration.ofSeconds(seconds, nanos);
	}
	
	public final java.sql.Time readTime() {
		var ticks = readTimeSpanAsInt64( );
		var milliSeconds = ticks / TimeBase.TicksPerMillisecond;
		return new java.sql.Time(milliSeconds);
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
	
	public final byte[] readStringAsBytes( ) {
		var dataType = readDataType();
		switch (dataType) {
			case DataType.EmptyString:
				return new byte[0];
		    case DataType.String:
		    	var size = Read7BitEncodedUInt64( );
		    	var buffer = readBuffer((int)size);
		    	return buffer.array();
		    default:
		        throw new UnexpectedDataTypeException(dataType);
		}
	}
	
	public final String readString( java.nio.charset.Charset charset ) {
		var bytes = readStringAsBytes( );
		return new String(bytes, charset );
	}
	public final String readString( ) {
		return readString( StandardCharsets.UTF_16 );
	}
	
	
	
}
