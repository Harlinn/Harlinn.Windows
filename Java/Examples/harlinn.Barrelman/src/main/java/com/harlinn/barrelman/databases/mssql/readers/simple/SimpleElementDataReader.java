package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleElementDataReader extends SimpleCatalogElementDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  e.[Id], \r\n" +
            "  e.[EntityType], \r\n" +
            "  e.[RowVersion], \r\n" +
            "  e.[Catalog], \r\n" +
            "  e.[Name], \r\n" +
            "  e.[ElementType] \r\n" +
            "FROM [ElementView] e \r\n";

    public final static String BaseViewName = "ElementView";
    public final static String ViewAliasName = "e";

    public final static int ELEMENTTYPE_FIELD_ID = 6;

    public SimpleElementDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getElementType() throws SQLException {
        return getNullableGuid( ELEMENTTYPE_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeNullableGuid( getElementType( ) );
    }

}
