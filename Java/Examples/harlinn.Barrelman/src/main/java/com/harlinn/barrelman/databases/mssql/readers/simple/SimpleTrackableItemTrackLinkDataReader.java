package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTrackableItemTrackLinkDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  titl.[Id], \r\n" +
            "  titl.[RowVersion], \r\n" +
            "  titl.[Item], \r\n" +
            "  titl.[Track], \r\n" +
            "  titl.[Start], \r\n" +
            "  titl.[End] \r\n" +
            "FROM [TrackableItemTrackLinkView] titl \r\n";

    public final static String BaseViewName = "TrackableItemTrackLinkView";
    public final static String ViewAliasName = "titl";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int ITEM_FIELD_ID = 3;
    public final static int TRACK_FIELD_ID = 4;
    public final static int START_FIELD_ID = 5;
    public final static int END_FIELD_ID = 6;

    public SimpleTrackableItemTrackLinkDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getItem() throws SQLException {
        return getGuid( ITEM_FIELD_ID );
    }

    public final Guid getTrack() throws SQLException {
        return getGuid( TRACK_FIELD_ID );
    }

    public final DateTime getStart() throws SQLException {
        return getDateTimeFromLong( START_FIELD_ID );
    }

    public final DateTime getEnd() throws SQLException {
        return getNullableDateTimeFromLong( END_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.TrackableItemTrackLink );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getItem( ) );
        destination.writeGuid( getTrack( ) );
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
