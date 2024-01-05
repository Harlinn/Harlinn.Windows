#pragma once
#ifndef HARLINN_MEDIA_GLIB_HWMGASYNQUEUE_H_
#define HARLINN_MEDIA_GLIB_HWMGASYNQUEUE_H_
/*
   Copyright 2024 Espen Harlinn

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

#include "HWMgtypes.h"

namespace Harlinn::Media::GLib
{
    class AsyncQueue;
    
    HWM_EXPORT AsyncQueue* AsyncQueueNew( );
    HWM_EXPORT AsyncQueue* AsyncQueueNewFull( DestroyNotify itemFreeFunc );
    HWM_EXPORT void AsyncQueueLock( AsyncQueue* queue );
    HWM_EXPORT void AsyncQueueUnlock( AsyncQueue* queue );
    HWM_EXPORT AsyncQueue* AsyncQueueRef( AsyncQueue* queue );
    HWM_EXPORT void AsyncQueueUnref( AsyncQueue* queue );
    HWM_EXPORT void AsyncQueuePush( AsyncQueue* queue, Pointer data );
    HWM_EXPORT void AsyncQueuePushUnlocked( AsyncQueue* queue, Pointer data );
    HWM_EXPORT void AsyncQueuePushSorted( AsyncQueue* queue, Pointer data, CompareDataFunc func, Pointer userData );
    HWM_EXPORT void AsyncQueuePushSortedUnlocked( AsyncQueue* queue, Pointer data, CompareDataFunc func, Pointer userData );
    HWM_EXPORT Pointer AsyncQueuePop( AsyncQueue* queue );
    HWM_EXPORT Pointer AsyncQueuePopUnlocked( AsyncQueue* queue );
    HWM_EXPORT Pointer AsyncQueueTryPop( AsyncQueue* queue );
    HWM_EXPORT Pointer AsyncQueueTryPopUnlocked( AsyncQueue* queue );
    HWM_EXPORT Pointer AsyncQueueTimeoutPop( AsyncQueue* queue, UInt64 timeout );
    HWM_EXPORT Pointer AsyncQueueTimeoutPopUnlocked( AsyncQueue* queue, UInt64 timeout );
    HWM_EXPORT Int32 AsyncQueueLength( AsyncQueue* queue );
    HWM_EXPORT Int32 AsyncQueueLengthUnlocked( AsyncQueue* queue );
    HWM_EXPORT void AsyncQueueSort( AsyncQueue* queue, CompareDataFunc func, Pointer userData );
    HWM_EXPORT void AsyncQueueSortUnlocked( AsyncQueue* queue, CompareDataFunc func, Pointer userData );
    HWM_EXPORT Bool32 AsyncQueueRemove( AsyncQueue* queue, Pointer item );
    HWM_EXPORT Bool32 AsyncQueueRemoveUnlocked( AsyncQueue* queue, Pointer item );
    HWM_EXPORT void AsyncQueuePushFront( AsyncQueue* queue, Pointer item );
    HWM_EXPORT void AsyncQueuePushFrontUnlocked( AsyncQueue* queue, Pointer item );

}

#endif
