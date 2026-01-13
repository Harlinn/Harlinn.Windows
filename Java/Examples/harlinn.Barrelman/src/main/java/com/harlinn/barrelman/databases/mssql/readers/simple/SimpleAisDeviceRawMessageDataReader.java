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

public class SimpleAisDeviceRawMessageDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  adrm.[Id], \r\n" +
            "  adrm.[RowVersion], \r\n" +
            "  adrm.[AisDevice], \r\n" +
            "  adrm.[Timestamp], \r\n" +
            "  adrm.[IsSent], \r\n" +
            "  adrm.[Message] \r\n" +
            "FROM [AisDeviceRawMessageView] adrm \r\n";

    public final static String BaseViewName = "AisDeviceRawMessageView";
    public final static String ViewAliasName = "adrm";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int AISDEVICE_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int ISSENT_FIELD_ID = 5;
    public final static int MESSAGE_FIELD_ID = 6;

    public SimpleAisDeviceRawMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getAisDevice() throws SQLException {
        return getGuid( AISDEVICE_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final boolean getIsSent() throws SQLException {
        return getBoolean( ISSENT_FIELD_ID );
    }

    public final String getMessage() throws SQLException {
        return getString( MESSAGE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.AisDeviceRawMessage );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getAisDevice( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeBoolean( getIsSent( ) );
        destination.writeStringUtf8( getMessage( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public AisDeviceRawMessageObject getDataObject( ) throws SQLException {
            return new AisDeviceRawMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getTimestamp( ), getIsSent( ), getMessage( ) );
    }

}
