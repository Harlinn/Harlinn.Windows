#pragma once 
#ifndef HARLINN_MEDIA_HWMGSTTASKPOOL_H_
#define HARLINN_MEDIA_HWMGSTTASKPOOL_H_
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

#include "HWMGstObject.h"

namespace Harlinn::Media::GStreamer
{
    namespace Internal
    {
        template<typename BaseT>
        class TaskPoolImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( TaskPoolImpl, GstTaskPool )
        };
    }
    using BasicTaskPool = Internal::TaskPoolImpl<BasicObject>;
    using TaskPool = Internal::TaskPoolImpl<Object>;

    namespace Internal
    {
        template<typename BaseT>
        class SharedTaskPoolImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( SharedTaskPoolImpl, GstSharedTaskPool )
        };
    }
    using BasicSharedTaskPool = Internal::SharedTaskPoolImpl<BasicTaskPool>;
    using SharedTaskPool = Internal::SharedTaskPoolImpl<TaskPool>;
}
#endif

