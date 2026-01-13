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

public class DmHadrAutoPageRepairReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_auto_page_repair]";
    public const string TableName = "dm_hadr_auto_page_repair";
    public const string ShortName = "dhapr";
    public const string Sql = """
        SELECT
          dhapr.[database_id],
          dhapr.[file_id],
          dhapr.[page_id],
          dhapr.[error_type],
          dhapr.[page_status],
          dhapr.[modification_time]
        FROM
          [sys].[dm_hadr_auto_page_repair] dhapr
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int FILEID_FIELD_ID = 1;
    public const int PAGEID_FIELD_ID = 2;
    public const int ERRORTYPE_FIELD_ID = 3;
    public const int PAGESTATUS_FIELD_ID = 4;
    public const int MODIFICATIONTIME_FIELD_ID = 5;


    public DmHadrAutoPageRepairReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrAutoPageRepairReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrAutoPageRepairReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public int FileId
    {
        get
        {
            return base.GetInt32(FILEID_FIELD_ID);
        }
    }

    public long PageId
    {
        get
        {
            return base.GetInt64(PAGEID_FIELD_ID);
        }
    }

    public short ErrorType
    {
        get
        {
            return base.GetInt16(ERRORTYPE_FIELD_ID);
        }
    }

    public byte PageStatus
    {
        get
        {
            return base.GetByte(PAGESTATUS_FIELD_ID);
        }
    }

    public DateTime ModificationTime
    {
        get
        {
            return base.GetDateTime(MODIFICATIONTIME_FIELD_ID);
        }
    }


    public Types.DmHadrAutoPageRepairDataType ToDataObject()
    {
        return new Types.DmHadrAutoPageRepairDataType(DatabaseId,
            FileId,
            PageId,
            ErrorType,
            PageStatus,
            ModificationTime);
    }

    public List<Types.DmHadrAutoPageRepairDataType> ToList()
    {
        var list = new List<Types.DmHadrAutoPageRepairDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
