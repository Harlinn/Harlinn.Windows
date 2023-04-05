#pragma once
#ifndef __HCCLINKEDLIST_H__
#define __HCCLINKEDLIST_H__

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
