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

public class SyscscontainersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syscscontainers]";
    public const string TableName = "syscscontainers";
    public const string ShortName = "s";
    public const string Sql = """
        SELECT
          s.[blob_container_id],
          s.[blob_container_url],
          s.[blob_container_type]
        FROM
          [sys].[syscscontainers] s
        """;

    public const int BLOBCONTAINERID_FIELD_ID = 0;
    public const int BLOBCONTAINERURL_FIELD_ID = 1;
    public const int BLOBCONTAINERTYPE_FIELD_ID = 2;


    public SyscscontainersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SyscscontainersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SyscscontainersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short BlobContainerId
    {
        get
        {
            return base.GetInt16(BLOBCONTAINERID_FIELD_ID);
        }
    }

    public string? BlobContainerUrl
    {
        get
        {
            return base.GetNullableString(BLOBCONTAINERURL_FIELD_ID);
        }
    }

    public byte? BlobContainerType
    {
        get
        {
            return base.GetNullableByte(BLOBCONTAINERTYPE_FIELD_ID);
        }
    }


    public Types.SyscscontainersDataType ToDataObject()
    {
        return new Types.SyscscontainersDataType(BlobContainerId,
            BlobContainerUrl,
            BlobContainerType);
    }

    public List<Types.SyscscontainersDataType> ToList()
    {
        var list = new List<Types.SyscscontainersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
