package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimpleZoneDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  z.[Id], \r\n" +
            "  z.[EntityType], \r\n" +
            "  z.[RowVersion], \r\n" +
            "  z.[Name], \r\n" +
            "  z.[Longitude], \r\n" +
            "  z.[Latitude], \r\n" +
            "  z.[AlarmType], \r\n" +
            "  z.[AlarmTime], \r\n" +
            "  z.[RadarTrackMinimumLifetime], \r\n" +
            "  z.[Speed], \r\n" +
            "  z.[StrokeColor], \r\n" +
            "  z.[FillColor] \r\n" +
            "FROM [ZoneView] z \r\n";

    public final static String BaseViewName = "ZoneView";
    public final static String ViewAliasName = "z";

    public final static int ID_FIELD_ID = 1;
    public final static int ENTITYTYPE_FIELD_ID = 2;
    public final static int ROWVERSION_FIELD_ID = 3;
    public final static int NAME_FIELD_ID = 4;
    public final static int LONGITUDE_FIELD_ID = 5;
    public final static int LATITUDE_FIELD_ID = 6;
    public final static int ALARMTYPE_FIELD_ID = 7;
    public final static int ALARMTIME_FIELD_ID = 8;
    public final static int RADARTRACKMINIMUMLIFETIME_FIELD_ID = 9;
    public final static int SPEED_FIELD_ID = 10;
    public final static int STROKECOLOR_FIELD_ID = 11;
    public final static int FILLCOLOR_FIELD_ID = 12;

    public SimpleZoneDataReader( ResultSet resultSet ) {
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

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final int getAlarmType() throws SQLException {
        return getInt32( ALARMTYPE_FIELD_ID );
    }

    public final TimeSpan getAlarmTime() throws SQLException {
        return getTimeSpan( ALARMTIME_FIELD_ID );
    }

    public final TimeSpan getRadarTrackMinimumLifetime() throws SQLException {
        return getTimeSpan( RADARTRACKMINIMUMLIFETIME_FIELD_ID );
    }

    public final double getSpeed() throws SQLException {
        return getDouble( SPEED_FIELD_ID );
    }

    public final int getStrokeColor() throws SQLException {
        return getUInt32( STROKECOLOR_FIELD_ID );
    }

    public final int getFillColor() throws SQLException {
        return getUInt32( FILLCOLOR_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.Zone );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeStringUtf8( getName( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeInt32( getAlarmType( ) );
        destination.writeTimeSpan( getAlarmTime( ) );
        destination.writeTimeSpan( getRadarTrackMinimumLifetime( ) );
        destination.writeDouble( getSpeed( ) );
        destination.writeUInt32( getStrokeColor( ) );
        destination.writeUInt32( getFillColor( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public abstract ZoneObject getDataObject( ) throws SQLException;

}
