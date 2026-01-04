using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Production.Database.Readers;

public class WorkorderReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[WorkOrder]";
    public const string TableName = "WorkOrder";
    public const string ShortName = "w";
    public const string Sql = """
        SELECT
          w.[Workorderid],
          w.[Productid],
          w.[Orderqty],
          w.[Stockedqty],
          w.[Scrappedqty],
          w.[Startdate],
          w.[Enddate],
          w.[Duedate],
          w.[Scrapreasonid],
          w.[Modifieddate]
        FROM
          [Production].[WorkOrder] w
        """;

    public const int WORKORDERID_FIELD_ID = 0;
    public const int PRODUCTID_FIELD_ID = 1;
    public const int ORDERQTY_FIELD_ID = 2;
    public const int STOCKEDQTY_FIELD_ID = 3;
    public const int SCRAPPEDQTY_FIELD_ID = 4;
    public const int STARTDATE_FIELD_ID = 5;
    public const int ENDDATE_FIELD_ID = 6;
    public const int DUEDATE_FIELD_ID = 7;
    public const int SCRAPREASONID_FIELD_ID = 8;
    public const int MODIFIEDDATE_FIELD_ID = 9;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public WorkorderReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Workorderid
    {
        get
        {
            return Reader.GetInt32(WORKORDERID_FIELD_ID);
        }
    }

    public int Productid
    {
        get
        {
            return Reader.GetInt32(PRODUCTID_FIELD_ID);
        }
    }

    public int Orderqty
    {
        get
        {
            return Reader.GetInt32(ORDERQTY_FIELD_ID);
        }
    }

    public int Stockedqty
    {
        get
        {
            return Reader.GetInt32(STOCKEDQTY_FIELD_ID);
        }
    }

    public short Scrappedqty
    {
        get
        {
            return Reader.GetInt16(SCRAPPEDQTY_FIELD_ID);
        }
    }

    public DateTime Startdate
    {
        get
        {
            return Reader.GetDateTime(STARTDATE_FIELD_ID);
        }
    }

    public DateTime? Enddate
    {
        get
        {
            return Reader.GetNullableDateTime(ENDDATE_FIELD_ID);
        }
    }

    public DateTime Duedate
    {
        get
        {
            return Reader.GetDateTime(DUEDATE_FIELD_ID);
        }
    }

    public short? Scrapreasonid
    {
        get
        {
            return Reader.GetNullableInt16(SCRAPREASONID_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.WorkorderDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.WorkorderDataType(Workorderid,
            Productid,
            Orderqty,
            Stockedqty,
            Scrappedqty,
            Startdate,
            Enddate,
            Duedate,
            Scrapreasonid,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.WorkorderDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.WorkorderDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
