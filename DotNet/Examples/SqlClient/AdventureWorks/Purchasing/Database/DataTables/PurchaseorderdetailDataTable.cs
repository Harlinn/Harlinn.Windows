using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Purchasing.Types;

namespace AdventureWorks.Purchasing.Database.DataTables;

public class PurchaseorderdetailDataTable
{

    DataTable _dataTable;

    public PurchaseorderdetailDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public PurchaseorderdetailDataTable()
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
        var purchaseorderdetailidColumn = new DataColumn("Purchaseorderdetailid", typeof(int));
        purchaseorderdetailidColumn.AllowDBNull = false;
        dataTable.Columns.Add(purchaseorderdetailidColumn);
        var duedateColumn = new DataColumn("Duedate", typeof(DateTime));
        duedateColumn.AllowDBNull = false;
        dataTable.Columns.Add(duedateColumn);
        var orderqtyColumn = new DataColumn("Orderqty", typeof(short));
        orderqtyColumn.AllowDBNull = false;
        dataTable.Columns.Add(orderqtyColumn);
        var productidColumn = new DataColumn("Productid", typeof(int));
        productidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productidColumn);
        var unitpriceColumn = new DataColumn("Unitprice", typeof(decimal));
        unitpriceColumn.AllowDBNull = false;
        dataTable.Columns.Add(unitpriceColumn);
        var receivedqtyColumn = new DataColumn("Receivedqty", typeof(decimal));
        receivedqtyColumn.AllowDBNull = false;
        dataTable.Columns.Add(receivedqtyColumn);
        var rejectedqtyColumn = new DataColumn("Rejectedqty", typeof(decimal));
        rejectedqtyColumn.AllowDBNull = false;
        dataTable.Columns.Add(rejectedqtyColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int purchaseorderid,
                        int purchaseorderdetailid,
                        DateTime duedate,
                        short orderqty,
                        int productid,
                        decimal unitprice,
                        decimal receivedqty,
                        decimal rejectedqty,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Purchaseorderid"] = purchaseorderid;
        row["Purchaseorderdetailid"] = purchaseorderdetailid;
        row["Duedate"] = duedate;
        row["Orderqty"] = orderqty;
        row["Productid"] = productid;
        row["Unitprice"] = unitprice;
        row["Receivedqty"] = receivedqty;
        row["Rejectedqty"] = rejectedqty;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(PurchaseorderdetailDataType data)
    {
        var row = _dataTable.NewRow();
        row["Purchaseorderid"] = data.Purchaseorderid;
        row["Purchaseorderdetailid"] = data.Purchaseorderdetailid;
        row["Duedate"] = data.Duedate;
        row["Orderqty"] = data.Orderqty;
        row["Productid"] = data.Productid;
        row["Unitprice"] = data.Unitprice;
        row["Receivedqty"] = data.Receivedqty;
        row["Rejectedqty"] = data.Rejectedqty;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Purchaseorderid", "[Purchaseorderid]");
        columnMappings.Add("Purchaseorderdetailid", "[Purchaseorderdetailid]");
        columnMappings.Add("Duedate", "[Duedate]");
        columnMappings.Add("Orderqty", "[Orderqty]");
        columnMappings.Add("Productid", "[Productid]");
        columnMappings.Add("Unitprice", "[Unitprice]");
        columnMappings.Add("Receivedqty", "[Receivedqty]");
        columnMappings.Add("Rejectedqty", "[Rejectedqty]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Purchasing].[PurchaseOrderDetail]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
