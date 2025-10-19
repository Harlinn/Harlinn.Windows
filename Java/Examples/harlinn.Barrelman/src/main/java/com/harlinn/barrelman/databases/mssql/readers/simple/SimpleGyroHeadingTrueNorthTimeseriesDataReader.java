package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGyroHeadingTrueNorthTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ghtnt.[Id], \r\n" +
            "  ghtnt.[EntityType], \r\n" +
            "  ghtnt.[RowVersion], \r\n" +
            "  ghtnt.[Catalog], \r\n" +
            "  ghtnt.[Name], \r\n" +
            "  ghtnt.[MaxRetention], \r\n" +
            "  ghtnt.[GyroDevice] \r\n" +
            "FROM [GyroHeadingTrueNorthTimeseriesView] ghtnt \r\n";

    public final static String BaseViewName = "GyroHeadingTrueNorthTimeseriesView";
    public final static String ViewAliasName = "ghtnt";

    public final static int GYRODEVICE_FIELD_ID = 7;

    public SimpleGyroHeadingTrueNorthTimeseriesDataReader( ResultSet resultSet ) {
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

    @Override
    public GyroHeadingTrueNorthTimeseriesObject getDataObject( ) throws SQLException {
        return new GyroHeadingTrueNorthTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGyroDevice( ) );
    }

}
