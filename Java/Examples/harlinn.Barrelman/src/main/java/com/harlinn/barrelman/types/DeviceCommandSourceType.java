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

public class DeviceCommandSourceType {
    public final static int Unknown = 0;
    public final static int Session = 1;
    public final static int Device = 2;
    public final static int Source = 3;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case Session:
    	        return "Session";
    	    case Device:
    	        return "Device";
    	    case Source:
    	        return "Source";
    	    default:
    	        throw new IllegalArgumentException( "Unknown DeviceCommandSourceType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "Session":
    	        return Session;
    	    case "Device":
    	        return Device;
    	    case "Source":
    	        return Source;
    	    default:
    	        throw new IllegalArgumentException( "Unknown DeviceCommandSourceType constant name:" + value );
    	}
    }

}

