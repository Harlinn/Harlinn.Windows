package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTimeseriesCatalogDataReader extends SimpleTimeseriesCatalogElementDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  tc.[Id], \r\n" +
            "  tc.[EntityType], \r\n" +
            "  tc.[RowVersion], \r\n" +
            "  tc.[Catalog], \r\n" +
            "  tc.[Name] \r\n" +
            "FROM [TimeseriesCatalogView] tc \r\n";

    public final static String BaseViewName = "TimeseriesCatalogView";
    public final static String ViewAliasName = "tc";

    public SimpleTimeseriesCatalogDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

}
