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

public class DmXePackagesDataType
{
    readonly string _name = string.Empty;
    readonly Guid _guid;
    readonly string _description = string.Empty;
    readonly int? _capabilities;
    readonly string? _capabilitiesDesc;
    readonly string _moduleGuid = string.Empty;
    readonly byte[] _moduleAddress = Array.Empty<byte>();

    public DmXePackagesDataType( )
    {
    }

    public DmXePackagesDataType(string name,
        Guid guid,
        string description,
        int? capabilities,
        string? capabilitiesDesc,
        string moduleGuid,
        byte[] moduleAddress)
    {
        _name = name;
        _guid = guid;
        _description = description;
        _capabilities = capabilities;
        _capabilitiesDesc = capabilitiesDesc;
        _moduleGuid = moduleGuid;
        _moduleAddress = moduleAddress;
    }

    public string Name => _name;
    public Guid Guid => _guid;
    public string Description => _description;
    public int? Capabilities => _capabilities;
    public string? CapabilitiesDesc => _capabilitiesDesc;
    public string ModuleGuid => _moduleGuid;
    public byte[] ModuleAddress => _moduleAddress;
}
