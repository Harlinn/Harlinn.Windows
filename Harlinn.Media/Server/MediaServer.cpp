#include "pch.h"
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

#include "MediaServer.h"
#include "Impl/MediaServerImpl.h"

namespace Harlinn::Media::Server
{
    MediaServer::~MediaServer( )
    { }

    MediaServer MediaServer::Create( const MediaServerOptions& options )
    {
        MediaServer result;
        result.impl_ = std::make_unique<MediaServerImpl>( options );
        return result;
    }

    void MediaServer::Start( )
    {
        if ( impl_ )
        {
            impl_->Start( );
        }
    }
    void MediaServer::Stop( )
    {
        if ( impl_ )
        {
            impl_->Stop( );
        }
    }


}