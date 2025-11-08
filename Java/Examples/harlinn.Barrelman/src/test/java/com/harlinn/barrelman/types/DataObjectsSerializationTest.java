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
