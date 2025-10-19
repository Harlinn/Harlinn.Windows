package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraCommandGeoMoveDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ccgm.[Id], \r\n" +
            "  ccgm.[EntityType], \r\n" +
            "  ccgm.[RowVersion], \r\n" +
            "  ccgm.[Camera], \r\n" +
            "  ccgm.[Timestamp], \r\n" +
            "  ccgm.[DeviceCommandSourceType], \r\n" +
            "  ccgm.[DeviceCommandSourceId], \r\n" +
            "  ccgm.[Reply], \r\n" +
            "  ccgm.[Latitude], \r\n" +
            "  ccgm.[Longitude], \r\n" +
            "  ccgm.[Altitude], \r\n" +
            "  ccgm.[ViewportWidth], \r\n" +
            "  ccgm.[ViewportHeight] \r\n" +
            "FROM [CameraCommandGeoMoveView] ccgm \r\n";

    public final static String BaseViewName = "CameraCommandGeoMoveView";
    public final static String ViewAliasName = "ccgm";

    public final static int LATITUDE_FIELD_ID = 9;
    public final static int LONGITUDE_FIELD_ID = 10;
    public final static int ALTITUDE_FIELD_ID = 11;
    public final static int VIEWPORTWIDTH_FIELD_ID = 12;
    public final static int VIEWPORTHEIGHT_FIELD_ID = 13;

    public SimpleCameraCommandGeoMoveDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final Double getAltitude() throws SQLException {
        return getNullableDouble( ALTITUDE_FIELD_ID );
    }

    public final Double getViewportWidth() throws SQLException {
        return getNullableDouble( VIEWPORTWIDTH_FIELD_ID );
    }

    public final Double getViewportHeight() throws SQLException {
        return getNullableDouble( VIEWPORTHEIGHT_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeNullableDouble( getAltitude( ) );
        destination.writeNullableDouble( getViewportWidth( ) );
        destination.writeNullableDouble( getViewportHeight( ) );
    }

    @Override
    public CameraCommandGeoMoveObject getDataObject( ) throws SQLException {
        return new CameraCommandGeoMoveObject( ObjectState.Stored, getId( ), getRowVersion( ), getCamera( ), getTimestamp( ), getDeviceCommandSourceType( ), getDeviceCommandSourceId( ), getReply( ), getLatitude( ), getLongitude( ), getAltitude( ), getViewportWidth( ), getViewportHeight( ) );
    }

}
