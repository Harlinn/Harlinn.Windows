package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleWeatherStationAirTemperatureTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  wsatt.[Id], \r\n" +
            "  wsatt.[EntityType], \r\n" +
            "  wsatt.[RowVersion], \r\n" +
            "  wsatt.[Catalog], \r\n" +
            "  wsatt.[Name], \r\n" +
            "  wsatt.[MaxRetention], \r\n" +
            "  wsatt.[WeatherStation] \r\n" +
            "FROM [WeatherStationAirTemperatureTimeseriesView] wsatt \r\n";

    public final static String BaseViewName = "WeatherStationAirTemperatureTimeseriesView";
    public final static String ViewAliasName = "wsatt";

    public final static int WEATHERSTATION_FIELD_ID = 7;

    public SimpleWeatherStationAirTemperatureTimeseriesDataReader( ResultSet resultSet ) {
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
    public WeatherStationAirTemperatureTimeseriesObject getDataObject( ) throws SQLException {
        return new WeatherStationAirTemperatureTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getWeatherStation( ) );
    }

}
