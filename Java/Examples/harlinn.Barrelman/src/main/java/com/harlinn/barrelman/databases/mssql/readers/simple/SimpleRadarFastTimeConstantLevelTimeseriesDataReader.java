package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarFastTimeConstantLevelTimeseriesDataReader extends SimpleInt32TimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rftclt.[Id], \r\n" +
            "  rftclt.[EntityType], \r\n" +
            "  rftclt.[RowVersion], \r\n" +
            "  rftclt.[Catalog], \r\n" +
            "  rftclt.[Name], \r\n" +
            "  rftclt.[MaxRetention], \r\n" +
            "  rftclt.[Radar] \r\n" +
            "FROM [RadarFastTimeConstantLevelTimeseriesView] rftclt \r\n";

    public final static String BaseViewName = "RadarFastTimeConstantLevelTimeseriesView";
    public final static String ViewAliasName = "rftclt";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarFastTimeConstantLevelTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadarFastTimeConstantLevelTimeseriesObject getDataObject( ) throws SQLException {
        return new RadarFastTimeConstantLevelTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
