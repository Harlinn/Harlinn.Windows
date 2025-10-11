package com.harlinn.common.io;

import java.io.InputStream;
import java.io.Closeable;
import java.io.IOException;


public class BinaryReader implements Closeable {
	InputStream input;
	
	public BinaryReader(InputStream input) {
		this.input = input;
	}

	@Override
	public void close() throws IOException {
		this.input.close();
		
	}
}
