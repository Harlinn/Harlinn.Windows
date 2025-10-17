package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarPowerOnTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rpot.[Id], \r\n" +
            "  rpot.[EntityType], \r\n" +
            "  rpot.[RowVersion], \r\n" +
            "  rpot.[Catalog], \r\n" +
            "  rpot.[Name], \r\n" +
            "  rpot.[MaxRetention], \r\n" +
            "  rpot.[Radar] \r\n" +
            "FROM [RadarPowerOnTimeseriesView] rpot \r\n";

    public final static String BaseViewName = "RadarPowerOnTimeseriesView";
    public final static String ViewAliasName = "rpot";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarPowerOnTimeseriesDataReader( ResultSet resultSet ) {
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
