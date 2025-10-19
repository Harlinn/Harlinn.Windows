package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleZoneTrackAlarmDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  zta.[Id], \r\n" +
            "  zta.[RowVersion], \r\n" +
            "  zta.[Track], \r\n" +
            "  zta.[Zone], \r\n" +
            "  zta.[RadarTrack], \r\n" +
            "  zta.[Timestamp], \r\n" +
            "  zta.[Latitude], \r\n" +
            "  zta.[Longitude], \r\n" +
            "  zta.[Speed], \r\n" +
            "  zta.[Course], \r\n" +
            "  zta.[Heading], \r\n" +
            "  zta.[EnterLatitude], \r\n" +
            "  zta.[EnterLongitude], \r\n" +
            "  zta.[LeaveLatitude], \r\n" +
            "  zta.[LeaveLongitude] \r\n" +
            "FROM [ZoneTrackAlarmView] zta \r\n";

    public final static String BaseViewName = "ZoneTrackAlarmView";
    public final static String ViewAliasName = "zta";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int TRACK_FIELD_ID = 3;
    public final static int ZONE_FIELD_ID = 4;
    public final static int RADARTRACK_FIELD_ID = 5;
    public final static int TIMESTAMP_FIELD_ID = 6;
    public final static int LATITUDE_FIELD_ID = 7;
    public final static int LONGITUDE_FIELD_ID = 8;
    public final static int SPEED_FIELD_ID = 9;
    public final static int COURSE_FIELD_ID = 10;
    public final static int HEADING_FIELD_ID = 11;
    public final static int ENTERLATITUDE_FIELD_ID = 12;
    public final static int ENTERLONGITUDE_FIELD_ID = 13;
    public final static int LEAVELATITUDE_FIELD_ID = 14;
    public final static int LEAVELONGITUDE_FIELD_ID = 15;

    public SimpleZoneTrackAlarmDataReader( ResultSet resultSet ) {
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

    public final Guid getZone() throws SQLException {
        return getGuid( ZONE_FIELD_ID );
    }

    public final Guid getRadarTrack() throws SQLException {
        return getNullableGuid( RADARTRACK_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
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

    public final Double getCourse() throws SQLException {
        return getNullableDouble( COURSE_FIELD_ID );
    }

    public final Double getHeading() throws SQLException {
        return getNullableDouble( HEADING_FIELD_ID );
    }

    public final double getEnterLatitude() throws SQLException {
        return getDouble( ENTERLATITUDE_FIELD_ID );
    }

    public final double getEnterLongitude() throws SQLException {
        return getDouble( ENTERLONGITUDE_FIELD_ID );
    }

    public final Double getLeaveLatitude() throws SQLException {
        return getNullableDouble( LEAVELATITUDE_FIELD_ID );
    }

    public final Double getLeaveLongitude() throws SQLException {
        return getNullableDouble( LEAVELONGITUDE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.ZoneTrackAlarm );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getTrack( ) );
        destination.writeGuid( getZone( ) );
        destination.writeNullableGuid( getRadarTrack( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getSpeed( ) );
        destination.writeNullableDouble( getCourse( ) );
        destination.writeNullableDouble( getHeading( ) );
        destination.writeDouble( getEnterLatitude( ) );
        destination.writeDouble( getEnterLongitude( ) );
        destination.writeNullableDouble( getLeaveLatitude( ) );
        destination.writeNullableDouble( getLeaveLongitude( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public ZoneTrackAlarmObject getDataObject( ) throws SQLException {
            return new ZoneTrackAlarmObject( ObjectState.Stored, getId( ), getRowVersion( ), getTrack( ), getZone( ), getRadarTrack( ), getTimestamp( ), getLatitude( ), getLongitude( ), getSpeed( ), getCourse( ), getHeading( ), getEnterLatitude( ), getEnterLongitude( ), getLeaveLatitude( ), getLeaveLongitude( ) );
    }

}
