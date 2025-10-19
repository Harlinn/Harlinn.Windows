package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleLineInputDeviceDataReader extends SimpleDeviceDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  lid.[Id], \r\n" +
            "  lid.[EntityType], \r\n" +
            "  lid.[RowVersion], \r\n" +
            "  lid.[Host], \r\n" +
            "  lid.[Name], \r\n" +
            "  lid.[Description], \r\n" +
            "  lid.[EnabledTimeseries] \r\n" +
            "FROM [LineInputDeviceView] lid \r\n";

    public final static String BaseViewName = "LineInputDeviceView";
    public final static String ViewAliasName = "lid";

    public SimpleLineInputDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public LineInputDeviceObject getDataObject( ) throws SQLException {
        return new LineInputDeviceObject( ObjectState.Stored, getId( ), getRowVersion( ), getHost( ), getName( ), getDescription( ), getEnabledTimeseries( ) );
    }

}
