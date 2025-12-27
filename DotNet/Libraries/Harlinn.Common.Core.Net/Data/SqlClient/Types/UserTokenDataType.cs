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

public class UserTokenDataType
{
    readonly int? _principalId;
    readonly byte[]? _sid;
    readonly string? _name;
    readonly string? _type;
    readonly string? _usage;

    public UserTokenDataType( )
    {
    }

    public UserTokenDataType(int? principalId,
        byte[]? sid,
        string? name,
        string? type,
        string? usage)
    {
        _principalId = principalId;
        _sid = sid;
        _name = name;
        _type = type;
        _usage = usage;
    }

    public int? PrincipalId => _principalId;
    public byte[]? Sid => _sid;
    public string? Name => _name;
    public string? Type => _type;
    public string? Usage => _usage;
}
