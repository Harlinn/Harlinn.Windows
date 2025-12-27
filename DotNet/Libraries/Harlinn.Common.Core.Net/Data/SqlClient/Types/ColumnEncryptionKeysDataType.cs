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

public class ColumnEncryptionKeysDataType
{
    readonly string _name = string.Empty;
    readonly int _columnEncryptionKeyId = 0;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;

    public ColumnEncryptionKeysDataType( )
    {
    }

    public ColumnEncryptionKeysDataType(string name,
        int columnEncryptionKeyId,
        DateTime createDate,
        DateTime modifyDate)
    {
        _name = name;
        _columnEncryptionKeyId = columnEncryptionKeyId;
        _createDate = createDate;
        _modifyDate = modifyDate;
    }

    public string Name => _name;
    public int ColumnEncryptionKeyId => _columnEncryptionKeyId;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
}
