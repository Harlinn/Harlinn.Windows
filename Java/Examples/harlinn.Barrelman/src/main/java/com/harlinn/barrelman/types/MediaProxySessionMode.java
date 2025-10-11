package com.harlinn.barrelman.types;

public class MediaProxySessionMode {
    public final static int Unknown = 0;
    public final static int RTP = 1;
    public final static int RTPOverTCP = 2;
    public final static int RTPOverHTTP = 3;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case RTP:
    	        return "RTP";
    	    case RTPOverTCP:
    	        return "RTPOverTCP";
    	    case RTPOverHTTP:
    	        return "RTPOverHTTP";
    	    default:
    	        throw new IllegalArgumentException( "Unknown MediaProxySessionMode constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "RTP":
    	        return RTP;
    	    case "RTPOverTCP":
    	        return RTPOverTCP;
    	    case "RTPOverHTTP":
    	        return RTPOverHTTP;
    	    default:
    	        throw new IllegalArgumentException( "Unknown MediaProxySessionMode constant name:" + value );
    	}
    }

}

