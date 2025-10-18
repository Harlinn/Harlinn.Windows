package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarEnableAutomaticFrequencyControlTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  reafct.[Id], \r\n" +
            "  reafct.[EntityType], \r\n" +
            "  reafct.[RowVersion], \r\n" +
            "  reafct.[Catalog], \r\n" +
            "  reafct.[Name], \r\n" +
            "  reafct.[MaxRetention], \r\n" +
            "  reafct.[Radar] \r\n" +
            "FROM [RadarEnableAutomaticFrequencyControlTimeseriesView] reafct \r\n";

    public final static String BaseViewName = "RadarEnableAutomaticFrequencyControlTimeseriesView";
    public final static String ViewAliasName = "reafct";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarEnableAutomaticFrequencyControlTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadarEnableAutomaticFrequencyControlTimeseriesObject GetDataObject( ) throws SQLException {
        return new RadarEnableAutomaticFrequencyControlTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
