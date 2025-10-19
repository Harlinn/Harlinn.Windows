package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarLongitudeTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rlots.[Id], \r\n" +
            "  rlots.[EntityType], \r\n" +
            "  rlots.[RowVersion], \r\n" +
            "  rlots.[Catalog], \r\n" +
            "  rlots.[Name], \r\n" +
            "  rlots.[MaxRetention], \r\n" +
            "  rlots.[Radar] \r\n" +
            "FROM [RadarLongitudeTimeseriesView] rlots \r\n";

    public final static String BaseViewName = "RadarLongitudeTimeseriesView";
    public final static String ViewAliasName = "rlots";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarLongitudeTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadarLongitudeTimeseriesObject getDataObject( ) throws SQLException {
        return new RadarLongitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
