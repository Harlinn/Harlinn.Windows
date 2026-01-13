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

public class ConfigurationsDataType
{
    readonly int _configurationId = 0;
    readonly string _name = string.Empty;
    readonly object? _value;
    readonly object? _minimum;
    readonly object? _maximum;
    readonly object? _valueInUse;
    readonly string _description = string.Empty;
    readonly bool _isDynamic = false;
    readonly bool _isAdvanced = false;

    public ConfigurationsDataType( )
    {
    }

    public ConfigurationsDataType(int configurationId,
        string name,
        object? value,
        object? minimum,
        object? maximum,
        object? valueInUse,
        string description,
        bool isDynamic,
        bool isAdvanced)
    {
        _configurationId = configurationId;
        _name = name;
        _value = value;
        _minimum = minimum;
        _maximum = maximum;
        _valueInUse = valueInUse;
        _description = description;
        _isDynamic = isDynamic;
        _isAdvanced = isAdvanced;
    }

    public int ConfigurationId => _configurationId;
    public string Name => _name;
    public object? Value => _value;
    public object? Minimum => _minimum;
    public object? Maximum => _maximum;
    public object? ValueInUse => _valueInUse;
    public string Description => _description;
    public bool IsDynamic => _isDynamic;
    public bool IsAdvanced => _isAdvanced;
}
