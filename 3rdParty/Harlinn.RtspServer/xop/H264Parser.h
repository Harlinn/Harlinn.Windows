#ifndef XOP_H264_PARSER_H
#define XOP_H264_PARSER_H

#include <xop/RtspServerDef.h>

#include <cstdint> 
#include <utility> 

namespace xop
{

typedef std::pair<uint8_t*, uint8_t*> Nal; // <nal begin, nal end>

class H264Parser
{
public:    
    HW_RTSPSERVER_EXPORT static Nal findNal(const uint8_t *data, uint32_t size);
        
private:
  
};
    
}

#endif 

