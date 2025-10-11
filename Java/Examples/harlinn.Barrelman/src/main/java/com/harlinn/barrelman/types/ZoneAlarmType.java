package com.harlinn.barrelman.types;

public class ZoneAlarmType {
    public final static int None = 0;
    public final static int Intrusion = 1;
    public final static int Speed = 2;
    public final static int Entered = 3;
    public final static int Exited = 4;

    public final static String toString(int value) {
    	switch(value) {
    	    case None:
    	        return "None";
    	    case Intrusion:
    	        return "Intrusion";
    	    case Speed:
    	        return "Speed";
    	    case Entered:
    	        return "Entered";
    	    case Exited:
    	        return "Exited";
    	    default:
    	        throw new IllegalArgumentException( "Unknown ZoneAlarmType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "None":
    	        return None;
    	    case "Intrusion":
    	        return Intrusion;
    	    case "Speed":
    	        return Speed;
    	    case "Entered":
    	        return Entered;
    	    case "Exited":
    	        return Exited;
    	    default:
    	        throw new IllegalArgumentException( "Unknown ZoneAlarmType constant name:" + value );
    	}
    }

}

