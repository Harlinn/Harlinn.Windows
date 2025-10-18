package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTrackValue3DDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tv3d.[Id], \r\n" +
            "  tv3d.[RowVersion], \r\n" +
            "  tv3d.[Track], \r\n" +
            "  tv3d.[Timestamp], \r\n" +
            "  tv3d.[Flags], \r\n" +
            "  tv3d.[Status], \r\n" +
            "  tv3d.[Latitude], \r\n" +
            "  tv3d.[Longitude], \r\n" +
            "  tv3d.[Altitude], \r\n" +
            "  tv3d.[Speed], \r\n" +
            "  tv3d.[Course], \r\n" +
            "  tv3d.[RateOfClimb] \r\n" +
            "FROM [TrackValue3DView] tv3d \r\n";

    public final static String BaseViewName = "TrackValue3DView";
    public final static String ViewAliasName = "tv3d";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int TRACK_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int FLAGS_FIELD_ID = 5;
    public final static int STATUS_FIELD_ID = 6;
    public final static int LATITUDE_FIELD_ID = 7;
    public final static int LONGITUDE_FIELD_ID = 8;
    public final static int ALTITUDE_FIELD_ID = 9;
    public final static int SPEED_FIELD_ID = 10;
    public final static int COURSE_FIELD_ID = 11;
    public final static int RATEOFCLIMB_FIELD_ID = 12;

    public SimpleTrackValue3DDataReader( ResultSet resultSet ) {
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
        return getUInt32( STATUS_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getAltitude() throws SQLException {
        return getDouble( ALTITUDE_FIELD_ID );
    }

    public final double getSpeed() throws SQLException {
        return getDouble( SPEED_FIELD_ID );
    }

    public final double getCourse() throws SQLException {
        return getDouble( COURSE_FIELD_ID );
    }

    public final double getRateOfClimb() throws SQLException {
        return getDouble( RATEOFCLIMB_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.TrackValue3D );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getTrack( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeInt32( getFlags( ) );
        destination.writeUInt32( getStatus( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getAltitude( ) );
        destination.writeDouble( getSpeed( ) );
        destination.writeDouble( getCourse( ) );
        destination.writeDouble( getRateOfClimb( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public TrackValue3DObject GetDataObject( ) throws SQLException {
            return new TrackValue3DObject( ObjectState.Stored, getId( ), getRowVersion( ), getTrack( ), getTimestamp( ), getFlags( ), getStatus( ), getLatitude( ), getLongitude( ), getAltitude( ), getSpeed( ), getCourse( ), getRateOfClimb( ) );
    }

}
