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

public class ShoppingcartitemDataTable
{

    DataTable _dataTable;

    public ShoppingcartitemDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ShoppingcartitemDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var shoppingcartitemidColumn = new DataColumn("Shoppingcartitemid", typeof(int));
        shoppingcartitemidColumn.AllowDBNull = false;
        dataTable.Columns.Add(shoppingcartitemidColumn);
        var shoppingcartidColumn = new DataColumn("Shoppingcartid", typeof(string));
        shoppingcartidColumn.AllowDBNull = false;
        dataTable.Columns.Add(shoppingcartidColumn);
        var quantityColumn = new DataColumn("Quantity", typeof(int));
        quantityColumn.AllowDBNull = false;
        dataTable.Columns.Add(quantityColumn);
        var productidColumn = new DataColumn("Productid", typeof(int));
        productidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productidColumn);
        var datecreatedColumn = new DataColumn("Datecreated", typeof(DateTime));
        datecreatedColumn.AllowDBNull = false;
        dataTable.Columns.Add(datecreatedColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int shoppingcartitemid,
                        string shoppingcartid,
                        int quantity,
                        int productid,
                        DateTime datecreated,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Shoppingcartitemid"] = shoppingcartitemid;
        row["Shoppingcartid"] = shoppingcartid;
        row["Quantity"] = quantity;
        row["Productid"] = productid;
        row["Datecreated"] = datecreated;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ShoppingcartitemDataType data)
    {
        var row = _dataTable.NewRow();
        row["Shoppingcartitemid"] = data.Shoppingcartitemid;
        row["Shoppingcartid"] = data.Shoppingcartid;
        row["Quantity"] = data.Quantity;
        row["Productid"] = data.Productid;
        row["Datecreated"] = data.Datecreated;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Shoppingcartitemid", "[Shoppingcartitemid]");
        columnMappings.Add("Shoppingcartid", "[Shoppingcartid]");
        columnMappings.Add("Quantity", "[Quantity]");
        columnMappings.Add("Productid", "[Productid]");
        columnMappings.Add("Datecreated", "[Datecreated]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[ShoppingCartItem]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
