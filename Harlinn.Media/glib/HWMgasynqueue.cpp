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
#include "pch.h"
#include "HWMgasynqueue.h"
#include <gst/gst.h>
namespace Harlinn::Media::GLib
{
    HWM_EXPORT AsyncQueue* AsyncQueueNew( )
    {
        return reinterpret_cast< AsyncQueue* >( g_async_queue_new( ) );
    }
    HWM_EXPORT AsyncQueue* AsyncQueueNewFull( DestroyNotify itemFreeFunc )
    {
        return reinterpret_cast< AsyncQueue* >( g_async_queue_new_full( itemFreeFunc ) );
    }
    HWM_EXPORT void AsyncQueueLock( AsyncQueue* queue )
    {
        g_async_queue_lock( reinterpret_cast< GAsyncQueue* >( queue ) );
    }
    HWM_EXPORT void AsyncQueueUnlock( AsyncQueue* queue )
    {
        g_async_queue_unlock( reinterpret_cast< GAsyncQueue* >( queue ) );
    }
    HWM_EXPORT AsyncQueue* AsyncQueueRef( AsyncQueue* queue )
    {
        return reinterpret_cast< AsyncQueue* >( g_async_queue_ref( reinterpret_cast< GAsyncQueue* >( queue ) ) );
    }
    HWM_EXPORT void AsyncQueueUnref( AsyncQueue* queue )
    {
        g_async_queue_unref( reinterpret_cast< GAsyncQueue* >( queue ) );
    }
    HWM_EXPORT void AsyncQueuePush( AsyncQueue* queue, Pointer data )
    {
        g_async_queue_push( reinterpret_cast< GAsyncQueue* >( queue ), data );
    }
    HWM_EXPORT void AsyncQueuePushUnlocked( AsyncQueue* queue, Pointer data )
    {
        g_async_queue_push_unlocked( reinterpret_cast< GAsyncQueue* >( queue ), data );
    }
    HWM_EXPORT void AsyncQueuePushSorted( AsyncQueue* queue, Pointer data, CompareDataFunc func, Pointer userData )
    {
        g_async_queue_push_sorted( reinterpret_cast< GAsyncQueue* >( queue ), data, func, userData );
    }
    HWM_EXPORT void AsyncQueuePushSortedUnlocked( AsyncQueue* queue, Pointer data, CompareDataFunc func, Pointer userData )
    {
        g_async_queue_push_sorted_unlocked( reinterpret_cast< GAsyncQueue* >( queue ), data, func, userData );
    }
    HWM_EXPORT Pointer AsyncQueuePop( AsyncQueue* queue )
    {
        return g_async_queue_pop( reinterpret_cast< GAsyncQueue* >( queue ) );
    }
    HWM_EXPORT Pointer AsyncQueuePopUnlocked( AsyncQueue* queue )
    {
        return g_async_queue_pop_unlocked( reinterpret_cast< GAsyncQueue* >( queue ) );
    }
    HWM_EXPORT Pointer AsyncQueueTryPop( AsyncQueue* queue )
    {
        return g_async_queue_try_pop( reinterpret_cast< GAsyncQueue* >( queue ) );
    }
    HWM_EXPORT Pointer AsyncQueueTryPopUnlocked( AsyncQueue* queue )
    {
        return g_async_queue_try_pop_unlocked( reinterpret_cast< GAsyncQueue* >( queue ) );
    }
    HWM_EXPORT Pointer AsyncQueueTimeoutPop( AsyncQueue* queue, UInt64 timeout )
    {
        return g_async_queue_timeout_pop( reinterpret_cast< GAsyncQueue* >( queue ), timeout );
    }
    HWM_EXPORT Pointer AsyncQueueTimeoutPopUnlocked( AsyncQueue* queue, UInt64 timeout )
    {
        return g_async_queue_timeout_pop_unlocked( reinterpret_cast< GAsyncQueue* >( queue ), timeout );
    }
    HWM_EXPORT Int32 AsyncQueueLength( AsyncQueue* queue )
    {
        return g_async_queue_length( reinterpret_cast< GAsyncQueue* >( queue ) );
    }
    HWM_EXPORT Int32 AsyncQueueLengthUnlocked( AsyncQueue* queue )
    {
        return g_async_queue_length_unlocked( reinterpret_cast< GAsyncQueue* >( queue ) );
    }
    HWM_EXPORT void AsyncQueueSort( AsyncQueue* queue, CompareDataFunc func, Pointer userData )
    {
        g_async_queue_sort( reinterpret_cast< GAsyncQueue* >( queue ), func, userData );
    }
    HWM_EXPORT void AsyncQueueSortUnlocked( AsyncQueue* queue, CompareDataFunc func, Pointer userData )
    {
        g_async_queue_sort_unlocked( reinterpret_cast< GAsyncQueue* >( queue ), func, userData );
    }
    HWM_EXPORT Bool32 AsyncQueueRemove( AsyncQueue* queue, Pointer item )
    {
        return g_async_queue_remove( reinterpret_cast< GAsyncQueue* >( queue ), item );
    }
    HWM_EXPORT Bool32 AsyncQueueRemoveUnlocked( AsyncQueue* queue, Pointer item )
    {
        return g_async_queue_remove_unlocked( reinterpret_cast< GAsyncQueue* >( queue ), item );
    }
    HWM_EXPORT void AsyncQueuePushFront( AsyncQueue* queue, Pointer item )
    {
        g_async_queue_push_front( reinterpret_cast< GAsyncQueue* >( queue ), item );
    }
    HWM_EXPORT void AsyncQueuePushFrontUnlocked( AsyncQueue* queue, Pointer item )
    {
        g_async_queue_push_front_unlocked( reinterpret_cast< GAsyncQueue* >( queue ), item );
    }
}