package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimplePolygonZoneDataReader extends SimpleZoneDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  pz.[Id], \r\n" +
            "  pz.[EntityType], \r\n" +
            "  pz.[RowVersion], \r\n" +
            "  pz.[Name], \r\n" +
            "  pz.[Longitude], \r\n" +
            "  pz.[Latitude], \r\n" +
            "  pz.[AlarmType], \r\n" +
            "  pz.[AlarmTime], \r\n" +
            "  pz.[RadarTrackMinimumLifetime], \r\n" +
            "  pz.[Speed], \r\n" +
            "  pz.[StrokeColor], \r\n" +
            "  pz.[FillColor], \r\n" +
            "  pz.[Polygon] \r\n" +
            "FROM [PolygonZoneView] pz \r\n";

    public final static String BaseViewName = "PolygonZoneView";
    public final static String ViewAliasName = "pz";

    public final static int POLYGON_FIELD_ID = 13;

    public SimplePolygonZoneDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final byte[] getPolygon() throws SQLException {
        return getBinary( POLYGON_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeUInt8Array( getPolygon( ) );
    }

    @Override
    public PolygonZoneObject GetDataObject( ) throws SQLException {
        return new PolygonZoneObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ), getLongitude( ), getLatitude( ), getAlarmType( ), getAlarmTime( ), getRadarTrackMinimumLifetime( ), getSpeed( ), getStrokeColor( ), getFillColor( ), getPolygon( ) );
    }

}
