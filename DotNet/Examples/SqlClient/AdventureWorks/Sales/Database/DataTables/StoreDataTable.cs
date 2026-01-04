using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Sales.Database.DataTables;

public class StoreDataTable
{

    DataTable _dataTable;

    public StoreDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public StoreDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var businessentityidColumn = new DataColumn("Businessentityid", typeof(int));
        businessentityidColumn.AllowDBNull = false;
        dataTable.Columns.Add(businessentityidColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var salespersonidColumn = new DataColumn("Salespersonid", typeof(int));
        dataTable.Columns.Add(salespersonidColumn);
        var demographicsColumn = new DataColumn("Demographics", typeof(SqlXml));
        dataTable.Columns.Add(demographicsColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int businessentityid,
                        string name,
                        int? salespersonid,
                        SqlXml? demographics,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = businessentityid;
        row["Name"] = name;
        row["Salespersonid"] = (object?)salespersonid ?? DBNull.Value;
        row["Demographics"] = (object?)demographics ?? DBNull.Value;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(StoreDataType data)
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = data.Businessentityid;
        row["Name"] = data.Name;
        row["Salespersonid"] = (object?)data.Salespersonid ?? DBNull.Value;
        row["Demographics"] = (object?)data.Demographics ?? DBNull.Value;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Salespersonid", "[Salespersonid]");
        columnMappings.Add("Demographics", "[Demographics]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[Store]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
