package com.harlinn.common.util;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class GuidTest {

	@Test
	void newGuidTest() {
		var guid = Guid.newGuid();
		assertNotNull(guid);
	}
	
	@Test
	void toStringTest() {
		var guid = Guid.newGuid();
		assertNotNull(guid);
		var str = guid.toString();
		assertTrue( str.length() != 0);
	}
	
	@Test
	void fromStringTest() {
		var guidString = "{089057FC-F714-4935-8047-701620727995}";
		var guidStringLength = guidString.length(); 
		var guid = Guid.fromString(guidString);
		assertNotNull(guid);
		var str = guid.toString();
		var strLength = str.length(); 
		var isEqual = str.equals(guidString);
		assertTrue( isEqual);
	}

}
