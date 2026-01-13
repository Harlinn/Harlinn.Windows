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

public class StatsColumnsDataType
{
    readonly int _objectId = 0;
    readonly int _statsId = 0;
    readonly int? _statsColumnId;
    readonly int? _columnId;

    public StatsColumnsDataType( )
    {
    }

    public StatsColumnsDataType(int objectId,
        int statsId,
        int? statsColumnId,
        int? columnId)
    {
        _objectId = objectId;
        _statsId = statsId;
        _statsColumnId = statsColumnId;
        _columnId = columnId;
    }

    public int ObjectId => _objectId;
    public int StatsId => _statsId;
    public int? StatsColumnId => _statsColumnId;
    public int? ColumnId => _columnId;
}
