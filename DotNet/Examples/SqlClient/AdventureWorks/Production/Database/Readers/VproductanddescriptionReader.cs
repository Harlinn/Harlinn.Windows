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

public class VproductanddescriptionReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[vProductAndDescription]";
    public const string TableName = "vProductAndDescription";
    public const string ShortName = "v7";
    public const string Sql = """
        SELECT
          v7.[Productid],
          v7.[Name],
          v7.[Productmodel],
          v7.[Cultureid],
          v7.[Description]
        FROM
          [Production].[vProductAndDescription] v7
        """;

    public const int PRODUCTID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int PRODUCTMODEL_FIELD_ID = 2;
    public const int CULTUREID_FIELD_ID = 3;
    public const int DESCRIPTION_FIELD_ID = 4;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VproductanddescriptionReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Productid
    {
        get
        {
            return Reader.GetInt32(PRODUCTID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public string Productmodel
    {
        get
        {
            return Reader.GetString(PRODUCTMODEL_FIELD_ID);
        }
    }

    public string Cultureid
    {
        get
        {
            return Reader.GetString(CULTUREID_FIELD_ID);
        }
    }

    public string Description
    {
        get
        {
            return Reader.GetString(DESCRIPTION_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.VproductanddescriptionDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.VproductanddescriptionDataType(Productid,
            Name,
            Productmodel,
            Cultureid,
            Description);
    }

    public List<AdventureWorks.Production.Types.VproductanddescriptionDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.VproductanddescriptionDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
