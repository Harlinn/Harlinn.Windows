using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class CultureDataTable
{

    DataTable _dataTable;

    public CultureDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public CultureDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var cultureidColumn = new DataColumn("Cultureid", typeof(string));
        cultureidColumn.AllowDBNull = false;
        dataTable.Columns.Add(cultureidColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        string cultureid,
                        string name,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Cultureid"] = cultureid;
        row["Name"] = name;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(CultureDataType data)
    {
        var row = _dataTable.NewRow();
        row["Cultureid"] = data.Cultureid;
        row["Name"] = data.Name;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Cultureid", "[Cultureid]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[Culture]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
