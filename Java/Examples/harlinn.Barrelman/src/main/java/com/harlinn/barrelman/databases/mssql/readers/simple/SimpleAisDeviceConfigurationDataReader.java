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

public class SimpleAisDeviceConfigurationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  adc.[Id], \r\n" +
            "  adc.[RowVersion], \r\n" +
            "  adc.[AisDevice], \r\n" +
            "  adc.[Timestamp], \r\n" +
            "  adc.[Filter], \r\n" +
            "  adc.[NorthWestLatitude], \r\n" +
            "  adc.[NorthWestLongitude], \r\n" +
            "  adc.[SouthEastLatitude], \r\n" +
            "  adc.[SouthEastLongitude], \r\n" +
            "  adc.[ComPort], \r\n" +
            "  adc.[BaudRate], \r\n" +
            "  adc.[IPAddress], \r\n" +
            "  adc.[Port], \r\n" +
            "  adc.[UdpPort], \r\n" +
            "  adc.[Authenticate], \r\n" +
            "  adc.[UserName], \r\n" +
            "  adc.[Password], \r\n" +
            "  adc.[AuthenticationURL], \r\n" +
            "  adc.[ConnectionType], \r\n" +
            "  adc.[SourceUpdateRate], \r\n" +
            "  adc.[ConfigurationURL], \r\n" +
            "  adc.[StoreReceivedSentences] \r\n" +
            "FROM [AisDeviceConfigurationView] adc \r\n";

    public final static String BaseViewName = "AisDeviceConfigurationView";
    public final static String ViewAliasName = "adc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int AISDEVICE_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int FILTER_FIELD_ID = 5;
    public final static int NORTHWESTLATITUDE_FIELD_ID = 6;
    public final static int NORTHWESTLONGITUDE_FIELD_ID = 7;
    public final static int SOUTHEASTLATITUDE_FIELD_ID = 8;
    public final static int SOUTHEASTLONGITUDE_FIELD_ID = 9;
    public final static int COMPORT_FIELD_ID = 10;
    public final static int BAUDRATE_FIELD_ID = 11;
    public final static int IPADDRESS_FIELD_ID = 12;
    public final static int PORT_FIELD_ID = 13;
    public final static int UDPPORT_FIELD_ID = 14;
    public final static int AUTHENTICATE_FIELD_ID = 15;
    public final static int USERNAME_FIELD_ID = 16;
    public final static int PASSWORD_FIELD_ID = 17;
    public final static int AUTHENTICATIONURL_FIELD_ID = 18;
    public final static int CONNECTIONTYPE_FIELD_ID = 19;
    public final static int SOURCEUPDATERATE_FIELD_ID = 20;
    public final static int CONFIGURATIONURL_FIELD_ID = 21;
    public final static int STORERECEIVEDSENTENCES_FIELD_ID = 22;

    public SimpleAisDeviceConfigurationDataReader( ResultSet resultSet ) {
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

    public final boolean getFilter() throws SQLException {
        return getBoolean( FILTER_FIELD_ID );
    }

    public final double getNorthWestLatitude() throws SQLException {
        return getDouble( NORTHWESTLATITUDE_FIELD_ID );
    }

    public final double getNorthWestLongitude() throws SQLException {
        return getDouble( NORTHWESTLONGITUDE_FIELD_ID );
    }

    public final double getSouthEastLatitude() throws SQLException {
        return getDouble( SOUTHEASTLATITUDE_FIELD_ID );
    }

    public final double getSouthEastLongitude() throws SQLException {
        return getDouble( SOUTHEASTLONGITUDE_FIELD_ID );
    }

    public final String getComPort() throws SQLException {
        return getString( COMPORT_FIELD_ID );
    }

    public final int getBaudRate() throws SQLException {
        return getInt32( BAUDRATE_FIELD_ID );
    }

    public final String getIPAddress() throws SQLException {
        return getString( IPADDRESS_FIELD_ID );
    }

    public final int getPort() throws SQLException {
        return getInt32( PORT_FIELD_ID );
    }

    public final int getUdpPort() throws SQLException {
        return getInt32( UDPPORT_FIELD_ID );
    }

    public final boolean getAuthenticate() throws SQLException {
        return getBoolean( AUTHENTICATE_FIELD_ID );
    }

    public final String getUserName() throws SQLException {
        return getString( USERNAME_FIELD_ID );
    }

    public final String getPassword() throws SQLException {
        return getString( PASSWORD_FIELD_ID );
    }

    public final String getAuthenticationURL() throws SQLException {
        return getString( AUTHENTICATIONURL_FIELD_ID );
    }

    public final int getConnectionType() throws SQLException {
        return getInt32( CONNECTIONTYPE_FIELD_ID );
    }

    public final int getSourceUpdateRate() throws SQLException {
        return getInt32( SOURCEUPDATERATE_FIELD_ID );
    }

    public final String getConfigurationURL() throws SQLException {
        return getString( CONFIGURATIONURL_FIELD_ID );
    }

    public final boolean getStoreReceivedSentences() throws SQLException {
        return getBoolean( STORERECEIVEDSENTENCES_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.AisDeviceConfiguration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getAisDevice( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeBoolean( getFilter( ) );
        destination.writeDouble( getNorthWestLatitude( ) );
        destination.writeDouble( getNorthWestLongitude( ) );
        destination.writeDouble( getSouthEastLatitude( ) );
        destination.writeDouble( getSouthEastLongitude( ) );
        destination.writeStringUtf8( getComPort( ) );
        destination.writeInt32( getBaudRate( ) );
        destination.writeStringUtf8( getIPAddress( ) );
        destination.writeInt32( getPort( ) );
        destination.writeInt32( getUdpPort( ) );
        destination.writeBoolean( getAuthenticate( ) );
        destination.writeStringUtf8( getUserName( ) );
        destination.writeStringUtf8( getPassword( ) );
        destination.writeStringUtf8( getAuthenticationURL( ) );
        destination.writeInt32( getConnectionType( ) );
        destination.writeInt32( getSourceUpdateRate( ) );
        destination.writeStringUtf8( getConfigurationURL( ) );
        destination.writeBoolean( getStoreReceivedSentences( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public AisDeviceConfigurationObject getDataObject( ) throws SQLException {
            return new AisDeviceConfigurationObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getTimestamp( ), getFilter( ), getNorthWestLatitude( ), getNorthWestLongitude( ), getSouthEastLatitude( ), getSouthEastLongitude( ), getComPort( ), getBaudRate( ), getIPAddress( ), getPort( ), getUdpPort( ), getAuthenticate( ), getUserName( ), getPassword( ), getAuthenticationURL( ), getConnectionType( ), getSourceUpdateRate( ), getConfigurationURL( ), getStoreReceivedSentences( ) );
    }

}
