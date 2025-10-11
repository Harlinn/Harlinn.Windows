package com.harlinn.barrelman.types;

public class DeviceCommandReplyStatus {
    public final static int Unknown = 0;
    public final static int Ok = 1;
    public final static int NotImplemented = 2;
    public final static int Error = 3;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case Ok:
    	        return "Ok";
    	    case NotImplemented:
    	        return "NotImplemented";
    	    case Error:
    	        return "Error";
    	    default:
    	        throw new IllegalArgumentException( "Unknown DeviceCommandReplyStatus constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "Ok":
    	        return Ok;
    	    case "NotImplemented":
    	        return NotImplemented;
    	    case "Error":
    	        return Error;
    	    default:
    	        throw new IllegalArgumentException( "Unknown DeviceCommandReplyStatus constant name:" + value );
    	}
    }

}

