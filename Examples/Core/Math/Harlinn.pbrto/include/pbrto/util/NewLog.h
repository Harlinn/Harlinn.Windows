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

}

namespace std
{
    template<typename CharT>
    struct formatter<pbrto::LogLevel, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( pbrto::LogLevel value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                switch ( value )
                {
                    case pbrto::LogLevel::Verbose:
                        return std::format_to( ctx.out( ), L"VERBOSE" );
                    case pbrto::LogLevel::Error:
                        return std::format_to( ctx.out( ), L"ERROR" );
                    case pbrto::LogLevel::Fatal:
                        return std::format_to( ctx.out( ), L"FATAL" );
                    default:
                        return std::format_to( ctx.out( ), L"UNKNOWN" );
                }

            }
            else
            {
                switch ( value )
                {
                    case pbrto::LogLevel::Verbose:
                        return std::format_to( ctx.out( ), "VERBOSE" );
                    case pbrto::LogLevel::Error:
                        return std::format_to( ctx.out( ), "ERROR" );
                    case pbrto::LogLevel::Fatal:
                        return std::format_to( ctx.out( ), "FATAL" );
                    default:
                        return std::format_to( ctx.out( ), "UNKNOWN" );
                }
            }
        }
    };
}

namespace pbrto
{

    PBRTO_EXPORT std::string ToString( LogLevel level );
    PBRTO_EXPORT LogLevel LogLevelFromString( const std::string& s );

    PBRTO_EXPORT void ShutdownLogging( );
    PBRTO_EXPORT void InitLogging( LogLevel level, std::string logFile, bool logUtilization, bool useGPU );

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
        PBRTO_EXPORT extern LogLevel logLevel;
        PBRTO_EXPORT extern FILE* logFile;
    }  // namespace logging

    // Logging Function Declarations
    PBRTO_EXPORT void Log( LogLevel level, const char* file, int line, const AnsiString& s );

    [[noreturn]]
    PBRTO_EXPORT void LogFatal( LogLevel level, const char* file, int line, const AnsiString& s );

#define TO_STRING(x) TO_STRING2(x)
#define TO_STRING2(x) #x

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


    template <typename... Args>
    inline void Log( LogLevel level, const char* file, int line, const std::format_string<Args...> fmt, Args&&... args )
    {
        auto s = FormatV( fmt.get( ), std::make_format_args( args... ) );
        Log( level, file, line, s );
    }

    template <typename... Args>
    inline void LogFatal( LogLevel level, const char* file, int line, const std::format_string<Args...> fmt, Args&&... args )
    {
        auto s = FormatV( fmt.get( ), std::make_format_args( args... ) );
        LogFatal( level, file, line, s );

    }

}

#endif
