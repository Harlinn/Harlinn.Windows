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

public class ServiceMessageTypesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[service_message_types]";
    public const string TableName = "service_message_types";
    public const string ShortName = "smt";
    public const string Sql = """
        SELECT
          smt.[Name],
          smt.[message_type_id],
          smt.[principal_id],
          smt.[Validation],
          smt.[validation_desc],
          smt.[xml_collection_id]
        FROM
          [sys].[service_message_types] smt
        """;

    public const int NAME_FIELD_ID = 0;
    public const int MESSAGETYPEID_FIELD_ID = 1;
    public const int PRINCIPALID_FIELD_ID = 2;
    public const int VALIDATION_FIELD_ID = 3;
    public const int VALIDATIONDESC_FIELD_ID = 4;
    public const int XMLCOLLECTIONID_FIELD_ID = 5;


    public ServiceMessageTypesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServiceMessageTypesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServiceMessageTypesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int MessageTypeId
    {
        get
        {
            return base.GetInt32(MESSAGETYPEID_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public string Validation
    {
        get
        {
            return base.GetString(VALIDATION_FIELD_ID);
        }
    }

    public string? ValidationDesc
    {
        get
        {
            return base.GetNullableString(VALIDATIONDESC_FIELD_ID);
        }
    }

    public int? XmlCollectionId
    {
        get
        {
            return base.GetNullableInt32(XMLCOLLECTIONID_FIELD_ID);
        }
    }


    public Types.ServiceMessageTypesDataType ToDataObject()
    {
        return new Types.ServiceMessageTypesDataType(Name,
            MessageTypeId,
            PrincipalId,
            Validation,
            ValidationDesc,
            XmlCollectionId);
    }

    public List<Types.ServiceMessageTypesDataType> ToList()
    {
        var list = new List<Types.ServiceMessageTypesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
