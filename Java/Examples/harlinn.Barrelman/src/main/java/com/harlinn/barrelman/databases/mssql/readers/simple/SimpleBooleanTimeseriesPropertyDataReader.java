package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBooleanTimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  botp.[Id], \r\n" +
            "  botp.[EntityType], \r\n" +
            "  botp.[RowVersion], \r\n" +
            "  botp.[Element], \r\n" +
            "  botp.[Definition], \r\n" +
            "  botp.[Timeseries] \r\n" +
            "FROM [BooleanTimeseriesPropertyView] botp \r\n";

    public final static String BaseViewName = "BooleanTimeseriesPropertyView";
    public final static String ViewAliasName = "botp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleBooleanTimeseriesPropertyDataReader( ResultSet resultSet ) {
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
    public BooleanTimeseriesPropertyObject getDataObject( ) throws SQLException {
        return new BooleanTimeseriesPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getTimeseries( ) );
    }

}
