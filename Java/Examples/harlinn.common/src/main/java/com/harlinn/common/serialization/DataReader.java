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
