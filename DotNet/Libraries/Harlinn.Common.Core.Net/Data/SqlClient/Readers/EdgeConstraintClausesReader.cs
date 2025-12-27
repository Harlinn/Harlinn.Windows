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
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers;

public class EdgeConstraintClausesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[edge_constraint_clauses]";
    public const string TableName = "edge_constraint_clauses";
    public const string ShortName = "ecc";
    public const string Sql = """
        SELECT
          ecc.[object_id],
          ecc.[clause_number],
          ecc.[from_object_id],
          ecc.[to_object_id]
        FROM
          [sys].[edge_constraint_clauses] ecc
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int CLAUSENUMBER_FIELD_ID = 1;
    public const int FROMOBJECTID_FIELD_ID = 2;
    public const int TOOBJECTID_FIELD_ID = 3;


    public EdgeConstraintClausesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public EdgeConstraintClausesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public EdgeConstraintClausesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int ClauseNumber
    {
        get
        {
            return base.GetInt32(CLAUSENUMBER_FIELD_ID);
        }
    }

    public int FromObjectId
    {
        get
        {
            return base.GetInt32(FROMOBJECTID_FIELD_ID);
        }
    }

    public int ToObjectId
    {
        get
        {
            return base.GetInt32(TOOBJECTID_FIELD_ID);
        }
    }


    public Types.EdgeConstraintClausesDataType ToDataObject()
    {
        return new Types.EdgeConstraintClausesDataType(ObjectId,
            ClauseNumber,
            FromObjectId,
            ToObjectId);
    }

    public List<Types.EdgeConstraintClausesDataType> ToList()
    {
        var list = new List<Types.EdgeConstraintClausesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
