package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleDateTimeTimeseriesDataReader extends SimpleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  dtt.[Id], \r\n" +
            "  dtt.[EntityType], \r\n" +
            "  dtt.[RowVersion], \r\n" +
            "  dtt.[Catalog], \r\n" +
            "  dtt.[Name], \r\n" +
            "  dtt.[MaxRetention] \r\n" +
            "FROM [DateTimeTimeseriesView] dtt \r\n";

    public final static String BaseViewName = "DateTimeTimeseriesView";
    public final static String ViewAliasName = "dtt";

    public SimpleDateTimeTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
