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

public class Parity {
    public final static int None = 0;
    public final static int Odd = 1;
    public final static int Even = 2;
    public final static int Mark = 3;
    public final static int Space = 4;

    public final static String toString(int value) {
    	switch(value) {
    	    case None:
    	        return "None";
    	    case Odd:
    	        return "Odd";
    	    case Even:
    	        return "Even";
    	    case Mark:
    	        return "Mark";
    	    case Space:
    	        return "Space";
    	    default:
    	        throw new IllegalArgumentException( "Unknown Parity constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "None":
    	        return None;
    	    case "Odd":
    	        return Odd;
    	    case "Even":
    	        return Even;
    	    case "Mark":
    	        return Mark;
    	    case "Space":
    	        return Space;
    	    default:
    	        throw new IllegalArgumentException( "Unknown Parity constant name:" + value );
    	}
    }

}

