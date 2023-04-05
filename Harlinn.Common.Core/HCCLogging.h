#pragma once
#ifndef __HCCLOGGING_H__
#define __HCCLOGGING_H__

//#define HCC_COMMON_CORE_NLOGGING 1

#ifndef HCC_COMMON_CORE_NLOGGING
#include <HCCLogger.h>
#endif

#include <HCCException.h>


#if defined (HCC_COMMON_CORE_NLOGGING)
#if !defined (HCC_INTERNAL_DEBUG)
#define HCC_INTERNAL_DEBUG(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_INFO)
#define HCC_INTERNAL_INFO(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_NOTICE)
#define HCC_INTERNAL_NOTICE(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_WARNING)
#define HCC_INTERNAL_WARNING(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_ERROR)
#define HCC_INTERNAL_ERROR(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_CRITICAL)
#define HCC_INTERNAL_CRITICAL(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_ALERT)
#define HCC_INTERNAL_ALERT(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_EMERGENCY)
#define HCC_INTERNAL_EMERGENCY(logger, fmt,...) do {} while (0)
#endif
#if !defined (HCC_INTERNAL_TRACE)
# define HCC_INTERNAL_TRACE(logger, fmt,...) do {} while (0)
#endif


#if !defined (HCC_INTERNAL_THROW)
#define HCC_INTERNAL_THROW( ExceptionType, ...  ) do { throw ExceptionType ( __VA_ARGS__ );  } while(0)
#endif

#else


#if !defined (HCC_INTERNAL_DEBUG)
#define HCC_INTERNAL_DEBUG(loggerExpr, fmt, ...) \
do \
{ \
    auto& logger = (loggerExpr);\
    if( (logger).IsDebugEnabled( ) ) \
    { \
        bool isFixedSize = Harlinn::Common::Core::Persistent::IsFixedSize( __VA_ARGS__ ); \
        size_t fixedSize = isFixedSize ? Harlinn::Common::Core::Persistent::BufferSize( __VA_ARGS__ ) : 0; \
        auto argDescriptor = Harlinn::Common::Core::Persistent::Descriptor( __VA_ARGS__ ); \
        static const Harlinn::Common::Core::Logging::LogSite logSite(Harlinn::Common::Core::Logging::Level::Debug, fmt, reinterpret_cast<const Byte*>(&argDescriptor), sizeof(argDescriptor), isFixedSize, fixedSize, __LINE__, 0, __FILE__, __FUNCTION__); \
        (logger).Debug(&logSite, __VA_ARGS__ ); \
    } \
} while (0)
#endif
#if !defined (HCC_INTERNAL_INFO)
#define HCC_INTERNAL_INFO(loggerExpr, fmt,...) \
do \
{ \
    auto& logger = (loggerExpr);\
    if( logger.IsInfoEnabled( ) ) \
    { \
        bool isFixedSize = Harlinn::Common::Core::Persistent::IsFixedSize( __VA_ARGS__ ); \
        size_t fixedSize = isFixedSize ? Harlinn::Common::Core::Persistent::BufferSize( __VA_ARGS__ ) : 0; \
        auto argDescriptor = Harlinn::Common::Core::Persistent::Descriptor( __VA_ARGS__ ); \
        static const Harlinn::Common::Core::Logging::LogSite logSite(Harlinn::Common::Core::Logging::Level::Info, fmt, reinterpret_cast<const Byte*>(&argDescriptor), sizeof(argDescriptor), isFixedSize, fixedSize, __LINE__, 0, __FILE__, __FUNCTION__); \
        logger.Info(&logSite, __VA_ARGS__ ); \
    } \
} while (0)
#endif
#if !defined (HCC_INTERNAL_NOTICE)
#define HCC_INTERNAL_NOTICE(loggerExpr, fmt,...) \
do \
{ \
    auto& logger = (loggerExpr);\
    if( logger.IsNoticeEnabled( ) ) \
    { \
        bool isFixedSize = Harlinn::Common::Core::Persistent::IsFixedSize( __VA_ARGS__ ); \
        size_t fixedSize = isFixedSize ? Harlinn::Common::Core::Persistent::BufferSize( __VA_ARGS__ ) : 0; \
        auto argDescriptor = Harlinn::Common::Core::Persistent::Descriptor( __VA_ARGS__ ); \
        static const Harlinn::Common::Core::Logging::LogSite logSite(Harlinn::Common::Core::Logging::Level::Notice, fmt, reinterpret_cast<const Byte*>(&argDescriptor), sizeof(argDescriptor), isFixedSize, fixedSize, __LINE__, 0, __FILE__, __FUNCTION__); \
        logger.Notice(&logSite, __VA_ARGS__ ); \
    } \
} while (0)
#endif
#if !defined (HCC_INTERNAL_WARNING)
#define HCC_INTERNAL_WARNING(loggerExpr, fmt,...) \
do \
{ \
    auto& logger = (loggerExpr);\
    if( logger.IsWarningEnabled( ) ) \
    { \
        bool isFixedSize = Harlinn::Common::Core::Persistent::IsFixedSize( __VA_ARGS__ ); \
        size_t fixedSize = isFixedSize ? Harlinn::Common::Core::Persistent::BufferSize( __VA_ARGS__ ) : 0; \
        auto argDescriptor = Harlinn::Common::Core::Persistent::Descriptor( __VA_ARGS__ ); \
        static const Harlinn::Common::Core::Logging::LogSite logSite(Harlinn::Common::Core::Logging::Level::Warning, fmt, reinterpret_cast<const Byte*>(&argDescriptor), sizeof(argDescriptor), isFixedSize, fixedSize, __LINE__, 0, __FILE__, __FUNCTION__); \
        logger.Warning(&logSite, __VA_ARGS__ ); \
    } \
} while (0)
#endif
#if !defined (HCC_INTERNAL_ERROR)
#define HCC_INTERNAL_ERROR(loggerExpr, fmt,...) \
do \
{ \
    auto& logger = (loggerExpr);\
    if( logger.IsErrorEnabled( ) ) \
    { \
        bool isFixedSize = Harlinn::Common::Core::Persistent::IsFixedSize( __VA_ARGS__ ); \
        size_t fixedSize = isFixedSize ? Harlinn::Common::Core::Persistent::BufferSize( __VA_ARGS__ ) : 0; \
        auto argDescriptor = Harlinn::Common::Core::Persistent::Descriptor( __VA_ARGS__ ); \
        static const Harlinn::Common::Core::Logging::LogSite logSite(Harlinn::Common::Core::Logging::Level::Error, fmt, reinterpret_cast<const Byte*>(&argDescriptor), sizeof(argDescriptor), isFixedSize, fixedSize, __LINE__, 0, __FILE__, __FUNCTION__); \
        logger.Error(&logSite, __VA_ARGS__ ); \
    } \
} while (0)
#endif
#if !defined (HCC_INTERNAL_CRITICAL)
#define HCC_INTERNAL_CRITICAL(loggerExpr, fmt,...) \
do \
{ \
    auto& logger = (loggerExpr);\
    if( logger.IsCriticalEnabled( ) ) \
    { \
        bool isFixedSize = Harlinn::Common::Core::Persistent::IsFixedSize( __VA_ARGS__ ); \
        size_t fixedSize = isFixedSize ? Harlinn::Common::Core::Persistent::BufferSize( __VA_ARGS__ ) : 0; \
        auto argDescriptor = Harlinn::Common::Core::Persistent::Descriptor( __VA_ARGS__ ); \
        static const Harlinn::Common::Core::Logging::LogSite logSite(Harlinn::Common::Core::Logging::Level::Critical, fmt, reinterpret_cast<const Byte*>(&argDescriptor), sizeof(argDescriptor), isFixedSize, fixedSize, __LINE__, 0, __FILE__, __FUNCTION__); \
        logger.Critical(&logSite, __VA_ARGS__ ); \
    } \
} while (0)
#endif
#if !defined (HCC_INTERNAL_ALERT)
#define HCC_INTERNAL_ALERT(loggerExpr, fmt,...) \
do \
{ \
    auto& logger = (loggerExpr);\
    if( logger.IsAlertEnabled( ) ) \
    { \
        bool isFixedSize = Harlinn::Common::Core::Persistent::IsFixedSize( __VA_ARGS__ ); \
        size_t fixedSize = isFixedSize ? Harlinn::Common::Core::Persistent::BufferSize( __VA_ARGS__ ) : 0; \
        auto argDescriptor = Harlinn::Common::Core::Persistent::Descriptor( __VA_ARGS__ ); \
        static const Harlinn::Common::Core::Logging::LogSite logSite(Harlinn::Common::Core::Logging::Level::Alert, fmt, reinterpret_cast<const Byte*>(&argDescriptor), sizeof(argDescriptor), isFixedSize, fixedSize, __LINE__, 0, __FILE__, __FUNCTION__); \
        logger.Alert(&logSite, __VA_ARGS__ ); \
    } \
} while (0)
#endif
#if !defined (HCC_INTERNAL_EMERGENCY)
#define HCC_INTERNAL_EMERGENCY(loggerExpr, fmt,...) \
do \
{ \
    auto& logger = (loggerExpr);\
    if( logger.IsEmergencyEnabled( ) ) \
    { \
        bool isFixedSize = Harlinn::Common::Core::Persistent::IsFixedSize( __VA_ARGS__ ); \
        size_t fixedSize = isFixedSize ? Harlinn::Common::Core::Persistent::BufferSize( __VA_ARGS__ ) : 0; \
        auto argDescriptor = Harlinn::Common::Core::Persistent::Descriptor( __VA_ARGS__ ); \
        static const Harlinn::Common::Core::Logging::LogSite logSite(Harlinn::Common::Core::Logging::Level::Emergency, fmt, reinterpret_cast<const Byte*>(&argDescriptor), sizeof(argDescriptor), isFixedSize, fixedSize, __LINE__, 0, __FILE__, __FUNCTION__); \
        logger.Emergency(&logSite, __VA_ARGS__ ); \
    } \
} while (0)
#endif
#if !defined (HCC_INTERNAL_TRACE)
# define HCC_INTERNAL_TRACE(loggerExpr, fmt,...) \
do \
{ \
    auto& logger = (loggerExpr);\
    if( logger.IsTraceEnabled( ) ) \
    { \
        bool isFixedSize = Harlinn::Common::Core::Persistent::IsFixedSize( __VA_ARGS__ ); \
        size_t fixedSize = isFixedSize ? Harlinn::Common::Core::Persistent::BufferSize( __VA_ARGS__ ) : 0; \
        auto argDescriptor = Harlinn::Common::Core::Persistent::Descriptor( __VA_ARGS__ ); \
        static const Harlinn::Common::Core::Logging::LogSite logSite(Harlinn::Common::Core::Logging::Level::Trace, fmt, reinterpret_cast<const Byte*>(&argDescriptor), sizeof(argDescriptor), isFixedSize, fixedSize, __LINE__, 0, __FILE__, __FUNCTION__); \
        logger.Trace(&logSite, __VA_ARGS__ ); \
    } \
} while (0)
#endif


#if !defined (HCC_INTERNAL_THROW)
#define HCC_INTERNAL_THROW( ExceptionType, ...  ) do { throw ExceptionType ( __VA_ARGS__ );  } while(0)
#endif

#endif // !HCC_NLOGGING


#ifdef _DEBUG
#ifndef HCC_DEBUG
#define HCC_DEBUG( logger, fmt, ... ) HCC_INTERNAL_DEBUG( logger, fmt, __VA_ARGS__ )
#endif
#else
#ifndef HCC_DEBUG
#define HCC_DEBUG( logger, fmt, ... )  \
  __pragma( warning(push) ) \
  __pragma( warning(disable:4127) ) \
  do {} while (0) \
  __pragma( warning(pop) )
#endif
#endif

#ifndef HCC_INFO
#define HCC_INFO( logger, fmt, ... ) HCC_INTERNAL_INFO( logger, fmt, __VA_ARGS__ )
#endif

#ifndef HCC_NOTICE
#define HCC_NOTICE( logger, fmt, ... ) HCC_INTERNAL_NOTICE( logger, fmt, __VA_ARGS__ )
#endif

#ifndef HCC_WARNING
#define HCC_WARNING( logger, fmt, ... ) HCC_INTERNAL_WARNING( logger, fmt, __VA_ARGS__ )
#endif

#ifndef HCC_ERROR
#define HCC_ERROR( logger, fmt, ... ) HCC_INTERNAL_ERROR( logger, fmt, __VA_ARGS__ )
#endif

#ifndef HCC_CRITICAL
#define HCC_CRITICAL( logger, fmt, ... ) HCC_INTERNAL_CRITICAL( logger, fmt, __VA_ARGS__ )
#endif

#ifndef HCC_ALERT
#define HCC_ALERT( logger, fmt, ... ) HCC_INTERNAL_ALERT( logger, fmt, __VA_ARGS__ )
#endif

#ifndef HCC_EMERGENCY
#define HCC_EMERGENCY( logger, fmt, ... ) HCC_INTERNAL_EMERGENCY( logger, fmt, __VA_ARGS__ )
#endif

#ifdef _DEBUG
#ifndef HCC_TRACE
#define HCC_TRACE( logger, fmt,...) HCC_INTERNAL_TRACE( logger, fmt, __VA_ARGS__)
#endif
#else
#ifndef HCC_TRACE 
#define HCC_TRACE( logger, fmt,... ) \
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
