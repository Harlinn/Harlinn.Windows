package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTrackValueDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tv.[Id], \r\n" +
            "  tv.[RowVersion], \r\n" +
            "  tv.[Track], \r\n" +
            "  tv.[Timestamp], \r\n" +
            "  tv.[Flags], \r\n" +
            "  tv.[Status], \r\n" +
            "  tv.[Latitude], \r\n" +
            "  tv.[Longitude], \r\n" +
            "  tv.[Speed], \r\n" +
            "  tv.[Course], \r\n" +
            "  tv.[Heading] \r\n" +
            "FROM [TrackValueView] tv \r\n";

    public final static String BaseViewName = "TrackValueView";
    public final static String ViewAliasName = "tv";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int TRACK_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int FLAGS_FIELD_ID = 5;
    public final static int STATUS_FIELD_ID = 6;
    public final static int LATITUDE_FIELD_ID = 7;
    public final static int LONGITUDE_FIELD_ID = 8;
    public final static int SPEED_FIELD_ID = 9;
    public final static int COURSE_FIELD_ID = 10;
    public final static int HEADING_FIELD_ID = 11;

    public SimpleTrackValueDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getTrack() throws SQLException {
        return getGuid( TRACK_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final int getFlags() throws SQLException {
        return getInt32( FLAGS_FIELD_ID );
    }

    public final int getStatus() throws SQLException {
        return getInt32( STATUS_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getSpeed() throws SQLException {
        return getDouble( SPEED_FIELD_ID );
    }

    public final double getCourse() throws SQLException {
        return getDouble( COURSE_FIELD_ID );
    }

    public final double getHeading() throws SQLException {
        return getDouble( HEADING_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.TrackValue );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getTrack( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeInt32( getFlags( ) );
        destination.writeInt32( getStatus( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getSpeed( ) );
        destination.writeDouble( getCourse( ) );
        destination.writeDouble( getHeading( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public TrackValueObject GetDataObject( ) throws SQLException {
            return new TrackValueObject( ObjectState.Stored, getId( ), getRowVersion( ), getTrack( ), getTimestamp( ), getFlags( ), getStatus( ), getLatitude( ), getLongitude( ), getSpeed( ), getCourse( ), getHeading( ) );
    }

}
