package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGyroHeadingMagneticNorthTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ghmnt.[Id], \r\n" +
            "  ghmnt.[EntityType], \r\n" +
            "  ghmnt.[RowVersion], \r\n" +
            "  ghmnt.[Catalog], \r\n" +
            "  ghmnt.[Name], \r\n" +
            "  ghmnt.[MaxRetention], \r\n" +
            "  ghmnt.[GyroDevice] \r\n" +
            "FROM [GyroHeadingMagneticNorthTimeseriesView] ghmnt \r\n";

    public final static String BaseViewName = "GyroHeadingMagneticNorthTimeseriesView";
    public final static String ViewAliasName = "ghmnt";

    public final static int GYRODEVICE_FIELD_ID = 7;

    public SimpleGyroHeadingMagneticNorthTimeseriesDataReader( ResultSet resultSet ) {
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
