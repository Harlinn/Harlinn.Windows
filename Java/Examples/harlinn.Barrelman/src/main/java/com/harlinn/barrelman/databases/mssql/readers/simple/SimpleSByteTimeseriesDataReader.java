package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleSByteTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  st.[Id], \r\n" +
            "  st.[EntityType], \r\n" +
            "  st.[RowVersion], \r\n" +
            "  st.[Catalog], \r\n" +
            "  st.[Name], \r\n" +
            "  st.[MaxRetention] \r\n" +
            "FROM [SByteTimeseriesView] st \r\n";

    public final static String BaseViewName = "SByteTimeseriesView";
    public final static String ViewAliasName = "st";

    public SimpleSByteTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
