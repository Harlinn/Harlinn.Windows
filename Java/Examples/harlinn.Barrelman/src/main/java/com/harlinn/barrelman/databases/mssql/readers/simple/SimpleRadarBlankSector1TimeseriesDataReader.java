package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarBlankSector1TimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rbs1t.[Id], \r\n" +
            "  rbs1t.[EntityType], \r\n" +
            "  rbs1t.[RowVersion], \r\n" +
            "  rbs1t.[Catalog], \r\n" +
            "  rbs1t.[Name], \r\n" +
            "  rbs1t.[MaxRetention], \r\n" +
            "  rbs1t.[Radar] \r\n" +
            "FROM [RadarBlankSector1TimeseriesView] rbs1t \r\n";

    public final static String BaseViewName = "RadarBlankSector1TimeseriesView";
    public final static String ViewAliasName = "rbs1t";

    public final static int RADAR_FIELD_ID = 7;

    public SimpleRadarBlankSector1TimeseriesDataReader( ResultSet resultSet ) {
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
    public RadarBlankSector1TimeseriesObject GetDataObject( ) throws SQLException {
        return new RadarBlankSector1TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getRadar( ) );
    }

}
