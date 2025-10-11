package com.harlinn.barrelman.types;

public class HeadingType {
    public final static int Unknown = 0;
    public final static int TrueNorth = 1;
    public final static int MagneticNorth = 2;
    public final static int Relative = 3;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case TrueNorth:
    	        return "TrueNorth";
    	    case MagneticNorth:
    	        return "MagneticNorth";
    	    case Relative:
    	        return "Relative";
    	    default:
    	        throw new IllegalArgumentException( "Unknown HeadingType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "TrueNorth":
    	        return TrueNorth;
    	    case "MagneticNorth":
    	        return MagneticNorth;
    	    case "Relative":
    	        return Relative;
    	    default:
    	        throw new IllegalArgumentException( "Unknown HeadingType constant name:" + value );
    	}
    }

}

