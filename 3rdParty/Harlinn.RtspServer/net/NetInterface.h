// PHZ
// 2018-5-15

#ifndef XOP_NET_INTERFACE_H
#define XOP_NET_INTERFACE_H

#include <Xop/RtspServerDef.h>

#include <string>

namespace xop {

class NetInterface
{
public:
    HW_RTSPSERVER_EXPORT static std::string GetLocalIPAddress();
};

}

#endif
