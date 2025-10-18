package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarEnableFastTimeConstantTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  reftct.[Id], \r\n" +
            "  reftct.[EntityType], \r\n" +
            "  reftct.[RowVersion], \r\n" +
            "  reftct.[Catalog], \r\n" +
            "  reftct.[Name], \r\n" +
            "  reftct.[MaxRetention], \r\n" +
            "  reftct.[Radar] \r\n" +
            "FROM [RadarEnableFastTimeConstantTimeseriesView] reftct \r\n";

    public final static String BaseViewName = "RadarEnableFastTimeConstantTimeseriesView";
    public final static String ViewAliasName = "reftct";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarEnableFastTimeConstantTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadarEnableFastTimeConstantTimeseriesObject GetDataObject( ) throws SQLException {
        return new RadarEnableFastTimeConstantTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
