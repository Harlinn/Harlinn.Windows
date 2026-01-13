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
using AdventureWorks.Purchasing.Types;

namespace AdventureWorks.Purchasing.Database.DataTables;

public class ProductvendorDataTable
{

    DataTable _dataTable;

    public ProductvendorDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ProductvendorDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var productidColumn = new DataColumn("Productid", typeof(int));
        productidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productidColumn);
        var businessentityidColumn = new DataColumn("Businessentityid", typeof(int));
        businessentityidColumn.AllowDBNull = false;
        dataTable.Columns.Add(businessentityidColumn);
        var averageleadtimeColumn = new DataColumn("Averageleadtime", typeof(int));
        averageleadtimeColumn.AllowDBNull = false;
        dataTable.Columns.Add(averageleadtimeColumn);
        var standardpriceColumn = new DataColumn("Standardprice", typeof(decimal));
        standardpriceColumn.AllowDBNull = false;
        dataTable.Columns.Add(standardpriceColumn);
        var lastreceiptcostColumn = new DataColumn("Lastreceiptcost", typeof(decimal));
        dataTable.Columns.Add(lastreceiptcostColumn);
        var lastreceiptdateColumn = new DataColumn("Lastreceiptdate", typeof(DateTime));
        dataTable.Columns.Add(lastreceiptdateColumn);
        var minorderqtyColumn = new DataColumn("Minorderqty", typeof(int));
        minorderqtyColumn.AllowDBNull = false;
        dataTable.Columns.Add(minorderqtyColumn);
        var maxorderqtyColumn = new DataColumn("Maxorderqty", typeof(int));
        maxorderqtyColumn.AllowDBNull = false;
        dataTable.Columns.Add(maxorderqtyColumn);
        var onorderqtyColumn = new DataColumn("Onorderqty", typeof(int));
        dataTable.Columns.Add(onorderqtyColumn);
        var unitmeasurecodeColumn = new DataColumn("Unitmeasurecode", typeof(string));
        unitmeasurecodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(unitmeasurecodeColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int productid,
                        int businessentityid,
                        int averageleadtime,
                        decimal standardprice,
                        decimal? lastreceiptcost,
                        DateTime? lastreceiptdate,
                        int minorderqty,
                        int maxorderqty,
                        int? onorderqty,
                        string unitmeasurecode,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Productid"] = productid;
        row["Businessentityid"] = businessentityid;
        row["Averageleadtime"] = averageleadtime;
        row["Standardprice"] = standardprice;
        row["Lastreceiptcost"] = (object?)lastreceiptcost ?? DBNull.Value;
        row["Lastreceiptdate"] = (object?)lastreceiptdate ?? DBNull.Value;
        row["Minorderqty"] = minorderqty;
        row["Maxorderqty"] = maxorderqty;
        row["Onorderqty"] = (object?)onorderqty ?? DBNull.Value;
        row["Unitmeasurecode"] = unitmeasurecode;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ProductvendorDataType data)
    {
        var row = _dataTable.NewRow();
        row["Productid"] = data.Productid;
        row["Businessentityid"] = data.Businessentityid;
        row["Averageleadtime"] = data.Averageleadtime;
        row["Standardprice"] = data.Standardprice;
        row["Lastreceiptcost"] = (object?)data.Lastreceiptcost ?? DBNull.Value;
        row["Lastreceiptdate"] = (object?)data.Lastreceiptdate ?? DBNull.Value;
        row["Minorderqty"] = data.Minorderqty;
        row["Maxorderqty"] = data.Maxorderqty;
        row["Onorderqty"] = (object?)data.Onorderqty ?? DBNull.Value;
        row["Unitmeasurecode"] = data.Unitmeasurecode;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Productid", "[Productid]");
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Averageleadtime", "[Averageleadtime]");
        columnMappings.Add("Standardprice", "[Standardprice]");
        columnMappings.Add("Lastreceiptcost", "[Lastreceiptcost]");
        columnMappings.Add("Lastreceiptdate", "[Lastreceiptdate]");
        columnMappings.Add("Minorderqty", "[Minorderqty]");
        columnMappings.Add("Maxorderqty", "[Maxorderqty]");
        columnMappings.Add("Onorderqty", "[Onorderqty]");
        columnMappings.Add("Unitmeasurecode", "[Unitmeasurecode]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Purchasing].[ProductVendor]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
