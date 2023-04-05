// PHZ
// 2018-5-15

#ifndef XOP_TIMESTAMP_H
#define XOP_TIMESTAMP_H

#include <Xop/RtspServerDef.h>

#include <string>
#include <functional>
#include <cstdint>
#include <chrono>
#include <thread>

namespace xop
{
    
class Timestamp
{
public:
    Timestamp()
        : begin_time_point_(std::chrono::high_resolution_clock::now())
    { }

    void Reset()
    {
        begin_time_point_ = std::chrono::high_resolution_clock::now();
    }

    int64_t Elapsed()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point_).count();
    }

    HW_RTSPSERVER_EXPORT static std::string Localtime();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> begin_time_point_;
};

}

#endif
