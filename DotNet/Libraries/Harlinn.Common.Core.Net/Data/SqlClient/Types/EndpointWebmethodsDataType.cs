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

public class EndpointWebmethodsDataType
{
    readonly int _endpointId = 0;
    readonly string? _namespace;
    readonly string _methodAlias = string.Empty;
    readonly string? _objectName;
    readonly byte? _resultSchema;
    readonly string? _resultSchemaDesc;
    readonly byte? _resultFormat;
    readonly string? _resultFormatDesc;

    public EndpointWebmethodsDataType( )
    {
    }

    public EndpointWebmethodsDataType(int endpointId,
        string? namespace__,
        string methodAlias,
        string? objectName,
        byte? resultSchema,
        string? resultSchemaDesc,
        byte? resultFormat,
        string? resultFormatDesc)
    {
        _endpointId = endpointId;
        _namespace = namespace__;
        _methodAlias = methodAlias;
        _objectName = objectName;
        _resultSchema = resultSchema;
        _resultSchemaDesc = resultSchemaDesc;
        _resultFormat = resultFormat;
        _resultFormatDesc = resultFormatDesc;
    }

    public int EndpointId => _endpointId;
    public string? Namespace => _namespace;
    public string MethodAlias => _methodAlias;
    public string? ObjectName => _objectName;
    public byte? ResultSchema => _resultSchema;
    public string? ResultSchemaDesc => _resultSchemaDesc;
    public byte? ResultFormat => _resultFormat;
    public string? ResultFormatDesc => _resultFormatDesc;
}
