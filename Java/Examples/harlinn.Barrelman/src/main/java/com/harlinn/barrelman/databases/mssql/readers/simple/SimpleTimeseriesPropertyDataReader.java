package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimpleTimeseriesPropertyDataReader extends SimplePropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tp.[Id], \r\n" +
            "  tp.[EntityType], \r\n" +
            "  tp.[RowVersion], \r\n" +
            "  tp.[Element], \r\n" +
            "  tp.[Definition] \r\n" +
            "FROM [TimeseriesPropertyView] tp \r\n";

    public final static String BaseViewName = "TimeseriesPropertyView";
    public final static String ViewAliasName = "tp";

    public SimpleTimeseriesPropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
