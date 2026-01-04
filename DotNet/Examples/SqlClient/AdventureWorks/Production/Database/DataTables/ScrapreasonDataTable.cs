using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class ScrapreasonDataTable
{

    DataTable _dataTable;

    public ScrapreasonDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ScrapreasonDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var scrapreasonidColumn = new DataColumn("Scrapreasonid", typeof(short));
        scrapreasonidColumn.AllowDBNull = false;
        dataTable.Columns.Add(scrapreasonidColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        short scrapreasonid,
                        string name,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Scrapreasonid"] = scrapreasonid;
        row["Name"] = name;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ScrapreasonDataType data)
    {
        var row = _dataTable.NewRow();
        row["Scrapreasonid"] = data.Scrapreasonid;
        row["Name"] = data.Name;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Scrapreasonid", "[Scrapreasonid]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[ScrapReason]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
