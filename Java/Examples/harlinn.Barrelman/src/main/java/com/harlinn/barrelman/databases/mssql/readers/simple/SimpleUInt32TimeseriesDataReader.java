package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleUInt32TimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u32t.[Id], \r\n" +
            "  u32t.[EntityType], \r\n" +
            "  u32t.[RowVersion], \r\n" +
            "  u32t.[Catalog], \r\n" +
            "  u32t.[Name], \r\n" +
            "  u32t.[MaxRetention] \r\n" +
            "FROM [UInt32TimeseriesView] u32t \r\n";

    public final static String BaseViewName = "UInt32TimeseriesView";
    public final static String ViewAliasName = "u32t";

    public SimpleUInt32TimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
