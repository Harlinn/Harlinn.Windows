using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Sales.Database.DataTables;

public class SalespersonquotahistoryDataTable
{

    DataTable _dataTable;

    public SalespersonquotahistoryDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public SalespersonquotahistoryDataTable()
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
        var quotadateColumn = new DataColumn("Quotadate", typeof(DateTime));
        quotadateColumn.AllowDBNull = false;
        dataTable.Columns.Add(quotadateColumn);
        var salesquotaColumn = new DataColumn("Salesquota", typeof(decimal));
        salesquotaColumn.AllowDBNull = false;
        dataTable.Columns.Add(salesquotaColumn);
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
                        DateTime quotadate,
                        decimal salesquota,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = businessentityid;
        row["Quotadate"] = quotadate;
        row["Salesquota"] = salesquota;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(SalespersonquotahistoryDataType data)
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = data.Businessentityid;
        row["Quotadate"] = data.Quotadate;
        row["Salesquota"] = data.Salesquota;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Quotadate", "[Quotadate]");
        columnMappings.Add("Salesquota", "[Salesquota]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[SalesPersonQuotaHistory]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
