package com.harlinn.barrelman.types;

public class RadarPulse {
    public final static int Short = 2;
    public final static int Medium = 1;
    public final static int Long = 0;

    public final static String toString(int value) {
    	switch(value) {
    	    case Short:
    	        return "Short";
    	    case Medium:
    	        return "Medium";
    	    case Long:
    	        return "Long";
    	    default:
    	        throw new IllegalArgumentException( "Unknown RadarPulse constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Short":
    	        return Short;
    	    case "Medium":
    	        return Medium;
    	    case "Long":
    	        return Long;
    	    default:
    	        throw new IllegalArgumentException( "Unknown RadarPulse constant name:" + value );
    	}
    }

}

