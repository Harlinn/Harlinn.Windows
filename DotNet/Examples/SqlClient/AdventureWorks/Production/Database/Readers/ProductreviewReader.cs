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

public class ProductreviewReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductReview]";
    public const string TableName = "ProductReview";
    public const string ShortName = "p15";
    public const string Sql = """
        SELECT
          p15.[Productreviewid],
          p15.[Productid],
          p15.[Reviewername],
          p15.[Reviewdate],
          p15.[Emailaddress],
          p15.[Rating],
          p15.[Comments],
          p15.[Modifieddate]
        FROM
          [Production].[ProductReview] p15
        """;

    public const int PRODUCTREVIEWID_FIELD_ID = 0;
    public const int PRODUCTID_FIELD_ID = 1;
    public const int REVIEWERNAME_FIELD_ID = 2;
    public const int REVIEWDATE_FIELD_ID = 3;
    public const int EMAILADDRESS_FIELD_ID = 4;
    public const int RATING_FIELD_ID = 5;
    public const int COMMENTS_FIELD_ID = 6;
    public const int MODIFIEDDATE_FIELD_ID = 7;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductreviewReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Productreviewid
    {
        get
        {
            return Reader.GetInt32(PRODUCTREVIEWID_FIELD_ID);
        }
    }

    public int Productid
    {
        get
        {
            return Reader.GetInt32(PRODUCTID_FIELD_ID);
        }
    }

    public string Reviewername
    {
        get
        {
            return Reader.GetString(REVIEWERNAME_FIELD_ID);
        }
    }

    public DateTime Reviewdate
    {
        get
        {
            return Reader.GetDateTime(REVIEWDATE_FIELD_ID);
        }
    }

    public string Emailaddress
    {
        get
        {
            return Reader.GetString(EMAILADDRESS_FIELD_ID);
        }
    }

    public int Rating
    {
        get
        {
            return Reader.GetInt32(RATING_FIELD_ID);
        }
    }

    public string? Comments
    {
        get
        {
            return Reader.GetNullableString(COMMENTS_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.ProductreviewDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.ProductreviewDataType(Productreviewid,
            Productid,
            Reviewername,
            Reviewdate,
            Emailaddress,
            Rating,
            Comments,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.ProductreviewDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.ProductreviewDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
