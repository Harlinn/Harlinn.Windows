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

public class SoapEndpointsDataType
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
    readonly bool _isSqlLanguageEnabled = false;
    readonly string? _wsdlGeneratorProcedure;
    readonly string? _defaultDatabase;
    readonly string? _defaultNamespace;
    readonly byte? _defaultResultSchema;
    readonly string? _defaultResultSchemaDesc;
    readonly bool _isXmlCharsetEnforced = false;
    readonly bool _isSessionEnabled = false;
    readonly int _sessionTimeout = 0;
    readonly string? _loginType;
    readonly int _headerLimit = 0;

    public SoapEndpointsDataType( )
    {
    }

    public SoapEndpointsDataType(string name,
        int endpointId,
        int? principalId,
        byte protocol,
        string? protocolDesc,
        byte type,
        string? typeDesc,
        byte? state,
        string? stateDesc,
        bool isAdminEndpoint,
        bool isSqlLanguageEnabled,
        string? wsdlGeneratorProcedure,
        string? defaultDatabase,
        string? defaultNamespace,
        byte? defaultResultSchema,
        string? defaultResultSchemaDesc,
        bool isXmlCharsetEnforced,
        bool isSessionEnabled,
        int sessionTimeout,
        string? loginType,
        int headerLimit)
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
        _isSqlLanguageEnabled = isSqlLanguageEnabled;
        _wsdlGeneratorProcedure = wsdlGeneratorProcedure;
        _defaultDatabase = defaultDatabase;
        _defaultNamespace = defaultNamespace;
        _defaultResultSchema = defaultResultSchema;
        _defaultResultSchemaDesc = defaultResultSchemaDesc;
        _isXmlCharsetEnforced = isXmlCharsetEnforced;
        _isSessionEnabled = isSessionEnabled;
        _sessionTimeout = sessionTimeout;
        _loginType = loginType;
        _headerLimit = headerLimit;
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
    public bool IsSqlLanguageEnabled => _isSqlLanguageEnabled;
    public string? WsdlGeneratorProcedure => _wsdlGeneratorProcedure;
    public string? DefaultDatabase => _defaultDatabase;
    public string? DefaultNamespace => _defaultNamespace;
    public byte? DefaultResultSchema => _defaultResultSchema;
    public string? DefaultResultSchemaDesc => _defaultResultSchemaDesc;
    public bool IsXmlCharsetEnforced => _isXmlCharsetEnforced;
    public bool IsSessionEnabled => _isSessionEnabled;
    public int SessionTimeout => _sessionTimeout;
    public string? LoginType => _loginType;
    public int HeaderLimit => _headerLimit;
}
