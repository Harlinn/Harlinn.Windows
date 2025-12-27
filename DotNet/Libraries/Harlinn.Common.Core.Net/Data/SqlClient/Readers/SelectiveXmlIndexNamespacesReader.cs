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

public class SelectiveXmlIndexNamespacesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[selective_xml_index_namespaces]";
    public const string TableName = "selective_xml_index_namespaces";
    public const string ShortName = "sxin";
    public const string Sql = """
        SELECT
          sxin.[object_id],
          sxin.[index_id],
          sxin.[is_default_uri],
          sxin.[Uri],
          sxin.[Prefix]
        FROM
          [sys].[selective_xml_index_namespaces] sxin
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int INDEXID_FIELD_ID = 1;
    public const int ISDEFAULTURI_FIELD_ID = 2;
    public const int URI_FIELD_ID = 3;
    public const int PREFIX_FIELD_ID = 4;


    public SelectiveXmlIndexNamespacesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SelectiveXmlIndexNamespacesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SelectiveXmlIndexNamespacesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int IndexId
    {
        get
        {
            return base.GetInt32(INDEXID_FIELD_ID);
        }
    }

    public bool? IsDefaultUri
    {
        get
        {
            return base.GetNullableBoolean(ISDEFAULTURI_FIELD_ID);
        }
    }

    public string? Uri
    {
        get
        {
            return base.GetNullableString(URI_FIELD_ID);
        }
    }

    public string? Prefix
    {
        get
        {
            return base.GetNullableString(PREFIX_FIELD_ID);
        }
    }


    public Types.SelectiveXmlIndexNamespacesDataType ToDataObject()
    {
        return new Types.SelectiveXmlIndexNamespacesDataType(ObjectId,
            IndexId,
            IsDefaultUri,
            Uri,
            Prefix);
    }

    public List<Types.SelectiveXmlIndexNamespacesDataType> ToList()
    {
        var list = new List<Types.SelectiveXmlIndexNamespacesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
