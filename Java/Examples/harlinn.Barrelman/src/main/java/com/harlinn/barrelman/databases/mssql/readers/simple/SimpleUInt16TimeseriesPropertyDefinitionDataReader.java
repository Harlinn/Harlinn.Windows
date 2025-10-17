package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleUInt16TimeseriesPropertyDefinitionDataReader extends SimpleTimeseriesPropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u16tpd.[Id], \r\n" +
            "  u16tpd.[EntityType], \r\n" +
            "  u16tpd.[RowVersion], \r\n" +
            "  u16tpd.[ElementType], \r\n" +
            "  u16tpd.[Name], \r\n" +
            "  u16tpd.[Description], \r\n" +
            "  u16tpd.[MinValue], \r\n" +
            "  u16tpd.[MaxValue] \r\n" +
            "FROM [UInt16TimeseriesPropertyDefinitionView] u16tpd \r\n";

    public final static String BaseViewName = "UInt16TimeseriesPropertyDefinitionView";
    public final static String ViewAliasName = "u16tpd";

    public final static int MINVALUE_FIELD_ID = 7;
    public final static int MAXVALUE_FIELD_ID = 8;

    public SimpleUInt16TimeseriesPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final short getMinValue() throws SQLException {
        return getUInt16( MINVALUE_FIELD_ID );
    }

    public final short getMaxValue() throws SQLException {
        return getUInt16( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeUInt16( getMinValue( ) );
        destination.writeUInt16( getMaxValue( ) );
    }

}
