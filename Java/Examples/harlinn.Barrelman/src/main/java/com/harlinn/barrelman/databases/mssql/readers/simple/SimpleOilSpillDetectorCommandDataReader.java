package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleOilSpillDetectorCommandDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  osdc.[Id], \r\n" +
            "  osdc.[RowVersion], \r\n" +
            "  osdc.[OilSpillDetector], \r\n" +
            "  osdc.[Timestamp], \r\n" +
            "  osdc.[DeviceCommandSourceType], \r\n" +
            "  osdc.[DeviceCommandSourceId], \r\n" +
            "  osdc.[Reply] \r\n" +
            "FROM [OilSpillDetectorCommandView] osdc \r\n";

    public final static String BaseViewName = "OilSpillDetectorCommandView";
    public final static String ViewAliasName = "osdc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int OILSPILLDETECTOR_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int DEVICECOMMANDSOURCETYPE_FIELD_ID = 5;
    public final static int DEVICECOMMANDSOURCEID_FIELD_ID = 6;
    public final static int REPLY_FIELD_ID = 7;

    public SimpleOilSpillDetectorCommandDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getOilSpillDetector() throws SQLException {
        return getGuid( OILSPILLDETECTOR_FIELD_ID );
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
        destination.writeInt32( Kind.OilSpillDetectorCommand );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getOilSpillDetector( ) );
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

    public OilSpillDetectorCommandObject getDataObject( ) throws SQLException {
            return new OilSpillDetectorCommandObject( ObjectState.Stored, getId( ), getRowVersion( ), getOilSpillDetector( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ) );
    }

}
