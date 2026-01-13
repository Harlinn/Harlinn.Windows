#pragma once
#ifndef __HCCLINKEDLIST_H__
#define __HCCLINKEDLIST_H__
/*
   Copyright 2024-2026 Espen Harlinn

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

#include <HCCDef.h>

namespace Harlinn::Common::Core
{
    class InterlockedLinkedList
    {
        SLIST_HEADER header_;
    public:
        using Entry = SLIST_ENTRY;

        InterlockedLinkedList( )
        {
            InitializeSListHead( &header_ );
        }

        // The return value is the previous first item in the list. 
        // If the list was previously empty, the return value is nullptr
        Entry* Push( Entry* entry )
        {
            return InterlockedPushEntrySList( &header_, entry );
        }

        Entry* Pop( )
        {
            return InterlockedPopEntrySList( &header_ );
        }

        Entry* Flush( )
        {
            return InterlockedFlushSList( &header_ );
        }



    };
}


#endif
