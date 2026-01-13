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

public class ProductphotoReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductPhoto]";
    public const string TableName = "ProductPhoto";
    public const string ShortName = "p13";
    public const string Sql = """
        SELECT
          p13.[Productphotoid],
          p13.[Thumbnailphoto],
          p13.[Thumbnailphotofilename],
          p13.[Largephoto],
          p13.[Largephotofilename],
          p13.[Modifieddate]
        FROM
          [Production].[ProductPhoto] p13
        """;

    public const int PRODUCTPHOTOID_FIELD_ID = 0;
    public const int THUMBNAILPHOTO_FIELD_ID = 1;
    public const int THUMBNAILPHOTOFILENAME_FIELD_ID = 2;
    public const int LARGEPHOTO_FIELD_ID = 3;
    public const int LARGEPHOTOFILENAME_FIELD_ID = 4;
    public const int MODIFIEDDATE_FIELD_ID = 5;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductphotoReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Productphotoid
    {
        get
        {
            return Reader.GetInt32(PRODUCTPHOTOID_FIELD_ID);
        }
    }

    public byte[]? Thumbnailphoto
    {
        get
        {
            return Reader.GetNullableBinary(THUMBNAILPHOTO_FIELD_ID);
        }
    }

    public string? Thumbnailphotofilename
    {
        get
        {
            return Reader.GetNullableString(THUMBNAILPHOTOFILENAME_FIELD_ID);
        }
    }

    public byte[]? Largephoto
    {
        get
        {
            return Reader.GetNullableBinary(LARGEPHOTO_FIELD_ID);
        }
    }

    public string? Largephotofilename
    {
        get
        {
            return Reader.GetNullableString(LARGEPHOTOFILENAME_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.ProductphotoDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.ProductphotoDataType(Productphotoid,
            Thumbnailphoto,
            Thumbnailphotofilename,
            Largephoto,
            Largephotofilename,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.ProductphotoDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.ProductphotoDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
