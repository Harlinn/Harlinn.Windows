package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleElementTypeDataReader extends SimpleNamespaceElementDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  et.[Id], \r\n" +
            "  et.[EntityType], \r\n" +
            "  et.[RowVersion], \r\n" +
            "  et.[Namespace], \r\n" +
            "  et.[Name], \r\n" +
            "  et.[Description] \r\n" +
            "FROM [ElementTypeView] et \r\n";

    public final static String BaseViewName = "ElementTypeView";
    public final static String ViewAliasName = "et";

    public SimpleElementTypeDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public ElementTypeObject GetDataObject( ) throws SQLException {
        return new ElementTypeObject( ObjectState.Stored, getId( ), getRowVersion( ), getNamespace( ), getName( ), getDescription( ) );
    }

}
