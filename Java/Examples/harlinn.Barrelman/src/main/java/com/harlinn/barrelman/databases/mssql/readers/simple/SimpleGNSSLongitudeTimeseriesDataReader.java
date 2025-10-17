package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGNSSLongitudeTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  glots.[Id], \r\n" +
            "  glots.[EntityType], \r\n" +
            "  glots.[RowVersion], \r\n" +
            "  glots.[Catalog], \r\n" +
            "  glots.[Name], \r\n" +
            "  glots.[MaxRetention], \r\n" +
            "  glots.[GNSSDevice] \r\n" +
            "FROM [GNSSLongitudeTimeseriesView] glots \r\n";

    public final static String BaseViewName = "GNSSLongitudeTimeseriesView";
    public final static String ViewAliasName = "glots";

    public final static int GNSSDEVICE_FIELD_ID = 7;

    public SimpleGNSSLongitudeTimeseriesDataReader( ResultSet resultSet ) {
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
