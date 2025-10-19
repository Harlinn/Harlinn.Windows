package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleWeatherStationConfigurationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  wsc.[Id], \r\n" +
            "  wsc.[RowVersion], \r\n" +
            "  wsc.[WeatherStation], \r\n" +
            "  wsc.[Timestamp], \r\n" +
            "  wsc.[NoDataTimeOut], \r\n" +
            "  wsc.[SendInterval], \r\n" +
            "  wsc.[Latitude], \r\n" +
            "  wsc.[Longitude], \r\n" +
            "  wsc.[GyroOffset], \r\n" +
            "  wsc.[EnableAveraging], \r\n" +
            "  wsc.[AveragingInterval] \r\n" +
            "FROM [WeatherStationConfigurationView] wsc \r\n";

    public final static String BaseViewName = "WeatherStationConfigurationView";
    public final static String ViewAliasName = "wsc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int WEATHERSTATION_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int NODATATIMEOUT_FIELD_ID = 5;
    public final static int SENDINTERVAL_FIELD_ID = 6;
    public final static int LATITUDE_FIELD_ID = 7;
    public final static int LONGITUDE_FIELD_ID = 8;
    public final static int GYROOFFSET_FIELD_ID = 9;
    public final static int ENABLEAVERAGING_FIELD_ID = 10;
    public final static int AVERAGINGINTERVAL_FIELD_ID = 11;

    public SimpleWeatherStationConfigurationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getWeatherStation() throws SQLException {
        return getGuid( WEATHERSTATION_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final TimeSpan getNoDataTimeOut() throws SQLException {
        return getTimeSpan( NODATATIMEOUT_FIELD_ID );
    }

    public final TimeSpan getSendInterval() throws SQLException {
        return getTimeSpan( SENDINTERVAL_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getGyroOffset() throws SQLException {
        return getDouble( GYROOFFSET_FIELD_ID );
    }

    public final boolean getEnableAveraging() throws SQLException {
        return getBoolean( ENABLEAVERAGING_FIELD_ID );
    }

    public final TimeSpan getAveragingInterval() throws SQLException {
        return getTimeSpan( AVERAGINGINTERVAL_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.WeatherStationConfiguration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getWeatherStation( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeTimeSpan( getNoDataTimeOut( ) );
        destination.writeTimeSpan( getSendInterval( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getGyroOffset( ) );
        destination.writeBoolean( getEnableAveraging( ) );
        destination.writeTimeSpan( getAveragingInterval( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public WeatherStationConfigurationObject getDataObject( ) throws SQLException {
            return new WeatherStationConfigurationObject( ObjectState.Stored, getId( ), getRowVersion( ), getWeatherStation( ), getTimestamp( ), getNoDataTimeOut( ), getSendInterval( ), getLatitude( ), getLongitude( ), getGyroOffset( ), getEnableAveraging( ), getAveragingInterval( ) );
    }

}
