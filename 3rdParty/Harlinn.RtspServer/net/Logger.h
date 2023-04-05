// PHZ
// 2020-5-15

#ifndef XOP_LOGGER_H
#define XOP_LOGGER_H

#include <xop/RtspServerDef.h>

#include <string>
#include <mutex>
#include <thread>
#include <fstream>
#include <cstring>
#include <iostream>
#include <sstream>

namespace xop {


enum Priority 
{
    LOG_DEBUG, LOG_STATE, LOG_INFO, LOG_WARNING, LOG_ERROR,
};	
	
class Logger
{
public:
	Logger &operator=(const Logger &) = delete;
	Logger(const Logger &) = delete;	
	HW_RTSPSERVER_EXPORT static Logger& Instance();
	HW_RTSPSERVER_EXPORT ~Logger();

	HW_RTSPSERVER_EXPORT void Init(char *pathname = nullptr);
	HW_RTSPSERVER_EXPORT void Exit();

	HW_RTSPSERVER_EXPORT void Log(Priority priority, const char* __file, const char* __func, int __line, const char *fmt, ...);
	HW_RTSPSERVER_EXPORT void Log2(Priority priority, const char *fmt, ...);

private:
	HW_RTSPSERVER_EXPORT void Write(std::string buf);
	HW_RTSPSERVER_EXPORT Logger();

	std::mutex mutex_;
	std::ofstream ofs_;
};
 
}

#ifdef _DEBUG
#define LOG_DEBUG(fmt, ...) xop::Logger::Instance().Log(LOG_DEBUG, __FILE__, __FUNCTION__,__LINE__, fmt, ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...)
#endif
#define LOG_INFO(fmt, ...) xop::Logger::Instance().Log2(LOG_INFO, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) xop::Logger::Instance().Log(LOG_ERROR, __FILE__, __FUNCTION__,__LINE__, fmt, ##__VA_ARGS__)

#endif

