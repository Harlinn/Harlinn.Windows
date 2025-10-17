package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimpleTimeseriesDataReader extends SimpleTimeseriesCatalogElementDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  t.[Id], \r\n" +
            "  t.[EntityType], \r\n" +
            "  t.[RowVersion], \r\n" +
            "  t.[Catalog], \r\n" +
            "  t.[Name], \r\n" +
            "  t.[MaxRetention] \r\n" +
            "FROM [TimeseriesView] t \r\n";

    public final static String BaseViewName = "TimeseriesView";
    public final static String ViewAliasName = "t";

    public final static int MAXRETENTION_FIELD_ID = 6;

    public SimpleTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final TimeSpan getMaxRetention() throws SQLException {
        return getTimeSpan( MAXRETENTION_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeTimeSpan( getMaxRetention( ) );
    }

}
