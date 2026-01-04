using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Sales.Database.DataTables;

public class SalesorderheaderDataTable
{

    DataTable _dataTable;

    public SalesorderheaderDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public SalesorderheaderDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var salesorderidColumn = new DataColumn("Salesorderid", typeof(int));
        salesorderidColumn.AllowDBNull = false;
        dataTable.Columns.Add(salesorderidColumn);
        var revisionnumberColumn = new DataColumn("Revisionnumber", typeof(byte));
        revisionnumberColumn.AllowDBNull = false;
        dataTable.Columns.Add(revisionnumberColumn);
        var orderdateColumn = new DataColumn("Orderdate", typeof(DateTime));
        orderdateColumn.AllowDBNull = false;
        dataTable.Columns.Add(orderdateColumn);
        var duedateColumn = new DataColumn("Duedate", typeof(DateTime));
        duedateColumn.AllowDBNull = false;
        dataTable.Columns.Add(duedateColumn);
        var shipdateColumn = new DataColumn("Shipdate", typeof(DateTime));
        dataTable.Columns.Add(shipdateColumn);
        var statusColumn = new DataColumn("Status", typeof(byte));
        statusColumn.AllowDBNull = false;
        dataTable.Columns.Add(statusColumn);
        var onlineorderflagColumn = new DataColumn("Onlineorderflag", typeof(bool));
        onlineorderflagColumn.AllowDBNull = false;
        dataTable.Columns.Add(onlineorderflagColumn);
        var purchaseordernumberColumn = new DataColumn("Purchaseordernumber", typeof(string));
        dataTable.Columns.Add(purchaseordernumberColumn);
        var accountnumberColumn = new DataColumn("Accountnumber", typeof(string));
        dataTable.Columns.Add(accountnumberColumn);
        var customeridColumn = new DataColumn("Customerid", typeof(int));
        customeridColumn.AllowDBNull = false;
        dataTable.Columns.Add(customeridColumn);
        var salespersonidColumn = new DataColumn("Salespersonid", typeof(int));
        dataTable.Columns.Add(salespersonidColumn);
        var territoryidColumn = new DataColumn("Territoryid", typeof(int));
        dataTable.Columns.Add(territoryidColumn);
        var billtoaddressidColumn = new DataColumn("Billtoaddressid", typeof(int));
        billtoaddressidColumn.AllowDBNull = false;
        dataTable.Columns.Add(billtoaddressidColumn);
        var shiptoaddressidColumn = new DataColumn("Shiptoaddressid", typeof(int));
        shiptoaddressidColumn.AllowDBNull = false;
        dataTable.Columns.Add(shiptoaddressidColumn);
        var shipmethodidColumn = new DataColumn("Shipmethodid", typeof(int));
        shipmethodidColumn.AllowDBNull = false;
        dataTable.Columns.Add(shipmethodidColumn);
        var creditcardidColumn = new DataColumn("Creditcardid", typeof(int));
        dataTable.Columns.Add(creditcardidColumn);
        var creditcardapprovalcodeColumn = new DataColumn("Creditcardapprovalcode", typeof(string));
        dataTable.Columns.Add(creditcardapprovalcodeColumn);
        var currencyrateidColumn = new DataColumn("Currencyrateid", typeof(int));
        dataTable.Columns.Add(currencyrateidColumn);
        var subtotalColumn = new DataColumn("Subtotal", typeof(decimal));
        subtotalColumn.AllowDBNull = false;
        dataTable.Columns.Add(subtotalColumn);
        var taxamtColumn = new DataColumn("Taxamt", typeof(decimal));
        taxamtColumn.AllowDBNull = false;
        dataTable.Columns.Add(taxamtColumn);
        var freightColumn = new DataColumn("Freight", typeof(decimal));
        freightColumn.AllowDBNull = false;
        dataTable.Columns.Add(freightColumn);
        var commentColumn = new DataColumn("Comment", typeof(string));
        dataTable.Columns.Add(commentColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int salesorderid,
                        byte revisionnumber,
                        DateTime orderdate,
                        DateTime duedate,
                        DateTime? shipdate,
                        byte status,
                        bool onlineorderflag,
                        string? purchaseordernumber,
                        string? accountnumber,
                        int customerid,
                        int? salespersonid,
                        int? territoryid,
                        int billtoaddressid,
                        int shiptoaddressid,
                        int shipmethodid,
                        int? creditcardid,
                        string? creditcardapprovalcode,
                        int? currencyrateid,
                        decimal subtotal,
                        decimal taxamt,
                        decimal freight,
                        string? comment,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Salesorderid"] = salesorderid;
        row["Revisionnumber"] = revisionnumber;
        row["Orderdate"] = orderdate;
        row["Duedate"] = duedate;
        row["Shipdate"] = (object?)shipdate ?? DBNull.Value;
        row["Status"] = status;
        row["Onlineorderflag"] = onlineorderflag;
        row["Purchaseordernumber"] = (object?)purchaseordernumber ?? DBNull.Value;
        row["Accountnumber"] = (object?)accountnumber ?? DBNull.Value;
        row["Customerid"] = customerid;
        row["Salespersonid"] = (object?)salespersonid ?? DBNull.Value;
        row["Territoryid"] = (object?)territoryid ?? DBNull.Value;
        row["Billtoaddressid"] = billtoaddressid;
        row["Shiptoaddressid"] = shiptoaddressid;
        row["Shipmethodid"] = shipmethodid;
        row["Creditcardid"] = (object?)creditcardid ?? DBNull.Value;
        row["Creditcardapprovalcode"] = (object?)creditcardapprovalcode ?? DBNull.Value;
        row["Currencyrateid"] = (object?)currencyrateid ?? DBNull.Value;
        row["Subtotal"] = subtotal;
        row["Taxamt"] = taxamt;
        row["Freight"] = freight;
        row["Comment"] = (object?)comment ?? DBNull.Value;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(SalesorderheaderDataType data)
    {
        var row = _dataTable.NewRow();
        row["Salesorderid"] = data.Salesorderid;
        row["Revisionnumber"] = data.Revisionnumber;
        row["Orderdate"] = data.Orderdate;
        row["Duedate"] = data.Duedate;
        row["Shipdate"] = (object?)data.Shipdate ?? DBNull.Value;
        row["Status"] = data.Status;
        row["Onlineorderflag"] = data.Onlineorderflag;
        row["Purchaseordernumber"] = (object?)data.Purchaseordernumber ?? DBNull.Value;
        row["Accountnumber"] = (object?)data.Accountnumber ?? DBNull.Value;
        row["Customerid"] = data.Customerid;
        row["Salespersonid"] = (object?)data.Salespersonid ?? DBNull.Value;
        row["Territoryid"] = (object?)data.Territoryid ?? DBNull.Value;
        row["Billtoaddressid"] = data.Billtoaddressid;
        row["Shiptoaddressid"] = data.Shiptoaddressid;
        row["Shipmethodid"] = data.Shipmethodid;
        row["Creditcardid"] = (object?)data.Creditcardid ?? DBNull.Value;
        row["Creditcardapprovalcode"] = (object?)data.Creditcardapprovalcode ?? DBNull.Value;
        row["Currencyrateid"] = (object?)data.Currencyrateid ?? DBNull.Value;
        row["Subtotal"] = data.Subtotal;
        row["Taxamt"] = data.Taxamt;
        row["Freight"] = data.Freight;
        row["Comment"] = (object?)data.Comment ?? DBNull.Value;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Salesorderid", "[Salesorderid]");
        columnMappings.Add("Revisionnumber", "[Revisionnumber]");
        columnMappings.Add("Orderdate", "[Orderdate]");
        columnMappings.Add("Duedate", "[Duedate]");
        columnMappings.Add("Shipdate", "[Shipdate]");
        columnMappings.Add("Status", "[Status]");
        columnMappings.Add("Onlineorderflag", "[Onlineorderflag]");
        columnMappings.Add("Purchaseordernumber", "[Purchaseordernumber]");
        columnMappings.Add("Accountnumber", "[Accountnumber]");
        columnMappings.Add("Customerid", "[Customerid]");
        columnMappings.Add("Salespersonid", "[Salespersonid]");
        columnMappings.Add("Territoryid", "[Territoryid]");
        columnMappings.Add("Billtoaddressid", "[Billtoaddressid]");
        columnMappings.Add("Shiptoaddressid", "[Shiptoaddressid]");
        columnMappings.Add("Shipmethodid", "[Shipmethodid]");
        columnMappings.Add("Creditcardid", "[Creditcardid]");
        columnMappings.Add("Creditcardapprovalcode", "[Creditcardapprovalcode]");
        columnMappings.Add("Currencyrateid", "[Currencyrateid]");
        columnMappings.Add("Subtotal", "[Subtotal]");
        columnMappings.Add("Taxamt", "[Taxamt]");
        columnMappings.Add("Freight", "[Freight]");
        columnMappings.Add("Comment", "[Comment]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[SalesOrderHeader]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
