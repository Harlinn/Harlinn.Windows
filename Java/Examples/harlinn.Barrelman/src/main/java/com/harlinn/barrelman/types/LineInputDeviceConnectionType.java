package com.harlinn.barrelman.types;

public class LineInputDeviceConnectionType {
    public final static int Unknown = 0;
    public final static int TCP = 1;
    public final static int UDP = 2;
    public final static int SerialPort = 3;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case TCP:
    	        return "TCP";
    	    case UDP:
    	        return "UDP";
    	    case SerialPort:
    	        return "SerialPort";
    	    default:
    	        throw new IllegalArgumentException( "Unknown LineInputDeviceConnectionType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "TCP":
    	        return TCP;
    	    case "UDP":
    	        return UDP;
    	    case "SerialPort":
    	        return SerialPort;
    	    default:
    	        throw new IllegalArgumentException( "Unknown LineInputDeviceConnectionType constant name:" + value );
    	}
    }

}

