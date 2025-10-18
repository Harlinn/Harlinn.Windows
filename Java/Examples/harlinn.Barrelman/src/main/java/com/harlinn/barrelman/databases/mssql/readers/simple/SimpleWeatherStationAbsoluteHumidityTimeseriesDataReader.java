package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleWeatherStationAbsoluteHumidityTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  wsaht.[Id], \r\n" +
            "  wsaht.[EntityType], \r\n" +
            "  wsaht.[RowVersion], \r\n" +
            "  wsaht.[Catalog], \r\n" +
            "  wsaht.[Name], \r\n" +
            "  wsaht.[MaxRetention], \r\n" +
            "  wsaht.[WeatherStation] \r\n" +
            "FROM [WeatherStationAbsoluteHumidityTimeseriesView] wsaht \r\n";

    public final static String BaseViewName = "WeatherStationAbsoluteHumidityTimeseriesView";
    public final static String ViewAliasName = "wsaht";

    public final static int WEATHERSTATION_FIELD_ID = 7;

    public SimpleWeatherStationAbsoluteHumidityTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getWeatherStation() throws SQLException {
        return getNullableGuid( WEATHERSTATION_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getWeatherStation( ) );
    }

    @Override
    public WeatherStationAbsoluteHumidityTimeseriesObject GetDataObject( ) throws SQLException {
        return new WeatherStationAbsoluteHumidityTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getWeatherStation( ) );
    }

}
