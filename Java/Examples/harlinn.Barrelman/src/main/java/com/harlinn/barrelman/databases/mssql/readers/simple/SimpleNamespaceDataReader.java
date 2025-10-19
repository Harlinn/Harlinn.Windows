package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleNamespaceDataReader extends SimpleNamespaceElementDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  n.[Id], \r\n" +
            "  n.[EntityType], \r\n" +
            "  n.[RowVersion], \r\n" +
            "  n.[Namespace], \r\n" +
            "  n.[Name], \r\n" +
            "  n.[Description] \r\n" +
            "FROM [NamespaceView] n \r\n";

    public final static String BaseViewName = "NamespaceView";
    public final static String ViewAliasName = "n";

    public SimpleNamespaceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public NamespaceObject getDataObject( ) throws SQLException {
        return new NamespaceObject( ObjectState.Stored, getId( ), getRowVersion( ), getNamespace( ), getName( ), getDescription( ) );
    }

}
