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

public class RegisteredSearchPropertyListsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[registered_search_property_lists]";
    public const string TableName = "registered_search_property_lists";
    public const string ShortName = "rspl";
    public const string Sql = """
        SELECT
          rspl.[property_list_id],
          rspl.[Name],
          rspl.[create_date],
          rspl.[modify_date],
          rspl.[principal_id]
        FROM
          [sys].[registered_search_property_lists] rspl
        """;

    public const int PROPERTYLISTID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int CREATEDATE_FIELD_ID = 2;
    public const int MODIFYDATE_FIELD_ID = 3;
    public const int PRINCIPALID_FIELD_ID = 4;


    public RegisteredSearchPropertyListsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public RegisteredSearchPropertyListsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public RegisteredSearchPropertyListsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }


    public Types.RegisteredSearchPropertyListsDataType ToDataObject()
    {
        return new Types.RegisteredSearchPropertyListsDataType(PropertyListId,
            Name,
            CreateDate,
            ModifyDate,
            PrincipalId);
    }

    public List<Types.RegisteredSearchPropertyListsDataType> ToList()
    {
        var list = new List<Types.RegisteredSearchPropertyListsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
