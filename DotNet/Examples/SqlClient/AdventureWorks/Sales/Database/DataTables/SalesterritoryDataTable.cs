using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Sales.Database.DataTables;

public class SalesterritoryDataTable
{

    DataTable _dataTable;

    public SalesterritoryDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public SalesterritoryDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var territoryidColumn = new DataColumn("Territoryid", typeof(int));
        territoryidColumn.AllowDBNull = false;
        dataTable.Columns.Add(territoryidColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var countryregioncodeColumn = new DataColumn("Countryregioncode", typeof(string));
        countryregioncodeColumn.AllowDBNull = false;
        dataTable.Columns.Add(countryregioncodeColumn);
        var groupColumn = new DataColumn("Group", typeof(string));
        groupColumn.AllowDBNull = false;
        dataTable.Columns.Add(groupColumn);
        var salesytdColumn = new DataColumn("Salesytd", typeof(decimal));
        salesytdColumn.AllowDBNull = false;
        dataTable.Columns.Add(salesytdColumn);
        var saleslastyearColumn = new DataColumn("Saleslastyear", typeof(decimal));
        saleslastyearColumn.AllowDBNull = false;
        dataTable.Columns.Add(saleslastyearColumn);
        var costytdColumn = new DataColumn("Costytd", typeof(decimal));
        costytdColumn.AllowDBNull = false;
        dataTable.Columns.Add(costytdColumn);
        var costlastyearColumn = new DataColumn("Costlastyear", typeof(decimal));
        costlastyearColumn.AllowDBNull = false;
        dataTable.Columns.Add(costlastyearColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int territoryid,
                        string name,
                        string countryregioncode,
                        string group,
                        decimal salesytd,
                        decimal saleslastyear,
                        decimal costytd,
                        decimal costlastyear,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Territoryid"] = territoryid;
        row["Name"] = name;
        row["Countryregioncode"] = countryregioncode;
        row["Group"] = group;
        row["Salesytd"] = salesytd;
        row["Saleslastyear"] = saleslastyear;
        row["Costytd"] = costytd;
        row["Costlastyear"] = costlastyear;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(SalesterritoryDataType data)
    {
        var row = _dataTable.NewRow();
        row["Territoryid"] = data.Territoryid;
        row["Name"] = data.Name;
        row["Countryregioncode"] = data.Countryregioncode;
        row["Group"] = data.Group;
        row["Salesytd"] = data.Salesytd;
        row["Saleslastyear"] = data.Saleslastyear;
        row["Costytd"] = data.Costytd;
        row["Costlastyear"] = data.Costlastyear;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Territoryid", "[Territoryid]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Countryregioncode", "[Countryregioncode]");
        columnMappings.Add("Group", "[Group]");
        columnMappings.Add("Salesytd", "[Salesytd]");
        columnMappings.Add("Saleslastyear", "[Saleslastyear]");
        columnMappings.Add("Costytd", "[Costytd]");
        columnMappings.Add("Costlastyear", "[Costlastyear]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Sales].[SalesTerritory]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
