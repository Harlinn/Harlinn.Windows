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

public class SimpleDeviceHostConfigurationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  dhc.[Id], \r\n" +
            "  dhc.[RowVersion], \r\n" +
            "  dhc.[Host], \r\n" +
            "  dhc.[Timestamp], \r\n" +
            "  dhc.[Hostname], \r\n" +
            "  dhc.[Port], \r\n" +
            "  dhc.[QueueName] \r\n" +
            "FROM [DeviceHostConfigurationView] dhc \r\n";

    public final static String BaseViewName = "DeviceHostConfigurationView";
    public final static String ViewAliasName = "dhc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int HOST_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int HOSTNAME_FIELD_ID = 5;
    public final static int PORT_FIELD_ID = 6;
    public final static int QUEUENAME_FIELD_ID = 7;

    public SimpleDeviceHostConfigurationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getHost() throws SQLException {
        return getGuid( HOST_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final String getHostname() throws SQLException {
        return getString( HOSTNAME_FIELD_ID );
    }

    public final int getPort() throws SQLException {
        return getInt32( PORT_FIELD_ID );
    }

    public final String getQueueName() throws SQLException {
        return getString( QUEUENAME_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.DeviceHostConfiguration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getHost( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeStringUtf8( getHostname( ) );
        destination.writeInt32( getPort( ) );
        destination.writeStringUtf8( getQueueName( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public DeviceHostConfigurationObject getDataObject( ) throws SQLException {
            return new DeviceHostConfigurationObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getTimestamp( ), getHostname( ), getPort( ), getQueueName( ) );
    }

}
