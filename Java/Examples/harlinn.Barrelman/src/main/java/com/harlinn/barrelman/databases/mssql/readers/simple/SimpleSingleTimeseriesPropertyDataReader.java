package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleSingleTimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sitp.[Id], \r\n" +
            "  sitp.[EntityType], \r\n" +
            "  sitp.[RowVersion], \r\n" +
            "  sitp.[Element], \r\n" +
            "  sitp.[Definition], \r\n" +
            "  sitp.[Timeseries] \r\n" +
            "FROM [SingleTimeseriesPropertyView] sitp \r\n";

    public final static String BaseViewName = "SingleTimeseriesPropertyView";
    public final static String ViewAliasName = "sitp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleSingleTimeseriesPropertyDataReader( ResultSet resultSet ) {
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
    public SingleTimeseriesPropertyObject getDataObject( ) throws SQLException {
        return new SingleTimeseriesPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getTimeseries( ) );
    }

}
