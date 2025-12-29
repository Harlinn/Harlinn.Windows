using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;

namespace AdventureWorks.Database.Readers.HumanResources;

public class EmployeeReader : IDisposable
{
    public const string QualifiedTableName = "[HumanResources].[Employee]";
    public const string TableName = "Employee";
    public const string ShortName = "e0";
    public const string Sql = """
        SELECT
          e0.[Businessentityid],
          e0.[Nationalidnumber],
          e0.[Loginid],
          e0.[Organizationnode],
          e0.[Organizationlevel],
          e0.[Jobtitle],
          e0.[Birthdate],
          e0.[Maritalstatus],
          e0.[Gender],
          e0.[Hiredate],
          e0.[Salariedflag],
          e0.[Vacationhours],
          e0.[Sickleavehours],
          e0.[Currentflag],
          e0.[Rowguid],
          e0.[Modifieddate]
        FROM
          [HumanResources].[Employee] e0
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int NATIONALIDNUMBER_FIELD_ID = 1;
    public const int LOGINID_FIELD_ID = 2;
    public const int ORGANIZATIONNODE_FIELD_ID = 3;
    public const int ORGANIZATIONLEVEL_FIELD_ID = 4;
    public const int JOBTITLE_FIELD_ID = 5;
    public const int BIRTHDATE_FIELD_ID = 6;
    public const int MARITALSTATUS_FIELD_ID = 7;
    public const int GENDER_FIELD_ID = 8;
    public const int HIREDATE_FIELD_ID = 9;
    public const int SALARIEDFLAG_FIELD_ID = 10;
    public const int VACATIONHOURS_FIELD_ID = 11;
    public const int SICKLEAVEHOURS_FIELD_ID = 12;
    public const int CURRENTFLAG_FIELD_ID = 13;
    public const int ROWGUID_FIELD_ID = 14;
    public const int MODIFIEDDATE_FIELD_ID = 15;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public EmployeeReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Nationalidnumber
    {
        get
        {
            return Reader.GetString(NATIONALIDNUMBER_FIELD_ID);
        }
    }

    public string Loginid
    {
        get
        {
            return Reader.GetString(LOGINID_FIELD_ID);
        }
    }

    public SqlHierarchyId? Organizationnode
    {
        get
        {
            return Reader.GetNullableSqlHierarchyId(ORGANIZATIONNODE_FIELD_ID);
        }
    }

    public short? Organizationlevel
    {
        get
        {
            return Reader.GetNullableInt16(ORGANIZATIONLEVEL_FIELD_ID);
        }
    }

    public string Jobtitle
    {
        get
        {
            return Reader.GetString(JOBTITLE_FIELD_ID);
        }
    }

    public DateTime Birthdate
    {
        get
        {
            return Reader.GetDateTime(BIRTHDATE_FIELD_ID);
        }
    }

    public string Maritalstatus
    {
        get
        {
            return Reader.GetString(MARITALSTATUS_FIELD_ID);
        }
    }

    public string Gender
    {
        get
        {
            return Reader.GetString(GENDER_FIELD_ID);
        }
    }

    public DateTime Hiredate
    {
        get
        {
            return Reader.GetDateTime(HIREDATE_FIELD_ID);
        }
    }

    public bool Salariedflag
    {
        get
        {
            return Reader.GetBoolean(SALARIEDFLAG_FIELD_ID);
        }
    }

    public short Vacationhours
    {
        get
        {
            return Reader.GetInt16(VACATIONHOURS_FIELD_ID);
        }
    }

    public short Sickleavehours
    {
        get
        {
            return Reader.GetInt16(SICKLEAVEHOURS_FIELD_ID);
        }
    }

    public bool Currentflag
    {
        get
        {
            return Reader.GetBoolean(CURRENTFLAG_FIELD_ID);
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


    public Types.HumanResources.EmployeeDataType ToDataObject()
    {
        return new Types.HumanResources.EmployeeDataType(Businessentityid,
            Nationalidnumber,
            Loginid,
            Organizationnode,
            Organizationlevel,
            Jobtitle,
            Birthdate,
            Maritalstatus,
            Gender,
            Hiredate,
            Salariedflag,
            Vacationhours,
            Sickleavehours,
            Currentflag,
            Rowguid,
            Modifieddate);
    }

    public List<Types.HumanResources.EmployeeDataType> ToList()
    {
        var list = new List<Types.HumanResources.EmployeeDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
