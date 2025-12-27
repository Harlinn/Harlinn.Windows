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

public class SqlDependenciesDataType
{
    readonly byte _class = 0;
    readonly string? _classDesc;
    readonly int _objectId = 0;
    readonly int _columnId = 0;
    readonly int _referencedMajorId = 0;
    readonly int _referencedMinorId = 0;
    readonly bool _isSelected = false;
    readonly bool _isUpdated = false;
    readonly bool _isSelectAll = false;

    public SqlDependenciesDataType( )
    {
    }

    public SqlDependenciesDataType(byte class__,
        string? classDesc,
        int objectId,
        int columnId,
        int referencedMajorId,
        int referencedMinorId,
        bool isSelected,
        bool isUpdated,
        bool isSelectAll)
    {
        _class = class__;
        _classDesc = classDesc;
        _objectId = objectId;
        _columnId = columnId;
        _referencedMajorId = referencedMajorId;
        _referencedMinorId = referencedMinorId;
        _isSelected = isSelected;
        _isUpdated = isUpdated;
        _isSelectAll = isSelectAll;
    }

    public byte Class => _class;
    public string? ClassDesc => _classDesc;
    public int ObjectId => _objectId;
    public int ColumnId => _columnId;
    public int ReferencedMajorId => _referencedMajorId;
    public int ReferencedMinorId => _referencedMinorId;
    public bool IsSelected => _isSelected;
    public bool IsUpdated => _isUpdated;
    public bool IsSelectAll => _isSelectAll;
}
