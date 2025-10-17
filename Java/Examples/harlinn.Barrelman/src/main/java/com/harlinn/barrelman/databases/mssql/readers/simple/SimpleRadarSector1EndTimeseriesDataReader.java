package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarSector1EndTimeseriesDataReader extends SimpleInt32TimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rs1et.[Id], \r\n" +
            "  rs1et.[EntityType], \r\n" +
            "  rs1et.[RowVersion], \r\n" +
            "  rs1et.[Catalog], \r\n" +
            "  rs1et.[Name], \r\n" +
            "  rs1et.[MaxRetention], \r\n" +
            "  rs1et.[Radar] \r\n" +
            "FROM [RadarSector1EndTimeseriesView] rs1et \r\n";

    public final static String BaseViewName = "RadarSector1EndTimeseriesView";
    public final static String ViewAliasName = "rs1et";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarSector1EndTimeseriesDataReader( ResultSet resultSet ) {
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
