package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInt32TimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i32t.[Id], \r\n" +
            "  i32t.[EntityType], \r\n" +
            "  i32t.[RowVersion], \r\n" +
            "  i32t.[Catalog], \r\n" +
            "  i32t.[Name], \r\n" +
            "  i32t.[MaxRetention] \r\n" +
            "FROM [Int32TimeseriesView] i32t \r\n";

    public final static String BaseViewName = "Int32TimeseriesView";
    public final static String ViewAliasName = "i32t";

    public SimpleInt32TimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
