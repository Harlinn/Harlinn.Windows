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

#include "pch.h"
#include "com_harlinn_common_platform_Ole32.h"

#include "jniHelpers.h"
#include <bit>

extern "C" 
{
    /*
     * Class:     com_harlinn_common_platform_Ole32
     * Method:    CoInitializeEx
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_com_harlinn_common_platform_Ole32_CoInitializeEx(JNIEnv* jniEnv, jclass, jint dwCoInit)
    {
        return CoInitializeEx(nullptr, dwCoInit);
    }

    /*
     * Class:     com_harlinn_common_platform_Ole32
     * Method:    CoUninitialize
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_com_harlinn_common_platform_Ole32_CoUninitialize(JNIEnv* jniEnv, jclass)
    {
        CoUninitialize();
    }

    /*
     * Class:     com_harlinn_common_platform_Ole32
     * Method:    CoCreateGuid
     * Signature: ()[B
     */
    JNIEXPORT jbyteArray JNICALL Java_com_harlinn_common_platform_Ole32_CoCreateGuid(JNIEnv* jniEnv, jclass)
    {
        GUID guid{};
        CoCreateGuid(&guid);

        jboolean isCopy;

        auto result = jniEnv->NewByteArray(16);
        jbyte* bytes = jniEnv->GetByteArrayElements(result, &isCopy);
        *((GUID*)bytes) = guid;
        jniEnv->ReleaseByteArrayElements(result, bytes, 0);
        return result;
    }

    /*
     * Class:     com_harlinn_common_platform_Ole32
     * Method:    StringFromGUID
     * Signature: (ISSBBBBBBBB)Ljava/lang/String;
     */
    JNIEXPORT jstring JNICALL Java_com_harlinn_common_platform_Ole32_StringFromGUID(JNIEnv* jniEnv, jclass, jint a, jshort b, jshort c, jbyte d, jbyte e, jbyte f, jbyte g, jbyte h, jbyte i, jbyte j, jbyte k)
    { 
        GUID guid{ std::bit_cast<unsigned long>(a), std::bit_cast<unsigned short>(b), std::bit_cast<unsigned short>(c), std::bit_cast<unsigned char>(d), std::bit_cast<unsigned char>(e), std::bit_cast<unsigned char>(f), std::bit_cast<unsigned char>(g), std::bit_cast<unsigned char>(h), std::bit_cast<unsigned char>(i), std::bit_cast<unsigned char>(j), std::bit_cast<unsigned char>(k) };
        wchar_t buffer[128]{};
        auto length = StringFromGUID2(guid, buffer, sizeof(buffer)/sizeof(wchar_t));
        if (!length)
        {
            return nullptr;
        }
        auto result = jniEnv->NewString((const jchar*)buffer, length-1);
        return result;
    }

    /*
     * Class:     com_harlinn_common_platform_Ole32
     * Method:    IIDFromString
     * Signature: (Ljava/lang/String;)[B
     */
    JNIEXPORT jbyteArray JNICALL Java_com_harlinn_common_platform_Ole32_IIDFromString(JNIEnv* jniEnv, jclass, jstring s)
    {
        if (!s)
        {
            return nullptr;
        }
        auto wstr = ToStdWString(jniEnv, s);
        GUID guid{};
        auto rc = IIDFromString(wstr.c_str(), &guid);
        if (FAILED(rc))
        {
            auto str = ToStdString(jniEnv, s);
            auto message = std::format("Unable to convert {} to valid GUID.", str);
            ThrowIllegalArgumentException(jniEnv, message);
            return nullptr;
        }
        else
        {
            auto result = ToByteArray(jniEnv, guid);
            return result;
        }
    }
}
