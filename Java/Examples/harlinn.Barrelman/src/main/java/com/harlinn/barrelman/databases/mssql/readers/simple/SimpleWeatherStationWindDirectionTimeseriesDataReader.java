package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleWeatherStationWindDirectionTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  wswdt.[Id], \r\n" +
            "  wswdt.[EntityType], \r\n" +
            "  wswdt.[RowVersion], \r\n" +
            "  wswdt.[Catalog], \r\n" +
            "  wswdt.[Name], \r\n" +
            "  wswdt.[MaxRetention], \r\n" +
            "  wswdt.[WeatherStation] \r\n" +
            "FROM [WeatherStationWindDirectionTimeseriesView] wswdt \r\n";

    public final static String BaseViewName = "WeatherStationWindDirectionTimeseriesView";
    public final static String ViewAliasName = "wswdt";

    public final static int WEATHERSTATION_FIELD_ID = 7;

    public SimpleWeatherStationWindDirectionTimeseriesDataReader( ResultSet resultSet ) {
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
