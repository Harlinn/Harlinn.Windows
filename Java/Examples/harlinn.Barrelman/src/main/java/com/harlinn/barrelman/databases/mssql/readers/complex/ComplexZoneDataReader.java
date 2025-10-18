package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexZoneDataReader extends ResultSetWrapper {

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
            "  z.[FillColor], \r\n" +
            "  cz.[Radius], \r\n" +
            "  pz.[Polygon] \r\n" +
            "FROM [ZoneView] z \r\n" +
            "  LEFT JOIN [CircularZone] cz ON(z.[Id] = cz.[Id] ) \r\n" +
            "  LEFT JOIN [PolygonZone] pz ON(z.[Id] = pz.[Id] ) \r\n";

    public final static String BaseViewName = "ZoneView";
    public final static String ViewAliasName = "z";

    public final static int Z_ID_FIELD_ID = 1;
    public final static int Z_KIND_FIELD_ID = 2;
    public final static int Z_ROWVERSION_FIELD_ID = 3;
    public final static int Z_NAME_FIELD_ID = 4;
    public final static int Z_LONGITUDE_FIELD_ID = 5;
    public final static int Z_LATITUDE_FIELD_ID = 6;
    public final static int Z_ALARMTYPE_FIELD_ID = 7;
    public final static int Z_ALARMTIME_FIELD_ID = 8;
    public final static int Z_RADARTRACKMINIMUMLIFETIME_FIELD_ID = 9;
    public final static int Z_SPEED_FIELD_ID = 10;
    public final static int Z_STROKECOLOR_FIELD_ID = 11;
    public final static int Z_FILLCOLOR_FIELD_ID = 12;
    public final static int CZ_RADIUS_FIELD_ID = 13;
    public final static int PZ_POLYGON_FIELD_ID = 14;

    public ComplexZoneDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( Z_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( Z_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( Z_ROWVERSION_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( Z_NAME_FIELD_ID );
    }

    public double getLongitude( ) throws SQLException {
        return getDouble( Z_LONGITUDE_FIELD_ID );
    }

    public double getLatitude( ) throws SQLException {
        return getDouble( Z_LATITUDE_FIELD_ID );
    }

    public int getAlarmType( ) throws SQLException {
        return getInt32( Z_ALARMTYPE_FIELD_ID );
    }

    public TimeSpan getAlarmTime( ) throws SQLException {
        return getTimeSpan( Z_ALARMTIME_FIELD_ID );
    }

    public TimeSpan getRadarTrackMinimumLifetime( ) throws SQLException {
        return getTimeSpan( Z_RADARTRACKMINIMUMLIFETIME_FIELD_ID );
    }

    public double getSpeed( ) throws SQLException {
        return getDouble( Z_SPEED_FIELD_ID );
    }

    public int getStrokeColor( ) throws SQLException {
        return getUInt32( Z_STROKECOLOR_FIELD_ID );
    }

    public int getFillColor( ) throws SQLException {
        return getUInt32( Z_FILLCOLOR_FIELD_ID );
    }

    public double getCircularZoneRadius( ) throws SQLException {
        return getDouble( CZ_RADIUS_FIELD_ID );
    }

    public byte[] getPolygonZonePolygon( ) throws SQLException {
        return getBinary( PZ_POLYGON_FIELD_ID );
    }

}

