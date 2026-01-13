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

public class IllustrationDataTable
{

    DataTable _dataTable;

    public IllustrationDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public IllustrationDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var illustrationidColumn = new DataColumn("Illustrationid", typeof(int));
        illustrationidColumn.AllowDBNull = false;
        dataTable.Columns.Add(illustrationidColumn);
        var diagramColumn = new DataColumn("Diagram", typeof(SqlXml));
        dataTable.Columns.Add(diagramColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int illustrationid,
                        SqlXml? diagram,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Illustrationid"] = illustrationid;
        row["Diagram"] = (object?)diagram ?? DBNull.Value;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(IllustrationDataType data)
    {
        var row = _dataTable.NewRow();
        row["Illustrationid"] = data.Illustrationid;
        row["Diagram"] = (object?)data.Diagram ?? DBNull.Value;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Illustrationid", "[Illustrationid]");
        columnMappings.Add("Diagram", "[Diagram]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[Illustration]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
