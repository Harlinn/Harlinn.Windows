using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class ProductmodelillustrationDataTable
{

    DataTable _dataTable;

    public ProductmodelillustrationDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ProductmodelillustrationDataTable()
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
        var illustrationidColumn = new DataColumn("Illustrationid", typeof(int));
        illustrationidColumn.AllowDBNull = false;
        dataTable.Columns.Add(illustrationidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int productmodelid,
                        int illustrationid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Productmodelid"] = productmodelid;
        row["Illustrationid"] = illustrationid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ProductmodelillustrationDataType data)
    {
        var row = _dataTable.NewRow();
        row["Productmodelid"] = data.Productmodelid;
        row["Illustrationid"] = data.Illustrationid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Productmodelid", "[Productmodelid]");
        columnMappings.Add("Illustrationid", "[Illustrationid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[ProductModelIllustration]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
