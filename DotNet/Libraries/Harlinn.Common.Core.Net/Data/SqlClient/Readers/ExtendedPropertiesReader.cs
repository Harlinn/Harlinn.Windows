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

public class ExtendedPropertiesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[extended_properties]";
    public const string TableName = "extended_properties";
    public const string ShortName = "ep";
    public const string Sql = """
        SELECT
          ep.[Class],
          ep.[class_desc],
          ep.[major_id],
          ep.[minor_id],
          ep.[Name],
          ep.[Value]
        FROM
          [sys].[extended_properties] ep
        """;

    public const int CLASS_FIELD_ID = 0;
    public const int CLASSDESC_FIELD_ID = 1;
    public const int MAJORID_FIELD_ID = 2;
    public const int MINORID_FIELD_ID = 3;
    public const int NAME_FIELD_ID = 4;
    public const int VALUE_FIELD_ID = 5;


    public ExtendedPropertiesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ExtendedPropertiesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ExtendedPropertiesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte Class
    {
        get
        {
            return base.GetByte(CLASS_FIELD_ID);
        }
    }

    public string? ClassDesc
    {
        get
        {
            return base.GetNullableString(CLASSDESC_FIELD_ID);
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

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public object? Value
    {
        get
        {
            return base.GetNullableValue(VALUE_FIELD_ID);
        }
    }


    public Types.ExtendedPropertiesDataType ToDataObject()
    {
        return new Types.ExtendedPropertiesDataType(Class,
            ClassDesc,
            MajorId,
            MinorId,
            Name,
            Value);
    }

    public List<Types.ExtendedPropertiesDataType> ToList()
    {
        var list = new List<Types.ExtendedPropertiesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
