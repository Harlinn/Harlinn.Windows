package com.harlinn.barrelman.types;

public class Parity {
    public final static int None = 0;
    public final static int Odd = 1;
    public final static int Even = 2;
    public final static int Mark = 3;
    public final static int Space = 4;

    public final static String toString(int value) {
    	switch(value) {
    	    case None:
    	        return "None";
    	    case Odd:
    	        return "Odd";
    	    case Even:
    	        return "Even";
    	    case Mark:
    	        return "Mark";
    	    case Space:
    	        return "Space";
    	    default:
    	        throw new IllegalArgumentException( "Unknown Parity constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "None":
    	        return None;
    	    case "Odd":
    	        return Odd;
    	    case "Even":
    	        return Even;
    	    case "Mark":
    	        return Mark;
    	    case "Space":
    	        return Space;
    	    default:
    	        throw new IllegalArgumentException( "Unknown Parity constant name:" + value );
    	}
    }

}

