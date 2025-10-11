package com.harlinn.barrelman.types;

public class RadomeStatus {
    public final static int None = 0;
    public final static int Overpressure = 1;
    public final static int Overridden = 2;
    public final static int Purging = 4;
    public final static int NormalOperation = 8;
    public final static int RadarPowerOff = 16;

    public final static String toString(int value) {
    	switch(value) {
    	    case None:
    	        return "None";
    	    case Overpressure:
    	        return "Overpressure";
    	    case Overridden:
    	        return "Overridden";
    	    case Purging:
    	        return "Purging";
    	    case NormalOperation:
    	        return "NormalOperation";
    	    case RadarPowerOff:
    	        return "RadarPowerOff";
    	    default:
    	        throw new IllegalArgumentException( "Unknown RadomeStatus constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "None":
    	        return None;
    	    case "Overpressure":
    	        return Overpressure;
    	    case "Overridden":
    	        return Overridden;
    	    case "Purging":
    	        return Purging;
    	    case "NormalOperation":
    	        return NormalOperation;
    	    case "RadarPowerOff":
    	        return RadarPowerOff;
    	    default:
    	        throw new IllegalArgumentException( "Unknown RadomeStatus constant name:" + value );
    	}
    }

}

