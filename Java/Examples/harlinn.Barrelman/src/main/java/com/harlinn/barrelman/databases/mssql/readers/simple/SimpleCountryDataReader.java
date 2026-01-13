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
package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCountryDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  c.[Id], \r\n" +
            "  c.[RowVersion], \r\n" +
            "  c.[Name], \r\n" +
            "  c.[Code], \r\n" +
            "  c.[Alpha2], \r\n" +
            "  c.[Alpha3] \r\n" +
            "FROM [CountryView] c \r\n";

    public final static String BaseViewName = "CountryView";
    public final static String ViewAliasName = "c";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int NAME_FIELD_ID = 3;
    public final static int CODE_FIELD_ID = 4;
    public final static int ALPHA2_FIELD_ID = 5;
    public final static int ALPHA3_FIELD_ID = 6;

    public SimpleCountryDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final int getCode() throws SQLException {
        return getInt32( CODE_FIELD_ID );
    }

    public final String getAlpha2() throws SQLException {
        return getString( ALPHA2_FIELD_ID );
    }

    public final String getAlpha3() throws SQLException {
        return getString( ALPHA3_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.Country );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeStringUtf8( getName( ) );
        destination.writeInt32( getCode( ) );
        destination.writeStringUtf8( getAlpha2( ) );
        destination.writeStringUtf8( getAlpha3( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public CountryObject getDataObject( ) throws SQLException {
            return new CountryObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ), getCode( ), getAlpha2( ), getAlpha3( ) );
    }

}
