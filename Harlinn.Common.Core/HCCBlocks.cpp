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

#include "pch.h"
#include <HCCBlocks.h>
#include <HCCMemory.h>

namespace Harlinn::Common::Core::IO::Blocks
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
