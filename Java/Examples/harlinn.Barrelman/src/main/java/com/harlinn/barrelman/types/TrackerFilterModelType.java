package com.harlinn.barrelman.types;

public class TrackerFilterModelType {
    public final static int Unknown = 0;
    public final static int Damp1 = 1;
    public final static int Damp2 = 2;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case Damp1:
    	        return "Damp1";
    	    case Damp2:
    	        return "Damp2";
    	    default:
    	        throw new IllegalArgumentException( "Unknown TrackerFilterModelType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "Damp1":
    	        return Damp1;
    	    case "Damp2":
    	        return Damp2;
    	    default:
    	        throw new IllegalArgumentException( "Unknown TrackerFilterModelType constant name:" + value );
    	}
    }

}

