package com.harlinn.barrelman.types;

public class NavigationalAidType {
    public final static int NotSpecified = 0;
    public final static int ReferencePoint = 1;
    public final static int Racon = 2;
    public final static int FixedStuctureOffShore = 3;
    public final static int Spare = 4;
    public final static int LightWithoutSectors = 5;
    public final static int LightWithSectors = 6;
    public final static int LeadingLightFront = 7;
    public final static int LeadingLigthRear = 8;
    public final static int BeaconCardinalN = 9;
    public final static int BeaconCardinalE = 10;
    public final static int BeaconCardinalS = 11;
    public final static int BeaconCardinalW = 12;
    public final static int BeaconPortHand = 13;
    public final static int BeaconStarboardHand = 14;
    public final static int BeaconPreferredChannelPortHand = 15;
    public final static int BeaconPreferredChannelStarboardHand = 16;
    public final static int BeaconIsolatedDanger = 17;
    public final static int BeaconSafeWater = 18;
    public final static int BeaconSpecialMark = 19;
    public final static int CardinalMarkN = 20;
    public final static int CardinalMarkE = 21;
    public final static int CardinalMarkS = 22;
    public final static int CardinalMarkW = 23;
    public final static int PortHandMark = 24;
    public final static int StarboardHandMark = 25;
    public final static int PreferredChannelPortHand = 26;
    public final static int PreferredChannelStarboardHand = 27;
    public final static int IsolatedDanger = 28;
    public final static int SafeWater = 29;
    public final static int SpecialMark = 30;
    public final static int LightVessel = 31;

    public final static String toString(int value) {
    	switch(value) {
    	    case NotSpecified:
    	        return "NotSpecified";
    	    case ReferencePoint:
    	        return "ReferencePoint";
    	    case Racon:
    	        return "Racon";
    	    case FixedStuctureOffShore:
    	        return "FixedStuctureOffShore";
    	    case Spare:
    	        return "Spare";
    	    case LightWithoutSectors:
    	        return "LightWithoutSectors";
    	    case LightWithSectors:
    	        return "LightWithSectors";
    	    case LeadingLightFront:
    	        return "LeadingLightFront";
    	    case LeadingLigthRear:
    	        return "LeadingLigthRear";
    	    case BeaconCardinalN:
    	        return "BeaconCardinalN";
    	    case BeaconCardinalE:
    	        return "BeaconCardinalE";
    	    case BeaconCardinalS:
    	        return "BeaconCardinalS";
    	    case BeaconCardinalW:
    	        return "BeaconCardinalW";
    	    case BeaconPortHand:
    	        return "BeaconPortHand";
    	    case BeaconStarboardHand:
    	        return "BeaconStarboardHand";
    	    case BeaconPreferredChannelPortHand:
    	        return "BeaconPreferredChannelPortHand";
    	    case BeaconPreferredChannelStarboardHand:
    	        return "BeaconPreferredChannelStarboardHand";
    	    case BeaconIsolatedDanger:
    	        return "BeaconIsolatedDanger";
    	    case BeaconSafeWater:
    	        return "BeaconSafeWater";
    	    case BeaconSpecialMark:
    	        return "BeaconSpecialMark";
    	    case CardinalMarkN:
    	        return "CardinalMarkN";
    	    case CardinalMarkE:
    	        return "CardinalMarkE";
    	    case CardinalMarkS:
    	        return "CardinalMarkS";
    	    case CardinalMarkW:
    	        return "CardinalMarkW";
    	    case PortHandMark:
    	        return "PortHandMark";
    	    case StarboardHandMark:
    	        return "StarboardHandMark";
    	    case PreferredChannelPortHand:
    	        return "PreferredChannelPortHand";
    	    case PreferredChannelStarboardHand:
    	        return "PreferredChannelStarboardHand";
    	    case IsolatedDanger:
    	        return "IsolatedDanger";
    	    case SafeWater:
    	        return "SafeWater";
    	    case SpecialMark:
    	        return "SpecialMark";
    	    case LightVessel:
    	        return "LightVessel";
    	    default:
    	        throw new IllegalArgumentException( "Unknown NavigationalAidType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "NotSpecified":
    	        return NotSpecified;
    	    case "ReferencePoint":
    	        return ReferencePoint;
    	    case "Racon":
    	        return Racon;
    	    case "FixedStuctureOffShore":
    	        return FixedStuctureOffShore;
    	    case "Spare":
    	        return Spare;
    	    case "LightWithoutSectors":
    	        return LightWithoutSectors;
    	    case "LightWithSectors":
    	        return LightWithSectors;
    	    case "LeadingLightFront":
    	        return LeadingLightFront;
    	    case "LeadingLigthRear":
    	        return LeadingLigthRear;
    	    case "BeaconCardinalN":
    	        return BeaconCardinalN;
    	    case "BeaconCardinalE":
    	        return BeaconCardinalE;
    	    case "BeaconCardinalS":
    	        return BeaconCardinalS;
    	    case "BeaconCardinalW":
    	        return BeaconCardinalW;
    	    case "BeaconPortHand":
    	        return BeaconPortHand;
    	    case "BeaconStarboardHand":
    	        return BeaconStarboardHand;
    	    case "BeaconPreferredChannelPortHand":
    	        return BeaconPreferredChannelPortHand;
    	    case "BeaconPreferredChannelStarboardHand":
    	        return BeaconPreferredChannelStarboardHand;
    	    case "BeaconIsolatedDanger":
    	        return BeaconIsolatedDanger;
    	    case "BeaconSafeWater":
    	        return BeaconSafeWater;
    	    case "BeaconSpecialMark":
    	        return BeaconSpecialMark;
    	    case "CardinalMarkN":
    	        return CardinalMarkN;
    	    case "CardinalMarkE":
    	        return CardinalMarkE;
    	    case "CardinalMarkS":
    	        return CardinalMarkS;
    	    case "CardinalMarkW":
    	        return CardinalMarkW;
    	    case "PortHandMark":
    	        return PortHandMark;
    	    case "StarboardHandMark":
    	        return StarboardHandMark;
    	    case "PreferredChannelPortHand":
    	        return PreferredChannelPortHand;
    	    case "PreferredChannelStarboardHand":
    	        return PreferredChannelStarboardHand;
    	    case "IsolatedDanger":
    	        return IsolatedDanger;
    	    case "SafeWater":
    	        return SafeWater;
    	    case "SpecialMark":
    	        return SpecialMark;
    	    case "LightVessel":
    	        return LightVessel;
    	    default:
    	        throw new IllegalArgumentException( "Unknown NavigationalAidType constant name:" + value );
    	}
    }

}

