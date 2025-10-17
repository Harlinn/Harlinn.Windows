package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBinaryTimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  btp.[Id], \r\n" +
            "  btp.[EntityType], \r\n" +
            "  btp.[RowVersion], \r\n" +
            "  btp.[Element], \r\n" +
            "  btp.[Definition], \r\n" +
            "  btp.[Timeseries] \r\n" +
            "FROM [BinaryTimeseriesPropertyView] btp \r\n";

    public final static String BaseViewName = "BinaryTimeseriesPropertyView";
    public final static String ViewAliasName = "btp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleBinaryTimeseriesPropertyDataReader( ResultSet resultSet ) {
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
