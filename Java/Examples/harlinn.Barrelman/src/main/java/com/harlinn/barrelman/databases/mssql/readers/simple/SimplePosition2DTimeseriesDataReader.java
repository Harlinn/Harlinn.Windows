package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimplePosition2DTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  p2d.[Id], \r\n" +
            "  p2d.[EntityType], \r\n" +
            "  p2d.[RowVersion], \r\n" +
            "  p2d.[Catalog], \r\n" +
            "  p2d.[Name], \r\n" +
            "  p2d.[MaxRetention] \r\n" +
            "FROM [Position2DTimeseriesView] p2d \r\n";

    public final static String BaseViewName = "Position2DTimeseriesView";
    public final static String ViewAliasName = "p2d";

    public SimplePosition2DTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
