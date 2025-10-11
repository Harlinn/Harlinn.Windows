package com.harlinn.barrelman.types;

public class Raim {
    public final static int NotInUse = 0;
    public final static int InUse = 1;

    public final static String toString(int value) {
    	switch(value) {
    	    case NotInUse:
    	        return "NotInUse";
    	    case InUse:
    	        return "InUse";
    	    default:
    	        throw new IllegalArgumentException( "Unknown Raim constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "NotInUse":
    	        return NotInUse;
    	    case "InUse":
    	        return InUse;
    	    default:
    	        throw new IllegalArgumentException( "Unknown Raim constant name:" + value );
    	}
    }

}

