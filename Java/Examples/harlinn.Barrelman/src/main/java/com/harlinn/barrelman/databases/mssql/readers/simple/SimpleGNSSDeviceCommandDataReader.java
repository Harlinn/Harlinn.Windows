package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGNSSDeviceCommandDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gc.[Id], \r\n" +
            "  gc.[RowVersion], \r\n" +
            "  gc.[GNSSDevice], \r\n" +
            "  gc.[Timestamp], \r\n" +
            "  gc.[DeviceCommandSourceType], \r\n" +
            "  gc.[DeviceCommandSourceId], \r\n" +
            "  gc.[Reply] \r\n" +
            "FROM [GNSSDeviceCommandView] gc \r\n";

    public final static String BaseViewName = "GNSSDeviceCommandView";
    public final static String ViewAliasName = "gc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int GNSSDEVICE_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
    public final static int DEVICECOMMANDSOURCEID_FIELD_ID = 6;
    public final static int REPLY_FIELD_ID = 7;

    public SimpleGNSSDeviceCommandDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getGNSSDevice() throws SQLException {
        return getGuid( GNSSDEVICE_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final int getDeviceCommandSourceType() throws SQLException {
        return getInt32( DEVICECOMMANDSOURCETYPE_FIELD_ID );
    }

    public final Guid getDeviceCommandSourceId() throws SQLException {
        return getGuid( DEVICECOMMANDSOURCEID_FIELD_ID );
    }

    public final Guid getReply() throws SQLException {
        return getNullableGuid( REPLY_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.GNSSDeviceCommand );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getGNSSDevice( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeInt32( getDeviceCommandSourceType( ) );
        destination.writeGuid( getDeviceCommandSourceId( ) );
        destination.writeNullableGuid( getReply( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public GNSSDeviceCommandObject getDataObject( ) throws SQLException {
            return new GNSSDeviceCommandObject( ObjectState.Stored, getId( ), getRowVersion( ), getGNSSDevice( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ) );
    }

}
