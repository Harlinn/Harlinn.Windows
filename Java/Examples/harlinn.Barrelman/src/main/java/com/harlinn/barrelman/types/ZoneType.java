package com.harlinn.barrelman.types;

public class ZoneType {
    public final static int None = 0;
    public final static int Circular = 1;
    public final static int Polygon = 2;

    public final static String toString(int value) {
    	switch(value) {
    	    case None:
    	        return "None";
    	    case Circular:
    	        return "Circular";
    	    case Polygon:
    	        return "Polygon";
    	    default:
    	        throw new IllegalArgumentException( "Unknown ZoneType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "None":
    	        return None;
    	    case "Circular":
    	        return Circular;
    	    case "Polygon":
    	        return Polygon;
    	    default:
    	        throw new IllegalArgumentException( "Unknown ZoneType constant name:" + value );
    	}
    }

}

