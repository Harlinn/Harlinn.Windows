package com.harlinn.common.io;

import java.io.OutputStream;
import java.io.Closeable;
import java.io.IOException;

public class BinaryWriter implements Closeable {
	OutputStream output;
	
	public BinaryWriter(OutputStream output) {
		this.output = output;
	}

	@Override
	public void close() throws IOException {
		this.output.close();
	}
	
	public final void Write(int value) {
	}
	
	
}
