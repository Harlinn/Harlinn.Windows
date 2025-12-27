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

public class DatabaseScopedConfigurationsDataType
{
    readonly int? _configurationId;
    readonly string? _name;
    readonly object? _value;
    readonly object? _valueForSecondary;
    readonly bool? _isValueDefault;

    public DatabaseScopedConfigurationsDataType( )
    {
    }

    public DatabaseScopedConfigurationsDataType(int? configurationId,
        string? name,
        object? value,
        object? valueForSecondary,
        bool? isValueDefault)
    {
        _configurationId = configurationId;
        _name = name;
        _value = value;
        _valueForSecondary = valueForSecondary;
        _isValueDefault = isValueDefault;
    }

    public int? ConfigurationId => _configurationId;
    public string? Name => _name;
    public object? Value => _value;
    public object? ValueForSecondary => _valueForSecondary;
    public bool? IsValueDefault => _isValueDefault;
}
