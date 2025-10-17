package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimpleDeviceDataReader extends SimpleItemDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  d.[Id], \r\n" +
            "  d.[EntityType], \r\n" +
            "  d.[RowVersion], \r\n" +
            "  d.[Host], \r\n" +
            "  d.[Name], \r\n" +
            "  d.[Description], \r\n" +
            "  d.[EnabledTimeseries] \r\n" +
            "FROM [DeviceView] d \r\n";

    public final static String BaseViewName = "DeviceView";
    public final static String ViewAliasName = "d";

    public final static int HOST_FIELD_ID = 4;
    public final static int NAME_FIELD_ID = 5;
    public final static int DESCRIPTION_FIELD_ID = 6;
    public final static int ENABLEDTIMESERIES_FIELD_ID = 7;

    public SimpleDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getHost() throws SQLException {
        return getGuid( HOST_FIELD_ID );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final String getDescription() throws SQLException {
        return getString( DESCRIPTION_FIELD_ID );
    }

    public final Guid getEnabledTimeseries() throws SQLException {
        return getNullableGuid( ENABLEDTIMESERIES_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeGuid( getHost( ) );
        destination.writeStringUtf8( getName( ) );
        destination.writeStringUtf8( getDescription( ) );
        destination.writeNullableGuid( getEnabledTimeseries( ) );
    }

}
