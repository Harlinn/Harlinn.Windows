package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGeoPosition3DTimeseriesValueDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gp3dv.[Id], \r\n" +
            "  gp3dv.[RowVersion], \r\n" +
            "  gp3dv.[Timeseries], \r\n" +
            "  gp3dv.[Timestamp], \r\n" +
            "  gp3dv.[Latitude], \r\n" +
            "  gp3dv.[Longitude], \r\n" +
            "  gp3dv.[Altitude] \r\n" +
            "FROM [GeoPosition3DTimeseriesValueView] gp3dv \r\n";

    public final static String BaseViewName = "GeoPosition3DTimeseriesValueView";
    public final static String ViewAliasName = "gp3dv";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int TIMESERIES_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int LATITUDE_FIELD_ID = 5;
    public final static int LONGITUDE_FIELD_ID = 6;
    public final static int ALTITUDE_FIELD_ID = 7;

    public SimpleGeoPosition3DTimeseriesValueDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getTimeseries() throws SQLException {
        return getGuid( TIMESERIES_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final Double getLatitude() throws SQLException {
        return getNullableDouble( LATITUDE_FIELD_ID );
    }

    public final Double getLongitude() throws SQLException {
        return getNullableDouble( LONGITUDE_FIELD_ID );
    }

    public final Double getAltitude() throws SQLException {
        return getNullableDouble( ALTITUDE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.GeoPosition3DTimeseriesValue );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getTimeseries( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeNullableDouble( getLatitude( ) );
        destination.writeNullableDouble( getLongitude( ) );
        destination.writeNullableDouble( getAltitude( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public GeoPosition3DTimeseriesValueObject getDataObject( ) throws SQLException {
            return new GeoPosition3DTimeseriesValueObject( ObjectState.Stored, getId( ), getRowVersion( ), getTimeseries( ), getTimestamp( ), getLatitude( ), getLongitude( ), getAltitude( ) );
    }

}
