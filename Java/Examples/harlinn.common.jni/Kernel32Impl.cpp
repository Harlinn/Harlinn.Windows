/*
   Copyright 2024-2025 Espen Harlinn

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

#include "pch.h"
#include "com_harlinn_common_platform_Kernel32.h"
#include "jniHelpers.h"

extern "C" {

    /*
     * Class:     com_harlinn_common_platform_Kernel32
     * Method:    GetLastError
     * Signature: ()I
     */
    JNIEXPORT jint JNICALL Java_com_harlinn_common_platform_Kernel32_GetLastError(JNIEnv*, jclass)
    {
        return GetLastError();
    }

    /*
     * Class:     com_harlinn_common_platform_Kernel32
     * Method:    GetErrorMessage
     * Signature: (I)Ljava/lang/String;
     */
    JNIEXPORT jstring JNICALL Java_com_harlinn_common_platform_Kernel32_GetErrorMessage(JNIEnv* jniEnv, jclass, jint errorId)
    {
        wchar_t buffer[4096]{};
        int length = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, errorId, 0, buffer, 4096, nullptr);
        return ToJString(jniEnv,buffer, static_cast<size_t>(length));
    }

    /*
     * Class:     com_harlinn_common_platform_Kernel32
     * Method:    GetSystemTimePreciseAsFileTime
     * Signature: ()J
     */
    JNIEXPORT jlong JNICALL Java_com_harlinn_common_platform_Kernel32_GetSystemTimePreciseAsFileTime(JNIEnv*, jclass)
    {
        jlong result = 0;
        GetSystemTimePreciseAsFileTime(reinterpret_cast<LPFILETIME>(&result));
        return result;
    }

    /*
     * Class:     com_harlinn_common_platform_Kernel32
     * Method:    FileTimeToLocalFileTime
     * Signature: (J)J
     */
    JNIEXPORT jlong JNICALL Java_com_harlinn_common_platform_Kernel32_FileTimeToLocalFileTime(JNIEnv*, jclass, jlong systemTime)
    {
        jlong result = 0;
        FileTimeToLocalFileTime(reinterpret_cast<const FILETIME*>(&systemTime),reinterpret_cast<LPFILETIME>(&result));
        return result;
    }

    /*
     * Class:     com_harlinn_common_platform_Kernel32
     * Method:    LocalFileTimeToFileTime
     * Signature: (J)J
     */
    JNIEXPORT jlong JNICALL Java_com_harlinn_common_platform_Kernel32_LocalFileTimeToFileTime(JNIEnv*, jclass, jlong localTime)
    {
        jlong result = 0;
        LocalFileTimeToFileTime(reinterpret_cast<const FILETIME*>(&localTime), reinterpret_cast<LPFILETIME>(&result));
        return result;
    }


}


