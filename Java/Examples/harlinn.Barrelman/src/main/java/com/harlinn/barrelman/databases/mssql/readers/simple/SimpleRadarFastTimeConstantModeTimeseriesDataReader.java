package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarFastTimeConstantModeTimeseriesDataReader extends SimpleInt32TimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rftcmt.[Id], \r\n" +
            "  rftcmt.[EntityType], \r\n" +
            "  rftcmt.[RowVersion], \r\n" +
            "  rftcmt.[Catalog], \r\n" +
            "  rftcmt.[Name], \r\n" +
            "  rftcmt.[MaxRetention], \r\n" +
            "  rftcmt.[Radar] \r\n" +
            "FROM [RadarFastTimeConstantModeTimeseriesView] rftcmt \r\n";

    public final static String BaseViewName = "RadarFastTimeConstantModeTimeseriesView";
    public final static String ViewAliasName = "rftcmt";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarFastTimeConstantModeTimeseriesDataReader( ResultSet resultSet ) {
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
