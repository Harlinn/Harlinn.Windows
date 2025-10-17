package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleUInt16PropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u16pd.[Id], \r\n" +
            "  u16pd.[EntityType], \r\n" +
            "  u16pd.[RowVersion], \r\n" +
            "  u16pd.[ElementType], \r\n" +
            "  u16pd.[Name], \r\n" +
            "  u16pd.[Description], \r\n" +
            "  u16pd.[DefaultValue], \r\n" +
            "  u16pd.[MinValue], \r\n" +
            "  u16pd.[MaxValue] \r\n" +
            "FROM [UInt16PropertyDefinitionView] u16pd \r\n";

    public final static String BaseViewName = "UInt16PropertyDefinitionView";
    public final static String ViewAliasName = "u16pd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;
    public final static int MINVALUE_FIELD_ID = 8;
    public final static int MAXVALUE_FIELD_ID = 9;

    public SimpleUInt16PropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final short getDefaultValue() throws SQLException {
        return getUInt16( DEFAULTVALUE_FIELD_ID );
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
        destination.writeUInt16( getDefaultValue( ) );
        destination.writeUInt16( getMinValue( ) );
        destination.writeUInt16( getMaxValue( ) );
    }

}
