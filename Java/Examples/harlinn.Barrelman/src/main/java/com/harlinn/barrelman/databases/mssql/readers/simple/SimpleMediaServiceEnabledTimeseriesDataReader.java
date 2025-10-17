package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleMediaServiceEnabledTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  mset.[Id], \r\n" +
            "  mset.[EntityType], \r\n" +
            "  mset.[RowVersion], \r\n" +
            "  mset.[Catalog], \r\n" +
            "  mset.[Name], \r\n" +
            "  mset.[MaxRetention], \r\n" +
            "  mset.[Service] \r\n" +
            "FROM [MediaServiceEnabledTimeseriesView] mset \r\n";

    public final static String BaseViewName = "MediaServiceEnabledTimeseriesView";
    public final static String ViewAliasName = "mset";

    public final static int SERVICE_FIELD_ID = 7;

    public SimpleMediaServiceEnabledTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getService() throws SQLException {
        return getNullableGuid( SERVICE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getService( ) );
    }

}
