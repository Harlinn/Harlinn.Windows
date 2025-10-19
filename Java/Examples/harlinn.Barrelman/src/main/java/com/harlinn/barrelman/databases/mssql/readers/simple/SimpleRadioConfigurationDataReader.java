package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadioConfigurationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rc.[Id], \r\n" +
            "  rc.[RowVersion], \r\n" +
            "  rc.[Radio], \r\n" +
            "  rc.[Timestamp], \r\n" +
            "  rc.[Longitude], \r\n" +
            "  rc.[Latitude], \r\n" +
            "  rc.[PlaybackUrl], \r\n" +
            "  rc.[RadioIPAddress], \r\n" +
            "  rc.[RadioPort], \r\n" +
            "  rc.[Ed137IPAddress], \r\n" +
            "  rc.[Ed137Port] \r\n" +
            "FROM [RadioConfigurationView] rc \r\n";

    public final static String BaseViewName = "RadioConfigurationView";
    public final static String ViewAliasName = "rc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int RADIO_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int LONGITUDE_FIELD_ID = 5;
    public final static int LATITUDE_FIELD_ID = 6;
    public final static int PLAYBACKURL_FIELD_ID = 7;
    public final static int RADIOIPADDRESS_FIELD_ID = 8;
    public final static int RADIOPORT_FIELD_ID = 9;
    public final static int ED137IPADDRESS_FIELD_ID = 10;
    public final static int ED137PORT_FIELD_ID = 11;

    public SimpleRadioConfigurationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getRadio() throws SQLException {
        return getGuid( RADIO_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final String getPlaybackUrl() throws SQLException {
        return getString( PLAYBACKURL_FIELD_ID );
    }

    public final String getRadioIPAddress() throws SQLException {
        return getString( RADIOIPADDRESS_FIELD_ID );
    }

    public final int getRadioPort() throws SQLException {
        return getInt32( RADIOPORT_FIELD_ID );
    }

    public final String getEd137IPAddress() throws SQLException {
        return getString( ED137IPADDRESS_FIELD_ID );
    }

    public final int getEd137Port() throws SQLException {
        return getInt32( ED137PORT_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.RadioConfiguration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getRadio( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeStringUtf8( getPlaybackUrl( ) );
        destination.writeStringUtf8( getRadioIPAddress( ) );
        destination.writeInt32( getRadioPort( ) );
        destination.writeStringUtf8( getEd137IPAddress( ) );
        destination.writeInt32( getEd137Port( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public RadioConfigurationObject getDataObject( ) throws SQLException {
            return new RadioConfigurationObject( ObjectState.Stored, getId( ), getRowVersion( ), getRadio( ), getTimestamp( ), getLongitude( ), getLatitude( ), getPlaybackUrl( ), getRadioIPAddress( ), getRadioPort( ), getEd137IPAddress( ), getEd137Port( ) );
    }

}
