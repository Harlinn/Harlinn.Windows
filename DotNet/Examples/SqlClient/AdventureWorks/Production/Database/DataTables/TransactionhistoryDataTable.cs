using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class TransactionhistoryDataTable
{

    DataTable _dataTable;

    public TransactionhistoryDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public TransactionhistoryDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var transactionidColumn = new DataColumn("Transactionid", typeof(int));
        transactionidColumn.AllowDBNull = false;
        dataTable.Columns.Add(transactionidColumn);
        var productidColumn = new DataColumn("Productid", typeof(int));
        productidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productidColumn);
        var referenceorderidColumn = new DataColumn("Referenceorderid", typeof(int));
        referenceorderidColumn.AllowDBNull = false;
        dataTable.Columns.Add(referenceorderidColumn);
        var referenceorderlineidColumn = new DataColumn("Referenceorderlineid", typeof(int));
        referenceorderlineidColumn.AllowDBNull = false;
        dataTable.Columns.Add(referenceorderlineidColumn);
        var transactiondateColumn = new DataColumn("Transactiondate", typeof(DateTime));
        transactiondateColumn.AllowDBNull = false;
        dataTable.Columns.Add(transactiondateColumn);
        var transactiontypeColumn = new DataColumn("Transactiontype", typeof(string));
        transactiontypeColumn.AllowDBNull = false;
        dataTable.Columns.Add(transactiontypeColumn);
        var quantityColumn = new DataColumn("Quantity", typeof(int));
        quantityColumn.AllowDBNull = false;
        dataTable.Columns.Add(quantityColumn);
        var actualcostColumn = new DataColumn("Actualcost", typeof(decimal));
        actualcostColumn.AllowDBNull = false;
        dataTable.Columns.Add(actualcostColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int transactionid,
                        int productid,
                        int referenceorderid,
                        int referenceorderlineid,
                        DateTime transactiondate,
                        string transactiontype,
                        int quantity,
                        decimal actualcost,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Transactionid"] = transactionid;
        row["Productid"] = productid;
        row["Referenceorderid"] = referenceorderid;
        row["Referenceorderlineid"] = referenceorderlineid;
        row["Transactiondate"] = transactiondate;
        row["Transactiontype"] = transactiontype;
        row["Quantity"] = quantity;
        row["Actualcost"] = actualcost;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(TransactionhistoryDataType data)
    {
        var row = _dataTable.NewRow();
        row["Transactionid"] = data.Transactionid;
        row["Productid"] = data.Productid;
        row["Referenceorderid"] = data.Referenceorderid;
        row["Referenceorderlineid"] = data.Referenceorderlineid;
        row["Transactiondate"] = data.Transactiondate;
        row["Transactiontype"] = data.Transactiontype;
        row["Quantity"] = data.Quantity;
        row["Actualcost"] = data.Actualcost;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Transactionid", "[Transactionid]");
        columnMappings.Add("Productid", "[Productid]");
        columnMappings.Add("Referenceorderid", "[Referenceorderid]");
        columnMappings.Add("Referenceorderlineid", "[Referenceorderlineid]");
        columnMappings.Add("Transactiondate", "[Transactiondate]");
        columnMappings.Add("Transactiontype", "[Transactiontype]");
        columnMappings.Add("Quantity", "[Quantity]");
        columnMappings.Add("Actualcost", "[Actualcost]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[TransactionHistory]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
