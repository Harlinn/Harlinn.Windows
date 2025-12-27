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

public class MessageTypeXmlSchemaCollectionUsagesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[message_type_xml_schema_collection_usages]";
    public const string TableName = "message_type_xml_schema_collection_usages";
    public const string ShortName = "mtxscu";
    public const string Sql = """
        SELECT
          mtxscu.[message_type_id],
          mtxscu.[xml_collection_id]
        FROM
          [sys].[message_type_xml_schema_collection_usages] mtxscu
        """;

    public const int MESSAGETYPEID_FIELD_ID = 0;
    public const int XMLCOLLECTIONID_FIELD_ID = 1;


    public MessageTypeXmlSchemaCollectionUsagesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public MessageTypeXmlSchemaCollectionUsagesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public MessageTypeXmlSchemaCollectionUsagesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int MessageTypeId
    {
        get
        {
            return base.GetInt32(MESSAGETYPEID_FIELD_ID);
        }
    }

    public int XmlCollectionId
    {
        get
        {
            return base.GetInt32(XMLCOLLECTIONID_FIELD_ID);
        }
    }


    public Types.MessageTypeXmlSchemaCollectionUsagesDataType ToDataObject()
    {
        return new Types.MessageTypeXmlSchemaCollectionUsagesDataType(MessageTypeId,
            XmlCollectionId);
    }

    public List<Types.MessageTypeXmlSchemaCollectionUsagesDataType> ToList()
    {
        var list = new List<Types.MessageTypeXmlSchemaCollectionUsagesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
