/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
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

