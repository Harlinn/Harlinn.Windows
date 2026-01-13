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

public class SyslanguagesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syslanguages]";
    public const string TableName = "syslanguages";
    public const string ShortName = "s24";
    public const string Sql = """
        SELECT
          s24.[Langid],
          s24.[Dateformat],
          s24.[Datefirst],
          s24.[Upgrade],
          s24.[Name],
          s24.[Alias],
          s24.[Months],
          s24.[Shortmonths],
          s24.[Days],
          s24.[Lcid],
          s24.[Msglangid]
        FROM
          [sys].[syslanguages] s24
        """;

    public const int LANGID_FIELD_ID = 0;
    public const int DATEFORMAT_FIELD_ID = 1;
    public const int DATEFIRST_FIELD_ID = 2;
    public const int UPGRADE_FIELD_ID = 3;
    public const int NAME_FIELD_ID = 4;
    public const int ALIAS_FIELD_ID = 5;
    public const int MONTHS_FIELD_ID = 6;
    public const int SHORTMONTHS_FIELD_ID = 7;
    public const int DAYS_FIELD_ID = 8;
    public const int LCID_FIELD_ID = 9;
    public const int MSGLANGID_FIELD_ID = 10;


    public SyslanguagesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SyslanguagesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SyslanguagesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short Langid
    {
        get
        {
            return base.GetInt16(LANGID_FIELD_ID);
        }
    }

    public string Dateformat
    {
        get
        {
            return base.GetString(DATEFORMAT_FIELD_ID);
        }
    }

    public byte Datefirst
    {
        get
        {
            return base.GetByte(DATEFIRST_FIELD_ID);
        }
    }

    public int? Upgrade
    {
        get
        {
            return base.GetNullableInt32(UPGRADE_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public string Alias
    {
        get
        {
            return base.GetString(ALIAS_FIELD_ID);
        }
    }

    public string? Months
    {
        get
        {
            return base.GetNullableString(MONTHS_FIELD_ID);
        }
    }

    public string? Shortmonths
    {
        get
        {
            return base.GetNullableString(SHORTMONTHS_FIELD_ID);
        }
    }

    public string? Days
    {
        get
        {
            return base.GetNullableString(DAYS_FIELD_ID);
        }
    }

    public int Lcid
    {
        get
        {
            return base.GetInt32(LCID_FIELD_ID);
        }
    }

    public short Msglangid
    {
        get
        {
            return base.GetInt16(MSGLANGID_FIELD_ID);
        }
    }


    public Types.SyslanguagesDataType ToDataObject()
    {
        return new Types.SyslanguagesDataType(Langid,
            Dateformat,
            Datefirst,
            Upgrade,
            Name,
            Alias,
            Months,
            Shortmonths,
            Days,
            Lcid,
            Msglangid);
    }

    public List<Types.SyslanguagesDataType> ToList()
    {
        var list = new List<Types.SyslanguagesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
