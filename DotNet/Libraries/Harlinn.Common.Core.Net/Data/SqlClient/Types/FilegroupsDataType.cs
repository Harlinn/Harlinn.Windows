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

public class FilegroupsDataType
{
    readonly string _name = string.Empty;
    readonly int _dataSpaceId = 0;
    readonly string _type = string.Empty;
    readonly string? _typeDesc;
    readonly bool? _isDefault;
    readonly bool? _isSystem;
    readonly Guid? _filegroupGuid;
    readonly int? _logFilegroupId;
    readonly bool? _isReadOnly;
    readonly bool? _isAutogrowAllFiles;

    public FilegroupsDataType( )
    {
    }

    public FilegroupsDataType(string name,
        int dataSpaceId,
        string type,
        string? typeDesc,
        bool? isDefault,
        bool? isSystem,
        Guid? filegroupGuid,
        int? logFilegroupId,
        bool? isReadOnly,
        bool? isAutogrowAllFiles)
    {
        _name = name;
        _dataSpaceId = dataSpaceId;
        _type = type;
        _typeDesc = typeDesc;
        _isDefault = isDefault;
        _isSystem = isSystem;
        _filegroupGuid = filegroupGuid;
        _logFilegroupId = logFilegroupId;
        _isReadOnly = isReadOnly;
        _isAutogrowAllFiles = isAutogrowAllFiles;
    }

    public string Name => _name;
    public int DataSpaceId => _dataSpaceId;
    public string Type => _type;
    public string? TypeDesc => _typeDesc;
    public bool? IsDefault => _isDefault;
    public bool? IsSystem => _isSystem;
    public Guid? FilegroupGuid => _filegroupGuid;
    public int? LogFilegroupId => _logFilegroupId;
    public bool? IsReadOnly => _isReadOnly;
    public bool? IsAutogrowAllFiles => _isAutogrowAllFiles;
}
