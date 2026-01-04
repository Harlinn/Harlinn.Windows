using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Purchasing.Types;

namespace AdventureWorks.Purchasing.Database.DataTables;

public class ShipmethodDataTable
{

    DataTable _dataTable;

    public ShipmethodDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ShipmethodDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var shipmethodidColumn = new DataColumn("Shipmethodid", typeof(int));
        shipmethodidColumn.AllowDBNull = false;
        dataTable.Columns.Add(shipmethodidColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var shipbaseColumn = new DataColumn("Shipbase", typeof(decimal));
        shipbaseColumn.AllowDBNull = false;
        dataTable.Columns.Add(shipbaseColumn);
        var shiprateColumn = new DataColumn("Shiprate", typeof(decimal));
        shiprateColumn.AllowDBNull = false;
        dataTable.Columns.Add(shiprateColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int shipmethodid,
                        string name,
                        decimal shipbase,
                        decimal shiprate,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Shipmethodid"] = shipmethodid;
        row["Name"] = name;
        row["Shipbase"] = shipbase;
        row["Shiprate"] = shiprate;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ShipmethodDataType data)
    {
        var row = _dataTable.NewRow();
        row["Shipmethodid"] = data.Shipmethodid;
        row["Name"] = data.Name;
        row["Shipbase"] = data.Shipbase;
        row["Shiprate"] = data.Shiprate;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Shipmethodid", "[Shipmethodid]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Shipbase", "[Shipbase]");
        columnMappings.Add("Shiprate", "[Shiprate]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Purchasing].[ShipMethod]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
