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

public class DmExecCachedPlansReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_cached_plans]";
    public const string TableName = "dm_exec_cached_plans";
    public const string ShortName = "decp";
    public const string Sql = """
        SELECT
          decp.[Bucketid],
          decp.[Refcounts],
          decp.[Usecounts],
          decp.[size_in_bytes],
          decp.[memory_object_address],
          decp.[Cacheobjtype],
          decp.[Objtype],
          decp.[plan_handle],
          decp.[pool_id],
          decp.[parent_plan_handle]
        FROM
          [sys].[dm_exec_cached_plans] decp
        """;

    public const int BUCKETID_FIELD_ID = 0;
    public const int REFCOUNTS_FIELD_ID = 1;
    public const int USECOUNTS_FIELD_ID = 2;
    public const int SIZEINBYTES_FIELD_ID = 3;
    public const int MEMORYOBJECTADDRESS_FIELD_ID = 4;
    public const int CACHEOBJTYPE_FIELD_ID = 5;
    public const int OBJTYPE_FIELD_ID = 6;
    public const int PLANHANDLE_FIELD_ID = 7;
    public const int POOLID_FIELD_ID = 8;
    public const int PARENTPLANHANDLE_FIELD_ID = 9;


    public DmExecCachedPlansReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecCachedPlansReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecCachedPlansReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Bucketid
    {
        get
        {
            return base.GetInt32(BUCKETID_FIELD_ID);
        }
    }

    public int Refcounts
    {
        get
        {
            return base.GetInt32(REFCOUNTS_FIELD_ID);
        }
    }

    public int Usecounts
    {
        get
        {
            return base.GetInt32(USECOUNTS_FIELD_ID);
        }
    }

    public int SizeInBytes
    {
        get
        {
            return base.GetInt32(SIZEINBYTES_FIELD_ID);
        }
    }

    public byte[] MemoryObjectAddress
    {
        get
        {
            return base.GetBinary(MEMORYOBJECTADDRESS_FIELD_ID);
        }
    }

    public string Cacheobjtype
    {
        get
        {
            return base.GetString(CACHEOBJTYPE_FIELD_ID);
        }
    }

    public string Objtype
    {
        get
        {
            return base.GetString(OBJTYPE_FIELD_ID);
        }
    }

    public byte[] PlanHandle
    {
        get
        {
            return base.GetBinary(PLANHANDLE_FIELD_ID);
        }
    }

    public int PoolId
    {
        get
        {
            return base.GetInt32(POOLID_FIELD_ID);
        }
    }

    public byte[]? ParentPlanHandle
    {
        get
        {
            return base.GetNullableBinary(PARENTPLANHANDLE_FIELD_ID);
        }
    }


    public Types.DmExecCachedPlansDataType ToDataObject()
    {
        return new Types.DmExecCachedPlansDataType(Bucketid,
            Refcounts,
            Usecounts,
            SizeInBytes,
            MemoryObjectAddress,
            Cacheobjtype,
            Objtype,
            PlanHandle,
            PoolId,
            ParentPlanHandle);
    }

    public List<Types.DmExecCachedPlansDataType> ToList()
    {
        var list = new List<Types.DmExecCachedPlansDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
