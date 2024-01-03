#pragma once
#ifndef HARLINN_MEDIA_HWMVLCCOMMON_H_
#define HARLINN_MEDIA_HWMVLCCOMMON_H_
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

#include "HWMDef.h"

struct libvlc_instance_t;
typedef int64_t libvlc_time_t;
struct libvlc_event_manager_t;
struct libvlc_event_t;
typedef int libvlc_event_type_t;
typedef void ( *libvlc_callback_t )( const struct libvlc_event_t* p_event, void* p_data );
struct libvlc_module_description_t;

#endif
