package com.harlinn.barrelman.types;

public class NavigationStatus {
    public final static int UnderWayUsingEngine = 0;
    public final static int AtAnchor = 1;
    public final static int NotUnderCommand = 2;
    public final static int RestrictedManeuverability = 3;
    public final static int ConstrainedByHerDraught = 4;
    public final static int Moored = 5;
    public final static int Aground = 6;
    public final static int EngagedInFishing = 7;
    public final static int UnderWaySailing = 8;
    public final static int ReservedForFutureAmendmentOfNavigationalStatusForHsc = 9;
    public final static int ReservedForFutureAmendmentOfNavigationalStatusForWig = 10;
    public final static int ReservedForFutureUse1 = 11;
    public final static int ReservedForFutureUse2 = 12;
    public final static int ReservedForFutureUse3 = 13;
    public final static int AisSartIsActive = 14;
    public final static int NotDefined = 15;

    public final static String toString(int value) {
    	switch(value) {
    	    case UnderWayUsingEngine:
    	        return "UnderWayUsingEngine";
    	    case AtAnchor:
    	        return "AtAnchor";
    	    case NotUnderCommand:
    	        return "NotUnderCommand";
    	    case RestrictedManeuverability:
    	        return "RestrictedManeuverability";
    	    case ConstrainedByHerDraught:
    	        return "ConstrainedByHerDraught";
    	    case Moored:
    	        return "Moored";
    	    case Aground:
    	        return "Aground";
    	    case EngagedInFishing:
    	        return "EngagedInFishing";
    	    case UnderWaySailing:
    	        return "UnderWaySailing";
    	    case ReservedForFutureAmendmentOfNavigationalStatusForHsc:
    	        return "ReservedForFutureAmendmentOfNavigationalStatusForHsc";
    	    case ReservedForFutureAmendmentOfNavigationalStatusForWig:
    	        return "ReservedForFutureAmendmentOfNavigationalStatusForWig";
    	    case ReservedForFutureUse1:
    	        return "ReservedForFutureUse1";
    	    case ReservedForFutureUse2:
    	        return "ReservedForFutureUse2";
    	    case ReservedForFutureUse3:
    	        return "ReservedForFutureUse3";
    	    case AisSartIsActive:
    	        return "AisSartIsActive";
    	    case NotDefined:
    	        return "NotDefined";
    	    default:
    	        throw new IllegalArgumentException( "Unknown NavigationStatus constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "UnderWayUsingEngine":
    	        return UnderWayUsingEngine;
    	    case "AtAnchor":
    	        return AtAnchor;
    	    case "NotUnderCommand":
    	        return NotUnderCommand;
    	    case "RestrictedManeuverability":
    	        return RestrictedManeuverability;
    	    case "ConstrainedByHerDraught":
    	        return ConstrainedByHerDraught;
    	    case "Moored":
    	        return Moored;
    	    case "Aground":
    	        return Aground;
    	    case "EngagedInFishing":
    	        return EngagedInFishing;
    	    case "UnderWaySailing":
    	        return UnderWaySailing;
    	    case "ReservedForFutureAmendmentOfNavigationalStatusForHsc":
    	        return ReservedForFutureAmendmentOfNavigationalStatusForHsc;
    	    case "ReservedForFutureAmendmentOfNavigationalStatusForWig":
    	        return ReservedForFutureAmendmentOfNavigationalStatusForWig;
    	    case "ReservedForFutureUse1":
    	        return ReservedForFutureUse1;
    	    case "ReservedForFutureUse2":
    	        return ReservedForFutureUse2;
    	    case "ReservedForFutureUse3":
    	        return ReservedForFutureUse3;
    	    case "AisSartIsActive":
    	        return AisSartIsActive;
    	    case "NotDefined":
    	        return NotDefined;
    	    default:
    	        throw new IllegalArgumentException( "Unknown NavigationStatus constant name:" + value );
    	}
    }

}

