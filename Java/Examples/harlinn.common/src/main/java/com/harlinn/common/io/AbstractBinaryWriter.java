package com.harlinn.common.io;



public abstract class AbstractBinaryWriter {
	
	public abstract void writeInt8(byte value);
	public abstract void writeInt16(short value);
	public abstract void writeInt32(int value);
	public abstract void writeInt64(long value);
	
	public final void writeBoolean(boolean value) {
		writeInt8(value?(byte)1:(byte)0);
	}
	
	public final void writeNullableBoolean(Boolean value) {
		if(value != null) {
			writeBoolean(true);
			writeBoolean(value);
		}
		else {
			writeBoolean(false);
		}
	}
	
	
	
}
