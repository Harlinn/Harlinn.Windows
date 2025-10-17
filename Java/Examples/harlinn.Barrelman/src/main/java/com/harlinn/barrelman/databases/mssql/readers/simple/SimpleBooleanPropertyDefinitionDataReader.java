package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBooleanPropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  bopd.[Id], \r\n" +
            "  bopd.[EntityType], \r\n" +
            "  bopd.[RowVersion], \r\n" +
            "  bopd.[ElementType], \r\n" +
            "  bopd.[Name], \r\n" +
            "  bopd.[Description], \r\n" +
            "  bopd.[DefaultValue] \r\n" +
            "FROM [BooleanPropertyDefinitionView] bopd \r\n";

    public final static String BaseViewName = "BooleanPropertyDefinitionView";
    public final static String ViewAliasName = "bopd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;

    public SimpleBooleanPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final boolean getDefaultValue() throws SQLException {
        return getBoolean( DEFAULTVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeBoolean( getDefaultValue( ) );
    }

}
