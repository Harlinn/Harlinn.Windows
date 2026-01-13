/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
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

namespace AdventureWorks.Sales.Database;

public class StoredProceduresWrapper
{
    public static bool InsertCountryregioncurrency(SqlConnection sqlConnection, string countryregioncode,
        string currencycode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertCountryRegionCurrency]";

        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNChar("@currencycode", currencycode, 3);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeCountryregioncurrency(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.CountryregioncurrencyDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeCountryRegionCurrency]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertCountryregioncurrency(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CountryregioncurrencyDataType data )
    {
        var dataCountryregioncode = data.Countryregioncode;
        var dataCurrencycode = data.Currencycode;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCountryregioncurrency( sqlConnection, 
                        dataCountryregioncode,
                        dataCurrencycode,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateCountryregioncurrency(SqlConnection sqlConnection, string countryregioncode,
        string currencycode,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateCountryRegionCurrency]";

        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNChar("@currencycode", currencycode, 3);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCountryregioncurrency(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CountryregioncurrencyDataType data )
    {
        var dataCountryregioncode = data.Countryregioncode;
        var dataCurrencycode = data.Currencycode;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCountryregioncurrency( sqlConnection, 
                        dataCountryregioncode,
                        dataCurrencycode,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCountryregioncurrency(SqlConnection sqlConnection, string countryregioncode,
        string currencycode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCountryRegionCurrency]";

        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNChar("@currencycode", currencycode, 3);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCountryregioncurrency(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CountryregioncurrencyDataType data )
    {
        var dataCountryregioncode = data.Countryregioncode;
        var dataCurrencycode = data.Currencycode;
        var result = DeleteCountryregioncurrency( sqlConnection, 
                        dataCountryregioncode,
                        dataCurrencycode );

        return result;
    }

    public static bool InsertCreditcard(SqlConnection sqlConnection, ref int creditcardid,
        string cardtype,
        string cardnumber,
        byte expmonth,
        short expyear,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertCreditCard]";

        var creditcardidParameter = command.Parameters.AddInt32("@creditcardid");
        command.Parameters.AddNVarChar("@cardtype", cardtype, 50);
        command.Parameters.AddNVarChar("@cardnumber", cardnumber, 25);
        command.Parameters.AddByte("@expmonth", expmonth);
        command.Parameters.AddInt16("@expyear", expyear);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            creditcardid = (int)creditcardidParameter.Value;
        }
        return result;
    }

    public static bool MergeCreditcard(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.CreditcardDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeCreditCard]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertCreditcard(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CreditcardDataType data )
    {
        var dataCreditcardid = data.Creditcardid;
        var dataCardtype = data.Cardtype;
        var dataCardnumber = data.Cardnumber;
        var dataExpmonth = data.Expmonth;
        var dataExpyear = data.Expyear;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCreditcard( sqlConnection, 
                        ref dataCreditcardid,
                        dataCardtype,
                        dataCardnumber,
                        dataExpmonth,
                        dataExpyear,
                        dataModifieddate );
        data.Creditcardid = dataCreditcardid;

        return result;
    }

    public static bool UpdateCreditcard(SqlConnection sqlConnection, int creditcardid,
        string cardtype,
        string cardnumber,
        byte expmonth,
        short expyear,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateCreditCard]";

        command.Parameters.AddInt32("@creditcardid", creditcardid);
        command.Parameters.AddNVarChar("@cardtype", cardtype, 50);
        command.Parameters.AddNVarChar("@cardnumber", cardnumber, 25);
        command.Parameters.AddByte("@expmonth", expmonth);
        command.Parameters.AddInt16("@expyear", expyear);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCreditcard(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CreditcardDataType data )
    {
        var dataCreditcardid = data.Creditcardid;
        var dataCardtype = data.Cardtype;
        var dataCardnumber = data.Cardnumber;
        var dataExpmonth = data.Expmonth;
        var dataExpyear = data.Expyear;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCreditcard( sqlConnection, 
                        dataCreditcardid,
                        dataCardtype,
                        dataCardnumber,
                        dataExpmonth,
                        dataExpyear,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCreditcard(SqlConnection sqlConnection, int creditcardid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCreditCard]";

        command.Parameters.AddInt32("@creditcardid", creditcardid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCreditcard(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CreditcardDataType data )
    {
        var dataCreditcardid = data.Creditcardid;
        var result = DeleteCreditcard( sqlConnection, 
                        dataCreditcardid );

        return result;
    }

    public static bool InsertCurrency(SqlConnection sqlConnection, string currencycode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertCurrency]";

        command.Parameters.AddNChar("@currencycode", currencycode, 3);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeCurrency(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.CurrencyDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeCurrency]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertCurrency(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CurrencyDataType data )
    {
        var dataCurrencycode = data.Currencycode;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCurrency( sqlConnection, 
                        dataCurrencycode,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateCurrency(SqlConnection sqlConnection, string currencycode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateCurrency]";

        command.Parameters.AddNChar("@currencycode", currencycode, 3);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCurrency(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CurrencyDataType data )
    {
        var dataCurrencycode = data.Currencycode;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCurrency( sqlConnection, 
                        dataCurrencycode,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCurrency(SqlConnection sqlConnection, string currencycode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCurrency]";

        command.Parameters.AddNChar("@currencycode", currencycode, 3);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCurrency(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CurrencyDataType data )
    {
        var dataCurrencycode = data.Currencycode;
        var result = DeleteCurrency( sqlConnection, 
                        dataCurrencycode );

        return result;
    }

    public static bool InsertCurrencyrate(SqlConnection sqlConnection, ref int currencyrateid,
        DateTime currencyratedate,
        string fromcurrencycode,
        string tocurrencycode,
        decimal averagerate,
        decimal endofdayrate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertCurrencyRate]";

        var currencyrateidParameter = command.Parameters.AddInt32("@currencyrateid");
        command.Parameters.AddDateTime("@currencyratedate", currencyratedate);
        command.Parameters.AddNChar("@fromcurrencycode", fromcurrencycode, 3);
        command.Parameters.AddNChar("@tocurrencycode", tocurrencycode, 3);
        command.Parameters.AddDecimal("@averagerate", averagerate);
        command.Parameters.AddDecimal("@endofdayrate", endofdayrate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            currencyrateid = (int)currencyrateidParameter.Value;
        }
        return result;
    }

    public static bool MergeCurrencyrate(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.CurrencyrateDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeCurrencyRate]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertCurrencyrate(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CurrencyrateDataType data )
    {
        var dataCurrencyrateid = data.Currencyrateid;
        var dataCurrencyratedate = data.Currencyratedate;
        var dataFromcurrencycode = data.Fromcurrencycode;
        var dataTocurrencycode = data.Tocurrencycode;
        var dataAveragerate = data.Averagerate;
        var dataEndofdayrate = data.Endofdayrate;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCurrencyrate( sqlConnection, 
                        ref dataCurrencyrateid,
                        dataCurrencyratedate,
                        dataFromcurrencycode,
                        dataTocurrencycode,
                        dataAveragerate,
                        dataEndofdayrate,
                        dataModifieddate );
        data.Currencyrateid = dataCurrencyrateid;

        return result;
    }

    public static bool UpdateCurrencyrate(SqlConnection sqlConnection, int currencyrateid,
        DateTime currencyratedate,
        string fromcurrencycode,
        string tocurrencycode,
        decimal averagerate,
        decimal endofdayrate,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateCurrencyRate]";

        command.Parameters.AddInt32("@currencyrateid", currencyrateid);
        command.Parameters.AddDateTime("@currencyratedate", currencyratedate);
        command.Parameters.AddNChar("@fromcurrencycode", fromcurrencycode, 3);
        command.Parameters.AddNChar("@tocurrencycode", tocurrencycode, 3);
        command.Parameters.AddDecimal("@averagerate", averagerate);
        command.Parameters.AddDecimal("@endofdayrate", endofdayrate);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCurrencyrate(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CurrencyrateDataType data )
    {
        var dataCurrencyrateid = data.Currencyrateid;
        var dataCurrencyratedate = data.Currencyratedate;
        var dataFromcurrencycode = data.Fromcurrencycode;
        var dataTocurrencycode = data.Tocurrencycode;
        var dataAveragerate = data.Averagerate;
        var dataEndofdayrate = data.Endofdayrate;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCurrencyrate( sqlConnection, 
                        dataCurrencyrateid,
                        dataCurrencyratedate,
                        dataFromcurrencycode,
                        dataTocurrencycode,
                        dataAveragerate,
                        dataEndofdayrate,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCurrencyrate(SqlConnection sqlConnection, int currencyrateid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCurrencyRate]";

        command.Parameters.AddInt32("@currencyrateid", currencyrateid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCurrencyrate(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CurrencyrateDataType data )
    {
        var dataCurrencyrateid = data.Currencyrateid;
        var result = DeleteCurrencyrate( sqlConnection, 
                        dataCurrencyrateid );

        return result;
    }

    public static bool InsertCustomer(SqlConnection sqlConnection, ref int customerid,
        int? personid,
        int? storeid,
        int? territoryid,
        string accountnumber,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertCustomer]";

        var customeridParameter = command.Parameters.AddInt32("@customerid");
        command.Parameters.AddInt32("@personid", personid);
        command.Parameters.AddInt32("@storeid", storeid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddVarChar("@accountnumber", accountnumber, 10);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            customerid = (int)customeridParameter.Value;
        }
        return result;
    }

    public static bool MergeCustomer(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.CustomerDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeCustomer]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertCustomer(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CustomerDataType data )
    {
        var dataCustomerid = data.Customerid;
        var dataPersonid = data.Personid;
        var dataStoreid = data.Storeid;
        var dataTerritoryid = data.Territoryid;
        var dataAccountnumber = data.Accountnumber;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCustomer( sqlConnection, 
                        ref dataCustomerid,
                        dataPersonid,
                        dataStoreid,
                        dataTerritoryid,
                        dataAccountnumber,
                        dataRowguid,
                        dataModifieddate );
        data.Customerid = dataCustomerid;

        return result;
    }

    public static bool UpdateCustomer(SqlConnection sqlConnection, int customerid,
        int? personid,
        int? storeid,
        int? territoryid,
        string accountnumber,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateCustomer]";

        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddInt32("@personid", personid);
        command.Parameters.AddInt32("@storeid", storeid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddVarChar("@accountnumber", accountnumber, 10);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCustomer(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CustomerDataType data )
    {
        var dataCustomerid = data.Customerid;
        var dataPersonid = data.Personid;
        var dataStoreid = data.Storeid;
        var dataTerritoryid = data.Territoryid;
        var dataAccountnumber = data.Accountnumber;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCustomer( sqlConnection, 
                        dataCustomerid,
                        dataPersonid,
                        dataStoreid,
                        dataTerritoryid,
                        dataAccountnumber,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCustomer(SqlConnection sqlConnection, int customerid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteCustomer]";

        command.Parameters.AddInt32("@customerid", customerid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCustomer(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CustomerDataType data )
    {
        var dataCustomerid = data.Customerid;
        var result = DeleteCustomer( sqlConnection, 
                        dataCustomerid );

        return result;
    }

    public static bool Insert1Customer(SqlConnection sqlConnection, ref int customerid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Insert1Customer]";

        var customeridParameter = command.Parameters.AddInt32("@customerid");
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            customerid = (int)customeridParameter.Value;
        }
        return result;
    }

    public static bool Insert1Customer(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CustomerDataType data )
    {
        var dataCustomerid = data.Customerid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Customer( sqlConnection, 
                        ref dataCustomerid,
                        dataRowguid,
                        dataModifieddate );
        data.Customerid = dataCustomerid;

        return result;
    }

    public static bool Update1Customer(SqlConnection sqlConnection, int customerid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update1Customer]";

        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update2Customer(SqlConnection sqlConnection, int customerid,
        int? personid,
        int? storeid,
        int? territoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update2Customer]";

        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddInt32("@personid", personid);
        command.Parameters.AddInt32("@storeid", storeid);
        command.Parameters.AddInt32("@territoryid", territoryid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Customer(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CustomerDataType data )
    {
        var dataCustomerid = data.Customerid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Customer( sqlConnection, 
                        dataCustomerid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Customer(SqlConnection sqlConnection, AdventureWorks.Sales.Types.CustomerDataType data )
    {
        var dataCustomerid = data.Customerid;
        var dataPersonid = data.Personid;
        var dataStoreid = data.Storeid;
        var dataTerritoryid = data.Territoryid;
        var result = Update2Customer( sqlConnection, 
                        dataCustomerid,
                        dataPersonid,
                        dataStoreid,
                        dataTerritoryid );

        return result;
    }

    public static bool InsertPersoncreditcard(SqlConnection sqlConnection, int businessentityid,
        int creditcardid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertPersonCreditCard]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@creditcardid", creditcardid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergePersoncreditcard(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.PersoncreditcardDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergePersonCreditCard]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertPersoncreditcard(SqlConnection sqlConnection, AdventureWorks.Sales.Types.PersoncreditcardDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataCreditcardid = data.Creditcardid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPersoncreditcard( sqlConnection, 
                        dataBusinessentityid,
                        dataCreditcardid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdatePersoncreditcard(SqlConnection sqlConnection, int businessentityid,
        int creditcardid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdatePersonCreditCard]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@creditcardid", creditcardid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePersoncreditcard(SqlConnection sqlConnection, AdventureWorks.Sales.Types.PersoncreditcardDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataCreditcardid = data.Creditcardid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePersoncreditcard( sqlConnection, 
                        dataBusinessentityid,
                        dataCreditcardid,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePersoncreditcard(SqlConnection sqlConnection, int businessentityid,
        int creditcardid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeletePersonCreditCard]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@creditcardid", creditcardid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePersoncreditcard(SqlConnection sqlConnection, AdventureWorks.Sales.Types.PersoncreditcardDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataCreditcardid = data.Creditcardid;
        var result = DeletePersoncreditcard( sqlConnection, 
                        dataBusinessentityid,
                        dataCreditcardid );

        return result;
    }

    public static bool InsertSalesorderdetail(SqlConnection sqlConnection, int salesorderid,
        ref int salesorderdetailid,
        string? carriertrackingnumber,
        short orderqty,
        int productid,
        int specialofferid,
        decimal unitprice,
        decimal unitpricediscount,
        decimal linetotal,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesOrderDetail]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        var salesorderdetailidParameter = command.Parameters.AddInt32("@salesorderdetailid");
        command.Parameters.AddNVarChar("@carriertrackingnumber", carriertrackingnumber, 25);
        command.Parameters.AddInt16("@orderqty", orderqty);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@specialofferid", specialofferid);
        command.Parameters.AddDecimal("@unitprice", unitprice);
        command.Parameters.AddDecimal("@unitpricediscount", unitpricediscount);
        command.Parameters.AddDecimal("@linetotal", linetotal);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            salesorderdetailid = (int)salesorderdetailidParameter.Value;
        }
        return result;
    }

    public static bool MergeSalesorderdetail(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.SalesorderdetailDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeSalesOrderDetail]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertSalesorderdetail(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesorderdetailDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalesorderdetailid = data.Salesorderdetailid;
        var dataCarriertrackingnumber = data.Carriertrackingnumber;
        var dataOrderqty = data.Orderqty;
        var dataProductid = data.Productid;
        var dataSpecialofferid = data.Specialofferid;
        var dataUnitprice = data.Unitprice;
        var dataUnitpricediscount = data.Unitpricediscount;
        var dataLinetotal = data.Linetotal;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesorderdetail( sqlConnection, 
                        dataSalesorderid,
                        ref dataSalesorderdetailid,
                        dataCarriertrackingnumber,
                        dataOrderqty,
                        dataProductid,
                        dataSpecialofferid,
                        dataUnitprice,
                        dataUnitpricediscount,
                        dataLinetotal,
                        dataRowguid,
                        dataModifieddate );
        data.Salesorderdetailid = dataSalesorderdetailid;

        return result;
    }

    public static bool UpdateSalesorderdetail(SqlConnection sqlConnection, int salesorderid,
        int salesorderdetailid,
        string? carriertrackingnumber,
        short orderqty,
        int productid,
        int specialofferid,
        decimal unitprice,
        decimal unitpricediscount,
        decimal linetotal,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesOrderDetail]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddInt32("@salesorderdetailid", salesorderdetailid);
        command.Parameters.AddNVarChar("@carriertrackingnumber", carriertrackingnumber, 25);
        command.Parameters.AddInt16("@orderqty", orderqty);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddInt32("@specialofferid", specialofferid);
        command.Parameters.AddDecimal("@unitprice", unitprice);
        command.Parameters.AddDecimal("@unitpricediscount", unitpricediscount);
        command.Parameters.AddDecimal("@linetotal", linetotal);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesorderdetail(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesorderdetailDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalesorderdetailid = data.Salesorderdetailid;
        var dataCarriertrackingnumber = data.Carriertrackingnumber;
        var dataOrderqty = data.Orderqty;
        var dataProductid = data.Productid;
        var dataSpecialofferid = data.Specialofferid;
        var dataUnitprice = data.Unitprice;
        var dataUnitpricediscount = data.Unitpricediscount;
        var dataLinetotal = data.Linetotal;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesorderdetail( sqlConnection, 
                        dataSalesorderid,
                        dataSalesorderdetailid,
                        dataCarriertrackingnumber,
                        dataOrderqty,
                        dataProductid,
                        dataSpecialofferid,
                        dataUnitprice,
                        dataUnitpricediscount,
                        dataLinetotal,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesorderdetail(SqlConnection sqlConnection, int salesorderid,
        int salesorderdetailid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesOrderDetail]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddInt32("@salesorderdetailid", salesorderdetailid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesorderdetail(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesorderdetailDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalesorderdetailid = data.Salesorderdetailid;
        var result = DeleteSalesorderdetail( sqlConnection, 
                        dataSalesorderid,
                        dataSalesorderdetailid );

        return result;
    }

    public static bool InsertSalesorderheader(SqlConnection sqlConnection, ref int salesorderid,
        byte revisionnumber,
        DateTime orderdate,
        DateTime duedate,
        DateTime? shipdate,
        byte status,
        bool onlineorderflag,
        string salesordernumber,
        string? purchaseordernumber,
        string? accountnumber,
        int customerid,
        int? salespersonid,
        int? territoryid,
        int billtoaddressid,
        int shiptoaddressid,
        int shipmethodid,
        int? creditcardid,
        string? creditcardapprovalcode,
        int? currencyrateid,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        decimal totaldue,
        string? comment,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesOrderHeader]";

        var salesorderidParameter = command.Parameters.AddInt32("@salesorderid");
        command.Parameters.AddByte("@revisionnumber", revisionnumber);
        command.Parameters.AddDateTime("@orderdate", orderdate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddDateTime("@shipdate", shipdate);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddBoolean("@onlineorderflag", onlineorderflag);
        command.Parameters.AddNVarChar("@salesordernumber", salesordernumber, 25);
        command.Parameters.AddNVarChar("@purchaseordernumber", purchaseordernumber, 25);
        command.Parameters.AddNVarChar("@accountnumber", accountnumber, 15);
        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddInt32("@salespersonid", salespersonid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddInt32("@billtoaddressid", billtoaddressid);
        command.Parameters.AddInt32("@shiptoaddressid", shiptoaddressid);
        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddInt32("@creditcardid", creditcardid);
        command.Parameters.AddVarChar("@creditcardapprovalcode", creditcardapprovalcode, 15);
        command.Parameters.AddInt32("@currencyrateid", currencyrateid);
        command.Parameters.AddDecimal("@subtotal", subtotal);
        command.Parameters.AddDecimal("@taxamt", taxamt);
        command.Parameters.AddDecimal("@freight", freight);
        command.Parameters.AddDecimal("@totaldue", totaldue);
        command.Parameters.AddNVarChar("@comment", comment, 128);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            salesorderid = (int)salesorderidParameter.Value;
        }
        return result;
    }

    public static bool MergeSalesorderheader(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.SalesorderheaderDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeSalesOrderHeader]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertSalesorderheader(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesorderheaderDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataRevisionnumber = data.Revisionnumber;
        var dataOrderdate = data.Orderdate;
        var dataDuedate = data.Duedate;
        var dataShipdate = data.Shipdate;
        var dataStatus = data.Status;
        var dataOnlineorderflag = data.Onlineorderflag;
        var dataSalesordernumber = data.Salesordernumber;
        var dataPurchaseordernumber = data.Purchaseordernumber;
        var dataAccountnumber = data.Accountnumber;
        var dataCustomerid = data.Customerid;
        var dataSalespersonid = data.Salespersonid;
        var dataTerritoryid = data.Territoryid;
        var dataBilltoaddressid = data.Billtoaddressid;
        var dataShiptoaddressid = data.Shiptoaddressid;
        var dataShipmethodid = data.Shipmethodid;
        var dataCreditcardid = data.Creditcardid;
        var dataCreditcardapprovalcode = data.Creditcardapprovalcode;
        var dataCurrencyrateid = data.Currencyrateid;
        var dataSubtotal = data.Subtotal;
        var dataTaxamt = data.Taxamt;
        var dataFreight = data.Freight;
        var dataTotaldue = data.Totaldue;
        var dataComment = data.Comment;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesorderheader( sqlConnection, 
                        ref dataSalesorderid,
                        dataRevisionnumber,
                        dataOrderdate,
                        dataDuedate,
                        dataShipdate,
                        dataStatus,
                        dataOnlineorderflag,
                        dataSalesordernumber,
                        dataPurchaseordernumber,
                        dataAccountnumber,
                        dataCustomerid,
                        dataSalespersonid,
                        dataTerritoryid,
                        dataBilltoaddressid,
                        dataShiptoaddressid,
                        dataShipmethodid,
                        dataCreditcardid,
                        dataCreditcardapprovalcode,
                        dataCurrencyrateid,
                        dataSubtotal,
                        dataTaxamt,
                        dataFreight,
                        dataTotaldue,
                        dataComment,
                        dataRowguid,
                        dataModifieddate );
        data.Salesorderid = dataSalesorderid;

        return result;
    }

    public static bool UpdateSalesorderheader(SqlConnection sqlConnection, int salesorderid,
        byte revisionnumber,
        DateTime orderdate,
        DateTime duedate,
        DateTime? shipdate,
        byte status,
        bool onlineorderflag,
        string salesordernumber,
        string? purchaseordernumber,
        string? accountnumber,
        int customerid,
        int? salespersonid,
        int? territoryid,
        int billtoaddressid,
        int shiptoaddressid,
        int shipmethodid,
        int? creditcardid,
        string? creditcardapprovalcode,
        int? currencyrateid,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        decimal totaldue,
        string? comment,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesOrderHeader]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddByte("@revisionnumber", revisionnumber);
        command.Parameters.AddDateTime("@orderdate", orderdate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddDateTime("@shipdate", shipdate);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddBoolean("@onlineorderflag", onlineorderflag);
        command.Parameters.AddNVarChar("@salesordernumber", salesordernumber, 25);
        command.Parameters.AddNVarChar("@purchaseordernumber", purchaseordernumber, 25);
        command.Parameters.AddNVarChar("@accountnumber", accountnumber, 15);
        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddInt32("@salespersonid", salespersonid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddInt32("@billtoaddressid", billtoaddressid);
        command.Parameters.AddInt32("@shiptoaddressid", shiptoaddressid);
        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddInt32("@creditcardid", creditcardid);
        command.Parameters.AddVarChar("@creditcardapprovalcode", creditcardapprovalcode, 15);
        command.Parameters.AddInt32("@currencyrateid", currencyrateid);
        command.Parameters.AddDecimal("@subtotal", subtotal);
        command.Parameters.AddDecimal("@taxamt", taxamt);
        command.Parameters.AddDecimal("@freight", freight);
        command.Parameters.AddDecimal("@totaldue", totaldue);
        command.Parameters.AddNVarChar("@comment", comment, 128);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesorderheader(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesorderheaderDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataRevisionnumber = data.Revisionnumber;
        var dataOrderdate = data.Orderdate;
        var dataDuedate = data.Duedate;
        var dataShipdate = data.Shipdate;
        var dataStatus = data.Status;
        var dataOnlineorderflag = data.Onlineorderflag;
        var dataSalesordernumber = data.Salesordernumber;
        var dataPurchaseordernumber = data.Purchaseordernumber;
        var dataAccountnumber = data.Accountnumber;
        var dataCustomerid = data.Customerid;
        var dataSalespersonid = data.Salespersonid;
        var dataTerritoryid = data.Territoryid;
        var dataBilltoaddressid = data.Billtoaddressid;
        var dataShiptoaddressid = data.Shiptoaddressid;
        var dataShipmethodid = data.Shipmethodid;
        var dataCreditcardid = data.Creditcardid;
        var dataCreditcardapprovalcode = data.Creditcardapprovalcode;
        var dataCurrencyrateid = data.Currencyrateid;
        var dataSubtotal = data.Subtotal;
        var dataTaxamt = data.Taxamt;
        var dataFreight = data.Freight;
        var dataTotaldue = data.Totaldue;
        var dataComment = data.Comment;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesorderheader( sqlConnection, 
                        dataSalesorderid,
                        dataRevisionnumber,
                        dataOrderdate,
                        dataDuedate,
                        dataShipdate,
                        dataStatus,
                        dataOnlineorderflag,
                        dataSalesordernumber,
                        dataPurchaseordernumber,
                        dataAccountnumber,
                        dataCustomerid,
                        dataSalespersonid,
                        dataTerritoryid,
                        dataBilltoaddressid,
                        dataShiptoaddressid,
                        dataShipmethodid,
                        dataCreditcardid,
                        dataCreditcardapprovalcode,
                        dataCurrencyrateid,
                        dataSubtotal,
                        dataTaxamt,
                        dataFreight,
                        dataTotaldue,
                        dataComment,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesorderheader(SqlConnection sqlConnection, int salesorderid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesOrderHeader]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesorderheader(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesorderheaderDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var result = DeleteSalesorderheader( sqlConnection, 
                        dataSalesorderid );

        return result;
    }

    public static bool Insert1Salesorderheader(SqlConnection sqlConnection, ref int salesorderid,
        byte revisionnumber,
        DateTime orderdate,
        DateTime duedate,
        DateTime? shipdate,
        byte status,
        bool onlineorderflag,
        string? purchaseordernumber,
        string? accountnumber,
        int customerid,
        int billtoaddressid,
        int shiptoaddressid,
        int shipmethodid,
        string? creditcardapprovalcode,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        string? comment,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Insert1SalesOrderHeader]";

        var salesorderidParameter = command.Parameters.AddInt32("@salesorderid");
        command.Parameters.AddByte("@revisionnumber", revisionnumber);
        command.Parameters.AddDateTime("@orderdate", orderdate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddDateTime("@shipdate", shipdate);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddBoolean("@onlineorderflag", onlineorderflag);
        command.Parameters.AddNVarChar("@purchaseordernumber", purchaseordernumber, 25);
        command.Parameters.AddNVarChar("@accountnumber", accountnumber, 15);
        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddInt32("@billtoaddressid", billtoaddressid);
        command.Parameters.AddInt32("@shiptoaddressid", shiptoaddressid);
        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddVarChar("@creditcardapprovalcode", creditcardapprovalcode, 15);
        command.Parameters.AddDecimal("@subtotal", subtotal);
        command.Parameters.AddDecimal("@taxamt", taxamt);
        command.Parameters.AddDecimal("@freight", freight);
        command.Parameters.AddNVarChar("@comment", comment, 128);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            salesorderid = (int)salesorderidParameter.Value;
        }
        return result;
    }

    public static bool Insert1Salesorderheader(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesorderheaderDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataRevisionnumber = data.Revisionnumber;
        var dataOrderdate = data.Orderdate;
        var dataDuedate = data.Duedate;
        var dataShipdate = data.Shipdate;
        var dataStatus = data.Status;
        var dataOnlineorderflag = data.Onlineorderflag;
        var dataPurchaseordernumber = data.Purchaseordernumber;
        var dataAccountnumber = data.Accountnumber;
        var dataCustomerid = data.Customerid;
        var dataBilltoaddressid = data.Billtoaddressid;
        var dataShiptoaddressid = data.Shiptoaddressid;
        var dataShipmethodid = data.Shipmethodid;
        var dataCreditcardapprovalcode = data.Creditcardapprovalcode;
        var dataSubtotal = data.Subtotal;
        var dataTaxamt = data.Taxamt;
        var dataFreight = data.Freight;
        var dataComment = data.Comment;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Salesorderheader( sqlConnection, 
                        ref dataSalesorderid,
                        dataRevisionnumber,
                        dataOrderdate,
                        dataDuedate,
                        dataShipdate,
                        dataStatus,
                        dataOnlineorderflag,
                        dataPurchaseordernumber,
                        dataAccountnumber,
                        dataCustomerid,
                        dataBilltoaddressid,
                        dataShiptoaddressid,
                        dataShipmethodid,
                        dataCreditcardapprovalcode,
                        dataSubtotal,
                        dataTaxamt,
                        dataFreight,
                        dataComment,
                        dataRowguid,
                        dataModifieddate );
        data.Salesorderid = dataSalesorderid;

        return result;
    }

    public static bool Update1Salesorderheader(SqlConnection sqlConnection, int salesorderid,
        byte revisionnumber,
        DateTime orderdate,
        DateTime duedate,
        DateTime? shipdate,
        byte status,
        bool onlineorderflag,
        string? purchaseordernumber,
        string? accountnumber,
        int customerid,
        int billtoaddressid,
        int shiptoaddressid,
        int shipmethodid,
        string? creditcardapprovalcode,
        decimal subtotal,
        decimal taxamt,
        decimal freight,
        string? comment,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update1SalesOrderHeader]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddByte("@revisionnumber", revisionnumber);
        command.Parameters.AddDateTime("@orderdate", orderdate);
        command.Parameters.AddDateTime("@duedate", duedate);
        command.Parameters.AddDateTime("@shipdate", shipdate);
        command.Parameters.AddByte("@status", status);
        command.Parameters.AddBoolean("@onlineorderflag", onlineorderflag);
        command.Parameters.AddNVarChar("@purchaseordernumber", purchaseordernumber, 25);
        command.Parameters.AddNVarChar("@accountnumber", accountnumber, 15);
        command.Parameters.AddInt32("@customerid", customerid);
        command.Parameters.AddInt32("@billtoaddressid", billtoaddressid);
        command.Parameters.AddInt32("@shiptoaddressid", shiptoaddressid);
        command.Parameters.AddInt32("@shipmethodid", shipmethodid);
        command.Parameters.AddVarChar("@creditcardapprovalcode", creditcardapprovalcode, 15);
        command.Parameters.AddDecimal("@subtotal", subtotal);
        command.Parameters.AddDecimal("@taxamt", taxamt);
        command.Parameters.AddDecimal("@freight", freight);
        command.Parameters.AddNVarChar("@comment", comment, 128);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update2Salesorderheader(SqlConnection sqlConnection, int salesorderid,
        int? salespersonid,
        int? territoryid,
        int? creditcardid,
        int? currencyrateid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update2SalesOrderHeader]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddInt32("@salespersonid", salespersonid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddInt32("@creditcardid", creditcardid);
        command.Parameters.AddInt32("@currencyrateid", currencyrateid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Salesorderheader(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesorderheaderDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataRevisionnumber = data.Revisionnumber;
        var dataOrderdate = data.Orderdate;
        var dataDuedate = data.Duedate;
        var dataShipdate = data.Shipdate;
        var dataStatus = data.Status;
        var dataOnlineorderflag = data.Onlineorderflag;
        var dataPurchaseordernumber = data.Purchaseordernumber;
        var dataAccountnumber = data.Accountnumber;
        var dataCustomerid = data.Customerid;
        var dataBilltoaddressid = data.Billtoaddressid;
        var dataShiptoaddressid = data.Shiptoaddressid;
        var dataShipmethodid = data.Shipmethodid;
        var dataCreditcardapprovalcode = data.Creditcardapprovalcode;
        var dataSubtotal = data.Subtotal;
        var dataTaxamt = data.Taxamt;
        var dataFreight = data.Freight;
        var dataComment = data.Comment;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Salesorderheader( sqlConnection, 
                        dataSalesorderid,
                        dataRevisionnumber,
                        dataOrderdate,
                        dataDuedate,
                        dataShipdate,
                        dataStatus,
                        dataOnlineorderflag,
                        dataPurchaseordernumber,
                        dataAccountnumber,
                        dataCustomerid,
                        dataBilltoaddressid,
                        dataShiptoaddressid,
                        dataShipmethodid,
                        dataCreditcardapprovalcode,
                        dataSubtotal,
                        dataTaxamt,
                        dataFreight,
                        dataComment,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Salesorderheader(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesorderheaderDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalespersonid = data.Salespersonid;
        var dataTerritoryid = data.Territoryid;
        var dataCreditcardid = data.Creditcardid;
        var dataCurrencyrateid = data.Currencyrateid;
        var result = Update2Salesorderheader( sqlConnection, 
                        dataSalesorderid,
                        dataSalespersonid,
                        dataTerritoryid,
                        dataCreditcardid,
                        dataCurrencyrateid );

        return result;
    }

    public static bool InsertSalesorderheadersalesreason(SqlConnection sqlConnection, int salesorderid,
        int salesreasonid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesOrderHeaderSalesReason]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddInt32("@salesreasonid", salesreasonid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeSalesorderheadersalesreason(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.SalesorderheadersalesreasonDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeSalesOrderHeaderSalesReason]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertSalesorderheadersalesreason(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesorderheadersalesreasonDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalesreasonid = data.Salesreasonid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesorderheadersalesreason( sqlConnection, 
                        dataSalesorderid,
                        dataSalesreasonid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateSalesorderheadersalesreason(SqlConnection sqlConnection, int salesorderid,
        int salesreasonid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesOrderHeaderSalesReason]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddInt32("@salesreasonid", salesreasonid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesorderheadersalesreason(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesorderheadersalesreasonDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalesreasonid = data.Salesreasonid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesorderheadersalesreason( sqlConnection, 
                        dataSalesorderid,
                        dataSalesreasonid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesorderheadersalesreason(SqlConnection sqlConnection, int salesorderid,
        int salesreasonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesOrderHeaderSalesReason]";

        command.Parameters.AddInt32("@salesorderid", salesorderid);
        command.Parameters.AddInt32("@salesreasonid", salesreasonid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesorderheadersalesreason(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesorderheadersalesreasonDataType data )
    {
        var dataSalesorderid = data.Salesorderid;
        var dataSalesreasonid = data.Salesreasonid;
        var result = DeleteSalesorderheadersalesreason( sqlConnection, 
                        dataSalesorderid,
                        dataSalesreasonid );

        return result;
    }

    public static bool InsertSalesperson(SqlConnection sqlConnection, int businessentityid,
        int? territoryid,
        decimal? salesquota,
        decimal bonus,
        decimal commissionpct,
        decimal salesytd,
        decimal saleslastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesPerson]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddDecimal("@salesquota", salesquota);
        command.Parameters.AddDecimal("@bonus", bonus);
        command.Parameters.AddDecimal("@commissionpct", commissionpct);
        command.Parameters.AddDecimal("@salesytd", salesytd);
        command.Parameters.AddDecimal("@saleslastyear", saleslastyear);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeSalesperson(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.SalespersonDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeSalesPerson]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertSalesperson(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalespersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataTerritoryid = data.Territoryid;
        var dataSalesquota = data.Salesquota;
        var dataBonus = data.Bonus;
        var dataCommissionpct = data.Commissionpct;
        var dataSalesytd = data.Salesytd;
        var dataSaleslastyear = data.Saleslastyear;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesperson( sqlConnection, 
                        dataBusinessentityid,
                        dataTerritoryid,
                        dataSalesquota,
                        dataBonus,
                        dataCommissionpct,
                        dataSalesytd,
                        dataSaleslastyear,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateSalesperson(SqlConnection sqlConnection, int businessentityid,
        int? territoryid,
        decimal? salesquota,
        decimal bonus,
        decimal commissionpct,
        decimal salesytd,
        decimal saleslastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesPerson]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddDecimal("@salesquota", salesquota);
        command.Parameters.AddDecimal("@bonus", bonus);
        command.Parameters.AddDecimal("@commissionpct", commissionpct);
        command.Parameters.AddDecimal("@salesytd", salesytd);
        command.Parameters.AddDecimal("@saleslastyear", saleslastyear);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesperson(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalespersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataTerritoryid = data.Territoryid;
        var dataSalesquota = data.Salesquota;
        var dataBonus = data.Bonus;
        var dataCommissionpct = data.Commissionpct;
        var dataSalesytd = data.Salesytd;
        var dataSaleslastyear = data.Saleslastyear;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesperson( sqlConnection, 
                        dataBusinessentityid,
                        dataTerritoryid,
                        dataSalesquota,
                        dataBonus,
                        dataCommissionpct,
                        dataSalesytd,
                        dataSaleslastyear,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesperson(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesPerson]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesperson(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalespersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var result = DeleteSalesperson( sqlConnection, 
                        dataBusinessentityid );

        return result;
    }

    public static bool Insert1Salesperson(SqlConnection sqlConnection, int businessentityid,
        decimal? salesquota,
        decimal bonus,
        decimal commissionpct,
        decimal salesytd,
        decimal saleslastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Insert1SalesPerson]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDecimal("@salesquota", salesquota);
        command.Parameters.AddDecimal("@bonus", bonus);
        command.Parameters.AddDecimal("@commissionpct", commissionpct);
        command.Parameters.AddDecimal("@salesytd", salesytd);
        command.Parameters.AddDecimal("@saleslastyear", saleslastyear);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Insert1Salesperson(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalespersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataSalesquota = data.Salesquota;
        var dataBonus = data.Bonus;
        var dataCommissionpct = data.Commissionpct;
        var dataSalesytd = data.Salesytd;
        var dataSaleslastyear = data.Saleslastyear;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Salesperson( sqlConnection, 
                        dataBusinessentityid,
                        dataSalesquota,
                        dataBonus,
                        dataCommissionpct,
                        dataSalesytd,
                        dataSaleslastyear,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool Update1Salesperson(SqlConnection sqlConnection, int businessentityid,
        decimal? salesquota,
        decimal bonus,
        decimal commissionpct,
        decimal salesytd,
        decimal saleslastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update1SalesPerson]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDecimal("@salesquota", salesquota);
        command.Parameters.AddDecimal("@bonus", bonus);
        command.Parameters.AddDecimal("@commissionpct", commissionpct);
        command.Parameters.AddDecimal("@salesytd", salesytd);
        command.Parameters.AddDecimal("@saleslastyear", saleslastyear);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update2Salesperson(SqlConnection sqlConnection, int businessentityid,
        int? territoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update2SalesPerson]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@territoryid", territoryid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Salesperson(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalespersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataSalesquota = data.Salesquota;
        var dataBonus = data.Bonus;
        var dataCommissionpct = data.Commissionpct;
        var dataSalesytd = data.Salesytd;
        var dataSaleslastyear = data.Saleslastyear;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Salesperson( sqlConnection, 
                        dataBusinessentityid,
                        dataSalesquota,
                        dataBonus,
                        dataCommissionpct,
                        dataSalesytd,
                        dataSaleslastyear,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Salesperson(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalespersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataTerritoryid = data.Territoryid;
        var result = Update2Salesperson( sqlConnection, 
                        dataBusinessentityid,
                        dataTerritoryid );

        return result;
    }

    public static bool InsertSalespersonquotahistory(SqlConnection sqlConnection, int businessentityid,
        DateTime quotadate,
        decimal salesquota,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesPersonQuotaHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDateTime("@quotadate", quotadate);
        command.Parameters.AddDecimal("@salesquota", salesquota);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeSalespersonquotahistory(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.SalespersonquotahistoryDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeSalesPersonQuotaHistory]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertSalespersonquotahistory(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalespersonquotahistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataQuotadate = data.Quotadate;
        var dataSalesquota = data.Salesquota;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalespersonquotahistory( sqlConnection, 
                        dataBusinessentityid,
                        dataQuotadate,
                        dataSalesquota,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateSalespersonquotahistory(SqlConnection sqlConnection, int businessentityid,
        DateTime quotadate,
        decimal salesquota,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesPersonQuotaHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDateTime("@quotadate", quotadate);
        command.Parameters.AddDecimal("@salesquota", salesquota);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalespersonquotahistory(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalespersonquotahistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataQuotadate = data.Quotadate;
        var dataSalesquota = data.Salesquota;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalespersonquotahistory( sqlConnection, 
                        dataBusinessentityid,
                        dataQuotadate,
                        dataSalesquota,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalespersonquotahistory(SqlConnection sqlConnection, int businessentityid,
        DateTime quotadate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesPersonQuotaHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDateTime("@quotadate", quotadate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalespersonquotahistory(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalespersonquotahistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataQuotadate = data.Quotadate;
        var result = DeleteSalespersonquotahistory( sqlConnection, 
                        dataBusinessentityid,
                        dataQuotadate );

        return result;
    }

    public static bool InsertSalesreason(SqlConnection sqlConnection, ref int salesreasonid,
        string name,
        string reasontype,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesReason]";

        var salesreasonidParameter = command.Parameters.AddInt32("@salesreasonid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@reasontype", reasontype, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            salesreasonid = (int)salesreasonidParameter.Value;
        }
        return result;
    }

    public static bool MergeSalesreason(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.SalesreasonDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeSalesReason]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertSalesreason(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesreasonDataType data )
    {
        var dataSalesreasonid = data.Salesreasonid;
        var dataName = data.Name;
        var dataReasontype = data.Reasontype;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesreason( sqlConnection, 
                        ref dataSalesreasonid,
                        dataName,
                        dataReasontype,
                        dataModifieddate );
        data.Salesreasonid = dataSalesreasonid;

        return result;
    }

    public static bool UpdateSalesreason(SqlConnection sqlConnection, int salesreasonid,
        string name,
        string reasontype,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesReason]";

        command.Parameters.AddInt32("@salesreasonid", salesreasonid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@reasontype", reasontype, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesreason(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesreasonDataType data )
    {
        var dataSalesreasonid = data.Salesreasonid;
        var dataName = data.Name;
        var dataReasontype = data.Reasontype;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesreason( sqlConnection, 
                        dataSalesreasonid,
                        dataName,
                        dataReasontype,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesreason(SqlConnection sqlConnection, int salesreasonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesReason]";

        command.Parameters.AddInt32("@salesreasonid", salesreasonid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesreason(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesreasonDataType data )
    {
        var dataSalesreasonid = data.Salesreasonid;
        var result = DeleteSalesreason( sqlConnection, 
                        dataSalesreasonid );

        return result;
    }

    public static bool InsertSalestaxrate(SqlConnection sqlConnection, ref int salestaxrateid,
        int stateprovinceid,
        byte taxtype,
        decimal taxrate,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesTaxRate]";

        var salestaxrateidParameter = command.Parameters.AddInt32("@salestaxrateid");
        command.Parameters.AddInt32("@stateprovinceid", stateprovinceid);
        command.Parameters.AddByte("@taxtype", taxtype);
        command.Parameters.AddDecimal("@taxrate", taxrate);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            salestaxrateid = (int)salestaxrateidParameter.Value;
        }
        return result;
    }

    public static bool MergeSalestaxrate(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.SalestaxrateDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeSalesTaxRate]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertSalestaxrate(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalestaxrateDataType data )
    {
        var dataSalestaxrateid = data.Salestaxrateid;
        var dataStateprovinceid = data.Stateprovinceid;
        var dataTaxtype = data.Taxtype;
        var dataTaxrate = data.Taxrate;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalestaxrate( sqlConnection, 
                        ref dataSalestaxrateid,
                        dataStateprovinceid,
                        dataTaxtype,
                        dataTaxrate,
                        dataName,
                        dataRowguid,
                        dataModifieddate );
        data.Salestaxrateid = dataSalestaxrateid;

        return result;
    }

    public static bool UpdateSalestaxrate(SqlConnection sqlConnection, int salestaxrateid,
        int stateprovinceid,
        byte taxtype,
        decimal taxrate,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesTaxRate]";

        command.Parameters.AddInt32("@salestaxrateid", salestaxrateid);
        command.Parameters.AddInt32("@stateprovinceid", stateprovinceid);
        command.Parameters.AddByte("@taxtype", taxtype);
        command.Parameters.AddDecimal("@taxrate", taxrate);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalestaxrate(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalestaxrateDataType data )
    {
        var dataSalestaxrateid = data.Salestaxrateid;
        var dataStateprovinceid = data.Stateprovinceid;
        var dataTaxtype = data.Taxtype;
        var dataTaxrate = data.Taxrate;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalestaxrate( sqlConnection, 
                        dataSalestaxrateid,
                        dataStateprovinceid,
                        dataTaxtype,
                        dataTaxrate,
                        dataName,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalestaxrate(SqlConnection sqlConnection, int salestaxrateid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesTaxRate]";

        command.Parameters.AddInt32("@salestaxrateid", salestaxrateid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalestaxrate(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalestaxrateDataType data )
    {
        var dataSalestaxrateid = data.Salestaxrateid;
        var result = DeleteSalestaxrate( sqlConnection, 
                        dataSalestaxrateid );

        return result;
    }

    public static bool InsertSalesterritory(SqlConnection sqlConnection, ref int territoryid,
        string name,
        string countryregioncode,
        string group,
        decimal salesytd,
        decimal saleslastyear,
        decimal costytd,
        decimal costlastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesTerritory]";

        var territoryidParameter = command.Parameters.AddInt32("@territoryid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNVarChar("@group", group, 50);
        command.Parameters.AddDecimal("@salesytd", salesytd);
        command.Parameters.AddDecimal("@saleslastyear", saleslastyear);
        command.Parameters.AddDecimal("@costytd", costytd);
        command.Parameters.AddDecimal("@costlastyear", costlastyear);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            territoryid = (int)territoryidParameter.Value;
        }
        return result;
    }

    public static bool MergeSalesterritory(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.SalesterritoryDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeSalesTerritory]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertSalesterritory(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesterritoryDataType data )
    {
        var dataTerritoryid = data.Territoryid;
        var dataName = data.Name;
        var dataCountryregioncode = data.Countryregioncode;
        var dataGroup = data.Group;
        var dataSalesytd = data.Salesytd;
        var dataSaleslastyear = data.Saleslastyear;
        var dataCostytd = data.Costytd;
        var dataCostlastyear = data.Costlastyear;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesterritory( sqlConnection, 
                        ref dataTerritoryid,
                        dataName,
                        dataCountryregioncode,
                        dataGroup,
                        dataSalesytd,
                        dataSaleslastyear,
                        dataCostytd,
                        dataCostlastyear,
                        dataRowguid,
                        dataModifieddate );
        data.Territoryid = dataTerritoryid;

        return result;
    }

    public static bool UpdateSalesterritory(SqlConnection sqlConnection, int territoryid,
        string name,
        string countryregioncode,
        string group,
        decimal salesytd,
        decimal saleslastyear,
        decimal costytd,
        decimal costlastyear,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesTerritory]";

        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNVarChar("@group", group, 50);
        command.Parameters.AddDecimal("@salesytd", salesytd);
        command.Parameters.AddDecimal("@saleslastyear", saleslastyear);
        command.Parameters.AddDecimal("@costytd", costytd);
        command.Parameters.AddDecimal("@costlastyear", costlastyear);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesterritory(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesterritoryDataType data )
    {
        var dataTerritoryid = data.Territoryid;
        var dataName = data.Name;
        var dataCountryregioncode = data.Countryregioncode;
        var dataGroup = data.Group;
        var dataSalesytd = data.Salesytd;
        var dataSaleslastyear = data.Saleslastyear;
        var dataCostytd = data.Costytd;
        var dataCostlastyear = data.Costlastyear;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesterritory( sqlConnection, 
                        dataTerritoryid,
                        dataName,
                        dataCountryregioncode,
                        dataGroup,
                        dataSalesytd,
                        dataSaleslastyear,
                        dataCostytd,
                        dataCostlastyear,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesterritory(SqlConnection sqlConnection, int territoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesTerritory]";

        command.Parameters.AddInt32("@territoryid", territoryid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesterritory(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesterritoryDataType data )
    {
        var dataTerritoryid = data.Territoryid;
        var result = DeleteSalesterritory( sqlConnection, 
                        dataTerritoryid );

        return result;
    }

    public static bool InsertSalesterritoryhistory(SqlConnection sqlConnection, int businessentityid,
        int territoryid,
        DateTime startdate,
        DateTime? enddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSalesTerritoryHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeSalesterritoryhistory(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.SalesterritoryhistoryDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeSalesTerritoryHistory]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertSalesterritoryhistory(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesterritoryhistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataTerritoryid = data.Territoryid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSalesterritoryhistory( sqlConnection, 
                        dataBusinessentityid,
                        dataTerritoryid,
                        dataStartdate,
                        dataEnddate,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateSalesterritoryhistory(SqlConnection sqlConnection, int businessentityid,
        int territoryid,
        DateTime startdate,
        DateTime? enddate,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSalesTerritoryHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSalesterritoryhistory(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesterritoryhistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataTerritoryid = data.Territoryid;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSalesterritoryhistory( sqlConnection, 
                        dataBusinessentityid,
                        dataTerritoryid,
                        dataStartdate,
                        dataEnddate,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSalesterritoryhistory(SqlConnection sqlConnection, int businessentityid,
        DateTime startdate,
        int territoryid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSalesTerritoryHistory]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddInt32("@territoryid", territoryid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSalesterritoryhistory(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SalesterritoryhistoryDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataStartdate = data.Startdate;
        var dataTerritoryid = data.Territoryid;
        var result = DeleteSalesterritoryhistory( sqlConnection, 
                        dataBusinessentityid,
                        dataStartdate,
                        dataTerritoryid );

        return result;
    }

    public static bool InsertShoppingcartitem(SqlConnection sqlConnection, ref int shoppingcartitemid,
        string shoppingcartid,
        int quantity,
        int productid,
        DateTime datecreated,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertShoppingCartItem]";

        var shoppingcartitemidParameter = command.Parameters.AddInt32("@shoppingcartitemid");
        command.Parameters.AddNVarChar("@shoppingcartid", shoppingcartid, 50);
        command.Parameters.AddInt32("@quantity", quantity);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@datecreated", datecreated);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            shoppingcartitemid = (int)shoppingcartitemidParameter.Value;
        }
        return result;
    }

    public static bool MergeShoppingcartitem(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.ShoppingcartitemDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeShoppingCartItem]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertShoppingcartitem(SqlConnection sqlConnection, AdventureWorks.Sales.Types.ShoppingcartitemDataType data )
    {
        var dataShoppingcartitemid = data.Shoppingcartitemid;
        var dataShoppingcartid = data.Shoppingcartid;
        var dataQuantity = data.Quantity;
        var dataProductid = data.Productid;
        var dataDatecreated = data.Datecreated;
        var dataModifieddate = data.Modifieddate;
        var result = InsertShoppingcartitem( sqlConnection, 
                        ref dataShoppingcartitemid,
                        dataShoppingcartid,
                        dataQuantity,
                        dataProductid,
                        dataDatecreated,
                        dataModifieddate );
        data.Shoppingcartitemid = dataShoppingcartitemid;

        return result;
    }

    public static bool UpdateShoppingcartitem(SqlConnection sqlConnection, int shoppingcartitemid,
        string shoppingcartid,
        int quantity,
        int productid,
        DateTime datecreated,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateShoppingCartItem]";

        command.Parameters.AddInt32("@shoppingcartitemid", shoppingcartitemid);
        command.Parameters.AddNVarChar("@shoppingcartid", shoppingcartid, 50);
        command.Parameters.AddInt32("@quantity", quantity);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddDateTime("@datecreated", datecreated);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateShoppingcartitem(SqlConnection sqlConnection, AdventureWorks.Sales.Types.ShoppingcartitemDataType data )
    {
        var dataShoppingcartitemid = data.Shoppingcartitemid;
        var dataShoppingcartid = data.Shoppingcartid;
        var dataQuantity = data.Quantity;
        var dataProductid = data.Productid;
        var dataDatecreated = data.Datecreated;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateShoppingcartitem( sqlConnection, 
                        dataShoppingcartitemid,
                        dataShoppingcartid,
                        dataQuantity,
                        dataProductid,
                        dataDatecreated,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteShoppingcartitem(SqlConnection sqlConnection, int shoppingcartitemid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteShoppingCartItem]";

        command.Parameters.AddInt32("@shoppingcartitemid", shoppingcartitemid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteShoppingcartitem(SqlConnection sqlConnection, AdventureWorks.Sales.Types.ShoppingcartitemDataType data )
    {
        var dataShoppingcartitemid = data.Shoppingcartitemid;
        var result = DeleteShoppingcartitem( sqlConnection, 
                        dataShoppingcartitemid );

        return result;
    }

    public static bool InsertSpecialoffer(SqlConnection sqlConnection, ref int specialofferid,
        string description,
        decimal discountpct,
        string type,
        string category,
        DateTime startdate,
        DateTime enddate,
        int minqty,
        int? maxqty,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSpecialOffer]";

        var specialofferidParameter = command.Parameters.AddInt32("@specialofferid");
        command.Parameters.AddNVarChar("@description", description, 255);
        command.Parameters.AddDecimal("@discountpct", discountpct);
        command.Parameters.AddNVarChar("@type", type, 50);
        command.Parameters.AddNVarChar("@category", category, 50);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddInt32("@minqty", minqty);
        command.Parameters.AddInt32("@maxqty", maxqty);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            specialofferid = (int)specialofferidParameter.Value;
        }
        return result;
    }

    public static bool MergeSpecialoffer(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.SpecialofferDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeSpecialOffer]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertSpecialoffer(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SpecialofferDataType data )
    {
        var dataSpecialofferid = data.Specialofferid;
        var dataDescription = data.Description;
        var dataDiscountpct = data.Discountpct;
        var dataType = data.Type;
        var dataCategory = data.Category;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataMinqty = data.Minqty;
        var dataMaxqty = data.Maxqty;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSpecialoffer( sqlConnection, 
                        ref dataSpecialofferid,
                        dataDescription,
                        dataDiscountpct,
                        dataType,
                        dataCategory,
                        dataStartdate,
                        dataEnddate,
                        dataMinqty,
                        dataMaxqty,
                        dataRowguid,
                        dataModifieddate );
        data.Specialofferid = dataSpecialofferid;

        return result;
    }

    public static bool UpdateSpecialoffer(SqlConnection sqlConnection, int specialofferid,
        string description,
        decimal discountpct,
        string type,
        string category,
        DateTime startdate,
        DateTime enddate,
        int minqty,
        int? maxqty,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSpecialOffer]";

        command.Parameters.AddInt32("@specialofferid", specialofferid);
        command.Parameters.AddNVarChar("@description", description, 255);
        command.Parameters.AddDecimal("@discountpct", discountpct);
        command.Parameters.AddNVarChar("@type", type, 50);
        command.Parameters.AddNVarChar("@category", category, 50);
        command.Parameters.AddDateTime("@startdate", startdate);
        command.Parameters.AddDateTime("@enddate", enddate);
        command.Parameters.AddInt32("@minqty", minqty);
        command.Parameters.AddInt32("@maxqty", maxqty);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSpecialoffer(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SpecialofferDataType data )
    {
        var dataSpecialofferid = data.Specialofferid;
        var dataDescription = data.Description;
        var dataDiscountpct = data.Discountpct;
        var dataType = data.Type;
        var dataCategory = data.Category;
        var dataStartdate = data.Startdate;
        var dataEnddate = data.Enddate;
        var dataMinqty = data.Minqty;
        var dataMaxqty = data.Maxqty;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSpecialoffer( sqlConnection, 
                        dataSpecialofferid,
                        dataDescription,
                        dataDiscountpct,
                        dataType,
                        dataCategory,
                        dataStartdate,
                        dataEnddate,
                        dataMinqty,
                        dataMaxqty,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSpecialoffer(SqlConnection sqlConnection, int specialofferid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSpecialOffer]";

        command.Parameters.AddInt32("@specialofferid", specialofferid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSpecialoffer(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SpecialofferDataType data )
    {
        var dataSpecialofferid = data.Specialofferid;
        var result = DeleteSpecialoffer( sqlConnection, 
                        dataSpecialofferid );

        return result;
    }

    public static bool InsertSpecialofferproduct(SqlConnection sqlConnection, int specialofferid,
        int productid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertSpecialOfferProduct]";

        command.Parameters.AddInt32("@specialofferid", specialofferid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeSpecialofferproduct(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.SpecialofferproductDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeSpecialOfferProduct]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertSpecialofferproduct(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SpecialofferproductDataType data )
    {
        var dataSpecialofferid = data.Specialofferid;
        var dataProductid = data.Productid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertSpecialofferproduct( sqlConnection, 
                        dataSpecialofferid,
                        dataProductid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateSpecialofferproduct(SqlConnection sqlConnection, int specialofferid,
        int productid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateSpecialOfferProduct]";

        command.Parameters.AddInt32("@specialofferid", specialofferid);
        command.Parameters.AddInt32("@productid", productid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateSpecialofferproduct(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SpecialofferproductDataType data )
    {
        var dataSpecialofferid = data.Specialofferid;
        var dataProductid = data.Productid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateSpecialofferproduct( sqlConnection, 
                        dataSpecialofferid,
                        dataProductid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteSpecialofferproduct(SqlConnection sqlConnection, int specialofferid,
        int productid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteSpecialOfferProduct]";

        command.Parameters.AddInt32("@specialofferid", specialofferid);
        command.Parameters.AddInt32("@productid", productid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteSpecialofferproduct(SqlConnection sqlConnection, AdventureWorks.Sales.Types.SpecialofferproductDataType data )
    {
        var dataSpecialofferid = data.Specialofferid;
        var dataProductid = data.Productid;
        var result = DeleteSpecialofferproduct( sqlConnection, 
                        dataSpecialofferid,
                        dataProductid );

        return result;
    }

    public static bool InsertStore(SqlConnection sqlConnection, int businessentityid,
        string name,
        int? salespersonid,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[InsertStore]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddInt32("@salespersonid", salespersonid);
        command.Parameters.AddSqlXml("@demographics", demographics);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeStore(SqlConnection sqlConnection, AdventureWorks.Sales.Database.DataTables.StoreDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Sales].[MergeStore]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertStore(SqlConnection sqlConnection, AdventureWorks.Sales.Types.StoreDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataName = data.Name;
        var dataSalespersonid = data.Salespersonid;
        var dataDemographics = data.Demographics;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertStore( sqlConnection, 
                        dataBusinessentityid,
                        dataName,
                        dataSalespersonid,
                        dataDemographics,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateStore(SqlConnection sqlConnection, int businessentityid,
        string name,
        int? salespersonid,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[UpdateStore]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddInt32("@salespersonid", salespersonid);
        command.Parameters.AddSqlXml("@demographics", demographics);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateStore(SqlConnection sqlConnection, AdventureWorks.Sales.Types.StoreDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataName = data.Name;
        var dataSalespersonid = data.Salespersonid;
        var dataDemographics = data.Demographics;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateStore( sqlConnection, 
                        dataBusinessentityid,
                        dataName,
                        dataSalespersonid,
                        dataDemographics,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteStore(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[DeleteStore]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteStore(SqlConnection sqlConnection, AdventureWorks.Sales.Types.StoreDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var result = DeleteStore( sqlConnection, 
                        dataBusinessentityid );

        return result;
    }

    public static bool Insert1Store(SqlConnection sqlConnection, int businessentityid,
        string name,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Insert1Store]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddSqlXml("@demographics", demographics);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Insert1Store(SqlConnection sqlConnection, AdventureWorks.Sales.Types.StoreDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataName = data.Name;
        var dataDemographics = data.Demographics;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Insert1Store( sqlConnection, 
                        dataBusinessentityid,
                        dataName,
                        dataDemographics,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool Update1Store(SqlConnection sqlConnection, int businessentityid,
        string name,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update1Store]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddSqlXml("@demographics", demographics);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update2Store(SqlConnection sqlConnection, int businessentityid,
        int? salespersonid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Sales].[Update2Store]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@salespersonid", salespersonid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool Update1Store(SqlConnection sqlConnection, AdventureWorks.Sales.Types.StoreDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataName = data.Name;
        var dataDemographics = data.Demographics;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = Update1Store( sqlConnection, 
                        dataBusinessentityid,
                        dataName,
                        dataDemographics,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool Update2Store(SqlConnection sqlConnection, AdventureWorks.Sales.Types.StoreDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataSalespersonid = data.Salespersonid;
        var result = Update2Store( sqlConnection, 
                        dataBusinessentityid,
                        dataSalespersonid );

        return result;
    }

}
