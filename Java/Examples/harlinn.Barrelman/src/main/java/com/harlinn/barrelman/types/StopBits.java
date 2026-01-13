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

public class StopBits {
    public final static int None = 0;
    public final static int One = 1;
    public final static int Two = 2;
    public final static int OnePointFive = 3;

    public final static String toString(int value) {
    	switch(value) {
    	    case None:
    	        return "None";
    	    case One:
    	        return "One";
    	    case Two:
    	        return "Two";
    	    case OnePointFive:
    	        return "OnePointFive";
    	    default:
    	        throw new IllegalArgumentException( "Unknown StopBits constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "None":
    	        return None;
    	    case "One":
    	        return One;
    	    case "Two":
    	        return Two;
    	    case "OnePointFive":
    	        return OnePointFive;
    	    default:
    	        throw new IllegalArgumentException( "Unknown StopBits constant name:" + value );
    	}
    }

}

