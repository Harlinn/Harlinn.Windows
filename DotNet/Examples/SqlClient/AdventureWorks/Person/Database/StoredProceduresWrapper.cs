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

namespace AdventureWorks.Person.Database;

public class StoredProceduresWrapper
{
    public static bool InsertAddress(SqlConnection sqlConnection, ref int addressid,
        string addressline1,
        string? addressline2,
        string city,
        int stateprovinceid,
        string postalcode,
        SqlGeography? spatiallocation,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertAddress]";

        var addressidParameter = command.Parameters.AddInt32("@addressid");
        command.Parameters.AddNVarChar("@addressline1", addressline1, 60);
        command.Parameters.AddNVarChar("@addressline2", addressline2, 60);
        command.Parameters.AddNVarChar("@city", city, 30);
        command.Parameters.AddInt32("@stateprovinceid", stateprovinceid);
        command.Parameters.AddNVarChar("@postalcode", postalcode, 15);
        command.Parameters.AddSqlGeography("@spatiallocation", spatiallocation);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            addressid = (int)addressidParameter.Value;
        }
        return result;
    }

    public static bool MergeAddress(SqlConnection sqlConnection, AdventureWorks.Person.Database.DataTables.AddressDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Person].[MergeAddress]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertAddress(SqlConnection sqlConnection, AdventureWorks.Person.Types.AddressDataType data )
    {
        var dataAddressid = data.Addressid;
        var dataAddressline1 = data.Addressline1;
        var dataAddressline2 = data.Addressline2;
        var dataCity = data.City;
        var dataStateprovinceid = data.Stateprovinceid;
        var dataPostalcode = data.Postalcode;
        var dataSpatiallocation = data.Spatiallocation;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertAddress( sqlConnection, 
                        ref dataAddressid,
                        dataAddressline1,
                        dataAddressline2,
                        dataCity,
                        dataStateprovinceid,
                        dataPostalcode,
                        dataSpatiallocation,
                        dataRowguid,
                        dataModifieddate );
        data.Addressid = dataAddressid;

        return result;
    }

    public static bool UpdateAddress(SqlConnection sqlConnection, int addressid,
        string addressline1,
        string? addressline2,
        string city,
        int stateprovinceid,
        string postalcode,
        SqlGeography? spatiallocation,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateAddress]";

        command.Parameters.AddInt32("@addressid", addressid);
        command.Parameters.AddNVarChar("@addressline1", addressline1, 60);
        command.Parameters.AddNVarChar("@addressline2", addressline2, 60);
        command.Parameters.AddNVarChar("@city", city, 30);
        command.Parameters.AddInt32("@stateprovinceid", stateprovinceid);
        command.Parameters.AddNVarChar("@postalcode", postalcode, 15);
        command.Parameters.AddSqlGeography("@spatiallocation", spatiallocation);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateAddress(SqlConnection sqlConnection, AdventureWorks.Person.Types.AddressDataType data )
    {
        var dataAddressid = data.Addressid;
        var dataAddressline1 = data.Addressline1;
        var dataAddressline2 = data.Addressline2;
        var dataCity = data.City;
        var dataStateprovinceid = data.Stateprovinceid;
        var dataPostalcode = data.Postalcode;
        var dataSpatiallocation = data.Spatiallocation;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateAddress( sqlConnection, 
                        dataAddressid,
                        dataAddressline1,
                        dataAddressline2,
                        dataCity,
                        dataStateprovinceid,
                        dataPostalcode,
                        dataSpatiallocation,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteAddress(SqlConnection sqlConnection, int addressid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteAddress]";

        command.Parameters.AddInt32("@addressid", addressid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteAddress(SqlConnection sqlConnection, AdventureWorks.Person.Types.AddressDataType data )
    {
        var dataAddressid = data.Addressid;
        var result = DeleteAddress( sqlConnection, 
                        dataAddressid );

        return result;
    }

    public static bool InsertAddresstype(SqlConnection sqlConnection, ref int addresstypeid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertAddressType]";

        var addresstypeidParameter = command.Parameters.AddInt32("@addresstypeid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            addresstypeid = (int)addresstypeidParameter.Value;
        }
        return result;
    }

    public static bool MergeAddresstype(SqlConnection sqlConnection, AdventureWorks.Person.Database.DataTables.AddresstypeDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Person].[MergeAddressType]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertAddresstype(SqlConnection sqlConnection, AdventureWorks.Person.Types.AddresstypeDataType data )
    {
        var dataAddresstypeid = data.Addresstypeid;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertAddresstype( sqlConnection, 
                        ref dataAddresstypeid,
                        dataName,
                        dataRowguid,
                        dataModifieddate );
        data.Addresstypeid = dataAddresstypeid;

        return result;
    }

    public static bool UpdateAddresstype(SqlConnection sqlConnection, int addresstypeid,
        string name,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateAddressType]";

        command.Parameters.AddInt32("@addresstypeid", addresstypeid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateAddresstype(SqlConnection sqlConnection, AdventureWorks.Person.Types.AddresstypeDataType data )
    {
        var dataAddresstypeid = data.Addresstypeid;
        var dataName = data.Name;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateAddresstype( sqlConnection, 
                        dataAddresstypeid,
                        dataName,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteAddresstype(SqlConnection sqlConnection, int addresstypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteAddressType]";

        command.Parameters.AddInt32("@addresstypeid", addresstypeid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteAddresstype(SqlConnection sqlConnection, AdventureWorks.Person.Types.AddresstypeDataType data )
    {
        var dataAddresstypeid = data.Addresstypeid;
        var result = DeleteAddresstype( sqlConnection, 
                        dataAddresstypeid );

        return result;
    }

    public static bool InsertBusinessentity(SqlConnection sqlConnection, ref int businessentityid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertBusinessEntity]";

        var businessentityidParameter = command.Parameters.AddInt32("@businessentityid");
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            businessentityid = (int)businessentityidParameter.Value;
        }
        return result;
    }

    public static bool MergeBusinessentity(SqlConnection sqlConnection, AdventureWorks.Person.Database.DataTables.BusinessentityDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Person].[MergeBusinessEntity]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertBusinessentity(SqlConnection sqlConnection, AdventureWorks.Person.Types.BusinessentityDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertBusinessentity( sqlConnection, 
                        ref dataBusinessentityid,
                        dataRowguid,
                        dataModifieddate );
        data.Businessentityid = dataBusinessentityid;

        return result;
    }

    public static bool UpdateBusinessentity(SqlConnection sqlConnection, int businessentityid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateBusinessEntity]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateBusinessentity(SqlConnection sqlConnection, AdventureWorks.Person.Types.BusinessentityDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateBusinessentity( sqlConnection, 
                        dataBusinessentityid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteBusinessentity(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteBusinessEntity]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteBusinessentity(SqlConnection sqlConnection, AdventureWorks.Person.Types.BusinessentityDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var result = DeleteBusinessentity( sqlConnection, 
                        dataBusinessentityid );

        return result;
    }

    public static bool InsertBusinessentityaddress(SqlConnection sqlConnection, int businessentityid,
        int addressid,
        int addresstypeid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertBusinessEntityAddress]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@addressid", addressid);
        command.Parameters.AddInt32("@addresstypeid", addresstypeid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeBusinessentityaddress(SqlConnection sqlConnection, AdventureWorks.Person.Database.DataTables.BusinessentityaddressDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Person].[MergeBusinessEntityAddress]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertBusinessentityaddress(SqlConnection sqlConnection, AdventureWorks.Person.Types.BusinessentityaddressDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataAddressid = data.Addressid;
        var dataAddresstypeid = data.Addresstypeid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertBusinessentityaddress( sqlConnection, 
                        dataBusinessentityid,
                        dataAddressid,
                        dataAddresstypeid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateBusinessentityaddress(SqlConnection sqlConnection, int businessentityid,
        int addressid,
        int addresstypeid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateBusinessEntityAddress]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@addressid", addressid);
        command.Parameters.AddInt32("@addresstypeid", addresstypeid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateBusinessentityaddress(SqlConnection sqlConnection, AdventureWorks.Person.Types.BusinessentityaddressDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataAddressid = data.Addressid;
        var dataAddresstypeid = data.Addresstypeid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateBusinessentityaddress( sqlConnection, 
                        dataBusinessentityid,
                        dataAddressid,
                        dataAddresstypeid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteBusinessentityaddress(SqlConnection sqlConnection, int businessentityid,
        int addressid,
        int addresstypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteBusinessEntityAddress]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@addressid", addressid);
        command.Parameters.AddInt32("@addresstypeid", addresstypeid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteBusinessentityaddress(SqlConnection sqlConnection, AdventureWorks.Person.Types.BusinessentityaddressDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataAddressid = data.Addressid;
        var dataAddresstypeid = data.Addresstypeid;
        var result = DeleteBusinessentityaddress( sqlConnection, 
                        dataBusinessentityid,
                        dataAddressid,
                        dataAddresstypeid );

        return result;
    }

    public static bool InsertBusinessentitycontact(SqlConnection sqlConnection, int businessentityid,
        int personid,
        int contacttypeid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertBusinessEntityContact]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@personid", personid);
        command.Parameters.AddInt32("@contacttypeid", contacttypeid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeBusinessentitycontact(SqlConnection sqlConnection, AdventureWorks.Person.Database.DataTables.BusinessentitycontactDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Person].[MergeBusinessEntityContact]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertBusinessentitycontact(SqlConnection sqlConnection, AdventureWorks.Person.Types.BusinessentitycontactDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPersonid = data.Personid;
        var dataContacttypeid = data.Contacttypeid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertBusinessentitycontact( sqlConnection, 
                        dataBusinessentityid,
                        dataPersonid,
                        dataContacttypeid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateBusinessentitycontact(SqlConnection sqlConnection, int businessentityid,
        int personid,
        int contacttypeid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateBusinessEntityContact]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@personid", personid);
        command.Parameters.AddInt32("@contacttypeid", contacttypeid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateBusinessentitycontact(SqlConnection sqlConnection, AdventureWorks.Person.Types.BusinessentitycontactDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPersonid = data.Personid;
        var dataContacttypeid = data.Contacttypeid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateBusinessentitycontact( sqlConnection, 
                        dataBusinessentityid,
                        dataPersonid,
                        dataContacttypeid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteBusinessentitycontact(SqlConnection sqlConnection, int businessentityid,
        int personid,
        int contacttypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteBusinessEntityContact]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@personid", personid);
        command.Parameters.AddInt32("@contacttypeid", contacttypeid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteBusinessentitycontact(SqlConnection sqlConnection, AdventureWorks.Person.Types.BusinessentitycontactDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPersonid = data.Personid;
        var dataContacttypeid = data.Contacttypeid;
        var result = DeleteBusinessentitycontact( sqlConnection, 
                        dataBusinessentityid,
                        dataPersonid,
                        dataContacttypeid );

        return result;
    }

    public static bool InsertContacttype(SqlConnection sqlConnection, ref int contacttypeid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertContactType]";

        var contacttypeidParameter = command.Parameters.AddInt32("@contacttypeid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            contacttypeid = (int)contacttypeidParameter.Value;
        }
        return result;
    }

    public static bool MergeContacttype(SqlConnection sqlConnection, AdventureWorks.Person.Database.DataTables.ContacttypeDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Person].[MergeContactType]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertContacttype(SqlConnection sqlConnection, AdventureWorks.Person.Types.ContacttypeDataType data )
    {
        var dataContacttypeid = data.Contacttypeid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertContacttype( sqlConnection, 
                        ref dataContacttypeid,
                        dataName,
                        dataModifieddate );
        data.Contacttypeid = dataContacttypeid;

        return result;
    }

    public static bool UpdateContacttype(SqlConnection sqlConnection, int contacttypeid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateContactType]";

        command.Parameters.AddInt32("@contacttypeid", contacttypeid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateContacttype(SqlConnection sqlConnection, AdventureWorks.Person.Types.ContacttypeDataType data )
    {
        var dataContacttypeid = data.Contacttypeid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateContacttype( sqlConnection, 
                        dataContacttypeid,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteContacttype(SqlConnection sqlConnection, int contacttypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteContactType]";

        command.Parameters.AddInt32("@contacttypeid", contacttypeid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteContacttype(SqlConnection sqlConnection, AdventureWorks.Person.Types.ContacttypeDataType data )
    {
        var dataContacttypeid = data.Contacttypeid;
        var result = DeleteContacttype( sqlConnection, 
                        dataContacttypeid );

        return result;
    }

    public static bool InsertCountryregion(SqlConnection sqlConnection, string countryregioncode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertCountryRegion]";

        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergeCountryregion(SqlConnection sqlConnection, AdventureWorks.Person.Database.DataTables.CountryregionDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Person].[MergeCountryRegion]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertCountryregion(SqlConnection sqlConnection, AdventureWorks.Person.Types.CountryregionDataType data )
    {
        var dataCountryregioncode = data.Countryregioncode;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertCountryregion( sqlConnection, 
                        dataCountryregioncode,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool UpdateCountryregion(SqlConnection sqlConnection, string countryregioncode,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateCountryRegion]";

        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateCountryregion(SqlConnection sqlConnection, AdventureWorks.Person.Types.CountryregionDataType data )
    {
        var dataCountryregioncode = data.Countryregioncode;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateCountryregion( sqlConnection, 
                        dataCountryregioncode,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteCountryregion(SqlConnection sqlConnection, string countryregioncode)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteCountryRegion]";

        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteCountryregion(SqlConnection sqlConnection, AdventureWorks.Person.Types.CountryregionDataType data )
    {
        var dataCountryregioncode = data.Countryregioncode;
        var result = DeleteCountryregion( sqlConnection, 
                        dataCountryregioncode );

        return result;
    }

    public static bool InsertEmailaddress(SqlConnection sqlConnection, int businessentityid,
        ref int emailaddressid,
        string? emailaddress,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertEmailAddress]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        var emailaddressidParameter = command.Parameters.AddInt32("@emailaddressid");
        command.Parameters.AddNVarChar("@emailaddress", emailaddress, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            emailaddressid = (int)emailaddressidParameter.Value;
        }
        return result;
    }

    public static bool MergeEmailaddress(SqlConnection sqlConnection, AdventureWorks.Person.Database.DataTables.EmailaddressDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Person].[MergeEmailAddress]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertEmailaddress(SqlConnection sqlConnection, AdventureWorks.Person.Types.EmailaddressDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataEmailaddressid = data.Emailaddressid;
        var dataEmailaddress = data.Emailaddress;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertEmailaddress( sqlConnection, 
                        dataBusinessentityid,
                        ref dataEmailaddressid,
                        dataEmailaddress,
                        dataRowguid,
                        dataModifieddate );
        data.Emailaddressid = dataEmailaddressid;

        return result;
    }

    public static bool UpdateEmailaddress(SqlConnection sqlConnection, int businessentityid,
        int emailaddressid,
        string? emailaddress,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateEmailAddress]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@emailaddressid", emailaddressid);
        command.Parameters.AddNVarChar("@emailaddress", emailaddress, 50);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateEmailaddress(SqlConnection sqlConnection, AdventureWorks.Person.Types.EmailaddressDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataEmailaddressid = data.Emailaddressid;
        var dataEmailaddress = data.Emailaddress;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateEmailaddress( sqlConnection, 
                        dataBusinessentityid,
                        dataEmailaddressid,
                        dataEmailaddress,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteEmailaddress(SqlConnection sqlConnection, int businessentityid,
        int emailaddressid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteEmailAddress]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddInt32("@emailaddressid", emailaddressid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteEmailaddress(SqlConnection sqlConnection, AdventureWorks.Person.Types.EmailaddressDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataEmailaddressid = data.Emailaddressid;
        var result = DeleteEmailaddress( sqlConnection, 
                        dataBusinessentityid,
                        dataEmailaddressid );

        return result;
    }

    public static bool InsertPassword(SqlConnection sqlConnection, int businessentityid,
        string passwordhash,
        string passwordsalt,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertPassword]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddVarChar("@passwordhash", passwordhash, 128);
        command.Parameters.AddVarChar("@passwordsalt", passwordsalt, 10);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergePassword(SqlConnection sqlConnection, AdventureWorks.Person.Database.DataTables.PasswordDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Person].[MergePassword]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertPassword(SqlConnection sqlConnection, AdventureWorks.Person.Types.PasswordDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPasswordhash = data.Passwordhash;
        var dataPasswordsalt = data.Passwordsalt;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPassword( sqlConnection, 
                        dataBusinessentityid,
                        dataPasswordhash,
                        dataPasswordsalt,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdatePassword(SqlConnection sqlConnection, int businessentityid,
        string passwordhash,
        string passwordsalt,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdatePassword]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddVarChar("@passwordhash", passwordhash, 128);
        command.Parameters.AddVarChar("@passwordsalt", passwordsalt, 10);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePassword(SqlConnection sqlConnection, AdventureWorks.Person.Types.PasswordDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPasswordhash = data.Passwordhash;
        var dataPasswordsalt = data.Passwordsalt;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePassword( sqlConnection, 
                        dataBusinessentityid,
                        dataPasswordhash,
                        dataPasswordsalt,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePassword(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeletePassword]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePassword(SqlConnection sqlConnection, AdventureWorks.Person.Types.PasswordDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var result = DeletePassword( sqlConnection, 
                        dataBusinessentityid );

        return result;
    }

    public static bool InsertPerson(SqlConnection sqlConnection, int businessentityid,
        string persontype,
        bool namestyle,
        string? title,
        string firstname,
        string? middlename,
        string lastname,
        string? suffix,
        int emailpromotion,
        SqlXml? additionalcontactinfo,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertPerson]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNChar("@persontype", persontype, 2);
        command.Parameters.AddBoolean("@namestyle", namestyle);
        command.Parameters.AddNVarChar("@title", title, 8);
        command.Parameters.AddNVarChar("@firstname", firstname, 50);
        command.Parameters.AddNVarChar("@middlename", middlename, 50);
        command.Parameters.AddNVarChar("@lastname", lastname, 50);
        command.Parameters.AddNVarChar("@suffix", suffix, 10);
        command.Parameters.AddInt32("@emailpromotion", emailpromotion);
        command.Parameters.AddSqlXml("@additionalcontactinfo", additionalcontactinfo);
        command.Parameters.AddSqlXml("@demographics", demographics);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergePerson(SqlConnection sqlConnection, AdventureWorks.Person.Database.DataTables.PersonDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Person].[MergePerson]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertPerson(SqlConnection sqlConnection, AdventureWorks.Person.Types.PersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPersontype = data.Persontype;
        var dataNamestyle = data.Namestyle;
        var dataTitle = data.Title;
        var dataFirstname = data.Firstname;
        var dataMiddlename = data.Middlename;
        var dataLastname = data.Lastname;
        var dataSuffix = data.Suffix;
        var dataEmailpromotion = data.Emailpromotion;
        var dataAdditionalcontactinfo = data.Additionalcontactinfo;
        var dataDemographics = data.Demographics;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPerson( sqlConnection, 
                        dataBusinessentityid,
                        dataPersontype,
                        dataNamestyle,
                        dataTitle,
                        dataFirstname,
                        dataMiddlename,
                        dataLastname,
                        dataSuffix,
                        dataEmailpromotion,
                        dataAdditionalcontactinfo,
                        dataDemographics,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdatePerson(SqlConnection sqlConnection, int businessentityid,
        string persontype,
        bool namestyle,
        string? title,
        string firstname,
        string? middlename,
        string lastname,
        string? suffix,
        int emailpromotion,
        SqlXml? additionalcontactinfo,
        SqlXml? demographics,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdatePerson]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNChar("@persontype", persontype, 2);
        command.Parameters.AddBoolean("@namestyle", namestyle);
        command.Parameters.AddNVarChar("@title", title, 8);
        command.Parameters.AddNVarChar("@firstname", firstname, 50);
        command.Parameters.AddNVarChar("@middlename", middlename, 50);
        command.Parameters.AddNVarChar("@lastname", lastname, 50);
        command.Parameters.AddNVarChar("@suffix", suffix, 10);
        command.Parameters.AddInt32("@emailpromotion", emailpromotion);
        command.Parameters.AddSqlXml("@additionalcontactinfo", additionalcontactinfo);
        command.Parameters.AddSqlXml("@demographics", demographics);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePerson(SqlConnection sqlConnection, AdventureWorks.Person.Types.PersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPersontype = data.Persontype;
        var dataNamestyle = data.Namestyle;
        var dataTitle = data.Title;
        var dataFirstname = data.Firstname;
        var dataMiddlename = data.Middlename;
        var dataLastname = data.Lastname;
        var dataSuffix = data.Suffix;
        var dataEmailpromotion = data.Emailpromotion;
        var dataAdditionalcontactinfo = data.Additionalcontactinfo;
        var dataDemographics = data.Demographics;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePerson( sqlConnection, 
                        dataBusinessentityid,
                        dataPersontype,
                        dataNamestyle,
                        dataTitle,
                        dataFirstname,
                        dataMiddlename,
                        dataLastname,
                        dataSuffix,
                        dataEmailpromotion,
                        dataAdditionalcontactinfo,
                        dataDemographics,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePerson(SqlConnection sqlConnection, int businessentityid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeletePerson]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePerson(SqlConnection sqlConnection, AdventureWorks.Person.Types.PersonDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var result = DeletePerson( sqlConnection, 
                        dataBusinessentityid );

        return result;
    }

    public static bool InsertPersonphone(SqlConnection sqlConnection, int businessentityid,
        string phonenumber,
        int phonenumbertypeid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertPersonPhone]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@phonenumber", phonenumber, 25);
        command.Parameters.AddInt32("@phonenumbertypeid", phonenumbertypeid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool MergePersonphone(SqlConnection sqlConnection, AdventureWorks.Person.Database.DataTables.PersonphoneDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Person].[MergePersonPhone]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertPersonphone(SqlConnection sqlConnection, AdventureWorks.Person.Types.PersonphoneDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPhonenumber = data.Phonenumber;
        var dataPhonenumbertypeid = data.Phonenumbertypeid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPersonphone( sqlConnection, 
                        dataBusinessentityid,
                        dataPhonenumber,
                        dataPhonenumbertypeid,
                        dataModifieddate );

        return result;
    }

    public static bool UpdatePersonphone(SqlConnection sqlConnection, int businessentityid,
        string phonenumber,
        int phonenumbertypeid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdatePersonPhone]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@phonenumber", phonenumber, 25);
        command.Parameters.AddInt32("@phonenumbertypeid", phonenumbertypeid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePersonphone(SqlConnection sqlConnection, AdventureWorks.Person.Types.PersonphoneDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPhonenumber = data.Phonenumber;
        var dataPhonenumbertypeid = data.Phonenumbertypeid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePersonphone( sqlConnection, 
                        dataBusinessentityid,
                        dataPhonenumber,
                        dataPhonenumbertypeid,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePersonphone(SqlConnection sqlConnection, int businessentityid,
        string phonenumber,
        int phonenumbertypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeletePersonPhone]";

        command.Parameters.AddInt32("@businessentityid", businessentityid);
        command.Parameters.AddNVarChar("@phonenumber", phonenumber, 25);
        command.Parameters.AddInt32("@phonenumbertypeid", phonenumbertypeid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePersonphone(SqlConnection sqlConnection, AdventureWorks.Person.Types.PersonphoneDataType data )
    {
        var dataBusinessentityid = data.Businessentityid;
        var dataPhonenumber = data.Phonenumber;
        var dataPhonenumbertypeid = data.Phonenumbertypeid;
        var result = DeletePersonphone( sqlConnection, 
                        dataBusinessentityid,
                        dataPhonenumber,
                        dataPhonenumbertypeid );

        return result;
    }

    public static bool InsertPhonenumbertype(SqlConnection sqlConnection, ref int phonenumbertypeid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertPhoneNumberType]";

        var phonenumbertypeidParameter = command.Parameters.AddInt32("@phonenumbertypeid");
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            phonenumbertypeid = (int)phonenumbertypeidParameter.Value;
        }
        return result;
    }

    public static bool MergePhonenumbertype(SqlConnection sqlConnection, AdventureWorks.Person.Database.DataTables.PhonenumbertypeDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Person].[MergePhoneNumberType]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertPhonenumbertype(SqlConnection sqlConnection, AdventureWorks.Person.Types.PhonenumbertypeDataType data )
    {
        var dataPhonenumbertypeid = data.Phonenumbertypeid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = InsertPhonenumbertype( sqlConnection, 
                        ref dataPhonenumbertypeid,
                        dataName,
                        dataModifieddate );
        data.Phonenumbertypeid = dataPhonenumbertypeid;

        return result;
    }

    public static bool UpdatePhonenumbertype(SqlConnection sqlConnection, int phonenumbertypeid,
        string name,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdatePhoneNumberType]";

        command.Parameters.AddInt32("@phonenumbertypeid", phonenumbertypeid);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdatePhonenumbertype(SqlConnection sqlConnection, AdventureWorks.Person.Types.PhonenumbertypeDataType data )
    {
        var dataPhonenumbertypeid = data.Phonenumbertypeid;
        var dataName = data.Name;
        var dataModifieddate = data.Modifieddate;
        var result = UpdatePhonenumbertype( sqlConnection, 
                        dataPhonenumbertypeid,
                        dataName,
                        dataModifieddate );

        return result;
    }

    public static bool DeletePhonenumbertype(SqlConnection sqlConnection, int phonenumbertypeid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeletePhoneNumberType]";

        command.Parameters.AddInt32("@phonenumbertypeid", phonenumbertypeid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeletePhonenumbertype(SqlConnection sqlConnection, AdventureWorks.Person.Types.PhonenumbertypeDataType data )
    {
        var dataPhonenumbertypeid = data.Phonenumbertypeid;
        var result = DeletePhonenumbertype( sqlConnection, 
                        dataPhonenumbertypeid );

        return result;
    }

    public static bool InsertStateprovince(SqlConnection sqlConnection, ref int stateprovinceid,
        string stateprovincecode,
        string countryregioncode,
        bool isonlystateprovinceflag,
        string name,
        int territoryid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[InsertStateProvince]";

        var stateprovinceidParameter = command.Parameters.AddInt32("@stateprovinceid");
        command.Parameters.AddNChar("@stateprovincecode", stateprovincecode, 3);
        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddBoolean("@isonlystateprovinceflag", isonlystateprovinceflag);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        if(result)
        {
            stateprovinceid = (int)stateprovinceidParameter.Value;
        }
        return result;
    }

    public static bool MergeStateprovince(SqlConnection sqlConnection, AdventureWorks.Person.Database.DataTables.StateprovinceDataTable data )
    {
        using (var command = new SqlCommand())
        {
            command.Connection = sqlConnection;
           command.CommandText = "[Person].[MergeStateProvince]";
            command.CommandType = CommandType.StoredProcedure;
            SqlParameter parameter = command.Parameters.AddWithValue("@Data", data.DataTable);
            parameter.SqlDbType = SqlDbType.Structured;
            return command.ExecuteNonQuery() > 0;
        }
    }
    public static bool InsertStateprovince(SqlConnection sqlConnection, AdventureWorks.Person.Types.StateprovinceDataType data )
    {
        var dataStateprovinceid = data.Stateprovinceid;
        var dataStateprovincecode = data.Stateprovincecode;
        var dataCountryregioncode = data.Countryregioncode;
        var dataIsonlystateprovinceflag = data.Isonlystateprovinceflag;
        var dataName = data.Name;
        var dataTerritoryid = data.Territoryid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = InsertStateprovince( sqlConnection, 
                        ref dataStateprovinceid,
                        dataStateprovincecode,
                        dataCountryregioncode,
                        dataIsonlystateprovinceflag,
                        dataName,
                        dataTerritoryid,
                        dataRowguid,
                        dataModifieddate );
        data.Stateprovinceid = dataStateprovinceid;

        return result;
    }

    public static bool UpdateStateprovince(SqlConnection sqlConnection, int stateprovinceid,
        string stateprovincecode,
        string countryregioncode,
        bool isonlystateprovinceflag,
        string name,
        int territoryid,
        Guid rowguid,
        DateTime modifieddate)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[UpdateStateProvince]";

        command.Parameters.AddInt32("@stateprovinceid", stateprovinceid);
        command.Parameters.AddNChar("@stateprovincecode", stateprovincecode, 3);
        command.Parameters.AddNVarChar("@countryregioncode", countryregioncode, 3);
        command.Parameters.AddBoolean("@isonlystateprovinceflag", isonlystateprovinceflag);
        command.Parameters.AddNVarChar("@name", name, 50);
        command.Parameters.AddInt32("@territoryid", territoryid);
        command.Parameters.AddGuid("@rowguid", rowguid);
        command.Parameters.AddDateTime("@modifieddate", modifieddate);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool UpdateStateprovince(SqlConnection sqlConnection, AdventureWorks.Person.Types.StateprovinceDataType data )
    {
        var dataStateprovinceid = data.Stateprovinceid;
        var dataStateprovincecode = data.Stateprovincecode;
        var dataCountryregioncode = data.Countryregioncode;
        var dataIsonlystateprovinceflag = data.Isonlystateprovinceflag;
        var dataName = data.Name;
        var dataTerritoryid = data.Territoryid;
        var dataRowguid = data.Rowguid;
        var dataModifieddate = data.Modifieddate;
        var result = UpdateStateprovince( sqlConnection, 
                        dataStateprovinceid,
                        dataStateprovincecode,
                        dataCountryregioncode,
                        dataIsonlystateprovinceflag,
                        dataName,
                        dataTerritoryid,
                        dataRowguid,
                        dataModifieddate );

        return result;
    }

    public static bool DeleteStateprovince(SqlConnection sqlConnection, int stateprovinceid)
    {
        using var command = sqlConnection.CreateCommand();
        command.CommandType = CommandType.StoredProcedure;
        command.CommandText = "[Person].[DeleteStateProvince]";

        command.Parameters.AddInt32("@stateprovinceid", stateprovinceid);

        var result = command.ExecuteNonQuery() > 0;
        return result;
    }

    public static bool DeleteStateprovince(SqlConnection sqlConnection, AdventureWorks.Person.Types.StateprovinceDataType data )
    {
        var dataStateprovinceid = data.Stateprovinceid;
        var result = DeleteStateprovince( sqlConnection, 
                        dataStateprovinceid );

        return result;
    }

}
