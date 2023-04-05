#include "pch.h"
#include <HCCBlocks.h>
#include <HCCMemory.h>

namespace Harlinn::Common::Core::Blocks
{
    namespace
    {
        FixedSizeMemoryManager<BlockSize, CacheSize> memoryManager;
    }

    Block* Block::Allocate( )
    {
        auto* result = (Block*)memoryManager.Malloc( );
        result->next_ = nullptr;
        result->previous_ = nullptr;
        return result;
    }

    Block* Block::Allocate( Block* previous )
    {
        auto* result = (Block*)memoryManager.Malloc( );
        result->next_ = nullptr;
        result->previous_ = previous;
        previous->next_ = result;
        return result;
    }

    Block* Block::Allocate( Block* next, Block* previous )
    {
        auto* result = (Block*)memoryManager.Malloc( );
        next->previous_ = result;
        result->next_ = next;
        result->previous_ = previous;
        previous->next_ = result;
        return result;
    }


    void Block::Free( Block* block )
    {
        memoryManager.Free( block );
    }




}
