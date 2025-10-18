package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarSector1StartTimeseriesDataReader extends SimpleInt32TimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rs1st.[Id], \r\n" +
            "  rs1st.[EntityType], \r\n" +
            "  rs1st.[RowVersion], \r\n" +
            "  rs1st.[Catalog], \r\n" +
            "  rs1st.[Name], \r\n" +
            "  rs1st.[MaxRetention], \r\n" +
            "  rs1st.[Radar] \r\n" +
            "FROM [RadarSector1StartTimeseriesView] rs1st \r\n";

    public final static String BaseViewName = "RadarSector1StartTimeseriesView";
    public final static String ViewAliasName = "rs1st";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarSector1StartTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadarSector1StartTimeseriesObject GetDataObject( ) throws SQLException {
        return new RadarSector1StartTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
