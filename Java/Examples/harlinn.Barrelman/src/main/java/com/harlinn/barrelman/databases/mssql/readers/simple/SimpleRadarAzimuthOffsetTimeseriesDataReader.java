package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarAzimuthOffsetTimeseriesDataReader extends SimpleInt32TimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  raot.[Id], \r\n" +
            "  raot.[EntityType], \r\n" +
            "  raot.[RowVersion], \r\n" +
            "  raot.[Catalog], \r\n" +
            "  raot.[Name], \r\n" +
            "  raot.[MaxRetention], \r\n" +
            "  raot.[Radar] \r\n" +
            "FROM [RadarAzimuthOffsetTimeseriesView] raot \r\n";

    public final static String BaseViewName = "RadarAzimuthOffsetTimeseriesView";
    public final static String ViewAliasName = "raot";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarAzimuthOffsetTimeseriesDataReader( ResultSet resultSet ) {
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

}
