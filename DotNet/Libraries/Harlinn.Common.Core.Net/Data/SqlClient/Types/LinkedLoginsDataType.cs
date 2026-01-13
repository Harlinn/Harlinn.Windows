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

public class LinkedLoginsDataType
{
    readonly int _serverId = 0;
    readonly int? _localPrincipalId;
    readonly bool _usesSelfCredential = false;
    readonly string? _remoteName;
    readonly DateTime _modifyDate;

    public LinkedLoginsDataType( )
    {
    }

    public LinkedLoginsDataType(int serverId,
        int? localPrincipalId,
        bool usesSelfCredential,
        string? remoteName,
        DateTime modifyDate)
    {
        _serverId = serverId;
        _localPrincipalId = localPrincipalId;
        _usesSelfCredential = usesSelfCredential;
        _remoteName = remoteName;
        _modifyDate = modifyDate;
    }

    public int ServerId => _serverId;
    public int? LocalPrincipalId => _localPrincipalId;
    public bool UsesSelfCredential => _usesSelfCredential;
    public string? RemoteName => _remoteName;
    public DateTime ModifyDate => _modifyDate;
}
