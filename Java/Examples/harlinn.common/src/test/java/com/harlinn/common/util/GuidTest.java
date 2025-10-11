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

}
