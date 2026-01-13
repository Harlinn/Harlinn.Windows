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

import java.nio.ByteOrder;

/**
 * Converts base data types to an array of bytes, and an array of bytes to base data types.
 */
public class BitConverter {
	private static final boolean isLittleEndian = ByteOrder.nativeOrder() == ByteOrder.LITTLE_ENDIAN;
	
	public static final byte[] getBytes(boolean value ) {
		byte[] result = new byte[1]; 
		if(value) {
			result[0] = 1; 
		}
		else {
			result[0] = 0;
		}
		return result;
	}
	
	public static final boolean toBoolean(byte[] bytes, int offset) {
		if(bytes == null) {
			throw new IllegalArgumentException("bytes is null");
		}
		if(offset < 0) {
			throw new IllegalArgumentException("offset("+offset+") < 0");
		}
		if(offset >= bytes.length) {
			throw new IllegalArgumentException("offset("+offset+") >= bytes.length("+bytes.length+")");
		}
		return bytes[offset] == 0 ? false : true;
	}
	
	public static final boolean toBoolean(byte[] bytes) {
		return toBoolean(bytes, 0);
	}
	
	public static final byte[] getBytes(byte value ) {
		byte[] result = new byte[1]; 
		result[0] = value; 
		return result;
	}
	
	public static final byte toByte(byte[] bytes, int offset) {
		if(bytes == null) {
			throw new IllegalArgumentException("bytes is null");
		}
		if(offset < 0) {
			throw new IllegalArgumentException("offset("+offset+") < 0");
		}
		if(offset >= bytes.length) {
			throw new IllegalArgumentException("offset("+offset+") >= bytes.length("+bytes.length+")");
		}
		return bytes[offset];
	}
	public static final byte toByte(byte[] bytes) {
		return toByte(bytes,0);
	}
	
	
	
	public static final byte[] getBytes(char value) {
		return getBytes((short)value);
	}
	
	public static char toChar(byte[] bytes, int offset) {
		return (char)toInt16(bytes,offset);
	}
	
	public static final char toChar(byte[] bytes) {
		return toChar(bytes,0);
	}
	
	public static final byte[] getBytes(short value) {
        byte[] bytes = new byte[2];
        if (isLittleEndian) {
	        bytes[0] = (byte) (value & 0xFF);
	        bytes[1] = (byte) ((value >>> 8) & 0xFF);
        }
        else {
        	bytes[1] = (byte) (value & 0xFF);
	        bytes[0] = (byte) ((value >>> 8) & 0xFF);
        }
        return bytes;
    }
	
	public static short toInt16(byte[] bytes, int offset) {
		if(bytes == null) {
			throw new IllegalArgumentException("bytes is null");
		}
		if(offset < 0) {
			throw new IllegalArgumentException("offset("+offset+") < 0");
		}
		if(offset + Short.BYTES > bytes.length) {
			throw new IllegalArgumentException("offset("+offset+") + Short.BYTES > bytes.length("+bytes.length+")");
		}
		if (isLittleEndian) {
	        return (short)(((bytes[offset] & 0xFF)) |
	               ((bytes[offset + 1] & 0xFF) << 8));
		}
		else {
			return (short)(((bytes[offset + 1] & 0xFF)) |
		               ((bytes[offset] & 0xFF) << 8));
		}
    }
	
	public static final short toInt16(byte[] bytes) {
		return toInt16(bytes,0);
	}
	
	
	
	public static final byte[] getBytes(int value) {
        byte[] bytes = new byte[4];
        if (isLittleEndian) {
	        bytes[0] = (byte) (value & 0xFF);
	        bytes[1] = (byte) ((value >>> 8) & 0xFF);
	        bytes[2] = (byte) ((value >>> 16) & 0xFF);
	        bytes[3] = (byte) ((value >>> 24) & 0xFF);
        }
        else {
        	bytes[3] = (byte) (value & 0xFF);
	        bytes[2] = (byte) ((value >>> 8) & 0xFF);
	        bytes[1] = (byte) ((value >>> 16) & 0xFF);
	        bytes[0] = (byte) ((value >>> 24) & 0xFF);
        }
        return bytes;
    }

    public static int toInt32(byte[] bytes, int offset) {
    	if(bytes == null) {
			throw new IllegalArgumentException("bytes is null");
		}
		if(offset < 0) {
			throw new IllegalArgumentException("offset("+offset+") < 0");
		}
		if(offset + Integer.BYTES > bytes.length) {
			throw new IllegalArgumentException("offset("+offset+") + Integer.BYTES > bytes.length("+bytes.length+")");
		}
    	if (isLittleEndian) {
	        return ((bytes[offset] & 0xFF)) |
	               ((bytes[offset + 1] & 0xFF) << 8) |
	               ((bytes[offset + 2] & 0xFF) << 16) |
	               ((bytes[offset + 3] & 0xFF) << 24);
    	}
    	else {
    		return ((bytes[offset + 3] & 0xFF)) |
 	               ((bytes[offset + 2] & 0xFF) << 8) |
 	               ((bytes[offset + 1] & 0xFF) << 16) |
 	               ((bytes[offset] & 0xFF) << 24);
    	}
    }
	
    public static final int toInt32(byte[] bytes) {
		return toInt32(bytes,0);
	}
    
    
    public static final byte[] getBytes(long value) {
        byte[] bytes = new byte[8];
        if (isLittleEndian) {
	        bytes[0] = (byte) (value & 0xFF);
	        bytes[1] = (byte) ((value >>> 8) & 0xFF);
	        bytes[2] = (byte) ((value >>> 16) & 0xFF);
	        bytes[3] = (byte) ((value >>> 24) & 0xFF);
	        bytes[4] = (byte) ((value >>> 32) & 0xFF);
	        bytes[5] = (byte) ((value >>> 40) & 0xFF);
	        bytes[6] = (byte) ((value >>> 48) & 0xFF);
	        bytes[7] = (byte) ((value >>> 56) & 0xFF);
        }
        else {
        	bytes[7] = (byte) (value & 0xFF);
	        bytes[6] = (byte) ((value >>> 8) & 0xFF);
	        bytes[5] = (byte) ((value >>> 16) & 0xFF);
	        bytes[4] = (byte) ((value >>> 24) & 0xFF);
	        bytes[3] = (byte) ((value >>> 32) & 0xFF);
	        bytes[2] = (byte) ((value >>> 40) & 0xFF);
	        bytes[1] = (byte) ((value >>> 48) & 0xFF);
	        bytes[0] = (byte) ((value >>> 56) & 0xFF);
        }
        return bytes;
    }
    
    public static long toInt64(byte[] bytes, int offset) {
    	if(bytes == null) {
			throw new IllegalArgumentException("bytes is null");
		}
		if(offset < 0) {
			throw new IllegalArgumentException("offset("+offset+") < 0");
		}
		if(offset + Long.BYTES > bytes.length) {
			throw new IllegalArgumentException("offset("+offset+") + Long.BYTES > bytes.length("+bytes.length+")");
		}
    	if (isLittleEndian) {
	        return ((bytes[offset] & 0xFFL)) |
	               ((bytes[offset + 1] & 0xFFL) << 8) |
	               ((bytes[offset + 2] & 0xFFL) << 16) |
	               ((bytes[offset + 3] & 0xFFL) << 24) |
	               ((bytes[offset + 4] & 0xFFL) << 32) |
	               ((bytes[offset + 5] & 0xFFL) << 40) |
	               ((bytes[offset + 6] & 0xFFL) << 48) |
	               ((bytes[offset + 7] & 0xFFL) << 56);
    	}
    	else {
    		return ((bytes[offset + 7] & 0xFFL)) |
 	               ((bytes[offset + 6] & 0xFFL) << 8) |
 	               ((bytes[offset + 5] & 0xFFL) << 16) |
 	               ((bytes[offset + 4] & 0xFFL) << 24) |
 	               ((bytes[offset + 3] & 0xFFL) << 32) |
 	               ((bytes[offset + 2] & 0xFFL) << 40) |
 	               ((bytes[offset + 1] & 0xFFL) << 48) |
 	               ((bytes[offset] & 0xFFL) << 56);
    	}
    }
    
    public static final long toInt64(byte[] bytes) {
		return toInt64(bytes,0);
	}
    
    
    public static final byte[] getBytes(float value) {
    	return getBytes(Float.floatToIntBits(value));
    }
    public static final float toSingle(byte[] bytes, int offset) {
    	return Float.intBitsToFloat(toInt32(bytes, offset));
    }
    public static final float toSingle(byte[] bytes) {
		return toSingle(bytes,0);
	}
    
    
    public static final byte[] getBytes(double value) {
    	return getBytes(Double.doubleToLongBits(value));
    }
    
    public static final double toDouble(byte[] bytes, int offset) {
    	return Double.longBitsToDouble(toInt64(bytes, offset));
    }
    
    public static final double toDouble(byte[] bytes) {
		return toDouble(bytes,0);
	}
    
	
}
