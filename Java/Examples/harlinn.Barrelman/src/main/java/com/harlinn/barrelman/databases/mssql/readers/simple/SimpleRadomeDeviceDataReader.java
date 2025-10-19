package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadomeDeviceDataReader extends SimpleDeviceDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rdo.[Id], \r\n" +
            "  rdo.[EntityType], \r\n" +
            "  rdo.[RowVersion], \r\n" +
            "  rdo.[Host], \r\n" +
            "  rdo.[Name], \r\n" +
            "  rdo.[Description], \r\n" +
            "  rdo.[EnabledTimeseries], \r\n" +
            "  rdo.[Radar], \r\n" +
            "  rdo.[PressureTimeseries], \r\n" +
            "  rdo.[TemperatureTimeseries], \r\n" +
            "  rdo.[DewPointTimeseries], \r\n" +
            "  rdo.[StatusTimeseries] \r\n" +
            "FROM [RadomeDeviceView] rdo \r\n";

    public final static String BaseViewName = "RadomeDeviceView";
    public final static String ViewAliasName = "rdo";

    public final static int RADAR_FIELD_ID = 8;
    public final static int PRESSURETIMESERIES_FIELD_ID = 9;
    public final static int TEMPERATURETIMESERIES_FIELD_ID = 10;
    public final static int DEWPOINTTIMESERIES_FIELD_ID = 11;
    public final static int STATUSTIMESERIES_FIELD_ID = 12;

    public SimpleRadomeDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getRadar() throws SQLException {
        return getNullableGuid( RADAR_FIELD_ID );
    }

    public final Guid getPressureTimeseries() throws SQLException {
        return getNullableGuid( PRESSURETIMESERIES_FIELD_ID );
    }

    public final Guid getTemperatureTimeseries() throws SQLException {
        return getNullableGuid( TEMPERATURETIMESERIES_FIELD_ID );
    }

    public final Guid getDewPointTimeseries() throws SQLException {
        return getNullableGuid( DEWPOINTTIMESERIES_FIELD_ID );
    }

    public final Guid getStatusTimeseries() throws SQLException {
        return getNullableGuid( STATUSTIMESERIES_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getRadar( ) );
        destination.writeNullableGuid( getPressureTimeseries( ) );
        destination.writeNullableGuid( getTemperatureTimeseries( ) );
        destination.writeNullableGuid( getDewPointTimeseries( ) );
        destination.writeNullableGuid( getStatusTimeseries( ) );
    }

    @Override
    public RadomeDeviceObject getDataObject( ) throws SQLException {
        return new RadomeDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ), getRadar( ), getPressureTimeseries( ), getTemperatureTimeseries( ), getDewPointTimeseries( ), getStatusTimeseries( ) );
    }

}
