package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBookmarkDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  b.[Id], \r\n" +
            "  b.[RowVersion], \r\n" +
            "  b.[View], \r\n" +
            "  b.[Name], \r\n" +
            "  b.[Timestamp], \r\n" +
            "  b.[Latitude], \r\n" +
            "  b.[Longitude], \r\n" +
            "  b.[ZoomLevel] \r\n" +
            "FROM [BookmarkView] b \r\n";

    public final static String BaseViewName = "BookmarkView";
    public final static String ViewAliasName = "b";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int VIEW_FIELD_ID = 3;
    public final static int NAME_FIELD_ID = 4;
    public final static int TIMESTAMP_FIELD_ID = 5;
    public final static int LATITUDE_FIELD_ID = 6;
    public final static int LONGITUDE_FIELD_ID = 7;
    public final static int ZOOMLEVEL_FIELD_ID = 8;

    public SimpleBookmarkDataReader( ResultSet resultSet ) {
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

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getNullableDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getZoomLevel() throws SQLException {
        return getDouble( ZOOMLEVEL_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.Bookmark );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getView( ) );
        destination.writeStringUtf8( getName( ) );
        destination.writeNullableDateTime( getTimestamp( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getZoomLevel( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
