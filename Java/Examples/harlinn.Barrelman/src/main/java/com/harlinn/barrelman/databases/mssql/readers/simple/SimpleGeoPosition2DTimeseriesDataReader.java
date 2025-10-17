package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGeoPosition2DTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gp2d.[Id], \r\n" +
            "  gp2d.[EntityType], \r\n" +
            "  gp2d.[RowVersion], \r\n" +
            "  gp2d.[Catalog], \r\n" +
            "  gp2d.[Name], \r\n" +
            "  gp2d.[MaxRetention] \r\n" +
            "FROM [GeoPosition2DTimeseriesView] gp2d \r\n";

    public final static String BaseViewName = "GeoPosition2DTimeseriesView";
    public final static String ViewAliasName = "gp2d";

    public SimpleGeoPosition2DTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
