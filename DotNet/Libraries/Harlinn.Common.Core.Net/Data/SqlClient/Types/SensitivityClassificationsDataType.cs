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

public class SensitivityClassificationsDataType
{
    readonly int _class = 0;
    readonly string _classDesc = string.Empty;
    readonly int _majorId = 0;
    readonly int _minorId = 0;
    readonly object? _label;
    readonly object? _labelId;
    readonly object? _informationType;
    readonly object? _informationTypeId;
    readonly object? _rank;
    readonly string? _rankDesc;

    public SensitivityClassificationsDataType( )
    {
    }

    public SensitivityClassificationsDataType(int class__,
        string classDesc,
        int majorId,
        int minorId,
        object? label,
        object? labelId,
        object? informationType,
        object? informationTypeId,
        object? rank,
        string? rankDesc)
    {
        _class = class__;
        _classDesc = classDesc;
        _majorId = majorId;
        _minorId = minorId;
        _label = label;
        _labelId = labelId;
        _informationType = informationType;
        _informationTypeId = informationTypeId;
        _rank = rank;
        _rankDesc = rankDesc;
    }

    public int Class => _class;
    public string ClassDesc => _classDesc;
    public int MajorId => _majorId;
    public int MinorId => _minorId;
    public object? Label => _label;
    public object? LabelId => _labelId;
    public object? InformationType => _informationType;
    public object? InformationTypeId => _informationTypeId;
    public object? Rank => _rank;
    public string? RankDesc => _rankDesc;
}
