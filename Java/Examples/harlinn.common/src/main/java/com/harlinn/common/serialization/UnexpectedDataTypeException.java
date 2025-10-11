package com.harlinn.common.serialization;

public class UnexpectedDataTypeException extends SerializationException {
	
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -7808558219930938097L;

	UnexpectedDataTypeException(byte value) {
		super( "Unexpected data type: " + DataType.toString(value) );
	}
}
