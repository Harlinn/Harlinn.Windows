package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleStringTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sttpd.[Id], \r\n" +
            "  sttpd.[EntityType], \r\n" +
            "  sttpd.[RowVersion], \r\n" +
            "  sttpd.[ElementType], \r\n" +
            "  sttpd.[Name], \r\n" +
            "  sttpd.[Description], \r\n" +
            "  sttpd.[Pattern] \r\n" +
            "FROM [StringTimeseriesPropertyDefinitionView] sttpd \r\n";

    public final static String BaseViewName = "StringTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "sttpd";

    public final static int PATTERN_FIELD_ID = 7;

    public SimpleStringTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getPattern() throws SQLException {
        return getString( PATTERN_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getPattern( ) );
    }

}
