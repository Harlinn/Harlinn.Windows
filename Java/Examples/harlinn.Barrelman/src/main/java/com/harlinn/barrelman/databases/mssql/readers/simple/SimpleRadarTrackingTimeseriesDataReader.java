package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarTrackingTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rtt.[Id], \r\n" +
            "  rtt.[EntityType], \r\n" +
            "  rtt.[RowVersion], \r\n" +
            "  rtt.[Catalog], \r\n" +
            "  rtt.[Name], \r\n" +
            "  rtt.[MaxRetention], \r\n" +
            "  rtt.[Radar] \r\n" +
            "FROM [RadarTrackingTimeseriesView] rtt \r\n";

    public final static String BaseViewName = "RadarTrackingTimeseriesView";
    public final static String ViewAliasName = "rtt";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarTrackingTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getRadar() throws SQLException {
        return getNullableGuid( RADAR_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getRadar( ) );
    }

    @Override
    public RadarTrackingTimeseriesObject getDataObject( ) throws SQLException {
        return new RadarTrackingTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
