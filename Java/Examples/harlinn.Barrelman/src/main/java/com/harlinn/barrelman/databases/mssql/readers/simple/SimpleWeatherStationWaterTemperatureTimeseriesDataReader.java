package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleWeatherStationWaterTemperatureTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  wswtt.[Id], \r\n" +
            "  wswtt.[EntityType], \r\n" +
            "  wswtt.[RowVersion], \r\n" +
            "  wswtt.[Catalog], \r\n" +
            "  wswtt.[Name], \r\n" +
            "  wswtt.[MaxRetention], \r\n" +
            "  wswtt.[WeatherStation] \r\n" +
            "FROM [WeatherStationWaterTemperatureTimeseriesView] wswtt \r\n";

    public final static String BaseViewName = "WeatherStationWaterTemperatureTimeseriesView";
    public final static String ViewAliasName = "wswtt";

    public final static int WEATHERSTATION_FIELD_ID = 7;

    public SimpleWeatherStationWaterTemperatureTimeseriesDataReader( ResultSet resultSet ) {
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

}
