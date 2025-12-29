using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.HumanResources;

public class VemployeedepartmenthistoryReader : IDisposable
{
    public const string QualifiedTableName = "[HumanResources].[vEmployeeDepartmentHistory]";
    public const string TableName = "vEmployeeDepartmentHistory";
    public const string ShortName = "v1";
    public const string Sql = """
        SELECT
          v1.[Businessentityid],
          v1.[Title],
          v1.[Firstname],
          v1.[Middlename],
          v1.[Lastname],
          v1.[Suffix],
          v1.[Shift],
          v1.[Department],
          v1.[Groupname],
          v1.[Startdate],
          v1.[Enddate]
        FROM
          [HumanResources].[vEmployeeDepartmentHistory] v1
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int TITLE_FIELD_ID = 1;
    public const int FIRSTNAME_FIELD_ID = 2;
    public const int MIDDLENAME_FIELD_ID = 3;
    public const int LASTNAME_FIELD_ID = 4;
    public const int SUFFIX_FIELD_ID = 5;
    public const int SHIFT_FIELD_ID = 6;
    public const int DEPARTMENT_FIELD_ID = 7;
    public const int GROUPNAME_FIELD_ID = 8;
    public const int STARTDATE_FIELD_ID = 9;
    public const int ENDDATE_FIELD_ID = 10;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VemployeedepartmenthistoryReader(SqlDataReader reader, bool ownsReader = false)
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

    public string? Title
    {
        get
        {
            return Reader.GetNullableString(TITLE_FIELD_ID);
        }
    }

    public string Firstname
    {
        get
        {
            return Reader.GetString(FIRSTNAME_FIELD_ID);
        }
    }

    public string? Middlename
    {
        get
        {
            return Reader.GetNullableString(MIDDLENAME_FIELD_ID);
        }
    }

    public string Lastname
    {
        get
        {
            return Reader.GetString(LASTNAME_FIELD_ID);
        }
    }

    public string? Suffix
    {
        get
        {
            return Reader.GetNullableString(SUFFIX_FIELD_ID);
        }
    }

    public string Shift
    {
        get
        {
            return Reader.GetString(SHIFT_FIELD_ID);
        }
    }

    public string Department
    {
        get
        {
            return Reader.GetString(DEPARTMENT_FIELD_ID);
        }
    }

    public string Groupname
    {
        get
        {
            return Reader.GetString(GROUPNAME_FIELD_ID);
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


    public Types.HumanResources.VemployeedepartmenthistoryDataType ToDataObject()
    {
        return new Types.HumanResources.VemployeedepartmenthistoryDataType(Businessentityid,
            Title,
            Firstname,
            Middlename,
            Lastname,
            Suffix,
            Shift,
            Department,
            Groupname,
            Startdate,
            Enddate);
    }

    public List<Types.HumanResources.VemployeedepartmenthistoryDataType> ToList()
    {
        var list = new List<Types.HumanResources.VemployeedepartmenthistoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
