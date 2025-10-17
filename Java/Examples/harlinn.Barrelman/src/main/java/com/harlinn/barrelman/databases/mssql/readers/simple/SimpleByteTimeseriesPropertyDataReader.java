package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleByteTimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  bytp.[Id], \r\n" +
            "  bytp.[EntityType], \r\n" +
            "  bytp.[RowVersion], \r\n" +
            "  bytp.[Element], \r\n" +
            "  bytp.[Definition], \r\n" +
            "  bytp.[Timeseries] \r\n" +
            "FROM [ByteTimeseriesPropertyView] bytp \r\n";

    public final static String BaseViewName = "ByteTimeseriesPropertyView";
    public final static String ViewAliasName = "bytp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleByteTimeseriesPropertyDataReader( ResultSet resultSet ) {
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
