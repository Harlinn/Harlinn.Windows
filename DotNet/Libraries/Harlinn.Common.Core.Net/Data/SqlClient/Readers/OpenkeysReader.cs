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

public class OpenkeysReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[openkeys]";
    public const string TableName = "openkeys";
    public const string ShortName = "o";
    public const string Sql = """
        SELECT
          o.[database_id],
          o.[database_name],
          o.[key_id],
          o.[key_name],
          o.[key_guid],
          o.[opened_date],
          o.[Status]
        FROM
          [sys].[openkeys] o
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int DATABASENAME_FIELD_ID = 1;
    public const int KEYID_FIELD_ID = 2;
    public const int KEYNAME_FIELD_ID = 3;
    public const int KEYGUID_FIELD_ID = 4;
    public const int OPENEDDATE_FIELD_ID = 5;
    public const int STATUS_FIELD_ID = 6;


    public OpenkeysReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public OpenkeysReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public OpenkeysReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? DatabaseId
    {
        get
        {
            return base.GetNullableInt32(DATABASEID_FIELD_ID);
        }
    }

    public string? DatabaseName
    {
        get
        {
            return base.GetNullableString(DATABASENAME_FIELD_ID);
        }
    }

    public int? KeyId
    {
        get
        {
            return base.GetNullableInt32(KEYID_FIELD_ID);
        }
    }

    public string? KeyName
    {
        get
        {
            return base.GetNullableString(KEYNAME_FIELD_ID);
        }
    }

    public Guid? KeyGuid
    {
        get
        {
            return base.GetNullableGuid(KEYGUID_FIELD_ID);
        }
    }

    public DateTime? OpenedDate
    {
        get
        {
            return base.GetNullableDateTime(OPENEDDATE_FIELD_ID);
        }
    }

    public short? Status
    {
        get
        {
            return base.GetNullableInt16(STATUS_FIELD_ID);
        }
    }


    public Types.OpenkeysDataType ToDataObject()
    {
        return new Types.OpenkeysDataType(DatabaseId,
            DatabaseName,
            KeyId,
            KeyName,
            KeyGuid,
            OpenedDate,
            Status);
    }

    public List<Types.OpenkeysDataType> ToList()
    {
        var list = new List<Types.OpenkeysDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
