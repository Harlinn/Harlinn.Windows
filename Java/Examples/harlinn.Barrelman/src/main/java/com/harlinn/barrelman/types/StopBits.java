package com.harlinn.barrelman.types;

public class StopBits {
    public final static int None = 0;
    public final static int One = 1;
    public final static int Two = 2;
    public final static int OnePointFive = 3;

    public final static String toString(int value) {
    	switch(value) {
    	    case None:
    	        return "None";
    	    case One:
    	        return "One";
    	    case Two:
    	        return "Two";
    	    case OnePointFive:
    	        return "OnePointFive";
    	    default:
    	        throw new IllegalArgumentException( "Unknown StopBits constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "None":
    	        return None;
    	    case "One":
    	        return One;
    	    case "Two":
    	        return Two;
    	    case "OnePointFive":
    	        return OnePointFive;
    	    default:
    	        throw new IllegalArgumentException( "Unknown StopBits constant name:" + value );
    	}
    }

}

