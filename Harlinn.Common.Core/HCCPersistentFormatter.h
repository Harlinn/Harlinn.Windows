#pragma once
#ifndef HARLINN_COMMON_CORE_HCCPERSISTENTFORMATTER_H_
#define HARLINN_COMMON_CORE_HCCPERSISTENTFORMATTER_H_

#include <HCCPersistent.h>
#include <HCCIO.h>

namespace Harlinn::Common::Core::Persistent
{
    HCC_EXPORT bool FormatTo( const char* formatString, size_t formatStringLength, const Byte* argumentDescriptor, const Byte* arguments, size_t argumentsSize, IO::MemoryStream& destination );


}

#endif
