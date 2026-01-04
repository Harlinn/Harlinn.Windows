using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Sales.Database.Readers;

public class SpecialofferReader : IDisposable
{
    public const string QualifiedTableName = "[Sales].[SpecialOffer]";
    public const string TableName = "SpecialOffer";
    public const string ShortName = "s13";
    public const string Sql = """
        SELECT
          s13.[Specialofferid],
          s13.[Description],
          s13.[Discountpct],
          s13.[Type],
          s13.[Category],
          s13.[Startdate],
          s13.[Enddate],
          s13.[Minqty],
          s13.[Maxqty],
          s13.[Rowguid],
          s13.[Modifieddate]
        FROM
          [Sales].[SpecialOffer] s13
        """;

    public const int SPECIALOFFERID_FIELD_ID = 0;
    public const int DESCRIPTION_FIELD_ID = 1;
    public const int DISCOUNTPCT_FIELD_ID = 2;
    public const int TYPE_FIELD_ID = 3;
    public const int CATEGORY_FIELD_ID = 4;
    public const int STARTDATE_FIELD_ID = 5;
    public const int ENDDATE_FIELD_ID = 6;
    public const int MINQTY_FIELD_ID = 7;
    public const int MAXQTY_FIELD_ID = 8;
    public const int ROWGUID_FIELD_ID = 9;
    public const int MODIFIEDDATE_FIELD_ID = 10;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public SpecialofferReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Specialofferid
    {
        get
        {
            return Reader.GetInt32(SPECIALOFFERID_FIELD_ID);
        }
    }

    public string Description
    {
        get
        {
            return Reader.GetString(DESCRIPTION_FIELD_ID);
        }
    }

    public decimal Discountpct
    {
        get
        {
            return Reader.GetDecimal(DISCOUNTPCT_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return Reader.GetString(TYPE_FIELD_ID);
        }
    }

    public string Category
    {
        get
        {
            return Reader.GetString(CATEGORY_FIELD_ID);
        }
    }

    public DateTime Startdate
    {
        get
        {
            return Reader.GetDateTime(STARTDATE_FIELD_ID);
        }
    }

    public DateTime Enddate
    {
        get
        {
            return Reader.GetDateTime(ENDDATE_FIELD_ID);
        }
    }

    public int Minqty
    {
        get
        {
            return Reader.GetInt32(MINQTY_FIELD_ID);
        }
    }

    public int? Maxqty
    {
        get
        {
            return Reader.GetNullableInt32(MAXQTY_FIELD_ID);
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


    public AdventureWorks.Sales.Types.SpecialofferDataType ToDataObject()
    {
        return new AdventureWorks.Sales.Types.SpecialofferDataType(Specialofferid,
            Description,
            Discountpct,
            Type,
            Category,
            Startdate,
            Enddate,
            Minqty,
            Maxqty,
            Rowguid,
            Modifieddate);
    }

    public List<AdventureWorks.Sales.Types.SpecialofferDataType> ToList()
    {
        var list = new List<AdventureWorks.Sales.Types.SpecialofferDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
