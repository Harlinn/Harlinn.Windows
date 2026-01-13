/*
   Copyright 2024-2026 Espen Harlinn

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

public class SysremoteloginsDataType
{
    readonly short? _remoteserverid;
    readonly string? _remoteusername;
    readonly short? _status;
    readonly byte[]? _sid;
    readonly DateTime _changedate;

    public SysremoteloginsDataType( )
    {
    }

    public SysremoteloginsDataType(short? remoteserverid,
        string? remoteusername,
        short? status,
        byte[]? sid,
        DateTime changedate)
    {
        _remoteserverid = remoteserverid;
        _remoteusername = remoteusername;
        _status = status;
        _sid = sid;
        _changedate = changedate;
    }

    public short? Remoteserverid => _remoteserverid;
    public string? Remoteusername => _remoteusername;
    public short? Status => _status;
    public byte[]? Sid => _sid;
    public DateTime Changedate => _changedate;
}
