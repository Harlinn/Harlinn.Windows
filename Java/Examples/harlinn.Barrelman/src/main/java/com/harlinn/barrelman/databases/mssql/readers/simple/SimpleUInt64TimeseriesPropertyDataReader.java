package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleUInt64TimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u64tp.[Id], \r\n" +
            "  u64tp.[EntityType], \r\n" +
            "  u64tp.[RowVersion], \r\n" +
            "  u64tp.[Element], \r\n" +
            "  u64tp.[Definition], \r\n" +
            "  u64tp.[Timeseries] \r\n" +
            "FROM [UInt64TimeseriesPropertyView] u64tp \r\n";

    public final static String BaseViewName = "UInt64TimeseriesPropertyView";
    public final static String ViewAliasName = "u64tp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleUInt64TimeseriesPropertyDataReader( ResultSet resultSet ) {
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

    @Override
    public UInt64TimeseriesPropertyObject getDataObject( ) throws SQLException {
        return new UInt64TimeseriesPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getTimeseries( ) );
    }

}
