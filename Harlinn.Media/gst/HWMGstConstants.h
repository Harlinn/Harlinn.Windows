#pragma once
#ifndef HARLINN_MEDIA_HWMGSTCONSTANTS_H_
#define HARLINN_MEDIA_HWMGSTCONSTANTS_H_

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


#include <HWMDef.h>

namespace Harlinn::Media::GStreamer
{
    enum class State
    {
        /// <summary>
        /// No pending state.
        /// </summary>
        VoidPending = 0,
        /// <summary>
        /// The NULL state or initial state of an element.
        /// </summary>
        Null = 1,
        /// <summary>
        /// The element is ready to go to Paused.
        /// </summary>
        Ready = 2,
        /// <summary>
        /// The element is Paused, it is ready to accept and process data. 
        /// Sink elements however only accept one buffer and then block.
        /// </summary>
        Paused = 3,
        /// <summary>
        /// The element is Playing, the #GstClock is running and the data is flowing.
        /// </summary>
        Playing = 4
    };




}


#endif
