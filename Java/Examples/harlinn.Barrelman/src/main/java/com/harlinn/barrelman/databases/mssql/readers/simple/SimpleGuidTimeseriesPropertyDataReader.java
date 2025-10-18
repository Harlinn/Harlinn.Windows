package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGuidTimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gtp.[Id], \r\n" +
            "  gtp.[EntityType], \r\n" +
            "  gtp.[RowVersion], \r\n" +
            "  gtp.[Element], \r\n" +
            "  gtp.[Definition], \r\n" +
            "  gtp.[Timeseries] \r\n" +
            "FROM [GuidTimeseriesPropertyView] gtp \r\n";

    public final static String BaseViewName = "GuidTimeseriesPropertyView";
    public final static String ViewAliasName = "gtp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleGuidTimeseriesPropertyDataReader( ResultSet resultSet ) {
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
    public GuidTimeseriesPropertyObject GetDataObject( ) throws SQLException {
        return new GuidTimeseriesPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getTimeseries( ) );
    }

}
