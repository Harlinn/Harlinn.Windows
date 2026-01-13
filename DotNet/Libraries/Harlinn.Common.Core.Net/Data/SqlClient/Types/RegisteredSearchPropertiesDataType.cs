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

public class RegisteredSearchPropertiesDataType
{
    readonly int _propertyListId = 0;
    readonly int _propertyId = 0;
    readonly string _propertyName = string.Empty;
    readonly Guid _propertySetGuid;
    readonly int _propertyIntId = 0;
    readonly string? _propertyDescription;

    public RegisteredSearchPropertiesDataType( )
    {
    }

    public RegisteredSearchPropertiesDataType(int propertyListId,
        int propertyId,
        string propertyName,
        Guid propertySetGuid,
        int propertyIntId,
        string? propertyDescription)
    {
        _propertyListId = propertyListId;
        _propertyId = propertyId;
        _propertyName = propertyName;
        _propertySetGuid = propertySetGuid;
        _propertyIntId = propertyIntId;
        _propertyDescription = propertyDescription;
    }

    public int PropertyListId => _propertyListId;
    public int PropertyId => _propertyId;
    public string PropertyName => _propertyName;
    public Guid PropertySetGuid => _propertySetGuid;
    public int PropertyIntId => _propertyIntId;
    public string? PropertyDescription => _propertyDescription;
}
