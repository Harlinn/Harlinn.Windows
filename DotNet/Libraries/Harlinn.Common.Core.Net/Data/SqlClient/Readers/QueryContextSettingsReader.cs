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

public class QueryContextSettingsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[query_context_settings]";
    public const string TableName = "query_context_settings";
    public const string ShortName = "qcs";
    public const string Sql = """
        SELECT
          qcs.[context_settings_id],
          qcs.[set_options],
          qcs.[language_id],
          qcs.[date_format],
          qcs.[date_first],
          qcs.[Status],
          qcs.[required_cursor_options],
          qcs.[acceptable_cursor_options],
          qcs.[merge_action_type],
          qcs.[default_schema_id],
          qcs.[is_replication_specific],
          qcs.[is_contained]
        FROM
          [sys].[query_context_settings] qcs
        """;

    public const int CONTEXTSETTINGSID_FIELD_ID = 0;
    public const int SETOPTIONS_FIELD_ID = 1;
    public const int LANGUAGEID_FIELD_ID = 2;
    public const int DATEFORMAT_FIELD_ID = 3;
    public const int DATEFIRST_FIELD_ID = 4;
    public const int STATUS_FIELD_ID = 5;
    public const int REQUIREDCURSOROPTIONS_FIELD_ID = 6;
    public const int ACCEPTABLECURSOROPTIONS_FIELD_ID = 7;
    public const int MERGEACTIONTYPE_FIELD_ID = 8;
    public const int DEFAULTSCHEMAID_FIELD_ID = 9;
    public const int ISREPLICATIONSPECIFIC_FIELD_ID = 10;
    public const int ISCONTAINED_FIELD_ID = 11;


    public QueryContextSettingsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public QueryContextSettingsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public QueryContextSettingsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long ContextSettingsId
    {
        get
        {
            return base.GetInt64(CONTEXTSETTINGSID_FIELD_ID);
        }
    }

    public byte[]? SetOptions
    {
        get
        {
            return base.GetNullableBinary(SETOPTIONS_FIELD_ID);
        }
    }

    public short LanguageId
    {
        get
        {
            return base.GetInt16(LANGUAGEID_FIELD_ID);
        }
    }

    public short DateFormat
    {
        get
        {
            return base.GetInt16(DATEFORMAT_FIELD_ID);
        }
    }

    public byte DateFirst
    {
        get
        {
            return base.GetByte(DATEFIRST_FIELD_ID);
        }
    }

    public byte[]? Status
    {
        get
        {
            return base.GetNullableBinary(STATUS_FIELD_ID);
        }
    }

    public int RequiredCursorOptions
    {
        get
        {
            return base.GetInt32(REQUIREDCURSOROPTIONS_FIELD_ID);
        }
    }

    public int AcceptableCursorOptions
    {
        get
        {
            return base.GetInt32(ACCEPTABLECURSOROPTIONS_FIELD_ID);
        }
    }

    public short MergeActionType
    {
        get
        {
            return base.GetInt16(MERGEACTIONTYPE_FIELD_ID);
        }
    }

    public int DefaultSchemaId
    {
        get
        {
            return base.GetInt32(DEFAULTSCHEMAID_FIELD_ID);
        }
    }

    public bool IsReplicationSpecific
    {
        get
        {
            return base.GetBoolean(ISREPLICATIONSPECIFIC_FIELD_ID);
        }
    }

    public byte[]? IsContained
    {
        get
        {
            return base.GetNullableBinary(ISCONTAINED_FIELD_ID);
        }
    }


    public Types.QueryContextSettingsDataType ToDataObject()
    {
        return new Types.QueryContextSettingsDataType(ContextSettingsId,
            SetOptions,
            LanguageId,
            DateFormat,
            DateFirst,
            Status,
            RequiredCursorOptions,
            AcceptableCursorOptions,
            MergeActionType,
            DefaultSchemaId,
            IsReplicationSpecific,
            IsContained);
    }

    public List<Types.QueryContextSettingsDataType> ToList()
    {
        var list = new List<Types.QueryContextSettingsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
