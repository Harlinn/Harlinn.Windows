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

public class ProductmodelproductdescriptioncultureDataTable
{

    DataTable _dataTable;

    public ProductmodelproductdescriptioncultureDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ProductmodelproductdescriptioncultureDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var productmodelidColumn = new DataColumn("Productmodelid", typeof(int));
        productmodelidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productmodelidColumn);
        var productdescriptionidColumn = new DataColumn("Productdescriptionid", typeof(int));
        productdescriptionidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productdescriptionidColumn);
        var cultureidColumn = new DataColumn("Cultureid", typeof(string));
        cultureidColumn.AllowDBNull = false;
        dataTable.Columns.Add(cultureidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int productmodelid,
                        int productdescriptionid,
                        string cultureid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Productmodelid"] = productmodelid;
        row["Productdescriptionid"] = productdescriptionid;
        row["Cultureid"] = cultureid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ProductmodelproductdescriptioncultureDataType data)
    {
        var row = _dataTable.NewRow();
        row["Productmodelid"] = data.Productmodelid;
        row["Productdescriptionid"] = data.Productdescriptionid;
        row["Cultureid"] = data.Cultureid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Productmodelid", "[Productmodelid]");
        columnMappings.Add("Productdescriptionid", "[Productdescriptionid]");
        columnMappings.Add("Cultureid", "[Cultureid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[ProductModelProductDescriptionCulture]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
