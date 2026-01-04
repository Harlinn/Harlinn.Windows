using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class ProductmodelDataTable
{

    DataTable _dataTable;

    public ProductmodelDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ProductmodelDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var productmodelidColumn = new DataColumn("Productmodelid", typeof(int));
        productmodelidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productmodelidColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var catalogdescriptionColumn = new DataColumn("Catalogdescription", typeof(SqlXml));
        dataTable.Columns.Add(catalogdescriptionColumn);
        var instructionsColumn = new DataColumn("Instructions", typeof(SqlXml));
        dataTable.Columns.Add(instructionsColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int productmodelid,
                        string name,
                        SqlXml? catalogdescription,
                        SqlXml? instructions,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Productmodelid"] = productmodelid;
        row["Name"] = name;
        row["Catalogdescription"] = (object?)catalogdescription ?? DBNull.Value;
        row["Instructions"] = (object?)instructions ?? DBNull.Value;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ProductmodelDataType data)
    {
        var row = _dataTable.NewRow();
        row["Productmodelid"] = data.Productmodelid;
        row["Name"] = data.Name;
        row["Catalogdescription"] = (object?)data.Catalogdescription ?? DBNull.Value;
        row["Instructions"] = (object?)data.Instructions ?? DBNull.Value;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Productmodelid", "[Productmodelid]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Catalogdescription", "[Catalogdescription]");
        columnMappings.Add("Instructions", "[Instructions]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[ProductModel]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
