using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Sales.Database.DataTables;

public class SalespersonDataTable
{

    DataTable _dataTable;

    public SalespersonDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public SalespersonDataTable()
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
        var territoryidColumn = new DataColumn("Territoryid", typeof(int));
        dataTable.Columns.Add(territoryidColumn);
        var salesquotaColumn = new DataColumn("Salesquota", typeof(decimal));
        dataTable.Columns.Add(salesquotaColumn);
        var bonusColumn = new DataColumn("Bonus", typeof(decimal));
        bonusColumn.AllowDBNull = false;
        dataTable.Columns.Add(bonusColumn);
        var commissionpctColumn = new DataColumn("Commissionpct", typeof(decimal));
        commissionpctColumn.AllowDBNull = false;
        dataTable.Columns.Add(commissionpctColumn);
        var salesytdColumn = new DataColumn("Salesytd", typeof(decimal));
        salesytdColumn.AllowDBNull = false;
        dataTable.Columns.Add(salesytdColumn);
        var saleslastyearColumn = new DataColumn("Saleslastyear", typeof(decimal));
        saleslastyearColumn.AllowDBNull = false;
        dataTable.Columns.Add(saleslastyearColumn);
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
                        int? territoryid,
                        decimal? salesquota,
                        decimal bonus,
                        decimal commissionpct,
                        decimal salesytd,
                        decimal saleslastyear,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = businessentityid;
        row["Territoryid"] = (object?)territoryid ?? DBNull.Value;
        row["Salesquota"] = (object?)salesquota ?? DBNull.Value;
        row["Bonus"] = bonus;
        row["Commissionpct"] = commissionpct;
        row["Salesytd"] = salesytd;
        row["Saleslastyear"] = saleslastyear;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(SalespersonDataType data)
    {
        var row = _dataTable.NewRow();
        row["Businessentityid"] = data.Businessentityid;
        row["Territoryid"] = (object?)data.Territoryid ?? DBNull.Value;
        row["Salesquota"] = (object?)data.Salesquota ?? DBNull.Value;
        row["Bonus"] = data.Bonus;
        row["Commissionpct"] = data.Commissionpct;
        row["Salesytd"] = data.Salesytd;
        row["Saleslastyear"] = data.Saleslastyear;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Businessentityid", "[Businessentityid]");
        columnMappings.Add("Territoryid", "[Territoryid]");
        columnMappings.Add("Salesquota", "[Salesquota]");
        columnMappings.Add("Bonus", "[Bonus]");
        columnMappings.Add("Commissionpct", "[Commissionpct]");
        columnMappings.Add("Salesytd", "[Salesytd]");
        columnMappings.Add("Saleslastyear", "[Saleslastyear]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[SalesPerson]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
