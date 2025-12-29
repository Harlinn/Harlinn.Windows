using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.Production;

public class ProductinventoryReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[ProductInventory]";
    public const string TableName = "ProductInventory";
    public const string ShortName = "p8";
    public const string Sql = """
        SELECT
          p8.[Productid],
          p8.[Locationid],
          p8.[Shelf],
          p8.[Bin],
          p8.[Quantity],
          p8.[Rowguid],
          p8.[Modifieddate]
        FROM
          [Production].[ProductInventory] p8
        """;

    public const int PRODUCTID_FIELD_ID = 0;
    public const int LOCATIONID_FIELD_ID = 1;
    public const int SHELF_FIELD_ID = 2;
    public const int BIN_FIELD_ID = 3;
    public const int QUANTITY_FIELD_ID = 4;
    public const int ROWGUID_FIELD_ID = 5;
    public const int MODIFIEDDATE_FIELD_ID = 6;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public ProductinventoryReader(SqlDataReader reader, bool ownsReader = false)
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

    public short Locationid
    {
        get
        {
            return Reader.GetInt16(LOCATIONID_FIELD_ID);
        }
    }

    public string Shelf
    {
        get
        {
            return Reader.GetString(SHELF_FIELD_ID);
        }
    }

    public byte Bin
    {
        get
        {
            return Reader.GetByte(BIN_FIELD_ID);
        }
    }

    public short Quantity
    {
        get
        {
            return Reader.GetInt16(QUANTITY_FIELD_ID);
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


    public Types.Production.ProductinventoryDataType ToDataObject()
    {
        return new Types.Production.ProductinventoryDataType(Productid,
            Locationid,
            Shelf,
            Bin,
            Quantity,
            Rowguid,
            Modifieddate);
    }

    public List<Types.Production.ProductinventoryDataType> ToList()
    {
        var list = new List<Types.Production.ProductinventoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
