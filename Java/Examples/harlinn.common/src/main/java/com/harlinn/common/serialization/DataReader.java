package com.harlinn.common.serialization;

import java.nio.ByteBuffer;

public class DataReader extends AbstractDataReader {

	private final java.io.InputStream stream;
	
	public DataReader(java.io.InputStream stream) {
		assert stream != null : "stream cannot be null.";
		this.stream = stream;
	}
	
	@Override
	protected byte readByte() {
		try {
			var value = stream.read();
			if(value == -1) {
				throw new java.io.UncheckedIOException(new java.io.EOFException());
			}
				
			return (byte)(value & 0xFF);
		}
		catch(java.io.IOException exc) {
			throw new java.io.UncheckedIOException(exc);
		}
	}

	@Override
	protected byte[] readBytes(int size) {
		try {
			var bytes = stream.readNBytes(size);
			return bytes;
		}
		catch(java.io.IOException exc) {
			throw new java.io.UncheckedIOException(exc);
		}
	}

}
