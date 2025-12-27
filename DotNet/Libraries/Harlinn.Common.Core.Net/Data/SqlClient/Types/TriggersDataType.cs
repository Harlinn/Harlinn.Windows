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

public class TriggersDataType
{
    readonly string _name = string.Empty;
    readonly int _objectId = 0;
    readonly byte _parentClass = 0;
    readonly string? _parentClassDesc;
    readonly int _parentId = 0;
    readonly string _type = string.Empty;
    readonly string? _typeDesc;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;
    readonly bool _isMsShipped = false;
    readonly bool _isDisabled = false;
    readonly bool _isNotForReplication = false;
    readonly bool _isInsteadOfTrigger = false;

    public TriggersDataType( )
    {
    }

    public TriggersDataType(string name,
        int objectId,
        byte parentClass,
        string? parentClassDesc,
        int parentId,
        string type,
        string? typeDesc,
        DateTime createDate,
        DateTime modifyDate,
        bool isMsShipped,
        bool isDisabled,
        bool isNotForReplication,
        bool isInsteadOfTrigger)
    {
        _name = name;
        _objectId = objectId;
        _parentClass = parentClass;
        _parentClassDesc = parentClassDesc;
        _parentId = parentId;
        _type = type;
        _typeDesc = typeDesc;
        _createDate = createDate;
        _modifyDate = modifyDate;
        _isMsShipped = isMsShipped;
        _isDisabled = isDisabled;
        _isNotForReplication = isNotForReplication;
        _isInsteadOfTrigger = isInsteadOfTrigger;
    }

    public string Name => _name;
    public int ObjectId => _objectId;
    public byte ParentClass => _parentClass;
    public string? ParentClassDesc => _parentClassDesc;
    public int ParentId => _parentId;
    public string Type => _type;
    public string? TypeDesc => _typeDesc;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
    public bool IsMsShipped => _isMsShipped;
    public bool IsDisabled => _isDisabled;
    public bool IsNotForReplication => _isNotForReplication;
    public bool IsInsteadOfTrigger => _isInsteadOfTrigger;
}
