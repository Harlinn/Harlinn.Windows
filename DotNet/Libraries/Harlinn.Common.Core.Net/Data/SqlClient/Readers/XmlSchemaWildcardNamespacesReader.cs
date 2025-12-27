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

public class XmlSchemaWildcardNamespacesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[xml_schema_wildcard_namespaces]";
    public const string TableName = "xml_schema_wildcard_namespaces";
    public const string ShortName = "xswn";
    public const string Sql = """
        SELECT
          xswn.[xml_component_id],
          xswn.[Namespace]
        FROM
          [sys].[xml_schema_wildcard_namespaces] xswn
        """;

    public const int XMLCOMPONENTID_FIELD_ID = 0;
    public const int NAMESPACE_FIELD_ID = 1;


    public XmlSchemaWildcardNamespacesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaWildcardNamespacesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaWildcardNamespacesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int XmlComponentId
    {
        get
        {
            return base.GetInt32(XMLCOMPONENTID_FIELD_ID);
        }
    }

    public string Namespace
    {
        get
        {
            return base.GetString(NAMESPACE_FIELD_ID);
        }
    }


    public Types.XmlSchemaWildcardNamespacesDataType ToDataObject()
    {
        return new Types.XmlSchemaWildcardNamespacesDataType(XmlComponentId,
            Namespace);
    }

    public List<Types.XmlSchemaWildcardNamespacesDataType> ToList()
    {
        var list = new List<Types.XmlSchemaWildcardNamespacesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
