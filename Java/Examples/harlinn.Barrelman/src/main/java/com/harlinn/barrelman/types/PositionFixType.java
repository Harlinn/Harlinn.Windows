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

public class PositionFixType {
    public final static int Undefined1 = 0;
    public final static int Gps = 1;
    public final static int Glonass = 2;
    public final static int CombinedGpsAndGlonass = 3;
    public final static int LoranC = 4;
    public final static int Chayka = 5;
    public final static int IntegratedNavigationSystem = 6;
    public final static int Surveyed = 7;
    public final static int Galileo = 8;
    public final static int Undefined2 = 15;

    public final static String toString(int value) {
    	switch(value) {
    	    case Undefined1:
    	        return "Undefined1";
    	    case Gps:
    	        return "Gps";
    	    case Glonass:
    	        return "Glonass";
    	    case CombinedGpsAndGlonass:
    	        return "CombinedGpsAndGlonass";
    	    case LoranC:
    	        return "LoranC";
    	    case Chayka:
    	        return "Chayka";
    	    case IntegratedNavigationSystem:
    	        return "IntegratedNavigationSystem";
    	    case Surveyed:
    	        return "Surveyed";
    	    case Galileo:
    	        return "Galileo";
    	    case Undefined2:
    	        return "Undefined2";
    	    default:
    	        throw new IllegalArgumentException( "Unknown PositionFixType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Undefined1":
    	        return Undefined1;
    	    case "Gps":
    	        return Gps;
    	    case "Glonass":
    	        return Glonass;
    	    case "CombinedGpsAndGlonass":
    	        return CombinedGpsAndGlonass;
    	    case "LoranC":
    	        return LoranC;
    	    case "Chayka":
    	        return Chayka;
    	    case "IntegratedNavigationSystem":
    	        return IntegratedNavigationSystem;
    	    case "Surveyed":
    	        return Surveyed;
    	    case "Galileo":
    	        return Galileo;
    	    case "Undefined2":
    	        return Undefined2;
    	    default:
    	        throw new IllegalArgumentException( "Unknown PositionFixType constant name:" + value );
    	}
    }

}

