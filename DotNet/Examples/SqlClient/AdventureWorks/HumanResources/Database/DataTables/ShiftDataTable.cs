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
using AdventureWorks.HumanResources.Types;

namespace AdventureWorks.HumanResources.Database.DataTables;

public class ShiftDataTable
{

    DataTable _dataTable;

    public ShiftDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ShiftDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var shiftidColumn = new DataColumn("Shiftid", typeof(byte));
        shiftidColumn.AllowDBNull = false;
        dataTable.Columns.Add(shiftidColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var starttimeColumn = new DataColumn("Starttime", typeof(DateTime));
        starttimeColumn.AllowDBNull = false;
        dataTable.Columns.Add(starttimeColumn);
        var endtimeColumn = new DataColumn("Endtime", typeof(DateTime));
        endtimeColumn.AllowDBNull = false;
        dataTable.Columns.Add(endtimeColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        byte shiftid,
                        string name,
                        DateTime starttime,
                        DateTime endtime,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Shiftid"] = shiftid;
        row["Name"] = name;
        row["Starttime"] = starttime;
        row["Endtime"] = endtime;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ShiftDataType data)
    {
        var row = _dataTable.NewRow();
        row["Shiftid"] = data.Shiftid;
        row["Name"] = data.Name;
        row["Starttime"] = data.Starttime;
        row["Endtime"] = data.Endtime;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Shiftid", "[Shiftid]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Starttime", "[Starttime]");
        columnMappings.Add("Endtime", "[Endtime]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[HumanResources].[Shift]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
