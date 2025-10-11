package com.harlinn.barrelman.types;

public class GnssPositionStatus {
    public final static int CurrentGnssPosition = 0;
    public final static int NotGnssPosition = 1;

    public final static String toString(int value) {
    	switch(value) {
    	    case CurrentGnssPosition:
    	        return "CurrentGnssPosition";
    	    case NotGnssPosition:
    	        return "NotGnssPosition";
    	    default:
    	        throw new IllegalArgumentException( "Unknown GnssPositionStatus constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "CurrentGnssPosition":
    	        return CurrentGnssPosition;
    	    case "NotGnssPosition":
    	        return NotGnssPosition;
    	    default:
    	        throw new IllegalArgumentException( "Unknown GnssPositionStatus constant name:" + value );
    	}
    }

}

