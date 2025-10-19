package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarEnableSensitivityTimeControlTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  restct.[Id], \r\n" +
            "  restct.[EntityType], \r\n" +
            "  restct.[RowVersion], \r\n" +
            "  restct.[Catalog], \r\n" +
            "  restct.[Name], \r\n" +
            "  restct.[MaxRetention], \r\n" +
            "  restct.[Radar] \r\n" +
            "FROM [RadarEnableSensitivityTimeControlTimeseriesView] restct \r\n";

    public final static String BaseViewName = "RadarEnableSensitivityTimeControlTimeseriesView";
    public final static String ViewAliasName = "restct";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarEnableSensitivityTimeControlTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadarEnableSensitivityTimeControlTimeseriesObject getDataObject( ) throws SQLException {
        return new RadarEnableSensitivityTimeControlTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
