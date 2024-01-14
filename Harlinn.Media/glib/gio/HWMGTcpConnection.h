#pragma once 
#ifndef HARLINN_MEDIA_GLIB_GIO_HWMGTCPCONNECTION_H_
#define HARLINN_MEDIA_GLIB_GIO_HWMGTCPCONNECTION_H_
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

#include "HWMGSocketConnection.h"

namespace Harlinn::Media::GLib::GIO
{
    namespace Internal
    {
        template<typename BaseT>
        class TcpConnectionImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( TcpConnectionImpl, GTcpConnection )
        };
    }
    using BasicTcpConnection = Internal::TcpConnectionImpl<BasicSocketConnection>;
    using TcpConnection = Internal::TcpConnectionImpl<SocketConnection>;

    namespace Internal
    {
        template<typename BaseT>
        class TcpWrapperConnectionImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( TcpWrapperConnectionImpl, GTcpWrapperConnection )
        };
    }
    using BasicTcpWrapperConnection = Internal::TcpWrapperConnectionImpl<BasicTcpConnection>;
    using TcpWrapperConnection = Internal::TcpWrapperConnectionImpl<TcpConnection>;
}
#endif
