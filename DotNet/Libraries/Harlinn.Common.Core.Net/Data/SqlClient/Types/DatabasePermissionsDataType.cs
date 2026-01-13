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

public class DatabasePermissionsDataType
{
    readonly byte _class = 0;
    readonly string? _classDesc;
    readonly int _majorId = 0;
    readonly int _minorId = 0;
    readonly int _granteePrincipalId = 0;
    readonly int _grantorPrincipalId = 0;
    readonly string _type = string.Empty;
    readonly string? _permissionName;
    readonly string _state = string.Empty;
    readonly string? _stateDesc;

    public DatabasePermissionsDataType( )
    {
    }

    public DatabasePermissionsDataType(byte class__,
        string? classDesc,
        int majorId,
        int minorId,
        int granteePrincipalId,
        int grantorPrincipalId,
        string type,
        string? permissionName,
        string state,
        string? stateDesc)
    {
        _class = class__;
        _classDesc = classDesc;
        _majorId = majorId;
        _minorId = minorId;
        _granteePrincipalId = granteePrincipalId;
        _grantorPrincipalId = grantorPrincipalId;
        _type = type;
        _permissionName = permissionName;
        _state = state;
        _stateDesc = stateDesc;
    }

    public byte Class => _class;
    public string? ClassDesc => _classDesc;
    public int MajorId => _majorId;
    public int MinorId => _minorId;
    public int GranteePrincipalId => _granteePrincipalId;
    public int GrantorPrincipalId => _grantorPrincipalId;
    public string Type => _type;
    public string? PermissionName => _permissionName;
    public string State => _state;
    public string? StateDesc => _stateDesc;
}
