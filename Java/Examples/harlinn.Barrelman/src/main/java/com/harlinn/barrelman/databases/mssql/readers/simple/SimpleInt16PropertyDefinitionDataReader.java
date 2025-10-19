package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInt16PropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i16pd.[Id], \r\n" +
            "  i16pd.[EntityType], \r\n" +
            "  i16pd.[RowVersion], \r\n" +
            "  i16pd.[ElementType], \r\n" +
            "  i16pd.[Name], \r\n" +
            "  i16pd.[Description], \r\n" +
            "  i16pd.[DefaultValue], \r\n" +
            "  i16pd.[MinValue], \r\n" +
            "  i16pd.[MaxValue] \r\n" +
            "FROM [Int16PropertyDefinitionView] i16pd \r\n";

    public final static String BaseViewName = "Int16PropertyDefinitionView";
    public final static String ViewAliasName = "i16pd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;
    public final static int MINVALUE_FIELD_ID = 8;
    public final static int MAXVALUE_FIELD_ID = 9;

    public SimpleInt16PropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final short getDefaultValue() throws SQLException {
        return getInt16( DEFAULTVALUE_FIELD_ID );
    }

    public final short getMinValue() throws SQLException {
        return getInt16( MINVALUE_FIELD_ID );
    }

    public final short getMaxValue() throws SQLException {
        return getInt16( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt16( getDefaultValue( ) );
        destination.writeInt16( getMinValue( ) );
        destination.writeInt16( getMaxValue( ) );
    }

    @Override
    public Int16PropertyDefinitionObject getDataObject( ) throws SQLException {
        return new Int16PropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ), getMinValue( ), getMaxValue( ) );
    }

}
