package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleSinglePropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sipd.[Id], \r\n" +
            "  sipd.[EntityType], \r\n" +
            "  sipd.[RowVersion], \r\n" +
            "  sipd.[ElementType], \r\n" +
            "  sipd.[Name], \r\n" +
            "  sipd.[Description], \r\n" +
            "  sipd.[DefaultValue], \r\n" +
            "  sipd.[MinValue], \r\n" +
            "  sipd.[MaxValue] \r\n" +
            "FROM [SinglePropertyDefinitionView] sipd \r\n";

    public final static String BaseViewName = "SinglePropertyDefinitionView";
    public final static String ViewAliasName = "sipd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;
    public final static int MINVALUE_FIELD_ID = 8;
    public final static int MAXVALUE_FIELD_ID = 9;

    public SimpleSinglePropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final float getDefaultValue() throws SQLException {
        return getSingle( DEFAULTVALUE_FIELD_ID );
    }

    public final float getMinValue() throws SQLException {
        return getSingle( MINVALUE_FIELD_ID );
    }

    public final float getMaxValue() throws SQLException {
        return getSingle( MAXVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeSingle( getDefaultValue( ) );
        destination.writeSingle( getMinValue( ) );
        destination.writeSingle( getMaxValue( ) );
    }

}
