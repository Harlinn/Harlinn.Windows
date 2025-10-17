package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarPulseTimeseriesDataReader extends SimpleInt32TimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rapts.[Id], \r\n" +
            "  rapts.[EntityType], \r\n" +
            "  rapts.[RowVersion], \r\n" +
            "  rapts.[Catalog], \r\n" +
            "  rapts.[Name], \r\n" +
            "  rapts.[MaxRetention], \r\n" +
            "  rapts.[Radar] \r\n" +
            "FROM [RadarPulseTimeseriesView] rapts \r\n";

    public final static String BaseViewName = "RadarPulseTimeseriesView";
    public final static String ViewAliasName = "rapts";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarPulseTimeseriesDataReader( ResultSet resultSet ) {
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
