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
package com.harlinn.common.types;

public class ObjectState {
	public static final byte Unknown = 0;
	public static final byte New = 1;
	public static final byte Stored = 2;
	public static final byte Changed = 3;
	public static final byte Deleted = 4;
	public static final byte ConcurrencyConflict = 5;
	
	
	public static final String toString(byte value) {
		switch(value) {
		case Unknown:
			return "Unknown";
		case New:
			return "New";
		case Stored:
			return "Stored";
		case Changed:
			return "Changed";
		case Deleted:
			return "Deleted";
		case ConcurrencyConflict:
			return "ConcurrencyConflict";
		default:
			throw new IllegalArgumentException("Unknown ObjectState constant: " + Integer.toString(value, 10));
		}
	}
	
	public static final byte toByte(String value) {
		switch(value) {
		case "Unknown":
			return Unknown;
		case "New":
			return New;
		case "Stored":
			return Stored;
		case "Changed":
			return Changed;
		case "Deleted":
			return Deleted;
		case "ConcurrencyConflict":
			return ConcurrencyConflict;
		default:
			throw new IllegalArgumentException("Unknown ObjectState constant name: " + value);
		}
	}
	
	
}
