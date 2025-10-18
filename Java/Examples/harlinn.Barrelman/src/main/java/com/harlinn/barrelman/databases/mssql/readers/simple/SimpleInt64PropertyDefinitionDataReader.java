package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInt64PropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i64pd.[Id], \r\n" +
            "  i64pd.[EntityType], \r\n" +
            "  i64pd.[RowVersion], \r\n" +
            "  i64pd.[ElementType], \r\n" +
            "  i64pd.[Name], \r\n" +
            "  i64pd.[Description], \r\n" +
            "  i64pd.[DefaultValue], \r\n" +
            "  i64pd.[MinValue], \r\n" +
            "  i64pd.[MaxValue] \r\n" +
            "FROM [Int64PropertyDefinitionView] i64pd \r\n";

    public final static String BaseViewName = "Int64PropertyDefinitionView";
    public final static String ViewAliasName = "i64pd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;
    public final static int MINVALUE_FIELD_ID = 8;
    public final static int MAXVALUE_FIELD_ID = 9;

    public SimpleInt64PropertyDefinitionDataReader( ResultSet resultSet ) {
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

    @Override
    public Int64PropertyDefinitionObject GetDataObject( ) throws SQLException {
        return new Int64PropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ), getMinValue( ), getMaxValue( ) );
    }

}
