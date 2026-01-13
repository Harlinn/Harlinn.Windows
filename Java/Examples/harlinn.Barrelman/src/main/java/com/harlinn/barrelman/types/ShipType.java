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

public class ShipType {
    public final static int NotAvailable = 0;
    public final static int WingInGround = 20;
    public final static int WingInGroundHazardousCategoryA = 21;
    public final static int WingInGroundHazardousCategoryB = 22;
    public final static int WingInGroundHazardousCategoryC = 23;
    public final static int WingInGroundHazardousCategoryD = 24;
    public final static int WingInGroundReserved1 = 25;
    public final static int WingInGroundReserved2 = 26;
    public final static int WingInGroundReserved3 = 27;
    public final static int WingInGroundReserved4 = 28;
    public final static int WingInGroundReserved5 = 29;
    public final static int Fishing = 30;
    public final static int Towing = 31;
    public final static int TowingLarge = 32;
    public final static int DredgingOrUnderwaterOps = 33;
    public final static int DivingOps = 34;
    public final static int MilitaryOps = 35;
    public final static int Sailing = 36;
    public final static int PleasureCraft = 37;
    public final static int Reserved1 = 38;
    public final static int Reserved2 = 39;
    public final static int HighSpeedCraft = 40;
    public final static int HighSpeedCraftHazardousCategoryA = 41;
    public final static int HighSpeedCraftHazardousCategoryB = 42;
    public final static int HighSpeedCraftHazardousCategoryC = 43;
    public final static int HighSpeedCraftHazardousCategoryD = 44;
    public final static int HighSpeedCraftReserved1 = 45;
    public final static int HighSpeedCraftReserved2 = 46;
    public final static int HighSpeedCraftReserved3 = 47;
    public final static int HighSpeedCraftReserved4 = 48;
    public final static int HighSpeedCraftNoAdditionalInformation = 49;
    public final static int PilotVessel = 50;
    public final static int SearchAndRescueVessel = 51;
    public final static int Tug = 52;
    public final static int PortTender = 53;
    public final static int AntiPollutionEquipment = 54;
    public final static int LawEnforcement = 55;
    public final static int SpareLocalVessel1 = 56;
    public final static int SpareLocalVessel2 = 57;
    public final static int MedicalTransport = 58;
    public final static int NonCombatantShip = 59;
    public final static int Passenger = 60;
    public final static int PassengerHazardousCategoryA = 61;
    public final static int PassengerHazardousCategoryB = 62;
    public final static int PassengerHazardousCategoryC = 63;
    public final static int PassengerHazardousCategoryD = 64;
    public final static int PassengerReserved1 = 65;
    public final static int PassengerReserved2 = 66;
    public final static int PassengerReserved3 = 67;
    public final static int PassengerReserved4 = 68;
    public final static int PassengerNoAdditionalInformation = 69;
    public final static int Cargo = 70;
    public final static int CargoHazardousCategoryA = 71;
    public final static int CargoHazardousCategoryB = 72;
    public final static int CargoHazardousCategoryC = 73;
    public final static int CargoHazardousCategoryD = 74;
    public final static int CargoReserved1 = 75;
    public final static int CargoReserved2 = 76;
    public final static int CargoReserved3 = 77;
    public final static int CargoReserved4 = 78;
    public final static int CargoNoAdditionalInformation = 79;
    public final static int Tanker = 80;
    public final static int TankerHazardousCategoryA = 81;
    public final static int TankerHazardousCategoryB = 82;
    public final static int TankerHazardousCategoryC = 83;
    public final static int TankerHazardousCategoryD = 84;
    public final static int TankerReserved1 = 85;
    public final static int TankerReserved2 = 86;
    public final static int TankerReserved3 = 87;
    public final static int TankerReserved4 = 88;
    public final static int TankerNoAdditionalInformation = 89;
    public final static int OtherType = 90;
    public final static int OtherTypeHazardousCategoryA = 91;
    public final static int OtherTypeHazardousCategoryB = 92;
    public final static int OtherTypeHazardousCategoryC = 93;
    public final static int OtherTypeHazardousCategoryD = 94;
    public final static int OtherTypeReserved1 = 95;
    public final static int OtherTypeReserved2 = 96;
    public final static int OtherTypeReserved3 = 97;
    public final static int OtherTypeReserved4 = 98;
    public final static int OtherTypeNoAdditionalInformation = 99;

    public final static String toString(int value) {
    	switch(value) {
    	    case NotAvailable:
    	        return "NotAvailable";
    	    case WingInGround:
    	        return "WingInGround";
    	    case WingInGroundHazardousCategoryA:
    	        return "WingInGroundHazardousCategoryA";
    	    case WingInGroundHazardousCategoryB:
    	        return "WingInGroundHazardousCategoryB";
    	    case WingInGroundHazardousCategoryC:
    	        return "WingInGroundHazardousCategoryC";
    	    case WingInGroundHazardousCategoryD:
    	        return "WingInGroundHazardousCategoryD";
    	    case WingInGroundReserved1:
    	        return "WingInGroundReserved1";
    	    case WingInGroundReserved2:
    	        return "WingInGroundReserved2";
    	    case WingInGroundReserved3:
    	        return "WingInGroundReserved3";
    	    case WingInGroundReserved4:
    	        return "WingInGroundReserved4";
    	    case WingInGroundReserved5:
    	        return "WingInGroundReserved5";
    	    case Fishing:
    	        return "Fishing";
    	    case Towing:
    	        return "Towing";
    	    case TowingLarge:
    	        return "TowingLarge";
    	    case DredgingOrUnderwaterOps:
    	        return "DredgingOrUnderwaterOps";
    	    case DivingOps:
    	        return "DivingOps";
    	    case MilitaryOps:
    	        return "MilitaryOps";
    	    case Sailing:
    	        return "Sailing";
    	    case PleasureCraft:
    	        return "PleasureCraft";
    	    case Reserved1:
    	        return "Reserved1";
    	    case Reserved2:
    	        return "Reserved2";
    	    case HighSpeedCraft:
    	        return "HighSpeedCraft";
    	    case HighSpeedCraftHazardousCategoryA:
    	        return "HighSpeedCraftHazardousCategoryA";
    	    case HighSpeedCraftHazardousCategoryB:
    	        return "HighSpeedCraftHazardousCategoryB";
    	    case HighSpeedCraftHazardousCategoryC:
    	        return "HighSpeedCraftHazardousCategoryC";
    	    case HighSpeedCraftHazardousCategoryD:
    	        return "HighSpeedCraftHazardousCategoryD";
    	    case HighSpeedCraftReserved1:
    	        return "HighSpeedCraftReserved1";
    	    case HighSpeedCraftReserved2:
    	        return "HighSpeedCraftReserved2";
    	    case HighSpeedCraftReserved3:
    	        return "HighSpeedCraftReserved3";
    	    case HighSpeedCraftReserved4:
    	        return "HighSpeedCraftReserved4";
    	    case HighSpeedCraftNoAdditionalInformation:
    	        return "HighSpeedCraftNoAdditionalInformation";
    	    case PilotVessel:
    	        return "PilotVessel";
    	    case SearchAndRescueVessel:
    	        return "SearchAndRescueVessel";
    	    case Tug:
    	        return "Tug";
    	    case PortTender:
    	        return "PortTender";
    	    case AntiPollutionEquipment:
    	        return "AntiPollutionEquipment";
    	    case LawEnforcement:
    	        return "LawEnforcement";
    	    case SpareLocalVessel1:
    	        return "SpareLocalVessel1";
    	    case SpareLocalVessel2:
    	        return "SpareLocalVessel2";
    	    case MedicalTransport:
    	        return "MedicalTransport";
    	    case NonCombatantShip:
    	        return "NonCombatantShip";
    	    case Passenger:
    	        return "Passenger";
    	    case PassengerHazardousCategoryA:
    	        return "PassengerHazardousCategoryA";
    	    case PassengerHazardousCategoryB:
    	        return "PassengerHazardousCategoryB";
    	    case PassengerHazardousCategoryC:
    	        return "PassengerHazardousCategoryC";
    	    case PassengerHazardousCategoryD:
    	        return "PassengerHazardousCategoryD";
    	    case PassengerReserved1:
    	        return "PassengerReserved1";
    	    case PassengerReserved2:
    	        return "PassengerReserved2";
    	    case PassengerReserved3:
    	        return "PassengerReserved3";
    	    case PassengerReserved4:
    	        return "PassengerReserved4";
    	    case PassengerNoAdditionalInformation:
    	        return "PassengerNoAdditionalInformation";
    	    case Cargo:
    	        return "Cargo";
    	    case CargoHazardousCategoryA:
    	        return "CargoHazardousCategoryA";
    	    case CargoHazardousCategoryB:
    	        return "CargoHazardousCategoryB";
    	    case CargoHazardousCategoryC:
    	        return "CargoHazardousCategoryC";
    	    case CargoHazardousCategoryD:
    	        return "CargoHazardousCategoryD";
    	    case CargoReserved1:
    	        return "CargoReserved1";
    	    case CargoReserved2:
    	        return "CargoReserved2";
    	    case CargoReserved3:
    	        return "CargoReserved3";
    	    case CargoReserved4:
    	        return "CargoReserved4";
    	    case CargoNoAdditionalInformation:
    	        return "CargoNoAdditionalInformation";
    	    case Tanker:
    	        return "Tanker";
    	    case TankerHazardousCategoryA:
    	        return "TankerHazardousCategoryA";
    	    case TankerHazardousCategoryB:
    	        return "TankerHazardousCategoryB";
    	    case TankerHazardousCategoryC:
    	        return "TankerHazardousCategoryC";
    	    case TankerHazardousCategoryD:
    	        return "TankerHazardousCategoryD";
    	    case TankerReserved1:
    	        return "TankerReserved1";
    	    case TankerReserved2:
    	        return "TankerReserved2";
    	    case TankerReserved3:
    	        return "TankerReserved3";
    	    case TankerReserved4:
    	        return "TankerReserved4";
    	    case TankerNoAdditionalInformation:
    	        return "TankerNoAdditionalInformation";
    	    case OtherType:
    	        return "OtherType";
    	    case OtherTypeHazardousCategoryA:
    	        return "OtherTypeHazardousCategoryA";
    	    case OtherTypeHazardousCategoryB:
    	        return "OtherTypeHazardousCategoryB";
    	    case OtherTypeHazardousCategoryC:
    	        return "OtherTypeHazardousCategoryC";
    	    case OtherTypeHazardousCategoryD:
    	        return "OtherTypeHazardousCategoryD";
    	    case OtherTypeReserved1:
    	        return "OtherTypeReserved1";
    	    case OtherTypeReserved2:
    	        return "OtherTypeReserved2";
    	    case OtherTypeReserved3:
    	        return "OtherTypeReserved3";
    	    case OtherTypeReserved4:
    	        return "OtherTypeReserved4";
    	    case OtherTypeNoAdditionalInformation:
    	        return "OtherTypeNoAdditionalInformation";
    	    default:
    	        throw new IllegalArgumentException( "Unknown ShipType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "NotAvailable":
    	        return NotAvailable;
    	    case "WingInGround":
    	        return WingInGround;
    	    case "WingInGroundHazardousCategoryA":
    	        return WingInGroundHazardousCategoryA;
    	    case "WingInGroundHazardousCategoryB":
    	        return WingInGroundHazardousCategoryB;
    	    case "WingInGroundHazardousCategoryC":
    	        return WingInGroundHazardousCategoryC;
    	    case "WingInGroundHazardousCategoryD":
    	        return WingInGroundHazardousCategoryD;
    	    case "WingInGroundReserved1":
    	        return WingInGroundReserved1;
    	    case "WingInGroundReserved2":
    	        return WingInGroundReserved2;
    	    case "WingInGroundReserved3":
    	        return WingInGroundReserved3;
    	    case "WingInGroundReserved4":
    	        return WingInGroundReserved4;
    	    case "WingInGroundReserved5":
    	        return WingInGroundReserved5;
    	    case "Fishing":
    	        return Fishing;
    	    case "Towing":
    	        return Towing;
    	    case "TowingLarge":
    	        return TowingLarge;
    	    case "DredgingOrUnderwaterOps":
    	        return DredgingOrUnderwaterOps;
    	    case "DivingOps":
    	        return DivingOps;
    	    case "MilitaryOps":
    	        return MilitaryOps;
    	    case "Sailing":
    	        return Sailing;
    	    case "PleasureCraft":
    	        return PleasureCraft;
    	    case "Reserved1":
    	        return Reserved1;
    	    case "Reserved2":
    	        return Reserved2;
    	    case "HighSpeedCraft":
    	        return HighSpeedCraft;
    	    case "HighSpeedCraftHazardousCategoryA":
    	        return HighSpeedCraftHazardousCategoryA;
    	    case "HighSpeedCraftHazardousCategoryB":
    	        return HighSpeedCraftHazardousCategoryB;
    	    case "HighSpeedCraftHazardousCategoryC":
    	        return HighSpeedCraftHazardousCategoryC;
    	    case "HighSpeedCraftHazardousCategoryD":
    	        return HighSpeedCraftHazardousCategoryD;
    	    case "HighSpeedCraftReserved1":
    	        return HighSpeedCraftReserved1;
    	    case "HighSpeedCraftReserved2":
    	        return HighSpeedCraftReserved2;
    	    case "HighSpeedCraftReserved3":
    	        return HighSpeedCraftReserved3;
    	    case "HighSpeedCraftReserved4":
    	        return HighSpeedCraftReserved4;
    	    case "HighSpeedCraftNoAdditionalInformation":
    	        return HighSpeedCraftNoAdditionalInformation;
    	    case "PilotVessel":
    	        return PilotVessel;
    	    case "SearchAndRescueVessel":
    	        return SearchAndRescueVessel;
    	    case "Tug":
    	        return Tug;
    	    case "PortTender":
    	        return PortTender;
    	    case "AntiPollutionEquipment":
    	        return AntiPollutionEquipment;
    	    case "LawEnforcement":
    	        return LawEnforcement;
    	    case "SpareLocalVessel1":
    	        return SpareLocalVessel1;
    	    case "SpareLocalVessel2":
    	        return SpareLocalVessel2;
    	    case "MedicalTransport":
    	        return MedicalTransport;
    	    case "NonCombatantShip":
    	        return NonCombatantShip;
    	    case "Passenger":
    	        return Passenger;
    	    case "PassengerHazardousCategoryA":
    	        return PassengerHazardousCategoryA;
    	    case "PassengerHazardousCategoryB":
    	        return PassengerHazardousCategoryB;
    	    case "PassengerHazardousCategoryC":
    	        return PassengerHazardousCategoryC;
    	    case "PassengerHazardousCategoryD":
    	        return PassengerHazardousCategoryD;
    	    case "PassengerReserved1":
    	        return PassengerReserved1;
    	    case "PassengerReserved2":
    	        return PassengerReserved2;
    	    case "PassengerReserved3":
    	        return PassengerReserved3;
    	    case "PassengerReserved4":
    	        return PassengerReserved4;
    	    case "PassengerNoAdditionalInformation":
    	        return PassengerNoAdditionalInformation;
    	    case "Cargo":
    	        return Cargo;
    	    case "CargoHazardousCategoryA":
    	        return CargoHazardousCategoryA;
    	    case "CargoHazardousCategoryB":
    	        return CargoHazardousCategoryB;
    	    case "CargoHazardousCategoryC":
    	        return CargoHazardousCategoryC;
    	    case "CargoHazardousCategoryD":
    	        return CargoHazardousCategoryD;
    	    case "CargoReserved1":
    	        return CargoReserved1;
    	    case "CargoReserved2":
    	        return CargoReserved2;
    	    case "CargoReserved3":
    	        return CargoReserved3;
    	    case "CargoReserved4":
    	        return CargoReserved4;
    	    case "CargoNoAdditionalInformation":
    	        return CargoNoAdditionalInformation;
    	    case "Tanker":
    	        return Tanker;
    	    case "TankerHazardousCategoryA":
    	        return TankerHazardousCategoryA;
    	    case "TankerHazardousCategoryB":
    	        return TankerHazardousCategoryB;
    	    case "TankerHazardousCategoryC":
    	        return TankerHazardousCategoryC;
    	    case "TankerHazardousCategoryD":
    	        return TankerHazardousCategoryD;
    	    case "TankerReserved1":
    	        return TankerReserved1;
    	    case "TankerReserved2":
    	        return TankerReserved2;
    	    case "TankerReserved3":
    	        return TankerReserved3;
    	    case "TankerReserved4":
    	        return TankerReserved4;
    	    case "TankerNoAdditionalInformation":
    	        return TankerNoAdditionalInformation;
    	    case "OtherType":
    	        return OtherType;
    	    case "OtherTypeHazardousCategoryA":
    	        return OtherTypeHazardousCategoryA;
    	    case "OtherTypeHazardousCategoryB":
    	        return OtherTypeHazardousCategoryB;
    	    case "OtherTypeHazardousCategoryC":
    	        return OtherTypeHazardousCategoryC;
    	    case "OtherTypeHazardousCategoryD":
    	        return OtherTypeHazardousCategoryD;
    	    case "OtherTypeReserved1":
    	        return OtherTypeReserved1;
    	    case "OtherTypeReserved2":
    	        return OtherTypeReserved2;
    	    case "OtherTypeReserved3":
    	        return OtherTypeReserved3;
    	    case "OtherTypeReserved4":
    	        return OtherTypeReserved4;
    	    case "OtherTypeNoAdditionalInformation":
    	        return OtherTypeNoAdditionalInformation;
    	    default:
    	        throw new IllegalArgumentException( "Unknown ShipType constant name:" + value );
    	}
    }

}

