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
