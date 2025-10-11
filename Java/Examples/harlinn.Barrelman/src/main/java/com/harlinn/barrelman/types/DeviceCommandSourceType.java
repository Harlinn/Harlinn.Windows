package com.harlinn.barrelman.types;

public class DeviceCommandSourceType {
    public final static int Unknown = 0;
    public final static int Session = 1;
    public final static int Device = 2;
    public final static int Source = 3;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case Session:
    	        return "Session";
    	    case Device:
    	        return "Device";
    	    case Source:
    	        return "Source";
    	    default:
    	        throw new IllegalArgumentException( "Unknown DeviceCommandSourceType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "Session":
    	        return Session;
    	    case "Device":
    	        return Device;
    	    case "Source":
    	        return Source;
    	    default:
    	        throw new IllegalArgumentException( "Unknown DeviceCommandSourceType constant name:" + value );
    	}
    }

}

