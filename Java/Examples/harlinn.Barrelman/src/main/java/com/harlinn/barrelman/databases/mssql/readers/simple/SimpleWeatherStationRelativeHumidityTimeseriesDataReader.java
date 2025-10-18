package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleWeatherStationRelativeHumidityTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  wsrht.[Id], \r\n" +
            "  wsrht.[EntityType], \r\n" +
            "  wsrht.[RowVersion], \r\n" +
            "  wsrht.[Catalog], \r\n" +
            "  wsrht.[Name], \r\n" +
            "  wsrht.[MaxRetention], \r\n" +
            "  wsrht.[WeatherStation] \r\n" +
            "FROM [WeatherStationRelativeHumidityTimeseriesView] wsrht \r\n";

    public final static String BaseViewName = "WeatherStationRelativeHumidityTimeseriesView";
    public final static String ViewAliasName = "wsrht";

    public final static int WEATHERSTATION_FIELD_ID = 7;

    public SimpleWeatherStationRelativeHumidityTimeseriesDataReader( ResultSet resultSet ) {
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
    public WeatherStationRelativeHumidityTimeseriesObject GetDataObject( ) throws SQLException {
        return new WeatherStationRelativeHumidityTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getWeatherStation( ) );
    }

}
