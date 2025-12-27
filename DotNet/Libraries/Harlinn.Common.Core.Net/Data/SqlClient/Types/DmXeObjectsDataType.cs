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

public class DmXeObjectsDataType
{
    readonly string _name = string.Empty;
    readonly string _objectType = string.Empty;
    readonly Guid _packageGuid;
    readonly string _description = string.Empty;
    readonly int? _capabilities;
    readonly string? _capabilitiesDesc;
    readonly string? _typeName;
    readonly Guid? _typePackageGuid;
    readonly int? _typeSize;

    public DmXeObjectsDataType( )
    {
    }

    public DmXeObjectsDataType(string name,
        string objectType,
        Guid packageGuid,
        string description,
        int? capabilities,
        string? capabilitiesDesc,
        string? typeName,
        Guid? typePackageGuid,
        int? typeSize)
    {
        _name = name;
        _objectType = objectType;
        _packageGuid = packageGuid;
        _description = description;
        _capabilities = capabilities;
        _capabilitiesDesc = capabilitiesDesc;
        _typeName = typeName;
        _typePackageGuid = typePackageGuid;
        _typeSize = typeSize;
    }

    public string Name => _name;
    public string ObjectType => _objectType;
    public Guid PackageGuid => _packageGuid;
    public string Description => _description;
    public int? Capabilities => _capabilities;
    public string? CapabilitiesDesc => _capabilitiesDesc;
    public string? TypeName => _typeName;
    public Guid? TypePackageGuid => _typePackageGuid;
    public int? TypeSize => _typeSize;
}
