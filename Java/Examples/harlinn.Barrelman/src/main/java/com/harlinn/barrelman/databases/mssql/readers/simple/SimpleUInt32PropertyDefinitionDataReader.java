package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleUInt32PropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  u32pd.[Id], \r\n" +
            "  u32pd.[EntityType], \r\n" +
            "  u32pd.[RowVersion], \r\n" +
            "  u32pd.[ElementType], \r\n" +
            "  u32pd.[Name], \r\n" +
            "  u32pd.[Description], \r\n" +
            "  u32pd.[DefaultValue], \r\n" +
            "  u32pd.[MinValue], \r\n" +
            "  u32pd.[MaxValue] \r\n" +
            "FROM [UInt32PropertyDefinitionView] u32pd \r\n";

    public final static String BaseViewName = "UInt32PropertyDefinitionView";
    public final static String ViewAliasName = "u32pd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;
    public final static int MINVALUE_FIELD_ID = 8;
    public final static int MAXVALUE_FIELD_ID = 9;

    public SimpleUInt32PropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getDefaultValue() throws SQLException {
        return getUInt32( DEFAULTVALUE_FIELD_ID );
    }

    public final int getMinValue() throws SQLException {
        return getUInt32( MINVALUE_FIELD_ID );
    }

    public final int getMaxValue() throws SQLException {
        return getUInt32( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeUInt32( getDefaultValue( ) );
        destination.writeUInt32( getMinValue( ) );
        destination.writeUInt32( getMaxValue( ) );
    }

    @Override
    public UInt32PropertyDefinitionObject GetDataObject( ) throws SQLException {
        return new UInt32PropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ), getMinValue( ), getMaxValue( ) );
    }

}
