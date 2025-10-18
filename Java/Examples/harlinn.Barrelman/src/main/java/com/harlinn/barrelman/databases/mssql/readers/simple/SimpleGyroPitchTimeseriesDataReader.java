package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGyroPitchTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gpt.[Id], \r\n" +
            "  gpt.[EntityType], \r\n" +
            "  gpt.[RowVersion], \r\n" +
            "  gpt.[Catalog], \r\n" +
            "  gpt.[Name], \r\n" +
            "  gpt.[MaxRetention], \r\n" +
            "  gpt.[GyroDevice] \r\n" +
            "FROM [GyroPitchTimeseriesView] gpt \r\n";

    public final static String BaseViewName = "GyroPitchTimeseriesView";
    public final static String ViewAliasName = "gpt";

    public final static int GYRODEVICE_FIELD_ID = 7;

    public SimpleGyroPitchTimeseriesDataReader( ResultSet resultSet ) {
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
    public GyroPitchTimeseriesObject GetDataObject( ) throws SQLException {
        return new GyroPitchTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getGyroDevice( ) );
    }

}
