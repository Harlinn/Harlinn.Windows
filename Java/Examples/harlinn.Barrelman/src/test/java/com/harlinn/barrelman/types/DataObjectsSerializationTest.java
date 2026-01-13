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
package com.harlinn.barrelman.types;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.Random;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import com.harlinn.common.serialization.DataReader;
import com.harlinn.common.serialization.DataWriter;

class DataObjectsSerializationTest {

	@Test
	void test() {
		var testDataObjectFactory = new TestDataObjectFactory();
		var dataObjectFactory = new DataObjectFactory();
		
		var dataObjects = testDataObjectFactory.getDataObjects();
		var count = dataObjects.length;
		for(var dataObject : dataObjects) {
			var outStream = new ByteArrayOutputStream();
			var writer = new DataWriter(outStream);
			dataObject.writeTo(writer);
			
			var bytes = outStream.toByteArray();
			
			var inStream = new ByteArrayInputStream(bytes);
			var reader = new DataReader(inStream);
			
			var deserializedDataObject = dataObjectFactory.readFrom(reader);
			var areEqual = deserializedDataObject.equals(dataObject);
			assertTrue(areEqual);
			
		}
	}

}
