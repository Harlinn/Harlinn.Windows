package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTimeSpanTimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tstp.[Id], \r\n" +
            "  tstp.[EntityType], \r\n" +
            "  tstp.[RowVersion], \r\n" +
            "  tstp.[Element], \r\n" +
            "  tstp.[Definition], \r\n" +
            "  tstp.[Timeseries] \r\n" +
            "FROM [TimeSpanTimeseriesPropertyView] tstp \r\n";

    public final static String BaseViewName = "TimeSpanTimeseriesPropertyView";
    public final static String ViewAliasName = "tstp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleTimeSpanTimeseriesPropertyDataReader( ResultSet resultSet ) {
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
