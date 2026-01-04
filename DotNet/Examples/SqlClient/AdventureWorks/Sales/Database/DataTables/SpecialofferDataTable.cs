using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Sales.Database.DataTables;

public class SpecialofferDataTable
{

    DataTable _dataTable;

    public SpecialofferDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public SpecialofferDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var specialofferidColumn = new DataColumn("Specialofferid", typeof(int));
        specialofferidColumn.AllowDBNull = false;
        dataTable.Columns.Add(specialofferidColumn);
        var descriptionColumn = new DataColumn("Description", typeof(string));
        descriptionColumn.AllowDBNull = false;
        dataTable.Columns.Add(descriptionColumn);
        var discountpctColumn = new DataColumn("Discountpct", typeof(decimal));
        discountpctColumn.AllowDBNull = false;
        dataTable.Columns.Add(discountpctColumn);
        var typeColumn = new DataColumn("Type", typeof(string));
        typeColumn.AllowDBNull = false;
        dataTable.Columns.Add(typeColumn);
        var categoryColumn = new DataColumn("Category", typeof(string));
        categoryColumn.AllowDBNull = false;
        dataTable.Columns.Add(categoryColumn);
        var startdateColumn = new DataColumn("Startdate", typeof(DateTime));
        startdateColumn.AllowDBNull = false;
        dataTable.Columns.Add(startdateColumn);
        var enddateColumn = new DataColumn("Enddate", typeof(DateTime));
        enddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(enddateColumn);
        var minqtyColumn = new DataColumn("Minqty", typeof(int));
        minqtyColumn.AllowDBNull = false;
        dataTable.Columns.Add(minqtyColumn);
        var maxqtyColumn = new DataColumn("Maxqty", typeof(int));
        dataTable.Columns.Add(maxqtyColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int specialofferid,
                        string description,
                        decimal discountpct,
                        string type,
                        string category,
                        DateTime startdate,
                        DateTime enddate,
                        int minqty,
                        int? maxqty,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Specialofferid"] = specialofferid;
        row["Description"] = description;
        row["Discountpct"] = discountpct;
        row["Type"] = type;
        row["Category"] = category;
        row["Startdate"] = startdate;
        row["Enddate"] = enddate;
        row["Minqty"] = minqty;
        row["Maxqty"] = (object?)maxqty ?? DBNull.Value;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(SpecialofferDataType data)
    {
        var row = _dataTable.NewRow();
        row["Specialofferid"] = data.Specialofferid;
        row["Description"] = data.Description;
        row["Discountpct"] = data.Discountpct;
        row["Type"] = data.Type;
        row["Category"] = data.Category;
        row["Startdate"] = data.Startdate;
        row["Enddate"] = data.Enddate;
        row["Minqty"] = data.Minqty;
        row["Maxqty"] = (object?)data.Maxqty ?? DBNull.Value;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Specialofferid", "[Specialofferid]");
        columnMappings.Add("Description", "[Description]");
        columnMappings.Add("Discountpct", "[Discountpct]");
        columnMappings.Add("Type", "[Type]");
        columnMappings.Add("Category", "[Category]");
        columnMappings.Add("Startdate", "[Startdate]");
        columnMappings.Add("Enddate", "[Enddate]");
        columnMappings.Add("Minqty", "[Minqty]");
        columnMappings.Add("Maxqty", "[Maxqty]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[SpecialOffer]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
