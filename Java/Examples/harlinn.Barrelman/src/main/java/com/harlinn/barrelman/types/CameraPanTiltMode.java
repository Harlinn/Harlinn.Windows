package com.harlinn.barrelman.types;

public class CameraPanTiltMode {
    public final static int Unknown = 0;
    public final static int Normalized = 1;
    public final static int Angular = 2;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case Normalized:
    	        return "Normalized";
    	    case Angular:
    	        return "Angular";
    	    default:
    	        throw new IllegalArgumentException( "Unknown CameraPanTiltMode constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "Normalized":
    	        return Normalized;
    	    case "Angular":
    	        return Angular;
    	    default:
    	        throw new IllegalArgumentException( "Unknown CameraPanTiltMode constant name:" + value );
    	}
    }

}

