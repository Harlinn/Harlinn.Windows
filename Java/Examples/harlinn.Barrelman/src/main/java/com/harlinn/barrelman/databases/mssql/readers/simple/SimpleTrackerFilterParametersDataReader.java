package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTrackerFilterParametersDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tfp.[Id], \r\n" +
            "  tfp.[RowVersion], \r\n" +
            "  tfp.[Tracker], \r\n" +
            "  tfp.[Name] \r\n" +
            "FROM [TrackerFilterParametersView] tfp \r\n";

    public final static String BaseViewName = "TrackerFilterParametersView";
    public final static String ViewAliasName = "tfp";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int TRACKER_FIELD_ID = 3;
    public final static int NAME_FIELD_ID = 4;

    public SimpleTrackerFilterParametersDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getTracker() throws SQLException {
        return getGuid( TRACKER_FIELD_ID );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.TrackerFilterParameters );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getTracker( ) );
        destination.writeStringUtf8( getName( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public TrackerFilterParametersObject getDataObject( ) throws SQLException {
            return new TrackerFilterParametersObject( ObjectState.Stored, getId( ), getRowVersion( ), getTracker( ), getName( ) );
    }

}
