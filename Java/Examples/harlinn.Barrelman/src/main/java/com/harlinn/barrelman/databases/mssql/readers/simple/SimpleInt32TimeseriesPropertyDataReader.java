package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInt32TimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i32tp.[Id], \r\n" +
            "  i32tp.[EntityType], \r\n" +
            "  i32tp.[RowVersion], \r\n" +
            "  i32tp.[Element], \r\n" +
            "  i32tp.[Definition], \r\n" +
            "  i32tp.[Timeseries] \r\n" +
            "FROM [Int32TimeseriesPropertyView] i32tp \r\n";

    public final static String BaseViewName = "Int32TimeseriesPropertyView";
    public final static String ViewAliasName = "i32tp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleInt32TimeseriesPropertyDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getTimeseries() throws SQLException {
        return getNullableGuid( TIMESERIES_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getTimeseries( ) );
    }

}
