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
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers;

public class SqlExpressionDependenciesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sql_expression_dependencies]";
    public const string TableName = "sql_expression_dependencies";
    public const string ShortName = "sed";
    public const string Sql = """
        SELECT
          sed.[referencing_id],
          sed.[referencing_minor_id],
          sed.[referencing_class],
          sed.[referencing_class_desc],
          sed.[is_schema_bound_reference],
          sed.[referenced_class],
          sed.[referenced_class_desc],
          sed.[referenced_server_name],
          sed.[referenced_database_name],
          sed.[referenced_schema_name],
          sed.[referenced_entity_name],
          sed.[referenced_id],
          sed.[referenced_minor_id],
          sed.[is_caller_dependent],
          sed.[is_ambiguous]
        FROM
          [sys].[sql_expression_dependencies] sed
        """;

    public const int REFERENCINGID_FIELD_ID = 0;
    public const int REFERENCINGMINORID_FIELD_ID = 1;
    public const int REFERENCINGCLASS_FIELD_ID = 2;
    public const int REFERENCINGCLASSDESC_FIELD_ID = 3;
    public const int ISSCHEMABOUNDREFERENCE_FIELD_ID = 4;
    public const int REFERENCEDCLASS_FIELD_ID = 5;
    public const int REFERENCEDCLASSDESC_FIELD_ID = 6;
    public const int REFERENCEDSERVERNAME_FIELD_ID = 7;
    public const int REFERENCEDDATABASENAME_FIELD_ID = 8;
    public const int REFERENCEDSCHEMANAME_FIELD_ID = 9;
    public const int REFERENCEDENTITYNAME_FIELD_ID = 10;
    public const int REFERENCEDID_FIELD_ID = 11;
    public const int REFERENCEDMINORID_FIELD_ID = 12;
    public const int ISCALLERDEPENDENT_FIELD_ID = 13;
    public const int ISAMBIGUOUS_FIELD_ID = 14;


    public SqlExpressionDependenciesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SqlExpressionDependenciesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SqlExpressionDependenciesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ReferencingId
    {
        get
        {
            return base.GetInt32(REFERENCINGID_FIELD_ID);
        }
    }

    public int ReferencingMinorId
    {
        get
        {
            return base.GetInt32(REFERENCINGMINORID_FIELD_ID);
        }
    }

    public byte? ReferencingClass
    {
        get
        {
            return base.GetNullableByte(REFERENCINGCLASS_FIELD_ID);
        }
    }

    public string? ReferencingClassDesc
    {
        get
        {
            return base.GetNullableString(REFERENCINGCLASSDESC_FIELD_ID);
        }
    }

    public bool IsSchemaBoundReference
    {
        get
        {
            return base.GetBoolean(ISSCHEMABOUNDREFERENCE_FIELD_ID);
        }
    }

    public byte? ReferencedClass
    {
        get
        {
            return base.GetNullableByte(REFERENCEDCLASS_FIELD_ID);
        }
    }

    public string? ReferencedClassDesc
    {
        get
        {
            return base.GetNullableString(REFERENCEDCLASSDESC_FIELD_ID);
        }
    }

    public string? ReferencedServerName
    {
        get
        {
            return base.GetNullableString(REFERENCEDSERVERNAME_FIELD_ID);
        }
    }

    public string? ReferencedDatabaseName
    {
        get
        {
            return base.GetNullableString(REFERENCEDDATABASENAME_FIELD_ID);
        }
    }

    public string? ReferencedSchemaName
    {
        get
        {
            return base.GetNullableString(REFERENCEDSCHEMANAME_FIELD_ID);
        }
    }

    public string? ReferencedEntityName
    {
        get
        {
            return base.GetNullableString(REFERENCEDENTITYNAME_FIELD_ID);
        }
    }

    public int? ReferencedId
    {
        get
        {
            return base.GetNullableInt32(REFERENCEDID_FIELD_ID);
        }
    }

    public int ReferencedMinorId
    {
        get
        {
            return base.GetInt32(REFERENCEDMINORID_FIELD_ID);
        }
    }

    public bool IsCallerDependent
    {
        get
        {
            return base.GetBoolean(ISCALLERDEPENDENT_FIELD_ID);
        }
    }

    public bool IsAmbiguous
    {
        get
        {
            return base.GetBoolean(ISAMBIGUOUS_FIELD_ID);
        }
    }


    public Types.SqlExpressionDependenciesDataType ToDataObject()
    {
        return new Types.SqlExpressionDependenciesDataType(ReferencingId,
            ReferencingMinorId,
            ReferencingClass,
            ReferencingClassDesc,
            IsSchemaBoundReference,
            ReferencedClass,
            ReferencedClassDesc,
            ReferencedServerName,
            ReferencedDatabaseName,
            ReferencedSchemaName,
            ReferencedEntityName,
            ReferencedId,
            ReferencedMinorId,
            IsCallerDependent,
            IsAmbiguous);
    }

    public List<Types.SqlExpressionDependenciesDataType> ToList()
    {
        var list = new List<Types.SqlExpressionDependenciesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
