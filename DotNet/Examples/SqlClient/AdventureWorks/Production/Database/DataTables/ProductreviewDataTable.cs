using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class ProductreviewDataTable
{

    DataTable _dataTable;

    public ProductreviewDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ProductreviewDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var productreviewidColumn = new DataColumn("Productreviewid", typeof(int));
        productreviewidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productreviewidColumn);
        var productidColumn = new DataColumn("Productid", typeof(int));
        productidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productidColumn);
        var reviewernameColumn = new DataColumn("Reviewername", typeof(string));
        reviewernameColumn.AllowDBNull = false;
        dataTable.Columns.Add(reviewernameColumn);
        var reviewdateColumn = new DataColumn("Reviewdate", typeof(DateTime));
        reviewdateColumn.AllowDBNull = false;
        dataTable.Columns.Add(reviewdateColumn);
        var emailaddressColumn = new DataColumn("Emailaddress", typeof(string));
        emailaddressColumn.AllowDBNull = false;
        dataTable.Columns.Add(emailaddressColumn);
        var ratingColumn = new DataColumn("Rating", typeof(int));
        ratingColumn.AllowDBNull = false;
        dataTable.Columns.Add(ratingColumn);
        var commentsColumn = new DataColumn("Comments", typeof(string));
        dataTable.Columns.Add(commentsColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int productreviewid,
                        int productid,
                        string reviewername,
                        DateTime reviewdate,
                        string emailaddress,
                        int rating,
                        string? comments,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Productreviewid"] = productreviewid;
        row["Productid"] = productid;
        row["Reviewername"] = reviewername;
        row["Reviewdate"] = reviewdate;
        row["Emailaddress"] = emailaddress;
        row["Rating"] = rating;
        row["Comments"] = (object?)comments ?? DBNull.Value;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ProductreviewDataType data)
    {
        var row = _dataTable.NewRow();
        row["Productreviewid"] = data.Productreviewid;
        row["Productid"] = data.Productid;
        row["Reviewername"] = data.Reviewername;
        row["Reviewdate"] = data.Reviewdate;
        row["Emailaddress"] = data.Emailaddress;
        row["Rating"] = data.Rating;
        row["Comments"] = (object?)data.Comments ?? DBNull.Value;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Productreviewid", "[Productreviewid]");
        columnMappings.Add("Productid", "[Productid]");
        columnMappings.Add("Reviewername", "[Reviewername]");
        columnMappings.Add("Reviewdate", "[Reviewdate]");
        columnMappings.Add("Emailaddress", "[Emailaddress]");
        columnMappings.Add("Rating", "[Rating]");
        columnMappings.Add("Comments", "[Comments]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[ProductReview]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
