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

import java.io.InputStream;
import java.io.OutputStream;
import java.util.Random;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import com.harlinn.common.util.Currency;
import com.harlinn.common.util.DateTime;
import com.harlinn.common.util.Guid;
import com.harlinn.common.util.TimeSpan;

class DataWriterDataReaderTest {

	
	@Test
	void booleanTest() {
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeBoolean(false);
		writer.writeBoolean(true);
		writer.writeNullableBoolean(null);
		writer.writeNullableBoolean(false);
		writer.writeNullableBoolean(true);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var falseValue = reader.readBoolean();
		assertFalse(falseValue);
		var trueValue = reader.readBoolean();
		assertTrue(trueValue);
		var nullNullableValue = reader.readNullableBoolean();
		assertNull(nullNullableValue);
		var falseNullableValue = reader.readNullableBoolean();
		assertNotNull(falseNullableValue);
		assertFalse(falseNullableValue);
		var trueNullableValue = reader.readNullableBoolean();
		assertNotNull(trueNullableValue);
		assertTrue(trueNullableValue);
	}
	
	@Test
	void charTest() {
		char zeroValue = (char)0;
		char oneValue = (char)1;
		char maxValue = (char)0xFFFF;
		char charValue = 'a';
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeChar(zeroValue);
		writer.writeChar(oneValue);
		writer.writeChar(maxValue);
		writer.writeChar(charValue);
		writer.writeNullableChar(null);
		writer.writeNullableChar(zeroValue);
		writer.writeNullableChar(oneValue);
		writer.writeNullableChar(maxValue);
		writer.writeNullableChar(charValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var zeroValueOut = reader.readChar();
		assertEquals(zeroValue,zeroValueOut);
		var oneValueOut = reader.readChar();
		assertEquals(oneValue,oneValueOut);
		var maxValueOut = reader.readChar();
		assertEquals(maxValue,maxValueOut);
		var charValueOut = reader.readChar();
		assertEquals(charValue,charValueOut);
		var nullNullableOut = reader.readNullableChar();
		assertNull(nullNullableOut);
		var zeroNullableValueOut = reader.readNullableChar();
		assertNotNull(zeroNullableValueOut);
		assertEquals(zeroValue,zeroNullableValueOut);
		var oneNullableValueOut = reader.readNullableChar();
		assertNotNull(oneNullableValueOut);
		assertEquals(oneValue,oneNullableValueOut);
		var maxNullableValueOut = reader.readNullableChar();
		assertNotNull(maxNullableValueOut);
		assertEquals(maxValue,maxNullableValueOut);
		var charNullableValueOut = reader.readNullableChar();
		assertNotNull(charNullableValueOut);
		assertEquals(charValue,charNullableValueOut);
	}
	
	@Test
	void uint8Test() {
		byte zeroValue = (byte)0;
		byte oneValue = (byte)1;
		byte maxValue = (byte)0xFF;
		byte otherValue = (byte)0x7F;
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeUInt8(zeroValue);
		writer.writeUInt8(oneValue);
		writer.writeUInt8(maxValue);
		writer.writeUInt8(otherValue);
		writer.writeNullableUInt8(null);
		writer.writeNullableUInt8(zeroValue);
		writer.writeNullableUInt8(oneValue);
		writer.writeNullableUInt8(maxValue);
		writer.writeNullableUInt8(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var zeroValueOut = reader.readUInt8();
		assertEquals(zeroValue,zeroValueOut);
		var oneValueOut = reader.readUInt8();
		assertEquals(oneValue,oneValueOut);
		var maxValueOut = reader.readUInt8();
		assertEquals(maxValue,maxValueOut);
		var otherValueOut = reader.readUInt8();
		assertEquals(otherValue,otherValueOut);
		var nullNullableOut = reader.readNullableUInt8();
		assertNull(nullNullableOut);
		var zeroNullableValueOut = reader.readNullableUInt8();
		assertNotNull(zeroNullableValueOut);
		assertEquals(zeroValue,zeroNullableValueOut);
		var oneNullableValueOut = reader.readNullableUInt8();
		assertNotNull(oneNullableValueOut);
		assertEquals(oneValue,oneNullableValueOut);
		var maxNullableValueOut = reader.readNullableUInt8();
		assertNotNull(maxNullableValueOut);
		assertEquals(maxValue,maxNullableValueOut);
		var otherNullableValueOut = reader.readNullableUInt8();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
	}
	
	@Test
	void int8Test() {
		byte minValue = Byte.MIN_VALUE;
		byte minusOneValue = (byte)-1;
		byte zeroValue = (byte)0;
		byte oneValue = (byte)1;
		byte maxValue = Byte.MAX_VALUE;
		byte otherValue = (byte)0x20;
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeInt8(minValue);
		writer.writeInt8(minusOneValue);
		writer.writeInt8(zeroValue);
		writer.writeInt8(oneValue);
		writer.writeInt8(maxValue);
		writer.writeInt8(otherValue);
		writer.writeNullableInt8(null);
		writer.writeNullableInt8(minValue);
		writer.writeNullableInt8(minusOneValue);
		writer.writeNullableInt8(zeroValue);
		writer.writeNullableInt8(oneValue);
		writer.writeNullableInt8(maxValue);
		writer.writeNullableInt8(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var minValueOut = reader.readInt8();
		assertEquals(minValue,minValueOut);
		var minusOneValueOut = reader.readInt8();
		assertEquals(minusOneValue,minusOneValueOut);
		var zeroValueOut = reader.readInt8();
		assertEquals(zeroValue,zeroValueOut);
		var oneValueOut = reader.readInt8();
		assertEquals(oneValue,oneValueOut);
		var maxValueOut = reader.readInt8();
		assertEquals(maxValue,maxValueOut);
		var otherValueOut = reader.readInt8();
		assertEquals(otherValue,otherValueOut);
		var nullNullableOut = reader.readNullableInt8();
		assertNull(nullNullableOut);
		
		var minNullableValueOut = reader.readNullableInt8();
		assertNotNull(minNullableValueOut);
		assertEquals(minValue,minNullableValueOut);
		var minusOneNullableValueOut = reader.readNullableInt8();
		assertNotNull(minusOneNullableValueOut);
		assertEquals(minusOneValue,minusOneNullableValueOut);
		var zeroNullableValueOut = reader.readNullableInt8();
		assertNotNull(zeroNullableValueOut);
		assertEquals(zeroValue,zeroNullableValueOut);
		var oneNullableValueOut = reader.readNullableInt8();
		assertNotNull(oneNullableValueOut);
		assertEquals(oneValue,oneNullableValueOut);
		var maxNullableValueOut = reader.readNullableInt8();
		assertNotNull(maxNullableValueOut);
		assertEquals(maxValue,maxNullableValueOut);
		var otherNullableValueOut = reader.readNullableInt8();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
	}
	
	@Test
	void uint16Test() {
		short zeroValue = (short)0;
		short oneValue = (short)1;
		short maxValue = (short)0xFFFF;
		short otherValue = (short)0x7FFF;
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeUInt16(zeroValue);
		writer.writeUInt16(oneValue);
		writer.writeUInt16(maxValue);
		writer.writeUInt16(otherValue);
		writer.writeNullableUInt16(null);
		writer.writeNullableUInt16(zeroValue);
		writer.writeNullableUInt16(oneValue);
		writer.writeNullableUInt16(maxValue);
		writer.writeNullableUInt16(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var zeroValueOut = reader.readUInt16();
		assertEquals(zeroValue,zeroValueOut);
		var oneValueOut = reader.readUInt16();
		assertEquals(oneValue,oneValueOut);
		var maxValueOut = reader.readUInt16();
		assertEquals(maxValue,maxValueOut);
		var otherValueOut = reader.readUInt16();
		assertEquals(otherValue,otherValueOut);
		var nullNullableOut = reader.readNullableUInt16();
		assertNull(nullNullableOut);
		var zeroNullableValueOut = reader.readNullableUInt16();
		assertNotNull(zeroNullableValueOut);
		assertEquals(zeroValue,zeroNullableValueOut);
		var oneNullableValueOut = reader.readNullableUInt16();
		assertNotNull(oneNullableValueOut);
		assertEquals(oneValue,oneNullableValueOut);
		var maxNullableValueOut = reader.readNullableUInt16();
		assertNotNull(maxNullableValueOut);
		assertEquals(maxValue,maxNullableValueOut);
		var otherNullableValueOut = reader.readNullableUInt16();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
	}
	
	@Test
	void int16Test() {
		short minValue = Short.MIN_VALUE;
		short minusOneValue = (short)-1;
		short zeroValue = (short)0;
		short oneValue = (short)1;
		short maxValue = Short.MAX_VALUE;
		short otherValue = (short)0x20;
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeInt16(minValue);
		writer.writeInt16(minusOneValue);
		writer.writeInt16(zeroValue);
		writer.writeInt16(oneValue);
		writer.writeInt16(maxValue);
		writer.writeInt16(otherValue);
		writer.writeNullableInt16(null);
		writer.writeNullableInt16(minValue);
		writer.writeNullableInt16(minusOneValue);
		writer.writeNullableInt16(zeroValue);
		writer.writeNullableInt16(oneValue);
		writer.writeNullableInt16(maxValue);
		writer.writeNullableInt16(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var minValueOut = reader.readInt16();
		assertEquals(minValue,minValueOut);
		var minusOneValueOut = reader.readInt16();
		assertEquals(minusOneValue,minusOneValueOut);
		var zeroValueOut = reader.readInt16();
		assertEquals(zeroValue,zeroValueOut);
		var oneValueOut = reader.readInt16();
		assertEquals(oneValue,oneValueOut);
		var maxValueOut = reader.readInt16();
		assertEquals(maxValue,maxValueOut);
		var otherValueOut = reader.readInt16();
		assertEquals(otherValue,otherValueOut);
		var nullNullableOut = reader.readNullableInt16();
		assertNull(nullNullableOut);
		
		var minNullableValueOut = reader.readNullableInt16();
		assertNotNull(minNullableValueOut);
		assertEquals(minValue,minNullableValueOut);
		var minusOneNullableValueOut = reader.readNullableInt16();
		assertNotNull(minusOneNullableValueOut);
		assertEquals(minusOneValue,minusOneNullableValueOut);
		var zeroNullableValueOut = reader.readNullableInt16();
		assertNotNull(zeroNullableValueOut);
		assertEquals(zeroValue,zeroNullableValueOut);
		var oneNullableValueOut = reader.readNullableInt16();
		assertNotNull(oneNullableValueOut);
		assertEquals(oneValue,oneNullableValueOut);
		var maxNullableValueOut = reader.readNullableInt16();
		assertNotNull(maxNullableValueOut);
		assertEquals(maxValue,maxNullableValueOut);
		var otherNullableValueOut = reader.readNullableInt16();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
	}
	
	@Test
	void uint32Test() {
		int zeroValue = (int)0;
		int oneValue = (int)1;
		int maxValue = (int)0xFFFFFFFF;
		int otherValue = (int)0x7FFFFFFF;
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeUInt32(zeroValue);
		writer.writeUInt32(oneValue);
		writer.writeUInt32(maxValue);
		writer.writeUInt32(otherValue);
		writer.writeNullableUInt32(null);
		writer.writeNullableUInt32(zeroValue);
		writer.writeNullableUInt32(oneValue);
		writer.writeNullableUInt32(maxValue);
		writer.writeNullableUInt32(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var zeroValueOut = reader.readUInt32();
		assertEquals(zeroValue,zeroValueOut);
		var oneValueOut = reader.readUInt32();
		assertEquals(oneValue,oneValueOut);
		var maxValueOut = reader.readUInt32();
		assertEquals(maxValue,maxValueOut);
		var otherValueOut = reader.readUInt32();
		assertEquals(otherValue,otherValueOut);
		var nullNullableOut = reader.readNullableUInt32();
		assertNull(nullNullableOut);
		var zeroNullableValueOut = reader.readNullableUInt32();
		assertNotNull(zeroNullableValueOut);
		assertEquals(zeroValue,zeroNullableValueOut);
		var oneNullableValueOut = reader.readNullableUInt32();
		assertNotNull(oneNullableValueOut);
		assertEquals(oneValue,oneNullableValueOut);
		var maxNullableValueOut = reader.readNullableUInt32();
		assertNotNull(maxNullableValueOut);
		assertEquals(maxValue,maxNullableValueOut);
		var otherNullableValueOut = reader.readNullableUInt32();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
	}
	
	@Test
	void int32Test() {
		int minValue = Integer.MIN_VALUE;
		int minusOneValue = (int)-1;
		int zeroValue = (int)0;
		int oneValue = (int)1;
		int maxValue = Integer.MAX_VALUE;
		int otherValue = (int)0x20;
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeInt32(minValue);
		writer.writeInt32(minusOneValue);
		writer.writeInt32(zeroValue);
		writer.writeInt32(oneValue);
		writer.writeInt32(maxValue);
		writer.writeInt32(otherValue);
		writer.writeNullableInt32(null);
		writer.writeNullableInt32(minValue);
		writer.writeNullableInt32(minusOneValue);
		writer.writeNullableInt32(zeroValue);
		writer.writeNullableInt32(oneValue);
		writer.writeNullableInt32(maxValue);
		writer.writeNullableInt32(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var minValueOut = reader.readInt32();
		assertEquals(minValue,minValueOut);
		var minusOneValueOut = reader.readInt32();
		assertEquals(minusOneValue,minusOneValueOut);
		var zeroValueOut = reader.readInt32();
		assertEquals(zeroValue,zeroValueOut);
		var oneValueOut = reader.readInt32();
		assertEquals(oneValue,oneValueOut);
		var maxValueOut = reader.readInt32();
		assertEquals(maxValue,maxValueOut);
		var otherValueOut = reader.readInt32();
		assertEquals(otherValue,otherValueOut);
		var nullNullableOut = reader.readNullableInt32();
		assertNull(nullNullableOut);
		
		var minNullableValueOut = reader.readNullableInt32();
		assertNotNull(minNullableValueOut);
		assertEquals(minValue,minNullableValueOut);
		var minusOneNullableValueOut = reader.readNullableInt32();
		assertNotNull(minusOneNullableValueOut);
		assertEquals(minusOneValue,minusOneNullableValueOut);
		var zeroNullableValueOut = reader.readNullableInt32();
		assertNotNull(zeroNullableValueOut);
		assertEquals(zeroValue,zeroNullableValueOut);
		var oneNullableValueOut = reader.readNullableInt32();
		assertNotNull(oneNullableValueOut);
		assertEquals(oneValue,oneNullableValueOut);
		var maxNullableValueOut = reader.readNullableInt32();
		assertNotNull(maxNullableValueOut);
		assertEquals(maxValue,maxNullableValueOut);
		var otherNullableValueOut = reader.readNullableInt32();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
	}
	
	@Test
	void uint64Test() {
		long zeroValue = (long)0;
		long oneValue = (long)1;
		long maxValue = 0xFFFFFFFFFFFFFFFFL;
		long otherValue = 0x7FFFFFFFFFFFFFFFL;
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeUInt64(zeroValue);
		writer.writeUInt64(oneValue);
		writer.writeUInt64(maxValue);
		writer.writeUInt64(otherValue);
		writer.writeNullableUInt64(null);
		writer.writeNullableUInt64(zeroValue);
		writer.writeNullableUInt64(oneValue);
		writer.writeNullableUInt64(maxValue);
		writer.writeNullableUInt64(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var zeroValueOut = reader.readUInt64();
		assertEquals(zeroValue,zeroValueOut);
		var oneValueOut = reader.readUInt64();
		assertEquals(oneValue,oneValueOut);
		var maxValueOut = reader.readUInt64();
		assertEquals(maxValue,maxValueOut);
		var otherValueOut = reader.readUInt64();
		assertEquals(otherValue,otherValueOut);
		var nullNullableOut = reader.readNullableUInt64();
		assertNull(nullNullableOut);
		var zeroNullableValueOut = reader.readNullableUInt64();
		assertNotNull(zeroNullableValueOut);
		assertEquals(zeroValue,zeroNullableValueOut);
		var oneNullableValueOut = reader.readNullableUInt64();
		assertNotNull(oneNullableValueOut);
		assertEquals(oneValue,oneNullableValueOut);
		var maxNullableValueOut = reader.readNullableUInt64();
		assertNotNull(maxNullableValueOut);
		assertEquals(maxValue,maxNullableValueOut);
		var otherNullableValueOut = reader.readNullableUInt64();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
	}
	
	@Test
	void int64Test() {
		long minValue = Long.MIN_VALUE;
		long minusOneValue = (long)-1;
		long zeroValue = (long)0;
		long oneValue = (long)1;
		long maxValue = Long.MAX_VALUE;
		long otherValue = (long)0x20;
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeInt64(minValue);
		writer.writeInt64(minusOneValue);
		writer.writeInt64(zeroValue);
		writer.writeInt64(oneValue);
		writer.writeInt64(maxValue);
		writer.writeInt64(otherValue);
		writer.writeNullableInt64(null);
		writer.writeNullableInt64(minValue);
		writer.writeNullableInt64(minusOneValue);
		writer.writeNullableInt64(zeroValue);
		writer.writeNullableInt64(oneValue);
		writer.writeNullableInt64(maxValue);
		writer.writeNullableInt64(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var minValueOut = reader.readInt64();
		assertEquals(minValue,minValueOut);
		var minusOneValueOut = reader.readInt64();
		assertEquals(minusOneValue,minusOneValueOut);
		var zeroValueOut = reader.readInt64();
		assertEquals(zeroValue,zeroValueOut);
		var oneValueOut = reader.readInt64();
		assertEquals(oneValue,oneValueOut);
		var maxValueOut = reader.readInt64();
		assertEquals(maxValue,maxValueOut);
		var otherValueOut = reader.readInt64();
		assertEquals(otherValue,otherValueOut);
		var nullNullableOut = reader.readNullableInt64();
		assertNull(nullNullableOut);
		
		var minNullableValueOut = reader.readNullableInt64();
		assertNotNull(minNullableValueOut);
		assertEquals(minValue,minNullableValueOut);
		var minusOneNullableValueOut = reader.readNullableInt64();
		assertNotNull(minusOneNullableValueOut);
		assertEquals(minusOneValue,minusOneNullableValueOut);
		var zeroNullableValueOut = reader.readNullableInt64();
		assertNotNull(zeroNullableValueOut);
		assertEquals(zeroValue,zeroNullableValueOut);
		var oneNullableValueOut = reader.readNullableInt64();
		assertNotNull(oneNullableValueOut);
		assertEquals(oneValue,oneNullableValueOut);
		var maxNullableValueOut = reader.readNullableInt64();
		assertNotNull(maxNullableValueOut);
		assertEquals(maxValue,maxNullableValueOut);
		var otherNullableValueOut = reader.readNullableInt64();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
	}
	
	@Test
	void singleTest() {
		float negativeInfinityValue = Float.NEGATIVE_INFINITY;
		float minValue = -Float.MAX_VALUE;
		float minusOneValue = -1.f;
		float zeroValue = 0.f;
		float oneValue = 1.f;
		float maxValue = Float.MAX_VALUE;
		float positiveInfinityValue = Float.POSITIVE_INFINITY;
		float nanValue = Float.NaN;
		float otherValue = (float)Math.PI;
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeSingle(negativeInfinityValue);
		writer.writeSingle(minValue);
		writer.writeSingle(minusOneValue);
		writer.writeSingle(zeroValue);
		writer.writeSingle(oneValue);
		writer.writeSingle(maxValue);
		writer.writeSingle(positiveInfinityValue);
		writer.writeSingle(nanValue);
		writer.writeSingle(otherValue);
		writer.writeNullableSingle(null);
		writer.writeNullableSingle(negativeInfinityValue);
		writer.writeNullableSingle(minValue);
		writer.writeNullableSingle(minusOneValue);
		writer.writeNullableSingle(zeroValue);
		writer.writeNullableSingle(oneValue);
		writer.writeNullableSingle(maxValue);
		writer.writeNullableSingle(positiveInfinityValue);
		writer.writeNullableSingle(nanValue);
		writer.writeNullableSingle(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var negativeInfinityValueOut = reader.readSingle();
		assertEquals(negativeInfinityValue,negativeInfinityValueOut);
		var minValueOut = reader.readSingle();
		assertEquals(minValue,minValueOut);
		var minusOneValueOut = reader.readSingle();
		assertEquals(minusOneValue,minusOneValueOut);
		var zeroValueOut = reader.readSingle();
		assertEquals(zeroValue,zeroValueOut);
		var oneValueOut = reader.readSingle();
		assertEquals(oneValue,oneValueOut);
		var maxValueOut = reader.readSingle();
		assertEquals(maxValue,maxValueOut);
		var positiveInfinityValueOut = reader.readSingle();
		assertEquals(positiveInfinityValue,positiveInfinityValueOut);
		var nanValueOut = reader.readSingle();
		assertTrue(Float.isNaN( nanValueOut ) );
		var otherValueOut = reader.readSingle();
		assertEquals(otherValue,otherValueOut);
		var nullNullableOut = reader.readNullableSingle();
		assertNull(nullNullableOut);
		
		var negativeInfinityNullableValueOut = reader.readNullableSingle();
		assertNotNull(negativeInfinityNullableValueOut);
		assertEquals(negativeInfinityValue,negativeInfinityNullableValueOut);
		var minNullableValueOut = reader.readNullableSingle();
		assertNotNull(minNullableValueOut);
		assertEquals(minValue,minNullableValueOut);
		var minusOneNullableValueOut = reader.readNullableSingle();
		assertNotNull(minusOneNullableValueOut);
		assertEquals(minusOneValue,minusOneNullableValueOut);
		var zeroNullableValueOut = reader.readNullableSingle();
		assertNotNull(zeroNullableValueOut);
		assertEquals(zeroValue,zeroNullableValueOut);
		var oneNullableValueOut = reader.readNullableSingle();
		assertNotNull(oneNullableValueOut);
		assertEquals(oneValue,oneNullableValueOut);
		var maxNullableValueOut = reader.readNullableSingle();
		assertNotNull(maxNullableValueOut);
		assertEquals(maxValue,maxNullableValueOut);
		
		var positiveInfinityNullableValueOut = reader.readNullableSingle();
		assertNotNull(positiveInfinityNullableValueOut);
		assertEquals(positiveInfinityValue,positiveInfinityNullableValueOut);
		
		var nanNullableValueOut = reader.readNullableSingle();
		assertNotNull(nanNullableValueOut);
		assertTrue(Float.isNaN( nanNullableValueOut ) );
		
		var otherNullableValueOut = reader.readNullableSingle();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
	}
	
	@Test
	void doubleTest() {
		double negativeInfinityValue = Double.NEGATIVE_INFINITY;
		double minValue = -Double.MAX_VALUE;
		double minusOneValue = -1.;
		double zeroValue = 0.;
		double oneValue = 1.;
		double maxValue = Double.MAX_VALUE;
		double positiveInfinityValue = Double.POSITIVE_INFINITY;
		double nanValue = Double.NaN;
		double otherValue = Math.PI;
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeDouble(negativeInfinityValue);
		writer.writeDouble(minValue);
		writer.writeDouble(minusOneValue);
		writer.writeDouble(zeroValue);
		writer.writeDouble(oneValue);
		writer.writeDouble(maxValue);
		writer.writeDouble(positiveInfinityValue);
		writer.writeDouble(nanValue);
		writer.writeDouble(otherValue);
		writer.writeNullableDouble(null);
		writer.writeNullableDouble(negativeInfinityValue);
		writer.writeNullableDouble(minValue);
		writer.writeNullableDouble(minusOneValue);
		writer.writeNullableDouble(zeroValue);
		writer.writeNullableDouble(oneValue);
		writer.writeNullableDouble(maxValue);
		writer.writeNullableDouble(positiveInfinityValue);
		writer.writeNullableDouble(nanValue);
		writer.writeNullableDouble(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var negativeInfinityValueOut = reader.readDouble();
		assertEquals(negativeInfinityValue,negativeInfinityValueOut);
		var minValueOut = reader.readDouble();
		assertEquals(minValue,minValueOut);
		var minusOneValueOut = reader.readDouble();
		assertEquals(minusOneValue,minusOneValueOut);
		var zeroValueOut = reader.readDouble();
		assertEquals(zeroValue,zeroValueOut);
		var oneValueOut = reader.readDouble();
		assertEquals(oneValue,oneValueOut);
		var maxValueOut = reader.readDouble();
		assertEquals(maxValue,maxValueOut);
		var positiveInfinityValueOut = reader.readDouble();
		assertEquals(positiveInfinityValue,positiveInfinityValueOut);
		var nanValueOut = reader.readDouble();
		assertTrue(Double.isNaN( nanValueOut ) );
		var otherValueOut = reader.readDouble();
		assertEquals(otherValue,otherValueOut);
		var nullNullableOut = reader.readNullableDouble();
		assertNull(nullNullableOut);
		
		var negativeInfinityNullableValueOut = reader.readNullableDouble();
		assertNotNull(negativeInfinityNullableValueOut);
		assertEquals(negativeInfinityValue,negativeInfinityNullableValueOut);
		var minNullableValueOut = reader.readNullableDouble();
		assertNotNull(minNullableValueOut);
		assertEquals(minValue,minNullableValueOut);
		var minusOneNullableValueOut = reader.readNullableDouble();
		assertNotNull(minusOneNullableValueOut);
		assertEquals(minusOneValue,minusOneNullableValueOut);
		var zeroNullableValueOut = reader.readNullableDouble();
		assertNotNull(zeroNullableValueOut);
		assertEquals(zeroValue,zeroNullableValueOut);
		var oneNullableValueOut = reader.readNullableDouble();
		assertNotNull(oneNullableValueOut);
		assertEquals(oneValue,oneNullableValueOut);
		var maxNullableValueOut = reader.readNullableDouble();
		assertNotNull(maxNullableValueOut);
		assertEquals(maxValue,maxNullableValueOut);
		
		var positiveInfinityNullableValueOut = reader.readNullableDouble();
		assertNotNull(positiveInfinityNullableValueOut);
		assertEquals(positiveInfinityValue,positiveInfinityNullableValueOut);
		
		var nanNullableValueOut = reader.readNullableDouble();
		assertNotNull(nanNullableValueOut);
		assertTrue(Double.isNaN( nanNullableValueOut ) );
		
		var otherNullableValueOut = reader.readNullableDouble();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
	}
	
	
	@Test
	void currencyTest() {
		Currency minValue = Currency.MIN_VALUE;
		Currency minusOneValue = new Currency( -1L );
		Currency zeroValue = new Currency( 0L );
		Currency oneValue = new Currency( 1L );
		Currency maxValue = Currency.MAX_VALUE;
		Currency otherValue = new Currency( 1L );
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeCurrency(minValue);
		writer.writeCurrency(minusOneValue);
		writer.writeCurrency(zeroValue);
		writer.writeCurrency(oneValue);
		writer.writeCurrency(maxValue);
		writer.writeCurrency(otherValue);
		writer.writeNullableCurrency(null);
		writer.writeNullableCurrency(minValue);
		writer.writeNullableCurrency(minusOneValue);
		writer.writeNullableCurrency(zeroValue);
		writer.writeNullableCurrency(oneValue);
		writer.writeNullableCurrency(maxValue);
		writer.writeNullableCurrency(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var minValueOut = reader.readCurrency();
		assertEquals(minValue,minValueOut);
		var minusOneValueOut = reader.readCurrency();
		assertEquals(minusOneValue,minusOneValueOut);
		var zeroValueOut = reader.readCurrency();
		assertEquals(zeroValue,zeroValueOut);
		var oneValueOut = reader.readCurrency();
		assertEquals(oneValue,oneValueOut);
		var maxValueOut = reader.readCurrency();
		assertEquals(maxValue,maxValueOut);
		var otherValueOut = reader.readCurrency();
		assertEquals(otherValue,otherValueOut);
		var nullNullableOut = reader.readNullableCurrency();
		assertNull(nullNullableOut);
		
		var minNullableValueOut = reader.readNullableCurrency();
		assertNotNull(minNullableValueOut);
		assertEquals(minValue,minNullableValueOut);
		var minusOneNullableValueOut = reader.readNullableCurrency();
		assertNotNull(minusOneNullableValueOut);
		assertEquals(minusOneValue,minusOneNullableValueOut);
		var zeroNullableValueOut = reader.readNullableCurrency();
		assertNotNull(zeroNullableValueOut);
		assertEquals(zeroValue,zeroNullableValueOut);
		var oneNullableValueOut = reader.readNullableCurrency();
		assertNotNull(oneNullableValueOut);
		assertEquals(oneValue,oneNullableValueOut);
		var maxNullableValueOut = reader.readNullableCurrency();
		assertNotNull(maxNullableValueOut);
		assertEquals(maxValue,maxNullableValueOut);
		var otherNullableValueOut = reader.readNullableCurrency();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
	}
	
	@Test
	void dateTimeTest() {
		
		var emptyValue = new DateTime(); 
		var otherValue = new DateTime(2025,10,21,13,30,0);
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeDateTime(emptyValue);
		writer.writeDateTime(otherValue);
		writer.writeNullableDateTime(null);
		writer.writeNullableDateTime(emptyValue);
		writer.writeNullableDateTime(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyValueOut = reader.readDateTime();
		assertEquals(emptyValue,emptyValueOut);
		var otherValueOut = reader.readDateTime();
		assertEquals(otherValue,otherValueOut);
		
		var nullNullableOut = reader.readNullableDateTime();
		assertNull(nullNullableOut);
		
		var emptyNullableValueOut = reader.readNullableDateTime();
		assertNotNull(emptyNullableValueOut);
		assertEquals(emptyValue,emptyNullableValueOut);
		
		var otherNullableValueOut = reader.readNullableDateTime();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
		
	}
	
	@Test
	void timeSpanTest() {
		
		var emptyValue = new TimeSpan(); 
		var otherValue = TimeSpan.fromHours(3);
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeTimeSpan(emptyValue);
		writer.writeTimeSpan(otherValue);
		writer.writeNullableTimeSpan(null);
		writer.writeNullableTimeSpan(emptyValue);
		writer.writeNullableTimeSpan(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyValueOut = reader.readTimeSpan();
		assertEquals(emptyValue,emptyValueOut);
		var otherValueOut = reader.readTimeSpan();
		assertEquals(otherValue,otherValueOut);
		
		var nullNullableOut = reader.readNullableTimeSpan();
		assertNull(nullNullableOut);
		
		var emptyNullableValueOut = reader.readNullableTimeSpan();
		assertNotNull(emptyNullableValueOut);
		assertEquals(emptyValue,emptyNullableValueOut);
		
		var otherNullableValueOut = reader.readNullableTimeSpan();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
		
	}
	
	@Test
	void guidTest() {
		
		var emptyValue = new Guid(); 
		var otherValue = Guid.fromString("{942E3BCE-3F05-4799-A196-0F7BC5389D70}");
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeGuid(emptyValue);
		writer.writeGuid(otherValue);
		writer.writeNullableGuid(null);
		writer.writeNullableGuid(emptyValue);
		writer.writeNullableGuid(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyValueOut = reader.readGuid();
		assertEquals(emptyValue,emptyValueOut);
		var otherValueOut = reader.readGuid();
		assertEquals(otherValue,otherValueOut);
		
		var nullNullableOut = reader.readNullableGuid();
		assertNull(nullNullableOut);
		
		var emptyNullableValueOut = reader.readNullableGuid();
		assertNotNull(emptyNullableValueOut);
		assertEquals(emptyValue,emptyNullableValueOut);
		
		var otherNullableValueOut = reader.readNullableGuid();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
		
	}
	
	@Test
	void stringTest() {
		
		var emptyValue = new String(); 
		var otherValue = "{942E3BCE-3F05-4799-A196-0F7BC5389D70}";
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeStringUtf8(emptyValue);
		writer.writeStringUtf8(otherValue);
		writer.writeNullableStringUtf8(null);
		writer.writeNullableStringUtf8(emptyValue);
		writer.writeNullableStringUtf8(otherValue);
		
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyValueOut = reader.readString();
		assertEquals(emptyValue,emptyValueOut);
		var otherValueOut = reader.readString();
		assertEquals(otherValue,otherValueOut);
		
		var nullNullableOut = reader.readNullableString();
		assertNull(nullNullableOut);
		
		var emptyNullableValueOut = reader.readNullableString();
		assertNotNull(emptyNullableValueOut);
		assertEquals(emptyValue,emptyNullableValueOut);
		
		var otherNullableValueOut = reader.readNullableString();
		assertNotNull(otherNullableValueOut);
		assertEquals(otherValue,otherNullableValueOut);
		
	}
	
	void fill(boolean[] array) {
		Random random = new Random();
		var count = array.length;
		for(int i = 0; i < count; i++) {
			array[i] = random.nextBoolean();
		}
	}
	void fill(byte[] array) {
		Random random = new Random();
		random.nextBytes(array);
	}
	void fill(char[] array) {
		Random random = new Random();
		var count = array.length;
		for(int i = 0; i < count; i++) {
			array[i] = (char)random.nextInt();
		}
	}
	void fill(short[] array) {
		Random random = new Random();
		var count = array.length;
		for(int i = 0; i < count; i++) {
			array[i] = (short)random.nextInt();
		}
	}
	void fill(int[] array) {
		Random random = new Random();
		var count = array.length;
		for(int i = 0; i < count; i++) {
			array[i] = random.nextInt();
		}
	}
	void fill(long[] array) {
		Random random = new Random();
		var count = array.length;
		for(int i = 0; i < count; i++) {
			array[i] = random.nextLong();
		}
	}
	void fill(float[] array) {
		Random random = new Random();
		var count = array.length;
		for(int i = 0; i < count; i++) {
			array[i] = random.nextFloat();
		}
	}
	void fill(double[] array) {
		Random random = new Random();
		var count = array.length;
		for(int i = 0; i < count; i++) {
			array[i] = random.nextDouble();
		}
	}
	void fill(DateTime[] array) {
		Random random = new Random();
		var count = array.length;
		for(int i = 0; i < count; i++) {
			array[i] = new DateTime( random.nextLong() );
		}
	}
	
	void fill(TimeSpan[] array) {
		Random random = new Random();
		var count = array.length;
		for(int i = 0; i < count; i++) {
			array[i] = new TimeSpan( random.nextLong() );
		}
	}
	
	void fill(Guid[] array) {
		Random random = new Random();
		var count = array.length;
		for(int i = 0; i < count; i++) {
			array[i] = new Guid( random.nextLong(), random.nextLong() );
		}
	}
	
	void fill(String[] array) {
		
		Random random = new Random();
		var count = array.length;
		for(int i = 0; i < count; i++) {
			array[i] = new Guid( random.nextLong(), random.nextLong() ).toString();
		}
	}
	
	void fill(byte[][] array) {
		
		Random random = new Random();
		var count = array.length;
		for(int i = 0; i < count; i++) {
			array[i] = new Guid( random.nextLong(), random.nextLong() ).toArray();
		}
	}
	
	
	
	@Test
	void booleanArrayTest() {
		var emptyArray = new boolean[0];
		var smallArray = new boolean[10];
		var array = new boolean[1000];
		var largeArray = new boolean[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeBooleanArray(emptyArray);
		writer.writeBooleanArray(smallArray);
		writer.writeBooleanArray(array);
		writer.writeBooleanArray(largeArray);
		writer.writeNullableBooleanArray(null);
		writer.writeNullableBooleanArray(emptyArray);
		writer.writeNullableBooleanArray(smallArray);
		writer.writeNullableBooleanArray(array);
		writer.writeNullableBooleanArray(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readBooleanArray();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readBooleanArray();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readBooleanArray();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readBooleanArray();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableBooleanArray();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableBooleanArray();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableBooleanArray();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableBooleanArray();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableBooleanArray();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	@Test
	void charArrayTest() {
		var emptyArray = new char[0];
		var smallArray = new char[10];
		var array = new char[1000];
		var largeArray = new char[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeCharArray(emptyArray);
		writer.writeCharArray(smallArray);
		writer.writeCharArray(array);
		writer.writeCharArray(largeArray);
		writer.writeNullableCharArray(null);
		writer.writeNullableCharArray(emptyArray);
		writer.writeNullableCharArray(smallArray);
		writer.writeNullableCharArray(array);
		writer.writeNullableCharArray(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readCharArray();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readCharArray();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readCharArray();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readCharArray();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableCharArray();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableCharArray();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableCharArray();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableCharArray();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableCharArray();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	@Test
	void uint8ArrayTest() {
		var emptyArray = new byte[0];
		var smallArray = new byte[10];
		var array = new byte[1000];
		var largeArray = new byte[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeUInt8Array(emptyArray);
		writer.writeUInt8Array(smallArray);
		writer.writeUInt8Array(array);
		writer.writeUInt8Array(largeArray);
		writer.writeNullableUInt8Array(null);
		writer.writeNullableUInt8Array(emptyArray);
		writer.writeNullableUInt8Array(smallArray);
		writer.writeNullableUInt8Array(array);
		writer.writeNullableUInt8Array(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readUInt8Array();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readUInt8Array();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readUInt8Array();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readUInt8Array();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableUInt8Array();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableUInt8Array();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableUInt8Array();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableUInt8Array();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableUInt8Array();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	@Test
	void int8ArrayTest() {
		var emptyArray = new byte[0];
		var smallArray = new byte[10];
		var array = new byte[1000];
		var largeArray = new byte[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeInt8Array(emptyArray);
		writer.writeInt8Array(smallArray);
		writer.writeInt8Array(array);
		writer.writeInt8Array(largeArray);
		writer.writeNullableInt8Array(null);
		writer.writeNullableInt8Array(emptyArray);
		writer.writeNullableInt8Array(smallArray);
		writer.writeNullableInt8Array(array);
		writer.writeNullableInt8Array(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readInt8Array();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readInt8Array();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readInt8Array();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readInt8Array();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableInt8Array();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableInt8Array();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableInt8Array();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableInt8Array();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableInt8Array();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	@Test
	void uint16ArrayTest() {
		var emptyArray = new short[0];
		var smallArray = new short[10];
		var array = new short[1000];
		var largeArray = new short[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeUInt16Array(emptyArray);
		writer.writeUInt16Array(smallArray);
		writer.writeUInt16Array(array);
		writer.writeUInt16Array(largeArray);
		writer.writeNullableUInt16Array(null);
		writer.writeNullableUInt16Array(emptyArray);
		writer.writeNullableUInt16Array(smallArray);
		writer.writeNullableUInt16Array(array);
		writer.writeNullableUInt16Array(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readUInt16Array();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readUInt16Array();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readUInt16Array();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readUInt16Array();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableUInt16Array();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableUInt16Array();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableUInt16Array();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableUInt16Array();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableUInt16Array();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	@Test
	void int16ArrayTest() {
		var emptyArray = new short[0];
		var smallArray = new short[10];
		var array = new short[1000];
		var largeArray = new short[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeInt16Array(emptyArray);
		writer.writeInt16Array(smallArray);
		writer.writeInt16Array(array);
		writer.writeInt16Array(largeArray);
		writer.writeNullableInt16Array(null);
		writer.writeNullableInt16Array(emptyArray);
		writer.writeNullableInt16Array(smallArray);
		writer.writeNullableInt16Array(array);
		writer.writeNullableInt16Array(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readInt16Array();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readInt16Array();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readInt16Array();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readInt16Array();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableInt16Array();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableInt16Array();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableInt16Array();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableInt16Array();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableInt16Array();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	
	@Test
	void uint32ArrayTest() {
		var emptyArray = new int[0];
		var smallArray = new int[10];
		var array = new int[1000];
		var largeArray = new int[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeUInt32Array(emptyArray);
		writer.writeUInt32Array(smallArray);
		writer.writeUInt32Array(array);
		writer.writeUInt32Array(largeArray);
		writer.writeNullableUInt32Array(null);
		writer.writeNullableUInt32Array(emptyArray);
		writer.writeNullableUInt32Array(smallArray);
		writer.writeNullableUInt32Array(array);
		writer.writeNullableUInt32Array(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readUInt32Array();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readUInt32Array();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readUInt32Array();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readUInt32Array();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableUInt32Array();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableUInt32Array();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableUInt32Array();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableUInt32Array();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableUInt32Array();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	@Test
	void int32ArrayTest() {
		var emptyArray = new int[0];
		var smallArray = new int[10];
		var array = new int[1000];
		var largeArray = new int[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeInt32Array(emptyArray);
		writer.writeInt32Array(smallArray);
		writer.writeInt32Array(array);
		writer.writeInt32Array(largeArray);
		writer.writeNullableInt32Array(null);
		writer.writeNullableInt32Array(emptyArray);
		writer.writeNullableInt32Array(smallArray);
		writer.writeNullableInt32Array(array);
		writer.writeNullableInt32Array(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readInt32Array();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readInt32Array();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readInt32Array();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readInt32Array();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableInt32Array();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableInt32Array();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableInt32Array();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableInt32Array();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableInt32Array();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	@Test
	void uint64ArrayTest() {
		var emptyArray = new long[0];
		var smallArray = new long[10];
		var array = new long[1000];
		var largeArray = new long[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeUInt64Array(emptyArray);
		writer.writeUInt64Array(smallArray);
		writer.writeUInt64Array(array);
		writer.writeUInt64Array(largeArray);
		writer.writeNullableUInt64Array(null);
		writer.writeNullableUInt64Array(emptyArray);
		writer.writeNullableUInt64Array(smallArray);
		writer.writeNullableUInt64Array(array);
		writer.writeNullableUInt64Array(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readUInt64Array();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readUInt64Array();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readUInt64Array();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readUInt64Array();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableUInt64Array();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableUInt64Array();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableUInt64Array();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableUInt64Array();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableUInt64Array();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	@Test
	void int64ArrayTest() {
		var emptyArray = new long[0];
		var smallArray = new long[10];
		var array = new long[1000];
		var largeArray = new long[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeInt64Array(emptyArray);
		writer.writeInt64Array(smallArray);
		writer.writeInt64Array(array);
		writer.writeInt64Array(largeArray);
		writer.writeNullableInt64Array(null);
		writer.writeNullableInt64Array(emptyArray);
		writer.writeNullableInt64Array(smallArray);
		writer.writeNullableInt64Array(array);
		writer.writeNullableInt64Array(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readInt64Array();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readInt64Array();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readInt64Array();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readInt64Array();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableInt64Array();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableInt64Array();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableInt64Array();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableInt64Array();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableInt64Array();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	
	@Test
	void singleArrayTest() {
		var emptyArray = new float[0];
		var smallArray = new float[10];
		var array = new float[1000];
		var largeArray = new float[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeSingleArray(emptyArray);
		writer.writeSingleArray(smallArray);
		writer.writeSingleArray(array);
		writer.writeSingleArray(largeArray);
		writer.writeNullableSingleArray(null);
		writer.writeNullableSingleArray(emptyArray);
		writer.writeNullableSingleArray(smallArray);
		writer.writeNullableSingleArray(array);
		writer.writeNullableSingleArray(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readSingleArray();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readSingleArray();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readSingleArray();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readSingleArray();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableSingleArray();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableSingleArray();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableSingleArray();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableSingleArray();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableSingleArray();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	@Test
	void doubleArrayTest() {
		var emptyArray = new double[0];
		var smallArray = new double[10];
		var array = new double[1000];
		var largeArray = new double[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeDoubleArray(emptyArray);
		writer.writeDoubleArray(smallArray);
		writer.writeDoubleArray(array);
		writer.writeDoubleArray(largeArray);
		writer.writeNullableDoubleArray(null);
		writer.writeNullableDoubleArray(emptyArray);
		writer.writeNullableDoubleArray(smallArray);
		writer.writeNullableDoubleArray(array);
		writer.writeNullableDoubleArray(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readDoubleArray();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readDoubleArray();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readDoubleArray();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readDoubleArray();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableDoubleArray();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableDoubleArray();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableDoubleArray();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableDoubleArray();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableDoubleArray();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	@Test
	void dateTimeArrayTest() {
		var emptyArray = new DateTime[0];
		var smallArray = new DateTime[10];
		var array = new DateTime[1000];
		var largeArray = new DateTime[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeDateTimeArray(emptyArray);
		writer.writeDateTimeArray(smallArray);
		writer.writeDateTimeArray(array);
		writer.writeDateTimeArray(largeArray);
		writer.writeNullableDateTimeArray(null);
		writer.writeNullableDateTimeArray(emptyArray);
		writer.writeNullableDateTimeArray(smallArray);
		writer.writeNullableDateTimeArray(array);
		writer.writeNullableDateTimeArray(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readDateTimeArray();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readDateTimeArray();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readDateTimeArray();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readDateTimeArray();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableDateTimeArray();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableDateTimeArray();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableDateTimeArray();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableDateTimeArray();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableDateTimeArray();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	@Test
	void timeSpanArrayTest() {
		var emptyArray = new TimeSpan[0];
		var smallArray = new TimeSpan[10];
		var array = new TimeSpan[1000];
		var largeArray = new TimeSpan[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeTimeSpanArray(emptyArray);
		writer.writeTimeSpanArray(smallArray);
		writer.writeTimeSpanArray(array);
		writer.writeTimeSpanArray(largeArray);
		writer.writeNullableTimeSpanArray(null);
		writer.writeNullableTimeSpanArray(emptyArray);
		writer.writeNullableTimeSpanArray(smallArray);
		writer.writeNullableTimeSpanArray(array);
		writer.writeNullableTimeSpanArray(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readTimeSpanArray();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readTimeSpanArray();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readTimeSpanArray();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readTimeSpanArray();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableTimeSpanArray();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableTimeSpanArray();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableTimeSpanArray();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableTimeSpanArray();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableTimeSpanArray();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	@Test
	void guidArrayTest() {
		var emptyArray = new Guid[0];
		var smallArray = new Guid[10];
		var array = new Guid[1000];
		var largeArray = new Guid[100000];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeGuidArray(emptyArray);
		writer.writeGuidArray(smallArray);
		writer.writeGuidArray(array);
		writer.writeGuidArray(largeArray);
		writer.writeNullableGuidArray(null);
		writer.writeNullableGuidArray(emptyArray);
		writer.writeNullableGuidArray(smallArray);
		writer.writeNullableGuidArray(array);
		writer.writeNullableGuidArray(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readGuidArray();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readGuidArray();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readGuidArray();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readGuidArray();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableGuidArray();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableGuidArray();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableGuidArray();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableGuidArray();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableGuidArray();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	@Test
	void uint8ListArrayTest() {
		var emptyArray = new byte[0][];
		var smallArray = new byte[10][];
		var array = new byte[1000][];
		var largeArray = new byte[100000][];
		
		fill(smallArray);
		fill(array);
		fill(largeArray);
		
		
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		writer.writeUInt8ListArray(emptyArray);
		writer.writeUInt8ListArray(smallArray);
		writer.writeUInt8ListArray(array);
		writer.writeUInt8ListArray(largeArray);
		writer.writeNullableUInt8ListArray(null);
		writer.writeNullableUInt8ListArray(emptyArray);
		writer.writeNullableUInt8ListArray(smallArray);
		writer.writeNullableUInt8ListArray(array);
		writer.writeNullableUInt8ListArray(largeArray);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
		
		var emptyArrayOut = reader.readUInt8ListArray();
		assertEquals(emptyArrayOut.length,emptyArray.length);
		var smallArrayOut = reader.readUInt8ListArray();
		assertArrayEquals(smallArrayOut,smallArray);
		var arrayOut = reader.readUInt8ListArray();
		assertArrayEquals(arrayOut,array);
		var largeArrayOut = reader.readUInt8ListArray();
		assertArrayEquals(largeArrayOut,largeArray);
		var nullNullableArrayOut = reader.readNullableUInt8ListArray();
		assertNull(nullNullableArrayOut);
		var emptyNullableArrayOut = reader.readNullableUInt8ListArray();
		assertNotNull(emptyNullableArrayOut);
		assertArrayEquals(emptyNullableArrayOut,emptyArray);
		var smallNullableArrayOut = reader.readNullableUInt8ListArray();
		assertNotNull(smallNullableArrayOut);
		assertArrayEquals(smallNullableArrayOut,smallArray);
		var arrayNullableOut = reader.readNullableUInt8ListArray();
		assertNotNull(arrayNullableOut);
		assertArrayEquals(arrayNullableOut,array);
		var largeNullableArrayOut = reader.readNullableUInt8ListArray();
		assertNotNull(largeNullableArrayOut);
		assertArrayEquals(largeNullableArrayOut,largeArray);
		
	}
	
	
	
	
	
	
	
	@Test
	void test() {
		var outStream = new ByteArrayOutputStream();
		var writer = new DataWriter(outStream);
		
		var bytes = outStream.toByteArray();
		
		var inStream = new ByteArrayInputStream(bytes);
		var reader = new DataReader(inStream);
	}

}
