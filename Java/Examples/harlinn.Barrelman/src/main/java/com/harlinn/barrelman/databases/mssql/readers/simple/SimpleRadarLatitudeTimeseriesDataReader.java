package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarLatitudeTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rlats.[Id], \r\n" +
            "  rlats.[EntityType], \r\n" +
            "  rlats.[RowVersion], \r\n" +
            "  rlats.[Catalog], \r\n" +
            "  rlats.[Name], \r\n" +
            "  rlats.[MaxRetention], \r\n" +
            "  rlats.[Radar] \r\n" +
            "FROM [RadarLatitudeTimeseriesView] rlats \r\n";

    public final static String BaseViewName = "RadarLatitudeTimeseriesView";
    public final static String ViewAliasName = "rlats";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarLatitudeTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadarLatitudeTimeseriesObject getDataObject( ) throws SQLException {
        return new RadarLatitudeTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
