package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarSector2StartTimeseriesDataReader extends SimpleInt32TimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rs2st.[Id], \r\n" +
            "  rs2st.[EntityType], \r\n" +
            "  rs2st.[RowVersion], \r\n" +
            "  rs2st.[Catalog], \r\n" +
            "  rs2st.[Name], \r\n" +
            "  rs2st.[MaxRetention], \r\n" +
            "  rs2st.[Radar] \r\n" +
            "FROM [RadarSector2StartTimeseriesView] rs2st \r\n";

    public final static String BaseViewName = "RadarSector2StartTimeseriesView";
    public final static String ViewAliasName = "rs2st";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarSector2StartTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadarSector2StartTimeseriesObject getDataObject( ) throws SQLException {
        return new RadarSector2StartTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
