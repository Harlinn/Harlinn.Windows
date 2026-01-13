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
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class BillofmaterialsDataTable
{

    DataTable _dataTable;

    public BillofmaterialsDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public BillofmaterialsDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var billofmaterialsidColumn = new DataColumn("Billofmaterialsid", typeof(int));
        billofmaterialsidColumn.AllowDBNull = false;
        dataTable.Columns.Add(billofmaterialsidColumn);
        var productassemblyidColumn = new DataColumn("Productassemblyid", typeof(int));
        dataTable.Columns.Add(productassemblyidColumn);
        var componentidColumn = new DataColumn("Componentid", typeof(int));
        componentidColumn.AllowDBNull = false;
        dataTable.Columns.Add(componentidColumn);
        var startdateColumn = new DataColumn("Startdate", typeof(DateTime));
        startdateColumn.AllowDBNull = false;
        dataTable.Columns.Add(startdateColumn);
        var enddateColumn = new DataColumn("Enddate", typeof(DateTime));
        dataTable.Columns.Add(enddateColumn);
        var unitmeasurecodeColumn = new DataColumn("Unitmeasurecode", typeof(string));
        unitmeasurecodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(unitmeasurecodeColumn);
        var bomlevelColumn = new DataColumn("Bomlevel", typeof(short));
        bomlevelColumn.AllowDBNull = false;
        dataTable.Columns.Add(bomlevelColumn);
        var perassemblyqtyColumn = new DataColumn("Perassemblyqty", typeof(decimal));
        perassemblyqtyColumn.AllowDBNull = false;
        dataTable.Columns.Add(perassemblyqtyColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int billofmaterialsid,
                        int? productassemblyid,
                        int componentid,
                        DateTime startdate,
                        DateTime? enddate,
                        string unitmeasurecode,
                        short bomlevel,
                        decimal perassemblyqty,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Billofmaterialsid"] = billofmaterialsid;
        row["Productassemblyid"] = (object?)productassemblyid ?? DBNull.Value;
        row["Componentid"] = componentid;
        row["Startdate"] = startdate;
        row["Enddate"] = (object?)enddate ?? DBNull.Value;
        row["Unitmeasurecode"] = unitmeasurecode;
        row["Bomlevel"] = bomlevel;
        row["Perassemblyqty"] = perassemblyqty;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(BillofmaterialsDataType data)
    {
        var row = _dataTable.NewRow();
        row["Billofmaterialsid"] = data.Billofmaterialsid;
        row["Productassemblyid"] = (object?)data.Productassemblyid ?? DBNull.Value;
        row["Componentid"] = data.Componentid;
        row["Startdate"] = data.Startdate;
        row["Enddate"] = (object?)data.Enddate ?? DBNull.Value;
        row["Unitmeasurecode"] = data.Unitmeasurecode;
        row["Bomlevel"] = data.Bomlevel;
        row["Perassemblyqty"] = data.Perassemblyqty;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Billofmaterialsid", "[Billofmaterialsid]");
        columnMappings.Add("Productassemblyid", "[Productassemblyid]");
        columnMappings.Add("Componentid", "[Componentid]");
        columnMappings.Add("Startdate", "[Startdate]");
        columnMappings.Add("Enddate", "[Enddate]");
        columnMappings.Add("Unitmeasurecode", "[Unitmeasurecode]");
        columnMappings.Add("Bomlevel", "[Bomlevel]");
        columnMappings.Add("Perassemblyqty", "[Perassemblyqty]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[BillOfMaterials]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
