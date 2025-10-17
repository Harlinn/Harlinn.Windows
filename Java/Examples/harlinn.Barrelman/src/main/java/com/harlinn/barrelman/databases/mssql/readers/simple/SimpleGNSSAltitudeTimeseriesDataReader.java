package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGNSSAltitudeTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gats.[Id], \r\n" +
            "  gats.[EntityType], \r\n" +
            "  gats.[RowVersion], \r\n" +
            "  gats.[Catalog], \r\n" +
            "  gats.[Name], \r\n" +
            "  gats.[MaxRetention], \r\n" +
            "  gats.[GNSSDevice] \r\n" +
            "FROM [GNSSAltitudeTimeseriesView] gats \r\n";

    public final static String BaseViewName = "GNSSAltitudeTimeseriesView";
    public final static String ViewAliasName = "gats";

    public final static int GNSSDEVICE_FIELD_ID = 7;

    public SimpleGNSSAltitudeTimeseriesDataReader( ResultSet resultSet ) {
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
