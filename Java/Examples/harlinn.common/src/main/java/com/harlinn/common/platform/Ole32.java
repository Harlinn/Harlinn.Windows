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

public class Ole32 {
	
	static {
		// Load the native library
        System.loadLibrary("harlinn.common.jni-x64r"); 
    }
	
	public static final int S_OK = 0;
	public static final int S_FALSE = 1;
	
	public static final int RPC_E_CHANGED_MODE = 0x80010106;
	
	public static final int COINITBASE_MULTITHREADED = 0x0;
	public static final int COINIT_APARTMENTTHREADED  = 0x2;
	public static final int COINIT_DISABLE_OLE1DDE = 0x4;
	public static final int COINIT_SPEED_OVER_MEMORY = 0x8;
	
	public static final native int CoInitializeEx(int dwCoInit);
	public static final native void CoUninitialize();
	public static final native byte[] CoCreateGuid();
	public static final native String StringFromGUID(int a, short b, short c, byte d, byte e, byte f, byte g, byte h, byte i, byte j, byte k);
	public static final native byte[] IIDFromString(String str);
	
	

}
