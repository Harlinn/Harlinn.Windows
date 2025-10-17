package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarSensitivityTimeControlLevelTimeseriesDataReader extends SimpleInt32TimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rstclt.[Id], \r\n" +
            "  rstclt.[EntityType], \r\n" +
            "  rstclt.[RowVersion], \r\n" +
            "  rstclt.[Catalog], \r\n" +
            "  rstclt.[Name], \r\n" +
            "  rstclt.[MaxRetention], \r\n" +
            "  rstclt.[Radar] \r\n" +
            "FROM [RadarSensitivityTimeControlLevelTimeseriesView] rstclt \r\n";

    public final static String BaseViewName = "RadarSensitivityTimeControlLevelTimeseriesView";
    public final static String ViewAliasName = "rstclt";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarSensitivityTimeControlLevelTimeseriesDataReader( ResultSet resultSet ) {
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
