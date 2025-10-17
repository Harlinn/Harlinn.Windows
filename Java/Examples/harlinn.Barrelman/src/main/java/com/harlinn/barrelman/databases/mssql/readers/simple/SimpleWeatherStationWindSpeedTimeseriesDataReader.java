package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleWeatherStationWindSpeedTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  wswst.[Id], \r\n" +
            "  wswst.[EntityType], \r\n" +
            "  wswst.[RowVersion], \r\n" +
            "  wswst.[Catalog], \r\n" +
            "  wswst.[Name], \r\n" +
            "  wswst.[MaxRetention], \r\n" +
            "  wswst.[WeatherStation] \r\n" +
            "FROM [WeatherStationWindSpeedTimeseriesView] wswst \r\n";

    public final static String BaseViewName = "WeatherStationWindSpeedTimeseriesView";
    public final static String ViewAliasName = "wswst";

    public final static int WEATHERSTATION_FIELD_ID = 7;

    public SimpleWeatherStationWindSpeedTimeseriesDataReader( ResultSet resultSet ) {
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
