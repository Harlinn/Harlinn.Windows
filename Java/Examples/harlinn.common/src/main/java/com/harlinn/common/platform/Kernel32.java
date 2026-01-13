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
package com.harlinn.common.platform;

public class Kernel32 {
	static {
		// Load the native library
        System.loadLibrary("harlinn.common.jni-x64r"); 
    }
	
	public static final native int GetLastError();
	public static final native String GetErrorMessage(int errorCode);
	
	public static final native long GetSystemTimePreciseAsFileTime( );
	public static final native long FileTimeToLocalFileTime( long systemTime );
	public static final native long LocalFileTimeToFileTime( long localTime );
}
