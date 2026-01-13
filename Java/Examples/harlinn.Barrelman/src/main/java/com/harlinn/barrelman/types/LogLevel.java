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

public class LogLevel {
    public final static int Unknown = 0;
    public final static int Finest = 10000;
    public final static int Finer = 20000;
    public final static int Trace = 20000;
    public final static int Fine = 30000;
    public final static int Info = 40000;
    public final static int Notice = 50000;
    public final static int Warn = 60000;
    public final static int Error = 70000;
    public final static int Severe = 80000;
    public final static int Critical = 90000;
    public final static int Alert = 100000;
    public final static int Fatal = 110000;
    public final static int Emergency = 120000;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case Finest:
    	        return "Finest";
    	    case Finer:
    	        return "Finer";
    	    case Fine:
    	        return "Fine";
    	    case Info:
    	        return "Info";
    	    case Notice:
    	        return "Notice";
    	    case Warn:
    	        return "Warn";
    	    case Error:
    	        return "Error";
    	    case Severe:
    	        return "Severe";
    	    case Critical:
    	        return "Critical";
    	    case Alert:
    	        return "Alert";
    	    case Fatal:
    	        return "Fatal";
    	    case Emergency:
    	        return "Emergency";
    	    default:
    	        throw new IllegalArgumentException( "Unknown LogLevel constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "Finest":
    	        return Finest;
    	    case "Finer":
    	        return Finer;
    	    case "Trace":
    	        return Trace;
    	    case "Fine":
    	        return Fine;
    	    case "Info":
    	        return Info;
    	    case "Notice":
    	        return Notice;
    	    case "Warn":
    	        return Warn;
    	    case "Error":
    	        return Error;
    	    case "Severe":
    	        return Severe;
    	    case "Critical":
    	        return Critical;
    	    case "Alert":
    	        return Alert;
    	    case "Fatal":
    	        return Fatal;
    	    case "Emergency":
    	        return Emergency;
    	    default:
    	        throw new IllegalArgumentException( "Unknown LogLevel constant name:" + value );
    	}
    }

}

