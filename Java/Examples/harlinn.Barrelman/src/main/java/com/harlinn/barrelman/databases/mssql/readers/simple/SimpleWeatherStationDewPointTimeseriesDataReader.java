package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleWeatherStationDewPointTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  wsdpt.[Id], \r\n" +
            "  wsdpt.[EntityType], \r\n" +
            "  wsdpt.[RowVersion], \r\n" +
            "  wsdpt.[Catalog], \r\n" +
            "  wsdpt.[Name], \r\n" +
            "  wsdpt.[MaxRetention], \r\n" +
            "  wsdpt.[WeatherStation] \r\n" +
            "FROM [WeatherStationDewPointTimeseriesView] wsdpt \r\n";

    public final static String BaseViewName = "WeatherStationDewPointTimeseriesView";
    public final static String ViewAliasName = "wsdpt";

    public final static int WEATHERSTATION_FIELD_ID = 7;

    public SimpleWeatherStationDewPointTimeseriesDataReader( ResultSet resultSet ) {
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
    public WeatherStationDewPointTimeseriesObject getDataObject( ) throws SQLException {
        return new WeatherStationDewPointTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getWeatherStation( ) );
    }

}
