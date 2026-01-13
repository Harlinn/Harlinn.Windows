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

public class ServiceMessageTypesDataType
{
    readonly string _name = string.Empty;
    readonly int _messageTypeId = 0;
    readonly int? _principalId;
    readonly string _validation = string.Empty;
    readonly string? _validationDesc;
    readonly int? _xmlCollectionId;

    public ServiceMessageTypesDataType( )
    {
    }

    public ServiceMessageTypesDataType(string name,
        int messageTypeId,
        int? principalId,
        string validation,
        string? validationDesc,
        int? xmlCollectionId)
    {
        _name = name;
        _messageTypeId = messageTypeId;
        _principalId = principalId;
        _validation = validation;
        _validationDesc = validationDesc;
        _xmlCollectionId = xmlCollectionId;
    }

    public string Name => _name;
    public int MessageTypeId => _messageTypeId;
    public int? PrincipalId => _principalId;
    public string Validation => _validation;
    public string? ValidationDesc => _validationDesc;
    public int? XmlCollectionId => _xmlCollectionId;
}
