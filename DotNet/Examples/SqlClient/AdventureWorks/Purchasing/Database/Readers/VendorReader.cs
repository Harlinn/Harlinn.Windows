using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Purchasing.Database.Readers;

public class VendorReader : IDisposable
{
    public const string QualifiedTableName = "[Purchasing].[Vendor]";
    public const string TableName = "Vendor";
    public const string ShortName = "v10";
    public const string Sql = """
        SELECT
          v10.[Businessentityid],
          v10.[Accountnumber],
          v10.[Name],
          v10.[Creditrating],
          v10.[Preferredvendorstatus],
          v10.[Activeflag],
          v10.[Purchasingwebserviceurl],
          v10.[Modifieddate]
        FROM
          [Purchasing].[Vendor] v10
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int ACCOUNTNUMBER_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int CREDITRATING_FIELD_ID = 3;
    public const int PREFERREDVENDORSTATUS_FIELD_ID = 4;
    public const int ACTIVEFLAG_FIELD_ID = 5;
    public const int PURCHASINGWEBSERVICEURL_FIELD_ID = 6;
    public const int MODIFIEDDATE_FIELD_ID = 7;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VendorReader(SqlDataReader reader, bool ownsReader = false)
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

    public int Businessentityid
    {
        get
        {
            return Reader.GetInt32(BUSINESSENTITYID_FIELD_ID);
        }
    }

    public string Accountnumber
    {
        get
        {
            return Reader.GetString(ACCOUNTNUMBER_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public byte Creditrating
    {
        get
        {
            return Reader.GetByte(CREDITRATING_FIELD_ID);
        }
    }

    public bool Preferredvendorstatus
    {
        get
        {
            return Reader.GetBoolean(PREFERREDVENDORSTATUS_FIELD_ID);
        }
    }

    public bool Activeflag
    {
        get
        {
            return Reader.GetBoolean(ACTIVEFLAG_FIELD_ID);
        }
    }

    public string? Purchasingwebserviceurl
    {
        get
        {
            return Reader.GetNullableString(PURCHASINGWEBSERVICEURL_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Purchasing.Types.VendorDataType ToDataObject()
    {
        return new AdventureWorks.Purchasing.Types.VendorDataType(Businessentityid,
            Accountnumber,
            Name,
            Creditrating,
            Preferredvendorstatus,
            Activeflag,
            Purchasingwebserviceurl,
            Modifieddate);
    }

    public List<AdventureWorks.Purchasing.Types.VendorDataType> ToList()
    {
        var list = new List<AdventureWorks.Purchasing.Types.VendorDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
