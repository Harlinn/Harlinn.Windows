package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleMediaProxySessionEnabledTimeseriesDataReader extends SimpleBooleanTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  mpset.[Id], \r\n" +
            "  mpset.[EntityType], \r\n" +
            "  mpset.[RowVersion], \r\n" +
            "  mpset.[Catalog], \r\n" +
            "  mpset.[Name], \r\n" +
            "  mpset.[MaxRetention], \r\n" +
            "  mpset.[ProxySession] \r\n" +
            "FROM [MediaProxySessionEnabledTimeseriesView] mpset \r\n";

    public final static String BaseViewName = "MediaProxySessionEnabledTimeseriesView";
    public final static String ViewAliasName = "mpset";

    public final static int PROXYSESSION_FIELD_ID = 7;

    public SimpleMediaProxySessionEnabledTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getProxySession() throws SQLException {
        return getNullableGuid( PROXYSESSION_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getProxySession( ) );
    }

    @Override
    public MediaProxySessionEnabledTimeseriesObject getDataObject( ) throws SQLException {
        return new MediaProxySessionEnabledTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ), getProxySession( ) );
    }

}
