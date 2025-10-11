package com.harlinn.barrelman.types;

public class RadarImageType {
    public final static int MaskedProcessed = 0;
    public final static int FullRaw = 1;
    public final static int MaskedRaw = 2;
    public final static int VideoMask = 3;
    public final static int TrackMask = 4;
    public final static int SpillRaw = 5;
    public final static int SpillProcessed = 6;
    public final static int RawUnscanConverted = 7;
    public final static int NoTrackInitMask = 8;

    public final static String toString(int value) {
    	switch(value) {
    	    case MaskedProcessed:
    	        return "MaskedProcessed";
    	    case FullRaw:
    	        return "FullRaw";
    	    case MaskedRaw:
    	        return "MaskedRaw";
    	    case VideoMask:
    	        return "VideoMask";
    	    case TrackMask:
    	        return "TrackMask";
    	    case SpillRaw:
    	        return "SpillRaw";
    	    case SpillProcessed:
    	        return "SpillProcessed";
    	    case RawUnscanConverted:
    	        return "RawUnscanConverted";
    	    case NoTrackInitMask:
    	        return "NoTrackInitMask";
    	    default:
    	        throw new IllegalArgumentException( "Unknown RadarImageType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "MaskedProcessed":
    	        return MaskedProcessed;
    	    case "FullRaw":
    	        return FullRaw;
    	    case "MaskedRaw":
    	        return MaskedRaw;
    	    case "VideoMask":
    	        return VideoMask;
    	    case "TrackMask":
    	        return TrackMask;
    	    case "SpillRaw":
    	        return SpillRaw;
    	    case "SpillProcessed":
    	        return SpillProcessed;
    	    case "RawUnscanConverted":
    	        return RawUnscanConverted;
    	    case "NoTrackInitMask":
    	        return NoTrackInitMask;
    	    default:
    	        throw new IllegalArgumentException( "Unknown RadarImageType constant name:" + value );
    	}
    }

}

