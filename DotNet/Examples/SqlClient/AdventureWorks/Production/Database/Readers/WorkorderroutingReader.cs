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

namespace AdventureWorks.Production.Database.Readers;

public class WorkorderroutingReader : IDisposable
{
    public const string QualifiedTableName = "[Production].[WorkOrderRouting]";
    public const string TableName = "WorkOrderRouting";
    public const string ShortName = "w0";
    public const string Sql = """
        SELECT
          w0.[Workorderid],
          w0.[Productid],
          w0.[Operationsequence],
          w0.[Locationid],
          w0.[Scheduledstartdate],
          w0.[Scheduledenddate],
          w0.[Actualstartdate],
          w0.[Actualenddate],
          w0.[Actualresourcehrs],
          w0.[Plannedcost],
          w0.[Actualcost],
          w0.[Modifieddate]
        FROM
          [Production].[WorkOrderRouting] w0
        """;

    public const int WORKORDERID_FIELD_ID = 0;
    public const int PRODUCTID_FIELD_ID = 1;
    public const int OPERATIONSEQUENCE_FIELD_ID = 2;
    public const int LOCATIONID_FIELD_ID = 3;
    public const int SCHEDULEDSTARTDATE_FIELD_ID = 4;
    public const int SCHEDULEDENDDATE_FIELD_ID = 5;
    public const int ACTUALSTARTDATE_FIELD_ID = 6;
    public const int ACTUALENDDATE_FIELD_ID = 7;
    public const int ACTUALRESOURCEHRS_FIELD_ID = 8;
    public const int PLANNEDCOST_FIELD_ID = 9;
    public const int ACTUALCOST_FIELD_ID = 10;
    public const int MODIFIEDDATE_FIELD_ID = 11;

    readonly SqlDataReader _reader;
    readonly bool _ownsReader;

    public WorkorderroutingReader(SqlDataReader reader, bool ownsReader = false)
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

    public short Operationsequence
    {
        get
        {
            return Reader.GetInt16(OPERATIONSEQUENCE_FIELD_ID);
        }
    }

    public short Locationid
    {
        get
        {
            return Reader.GetInt16(LOCATIONID_FIELD_ID);
        }
    }

    public DateTime Scheduledstartdate
    {
        get
        {
            return Reader.GetDateTime(SCHEDULEDSTARTDATE_FIELD_ID);
        }
    }

    public DateTime Scheduledenddate
    {
        get
        {
            return Reader.GetDateTime(SCHEDULEDENDDATE_FIELD_ID);
        }
    }

    public DateTime? Actualstartdate
    {
        get
        {
            return Reader.GetNullableDateTime(ACTUALSTARTDATE_FIELD_ID);
        }
    }

    public DateTime? Actualenddate
    {
        get
        {
            return Reader.GetNullableDateTime(ACTUALENDDATE_FIELD_ID);
        }
    }

    public decimal? Actualresourcehrs
    {
        get
        {
            return Reader.GetNullableDecimal(ACTUALRESOURCEHRS_FIELD_ID);
        }
    }

    public decimal Plannedcost
    {
        get
        {
            return Reader.GetDecimal(PLANNEDCOST_FIELD_ID);
        }
    }

    public decimal? Actualcost
    {
        get
        {
            return Reader.GetNullableDecimal(ACTUALCOST_FIELD_ID);
        }
    }

    public DateTime Modifieddate
    {
        get
        {
            return Reader.GetDateTime(MODIFIEDDATE_FIELD_ID);
        }
    }


    public AdventureWorks.Production.Types.WorkorderroutingDataType ToDataObject()
    {
        return new AdventureWorks.Production.Types.WorkorderroutingDataType(Workorderid,
            Productid,
            Operationsequence,
            Locationid,
            Scheduledstartdate,
            Scheduledenddate,
            Actualstartdate,
            Actualenddate,
            Actualresourcehrs,
            Plannedcost,
            Actualcost,
            Modifieddate);
    }

    public List<AdventureWorks.Production.Types.WorkorderroutingDataType> ToList()
    {
        var list = new List<AdventureWorks.Production.Types.WorkorderroutingDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
