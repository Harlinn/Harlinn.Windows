package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleUInt16TimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u16tp.[Id], \r\n" +
            "  u16tp.[EntityType], \r\n" +
            "  u16tp.[RowVersion], \r\n" +
            "  u16tp.[Element], \r\n" +
            "  u16tp.[Definition], \r\n" +
            "  u16tp.[Timeseries] \r\n" +
            "FROM [UInt16TimeseriesPropertyView] u16tp \r\n";

    public final static String BaseViewName = "UInt16TimeseriesPropertyView";
    public final static String ViewAliasName = "u16tp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleUInt16TimeseriesPropertyDataReader( ResultSet resultSet ) {
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
    public UInt16TimeseriesPropertyObject GetDataObject( ) throws SQLException {
        return new UInt16TimeseriesPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getTimeseries( ) );
    }

}
