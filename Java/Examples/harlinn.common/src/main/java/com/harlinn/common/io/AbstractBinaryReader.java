package com.harlinn.common.io;

import java.nio.ByteBuffer;

import com.harlinn.common.util.*;

public abstract class AbstractBinaryReader {
	public abstract byte readInt8();
	public abstract short readInt16();
	public abstract int readInt32();
	public abstract long readInt64();
	public abstract byte[] readBytes(int numberOfBytes);
	
	public final long Read7BitEncodedUInt64( ) {
	    long resultValue = 0;
	    byte byteValue = readInt8( );
	    resultValue = byteValue & 0x7F;
	    if ( (byteValue & (byte)0x80) != 0 ) {
	    	byteValue = readInt8( );
	        resultValue |= ((long)( byteValue & 0x7F )) << 7;
	        if ( (byteValue & (byte)0x80) != 0 ) {
	        	byteValue = readInt8( );
	            resultValue |= ((long)( byteValue & 0x7F )) << 14;
	            if ( (byteValue & (byte)0x80) != 0 ) {
	            	byteValue = readInt8( );
	                resultValue |= ((long)( byteValue & 0x7F )) << 21;
	                if ( (byteValue & (byte)0x80) != 0 ) {
	                	byteValue = readInt8( );
	                    resultValue |= ((long)( byteValue & 0x7F )) << 28;
	                    if ( (byteValue & (byte)0x80) != 0 ) {
	                    	byteValue = readInt8( );
	                        resultValue |= ((long)( byteValue & 0x7F )) << 35;
	                        if ( (byteValue & (byte)0x80) != 0 ) {
	                        	byteValue = readInt8( );
	                            resultValue |= ((long)( byteValue & 0x7F )) << 42;
	                            if ( (byteValue & (byte)0x80) != 0 ) {
	                            	byteValue = readInt8( );
	                                resultValue |= ((long)( byteValue & 0x7F )) << 49;
	                                if ( (byteValue & (byte)0x80) != 0 ) {
	                                	byteValue = readInt8( );
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
	
	public final boolean readBoolean() {
		byte byteValue = readInt8( );
		return byteValue != 0 ? true : false;
	}
	
	public final Boolean readNullableBoolean() {
		var hasValue = readBoolean();
		if(hasValue) {
			byte byteValue = readInt8( );
			return byteValue != 0 ? true : false;
		}
		return null;
	}
	
	
	public final byte readUInt8() {
		return readInt8();
	}
	
	public final UnsignedByte readNullableUInt8() {
		var hasValue = readBoolean();
		if(hasValue) {
			return new UnsignedByte( readUInt8( ) );
		}
		return null;
	}
	
	public final Byte readNullableInt8() {
		var hasValue = readBoolean();
		if(hasValue) {
			return readInt8( );
		}
		return null;
	}
	
	public final Short readNullableInt16() {
		var hasValue = readBoolean();
		if(hasValue) {
			return readInt16( );
		}
		return null;
	}
	
	public final short readUInt16() {
		return readInt16();
	}
	
	public final UnsignedShort readNullableUInt16() {
		var hasValue = readBoolean();
		if(hasValue) {
			return new UnsignedShort( readInt16( ) );
		}
		return null;
	}
	
	public final Integer readNullableInt32() {
		var hasValue = readBoolean();
		if(hasValue) {
			return readInt32( );
		}
		return null;
	}
	
	public final int readUInt32() {
		return readInt32();
	}
	
	public final UnsignedInteger readNullableUInt32() {
		var hasValue = readBoolean();
		if(hasValue) {
			return new UnsignedInteger( readInt32( ) );
		}
		return null;
	}
	
	public final Long readNullableInt64() {
		var hasValue = readBoolean();
		if(hasValue) {
			return readInt64( );
		}
		return null;
	}
	
	public final long readUInt64() {
		return readInt64();
	}
	
	public final UnsignedLong readNullableUInt64() {
		var hasValue = readBoolean();
		if(hasValue) {
			return new UnsignedLong( readInt64( ) );
		}
		return null;
	}
	
	public final float readSingle() {
		return Float.intBitsToFloat( readInt32() );
	}
	
	public final Float readNullableSingle() {
		var hasValue = readBoolean();
		if(hasValue) {
			return readSingle();
		}
		return null;
	}
	
	public final double readDouble() {
		return Double.longBitsToDouble( readInt64() );
	}
	
	public final Double readNullableDouble() {
		var hasValue = readBoolean();
		if(hasValue) {
			return readDouble();
		}
		return null;
	}
	
	public final DateTime readDateTime() {
		return new DateTime( readInt64() );
	}
	
	public final DateTime readNullableDateTime() {
		var hasValue = readBoolean();
		if(hasValue) {
			return readDateTime();
		}
		return null;
	}
	
	public final TimeSpan readTimeSpan() {
		return new TimeSpan( readInt64() );
	}
	
	public final TimeSpan readNullableTimeSpan() {
		var hasValue = readBoolean();
		if(hasValue) {
			return readTimeSpan();
		}
		return null;
	}
	
	public final Currency readCurrency() {
		return Currency.fromValue( readInt64() );
	}
	
	public final Currency readNullableCurrency() {
		var hasValue = readBoolean();
		if(hasValue) {
			return readCurrency();
		}
		return null;
	}
	
	public final Guid readGuid() {
		var bytes = readBytes(16);
		return new Guid(bytes);
	}
	
	public final Guid readNullableGuid() {
		var hasValue = readBoolean();
		if(hasValue) {
			return readGuid();
		}
		return null;
	}
	
	public final byte[] readStringBytes() {
		var numberOfBytes = (int)Read7BitEncodedUInt64( ); 
		var bytes = readBytes(numberOfBytes);
		return bytes;
	}
	
	public final String readString(java.nio.charset.Charset charset) {
		var bytes = readStringBytes();
		return new String(bytes,charset);
	}
	
	public final String readString() {
		var bytes = readStringBytes();
		return new String(bytes,java.nio.charset.StandardCharsets.UTF_16LE);
	}
	
	
	
	
	
	
	
}
