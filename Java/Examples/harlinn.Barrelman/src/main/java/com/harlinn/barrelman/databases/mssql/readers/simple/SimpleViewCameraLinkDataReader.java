package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleViewCameraLinkDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  vcl.[Id], \r\n" +
            "  vcl.[RowVersion], \r\n" +
            "  vcl.[View], \r\n" +
            "  vcl.[Camera], \r\n" +
            "  vcl.[Start], \r\n" +
            "  vcl.[End] \r\n" +
            "FROM [ViewCameraLinkView] vcl \r\n";

    public final static String BaseViewName = "ViewCameraLinkView";
    public final static String ViewAliasName = "vcl";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int VIEW_FIELD_ID = 3;
    public final static int CAMERA_FIELD_ID = 4;
    public final static int START_FIELD_ID = 5;
    public final static int END_FIELD_ID = 6;

    public SimpleViewCameraLinkDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getView() throws SQLException {
        return getGuid( VIEW_FIELD_ID );
    }

    public final Guid getCamera() throws SQLException {
        return getGuid( CAMERA_FIELD_ID );
    }

    public final DateTime getStart() throws SQLException {
        return getDateTimeFromLong( START_FIELD_ID );
    }

    public final DateTime getEnd() throws SQLException {
        return getNullableDateTimeFromLong( END_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.ViewCameraLink );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getView( ) );
        destination.writeGuid( getCamera( ) );
        destination.writeDateTime( getStart( ) );
        destination.writeNullableDateTime( getEnd( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
