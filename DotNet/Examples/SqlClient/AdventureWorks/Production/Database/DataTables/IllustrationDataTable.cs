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
