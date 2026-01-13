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

public class SysmessagesDataType
{
    readonly int _error = 0;
    readonly byte? _severity;
    readonly short? _dlevel;
    readonly string? _description;
    readonly short _msglangid = 0;

    public SysmessagesDataType( )
    {
    }

    public SysmessagesDataType(int error,
        byte? severity,
        short? dlevel,
        string? description,
        short msglangid)
    {
        _error = error;
        _severity = severity;
        _dlevel = dlevel;
        _description = description;
        _msglangid = msglangid;
    }

    public int Error => _error;
    public byte? Severity => _severity;
    public short? Dlevel => _dlevel;
    public string? Description => _description;
    public short Msglangid => _msglangid;
}
