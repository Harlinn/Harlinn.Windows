package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGyroRateOfTurnTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  grott.[Id], \r\n" +
            "  grott.[EntityType], \r\n" +
            "  grott.[RowVersion], \r\n" +
            "  grott.[Catalog], \r\n" +
            "  grott.[Name], \r\n" +
            "  grott.[MaxRetention], \r\n" +
            "  grott.[GyroDevice] \r\n" +
            "FROM [GyroRateOfTurnTimeseriesView] grott \r\n";

    public final static String BaseViewName = "GyroRateOfTurnTimeseriesView";
    public final static String ViewAliasName = "grott";

    public final static int GYRODEVICE_FIELD_ID = 7;

    public SimpleGyroRateOfTurnTimeseriesDataReader( ResultSet resultSet ) {
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
