#pragma once
#ifndef __HCCLOGGING_H__
#define __HCCLOGGING_H__
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

#define HCC_COMMON_CORE_NLOGGING 1

#include <HCCException.h>

#if defined (HCC_COMMON_CORE_NLOGGING)

#if !defined (HCC_INTERNAL_VERBOSE)
#define HCC_INTERNAL_VERBOSE(fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_DEBUG)
#define HCC_INTERNAL_DEBUG(fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_INFO)
#define HCC_INTERNAL_INFO(fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_NOTICE)
#define HCC_INTERNAL_NOTICE(fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_WARNING)
#define HCC_INTERNAL_WARNING(fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_ERROR)
#define HCC_INTERNAL_ERROR(fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_CRITICAL)
#define HCC_INTERNAL_CRITICAL(fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_ALERT)
#define HCC_INTERNAL_ALERT(fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_EMERGENCY)
#define HCC_INTERNAL_EMERGENCY(fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_TRACE)
# define HCC_INTERNAL_TRACE(fmt,...) do {} while (0)
#endif

#if !defined (HCC_INTERNAL_VERBOSE_EX)
#define HCC_INTERNAL_VERBOSE_EX(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_DEBUG_EX)
#define HCC_INTERNAL_DEBUG_EX(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_INFO_EX)
#define HCC_INTERNAL_INFO_EX(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_NOTICE_EX)
#define HCC_INTERNAL_NOTICE_EX(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_WARNING_EX)
#define HCC_INTERNAL_WARNING_EX(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_ERROR_EX)
#define HCC_INTERNAL_ERROR_EX(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_CRITICAL_EX)
#define HCC_INTERNAL_CRITICAL_EX(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_ALERT_EX)
#define HCC_INTERNAL_ALERT_EX(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_EMERGENCY_EX)
#define HCC_INTERNAL_EMERGENCY_EX(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_TRACE_EX)
# define HCC_INTERNAL_TRACE_EX(logger, fmt,...) do {} while (0)
#endif



#if !defined (HCC_INTERNAL_THROW)
#define HCC_INTERNAL_THROW( ExceptionType, ...  ) do { throw ExceptionType ( __VA_ARGS__ );  } while(0)
#endif

#else



#endif // !HCC_COMMON_CORE_NLOGGING


#ifdef _DEBUG
#ifndef HCC_VERBOSE
#define HCC_VERBOSE( fmt, ... ) HCC_INTERNAL_VERBOSE( fmt, __VA_ARGS__ )
#endif
#ifndef HCC_VERBOSE_EX
#define HCC_VERBOSE_EX( loggerExpr, fmt, ... ) HCC_INTERNAL_VERBOSE_EX( loggerExpr, fmt, __VA_ARGS__ )
#endif
#else
#ifndef HCC_VERBOSE
#define HCC_VERBOSE( fmt, ... )  \
  __pragma( warning(push) ) \
  __pragma( warning(disable:4127) ) \
  do {} while (0) \
  __pragma( warning(pop) )
#endif
#ifndef HCC_VERBOSE_EX
#define HCC_VERBOSE_EX( loggerExpr, fmt, ... )  \
  __pragma( warning(push) ) \
  __pragma( warning(disable:4127) ) \
  do {} while (0) \
  __pragma( warning(pop) )
#endif
#endif

#ifdef _DEBUG
#ifndef HCC_DEBUG
#define HCC_DEBUG( fmt, ... ) HCC_INTERNAL_DEBUG( fmt, __VA_ARGS__ )
#endif
#ifndef HCC_DEBUG_EX
#define HCC_DEBUG_EX( loggerExpr, fmt, ... ) HCC_INTERNAL_DEBUG_EX( loggerExpr, fmt, __VA_ARGS__ )
#endif
#else
#ifndef HCC_DEBUG
#define HCC_DEBUG( fmt, ... )  \
  __pragma( warning(push) ) \
  __pragma( warning(disable:4127) ) \
  do {} while (0) \
  __pragma( warning(pop) )
#endif
#ifndef HCC_DEBUG_EX
#define HCC_DEBUG_EX( loggerExpr, fmt, ... )  \
  __pragma( warning(push) ) \
  __pragma( warning(disable:4127) ) \
  do {} while (0) \
  __pragma( warning(pop) )
#endif
#endif

#ifndef HCC_INFO
#define HCC_INFO( fmt, ... ) HCC_INTERNAL_INFO( fmt, __VA_ARGS__ )
#endif

#ifndef HCC_INFO_EX
#define HCC_INFO_EX( loggerExpr, fmt, ... ) HCC_INTERNAL_INFO_EX( loggerExpr, fmt, __VA_ARGS__ )
#endif

#ifndef HCC_NOTICE
#define HCC_NOTICE( fmt, ... ) HCC_INTERNAL_NOTICE( fmt, __VA_ARGS__ )
#endif

#ifndef HCC_NOTICE_EX
#define HCC_NOTICE_EX( loggerExpr, fmt, ... ) HCC_INTERNAL_NOTICE_EX( loggerExpr, fmt, __VA_ARGS__ )
#endif

#ifndef HCC_WARNING
#define HCC_WARNING( fmt, ... ) HCC_INTERNAL_WARNING( fmt, __VA_ARGS__ )
#endif

#ifndef HCC_WARNING_EX
#define HCC_WARNING_EX( loggerExpr, fmt, ... ) HCC_INTERNAL_WARNING_EX( loggerExpr, fmt, __VA_ARGS__ )
#endif

#ifndef HCC_ERROR
#define HCC_ERROR( fmt, ... ) HCC_INTERNAL_ERROR( fmt, __VA_ARGS__ )
#endif

#ifndef HCC_ERROR_EX
#define HCC_ERROR_EX( loggerExpr, fmt, ... ) HCC_INTERNAL_ERROR_EX( loggerExpr, fmt, __VA_ARGS__ )
#endif

#ifndef HCC_CRITICAL
#define HCC_CRITICAL( fmt, ... ) HCC_INTERNAL_CRITICAL( fmt, __VA_ARGS__ )
#endif

#ifndef HCC_CRITICAL_EX
#define HCC_CRITICAL_EX( loggerExpr, fmt, ... ) HCC_INTERNAL_CRITICAL( loggerExpr, fmt, __VA_ARGS__ )
#endif

#ifndef HCC_ALERT
#define HCC_ALERT( fmt, ... ) HCC_INTERNAL_ALERT( fmt, __VA_ARGS__ )
#endif

#ifndef HCC_ALERT_EX
#define HCC_ALERT_EX( loggerExpr, fmt, ... ) HCC_INTERNAL_ALERT_EX( loggerExpr, fmt, __VA_ARGS__ )
#endif

#ifndef HCC_EMERGENCY
#define HCC_EMERGENCY( fmt, ... ) HCC_INTERNAL_EMERGENCY( fmt, __VA_ARGS__ )
#endif

#ifndef HCC_EMERGENCY_EX
#define HCC_EMERGENCY_EX( loggerExpr, fmt, ... ) HCC_INTERNAL_EMERGENCY_EX( loggerExpr, fmt, __VA_ARGS__ )
#endif


#ifdef _DEBUG
#ifndef HCC_TRACE
#define HCC_TRACE( fmt,...) HCC_INTERNAL_TRACE( fmt, __VA_ARGS__)
#endif

#ifndef HCC_TRACE_EX
#define HCC_TRACE_EX( loggerExpr, fmt,...) HCC_INTERNAL_TRACE_EX( loggerExpr, fmt, __VA_ARGS__)
#endif

#else
#ifndef HCC_TRACE 
#define HCC_TRACE( fmt,... ) \
  __pragma( warning(push) ) \
  __pragma( warning(disable:4127) ) \
  do {} while (0) \
  __pragma( warning(pop) )
#endif
#ifndef HCC_TRACE_EX 
#define HCC_TRACE_EX( loggerExpr, fmt,... ) \
  __pragma( warning(push) ) \
  __pragma( warning(disable:4127) ) \
  do {} while (0) \
  __pragma( warning(pop) )
#endif
#endif

#ifndef HCC_THROW
#define HCC_THROW( ExceptionType, ... ) HCC_INTERNAL_THROW( ExceptionType, __VA_ARGS__ )
#endif

#endif
