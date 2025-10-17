package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGNSSLatitudeTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  glats.[Id], \r\n" +
            "  glats.[EntityType], \r\n" +
            "  glats.[RowVersion], \r\n" +
            "  glats.[Catalog], \r\n" +
            "  glats.[Name], \r\n" +
            "  glats.[MaxRetention], \r\n" +
            "  glats.[GNSSDevice] \r\n" +
            "FROM [GNSSLatitudeTimeseriesView] glats \r\n";

    public final static String BaseViewName = "GNSSLatitudeTimeseriesView";
    public final static String ViewAliasName = "glats";

    public final static int GNSSDEVICE_FIELD_ID = 7;

    public SimpleGNSSLatitudeTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getGNSSDevice() throws SQLException {
        return getNullableGuid( GNSSDEVICE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getGNSSDevice( ) );
    }

}
