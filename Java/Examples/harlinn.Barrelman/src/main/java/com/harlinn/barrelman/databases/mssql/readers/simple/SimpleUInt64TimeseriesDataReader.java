package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleUInt64TimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u64t.[Id], \r\n" +
            "  u64t.[EntityType], \r\n" +
            "  u64t.[RowVersion], \r\n" +
            "  u64t.[Catalog], \r\n" +
            "  u64t.[Name], \r\n" +
            "  u64t.[MaxRetention] \r\n" +
            "FROM [UInt64TimeseriesView] u64t \r\n";

    public final static String BaseViewName = "UInt64TimeseriesView";
    public final static String ViewAliasName = "u64t";

    public SimpleUInt64TimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public UInt64TimeseriesObject GetDataObject( ) throws SQLException {
        return new UInt64TimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
