package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleReferenceTimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rtp.[Id], \r\n" +
            "  rtp.[EntityType], \r\n" +
            "  rtp.[RowVersion], \r\n" +
            "  rtp.[Element], \r\n" +
            "  rtp.[Definition], \r\n" +
            "  rtp.[Timeseries] \r\n" +
            "FROM [ReferenceTimeseriesPropertyView] rtp \r\n";

    public final static String BaseViewName = "ReferenceTimeseriesPropertyView";
    public final static String ViewAliasName = "rtp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleReferenceTimeseriesPropertyDataReader( ResultSet resultSet ) {
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
