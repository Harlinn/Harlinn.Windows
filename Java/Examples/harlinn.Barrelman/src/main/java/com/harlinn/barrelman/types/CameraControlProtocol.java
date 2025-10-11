package com.harlinn.barrelman.types;

public class CameraControlProtocol {
    public final static int Unknown = 0;
    public final static int ONVIF = 1;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case ONVIF:
    	        return "ONVIF";
    	    default:
    	        throw new IllegalArgumentException( "Unknown CameraControlProtocol constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "ONVIF":
    	        return ONVIF;
    	    default:
    	        throw new IllegalArgumentException( "Unknown CameraControlProtocol constant name:" + value );
    	}
    }

}

