using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class UnitmeasureDataTable
{

    DataTable _dataTable;

    public UnitmeasureDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public UnitmeasureDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var unitmeasurecodeColumn = new DataColumn("Unitmeasurecode", typeof(string));
        unitmeasurecodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(unitmeasurecodeColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        string unitmeasurecode,
                        string name,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Unitmeasurecode"] = unitmeasurecode;
        row["Name"] = name;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(UnitmeasureDataType data)
    {
        var row = _dataTable.NewRow();
        row["Unitmeasurecode"] = data.Unitmeasurecode;
        row["Name"] = data.Name;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Unitmeasurecode", "[Unitmeasurecode]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[UnitMeasure]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
