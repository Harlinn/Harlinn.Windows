package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleDoubleTimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  dotp.[Id], \r\n" +
            "  dotp.[EntityType], \r\n" +
            "  dotp.[RowVersion], \r\n" +
            "  dotp.[Element], \r\n" +
            "  dotp.[Definition], \r\n" +
            "  dotp.[Timeseries] \r\n" +
            "FROM [DoubleTimeseriesPropertyView] dotp \r\n";

    public final static String BaseViewName = "DoubleTimeseriesPropertyView";
    public final static String ViewAliasName = "dotp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleDoubleTimeseriesPropertyDataReader( ResultSet resultSet ) {
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
    public DoubleTimeseriesPropertyObject getDataObject( ) throws SQLException {
        return new DoubleTimeseriesPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getTimeseries( ) );
    }

}
