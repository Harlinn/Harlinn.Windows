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

public class SysconstraintsDataType
{
    readonly int _constid = 0;
    readonly int _id = 0;
    readonly short? _colid;
    readonly byte? _spare1;
    readonly int? _status;
    readonly int? _actions;
    readonly int? _error;

    public SysconstraintsDataType( )
    {
    }

    public SysconstraintsDataType(int constid,
        int id,
        short? colid,
        byte? spare1,
        int? status,
        int? actions,
        int? error)
    {
        _constid = constid;
        _id = id;
        _colid = colid;
        _spare1 = spare1;
        _status = status;
        _actions = actions;
        _error = error;
    }

    public int Constid => _constid;
    public int Id => _id;
    public short? Colid => _colid;
    public byte? Spare1 => _spare1;
    public int? Status => _status;
    public int? Actions => _actions;
    public int? Error => _error;
}
