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

public class EdgeConstraintClausesDataType
{
    readonly int _objectId = 0;
    readonly int _clauseNumber = 0;
    readonly int _fromObjectId = 0;
    readonly int _toObjectId = 0;

    public EdgeConstraintClausesDataType( )
    {
    }

    public EdgeConstraintClausesDataType(int objectId,
        int clauseNumber,
        int fromObjectId,
        int toObjectId)
    {
        _objectId = objectId;
        _clauseNumber = clauseNumber;
        _fromObjectId = fromObjectId;
        _toObjectId = toObjectId;
    }

    public int ObjectId => _objectId;
    public int ClauseNumber => _clauseNumber;
    public int FromObjectId => _fromObjectId;
    public int ToObjectId => _toObjectId;
}
