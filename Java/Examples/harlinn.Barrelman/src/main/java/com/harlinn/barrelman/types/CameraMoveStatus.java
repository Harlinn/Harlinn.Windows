package com.harlinn.barrelman.types;

public class CameraMoveStatus {
    public final static int Unknown = 0;
    public final static int Idle = 1;
    public final static int Moving = 2;
    public final static int MovingContinuously = 3;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case Idle:
    	        return "Idle";
    	    case Moving:
    	        return "Moving";
    	    case MovingContinuously:
    	        return "MovingContinuously";
    	    default:
    	        throw new IllegalArgumentException( "Unknown CameraMoveStatus constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "Idle":
    	        return Idle;
    	    case "Moving":
    	        return Moving;
    	    case "MovingContinuously":
    	        return MovingContinuously;
    	    default:
    	        throw new IllegalArgumentException( "Unknown CameraMoveStatus constant name:" + value );
    	}
    }

}

