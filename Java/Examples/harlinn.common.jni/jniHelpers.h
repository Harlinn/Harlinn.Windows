#pragma once
#ifndef JNIHELPERS_H_
#define JNIHELPERS_H_

#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <format>

namespace Signatures
{
	constexpr char IllegalArgumentException[] = "java/lang/IllegalArgumentException";

}

inline jstring ToJString(JNIEnv* jniEnv, const wchar_t* text, size_t textLength) noexcept
{
	return jniEnv->NewString(reinterpret_cast<const jchar*>(text), static_cast<jsize>(textLength));
}

inline jstring ToJString(JNIEnv* jniEnv, const wchar_t* text) noexcept
{
	if (text)
	{
		return ToJString(jniEnv, text, wcslen(text));
	}
	return nullptr;
}

inline jstring ToJString(JNIEnv* jniEnv, const char* text) noexcept
{
	return jniEnv->NewStringUTF(text);
}

inline jstring ToJString(JNIEnv* jniEnv, const std::wstring& text) noexcept
{
	return jniEnv->NewString(reinterpret_cast<const jchar*>(text.c_str()), static_cast<jsize>(text.length()));
}

inline jstring ToJString(JNIEnv* jniEnv, const std::string& text) noexcept
{
	return jniEnv->NewStringUTF(text.c_str());
}



inline jbyteArray ToByteArray(JNIEnv* jniEnv, const void* bytes, size_t numberOfBytes) noexcept
{
	auto byteArray = jniEnv->NewByteArray(static_cast<jsize>(numberOfBytes));
	if (byteArray)
	{
		jboolean isCopy;
		auto byteArrayElements = jniEnv->GetByteArrayElements(byteArray,&isCopy);
		memcpy_s(byteArrayElements, numberOfBytes, bytes, numberOfBytes);
		jniEnv->ReleaseByteArrayElements(byteArray, byteArrayElements, 0);
	}
	return byteArray;
}

template<typename T>
inline jbyteArray ToByteArray(JNIEnv* jniEnv, const T& value) noexcept
{
	return ToByteArray(jniEnv, &value, sizeof(T));
}




inline void ThrowException(JNIEnv* jniEnv, const char* exceptionSignature) noexcept
{
	auto clazz = jniEnv->FindClass(exceptionSignature);
	if (clazz)
	{
		jmethodID constructorID = jniEnv->GetMethodID(clazz, "<init>", "()V");
		if (constructorID)
		{
			jobject newExcption = jniEnv->NewObject(clazz, constructorID);
			if (newExcption)
			{
				jniEnv->Throw(reinterpret_cast<jthrowable>(newExcption));
				jniEnv->DeleteLocalRef(newExcption);
			}
		}
	}
}

inline void ThrowException(JNIEnv* jniEnv, const char* exceptionSignature, const char* text) noexcept
{
	auto clazz = jniEnv->FindClass(exceptionSignature);
	if (clazz)
	{
		jniEnv->ThrowNew(clazz, text);
	}
}

inline void ThrowIllegalArgumentException(JNIEnv* jniEnv) noexcept
{
	ThrowException(jniEnv, Signatures::IllegalArgumentException);
}

inline void ThrowIllegalArgumentException(JNIEnv* jniEnv, const char* text) noexcept
{
	ThrowException(jniEnv, Signatures::IllegalArgumentException, text);
}

inline void ThrowIllegalArgumentException(JNIEnv* jniEnv, const std::string& text) noexcept
{
	ThrowException(jniEnv, Signatures::IllegalArgumentException, text.c_str());
}


template<typename T>
inline T ToStruct(JNIEnv* jniEnv, jbyteArray byteArray) noexcept
{
	if (byteArray == nullptr)
	{
		ThrowIllegalArgumentException(jniEnv, "byteArray is null");
		return {};
	}
	auto numberOfBytes = jniEnv->GetArrayLength(byteArray);
	if (numberOfBytes != sizeof(T))
	{
		char message[256]{};
		sprintf_s(message, sizeof(message), "byteArray.length(%d) != %zu", numberOfBytes, sizeof(T));
		ThrowIllegalArgumentException(jniEnv, message);
		return {};
	}
	jboolean isCopy;
	auto byteArrayElements = jniEnv->GetByteArrayElements(byteArray, &isCopy);
	T result = *((const T*)byteArrayElements);
	jniEnv->ReleaseByteArrayElements(byteArray, byteArrayElements, 0);
	return result;
}

inline std::wstring ToStdWString(JNIEnv* jniEnv, jstring str) noexcept
{
	if (str == nullptr)
	{
		ThrowIllegalArgumentException(jniEnv, "str is null");
		return {};
	}
	size_t length = jniEnv->GetStringLength(str);
	if (length)
	{
		jboolean isCopy;
		auto stringChars = jniEnv->GetStringChars(str,&isCopy);
		if (stringChars)
		{
			std::wstring result(reinterpret_cast<const wchar_t*>(stringChars), length);
			jniEnv->ReleaseStringChars(str, stringChars);
			return result;
		}
	}
	return {};
}

inline std::string ToStdString(JNIEnv* jniEnv, jstring str) noexcept
{
	if (str == nullptr)
	{
		ThrowIllegalArgumentException(jniEnv, "str is null");
		return {};
	}
	size_t length = jniEnv->GetStringUTFLength(str);
	if (length)
	{
		jboolean isCopy;
		auto stringChars = jniEnv->GetStringUTFChars(str, &isCopy);
		if (stringChars)
		{
			std::string result(stringChars, length);
			jniEnv->ReleaseStringUTFChars(str, stringChars);
			return result;
		}
	}
	return {};
}



#endif
