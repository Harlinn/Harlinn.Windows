package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCircularZoneDataReader extends SimpleZoneDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  cz.[Id], \r\n" +
            "  cz.[EntityType], \r\n" +
            "  cz.[RowVersion], \r\n" +
            "  cz.[Name], \r\n" +
            "  cz.[Longitude], \r\n" +
            "  cz.[Latitude], \r\n" +
            "  cz.[AlarmType], \r\n" +
            "  cz.[AlarmTime], \r\n" +
            "  cz.[RadarTrackMinimumLifetime], \r\n" +
            "  cz.[Speed], \r\n" +
            "  cz.[StrokeColor], \r\n" +
            "  cz.[FillColor], \r\n" +
            "  cz.[Radius] \r\n" +
            "FROM [CircularZoneView] cz \r\n";

    public final static String BaseViewName = "CircularZoneView";
    public final static String ViewAliasName = "cz";

    public final static int RADIUS_FIELD_ID = 13;

    public SimpleCircularZoneDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final double getRadius() throws SQLException {
        return getDouble( RADIUS_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeDouble( getRadius( ) );
    }

    @Override
    public CircularZoneObject GetDataObject( ) throws SQLException {
        return new CircularZoneObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ), getLongitude( ), getLatitude( ), getAlarmType( ), getAlarmTime( ), getRadarTrackMinimumLifetime( ), getSpeed( ), getStrokeColor( ), getFillColor( ), getRadius( ) );
    }

}
