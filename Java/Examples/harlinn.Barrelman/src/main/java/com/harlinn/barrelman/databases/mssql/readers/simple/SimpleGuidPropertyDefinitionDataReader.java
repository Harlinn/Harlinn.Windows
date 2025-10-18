package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleGuidPropertyDefinitionDataReader extends SimplePropertyDefinitionDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  gpd.[Id], \r\n" +
            "  gpd.[EntityType], \r\n" +
            "  gpd.[RowVersion], \r\n" +
            "  gpd.[ElementType], \r\n" +
            "  gpd.[Name], \r\n" +
            "  gpd.[Description], \r\n" +
            "  gpd.[DefaultValue] \r\n" +
            "FROM [GuidPropertyDefinitionView] gpd \r\n";

    public final static String BaseViewName = "GuidPropertyDefinitionView";
    public final static String ViewAliasName = "gpd";

    public final static int DEFAULTVALUE_FIELD_ID = 7;

    public SimpleGuidPropertyDefinitionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getDefaultValue() throws SQLException {
        return getGuid( DEFAULTVALUE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeGuid( getDefaultValue( ) );
    }

    @Override
    public GuidPropertyDefinitionObject GetDataObject( ) throws SQLException {
        return new GuidPropertyDefinitionObject( ObjectState.Stored, getId( ), getRowVersion( ), getElementType( ), getName( ), getDescription( ), getDefaultValue( ) );
    }

}
