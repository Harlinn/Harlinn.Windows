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

public class RegisteredSearchPropertiesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[registered_search_properties]";
    public const string TableName = "registered_search_properties";
    public const string ShortName = "rsp";
    public const string Sql = """
        SELECT
          rsp.[property_list_id],
          rsp.[property_id],
          rsp.[property_name],
          rsp.[property_set_guid],
          rsp.[property_int_id],
          rsp.[property_description]
        FROM
          [sys].[registered_search_properties] rsp
        """;

    public const int PROPERTYLISTID_FIELD_ID = 0;
    public const int PROPERTYID_FIELD_ID = 1;
    public const int PROPERTYNAME_FIELD_ID = 2;
    public const int PROPERTYSETGUID_FIELD_ID = 3;
    public const int PROPERTYINTID_FIELD_ID = 4;
    public const int PROPERTYDESCRIPTION_FIELD_ID = 5;


    public RegisteredSearchPropertiesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public RegisteredSearchPropertiesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public RegisteredSearchPropertiesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int PropertyListId
    {
        get
        {
            return base.GetInt32(PROPERTYLISTID_FIELD_ID);
        }
    }

    public int PropertyId
    {
        get
        {
            return base.GetInt32(PROPERTYID_FIELD_ID);
        }
    }

    public string PropertyName
    {
        get
        {
            return base.GetString(PROPERTYNAME_FIELD_ID);
        }
    }

    public Guid PropertySetGuid
    {
        get
        {
            return base.GetGuid(PROPERTYSETGUID_FIELD_ID);
        }
    }

    public int PropertyIntId
    {
        get
        {
            return base.GetInt32(PROPERTYINTID_FIELD_ID);
        }
    }

    public string? PropertyDescription
    {
        get
        {
            return base.GetNullableString(PROPERTYDESCRIPTION_FIELD_ID);
        }
    }


    public Types.RegisteredSearchPropertiesDataType ToDataObject()
    {
        return new Types.RegisteredSearchPropertiesDataType(PropertyListId,
            PropertyId,
            PropertyName,
            PropertySetGuid,
            PropertyIntId,
            PropertyDescription);
    }

    public List<Types.RegisteredSearchPropertiesDataType> ToList()
    {
        var list = new List<Types.RegisteredSearchPropertiesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
