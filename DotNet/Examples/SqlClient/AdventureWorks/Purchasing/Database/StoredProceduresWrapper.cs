using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Types;

using AdventureWorks.Dbo.Types;
using AdventureWorks.HumanResources.Types;
using AdventureWorks.Person.Types;
using AdventureWorks.Production.Types;
using AdventureWorks.Purchasing.Types;
using AdventureWorks.Sales.Types;

namespace AdventureWorks.Purchasing.Database;

public class StoredProcedures
{
    public static bool InsertProductvendor(SqlConnection sqlConnection, int productid,
        int businessentityid,
        int averageleadtime,
        decimal standardprice,
        decimal? lastreceiptcost,
        DateTime? lastreceiptdate,
        int minorderqty,
        int maxorderqty,
        int? onorderqty,
        string unitmeasurecode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[InsertProductVendor]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@averageleadtime", averageleadtime);
        command.Parameters.AddDecimal("@standardprice", standardprice);
        command.Parameters.AddDecimal("@lastreceiptcost", lastreceiptcost);
        command.Parameters.AddDateTime("@lastreceiptdate", lastreceiptdate);
        command.Parameters.AddInt32("@minorderqty", minorderqty);
        command.Parameters.AddInt32("@maxorderqty", maxorderqty);
        command.Parameters.AddInt32("@onorderqty", onorderqty);
        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertProductvendor(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.ProductvendorDataType data )
    {
        var dataProductid = data.Productid;
        var dataBusinessentityid = data.Businessentityid;
        var dataAverageleadtime = data.Averageleadtime;
        var dataStandardprice = data.Standardprice;
        var dataLastreceiptcost = data.Lastreceiptcost;
        var dataLastreceiptdate = data.Lastreceiptdate;
        var dataMinorderqty = data.Minorderqty;
        var dataMaxorderqty = data.Maxorderqty;
        var dataOnorderqty = data.Onorderqty;
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataModifieddate = data.Modifieddate;
        var result = InsertProductvendor( sqlConnection, 
                        dataProductid,
                        dataBusinessentityid,
                        dataAverageleadtime,
                        dataStandardprice,
                        dataLastreceiptcost,
                        dataLastreceiptdate,
                        dataMinorderqty,
                        dataMaxorderqty,
                        dataOnorderqty,
                        dataUnitmeasurecode,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateProductvendor(SqlConnection sqlConnection, int productid,
        int businessentityid,
        int averageleadtime,
        decimal standardprice,
        decimal? lastreceiptcost,
        DateTime? lastreceiptdate,
        int minorderqty,
        int maxorderqty,
        int? onorderqty,
        string unitmeasurecode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[UpdateProductVendor]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@averageleadtime", averageleadtime);
        command.Parameters.AddDecimal("@standardprice", standardprice);
        command.Parameters.AddDecimal("@lastreceiptcost", lastreceiptcost);
        command.Parameters.AddDateTime("@lastreceiptdate", lastreceiptdate);
        command.Parameters.AddInt32("@minorderqty", minorderqty);
        command.Parameters.AddInt32("@maxorderqty", maxorderqty);
        command.Parameters.AddInt32("@onorderqty", onorderqty);
        command.Parameters.AddNChar("@unitmeasurecode", unitmeasurecode, 3);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateProductvendor(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.ProductvendorDataType data )
    {
        var dataProductid = data.Productid;
        var dataBusinessentityid = data.Businessentityid;
        var dataAverageleadtime = data.Averageleadtime;
        var dataStandardprice = data.Standardprice;
        var dataLastreceiptcost = data.Lastreceiptcost;
        var dataLastreceiptdate = data.Lastreceiptdate;
        var dataMinorderqty = data.Minorderqty;
        var dataMaxorderqty = data.Maxorderqty;
        var dataOnorderqty = data.Onorderqty;
        var dataUnitmeasurecode = data.Unitmeasurecode;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateProductvendor( sqlConnection, 
                        dataProductid,
                        dataBusinessentityid,
                        dataAverageleadtime,
                        dataStandardprice,
                        dataLastreceiptcost,
                        dataLastreceiptdate,
                        dataMinorderqty,
                        dataMaxorderqty,
                        dataOnorderqty,
                        dataUnitmeasurecode,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteProductvendor(SqlConnection sqlConnection, int productid,
        int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeleteProductVendor]";

        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteProductvendor(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.ProductvendorDataType data )
    {
        var dataProductid = data.Productid;
        var dataBusinessentityid = data.Businessentityid;
        var result = DeleteProductvendor( sqlConnection, 
                        dataProductid,
                        dataBusinessentityid );

        return result;
    }

    public static bool InsertPurchaseorderdetail(SqlConnection sqlConnection, int purchaseorderid,
        ref int purchaseorderdetailid,
        DateTime duedate,
        short orderqty,
        int productid,
        decimal unitprice,
        decimal linetotal,
        decimal receivedqty,
        decimal rejectedqty,
        decimal stockedqty,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[InsertPurchaseOrderDetail]";

        command.Parameters.AddInt32("@purchaseorderid", purchaseorderid);
        var purchaseorderdetailidParameter = command.Parameters.AddInt32("@purchaseorderdetailid");
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddInt16("@orderqty", orderqty);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDecimal("@unitprice", unitprice);
        command.Parameters.AddDecimal("@linetotal", linetotal);
        command.Parameters.AddDecimal("@receivedqty", receivedqty);
        command.Parameters.AddDecimal("@rejectedqty", rejectedqty);
        command.Parameters.AddDecimal("@stockedqty", stockedqty);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            purchaseorderdetailid = (int)purchaseorderdetailidParameter.Value;
        }
        return result;
    }

    public static bool InsertPurchaseorderdetail(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.PurchaseorderdetailDataType data )
    {
        var dataPurchaseorderid = data.Purchaseorderid;
        var dataPurchaseorderdetailid = data.Purchaseorderdetailid;
        var dataDuedate = data.Duedate;
        var dataOrderqty = data.Orderqty;
        var dataProductid = data.Productid;
        var dataUnitprice = data.Unitprice;
        var dataLinetotal = data.Linetotal;
        var dataReceivedqty = data.Receivedqty;
        var dataRejectedqty = data.Rejectedqty;
        var dataStockedqty = data.Stockedqty;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPurchaseorderdetail( sqlConnection, 
                        dataPurchaseorderid,
                        ref dataPurchaseorderdetailid,
                        dataDuedate,
                        dataOrderqty,
                        dataProductid,
                        dataUnitprice,
                        dataLinetotal,
                        dataReceivedqty,
                        dataRejectedqty,
                        dataStockedqty,
                        dataModifieddate );
        data.Purchaseorderdetailid = dataPurchaseorderdetailid;

        return result;
    }

    public static bool UpdatePurchaseorderdetail(SqlConnection sqlConnection, int purchaseorderid,
        int purchaseorderdetailid,
        DateTime duedate,
        short orderqty,
        int productid,
        decimal unitprice,
        decimal linetotal,
        decimal receivedqty,
        decimal rejectedqty,
        decimal stockedqty,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[UpdatePurchaseOrderDetail]";

        command.Parameters.AddInt32("@purchaseorderid", purchaseorderid);
        command.Parameters.AddInt32("@purchaseorderdetailid", purchaseorderdetailid);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddInt16("@orderqty", orderqty);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDecimal("@unitprice", unitprice);
        command.Parameters.AddDecimal("@linetotal", linetotal);
        command.Parameters.AddDecimal("@receivedqty", receivedqty);
        command.Parameters.AddDecimal("@rejectedqty", rejectedqty);
        command.Parameters.AddDecimal("@stockedqty", stockedqty);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePurchaseorderdetail(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.PurchaseorderdetailDataType data )
    {
        var dataPurchaseorderid = data.Purchaseorderid;
        var dataPurchaseorderdetailid = data.Purchaseorderdetailid;
        var dataDuedate = data.Duedate;
        var dataOrderqty = data.Orderqty;
        var dataProductid = data.Productid;
        var dataUnitprice = data.Unitprice;
        var dataLinetotal = data.Linetotal;
        var dataReceivedqty = data.Receivedqty;
        var dataRejectedqty = data.Rejectedqty;
        var dataStockedqty = data.Stockedqty;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePurchaseorderdetail( sqlConnection, 
                        dataPurchaseorderid,
                        dataPurchaseorderdetailid,
                        dataDuedate,
                        dataOrderqty,
                        dataProductid,
                        dataUnitprice,
                        dataLinetotal,
                        dataReceivedqty,
                        dataRejectedqty,
                        dataStockedqty,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePurchaseorderdetail(SqlConnection sqlConnection, int purchaseorderid,
        int purchaseorderdetailid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeletePurchaseOrderDetail]";

        command.Parameters.AddInt32("@purchaseorderid", purchaseorderid);
        command.Parameters.AddInt32("@purchaseorderdetailid", purchaseorderdetailid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePurchaseorderdetail(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.PurchaseorderdetailDataType data )
    {
        var dataPurchaseorderid = data.Purchaseorderid;
        var dataPurchaseorderdetailid = data.Purchaseorderdetailid;
        var result = DeletePurchaseorderdetail( sqlConnection, 
                        dataPurchaseorderid,
                        dataPurchaseorderdetailid );

        return result;
    }

    public static bool InsertPurchaseorderheader(SqlConnection sqlConnection, ref int purchaseorderid,
        byte revisionnumber,
        byte status,
        int employeeid,
        int vendorid,
        int shipmethodid,
        DateTime orderdate,
        DateTime? shipdate,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        decimal totaldue,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[InsertPurchaseOrderHeader]";

        var purchaseorderidParameter = command.Parameters.AddInt32("@purchaseorderid");
        command.Parameters.AddByte("@revisionnumber", revisionnumber);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddInt32("@employeeid", employeeid);
        command.Parameters.AddInt32("@vendorid", vendorid);
        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddDateTime("@orderdate", orderdate);
        command.Parameters.AddDateTime("@shipdate", shipdate);
        command.Parameters.AddDecimal("@subtotal", subtotal);
        command.Parameters.AddDecimal("@taxamt", taxamt);
        command.Parameters.AddDecimal("@freight", freight);
        command.Parameters.AddDecimal("@totaldue", totaldue);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            purchaseorderid = (int)purchaseorderidParameter.Value;
        }
        return result;
    }

    public static bool InsertPurchaseorderheader(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.PurchaseorderheaderDataType data )
    {
        var dataPurchaseorderid = data.Purchaseorderid;
        var dataRevisionnumber = data.Revisionnumber;
        var dataStatus = data.Status;
        var dataEmployeeid = data.Employeeid;
        var dataVendorid = data.Vendorid;
        var dataShipmethodid = data.Shipmethodid;
        var dataOrderdate = data.Orderdate;
        var dataShipdate = data.Shipdate;
        var dataSubtotal = data.Subtotal;
        var dataTaxamt = data.Taxamt;
        var dataFreight = data.Freight;
        var dataTotaldue = data.Totaldue;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPurchaseorderheader( sqlConnection, 
                        ref dataPurchaseorderid,
                        dataRevisionnumber,
                        dataStatus,
                        dataEmployeeid,
                        dataVendorid,
                        dataShipmethodid,
                        dataOrderdate,
                        dataShipdate,
                        dataSubtotal,
                        dataTaxamt,
                        dataFreight,
                        dataTotaldue,
                        dataModifieddate );
        data.Purchaseorderid = dataPurchaseorderid;

        return result;
    }

    public static bool UpdatePurchaseorderheader(SqlConnection sqlConnection, int purchaseorderid,
        byte revisionnumber,
        byte status,
        int employeeid,
        int vendorid,
        int shipmethodid,
        DateTime orderdate,
        DateTime? shipdate,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        decimal totaldue,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[UpdatePurchaseOrderHeader]";

        command.Parameters.AddInt32("@purchaseorderid", purchaseorderid);
        command.Parameters.AddByte("@revisionnumber", revisionnumber);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddInt32("@employeeid", employeeid);
        command.Parameters.AddInt32("@vendorid", vendorid);
        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddDateTime("@orderdate", orderdate);
        command.Parameters.AddDateTime("@shipdate", shipdate);
        command.Parameters.AddDecimal("@subtotal", subtotal);
        command.Parameters.AddDecimal("@taxamt", taxamt);
        command.Parameters.AddDecimal("@freight", freight);
        command.Parameters.AddDecimal("@totaldue", totaldue);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePurchaseorderheader(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.PurchaseorderheaderDataType data )
    {
        var dataPurchaseorderid = data.Purchaseorderid;
        var dataRevisionnumber = data.Revisionnumber;
        var dataStatus = data.Status;
        var dataEmployeeid = data.Employeeid;
        var dataVendorid = data.Vendorid;
        var dataShipmethodid = data.Shipmethodid;
        var dataOrderdate = data.Orderdate;
        var dataShipdate = data.Shipdate;
        var dataSubtotal = data.Subtotal;
        var dataTaxamt = data.Taxamt;
        var dataFreight = data.Freight;
        var dataTotaldue = data.Totaldue;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePurchaseorderheader( sqlConnection, 
                        dataPurchaseorderid,
                        dataRevisionnumber,
                        dataStatus,
                        dataEmployeeid,
                        dataVendorid,
                        dataShipmethodid,
                        dataOrderdate,
                        dataShipdate,
                        dataSubtotal,
                        dataTaxamt,
                        dataFreight,
                        dataTotaldue,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePurchaseorderheader(SqlConnection sqlConnection, int purchaseorderid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeletePurchaseOrderHeader]";

        command.Parameters.AddInt32("@purchaseorderid", purchaseorderid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePurchaseorderheader(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.PurchaseorderheaderDataType data )
    {
        var dataPurchaseorderid = data.Purchaseorderid;
        var result = DeletePurchaseorderheader( sqlConnection, 
                        dataPurchaseorderid );

        return result;
    }

    public static bool InsertShipmethod(SqlConnection sqlConnection, ref int shipmethodid,
        string name,
        decimal shipbase,
        decimal shiprate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[InsertShipMethod]";

        var shipmethodidParameter = command.Parameters.AddInt32("@shipmethodid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDecimal("@shipbase", shipbase);
        command.Parameters.AddDecimal("@shiprate", shiprate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            shipmethodid = (int)shipmethodidParameter.Value;
        }
        return result;
    }

    public static bool InsertShipmethod(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.ShipmethodDataType data )
    {
        var dataShipmethodid = data.Shipmethodid;
        var dataName = data.Name;
        var dataShipbase = data.Shipbase;
        var dataShiprate = data.Shiprate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertShipmethod( sqlConnection, 
                        ref dataShipmethodid,
                        dataName,
                        dataShipbase,
                        dataShiprate,
                        dataRowguid,
                        dataModifieddate );
        data.Shipmethodid = dataShipmethodid;

        return result;
    }

    public static bool UpdateShipmethod(SqlConnection sqlConnection, int shipmethodid,
        string name,
        decimal shipbase,
        decimal shiprate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[UpdateShipMethod]";

        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDecimal("@shipbase", shipbase);
        command.Parameters.AddDecimal("@shiprate", shiprate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateShipmethod(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.ShipmethodDataType data )
    {
        var dataShipmethodid = data.Shipmethodid;
        var dataName = data.Name;
        var dataShipbase = data.Shipbase;
        var dataShiprate = data.Shiprate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateShipmethod( sqlConnection, 
                        dataShipmethodid,
                        dataName,
                        dataShipbase,
                        dataShiprate,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteShipmethod(SqlConnection sqlConnection, int shipmethodid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeleteShipMethod]";

        command.Parameters.AddInt32("@shipmethodid", shipmethodid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteShipmethod(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.ShipmethodDataType data )
    {
        var dataShipmethodid = data.Shipmethodid;
        var result = DeleteShipmethod( sqlConnection, 
                        dataShipmethodid );

        return result;
    }

    public static bool InsertVendor(SqlConnection sqlConnection, int businessentityid,
        string accountnumber,
        string name,
        byte creditrating,
        bool preferredvendorstatus,
        bool activeflag,
        string? purchasingwebserviceurl,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[InsertVendor]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@accountnumber", accountnumber, 15);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddByte("@creditrating", creditrating);
        command.Parameters.AddBoolean("@preferredvendorstatus", preferredvendorstatus);
        command.Parameters.AddBoolean("@activeflag", activeflag);
        command.Parameters.AddNVarChar("@purchasingwebserviceurl", purchasingwebserviceurl, 1024);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool InsertVendor(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.VendorDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataAccountnumber = data.Accountnumber;
        var dataName = data.Name;
        var dataCreditrating = data.Creditrating;
        var dataPreferredvendorstatus = data.Preferredvendorstatus;
        var dataActiveflag = data.Activeflag;
        var dataPurchasingwebserviceurl = data.Purchasingwebserviceurl;
        var dataModifieddate = data.Modifieddate;
        var result = InsertVendor( sqlConnection, 
                        dataBusinessentityid,
                        dataAccountnumber,
                        dataName,
                        dataCreditrating,
                        dataPreferredvendorstatus,
                        dataActiveflag,
                        dataPurchasingwebserviceurl,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateVendor(SqlConnection sqlConnection, int businessentityid,
        string accountnumber,
        string name,
        byte creditrating,
        bool preferredvendorstatus,
        bool activeflag,
        string? purchasingwebserviceurl,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[UpdateVendor]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@accountnumber", accountnumber, 15);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddByte("@creditrating", creditrating);
        command.Parameters.AddBoolean("@preferredvendorstatus", preferredvendorstatus);
        command.Parameters.AddBoolean("@activeflag", activeflag);
        command.Parameters.AddNVarChar("@purchasingwebserviceurl", purchasingwebserviceurl, 1024);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateVendor(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.VendorDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataAccountnumber = data.Accountnumber;
        var dataName = data.Name;
        var dataCreditrating = data.Creditrating;
        var dataPreferredvendorstatus = data.Preferredvendorstatus;
        var dataActiveflag = data.Activeflag;
        var dataPurchasingwebserviceurl = data.Purchasingwebserviceurl;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateVendor( sqlConnection, 
                        dataBusinessentityid,
                        dataAccountnumber,
                        dataName,
                        dataCreditrating,
                        dataPreferredvendorstatus,
                        dataActiveflag,
                        dataPurchasingwebserviceurl,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteVendor(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Purchasing].[DeleteVendor]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteVendor(SqlConnection sqlConnection, AdventureWorks.Purchasing.Types.VendorDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var result = DeleteVendor( sqlConnection, 
                        dataBusinessentityid );

        return result;
    }

}
