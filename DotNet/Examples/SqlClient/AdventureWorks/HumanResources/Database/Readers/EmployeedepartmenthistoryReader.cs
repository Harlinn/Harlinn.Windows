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

public class EmployeedepartmenthistoryReader : IDisposable
{
    public const string QualifiedTableName = "[HumanResources].[EmployeeDepartmentHistory]";
    public const string TableName = "EmployeeDepartmentHistory";
    public const string ShortName = "e1";
    public const string Sql = """
        SELECT
          e1.[Businessentityid],
          e1.[Departmentid],
          e1.[Shiftid],
          e1.[Startdate],
          e1.[Enddate],
          e1.[Modifieddate]
        FROM
          [HumanResources].[EmployeeDepartmentHistory] e1
        """;

    public const int BUSINESSENTITYID_FIELD_ID = 0;
    public const int DEPARTMENTID_FIELD_ID = 1;
    public const int SHIFTID_FIELD_ID = 2;
    public const int STARTDATE_FIELD_ID = 3;
    public const int ENDDATE_FIELD_ID = 4;
    public const int MODIFIEDDATE_FIELD_ID = 5;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public EmployeedepartmenthistoryReader(SqlDataReader reader, bool ownsReader = false)
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

    public short Departmentid
    {
        get
        {
            return Reader.GetInt16(DEPARTMENTID_FIELD_ID);
        }
    }

    public byte Shiftid
    {
        get
        {
            return Reader.GetByte(SHIFTID_FIELD_ID);
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

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.HumanResources.Types.EmployeedepartmenthistoryDataType ToDataObject()
    {
        return new AdventureWorks.HumanResources.Types.EmployeedepartmenthistoryDataType(Businessentityid,
            Departmentid,
            Shiftid,
            Startdate,
            Enddate,
            Modifieddate);
    }

    public List<AdventureWorks.HumanResources.Types.EmployeedepartmenthistoryDataType> ToList()
    {
        var list = new List<AdventureWorks.HumanResources.Types.EmployeedepartmenthistoryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
