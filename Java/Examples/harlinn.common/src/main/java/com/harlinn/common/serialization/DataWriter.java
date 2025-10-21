package com.harlinn.common.serialization;

public class DataWriter extends AbstractDataWriter {

	private final java.io.OutputStream stream;
	public DataWriter(java.io.OutputStream stream) {
		assert stream != null : "stream cannot be null.";
		this.stream = stream;
	}
	
	@Override
	public void writeBytes(byte[] buffer, int offset, int count) {
		try {
			stream.write(buffer, offset, count);
		}
		catch(java.io.IOException exc) {
			throw new java.io.UncheckedIOException(exc);
		}
	}

}
