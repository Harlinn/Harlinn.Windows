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

public class SalestaxrateDataTable
{

    DataTable _dataTable;

    public SalestaxrateDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public SalestaxrateDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var salestaxrateidColumn = new DataColumn("Salestaxrateid", typeof(int));
        salestaxrateidColumn.AllowDBNull = false;
        dataTable.Columns.Add(salestaxrateidColumn);
        var stateprovinceidColumn = new DataColumn("Stateprovinceid", typeof(int));
        stateprovinceidColumn.AllowDBNull = false;
        dataTable.Columns.Add(stateprovinceidColumn);
        var taxtypeColumn = new DataColumn("Taxtype", typeof(byte));
        taxtypeColumn.AllowDBNull = false;
        dataTable.Columns.Add(taxtypeColumn);
        var taxrateColumn = new DataColumn("Taxrate", typeof(decimal));
        taxrateColumn.AllowDBNull = false;
        dataTable.Columns.Add(taxrateColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int salestaxrateid,
                        int stateprovinceid,
                        byte taxtype,
                        decimal taxrate,
                        string name,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Salestaxrateid"] = salestaxrateid;
        row["Stateprovinceid"] = stateprovinceid;
        row["Taxtype"] = taxtype;
        row["Taxrate"] = taxrate;
        row["Name"] = name;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(SalestaxrateDataType data)
    {
        var row = _dataTable.NewRow();
        row["Salestaxrateid"] = data.Salestaxrateid;
        row["Stateprovinceid"] = data.Stateprovinceid;
        row["Taxtype"] = data.Taxtype;
        row["Taxrate"] = data.Taxrate;
        row["Name"] = data.Name;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Salestaxrateid", "[Salestaxrateid]");
        columnMappings.Add("Stateprovinceid", "[Stateprovinceid]");
        columnMappings.Add("Taxtype", "[Taxtype]");
        columnMappings.Add("Taxrate", "[Taxrate]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[SalesTaxRate]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
