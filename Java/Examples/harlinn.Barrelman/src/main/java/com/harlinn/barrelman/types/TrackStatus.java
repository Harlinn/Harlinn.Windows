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

public class TrackStatus {
    public final static int Unknown = 0;
    public final static int New = 1;
    public final static int Tracked = 2;
    public final static int NoPositionUpdate = 3;
    public final static int Lost = 4;
    public final static int Killed = 5;
    public final static int DIW = 6;
    public final static int UnderWayUsingEngine = 7;
    public final static int AtAnchor = 8;
    public final static int NotUnderCommand = 9;
    public final static int RestrictedManeuverability = 10;
    public final static int ConstrainedByDraught = 11;
    public final static int Moored = 12;
    public final static int Aground = 13;
    public final static int EngagedInFishing = 14;
    public final static int UnderWaySailing = 15;
    public final static int ReservedForFutureAmendmentOfNavigationalStatusForHSC = 16;
    public final static int ReservedForFutureAmendmentOfNavigationalStatusForWIG = 17;
    public final static int ReservedForFutureUse1 = 18;
    public final static int ReservedForFutureUse2 = 19;
    public final static int ReservedForFutureUse3 = 20;
    public final static int ReservedForFutureUse = 21;
    public final static int AisSartIsActive = 22;
    public final static int NotDefined = 23;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case New:
    	        return "New";
    	    case Tracked:
    	        return "Tracked";
    	    case NoPositionUpdate:
    	        return "NoPositionUpdate";
    	    case Lost:
    	        return "Lost";
    	    case Killed:
    	        return "Killed";
    	    case DIW:
    	        return "DIW";
    	    case UnderWayUsingEngine:
    	        return "UnderWayUsingEngine";
    	    case AtAnchor:
    	        return "AtAnchor";
    	    case NotUnderCommand:
    	        return "NotUnderCommand";
    	    case RestrictedManeuverability:
    	        return "RestrictedManeuverability";
    	    case ConstrainedByDraught:
    	        return "ConstrainedByDraught";
    	    case Moored:
    	        return "Moored";
    	    case Aground:
    	        return "Aground";
    	    case EngagedInFishing:
    	        return "EngagedInFishing";
    	    case UnderWaySailing:
    	        return "UnderWaySailing";
    	    case ReservedForFutureAmendmentOfNavigationalStatusForHSC:
    	        return "ReservedForFutureAmendmentOfNavigationalStatusForHSC";
    	    case ReservedForFutureAmendmentOfNavigationalStatusForWIG:
    	        return "ReservedForFutureAmendmentOfNavigationalStatusForWIG";
    	    case ReservedForFutureUse1:
    	        return "ReservedForFutureUse1";
    	    case ReservedForFutureUse2:
    	        return "ReservedForFutureUse2";
    	    case ReservedForFutureUse3:
    	        return "ReservedForFutureUse3";
    	    case ReservedForFutureUse:
    	        return "ReservedForFutureUse";
    	    case AisSartIsActive:
    	        return "AisSartIsActive";
    	    case NotDefined:
    	        return "NotDefined";
    	    default:
    	        throw new IllegalArgumentException( "Unknown TrackStatus constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "New":
    	        return New;
    	    case "Tracked":
    	        return Tracked;
    	    case "NoPositionUpdate":
    	        return NoPositionUpdate;
    	    case "Lost":
    	        return Lost;
    	    case "Killed":
    	        return Killed;
    	    case "DIW":
    	        return DIW;
    	    case "UnderWayUsingEngine":
    	        return UnderWayUsingEngine;
    	    case "AtAnchor":
    	        return AtAnchor;
    	    case "NotUnderCommand":
    	        return NotUnderCommand;
    	    case "RestrictedManeuverability":
    	        return RestrictedManeuverability;
    	    case "ConstrainedByDraught":
    	        return ConstrainedByDraught;
    	    case "Moored":
    	        return Moored;
    	    case "Aground":
    	        return Aground;
    	    case "EngagedInFishing":
    	        return EngagedInFishing;
    	    case "UnderWaySailing":
    	        return UnderWaySailing;
    	    case "ReservedForFutureAmendmentOfNavigationalStatusForHSC":
    	        return ReservedForFutureAmendmentOfNavigationalStatusForHSC;
    	    case "ReservedForFutureAmendmentOfNavigationalStatusForWIG":
    	        return ReservedForFutureAmendmentOfNavigationalStatusForWIG;
    	    case "ReservedForFutureUse1":
    	        return ReservedForFutureUse1;
    	    case "ReservedForFutureUse2":
    	        return ReservedForFutureUse2;
    	    case "ReservedForFutureUse3":
    	        return ReservedForFutureUse3;
    	    case "ReservedForFutureUse":
    	        return ReservedForFutureUse;
    	    case "AisSartIsActive":
    	        return AisSartIsActive;
    	    case "NotDefined":
    	        return NotDefined;
    	    default:
    	        throw new IllegalArgumentException( "Unknown TrackStatus constant name:" + value );
    	}
    }

}

