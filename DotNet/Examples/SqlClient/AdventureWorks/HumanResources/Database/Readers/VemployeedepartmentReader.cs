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

namespace AdventureWorks.HumanResources.Database.Readers;

public class VemployeedepartmentReader : IDisposable
{
    public const string QualifiedTableName = "[HumanResources].[vEmployeeDepartment]";
    public const string TableName = "vEmployeeDepartment";
    public const string ShortName = "v0";
    public const string Sql = """
        SELECT
          v0.[Businessentityid],
          v0.[Title],
          v0.[Firstname],
          v0.[Middlename],
          v0.[Lastname],
          v0.[Suffix],
          v0.[Jobtitle],
          v0.[Department],
          v0.[Groupname],
          v0.[Startdate]
        FROM
          [HumanResources].[vEmployeeDepartment] v0
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int TITLE_FIELD_ID = 1;
    public const int FIRSTNAME_FIELD_ID = 2;
    public const int MIDDLENAME_FIELD_ID = 3;
    public const int LASTNAME_FIELD_ID = 4;
    public const int SUFFIX_FIELD_ID = 5;
    public const int JOBTITLE_FIELD_ID = 6;
    public const int DEPARTMENT_FIELD_ID = 7;
    public const int GROUPNAME_FIELD_ID = 8;
    public const int STARTDATE_FIELD_ID = 9;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public VemployeedepartmentReader(SqlDataReader reader, bool ownsReader = false)
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

    public string Jobtitle
    {
        get
        {
            return Reader.GetString(JOBTITLE_FIELD_ID);
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


    public AdventureWorks.HumanResources.Types.VemployeedepartmentDataType ToDataObject()
    {
        return new AdventureWorks.HumanResources.Types.VemployeedepartmentDataType(Businessentityid,
            Title,
            Firstname,
            Middlename,
            Lastname,
            Suffix,
            Jobtitle,
            Department,
            Groupname,
            Startdate);
    }

    public List<AdventureWorks.HumanResources.Types.VemployeedepartmentDataType> ToList()
    {
        var list = new List<AdventureWorks.HumanResources.Types.VemployeedepartmentDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
