
#include "config.h"

#include "effectslot.h"

#include <stddef.h>

#include "alcontext.h"
#include "almalloc.h"


EffectSlotArray *EffectSlot::CreatePtrArray(size_t count) noexcept
{
    /* Allocate space for twice as many pointers, so the mixer has scratch
     * space to store a sorted list during mixing.
     */
    void *ptr{al_calloc(alignof(EffectSlotArray), EffectSlotArray::Sizeof(count*2))};
    return new(ptr) EffectSlotArray{count};
}

EffectSlot::~EffectSlot()
{
    if(mWetBuffer)
        mWetBuffer->mInUse = false;
}
