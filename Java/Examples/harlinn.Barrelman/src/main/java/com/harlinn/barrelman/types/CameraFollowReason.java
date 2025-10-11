package com.harlinn.barrelman.types;

public class CameraFollowReason {
    public final static int Alarm = 0;
    public final static int User = 1;

    public final static String toString(int value) {
    	switch(value) {
    	    case Alarm:
    	        return "Alarm";
    	    case User:
    	        return "User";
    	    default:
    	        throw new IllegalArgumentException( "Unknown CameraFollowReason constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Alarm":
    	        return Alarm;
    	    case "User":
    	        return User;
    	    default:
    	        throw new IllegalArgumentException( "Unknown CameraFollowReason constant name:" + value );
    	}
    }

}

