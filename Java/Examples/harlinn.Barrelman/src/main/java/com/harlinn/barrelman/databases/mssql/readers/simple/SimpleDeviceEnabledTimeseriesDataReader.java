package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleDeviceEnabledTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  det.[Id], \r\n" +
            "  det.[EntityType], \r\n" +
            "  det.[RowVersion], \r\n" +
            "  det.[Catalog], \r\n" +
            "  det.[Name], \r\n" +
            "  det.[MaxRetention], \r\n" +
            "  det.[Device] \r\n" +
            "FROM [DeviceEnabledTimeseriesView] det \r\n";

    public final static String BaseViewName = "DeviceEnabledTimeseriesView";
    public final static String ViewAliasName = "det";

    public final static int DEVICE_FIELD_ID = 7;

    public SimpleDeviceEnabledTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getDevice() throws SQLException {
        return getNullableGuid( DEVICE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getDevice( ) );
    }

}
