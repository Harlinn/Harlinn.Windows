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

public class XmlSchemaCollectionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[xml_schema_collections]";
    public const string TableName = "xml_schema_collections";
    public const string ShortName = "xsc";
    public const string Sql = """
        SELECT
          xsc.[xml_collection_id],
          xsc.[schema_id],
          xsc.[principal_id],
          xsc.[Name],
          xsc.[create_date],
          xsc.[modify_date]
        FROM
          [sys].[xml_schema_collections] xsc
        """;

    public const int XMLCOLLECTIONID_FIELD_ID = 0;
    public const int SCHEMAID_FIELD_ID = 1;
    public const int PRINCIPALID_FIELD_ID = 2;
    public const int NAME_FIELD_ID = 3;
    public const int CREATEDATE_FIELD_ID = 4;
    public const int MODIFYDATE_FIELD_ID = 5;


    public XmlSchemaCollectionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaCollectionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaCollectionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int XmlCollectionId
    {
        get
        {
            return base.GetInt32(XMLCOLLECTIONID_FIELD_ID);
        }
    }

    public int SchemaId
    {
        get
        {
            return base.GetInt32(SCHEMAID_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public DateTime CreateDate
    {
        get
        {
            return base.GetDateTime(CREATEDATE_FIELD_ID);
        }
    }

    public DateTime ModifyDate
    {
        get
        {
            return base.GetDateTime(MODIFYDATE_FIELD_ID);
        }
    }


    public Types.XmlSchemaCollection ToDataObject()
    {
        return new Types.XmlSchemaCollection(XmlCollectionId,
            SchemaId,
            PrincipalId,
            Name,
            CreateDate,
            ModifyDate);
    }

    public List<Types.XmlSchemaCollection> ToList()
    {
        var list = new List<Types.XmlSchemaCollection>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
