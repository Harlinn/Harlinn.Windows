package com.harlinn.barrelman.types;

public class PositionAccuracy {
    public final static int Low = 0;
    public final static int High = 1;

    public final static String toString(int value) {
    	switch(value) {
    	    case Low:
    	        return "Low";
    	    case High:
    	        return "High";
    	    default:
    	        throw new IllegalArgumentException( "Unknown PositionAccuracy constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Low":
    	        return Low;
    	    case "High":
    	        return High;
    	    default:
    	        throw new IllegalArgumentException( "Unknown PositionAccuracy constant name:" + value );
    	}
    }

}

