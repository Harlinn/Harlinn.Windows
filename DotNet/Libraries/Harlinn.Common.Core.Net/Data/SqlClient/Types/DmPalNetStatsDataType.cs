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

public class DmPalNetStatsDataType
{
    readonly string _interface = string.Empty;
    readonly long _recvBytes = 0;
    readonly long _recvPackets = 0;
    readonly long _errors = 0;
    readonly long _drops = 0;
    readonly long _fifo = 0;
    readonly long _frame = 0;
    readonly long _compressed = 0;
    readonly long _multicast = 0;

    public DmPalNetStatsDataType( )
    {
    }

    public DmPalNetStatsDataType(string interface__,
        long recvBytes,
        long recvPackets,
        long errors,
        long drops,
        long fifo,
        long frame,
        long compressed,
        long multicast)
    {
        _interface = interface__;
        _recvBytes = recvBytes;
        _recvPackets = recvPackets;
        _errors = errors;
        _drops = drops;
        _fifo = fifo;
        _frame = frame;
        _compressed = compressed;
        _multicast = multicast;
    }

    public string Interface => _interface;
    public long RecvBytes => _recvBytes;
    public long RecvPackets => _recvPackets;
    public long Errors => _errors;
    public long Drops => _drops;
    public long Fifo => _fifo;
    public long Frame => _frame;
    public long Compressed => _compressed;
    public long Multicast => _multicast;
}
