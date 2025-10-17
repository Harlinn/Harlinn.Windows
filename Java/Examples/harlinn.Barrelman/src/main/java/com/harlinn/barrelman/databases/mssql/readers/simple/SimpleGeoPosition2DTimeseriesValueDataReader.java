package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGeoPosition2DTimeseriesValueDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gp2dv.[Id], \r\n" +
            "  gp2dv.[RowVersion], \r\n" +
            "  gp2dv.[Timeseries], \r\n" +
            "  gp2dv.[Timestamp], \r\n" +
            "  gp2dv.[Latitude], \r\n" +
            "  gp2dv.[Longitude] \r\n" +
            "FROM [GeoPosition2DTimeseriesValueView] gp2dv \r\n";

    public final static String BaseViewName = "GeoPosition2DTimeseriesValueView";
    public final static String ViewAliasName = "gp2dv";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int TIMESERIES_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int LATITUDE_FIELD_ID = 5;
    public final static int LONGITUDE_FIELD_ID = 6;

    public SimpleGeoPosition2DTimeseriesValueDataReader( ResultSet resultSet ) {
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

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.GeoPosition2DTimeseriesValue );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getTimeseries( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeNullableDouble( getLatitude( ) );
        destination.writeNullableDouble( getLongitude( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
