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

public class ProductphotoDataTable
{

    DataTable _dataTable;

    public ProductphotoDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ProductphotoDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var productphotoidColumn = new DataColumn("Productphotoid", typeof(int));
        productphotoidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productphotoidColumn);
        var thumbnailphotoColumn = new DataColumn("Thumbnailphoto", typeof(byte[]));
        dataTable.Columns.Add(thumbnailphotoColumn);
        var thumbnailphotofilenameColumn = new DataColumn("Thumbnailphotofilename", typeof(string));
        dataTable.Columns.Add(thumbnailphotofilenameColumn);
        var largephotoColumn = new DataColumn("Largephoto", typeof(byte[]));
        dataTable.Columns.Add(largephotoColumn);
        var largephotofilenameColumn = new DataColumn("Largephotofilename", typeof(string));
        dataTable.Columns.Add(largephotofilenameColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int productphotoid,
                        byte[]? thumbnailphoto,
                        string? thumbnailphotofilename,
                        byte[]? largephoto,
                        string? largephotofilename,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Productphotoid"] = productphotoid;
        row["Thumbnailphoto"] = (object?)thumbnailphoto ?? DBNull.Value;
        row["Thumbnailphotofilename"] = (object?)thumbnailphotofilename ?? DBNull.Value;
        row["Largephoto"] = (object?)largephoto ?? DBNull.Value;
        row["Largephotofilename"] = (object?)largephotofilename ?? DBNull.Value;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ProductphotoDataType data)
    {
        var row = _dataTable.NewRow();
        row["Productphotoid"] = data.Productphotoid;
        row["Thumbnailphoto"] = (object?)data.Thumbnailphoto ?? DBNull.Value;
        row["Thumbnailphotofilename"] = (object?)data.Thumbnailphotofilename ?? DBNull.Value;
        row["Largephoto"] = (object?)data.Largephoto ?? DBNull.Value;
        row["Largephotofilename"] = (object?)data.Largephotofilename ?? DBNull.Value;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Productphotoid", "[Productphotoid]");
        columnMappings.Add("Thumbnailphoto", "[Thumbnailphoto]");
        columnMappings.Add("Thumbnailphotofilename", "[Thumbnailphotofilename]");
        columnMappings.Add("Largephoto", "[Largephoto]");
        columnMappings.Add("Largephotofilename", "[Largephotofilename]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[ProductPhoto]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
