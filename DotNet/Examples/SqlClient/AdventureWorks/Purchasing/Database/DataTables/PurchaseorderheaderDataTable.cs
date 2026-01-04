using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Purchasing.Types;

namespace AdventureWorks.Purchasing.Database.DataTables;

public class PurchaseorderheaderDataTable
{

    DataTable _dataTable;

    public PurchaseorderheaderDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public PurchaseorderheaderDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var purchaseorderidColumn = new DataColumn("Purchaseorderid", typeof(int));
        purchaseorderidColumn.AllowDBNull = false;
        dataTable.Columns.Add(purchaseorderidColumn);
        var revisionnumberColumn = new DataColumn("Revisionnumber", typeof(byte));
        revisionnumberColumn.AllowDBNull = false;
        dataTable.Columns.Add(revisionnumberColumn);
        var statusColumn = new DataColumn("Status", typeof(byte));
        statusColumn.AllowDBNull = false;
        dataTable.Columns.Add(statusColumn);
        var employeeidColumn = new DataColumn("Employeeid", typeof(int));
        employeeidColumn.AllowDBNull = false;
        dataTable.Columns.Add(employeeidColumn);
        var vendoridColumn = new DataColumn("Vendorid", typeof(int));
        vendoridColumn.AllowDBNull = false;
        dataTable.Columns.Add(vendoridColumn);
        var shipmethodidColumn = new DataColumn("Shipmethodid", typeof(int));
        shipmethodidColumn.AllowDBNull = false;
        dataTable.Columns.Add(shipmethodidColumn);
        var orderdateColumn = new DataColumn("Orderdate", typeof(DateTime));
        orderdateColumn.AllowDBNull = false;
        dataTable.Columns.Add(orderdateColumn);
        var shipdateColumn = new DataColumn("Shipdate", typeof(DateTime));
        dataTable.Columns.Add(shipdateColumn);
        var subtotalColumn = new DataColumn("Subtotal", typeof(decimal));
        subtotalColumn.AllowDBNull = false;
        dataTable.Columns.Add(subtotalColumn);
        var taxamtColumn = new DataColumn("Taxamt", typeof(decimal));
        taxamtColumn.AllowDBNull = false;
        dataTable.Columns.Add(taxamtColumn);
        var freightColumn = new DataColumn("Freight", typeof(decimal));
        freightColumn.AllowDBNull = false;
        dataTable.Columns.Add(freightColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int purchaseorderid,
                        byte revisionnumber,
                        byte status,
                        int employeeid,
                        int vendorid,
                        int shipmethodid,
                        DateTime orderdate,
                        DateTime? shipdate,
                        decimal subtotal,
                        decimal taxamt,
                        decimal freight,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Purchaseorderid"] = purchaseorderid;
        row["Revisionnumber"] = revisionnumber;
        row["Status"] = status;
        row["Employeeid"] = employeeid;
        row["Vendorid"] = vendorid;
        row["Shipmethodid"] = shipmethodid;
        row["Orderdate"] = orderdate;
        row["Shipdate"] = (object?)shipdate ?? DBNull.Value;
        row["Subtotal"] = subtotal;
        row["Taxamt"] = taxamt;
        row["Freight"] = freight;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(PurchaseorderheaderDataType data)
    {
        var row = _dataTable.NewRow();
        row["Purchaseorderid"] = data.Purchaseorderid;
        row["Revisionnumber"] = data.Revisionnumber;
        row["Status"] = data.Status;
        row["Employeeid"] = data.Employeeid;
        row["Vendorid"] = data.Vendorid;
        row["Shipmethodid"] = data.Shipmethodid;
        row["Orderdate"] = data.Orderdate;
        row["Shipdate"] = (object?)data.Shipdate ?? DBNull.Value;
        row["Subtotal"] = data.Subtotal;
        row["Taxamt"] = data.Taxamt;
        row["Freight"] = data.Freight;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Purchaseorderid", "[Purchaseorderid]");
        columnMappings.Add("Revisionnumber", "[Revisionnumber]");
        columnMappings.Add("Status", "[Status]");
        columnMappings.Add("Employeeid", "[Employeeid]");
        columnMappings.Add("Vendorid", "[Vendorid]");
        columnMappings.Add("Shipmethodid", "[Shipmethodid]");
        columnMappings.Add("Orderdate", "[Orderdate]");
        columnMappings.Add("Shipdate", "[Shipdate]");
        columnMappings.Add("Subtotal", "[Subtotal]");
        columnMappings.Add("Taxamt", "[Taxamt]");
        columnMappings.Add("Freight", "[Freight]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Purchasing].[PurchaseOrderHeader]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
