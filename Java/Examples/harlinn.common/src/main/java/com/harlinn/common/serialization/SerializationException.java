package com.harlinn.common.serialization;

public class SerializationException extends RuntimeException {

	private static final long serialVersionUID = 5389413685853421926L;
	
	public SerializationException() {
        super();
    }
	
	public SerializationException(String message) {
        super(message);
    }
}
