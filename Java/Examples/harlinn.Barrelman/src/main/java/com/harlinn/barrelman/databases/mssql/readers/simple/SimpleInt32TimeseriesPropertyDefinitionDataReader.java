package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInt32TimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i32tpd.[Id], \r\n" +
            "  i32tpd.[EntityType], \r\n" +
            "  i32tpd.[RowVersion], \r\n" +
            "  i32tpd.[ElementType], \r\n" +
            "  i32tpd.[Name], \r\n" +
            "  i32tpd.[Description], \r\n" +
            "  i32tpd.[MinValue], \r\n" +
            "  i32tpd.[MaxValue] \r\n" +
            "FROM [Int32TimeseriesPropertyDefinitionView] i32tpd \r\n";

    public final static String BaseViewName = "Int32TimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "i32tpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleInt32TimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getMinValue() throws SQLException {
        return getInt32( MINVALUE_FIELD_ID );
    }

    public final int getMaxValue() throws SQLException {
        return getInt32( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getMinValue( ) );
        destination.writeInt32( getMaxValue( ) );
    }

}
