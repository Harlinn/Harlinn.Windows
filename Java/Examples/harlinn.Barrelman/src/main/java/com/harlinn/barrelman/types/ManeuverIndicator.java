package com.harlinn.barrelman.types;

public class ManeuverIndicator {
    public final static int NotAvailable = 0;
    public final static int NoSpecialManeuver = 1;
    public final static int SpecialManeuver = 2;

    public final static String toString(int value) {
    	switch(value) {
    	    case NotAvailable:
    	        return "NotAvailable";
    	    case NoSpecialManeuver:
    	        return "NoSpecialManeuver";
    	    case SpecialManeuver:
    	        return "SpecialManeuver";
    	    default:
    	        throw new IllegalArgumentException( "Unknown ManeuverIndicator constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "NotAvailable":
    	        return NotAvailable;
    	    case "NoSpecialManeuver":
    	        return NoSpecialManeuver;
    	    case "SpecialManeuver":
    	        return SpecialManeuver;
    	    default:
    	        throw new IllegalArgumentException( "Unknown ManeuverIndicator constant name:" + value );
    	}
    }

}

