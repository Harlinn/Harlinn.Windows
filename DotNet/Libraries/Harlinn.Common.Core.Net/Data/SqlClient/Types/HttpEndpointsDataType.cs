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

public class HttpEndpointsDataType
{
    readonly string _name = string.Empty;
    readonly int _endpointId = 0;
    readonly int? _principalId;
    readonly byte _protocol = 0;
    readonly string? _protocolDesc;
    readonly byte _type = 0;
    readonly string? _typeDesc;
    readonly byte? _state;
    readonly string? _stateDesc;
    readonly bool _isAdminEndpoint = false;
    readonly string? _site;
    readonly string? _urlPath;
    readonly bool _isClearPortEnabled = false;
    readonly int _clearPort = 0;
    readonly bool _isSslPortEnabled = false;
    readonly int _sslPort = 0;
    readonly bool _isAnonymousEnabled = false;
    readonly bool _isBasicAuthEnabled = false;
    readonly bool _isDigestAuthEnabled = false;
    readonly bool _isKerberosAuthEnabled = false;
    readonly bool _isNtlmAuthEnabled = false;
    readonly bool _isIntegratedAuthEnabled = false;
    readonly string? _authorizationRealm;
    readonly string? _defaultLogonDomain;
    readonly bool _isCompressionEnabled = false;

    public HttpEndpointsDataType( )
    {
    }

    public HttpEndpointsDataType(string name,
        int endpointId,
        int? principalId,
        byte protocol,
        string? protocolDesc,
        byte type,
        string? typeDesc,
        byte? state,
        string? stateDesc,
        bool isAdminEndpoint,
        string? site,
        string? urlPath,
        bool isClearPortEnabled,
        int clearPort,
        bool isSslPortEnabled,
        int sslPort,
        bool isAnonymousEnabled,
        bool isBasicAuthEnabled,
        bool isDigestAuthEnabled,
        bool isKerberosAuthEnabled,
        bool isNtlmAuthEnabled,
        bool isIntegratedAuthEnabled,
        string? authorizationRealm,
        string? defaultLogonDomain,
        bool isCompressionEnabled)
    {
        _name = name;
        _endpointId = endpointId;
        _principalId = principalId;
        _protocol = protocol;
        _protocolDesc = protocolDesc;
        _type = type;
        _typeDesc = typeDesc;
        _state = state;
        _stateDesc = stateDesc;
        _isAdminEndpoint = isAdminEndpoint;
        _site = site;
        _urlPath = urlPath;
        _isClearPortEnabled = isClearPortEnabled;
        _clearPort = clearPort;
        _isSslPortEnabled = isSslPortEnabled;
        _sslPort = sslPort;
        _isAnonymousEnabled = isAnonymousEnabled;
        _isBasicAuthEnabled = isBasicAuthEnabled;
        _isDigestAuthEnabled = isDigestAuthEnabled;
        _isKerberosAuthEnabled = isKerberosAuthEnabled;
        _isNtlmAuthEnabled = isNtlmAuthEnabled;
        _isIntegratedAuthEnabled = isIntegratedAuthEnabled;
        _authorizationRealm = authorizationRealm;
        _defaultLogonDomain = defaultLogonDomain;
        _isCompressionEnabled = isCompressionEnabled;
    }

    public string Name => _name;
    public int EndpointId => _endpointId;
    public int? PrincipalId => _principalId;
    public byte Protocol => _protocol;
    public string? ProtocolDesc => _protocolDesc;
    public byte Type => _type;
    public string? TypeDesc => _typeDesc;
    public byte? State => _state;
    public string? StateDesc => _stateDesc;
    public bool IsAdminEndpoint => _isAdminEndpoint;
    public string? Site => _site;
    public string? UrlPath => _urlPath;
    public bool IsClearPortEnabled => _isClearPortEnabled;
    public int ClearPort => _clearPort;
    public bool IsSslPortEnabled => _isSslPortEnabled;
    public int SslPort => _sslPort;
    public bool IsAnonymousEnabled => _isAnonymousEnabled;
    public bool IsBasicAuthEnabled => _isBasicAuthEnabled;
    public bool IsDigestAuthEnabled => _isDigestAuthEnabled;
    public bool IsKerberosAuthEnabled => _isKerberosAuthEnabled;
    public bool IsNtlmAuthEnabled => _isNtlmAuthEnabled;
    public bool IsIntegratedAuthEnabled => _isIntegratedAuthEnabled;
    public string? AuthorizationRealm => _authorizationRealm;
    public string? DefaultLogonDomain => _defaultLogonDomain;
    public bool IsCompressionEnabled => _isCompressionEnabled;
}
