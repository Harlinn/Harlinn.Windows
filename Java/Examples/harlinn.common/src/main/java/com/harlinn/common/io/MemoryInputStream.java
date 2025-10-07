package com.harlinn.common.io;

import java.io.*;
import java.nio.ByteBuffer;

public class MemoryInputStream extends InputStream {
    ByteBuffer[] buffers;
    int currentBufferIndex;
    int currentBufferOffset;
    long size;
    
    public MemoryInputStream(ByteBuffer[] buffers) {
    	if(buffers == null) {
    		throw new IllegalArgumentException("buffers cannot be null");
    	}
    	this.buffers = buffers;
    	this.size = sizeOf(buffers);
    }
    
    private static long sizeOf(ByteBuffer[] buffers) {
    	long result = 0;
    	for(int i = 0; i < buffers.length; i++) {
    		var buffer = buffers[i];
    		result += buffer.limit();
    	}
    	return result;
    }
    
    
	@Override
	public int read() throws IOException {
		// TODO Auto-generated method stub
		return 0;
	}
    
}
