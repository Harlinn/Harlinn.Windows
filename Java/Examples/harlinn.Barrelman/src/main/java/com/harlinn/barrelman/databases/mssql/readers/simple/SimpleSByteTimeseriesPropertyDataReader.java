package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleSByteTimeseriesPropertyDataReader extends SimpleTimeseriesPropertyDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sbtp.[Id], \r\n" +
            "  sbtp.[EntityType], \r\n" +
            "  sbtp.[RowVersion], \r\n" +
            "  sbtp.[Element], \r\n" +
            "  sbtp.[Definition], \r\n" +
            "  sbtp.[Timeseries] \r\n" +
            "FROM [SByteTimeseriesPropertyView] sbtp \r\n";

    public final static String BaseViewName = "SByteTimeseriesPropertyView";
    public final static String ViewAliasName = "sbtp";

    public final static int TIMESERIES_FIELD_ID = 6;

    public SimpleSByteTimeseriesPropertyDataReader( ResultSet resultSet ) {
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
    public SByteTimeseriesPropertyObject getDataObject( ) throws SQLException {
        return new SByteTimeseriesPropertyObject( ObjectState.Stored, getId( ), getRowVersion( ), getElement( ), getDefinition( ), getTimeseries( ) );
    }

}
