#pragma once
#ifndef PBRTO_UTIL_NEWLOG_H_
#define PBRTO_UTIL_NEWLOG_H_

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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/NewPbrt.h>

#include <string>
#include <vector>

namespace pbrto
{

    // LogLevel Definition
    enum class LogLevel { Verbose, Error, Fatal, Invalid };

    PBRTO_EXPORT
        std::string ToString( LogLevel level );
    PBRTO_EXPORT
        LogLevel LogLevelFromString( const std::string& s );

    void ShutdownLogging( );
    void InitLogging( LogLevel level, std::string logFile, bool logUtilization, bool useGPU );

#ifdef PBRT_BUILD_GPU_RENDERER

    struct GPULogItem
    {
        LogLevel level;
        char file[ 64 ];
        int line;
        char message[ 128 ];
    };

    std::vector<GPULogItem> ReadGPULogs( );

#endif

    // LogLevel Global Variable Declaration
    namespace logging
    {
        PBRTO_EXPORT
            extern LogLevel logLevel;
        PBRTO_EXPORT
            extern FILE* logFile;
    }  // namespace logging

    // Logging Function Declarations
    PBRT_CPU_GPU
        PBRTO_EXPORT
        void Log( LogLevel level, const char* file, int line, const char* s );


    PBRT_CPU_GPU [[noreturn]] void PBRTO_EXPORT LogFatal( LogLevel level, const char* file, int line,
        const char* s );

    template <typename... Args>
    PBRT_CPU_GPU inline void Log( LogLevel level, const char* file, int line, const char* fmt,
        Args &&...args );

    template <typename... Args>
    PBRT_CPU_GPU [[noreturn]] inline void LogFatal( LogLevel level, const char* file, int line,
        const char* fmt, Args &&...args );

#define NTO_STRING(x) NTO_STRING2(x)
#define NTO_STRING2(x) #x

#ifdef PBRT_IS_GPU_CODE

    extern __constant__ LogLevel LOGGING_LogLevelGPU;

#define NLOG_VERBOSE(...)                               \
    (pbrto::LogLevel::Verbose >= LOGGING_LogLevelGPU && \
     (pbrto::Log(LogLevel::Verbose, __FILE__, __LINE__, __VA_ARGS__), true))

#define NLOG_ERROR(...)                               \
    (pbrto::LogLevel::Error >= LOGGING_LogLevelGPU && \
     (pbrto::Log(LogLevel::Error, __FILE__, __LINE__, __VA_ARGS__), true))

#define NLOG_FATAL(...) \
    pbrto::LogFatal(pbrto::LogLevel::Fatal, __FILE__, __LINE__, __VA_ARGS__)

#else

    // Logging Macros
#define NLOG_VERBOSE(...)                             \
    (pbrto::LogLevel::Verbose >= logging::logLevel && \
     (pbrto::Log(LogLevel::Verbose, __FILE__, __LINE__, __VA_ARGS__), true))

#define NLOG_ERROR(...)                                   \
    (pbrto::LogLevel::Error >= pbrto::logging::logLevel && \
     (pbrto::Log(LogLevel::Error, __FILE__, __LINE__, __VA_ARGS__), true))

#define NLOG_FATAL(...) \
    pbrto::LogFatal(pbrto::LogLevel::Fatal, __FILE__, __LINE__, __VA_ARGS__)

#endif

}  // namespace pbrt

#include <pbrto/util/NewPrint.h>

namespace pbrto
{

    template <typename... Args>
    inline void Log( LogLevel level, const char* file, int line, const char* fmt,
        Args &&...args )
    {
#ifdef PBRT_IS_GPU_CODE
        Log( level, file, line, fmt );  // just the format string #yolo
#else
        std::string s = StringPrintf( fmt, std::forward<Args>( args )... );
        Log( level, file, line, s.c_str( ) );
#endif
    }

    template <typename... Args>
    inline void LogFatal( LogLevel level, const char* file, int line, const char* fmt,
        Args &&...args )
    {
#ifdef PBRT_IS_GPU_CODE
        LogFatal( level, file, line, fmt );  // just the format string #yolo
#else
        std::string s = StringPrintf( fmt, std::forward<Args>( args )... );
        LogFatal( level, file, line, s.c_str( ) );
#endif
    }

}

#endif
