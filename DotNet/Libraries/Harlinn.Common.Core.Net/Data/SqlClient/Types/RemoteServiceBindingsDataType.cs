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

public class RemoteServiceBindingsDataType
{
    readonly string _name = string.Empty;
    readonly int _remoteServiceBindingId = 0;
    readonly int? _principalId;
    readonly string? _remoteServiceName;
    readonly int _serviceContractId = 0;
    readonly int? _remotePrincipalId;
    readonly bool _isAnonymousOn = false;

    public RemoteServiceBindingsDataType( )
    {
    }

    public RemoteServiceBindingsDataType(string name,
        int remoteServiceBindingId,
        int? principalId,
        string? remoteServiceName,
        int serviceContractId,
        int? remotePrincipalId,
        bool isAnonymousOn)
    {
        _name = name;
        _remoteServiceBindingId = remoteServiceBindingId;
        _principalId = principalId;
        _remoteServiceName = remoteServiceName;
        _serviceContractId = serviceContractId;
        _remotePrincipalId = remotePrincipalId;
        _isAnonymousOn = isAnonymousOn;
    }

    public string Name => _name;
    public int RemoteServiceBindingId => _remoteServiceBindingId;
    public int? PrincipalId => _principalId;
    public string? RemoteServiceName => _remoteServiceName;
    public int ServiceContractId => _serviceContractId;
    public int? RemotePrincipalId => _remotePrincipalId;
    public bool IsAnonymousOn => _isAnonymousOn;
}
