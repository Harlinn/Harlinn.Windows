package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleSBytePropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sbpd.[Id], \r\n" +
            "  sbpd.[EntityType], \r\n" +
            "  sbpd.[RowVersion], \r\n" +
            "  sbpd.[ElementType], \r\n" +
            "  sbpd.[Name], \r\n" +
            "  sbpd.[Description], \r\n" +
            "  sbpd.[DefaultValue], \r\n" +
            "  sbpd.[MinValue], \r\n" +
            "  sbpd.[MaxValue] \r\n" +
            "FROM [SBytePropertyDefinitionView] sbpd \r\n";

    public final static String BaseViewName = "SBytePropertyDefinitionView";
    public final static String ViewAliasName = "sbpd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;
    public final static int MINVALUE_FIELD_ID = 8;
    public final static int MAXVALUE_FIELD_ID = 9;

    public SimpleSBytePropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final byte getDefaultValue() throws SQLException {
        return getInt8( DEFAULTVALUE_FIELD_ID );
    }

    public final byte getMinValue() throws SQLException {
        return getInt8( MINVALUE_FIELD_ID );
    }

    public final byte getMaxValue() throws SQLException {
        return getInt8( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt8( getDefaultValue( ) );
        destination.writeInt8( getMinValue( ) );
        destination.writeInt8( getMaxValue( ) );
    }

    @Override
    public SBytePropertyDefinitionObject getDataObject( ) throws SQLException {
        return new SBytePropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ), getMinValue( ), getMaxValue( ) );
    }

}
