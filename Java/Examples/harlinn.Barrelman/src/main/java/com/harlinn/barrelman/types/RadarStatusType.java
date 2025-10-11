package com.harlinn.barrelman.types;

public class RadarStatusType {
    public final static int Off = 0;
    public final static int On = 1;
    public final static int Error = 2;
    public final static int NoData = 3;

    public final static String toString(int value) {
    	switch(value) {
    	    case Off:
    	        return "Off";
    	    case On:
    	        return "On";
    	    case Error:
    	        return "Error";
    	    case NoData:
    	        return "NoData";
    	    default:
    	        throw new IllegalArgumentException( "Unknown RadarStatusType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Off":
    	        return Off;
    	    case "On":
    	        return On;
    	    case "Error":
    	        return Error;
    	    case "NoData":
    	        return NoData;
    	    default:
    	        throw new IllegalArgumentException( "Unknown RadarStatusType constant name:" + value );
    	}
    }

}

