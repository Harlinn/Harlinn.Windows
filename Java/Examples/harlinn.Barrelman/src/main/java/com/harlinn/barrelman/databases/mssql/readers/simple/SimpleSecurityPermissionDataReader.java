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

public class SimpleSecurityPermissionDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sp.[Id], \r\n" +
            "  sp.[RowVersion], \r\n" +
            "  sp.[Identifier], \r\n" +
            "  sp.[Timestamp], \r\n" +
            "  sp.[TypeCode], \r\n" +
            "  sp.[CanCreate], \r\n" +
            "  sp.[CanRead], \r\n" +
            "  sp.[CanUpdate], \r\n" +
            "  sp.[CanDelete] \r\n" +
            "FROM [SecurityPermissionView] sp \r\n";

    public final static String BaseViewName = "SecurityPermissionView";
    public final static String ViewAliasName = "sp";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int IDENTIFIER_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int TYPECODE_FIELD_ID = 5;
    public final static int CANCREATE_FIELD_ID = 6;
    public final static int CANREAD_FIELD_ID = 7;
    public final static int CANUPDATE_FIELD_ID = 8;
    public final static int CANDELETE_FIELD_ID = 9;

    public SimpleSecurityPermissionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getIdentifier() throws SQLException {
        return getGuid( IDENTIFIER_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final int getTypeCode() throws SQLException {
        return getInt32( TYPECODE_FIELD_ID );
    }

    public final boolean getCanCreate() throws SQLException {
        return getBoolean( CANCREATE_FIELD_ID );
    }

    public final boolean getCanRead() throws SQLException {
        return getBoolean( CANREAD_FIELD_ID );
    }

    public final boolean getCanUpdate() throws SQLException {
        return getBoolean( CANUPDATE_FIELD_ID );
    }

    public final boolean getCanDelete() throws SQLException {
        return getBoolean( CANDELETE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.SecurityPermission );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getIdentifier( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeInt32( getTypeCode( ) );
        destination.writeBoolean( getCanCreate( ) );
        destination.writeBoolean( getCanRead( ) );
        destination.writeBoolean( getCanUpdate( ) );
        destination.writeBoolean( getCanDelete( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public SecurityPermissionObject getDataObject( ) throws SQLException {
            return new SecurityPermissionObject( ObjectState.Stored, getId( ), getRowVersion( ), getIdentifier( ), getTimestamp( ), getTypeCode( ), getCanCreate( ), getCanRead( ), getCanUpdate( ), getCanDelete( ) );
    }

}
