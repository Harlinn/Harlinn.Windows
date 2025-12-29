using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

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


    public Types.Production.ProductreviewDataType ToDataObject()
    {
        return new Types.Production.ProductreviewDataType(Productreviewid,
            Productid,
            Reviewername,
            Reviewdate,
            Emailaddress,
            Rating,
            Comments,
            Modifieddate);
    }

    public List<Types.Production.ProductreviewDataType> ToList()
    {
        var list = new List<Types.Production.ProductreviewDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
