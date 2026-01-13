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

public class EmployeepayhistoryDataTable
{

    DataTable _dataTable;

    public EmployeepayhistoryDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public EmployeepayhistoryDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var businessentityidColumn = new DataColumn("Businessentityid", typeof(int));
        businessentityidColumn.AllowDBNull = false;
        dataTable.Columns.Add(businessentityidColumn);
        var ratechangedateColumn = new DataColumn("Ratechangedate", typeof(DateTime));
        ratechangedateColumn.AllowDBNull = false;
        dataTable.Columns.Add(ratechangedateColumn);
        var rateColumn = new DataColumn("Rate", typeof(decimal));
        rateColumn.AllowDBNull = false;
        dataTable.Columns.Add(rateColumn);
        var payfrequencyColumn = new DataColumn("Payfrequency", typeof(byte));
        payfrequencyColumn.AllowDBNull = false;
        dataTable.Columns.Add(payfrequencyColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int businessentityid,
                        DateTime ratechangedate,
                        decimal rate,
                        byte payfrequency,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = businessentityid;
        row["Ratechangedate"] = ratechangedate;
        row["Rate"] = rate;
        row["Payfrequency"] = payfrequency;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(EmployeepayhistoryDataType data)
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = data.Businessentityid;
        row["Ratechangedate"] = data.Ratechangedate;
        row["Rate"] = data.Rate;
        row["Payfrequency"] = data.Payfrequency;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Ratechangedate", "[Ratechangedate]");
        columnMappings.Add("Rate", "[Rate]");
        columnMappings.Add("Payfrequency", "[Payfrequency]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[HumanResources].[EmployeePayHistory]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
