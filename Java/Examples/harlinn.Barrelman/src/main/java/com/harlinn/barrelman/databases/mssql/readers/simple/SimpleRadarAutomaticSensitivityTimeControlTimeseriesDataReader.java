package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarAutomaticSensitivityTimeControlTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rastct.[Id], \r\n" +
            "  rastct.[EntityType], \r\n" +
            "  rastct.[RowVersion], \r\n" +
            "  rastct.[Catalog], \r\n" +
            "  rastct.[Name], \r\n" +
            "  rastct.[MaxRetention], \r\n" +
            "  rastct.[Radar] \r\n" +
            "FROM [RadarAutomaticSensitivityTimeControlTimeseriesView] rastct \r\n";

    public final static String BaseViewName = "RadarAutomaticSensitivityTimeControlTimeseriesView";
    public final static String ViewAliasName = "rastct";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarAutomaticSensitivityTimeControlTimeseriesDataReader( ResultSet resultSet ) {
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
