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
