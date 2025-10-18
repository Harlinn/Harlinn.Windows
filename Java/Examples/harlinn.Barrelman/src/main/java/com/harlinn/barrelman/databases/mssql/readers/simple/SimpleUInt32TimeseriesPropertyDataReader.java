package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleUInt32TimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u32tp.[Id], \r\n" +
            "  u32tp.[EntityType], \r\n" +
            "  u32tp.[RowVersion], \r\n" +
            "  u32tp.[Element], \r\n" +
            "  u32tp.[Definition], \r\n" +
            "  u32tp.[Timeseries] \r\n" +
            "FROM [UInt32TimeseriesPropertyView] u32tp \r\n";

    public final static String BaseViewName = "UInt32TimeseriesPropertyView";
    public final static String ViewAliasName = "u32tp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleUInt32TimeseriesPropertyDataReader( ResultSet resultSet ) {
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
    public UInt32TimeseriesPropertyObject GetDataObject( ) throws SQLException {
        return new UInt32TimeseriesPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getTimeseries( ) );
    }

}
