package com.harlinn.barrelman.types;

public class TrackFlags3D {
    public final static int None = 0;
    public final static int Status = 1;
    public final static int Position = 2;
    public final static int Speed = 4;
    public final static int Course = 8;
    public final static int RateOfClimb = 16;

    public final static String toString(int value) {
    	switch(value) {
    	    case None:
    	        return "None";
    	    case Status:
    	        return "Status";
    	    case Position:
    	        return "Position";
    	    case Speed:
    	        return "Speed";
    	    case Course:
    	        return "Course";
    	    case RateOfClimb:
    	        return "RateOfClimb";
    	    default:
    	        throw new IllegalArgumentException( "Unknown TrackFlags3D constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "None":
    	        return None;
    	    case "Status":
    	        return Status;
    	    case "Position":
    	        return Position;
    	    case "Speed":
    	        return Speed;
    	    case "Course":
    	        return Course;
    	    case "RateOfClimb":
    	        return RateOfClimb;
    	    default:
    	        throw new IllegalArgumentException( "Unknown TrackFlags3D constant name:" + value );
    	}
    }

}

