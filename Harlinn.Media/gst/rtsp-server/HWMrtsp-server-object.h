#pragma once
#ifndef HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_SERVER_OBJECT_H_
#define HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_SERVER_OBJECT_H_

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

#include <glib/gobject/HWMgobject.h>
#include "HWMrtsp-session-pool.h"
#include "HWMrtsp-mount-points.h"

namespace Harlinn::Media::GStreamer::RtspServer
{
    namespace Internal
    {
        template<typename BaseT>
        class RTSPServer : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( RTSPServer, GstRTSPServer )
        };
    }

    using BasicRTSPServer = Internal::RTSPServer<GLib::BasicObject>;
    using RTSPServer = Internal::RTSPServer<GLib::Object>;
}
#endif

