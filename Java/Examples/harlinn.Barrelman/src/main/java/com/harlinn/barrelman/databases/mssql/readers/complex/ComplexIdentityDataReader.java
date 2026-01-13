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
package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexIdentityDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  i.[Id], \r\n" +
            "  i.[EntityType], \r\n" +
            "  i.[RowVersion], \r\n" +
            "  c.[Identifier], \r\n" +
            "  imon.[Identifier], \r\n" +
            "  mmsi.[Identifier], \r\n" +
            "  n.[Text] \r\n" +
            "FROM [IdentityView] i \r\n" +
            "  LEFT JOIN [Callsign] c ON(i.[Id] = c.[Id] ) \r\n" +
            "  LEFT JOIN [InternationalMaritimeOrganizationNumber] imon ON(i.[Id] = imon.[Id] ) \r\n" +
            "  LEFT JOIN [MaritimeMobileServiceIdentity] mmsi ON(i.[Id] = mmsi.[Id] ) \r\n" +
            "  LEFT JOIN [Name] n ON(i.[Id] = n.[Id] ) \r\n";

    public final static String BaseViewName = "IdentityView";
    public final static String ViewAliasName = "i";

    public final static int I_ID_FIELD_ID = 1;
    public final static int I_KIND_FIELD_ID = 2;
    public final static int I_ROWVERSION_FIELD_ID = 3;
    public final static int C_IDENTIFIER_FIELD_ID = 4;
    public final static int IMON_IDENTIFIER_FIELD_ID = 5;
    public final static int MMSI_IDENTIFIER_FIELD_ID = 6;
    public final static int N_TEXT_FIELD_ID = 7;

    public ComplexIdentityDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( I_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( I_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( I_ROWVERSION_FIELD_ID );
    }

    public String getCallsignIdentifier( ) throws SQLException {
        return getString( C_IDENTIFIER_FIELD_ID );
    }

    public long getInternationalMaritimeOrganizationNumberIdentifier( ) throws SQLException {
        return getInt64( IMON_IDENTIFIER_FIELD_ID );
    }

    public long getMaritimeMobileServiceIdentityIdentifier( ) throws SQLException {
        return getInt64( MMSI_IDENTIFIER_FIELD_ID );
    }

    public String getNameText( ) throws SQLException {
        return getString( N_TEXT_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.Callsign: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeStringUtf8( getCallsignIdentifier( ) );
            }
            break;
            case Kind.InternationalMaritimeOrganizationNumber: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeInt64( getInternationalMaritimeOrganizationNumberIdentifier( ) );
            }
            break;
            case Kind.MaritimeMobileServiceIdentity: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeInt64( getMaritimeMobileServiceIdentityIdentifier( ) );
            }
            break;
            case Kind.Name: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeStringUtf8( getNameText( ) );
            }
            break;
            default: {
                var exc = new SQLException( "Cannot perform serialization for kind=" + kind + "." );
                throw exc;
            }
        }
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public IdentityObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.Callsign: {
                return new CallsignObject( ObjectState.Stored, getId( ), getRowVersion( ), getCallsignIdentifier( ) );
            }
            case Kind.InternationalMaritimeOrganizationNumber: {
                return new InternationalMaritimeOrganizationNumberObject( ObjectState.Stored, getId( ), getRowVersion( ), getInternationalMaritimeOrganizationNumberIdentifier( ) );
            }
            case Kind.MaritimeMobileServiceIdentity: {
                return new MaritimeMobileServiceIdentityObject( ObjectState.Stored, getId( ), getRowVersion( ), getMaritimeMobileServiceIdentityIdentifier( ) );
            }
            case Kind.Name: {
                return new NameObject( ObjectState.Stored, getId( ), getRowVersion( ), getNameText( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

