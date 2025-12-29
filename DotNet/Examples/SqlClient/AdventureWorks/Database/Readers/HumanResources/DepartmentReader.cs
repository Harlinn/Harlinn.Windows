using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.HumanResources;

public class DepartmentReader : IDisposable
{
    public const string QualifiedTableName = "[HumanResources].[Department]";
    public const string TableName = "Department";
    public const string ShortName = "d0";
    public const string Sql = """
        SELECT
          d0.[Departmentid],
          d0.[Name],
          d0.[Groupname],
          d0.[Modifieddate]
        FROM
          [HumanResources].[Department] d0
        """;

    public const int DEPARTMENTID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int GROUPNAME_FIELD_ID = 2;
    public const int MODIFIEDDATE_FIELD_ID = 3;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public DepartmentReader(SqlDataReader reader, bool ownsReader = false)
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

    public short Departmentid
    {
        get
        {
            return Reader.GetInt16(DEPARTMENTID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return Reader.GetString(NAME_FIELD_ID);
        }
    }

    public string Groupname
    {
        get
        {
            return Reader.GetString(GROUPNAME_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public Types.HumanResources.DepartmentDataType ToDataObject()
    {
        return new Types.HumanResources.DepartmentDataType(Departmentid,
            Name,
            Groupname,
            Modifieddate);
    }

    public List<Types.HumanResources.DepartmentDataType> ToList()
    {
        var list = new List<Types.HumanResources.DepartmentDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
