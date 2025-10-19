package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBinaryTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  bt.[Id], \r\n" +
            "  bt.[EntityType], \r\n" +
            "  bt.[RowVersion], \r\n" +
            "  bt.[Catalog], \r\n" +
            "  bt.[Name], \r\n" +
            "  bt.[MaxRetention] \r\n" +
            "FROM [BinaryTimeseriesView] bt \r\n";

    public final static String BaseViewName = "BinaryTimeseriesView";
    public final static String ViewAliasName = "bt";

    public SimpleBinaryTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public BinaryTimeseriesObject getDataObject( ) throws SQLException {
        return new BinaryTimeseriesObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ), getMaxRetention( ) );
    }

}
