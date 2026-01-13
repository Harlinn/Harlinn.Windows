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
