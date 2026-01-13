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
using System.Data.SqlTypes;

namespace AdventureWorks.Production.Database.Readers;

public class ProductsubcategoryReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductSubcategory]";
    public const string TableName = "ProductSubcategory";
    public const string ShortName = "p16";
    public const string Sql = """
        SELECT
          p16.[Productsubcategoryid],
          p16.[Productcategoryid],
          p16.[Name],
          p16.[Rowguid],
          p16.[Modifieddate]
        FROM
          [Production].[ProductSubcategory] p16
        """;

    public const int PRODUCTSUBCATEGORYID_FIELD_ID = 0;
    public const int PRODUCTCATEGORYID_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int ROWGUID_FIELD_ID = 3;
    public const int MODIFIEDDATE_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductsubcategoryReader(SqlDataReader reader, bool ownsReader = false)
    {
        _reader = reader;
        _ownsReader = ownsReader;
    }

    public SqlDataReader Reader => _reader;

    public void Dispose()
    {
        if (_ownsReader)
        {
            ((IDisposable)_reader).Dispose();
        }
    }

    public bool Read()
    {
        return _reader.Read();
    }

    public int Productsubcategoryid
    {
        get
        {
            return Reader.GetInt32(PRODUCTSUBCATEGORYID_FIELD_ID);
        }
    }

    public int Productcategoryid
    {
        get
        {
            return Reader.GetInt32(PRODUCTCATEGORYID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public Guid Rowguid
    {
        get
        {
            return Reader.GetGuid(ROWGUID_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.ProductsubcategoryDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.ProductsubcategoryDataType(Productsubcategoryid,
            Productcategoryid,
            Name,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.ProductsubcategoryDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.ProductsubcategoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
