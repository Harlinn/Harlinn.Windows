package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInt16TimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i16tp.[Id], \r\n" +
            "  i16tp.[EntityType], \r\n" +
            "  i16tp.[RowVersion], \r\n" +
            "  i16tp.[Element], \r\n" +
            "  i16tp.[Definition], \r\n" +
            "  i16tp.[Timeseries] \r\n" +
            "FROM [Int16TimeseriesPropertyView] i16tp \r\n";

    public final static String BaseViewName = "Int16TimeseriesPropertyView";
    public final static String ViewAliasName = "i16tp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleInt16TimeseriesPropertyDataReader( ResultSet resultSet ) {
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
    public Int16TimeseriesPropertyObject GetDataObject( ) throws SQLException {
        return new Int16TimeseriesPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getTimeseries( ) );
    }

}
