package com.harlinn.barrelman.types;

public class MapElementType {
    public final static int Unknown = 0;
    public final static int Svg = 1;
    public final static int Png = 2;
    public final static int Jpeg = 3;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case Svg:
    	        return "Svg";
    	    case Png:
    	        return "Png";
    	    case Jpeg:
    	        return "Jpeg";
    	    default:
    	        throw new IllegalArgumentException( "Unknown MapElementType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "Svg":
    	        return Svg;
    	    case "Png":
    	        return Png;
    	    case "Jpeg":
    	        return Jpeg;
    	    default:
    	        throw new IllegalArgumentException( "Unknown MapElementType constant name:" + value );
    	}
    }

}

