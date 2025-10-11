package com.harlinn.barrelman.types;

public class CameraFocalLengthMode {
    public final static int Unknown = 0;
    public final static int Normalized = 1;
    public final static int Millimeter = 2;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case Normalized:
    	        return "Normalized";
    	    case Millimeter:
    	        return "Millimeter";
    	    default:
    	        throw new IllegalArgumentException( "Unknown CameraFocalLengthMode constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "Normalized":
    	        return Normalized;
    	    case "Millimeter":
    	        return Millimeter;
    	    default:
    	        throw new IllegalArgumentException( "Unknown CameraFocalLengthMode constant name:" + value );
    	}
    }

}

