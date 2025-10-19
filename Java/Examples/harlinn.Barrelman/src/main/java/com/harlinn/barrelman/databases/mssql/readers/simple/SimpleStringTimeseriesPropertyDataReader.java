package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleStringTimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sttp.[Id], \r\n" +
            "  sttp.[EntityType], \r\n" +
            "  sttp.[RowVersion], \r\n" +
            "  sttp.[Element], \r\n" +
            "  sttp.[Definition], \r\n" +
            "  sttp.[Timeseries] \r\n" +
            "FROM [StringTimeseriesPropertyView] sttp \r\n";

    public final static String BaseViewName = "StringTimeseriesPropertyView";
    public final static String ViewAliasName = "sttp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleStringTimeseriesPropertyDataReader( ResultSet resultSet ) {
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
    public StringTimeseriesPropertyObject getDataObject( ) throws SQLException {
        return new StringTimeseriesPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getTimeseries( ) );
    }

}
