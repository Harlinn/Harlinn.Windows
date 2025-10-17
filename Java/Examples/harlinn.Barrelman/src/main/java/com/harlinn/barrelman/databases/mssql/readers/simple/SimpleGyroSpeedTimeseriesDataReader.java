package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGyroSpeedTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gst.[Id], \r\n" +
            "  gst.[EntityType], \r\n" +
            "  gst.[RowVersion], \r\n" +
            "  gst.[Catalog], \r\n" +
            "  gst.[Name], \r\n" +
            "  gst.[MaxRetention], \r\n" +
            "  gst.[GyroDevice] \r\n" +
            "FROM [GyroSpeedTimeseriesView] gst \r\n";

    public final static String BaseViewName = "GyroSpeedTimeseriesView";
    public final static String ViewAliasName = "gst";

    public final static int GYRODEVICE_FIELD_ID = 7;

    public SimpleGyroSpeedTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getGyroDevice() throws SQLException {
        return getNullableGuid( GYRODEVICE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getGyroDevice( ) );
    }

}
