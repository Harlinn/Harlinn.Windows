package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInt64TimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i64t.[Id], \r\n" +
            "  i64t.[EntityType], \r\n" +
            "  i64t.[RowVersion], \r\n" +
            "  i64t.[Catalog], \r\n" +
            "  i64t.[Name], \r\n" +
            "  i64t.[MaxRetention] \r\n" +
            "FROM [Int64TimeseriesView] i64t \r\n";

    public final static String BaseViewName = "Int64TimeseriesView";
    public final static String ViewAliasName = "i64t";

    public SimpleInt64TimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
