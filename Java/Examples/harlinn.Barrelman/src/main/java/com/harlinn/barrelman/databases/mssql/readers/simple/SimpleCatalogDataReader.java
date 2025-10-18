package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCatalogDataReader extends SimpleCatalogElementDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  c.[Id], \r\n" +
            "  c.[EntityType], \r\n" +
            "  c.[RowVersion], \r\n" +
            "  c.[Catalog], \r\n" +
            "  c.[Name] \r\n" +
            "FROM [CatalogView] c \r\n";

    public final static String BaseViewName = "CatalogView";
    public final static String ViewAliasName = "c";

    public SimpleCatalogDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public CatalogObject GetDataObject( ) throws SQLException {
        return new CatalogObject( ObjectState.Stored, getId( ), getRowVersion( ), getCatalog( ), getName( ) );
    }

}
