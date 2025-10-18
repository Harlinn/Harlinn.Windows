package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleStringPropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  stpd.[Id], \r\n" +
            "  stpd.[EntityType], \r\n" +
            "  stpd.[RowVersion], \r\n" +
            "  stpd.[ElementType], \r\n" +
            "  stpd.[Name], \r\n" +
            "  stpd.[Description], \r\n" +
            "  stpd.[DefaultValue], \r\n" +
            "  stpd.[Pattern] \r\n" +
            "FROM [StringPropertyDefinitionView] stpd \r\n";

    public final static String BaseViewName = "StringPropertyDefinitionView";
    public final static String ViewAliasName = "stpd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;
    public final static int PATTERN_FIELD_ID = 8;

    public SimpleStringPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getDefaultValue() throws SQLException {
        return getString( DEFAULTVALUE_FIELD_ID );
    }

    public final String getPattern() throws SQLException {
        return getString( PATTERN_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getDefaultValue( ) );
        destination.writeStringUtf8( getPattern( ) );
    }

    @Override
    public StringPropertyDefinitionObject GetDataObject( ) throws SQLException {
        return new StringPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ), getPattern( ) );
    }

}
