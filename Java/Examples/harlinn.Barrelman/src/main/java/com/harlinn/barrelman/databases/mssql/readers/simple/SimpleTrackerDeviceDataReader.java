package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimpleTrackerDeviceDataReader extends SimpleDeviceDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  td.[Id], \r\n" +
            "  td.[EntityType], \r\n" +
            "  td.[RowVersion], \r\n" +
            "  td.[Host], \r\n" +
            "  td.[Name], \r\n" +
            "  td.[Description], \r\n" +
            "  td.[EnabledTimeseries] \r\n" +
            "FROM [TrackerDeviceView] td \r\n";

    public final static String BaseViewName = "TrackerDeviceView";
    public final static String ViewAliasName = "td";

    public SimpleTrackerDeviceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
