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

public class ByteSwap {

	public static final byte swapBytes(byte value) {
		return value;
	}
	
	public static final short swapBytes(short value) {
		return (short)((short) ((value & (short)0xFF00) >>> 8) | 
				(short) ((value & (short)0x00FF) << 8));
	}
	
	public static final int swapBytes(int value) {
		return (value << 24) |
	               ((value & 0x0000FF00) << 8) |
	               ((value & 0x00FF0000) >>> 8) |
	               (value >>> 24);
	}
	
	public static final long swapBytes(long value) {
		return ((value & 0x00000000000000FFL) << 56) |
	               ((value & 0x000000000000FF00L) << 40) |
	               ((value & 0x0000000000FF0000L) << 24) |
	               ((value & 0x00000000FF000000L) << 8)  |
	               ((value & 0x000000FF00000000L) >>> 8) |
	               ((value & 0x0000FF0000000000L) >>> 24) |
	               ((value & 0x00FF000000000000L) >>> 40) |
	               ((value & 0xFF00000000000000L) >>> 56);
	}
	
	
}
