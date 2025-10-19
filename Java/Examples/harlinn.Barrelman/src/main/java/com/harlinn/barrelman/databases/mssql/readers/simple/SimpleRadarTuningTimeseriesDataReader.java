package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarTuningTimeseriesDataReader extends SimpleInt32TimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ratuts.[Id], \r\n" +
            "  ratuts.[EntityType], \r\n" +
            "  ratuts.[RowVersion], \r\n" +
            "  ratuts.[Catalog], \r\n" +
            "  ratuts.[Name], \r\n" +
            "  ratuts.[MaxRetention], \r\n" +
            "  ratuts.[Radar] \r\n" +
            "FROM [RadarTuningTimeseriesView] ratuts \r\n";

    public final static String BaseViewName = "RadarTuningTimeseriesView";
    public final static String ViewAliasName = "ratuts";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarTuningTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadarTuningTimeseriesObject getDataObject( ) throws SQLException {
        return new RadarTuningTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
