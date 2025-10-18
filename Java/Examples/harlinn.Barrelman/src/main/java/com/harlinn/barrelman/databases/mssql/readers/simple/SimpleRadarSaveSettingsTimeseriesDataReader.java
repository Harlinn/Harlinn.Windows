package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarSaveSettingsTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rsst.[Id], \r\n" +
            "  rsst.[EntityType], \r\n" +
            "  rsst.[RowVersion], \r\n" +
            "  rsst.[Catalog], \r\n" +
            "  rsst.[Name], \r\n" +
            "  rsst.[MaxRetention], \r\n" +
            "  rsst.[Radar] \r\n" +
            "FROM [RadarSaveSettingsTimeseriesView] rsst \r\n";

    public final static String BaseViewName = "RadarSaveSettingsTimeseriesView";
    public final static String ViewAliasName = "rsst";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarSaveSettingsTimeseriesDataReader( ResultSet resultSet ) {
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
    public RadarSaveSettingsTimeseriesObject GetDataObject( ) throws SQLException {
        return new RadarSaveSettingsTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
