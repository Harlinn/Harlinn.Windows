package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadomeDewPointTimeseriesDataReader extends SimpleDoubleTimeseriesDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  rdpt.[Id], \r\n" +
            "  rdpt.[EntityType], \r\n" +
            "  rdpt.[RowVersion], \r\n" +
            "  rdpt.[Catalog], \r\n" +
            "  rdpt.[Name], \r\n" +
            "  rdpt.[MaxRetention], \r\n" +
            "  rdpt.[Radome] \r\n" +
            "FROM [RadomeDewPointTimeseriesView] rdpt \r\n";

    public final static String BaseViewName = "RadomeDewPointTimeseriesView";
    public final static String ViewAliasName = "rdpt";

    public final static int RADOME_FIELD_ID = 7;

    public SimpleRadomeDewPointTimeseriesDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getRadome() throws SQLException {
        return getNullableGuid( RADOME_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getRadome( ) );
    }

}
