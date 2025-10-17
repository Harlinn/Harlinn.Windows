package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleDateTimeTimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  dttpd.[Id], \r\n" +
            "  dttpd.[EntityType], \r\n" +
            "  dttpd.[RowVersion], \r\n" +
            "  dttpd.[ElementType], \r\n" +
            "  dttpd.[Name], \r\n" +
            "  dttpd.[Description], \r\n" +
            "  dttpd.[MinValue], \r\n" +
            "  dttpd.[MaxValue] \r\n" +
            "FROM [DateTimeTimeseriesPropertyDefinitionView] dttpd \r\n";

    public final static String BaseViewName = "DateTimeTimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "dttpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleDateTimeTimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getMinValue() throws SQLException {
        return getString( MINVALUE_FIELD_ID );
    }

    public final String getMaxValue() throws SQLException {
        return getString( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getMinValue( ) );
        destination.writeStringUtf8( getMaxValue( ) );
    }

}
