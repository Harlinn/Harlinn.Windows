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

public class SensitivityClassificationsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sensitivity_classifications]";
    public const string TableName = "sensitivity_classifications";
    public const string ShortName = "sc0";
    public const string Sql = """
        SELECT
          sc0.[Class],
          sc0.[class_desc],
          sc0.[major_id],
          sc0.[minor_id],
          sc0.[Label],
          sc0.[label_id],
          sc0.[information_type],
          sc0.[information_type_id],
          sc0.[Rank],
          sc0.[rank_desc]
        FROM
          [sys].[sensitivity_classifications] sc0
        """;

    public const int CLASS_FIELD_ID = 0;
    public const int CLASSDESC_FIELD_ID = 1;
    public const int MAJORID_FIELD_ID = 2;
    public const int MINORID_FIELD_ID = 3;
    public const int LABEL_FIELD_ID = 4;
    public const int LABELID_FIELD_ID = 5;
    public const int INFORMATIONTYPE_FIELD_ID = 6;
    public const int INFORMATIONTYPEID_FIELD_ID = 7;
    public const int RANK_FIELD_ID = 8;
    public const int RANKDESC_FIELD_ID = 9;


    public SensitivityClassificationsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SensitivityClassificationsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SensitivityClassificationsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int MinorId
    {
        get
        {
            return base.GetInt32(MINORID_FIELD_ID);
        }
    }

    public object? Label
    {
        get
        {
            return base.GetNullableValue(LABEL_FIELD_ID);
        }
    }

    public object? LabelId
    {
        get
        {
            return base.GetNullableValue(LABELID_FIELD_ID);
        }
    }

    public object? InformationType
    {
        get
        {
            return base.GetNullableValue(INFORMATIONTYPE_FIELD_ID);
        }
    }

    public object? InformationTypeId
    {
        get
        {
            return base.GetNullableValue(INFORMATIONTYPEID_FIELD_ID);
        }
    }

    public object? Rank
    {
        get
        {
            return base.GetNullableValue(RANK_FIELD_ID);
        }
    }

    public string? RankDesc
    {
        get
        {
            return base.GetNullableString(RANKDESC_FIELD_ID);
        }
    }


    public Types.SensitivityClassificationsDataType ToDataObject()
    {
        return new Types.SensitivityClassificationsDataType(Class,
            ClassDesc,
            MajorId,
            MinorId,
            Label,
            LabelId,
            InformationType,
            InformationTypeId,
            Rank,
            RankDesc);
    }

    public List<Types.SensitivityClassificationsDataType> ToList()
    {
        var list = new List<Types.SensitivityClassificationsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
