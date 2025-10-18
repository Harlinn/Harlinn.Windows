package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleProcessTrackValueResultDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ptvr.[Id], \r\n" +
            "  ptvr.[RowVersion], \r\n" +
            "  ptvr.[CreatedNewTrack], \r\n" +
            "  ptvr.[TrackId] \r\n" +
            "FROM [ProcessTrackValueResultView] ptvr \r\n";

    public final static String BaseViewName = "ProcessTrackValueResultView";
    public final static String ViewAliasName = "ptvr";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int CREATEDNEWTRACK_FIELD_ID = 3;
    public final static int TRACKID_FIELD_ID = 4;

    public SimpleProcessTrackValueResultDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final boolean getCreatedNewTrack() throws SQLException {
        return getBoolean( CREATEDNEWTRACK_FIELD_ID );
    }

    public final Guid getTrackId() throws SQLException {
        return getGuid( TRACKID_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.ProcessTrackValueResult );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeBoolean( getCreatedNewTrack( ) );
        destination.writeGuid( getTrackId( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public ProcessTrackValueResultObject GetDataObject( ) throws SQLException {
            return new ProcessTrackValueResultObject( ObjectState.Stored, getId( ), getRowVersion( ), getCreatedNewTrack( ), getTrackId( ) );
    }

}
