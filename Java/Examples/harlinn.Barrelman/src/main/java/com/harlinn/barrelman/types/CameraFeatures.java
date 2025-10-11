package com.harlinn.barrelman.types;

public class CameraFeatures {
    public final static int None = 0;
    public final static int ColorMode = 1;
    public final static int Washer = 2;
    public final static int Wiper = 4;
    public final static int IRLamp = 8;
    public final static int AutoFocusControl = 16;

    public final static String toString(int value) {
    	switch(value) {
    	    case None:
    	        return "None";
    	    case ColorMode:
    	        return "ColorMode";
    	    case Washer:
    	        return "Washer";
    	    case Wiper:
    	        return "Wiper";
    	    case IRLamp:
    	        return "IRLamp";
    	    case AutoFocusControl:
    	        return "AutoFocusControl";
    	    default:
    	        throw new IllegalArgumentException( "Unknown CameraFeatures constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "None":
    	        return None;
    	    case "ColorMode":
    	        return ColorMode;
    	    case "Washer":
    	        return Washer;
    	    case "Wiper":
    	        return Wiper;
    	    case "IRLamp":
    	        return IRLamp;
    	    case "AutoFocusControl":
    	        return AutoFocusControl;
    	    default:
    	        throw new IllegalArgumentException( "Unknown CameraFeatures constant name:" + value );
    	}
    }

}

