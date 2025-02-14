#pragma once
#ifndef HARLINN_COMMON_CORE_HCCPERSISTENTFORMATTER_H_
#define HARLINN_COMMON_CORE_HCCPERSISTENTFORMATTER_H_
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

#include <HCCPersistent.h>
#include <HCCIO.h>

namespace Harlinn::Common::Core::Persistent
{
    HCC_EXPORT bool FormatTo( const char* formatString, size_t formatStringLength, const Byte* argumentDescriptor, const Byte* arguments, size_t argumentsSize, IO::MemoryStream& destination );
}

#endif
