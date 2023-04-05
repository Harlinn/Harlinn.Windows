#pragma once
#ifndef HARLINN_COMMON_CORE_HCCTCPCLIENT_H_
#define HARLINN_COMMON_CORE_HCCTCPCLIENT_H_

#include <HCCSocket.h>

namespace Harlinn::Common::Core::IO::Sockets::Tcp::Client
{
    using Socket = Sockets::SocketT<SocketType::Stream, ProtocolType::Tcp>;



    template< typename DerivedT >
    class ConnectionHandler : public SocketHandler<DerivedT>
    {
    public:
        using Base = SocketHandler<DerivedT>;
    private:
        Socket socket_;
    public:

    };
}

#endif
