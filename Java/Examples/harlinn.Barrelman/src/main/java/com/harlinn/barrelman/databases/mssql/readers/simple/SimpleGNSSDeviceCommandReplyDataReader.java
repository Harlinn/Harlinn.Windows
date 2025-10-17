package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGNSSDeviceCommandReplyDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gcr.[Id], \r\n" +
            "  gcr.[RowVersion], \r\n" +
            "  gcr.[GNSSDevice], \r\n" +
            "  gcr.[Timestamp], \r\n" +
            "  gcr.[Command], \r\n" +
            "  gcr.[Status], \r\n" +
            "  gcr.[Message] \r\n" +
            "FROM [GNSSDeviceCommandReplyView] gcr \r\n";

    public final static String BaseViewName = "GNSSDeviceCommandReplyView";
    public final static String ViewAliasName = "gcr";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int GNSSDEVICE_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int COMMAND_FIELD_ID = 5;
    public final static int STATUS_FIELD_ID = 6;
    public final static int MESSAGE_FIELD_ID = 7;

    public SimpleGNSSDeviceCommandReplyDataReader( ResultSet resultSet ) {
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

    public final Guid getCommand() throws SQLException {
        return getNullableGuid( COMMAND_FIELD_ID );
    }

    public final int getStatus() throws SQLException {
        return getInt32( STATUS_FIELD_ID );
    }

    public final String getMessage() throws SQLException {
        return getString( MESSAGE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.GNSSDeviceCommandReply );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getGNSSDevice( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeNullableGuid( getCommand( ) );
        destination.writeInt32( getStatus( ) );
        destination.writeStringUtf8( getMessage( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
