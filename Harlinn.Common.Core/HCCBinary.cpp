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

#include <pch.h>
#include <HCCBinary.h>
#include <HCCString.h>

namespace Harlinn::Common::Core
{
    namespace Internal
    {

        void ThrowFixedBinaryArgumentToLong( size_t size, size_t maxSize )
        {
            auto message = Format( L"Argument buffer is to long:{}, maximum length is {}.", size, maxSize );
            Exception exc( message );
            throw exc;
        }
    }
}