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

public class StatsDataType
{
    readonly int _objectId = 0;
    readonly string? _name;
    readonly int _statsId = 0;
    readonly bool? _autoCreated;
    readonly bool? _userCreated;
    readonly bool? _noRecompute;
    readonly bool? _hasFilter;
    readonly string? _filterDefinition;
    readonly bool? _isTemporary;
    readonly bool? _isIncremental;
    readonly bool? _hasPersistedSample;
    readonly int _statsGenerationMethod = 0;
    readonly string _statsGenerationMethodDesc = string.Empty;

    public StatsDataType( )
    {
    }

    public StatsDataType(int objectId,
        string? name,
        int statsId,
        bool? autoCreated,
        bool? userCreated,
        bool? noRecompute,
        bool? hasFilter,
        string? filterDefinition,
        bool? isTemporary,
        bool? isIncremental,
        bool? hasPersistedSample,
        int statsGenerationMethod,
        string statsGenerationMethodDesc)
    {
        _objectId = objectId;
        _name = name;
        _statsId = statsId;
        _autoCreated = autoCreated;
        _userCreated = userCreated;
        _noRecompute = noRecompute;
        _hasFilter = hasFilter;
        _filterDefinition = filterDefinition;
        _isTemporary = isTemporary;
        _isIncremental = isIncremental;
        _hasPersistedSample = hasPersistedSample;
        _statsGenerationMethod = statsGenerationMethod;
        _statsGenerationMethodDesc = statsGenerationMethodDesc;
    }

    public int ObjectId => _objectId;
    public string? Name => _name;
    public int StatsId => _statsId;
    public bool? AutoCreated => _autoCreated;
    public bool? UserCreated => _userCreated;
    public bool? NoRecompute => _noRecompute;
    public bool? HasFilter => _hasFilter;
    public string? FilterDefinition => _filterDefinition;
    public bool? IsTemporary => _isTemporary;
    public bool? IsIncremental => _isIncremental;
    public bool? HasPersistedSample => _hasPersistedSample;
    public int StatsGenerationMethod => _statsGenerationMethod;
    public string StatsGenerationMethodDesc => _statsGenerationMethodDesc;
}
