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

public class DmDbUncontainedEntitiesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_uncontained_entities]";
    public const string TableName = "dm_db_uncontained_entities";
    public const string ShortName = "ddue";
    public const string Sql = """
        SELECT
          ddue.[Class],
          ddue.[class_desc],
          ddue.[major_id],
          ddue.[statement_line_number],
          ddue.[statement_offset_begin],
          ddue.[statement_offset_end],
          ddue.[statement_type],
          ddue.[feature_name],
          ddue.[feature_type_name]
        FROM
          [sys].[dm_db_uncontained_entities] ddue
        """;

    public const int CLASS_FIELD_ID = 0;
    public const int CLASSDESC_FIELD_ID = 1;
    public const int MAJORID_FIELD_ID = 2;
    public const int STATEMENTLINENUMBER_FIELD_ID = 3;
    public const int STATEMENTOFFSETBEGIN_FIELD_ID = 4;
    public const int STATEMENTOFFSETEND_FIELD_ID = 5;
    public const int STATEMENTTYPE_FIELD_ID = 6;
    public const int FEATURENAME_FIELD_ID = 7;
    public const int FEATURETYPENAME_FIELD_ID = 8;


    public DmDbUncontainedEntitiesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbUncontainedEntitiesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbUncontainedEntitiesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Class
    {
        get
        {
            return base.GetInt32(CLASS_FIELD_ID);
        }
    }

    public string ClassDesc
    {
        get
        {
            return base.GetString(CLASSDESC_FIELD_ID);
        }
    }

    public int MajorId
    {
        get
        {
            return base.GetInt32(MAJORID_FIELD_ID);
        }
    }

    public int? StatementLineNumber
    {
        get
        {
            return base.GetNullableInt32(STATEMENTLINENUMBER_FIELD_ID);
        }
    }

    public int? StatementOffsetBegin
    {
        get
        {
            return base.GetNullableInt32(STATEMENTOFFSETBEGIN_FIELD_ID);
        }
    }

    public int? StatementOffsetEnd
    {
        get
        {
            return base.GetNullableInt32(STATEMENTOFFSETEND_FIELD_ID);
        }
    }

    public string? StatementType
    {
        get
        {
            return base.GetNullableString(STATEMENTTYPE_FIELD_ID);
        }
    }

    public string FeatureName
    {
        get
        {
            return base.GetString(FEATURENAME_FIELD_ID);
        }
    }

    public string FeatureTypeName
    {
        get
        {
            return base.GetString(FEATURETYPENAME_FIELD_ID);
        }
    }


    public Types.DmDbUncontainedEntitiesDataType ToDataObject()
    {
        return new Types.DmDbUncontainedEntitiesDataType(Class,
            ClassDesc,
            MajorId,
            StatementLineNumber,
            StatementOffsetBegin,
            StatementOffsetEnd,
            StatementType,
            FeatureName,
            FeatureTypeName);
    }

    public List<Types.DmDbUncontainedEntitiesDataType> ToList()
    {
        var list = new List<Types.DmDbUncontainedEntitiesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
