package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisDeviceDataReader extends SimpleTrackerDeviceDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ad.[Id], \r\n" +
            "  ad.[EntityType], \r\n" +
            "  ad.[RowVersion], \r\n" +
            "  ad.[Host], \r\n" +
            "  ad.[Name], \r\n" +
            "  ad.[Description], \r\n" +
            "  ad.[EnabledTimeseries] \r\n" +
            "FROM [AisDeviceView] ad \r\n";

    public final static String BaseViewName = "AisDeviceView";
    public final static String ViewAliasName = "ad";

    public SimpleAisDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public AisDeviceObject GetDataObject( ) throws SQLException {
        return new AisDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ) );
    }

}
