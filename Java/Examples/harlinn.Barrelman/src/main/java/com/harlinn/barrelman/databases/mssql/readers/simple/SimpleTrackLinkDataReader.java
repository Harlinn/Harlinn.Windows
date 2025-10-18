package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTrackLinkDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tl.[Id], \r\n" +
            "  tl.[RowVersion], \r\n" +
            "  tl.[Primary], \r\n" +
            "  tl.[Secondary], \r\n" +
            "  tl.[Start], \r\n" +
            "  tl.[End] \r\n" +
            "FROM [TrackLinkView] tl \r\n";

    public final static String BaseViewName = "TrackLinkView";
    public final static String ViewAliasName = "tl";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int PRIMARY_FIELD_ID = 3;
    public final static int SECONDARY_FIELD_ID = 4;
    public final static int START_FIELD_ID = 5;
    public final static int END_FIELD_ID = 6;

    public SimpleTrackLinkDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getPrimary() throws SQLException {
        return getGuid( PRIMARY_FIELD_ID );
    }

    public final Guid getSecondary() throws SQLException {
        return getGuid( SECONDARY_FIELD_ID );
    }

    public final DateTime getStart() throws SQLException {
        return getDateTimeFromLong( START_FIELD_ID );
    }

    public final DateTime getEnd() throws SQLException {
        return getNullableDateTimeFromLong( END_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.TrackLink );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getPrimary( ) );
        destination.writeGuid( getSecondary( ) );
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

    public TrackLinkObject GetDataObject( ) throws SQLException {
            return new TrackLinkObject( ObjectState.Stored, getId( ), getRowVersion( ), getPrimary( ), getSecondary( ), getStart( ), getEnd( ) );
    }

}
