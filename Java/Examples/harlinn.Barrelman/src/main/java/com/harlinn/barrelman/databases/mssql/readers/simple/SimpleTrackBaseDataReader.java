package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimpleTrackBaseDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tb.[Id], \r\n" +
            "  tb.[EntityType], \r\n" +
            "  tb.[RowVersion], \r\n" +
            "  tb.[Tracker], \r\n" +
            "  tb.[TrackNumber], \r\n" +
            "  tb.[Timestamp] \r\n" +
            "FROM [TrackBaseView] tb \r\n";

    public final static String BaseViewName = "TrackBaseView";
    public final static String ViewAliasName = "tb";

    public final static int ID_FIELD_ID = 1;
    public final static int ENTITYTYPE_FIELD_ID = 2;
    public final static int ROWVERSION_FIELD_ID = 3;
    public final static int TRACKER_FIELD_ID = 4;
    public final static int TRACKNUMBER_FIELD_ID = 5;
    public final static int TIMESTAMP_FIELD_ID = 6;

    public SimpleTrackBaseDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final int getObjectType() throws SQLException {
        return getInt32( ENTITYTYPE_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getTracker() throws SQLException {
        return getGuid( TRACKER_FIELD_ID );
    }

    public final long getTrackNumber() throws SQLException {
        return getInt64( TRACKNUMBER_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.TrackBase );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getTracker( ) );
        destination.writeInt64( getTrackNumber( ) );
        destination.writeDateTime( getTimestamp( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public abstract TrackBaseObject GetDataObject( ) throws SQLException;

}
