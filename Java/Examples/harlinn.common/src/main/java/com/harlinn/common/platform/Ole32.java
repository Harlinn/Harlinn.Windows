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
