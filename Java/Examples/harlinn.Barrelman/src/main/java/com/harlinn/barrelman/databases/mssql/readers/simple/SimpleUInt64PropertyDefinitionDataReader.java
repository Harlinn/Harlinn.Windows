package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleUInt64PropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u64pd.[Id], \r\n" +
            "  u64pd.[EntityType], \r\n" +
            "  u64pd.[RowVersion], \r\n" +
            "  u64pd.[ElementType], \r\n" +
            "  u64pd.[Name], \r\n" +
            "  u64pd.[Description], \r\n" +
            "  u64pd.[DefaultValue], \r\n" +
            "  u64pd.[MinValue], \r\n" +
            "  u64pd.[MaxValue] \r\n" +
            "FROM [UInt64PropertyDefinitionView] u64pd \r\n";

    public final static String BaseViewName = "UInt64PropertyDefinitionView";
    public final static String ViewAliasName = "u64pd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;
    public final static int MINVALUE_FIELD_ID = 8;
    public final static int MAXVALUE_FIELD_ID = 9;

    public SimpleUInt64PropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final long getDefaultValue() throws SQLException {
        return getInt64( DEFAULTVALUE_FIELD_ID );
    }

    public final long getMinValue() throws SQLException {
        return getInt64( MINVALUE_FIELD_ID );
    }

    public final long getMaxValue() throws SQLException {
        return getInt64( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt64( getDefaultValue( ) );
        destination.writeInt64( getMinValue( ) );
        destination.writeInt64( getMaxValue( ) );
    }

}
