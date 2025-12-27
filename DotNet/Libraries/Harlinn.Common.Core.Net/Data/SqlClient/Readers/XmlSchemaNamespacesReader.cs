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

public class XmlSchemaNamespacesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[xml_schema_namespaces]";
    public const string TableName = "xml_schema_namespaces";
    public const string ShortName = "xsn";
    public const string Sql = """
        SELECT
          xsn.[xml_collection_id],
          xsn.[Name],
          xsn.[xml_namespace_id]
        FROM
          [sys].[xml_schema_namespaces] xsn
        """;

    public const int XMLCOLLECTIONID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int XMLNAMESPACEID_FIELD_ID = 2;


    public XmlSchemaNamespacesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaNamespacesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaNamespacesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public int XmlNamespaceId
    {
        get
        {
            return base.GetInt32(XMLNAMESPACEID_FIELD_ID);
        }
    }


    public Types.XmlSchemaNamespacesDataType ToDataObject()
    {
        return new Types.XmlSchemaNamespacesDataType(XmlCollectionId,
            Name,
            XmlNamespaceId);
    }

    public List<Types.XmlSchemaNamespacesDataType> ToList()
    {
        var list = new List<Types.XmlSchemaNamespacesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
