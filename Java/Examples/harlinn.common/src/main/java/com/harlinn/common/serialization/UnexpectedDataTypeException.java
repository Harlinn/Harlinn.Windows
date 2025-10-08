package com.harlinn.common.serialization;

public class UnexpectedDataTypeException extends SerializationException {
	UnexpectedDataTypeException(byte value) {
		super( "Unexpected data type: " + DataType.toString(value) );
	}
}
