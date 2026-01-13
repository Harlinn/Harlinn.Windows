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

public class SyscommentsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syscomments]";
    public const string TableName = "syscomments";
    public const string ShortName = "s41";
    public const string Sql = """
        SELECT
          s41.[Id],
          s41.[Number],
          s41.[Colid],
          s41.[Status],
          s41.[Ctext],
          s41.[Texttype],
          s41.[Language],
          s41.[Encrypted],
          s41.[Compressed],
          s41.[Text]
        FROM
          [sys].[syscomments] s41
        """;

    public const int ID_FIELD_ID = 0;
    public const int NUMBER_FIELD_ID = 1;
    public const int COLID_FIELD_ID = 2;
    public const int STATUS_FIELD_ID = 3;
    public const int CTEXT_FIELD_ID = 4;
    public const int TEXTTYPE_FIELD_ID = 5;
    public const int LANGUAGE_FIELD_ID = 6;
    public const int ENCRYPTED_FIELD_ID = 7;
    public const int COMPRESSED_FIELD_ID = 8;
    public const int TEXT_FIELD_ID = 9;


    public SyscommentsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SyscommentsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SyscommentsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Id
    {
        get
        {
            return base.GetInt32(ID_FIELD_ID);
        }
    }

    public short? Number
    {
        get
        {
            return base.GetNullableInt16(NUMBER_FIELD_ID);
        }
    }

    public short Colid
    {
        get
        {
            return base.GetInt16(COLID_FIELD_ID);
        }
    }

    public short Status
    {
        get
        {
            return base.GetInt16(STATUS_FIELD_ID);
        }
    }

    public byte[]? Ctext
    {
        get
        {
            return base.GetNullableBinary(CTEXT_FIELD_ID);
        }
    }

    public short? Texttype
    {
        get
        {
            return base.GetNullableInt16(TEXTTYPE_FIELD_ID);
        }
    }

    public short? Language
    {
        get
        {
            return base.GetNullableInt16(LANGUAGE_FIELD_ID);
        }
    }

    public bool Encrypted
    {
        get
        {
            return base.GetBoolean(ENCRYPTED_FIELD_ID);
        }
    }

    public bool Compressed
    {
        get
        {
            return base.GetBoolean(COMPRESSED_FIELD_ID);
        }
    }

    public string? Text
    {
        get
        {
            return base.GetNullableString(TEXT_FIELD_ID);
        }
    }


    public Types.SyscommentsDataType ToDataObject()
    {
        return new Types.SyscommentsDataType(Id,
            Number,
            Colid,
            Status,
            Ctext,
            Texttype,
            Language,
            Encrypted,
            Compressed,
            Text);
    }

    public List<Types.SyscommentsDataType> ToList()
    {
        var list = new List<Types.SyscommentsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
