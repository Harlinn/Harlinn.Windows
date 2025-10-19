package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleWeatherStationDeviceDataReader extends SimpleDeviceDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  wsd.[Id], \r\n" +
            "  wsd.[EntityType], \r\n" +
            "  wsd.[RowVersion], \r\n" +
            "  wsd.[Host], \r\n" +
            "  wsd.[Name], \r\n" +
            "  wsd.[Description], \r\n" +
            "  wsd.[EnabledTimeseries], \r\n" +
            "  wsd.[BarometricPressureTimeseries], \r\n" +
            "  wsd.[AirTemperatureTimeseries], \r\n" +
            "  wsd.[WaterTemperatureTimeseries], \r\n" +
            "  wsd.[RelativeHumidityTimeseries], \r\n" +
            "  wsd.[AbsoluteHumidityTimeseries], \r\n" +
            "  wsd.[DewPointTimeseries], \r\n" +
            "  wsd.[WindDirectionTimeseries], \r\n" +
            "  wsd.[WindSpeedTimeseries], \r\n" +
            "  wsd.[Gyro] \r\n" +
            "FROM [WeatherStationDeviceView] wsd \r\n";

    public final static String BaseViewName = "WeatherStationDeviceView";
    public final static String ViewAliasName = "wsd";

    public final static int BAROMETRICPRESSURETIMESERIES_FIELD_ID = 8;
    public final static int AIRTEMPERATURETIMESERIES_FIELD_ID = 9;
    public final static int WATERTEMPERATURETIMESERIES_FIELD_ID = 10;
    public final static int RELATIVEHUMIDITYTIMESERIES_FIELD_ID = 11;
    public final static int ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID = 12;
    public final static int DEWPOINTTIMESERIES_FIELD_ID = 13;
    public final static int WINDDIRECTIONTIMESERIES_FIELD_ID = 14;
    public final static int WINDSPEEDTIMESERIES_FIELD_ID = 15;
    public final static int GYRO_FIELD_ID = 16;

    public SimpleWeatherStationDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getBarometricPressureTimeseries() throws SQLException {
        return getNullableGuid( BAROMETRICPRESSURETIMESERIES_FIELD_ID );
    }

    public final Guid getAirTemperatureTimeseries() throws SQLException {
        return getNullableGuid( AIRTEMPERATURETIMESERIES_FIELD_ID );
    }

    public final Guid getWaterTemperatureTimeseries() throws SQLException {
        return getNullableGuid( WATERTEMPERATURETIMESERIES_FIELD_ID );
    }

    public final Guid getRelativeHumidityTimeseries() throws SQLException {
        return getNullableGuid( RELATIVEHUMIDITYTIMESERIES_FIELD_ID );
    }

    public final Guid getAbsoluteHumidityTimeseries() throws SQLException {
        return getNullableGuid( ABSOLUTEHUMIDITYTIMESERIES_FIELD_ID );
    }

    public final Guid getDewPointTimeseries() throws SQLException {
        return getNullableGuid( DEWPOINTTIMESERIES_FIELD_ID );
    }

    public final Guid getWindDirectionTimeseries() throws SQLException {
        return getNullableGuid( WINDDIRECTIONTIMESERIES_FIELD_ID );
    }

    public final Guid getWindSpeedTimeseries() throws SQLException {
        return getNullableGuid( WINDSPEEDTIMESERIES_FIELD_ID );
    }

    public final Guid getGyro() throws SQLException {
        return getNullableGuid( GYRO_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getBarometricPressureTimeseries( ) );
        destination.writeNullableGuid( getAirTemperatureTimeseries( ) );
        destination.writeNullableGuid( getWaterTemperatureTimeseries( ) );
        destination.writeNullableGuid( getRelativeHumidityTimeseries( ) );
        destination.writeNullableGuid( getAbsoluteHumidityTimeseries( ) );
        destination.writeNullableGuid( getDewPointTimeseries( ) );
        destination.writeNullableGuid( getWindDirectionTimeseries( ) );
        destination.writeNullableGuid( getWindSpeedTimeseries( ) );
        destination.writeNullableGuid( getGyro( ) );
    }

    @Override
    public WeatherStationDeviceObject getDataObject( ) throws SQLException {
        return new WeatherStationDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ), getBarometricPressureTimeseries( ), getAirTemperatureTimeseries( ), getWaterTemperatureTimeseries( ), getRelativeHumidityTimeseries( ), getAbsoluteHumidityTimeseries( ), getDewPointTimeseries( ), getWindDirectionTimeseries( ), getWindSpeedTimeseries( ), getGyro( ) );
    }

}
