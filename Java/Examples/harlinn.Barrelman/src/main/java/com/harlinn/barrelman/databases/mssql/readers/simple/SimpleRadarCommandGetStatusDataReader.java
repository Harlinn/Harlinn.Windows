package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarCommandGetStatusDataReader extends SimpleRadarCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rcgs.[Id], \r\n" +
            "  rcgs.[EntityType], \r\n" +
            "  rcgs.[RowVersion], \r\n" +
            "  rcgs.[Radar], \r\n" +
            "  rcgs.[Timestamp], \r\n" +
            "  rcgs.[DeviceCommandSourceType], \r\n" +
            "  rcgs.[DeviceCommandSourceId], \r\n" +
            "  rcgs.[Reply] \r\n" +
            "FROM [RadarCommandGetStatusView] rcgs \r\n";

    public final static String BaseViewName = "RadarCommandGetStatusView";
    public final static String ViewAliasName = "rcgs";

    public SimpleRadarCommandGetStatusDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
