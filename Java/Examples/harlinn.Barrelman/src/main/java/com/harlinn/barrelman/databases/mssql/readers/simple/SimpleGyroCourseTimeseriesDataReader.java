package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGyroCourseTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gct.[Id], \r\n" +
            "  gct.[EntityType], \r\n" +
            "  gct.[RowVersion], \r\n" +
            "  gct.[Catalog], \r\n" +
            "  gct.[Name], \r\n" +
            "  gct.[MaxRetention], \r\n" +
            "  gct.[GyroDevice] \r\n" +
            "FROM [GyroCourseTimeseriesView] gct \r\n";

    public final static String BaseViewName = "GyroCourseTimeseriesView";
    public final static String ViewAliasName = "gct";

    public final static int GYRODEVICE_FIELD_ID = 7;

    public SimpleGyroCourseTimeseriesDataReader( ResultSet resultSet ) {
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
