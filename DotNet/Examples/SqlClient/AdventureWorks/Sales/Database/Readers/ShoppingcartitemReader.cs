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

namespace AdventureWorks.Sales.Database.Readers;

public class ShoppingcartitemReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[ShoppingCartItem]";
    public const string TableName = "ShoppingCartItem";
    public const string ShortName = "s12";
    public const string Sql = """
        SELECT
          s12.[Shoppingcartitemid],
          s12.[Shoppingcartid],
          s12.[Quantity],
          s12.[Productid],
          s12.[Datecreated],
          s12.[Modifieddate]
        FROM
          [Sales].[ShoppingCartItem] s12
        """;

    public const int SHOPPINGCARTITEMID_FIELD_ID = 0;
    public const int SHOPPINGCARTID_FIELD_ID = 1;
    public const int QUANTITY_FIELD_ID = 2;
    public const int PRODUCTID_FIELD_ID = 3;
    public const int DATECREATED_FIELD_ID = 4;
    public const int MODIFIEDDATE_FIELD_ID = 5;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ShoppingcartitemReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Shoppingcartitemid
    {
        get
        {
            return Reader.GetInt32(SHOPPINGCARTITEMID_FIELD_ID);
        }
    }

    public string Shoppingcartid
    {
        get
        {
            return Reader.GetString(SHOPPINGCARTID_FIELD_ID);
        }
    }

    public int Quantity
    {
        get
        {
            return Reader.GetInt32(QUANTITY_FIELD_ID);
        }
    }

    public int Productid
    {
        get
        {
            return Reader.GetInt32(PRODUCTID_FIELD_ID);
        }
    }

    public DateTime Datecreated
    {
        get
        {
            return Reader.GetDateTime(DATECREATED_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Sales.Types.ShoppingcartitemDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.ShoppingcartitemDataType(Shoppingcartitemid,
            Shoppingcartid,
            Quantity,
            Productid,
            Datecreated,
            Modifieddate);
    }

    public List<AdventureWorks.Sales.Types.ShoppingcartitemDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.ShoppingcartitemDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
