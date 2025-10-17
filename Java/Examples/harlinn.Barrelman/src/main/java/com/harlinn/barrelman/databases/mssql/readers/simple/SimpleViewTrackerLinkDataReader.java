package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleViewTrackerLinkDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  vtl.[Id], \r\n" +
            "  vtl.[RowVersion], \r\n" +
            "  vtl.[View], \r\n" +
            "  vtl.[Tracker], \r\n" +
            "  vtl.[Start], \r\n" +
            "  vtl.[End] \r\n" +
            "FROM [ViewTrackerLinkView] vtl \r\n";

    public final static String BaseViewName = "ViewTrackerLinkView";
    public final static String ViewAliasName = "vtl";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int VIEW_FIELD_ID = 3;
    public final static int TRACKER_FIELD_ID = 4;
    public final static int START_FIELD_ID = 5;
    public final static int END_FIELD_ID = 6;

    public SimpleViewTrackerLinkDataReader( ResultSet resultSet ) {
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

    public final Guid getTracker() throws SQLException {
        return getGuid( TRACKER_FIELD_ID );
    }

    public final DateTime getStart() throws SQLException {
        return getDateTimeFromLong( START_FIELD_ID );
    }

    public final DateTime getEnd() throws SQLException {
        return getNullableDateTimeFromLong( END_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.ViewTrackerLink );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getView( ) );
        destination.writeGuid( getTracker( ) );
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
