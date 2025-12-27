/*
   Copyright 2024-2025 Espen Harlinn

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
using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class DmTcpListenerStatesDataType
{
    readonly int _listenerId = 0;
    readonly string _ipAddress = string.Empty;
    readonly bool _isIpv4 = false;
    readonly int _port = 0;
    readonly short _type = 0;
    readonly string _typeDesc = string.Empty;
    readonly short _state = 0;
    readonly string _stateDesc = string.Empty;
    readonly DateTime _startTime;

    public DmTcpListenerStatesDataType( )
    {
    }

    public DmTcpListenerStatesDataType(int listenerId,
        string ipAddress,
        bool isIpv4,
        int port,
        short type,
        string typeDesc,
        short state,
        string stateDesc,
        DateTime startTime)
    {
        _listenerId = listenerId;
        _ipAddress = ipAddress;
        _isIpv4 = isIpv4;
        _port = port;
        _type = type;
        _typeDesc = typeDesc;
        _state = state;
        _stateDesc = stateDesc;
        _startTime = startTime;
    }

    public int ListenerId => _listenerId;
    public string IpAddress => _ipAddress;
    public bool IsIpv4 => _isIpv4;
    public int Port => _port;
    public short Type => _type;
    public string TypeDesc => _typeDesc;
    public short State => _state;
    public string StateDesc => _stateDesc;
    public DateTime StartTime => _startTime;
}
