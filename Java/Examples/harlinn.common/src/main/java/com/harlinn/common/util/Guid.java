package com.harlinn.common.util;

import java.io.Serializable;
import java.util.UUID;

/**
 * Represents a globally unique identifier (GUID).
 * <p>
 * A GUID is a 128-bit integer (16 bytes) that can be used across all computers and networks wherever a unique identifier is required. Such an identifier has a very low probability of being duplicated.
 * </p>
 * <p>
 * Unlike the java.util.UUID class, Guid implements ordering that is compatible with the .Net struct Guid type.  
 * </p>
 */
public class Guid implements Serializable, Comparable<Guid> {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -8789793390805576598L;
	
	public static final int BYTES = 16; 
	
	private final int a;
	private final short b;
    private final short c;
    private final byte d;
    private final byte e;
    private final byte f;
    private final byte g;
    private final byte h;
    private final byte i;
    private final byte j;
    private final byte k;
	
	public Guid() {
		a = 0;
	    b = 0;
	    c = 0;
	    d = 0;
	    e = 0;
	    f = 0;
	    g = 0;
	    h = 0;
	    i = 0;
	    j = 0;
	    k = 0;
	}
	
	public Guid(int a, short b, short c, byte d, byte e, byte f, byte g, byte h, byte i, byte j, byte k ) {
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = d;
		this.e = e;
		this.f = f;
		this.g = g;
		this.h = h;
		this.i = i;
		this.j = j;
		this.k = k;
	}
	
	public Guid(int a, short b, short c, byte[] bytes ) {
		if(bytes == null) {
			throw new IllegalArgumentException("bytes == null");
		}
		if(bytes.length != 8) {
			throw new IllegalArgumentException("bytes.length("+bytes.length+") != 8");
		}
		this.a = a;
		this.b = b;
		this.c = c;
		this.d = bytes[0];
		this.e = bytes[1];
		this.f = bytes[2];
		this.g = bytes[3];
		this.h = bytes[4];
		this.i = bytes[5];
		this.j = bytes[6];
		this.k = bytes[7];
	}
	
	public Guid(byte[] bytes ) {
		if(bytes == null) {
			throw new IllegalArgumentException("bytes == null");
		}
		if(bytes.length != BYTES) {
			throw new IllegalArgumentException("bytes.length("+bytes.length+") != BYTES("+BYTES+")");
		}
		this.a = BitConverter.toInt32(bytes);
		this.b = BitConverter.toInt16(bytes,4);
		this.c = BitConverter.toInt16(bytes,6);
		this.d = bytes[8];
		this.e = bytes[9];
		this.f = bytes[10];
		this.g = bytes[11];
		this.h = bytes[12];
		this.i = bytes[13];
		this.j = bytes[14];
		this.k = bytes[15];
	}
	
	
	public int getA() {
		return a;
	}
	
	public int getData1() {
		return a;
	}

	public short getB() {
		return b;
	}
	
	public short getDats2() {
		return b;
	}

	public short getC() {
		return c;
	}
	
	public short getData3() {
		return c;
	}

	public byte getD() {
		return d;
	}

	public byte getE() {
		return e;
	}

	public byte getF() {
		return f;
	}

	public byte getG() {
		return g;
	}

	public byte getH() {
		return h;
	}

	public byte getI() {
		return i;
	}

	public byte getJ() {
		return j;
	}

	public byte getK() {
		return k;
	}
	
	public byte[] getData4() {
		byte[] result = {d,e,f,g,h,i,j,k};
		return result;
	}
	
	public byte[] toArray() {
		byte[] result = new byte[16];
		var data1 = BitConverter.getBytes(a);
		var data2 = BitConverter.getBytes(b);
		var data3 = BitConverter.getBytes(c);
		
		result[0] = data1[0]; 
		result[1] = data1[1];
		result[2] = data1[2];
		result[3] = data1[3];
		
		result[4] = data2[0]; 
		result[5] = data2[1];
		
		result[6] = data3[0]; 
		result[7] = data3[1];
		
		result[8] = d;
		result[9] = e;
		result[10] = f;
		result[11] = g;
		result[12] = h;
		result[13] = i;
		result[14] = j;
		result[15] = k;
		
		return result;
	}
	
	
	public UUID toUUID() {
		byte[] bytes = new byte[16];
		var data1 = BitConverter.getBytes(a);
		var data2 = BitConverter.getBytes(b);
		var data3 = BitConverter.getBytes(c);
		
		bytes[0] = data1[3]; 
		bytes[1] = data1[2];
		bytes[2] = data1[1];
		bytes[3] = data1[0];
		
		bytes[4] = data2[1]; 
		bytes[5] = data2[0];
		
		bytes[6] = data3[1]; 
		bytes[7] = data3[0];
		
		bytes[8] = d;
		bytes[9] = e;
		bytes[10] = f;
		bytes[11] = g;
		bytes[12] = h;
		bytes[13] = i;
		bytes[14] = j;
		bytes[15] = k;
		
		var msb = BitConverter.toInt64(bytes);
        var lsb = BitConverter.toInt64(bytes, 8);
		
        return new UUID(msb, lsb);
	}

	@Override
	public int compareTo(Guid other) {
		var result = Integer.compareUnsigned(a, other.a);
		if(result != 0)
		{
			return result;
		}
		result = Short.compareUnsigned(b, other.b);
		if(result != 0)
		{
			return result;
		}
		result = Short.compareUnsigned(c, other.c);
		if(result != 0)
		{
			return result;
		}
		result = Byte.compareUnsigned(d, other.d);
		if(result != 0)
		{
			return result;
		}
		result = Byte.compareUnsigned(e, other.e);
		if(result != 0)
		{
			return result;
		}
		result = Byte.compareUnsigned(f, other.f);
		if(result != 0)
		{
			return result;
		}
		result = Byte.compareUnsigned(g, other.g);
		if(result != 0)
		{
			return result;
		}
		result = Byte.compareUnsigned(h, other.h);
		if(result != 0)
		{
			return result;
		}
		result = Byte.compareUnsigned(i, other.i);
		if(result != 0)
		{
			return result;
		}
		result = Byte.compareUnsigned(j, other.j);
		if(result != 0)
		{
			return result;
		}
		result = Byte.compareUnsigned(k, other.k);
		return result;
	}
	
	
	public static final Guid newGuid()	{
		var bytes = com.harlinn.common.platform.Ole32.CoCreateGuid();
		return new Guid(bytes);
	}
	
	@Override
	public String toString() {
		var result = com.harlinn.common.platform.Ole32.StringFromGUID(a,b,c,d,e,f,g,h,i,j,k);
		return result;
	}
	
	
	
}
