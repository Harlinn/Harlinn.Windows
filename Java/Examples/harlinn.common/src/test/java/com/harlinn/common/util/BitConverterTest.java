package com.harlinn.common.util;

import static org.junit.jupiter.api.Assertions.*;

import java.nio.charset.StandardCharsets;
import java.util.Arrays;

import org.junit.jupiter.api.Test;

class BitConverterTest {

	@Test
	void testGetBytesBoolean() {
		var falseBytes = BitConverter.getBytes(false);
		assertTrue(falseBytes.length == 1);
		assertTrue(falseBytes[0] == 0);
		
		var trueBytes = BitConverter.getBytes(true);
		assertTrue(trueBytes.length == 1);
		assertTrue(trueBytes[0] == 1);
		
	}

	@Test
	void testToBoolean() {
		byte[] falseBytes = {(byte)0};
		byte[] trueBytes = {(byte)1};
		
		var falseExpected = BitConverter.toBoolean(falseBytes, 0); 
		var trueExpected = BitConverter.toBoolean(trueBytes, 0);
		
		assertFalse(falseExpected);
		assertTrue(trueExpected);
	}

	
	@Test
	void testGetBytesByte() {
		var bytes = BitConverter.getBytes((byte)0);
		assertTrue(bytes.length == 1);
		assertTrue(bytes[0] == 0);
		
		bytes = BitConverter.getBytes((byte)0xFF);
		assertTrue(bytes.length == 1);
		assertTrue(bytes[0] == (byte)0xFF);
	}

	
	@Test
	void testToByte() {
		byte[] bytes = {(byte)0};
		var expect0 = BitConverter.toByte(bytes);
		assertTrue(expect0 == (byte)0);
		bytes[0] = (byte)0xFF;
		var expect0xFF = BitConverter.toByte(bytes);
		assertTrue(expect0xFF == (byte)0xFF);
	}

	
	
	@Test
	void testGetBytesChar() {
		String s = String.valueOf('c');
        byte[] byteArray = s.getBytes(StandardCharsets.UTF_16LE);
        byte[] expectedBytes = {(byte)'c',(byte)0};
        
        assertTrue(Arrays.equals(expectedBytes,byteArray));
        
		var bytes = BitConverter.getBytes('c');
		
		assertTrue(Arrays.equals(expectedBytes,bytes));
	}

	
	@Test
	void testToChar() {
		byte[] bytes = {(byte)'c',(byte)0};
		var value = BitConverter.toChar(bytes);
		assertEquals('c', value);
	}

	
	@Test
	void testGetBytesShort() {
		byte[] expectedBytes99 = {(byte)99,(byte)0};
		var bytes99 = BitConverter.getBytes((short)99);
		
		assertTrue(Arrays.equals(expectedBytes99,bytes99));
		
		byte[] expectedBytes0x8000 = {(byte)00,(byte)0x80};
		var bytes0x8000 = BitConverter.getBytes((short)0x8000);
		
		assertTrue(Arrays.equals(expectedBytes0x8000,bytes0x8000));
		
	}

	
	@Test
	void testToInt16() {
		byte[] bytes = {(byte)99,(byte)0};
		var value = BitConverter.toInt16(bytes);
		assertEquals((short)99, value);
		
		byte[] bytes0x8000 = {(byte)00,(byte)0x80};
		value = BitConverter.toInt16(bytes0x8000);
		assertEquals((short)0x8000, value);
	}

    
	@Test
	void testGetBytesInt() {
		byte[] expectedBytes99 = {(byte)99,(byte)0,(byte)0,(byte)0};
		var bytes99 = BitConverter.getBytes((int)99);
		
		assertTrue(Arrays.equals(expectedBytes99,bytes99));
		
		byte[] expectedBytes0x80000000 = {(byte)00,(byte)0,(byte)0, (byte)0x80};
		var bytes0x80000000 = BitConverter.getBytes((int)0x80000000);
		
		assertTrue(Arrays.equals(expectedBytes0x80000000,bytes0x80000000));
	}

	
	@Test
	void testToInt32() {
		byte[] bytes = {(byte)99,(byte)0,(byte)0,(byte)0};
		var value = BitConverter.toInt32(bytes);
		assertEquals((int)99, value);
		
		byte[] bytes0x80000000 = {(byte)00,(byte)0,(byte)0,(byte)0x80};
		value = BitConverter.toInt32(bytes0x80000000);
		assertEquals(0x80000000, value);
	}

	@Test
	void testGetBytesLong() {
		byte[] expectedBytes99 = {(byte)99,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0};
		var bytes99 = BitConverter.getBytes((long)99);
		
		assertTrue(Arrays.equals(expectedBytes99,bytes99));
		
		byte[] expectedBytes0x8000000000000000 = {(byte)00,(byte)00,(byte)0,(byte)0,(byte)00,(byte)0,(byte)0,(byte)0x80};
		var bytes0x8000000000000000 = BitConverter.getBytes((long)0x8000000000000000L);
		
		assertTrue(Arrays.equals(expectedBytes0x8000000000000000,bytes0x8000000000000000));
	}

	@Test
	void testToInt64() {
		byte[] bytes = {(byte)99,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0,(byte)0};
		var value = BitConverter.toInt64(bytes);
		assertEquals((long)99, value);
		
		byte[] bytes0x8000000000000000 = {(byte)00,(byte)00,(byte)0,(byte)0,(byte)00,(byte)0,(byte)0,(byte)0x80};
		value = BitConverter.toInt64(bytes0x8000000000000000);
		assertEquals(0x8000000000000000L, value);
	}
	

}
