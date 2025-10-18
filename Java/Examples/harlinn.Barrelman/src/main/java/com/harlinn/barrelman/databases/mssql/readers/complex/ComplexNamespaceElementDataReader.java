package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexNamespaceElementDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  ne.[Id], \r\n" +
            "  ne.[EntityType], \r\n" +
            "  ne.[RowVersion], \r\n" +
            "  ne.[Namespace], \r\n" +
            "  ne.[Name], \r\n" +
            "  ne.[Description] \r\n" +
            "FROM [NamespaceElementView] ne \r\n" +
            "  LEFT JOIN [ElementType] et ON(ne.[Id] = et.[Id] ) \r\n" +
            "  LEFT JOIN [Namespace] n ON(ne.[Id] = n.[Id] ) \r\n";

    public final static String BaseViewName = "NamespaceElementView";
    public final static String ViewAliasName = "ne";

    public final static int NE_ID_FIELD_ID = 1;
    public final static int NE_KIND_FIELD_ID = 2;
    public final static int NE_ROWVERSION_FIELD_ID = 3;
    public final static int NE_NAMESPACE_FIELD_ID = 4;
    public final static int NE_NAME_FIELD_ID = 5;
    public final static int NE_DESCRIPTION_FIELD_ID = 6;

    public ComplexNamespaceElementDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( NE_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( NE_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( NE_ROWVERSION_FIELD_ID );
    }

    public Guid getNamespace( ) throws SQLException {
        return getGuid( NE_NAMESPACE_FIELD_ID );
    }

    public String getName( ) throws SQLException {
        return getString( NE_NAME_FIELD_ID );
    }

    public String getDescription( ) throws SQLException {
        return getString( NE_DESCRIPTION_FIELD_ID );
    }

}

