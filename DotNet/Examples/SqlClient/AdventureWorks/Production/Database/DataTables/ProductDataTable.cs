using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using System.Data.SqlTypes;
using AdventureWorks.Production.Types;

namespace AdventureWorks.Production.Database.DataTables;

public class ProductDataTable
{

    DataTable _dataTable;

    public ProductDataTable(DataTable dataTable)
    {
        _dataTable = dataTable;
    }
    public ProductDataTable()
    {
        _dataTable = CreateDataTable();
    }
    public DataTable DataTable => _dataTable;

    public static DataTable CreateDataTable( )
    {
        var dataTable = new DataTable();

        var productidColumn = new DataColumn("Productid", typeof(int));
        productidColumn.AllowDBNull = false;
        dataTable.Columns.Add(productidColumn);
        var nameColumn = new DataColumn("Name", typeof(string));
        nameColumn.AllowDBNull = false;
        dataTable.Columns.Add(nameColumn);
        var productnumberColumn = new DataColumn("Productnumber", typeof(string));
        productnumberColumn.AllowDBNull = false;
        dataTable.Columns.Add(productnumberColumn);
        var makeflagColumn = new DataColumn("Makeflag", typeof(bool));
        makeflagColumn.AllowDBNull = false;
        dataTable.Columns.Add(makeflagColumn);
        var finishedgoodsflagColumn = new DataColumn("Finishedgoodsflag", typeof(bool));
        finishedgoodsflagColumn.AllowDBNull = false;
        dataTable.Columns.Add(finishedgoodsflagColumn);
        var colorColumn = new DataColumn("Color", typeof(string));
        dataTable.Columns.Add(colorColumn);
        var safetystocklevelColumn = new DataColumn("Safetystocklevel", typeof(short));
        safetystocklevelColumn.AllowDBNull = false;
        dataTable.Columns.Add(safetystocklevelColumn);
        var reorderpointColumn = new DataColumn("Reorderpoint", typeof(short));
        reorderpointColumn.AllowDBNull = false;
        dataTable.Columns.Add(reorderpointColumn);
        var standardcostColumn = new DataColumn("Standardcost", typeof(decimal));
        standardcostColumn.AllowDBNull = false;
        dataTable.Columns.Add(standardcostColumn);
        var listpriceColumn = new DataColumn("Listprice", typeof(decimal));
        listpriceColumn.AllowDBNull = false;
        dataTable.Columns.Add(listpriceColumn);
        var sizeColumn = new DataColumn("Size", typeof(string));
        dataTable.Columns.Add(sizeColumn);
        var sizeunitmeasurecodeColumn = new DataColumn("Sizeunitmeasurecode", typeof(string));
        dataTable.Columns.Add(sizeunitmeasurecodeColumn);
        var weightunitmeasurecodeColumn = new DataColumn("Weightunitmeasurecode", typeof(string));
        dataTable.Columns.Add(weightunitmeasurecodeColumn);
        var weightColumn = new DataColumn("Weight", typeof(decimal));
        dataTable.Columns.Add(weightColumn);
        var daystomanufactureColumn = new DataColumn("Daystomanufacture", typeof(int));
        daystomanufactureColumn.AllowDBNull = false;
        dataTable.Columns.Add(daystomanufactureColumn);
        var productlineColumn = new DataColumn("Productline", typeof(string));
        dataTable.Columns.Add(productlineColumn);
        var class__Column = new DataColumn("Class", typeof(string));
        dataTable.Columns.Add(class__Column);
        var styleColumn = new DataColumn("Style", typeof(string));
        dataTable.Columns.Add(styleColumn);
        var productsubcategoryidColumn = new DataColumn("Productsubcategoryid", typeof(int));
        dataTable.Columns.Add(productsubcategoryidColumn);
        var productmodelidColumn = new DataColumn("Productmodelid", typeof(int));
        dataTable.Columns.Add(productmodelidColumn);
        var sellstartdateColumn = new DataColumn("Sellstartdate", typeof(DateTime));
        sellstartdateColumn.AllowDBNull = false;
        dataTable.Columns.Add(sellstartdateColumn);
        var sellenddateColumn = new DataColumn("Sellenddate", typeof(DateTime));
        dataTable.Columns.Add(sellenddateColumn);
        var discontinueddateColumn = new DataColumn("Discontinueddate", typeof(DateTime));
        dataTable.Columns.Add(discontinueddateColumn);
        var rowguidColumn = new DataColumn("Rowguid", typeof(Guid));
        rowguidColumn.AllowDBNull = false;
        dataTable.Columns.Add(rowguidColumn);
        var modifieddateColumn = new DataColumn("Modifieddate", typeof(DateTime));
        modifieddateColumn.AllowDBNull = false;
        dataTable.Columns.Add(modifieddateColumn);

        return dataTable;
    }

    public void AddRow( 
                        int productid,
                        string name,
                        string productnumber,
                        bool makeflag,
                        bool finishedgoodsflag,
                        string? color,
                        short safetystocklevel,
                        short reorderpoint,
                        decimal standardcost,
                        decimal listprice,
                        string? size,
                        string? sizeunitmeasurecode,
                        string? weightunitmeasurecode,
                        decimal? weight,
                        int daystomanufacture,
                        string? productline,
                        string? class__,
                        string? style,
                        int? productsubcategoryid,
                        int? productmodelid,
                        DateTime sellstartdate,
                        DateTime? sellenddate,
                        DateTime? discontinueddate,
                        Guid rowguid,
                        DateTime modifieddate
                        )
    {
        var row = _dataTable.NewRow();
        row["Productid"] = productid;
        row["Name"] = name;
        row["Productnumber"] = productnumber;
        row["Makeflag"] = makeflag;
        row["Finishedgoodsflag"] = finishedgoodsflag;
        row["Color"] = (object?)color ?? DBNull.Value;
        row["Safetystocklevel"] = safetystocklevel;
        row["Reorderpoint"] = reorderpoint;
        row["Standardcost"] = standardcost;
        row["Listprice"] = listprice;
        row["Size"] = (object?)size ?? DBNull.Value;
        row["Sizeunitmeasurecode"] = (object?)sizeunitmeasurecode ?? DBNull.Value;
        row["Weightunitmeasurecode"] = (object?)weightunitmeasurecode ?? DBNull.Value;
        row["Weight"] = (object?)weight ?? DBNull.Value;
        row["Daystomanufacture"] = daystomanufacture;
        row["Productline"] = (object?)productline ?? DBNull.Value;
        row["Class"] = (object?)class__ ?? DBNull.Value;
        row["Style"] = (object?)style ?? DBNull.Value;
        row["Productsubcategoryid"] = (object?)productsubcategoryid ?? DBNull.Value;
        row["Productmodelid"] = (object?)productmodelid ?? DBNull.Value;
        row["Sellstartdate"] = sellstartdate;
        row["Sellenddate"] = (object?)sellenddate ?? DBNull.Value;
        row["Discontinueddate"] = (object?)discontinueddate ?? DBNull.Value;
        row["Rowguid"] = rowguid;
        row["Modifieddate"] = modifieddate;
        _dataTable.Rows.Add(row);
    }

    public void AddRow(ProductDataType data)
    {
        var row = _dataTable.NewRow();
        row["Productid"] = data.Productid;
        row["Name"] = data.Name;
        row["Productnumber"] = data.Productnumber;
        row["Makeflag"] = data.Makeflag;
        row["Finishedgoodsflag"] = data.Finishedgoodsflag;
        row["Color"] = (object?)data.Color ?? DBNull.Value;
        row["Safetystocklevel"] = data.Safetystocklevel;
        row["Reorderpoint"] = data.Reorderpoint;
        row["Standardcost"] = data.Standardcost;
        row["Listprice"] = data.Listprice;
        row["Size"] = (object?)data.Size ?? DBNull.Value;
        row["Sizeunitmeasurecode"] = (object?)data.Sizeunitmeasurecode ?? DBNull.Value;
        row["Weightunitmeasurecode"] = (object?)data.Weightunitmeasurecode ?? DBNull.Value;
        row["Weight"] = (object?)data.Weight ?? DBNull.Value;
        row["Daystomanufacture"] = data.Daystomanufacture;
        row["Productline"] = (object?)data.Productline ?? DBNull.Value;
        row["Class"] = (object?)data.Class ?? DBNull.Value;
        row["Style"] = (object?)data.Style ?? DBNull.Value;
        row["Productsubcategoryid"] = (object?)data.Productsubcategoryid ?? DBNull.Value;
        row["Productmodelid"] = (object?)data.Productmodelid ?? DBNull.Value;
        row["Sellstartdate"] = data.Sellstartdate;
        row["Sellenddate"] = (object?)data.Sellenddate ?? DBNull.Value;
        row["Discontinueddate"] = (object?)data.Discontinueddate ?? DBNull.Value;
        row["Rowguid"] = data.Rowguid;
        row["Modifieddate"] = data.Modifieddate;
        _dataTable.Rows.Add(row);
    }

    public static void AssignMapping(SqlBulkCopy sqlBulkCopy)
    {
        var columnMappings = sqlBulkCopy.ColumnMappings;
        columnMappings.Add("Productid", "[Productid]");
        columnMappings.Add("Name", "[Name]");
        columnMappings.Add("Productnumber", "[Productnumber]");
        columnMappings.Add("Makeflag", "[Makeflag]");
        columnMappings.Add("Finishedgoodsflag", "[Finishedgoodsflag]");
        columnMappings.Add("Color", "[Color]");
        columnMappings.Add("Safetystocklevel", "[Safetystocklevel]");
        columnMappings.Add("Reorderpoint", "[Reorderpoint]");
        columnMappings.Add("Standardcost", "[Standardcost]");
        columnMappings.Add("Listprice", "[Listprice]");
        columnMappings.Add("Size", "[Size]");
        columnMappings.Add("Sizeunitmeasurecode", "[Sizeunitmeasurecode]");
        columnMappings.Add("Weightunitmeasurecode", "[Weightunitmeasurecode]");
        columnMappings.Add("Weight", "[Weight]");
        columnMappings.Add("Daystomanufacture", "[Daystomanufacture]");
        columnMappings.Add("Productline", "[Productline]");
        columnMappings.Add("Class", "[Class]");
        columnMappings.Add("Style", "[Style]");
        columnMappings.Add("Productsubcategoryid", "[Productsubcategoryid]");
        columnMappings.Add("Productmodelid", "[Productmodelid]");
        columnMappings.Add("Sellstartdate", "[Sellstartdate]");
        columnMappings.Add("Sellenddate", "[Sellenddate]");
        columnMappings.Add("Discontinueddate", "[Discontinueddate]");
        columnMappings.Add("Rowguid", "[Rowguid]");
        columnMappings.Add("Modifieddate", "[Modifieddate]");
    }

    public static SqlBulkCopy CreateSqlBulkCopy(SqlConnection sqlConnection, string? destinationTableName = null)
    {
        var sqlBulkCopy = new SqlBulkCopy(sqlConnection)
        {
            DestinationTableName = destinationTableName ?? "[Production].[Product]"
        };
        AssignMapping(sqlBulkCopy);
        return sqlBulkCopy;
    }

}
