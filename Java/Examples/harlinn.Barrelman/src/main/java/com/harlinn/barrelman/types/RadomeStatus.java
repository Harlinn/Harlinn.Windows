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

public class RadomeStatus {
    public final static int None = 0;
    public final static int Overpressure = 1;
    public final static int Overridden = 2;
    public final static int Purging = 4;
    public final static int NormalOperation = 8;
    public final static int RadarPowerOff = 16;

    public final static String toString(int value) {
    	switch(value) {
    	    case None:
    	        return "None";
    	    case Overpressure:
    	        return "Overpressure";
    	    case Overridden:
    	        return "Overridden";
    	    case Purging:
    	        return "Purging";
    	    case NormalOperation:
    	        return "NormalOperation";
    	    case RadarPowerOff:
    	        return "RadarPowerOff";
    	    default:
    	        throw new IllegalArgumentException( "Unknown RadomeStatus constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "None":
    	        return None;
    	    case "Overpressure":
    	        return Overpressure;
    	    case "Overridden":
    	        return Overridden;
    	    case "Purging":
    	        return Purging;
    	    case "NormalOperation":
    	        return NormalOperation;
    	    case "RadarPowerOff":
    	        return RadarPowerOff;
    	    default:
    	        throw new IllegalArgumentException( "Unknown RadomeStatus constant name:" + value );
    	}
    }

}

