package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleOilSpillDetectorDeviceDataReader extends SimpleDeviceDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  osdd.[Id], \r\n" +
            "  osdd.[EntityType], \r\n" +
            "  osdd.[RowVersion], \r\n" +
            "  osdd.[Host], \r\n" +
            "  osdd.[Name], \r\n" +
            "  osdd.[Description], \r\n" +
            "  osdd.[EnabledTimeseries] \r\n" +
            "FROM [OilSpillDetectorDeviceView] osdd \r\n";

    public final static String BaseViewName = "OilSpillDetectorDeviceView";
    public final static String ViewAliasName = "osdd";

    public SimpleOilSpillDetectorDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public OilSpillDetectorDeviceObject getDataObject( ) throws SQLException {
        return new OilSpillDetectorDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ) );
    }

}
