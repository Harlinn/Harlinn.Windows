package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarSector2EndTimeseriesDataReader extends SimpleInt32TimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rs2et.[Id], \r\n" +
            "  rs2et.[EntityType], \r\n" +
            "  rs2et.[RowVersion], \r\n" +
            "  rs2et.[Catalog], \r\n" +
            "  rs2et.[Name], \r\n" +
            "  rs2et.[MaxRetention], \r\n" +
            "  rs2et.[Radar] \r\n" +
            "FROM [RadarSector2EndTimeseriesView] rs2et \r\n";

    public final static String BaseViewName = "RadarSector2EndTimeseriesView";
    public final static String ViewAliasName = "rs2et";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarSector2EndTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadarSector2EndTimeseriesObject GetDataObject( ) throws SQLException {
        return new RadarSector2EndTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
