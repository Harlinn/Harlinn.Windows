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

public class FiletableSystemDefinedObjectsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[filetable_system_defined_objects]";
    public const string TableName = "filetable_system_defined_objects";
    public const string ShortName = "fsdo";
    public const string Sql = """
        SELECT
          fsdo.[object_id],
          fsdo.[parent_object_id]
        FROM
          [sys].[filetable_system_defined_objects] fsdo
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int PARENTOBJECTID_FIELD_ID = 1;


    public FiletableSystemDefinedObjectsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FiletableSystemDefinedObjectsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FiletableSystemDefinedObjectsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int ParentObjectId
    {
        get
        {
            return base.GetInt32(PARENTOBJECTID_FIELD_ID);
        }
    }


    public Types.FiletableSystemDefinedObjectsDataType ToDataObject()
    {
        return new Types.FiletableSystemDefinedObjectsDataType(ObjectId,
            ParentObjectId);
    }

    public List<Types.FiletableSystemDefinedObjectsDataType> ToList()
    {
        var list = new List<Types.FiletableSystemDefinedObjectsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
