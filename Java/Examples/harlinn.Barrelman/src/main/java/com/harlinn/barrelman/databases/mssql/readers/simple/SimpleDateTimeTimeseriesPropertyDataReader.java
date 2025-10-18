package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleDateTimeTimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  dttp.[Id], \r\n" +
            "  dttp.[EntityType], \r\n" +
            "  dttp.[RowVersion], \r\n" +
            "  dttp.[Element], \r\n" +
            "  dttp.[Definition], \r\n" +
            "  dttp.[Timeseries] \r\n" +
            "FROM [DateTimeTimeseriesPropertyView] dttp \r\n";

    public final static String BaseViewName = "DateTimeTimeseriesPropertyView";
    public final static String ViewAliasName = "dttp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleDateTimeTimeseriesPropertyDataReader( ResultSet resultSet ) {
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
    public DateTimeTimeseriesPropertyObject GetDataObject( ) throws SQLException {
        return new DateTimeTimeseriesPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getTimeseries( ) );
    }

}
