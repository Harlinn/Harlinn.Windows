package com.harlinn.barrelman.types;

public class Handshake {
    public final static int None = 0;
    public final static int XOnXOff = 1;
    public final static int RequestToSend = 2;
    public final static int RequestToSendXOnXOff = 3;

    public final static String toString(int value) {
    	switch(value) {
    	    case None:
    	        return "None";
    	    case XOnXOff:
    	        return "XOnXOff";
    	    case RequestToSend:
    	        return "RequestToSend";
    	    case RequestToSendXOnXOff:
    	        return "RequestToSendXOnXOff";
    	    default:
    	        throw new IllegalArgumentException( "Unknown Handshake constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "None":
    	        return None;
    	    case "XOnXOff":
    	        return XOnXOff;
    	    case "RequestToSend":
    	        return RequestToSend;
    	    case "RequestToSendXOnXOff":
    	        return RequestToSendXOnXOff;
    	    default:
    	        throw new IllegalArgumentException( "Unknown Handshake constant name:" + value );
    	}
    }

}

