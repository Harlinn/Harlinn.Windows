package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGyroRollTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  grt.[Id], \r\n" +
            "  grt.[EntityType], \r\n" +
            "  grt.[RowVersion], \r\n" +
            "  grt.[Catalog], \r\n" +
            "  grt.[Name], \r\n" +
            "  grt.[MaxRetention], \r\n" +
            "  grt.[GyroDevice] \r\n" +
            "FROM [GyroRollTimeseriesView] grt \r\n";

    public final static String BaseViewName = "GyroRollTimeseriesView";
    public final static String ViewAliasName = "grt";

    public final static int GYRODEVICE_FIELD_ID = 7;

    public SimpleGyroRollTimeseriesDataReader( ResultSet resultSet ) {
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
    public GyroRollTimeseriesObject getDataObject( ) throws SQLException {
        return new GyroRollTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGyroDevice( ) );
    }

}
