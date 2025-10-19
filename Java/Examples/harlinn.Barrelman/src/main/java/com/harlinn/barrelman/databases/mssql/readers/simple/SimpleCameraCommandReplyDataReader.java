package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraCommandReplyDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ccr.[Id], \r\n" +
            "  ccr.[RowVersion], \r\n" +
            "  ccr.[Camera], \r\n" +
            "  ccr.[Timestamp], \r\n" +
            "  ccr.[Command], \r\n" +
            "  ccr.[Status], \r\n" +
            "  ccr.[Message], \r\n" +
            "  ccr.[PanAngle], \r\n" +
            "  ccr.[TiltAngle], \r\n" +
            "  ccr.[FocalLength] \r\n" +
            "FROM [CameraCommandReplyView] ccr \r\n";

    public final static String BaseViewName = "CameraCommandReplyView";
    public final static String ViewAliasName = "ccr";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int CAMERA_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int COMMAND_FIELD_ID = 5;
    public final static int STATUS_FIELD_ID = 6;
    public final static int MESSAGE_FIELD_ID = 7;
    public final static int PANANGLE_FIELD_ID = 8;
    public final static int TILTANGLE_FIELD_ID = 9;
    public final static int FOCALLENGTH_FIELD_ID = 10;

    public SimpleCameraCommandReplyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getCamera() throws SQLException {
        return getGuid( CAMERA_FIELD_ID );
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

    public final double getPanAngle() throws SQLException {
        return getDouble( PANANGLE_FIELD_ID );
    }

    public final double getTiltAngle() throws SQLException {
        return getDouble( TILTANGLE_FIELD_ID );
    }

    public final double getFocalLength() throws SQLException {
        return getDouble( FOCALLENGTH_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.CameraCommandReply );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getCamera( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeNullableGuid( getCommand( ) );
        destination.writeInt32( getStatus( ) );
        destination.writeStringUtf8( getMessage( ) );
        destination.writeDouble( getPanAngle( ) );
        destination.writeDouble( getTiltAngle( ) );
        destination.writeDouble( getFocalLength( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public CameraCommandReplyObject getDataObject( ) throws SQLException {
            return new CameraCommandReplyObject( ObjectState.Stored, getId( ), getRowVersion( ), getCamera( ), getTimestamp( ), getCommand( ), getStatus( ), getMessage( ), getPanAngle( ), getTiltAngle( ), getFocalLength( ) );
    }

}
