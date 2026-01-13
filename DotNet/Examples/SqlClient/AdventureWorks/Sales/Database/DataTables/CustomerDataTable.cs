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
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Sales.Database.DataTables;

public class CustomerDataTable
{

    DataTable _dataTable;

    public CustomerDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public CustomerDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var customeridColumn = new DataColumn("Customerid", typeof(int));
        customeridColumn.AllowDBNull = false;
        dataTable.Columns.Add(customeridColumn);
        var personidColumn = new DataColumn("Personid", typeof(int));
        dataTable.Columns.Add(personidColumn);
        var storeidColumn = new DataColumn("Storeid", typeof(int));
        dataTable.Columns.Add(storeidColumn);
        var territoryidColumn = new DataColumn("Territoryid", typeof(int));
        dataTable.Columns.Add(territoryidColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int customerid,
                        int? personid,
                        int? storeid,
                        int? territoryid,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Customerid"] = customerid;
        row["Personid"] = (object?)personid ?? DBNull.Value;
        row["Storeid"] = (object?)storeid ?? DBNull.Value;
        row["Territoryid"] = (object?)territoryid ?? DBNull.Value;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(CustomerDataType data)
    {
        var row = _dataTable.NewRow();
        row["Customerid"] = data.Customerid;
        row["Personid"] = (object?)data.Personid ?? DBNull.Value;
        row["Storeid"] = (object?)data.Storeid ?? DBNull.Value;
        row["Territoryid"] = (object?)data.Territoryid ?? DBNull.Value;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Customerid", "[Customerid]");
        columnMappings.Add("Personid", "[Personid]");
        columnMappings.Add("Storeid", "[Storeid]");
        columnMappings.Add("Territoryid", "[Territoryid]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[Customer]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
