package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTimeSpanTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tst.[Id], \r\n" +
            "  tst.[EntityType], \r\n" +
            "  tst.[RowVersion], \r\n" +
            "  tst.[Catalog], \r\n" +
            "  tst.[Name], \r\n" +
            "  tst.[MaxRetention] \r\n" +
            "FROM [TimeSpanTimeseriesView] tst \r\n";

    public final static String BaseViewName = "TimeSpanTimeseriesView";
    public final static String ViewAliasName = "tst";

    public SimpleTimeSpanTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
