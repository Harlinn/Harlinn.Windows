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

public class SalesorderdetailDataTable
{

    DataTable _dataTable;

    public SalesorderdetailDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public SalesorderdetailDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var salesorderidColumn = new DataColumn("Salesorderid", typeof(int));
        salesorderidColumn.AllowDBNull = false;
        dataTable.Columns.Add(salesorderidColumn);
        var salesorderdetailidColumn = new DataColumn("Salesorderdetailid", typeof(int));
        salesorderdetailidColumn.AllowDBNull = false;
        dataTable.Columns.Add(salesorderdetailidColumn);
        var carriertrackingnumberColumn = new DataColumn("Carriertrackingnumber", typeof(string));
        dataTable.Columns.Add(carriertrackingnumberColumn);
        var orderqtyColumn = new DataColumn("Orderqty", typeof(short));
        orderqtyColumn.AllowDBNull = false;
        dataTable.Columns.Add(orderqtyColumn);
        var productidColumn = new DataColumn("Productid", typeof(int));
        productidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productidColumn);
        var specialofferidColumn = new DataColumn("Specialofferid", typeof(int));
        specialofferidColumn.AllowDBNull = false;
        dataTable.Columns.Add(specialofferidColumn);
        var unitpriceColumn = new DataColumn("Unitprice", typeof(decimal));
        unitpriceColumn.AllowDBNull = false;
        dataTable.Columns.Add(unitpriceColumn);
        var unitpricediscountColumn = new DataColumn("Unitpricediscount", typeof(decimal));
        unitpricediscountColumn.AllowDBNull = false;
        dataTable.Columns.Add(unitpricediscountColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int salesorderid,
                        int salesorderdetailid,
                        string? carriertrackingnumber,
                        short orderqty,
                        int productid,
                        int specialofferid,
                        decimal unitprice,
                        decimal unitpricediscount,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Salesorderid"] = salesorderid;
        row["Salesorderdetailid"] = salesorderdetailid;
        row["Carriertrackingnumber"] = (object?)carriertrackingnumber ?? DBNull.Value;
        row["Orderqty"] = orderqty;
        row["Productid"] = productid;
        row["Specialofferid"] = specialofferid;
        row["Unitprice"] = unitprice;
        row["Unitpricediscount"] = unitpricediscount;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(SalesorderdetailDataType data)
    {
        var row = _dataTable.NewRow();
        row["Salesorderid"] = data.Salesorderid;
        row["Salesorderdetailid"] = data.Salesorderdetailid;
        row["Carriertrackingnumber"] = (object?)data.Carriertrackingnumber ?? DBNull.Value;
        row["Orderqty"] = data.Orderqty;
        row["Productid"] = data.Productid;
        row["Specialofferid"] = data.Specialofferid;
        row["Unitprice"] = data.Unitprice;
        row["Unitpricediscount"] = data.Unitpricediscount;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Salesorderid", "[Salesorderid]");
        columnMappings.Add("Salesorderdetailid", "[Salesorderdetailid]");
        columnMappings.Add("Carriertrackingnumber", "[Carriertrackingnumber]");
        columnMappings.Add("Orderqty", "[Orderqty]");
        columnMappings.Add("Productid", "[Productid]");
        columnMappings.Add("Specialofferid", "[Specialofferid]");
        columnMappings.Add("Unitprice", "[Unitprice]");
        columnMappings.Add("Unitpricediscount", "[Unitpricediscount]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[SalesOrderDetail]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
