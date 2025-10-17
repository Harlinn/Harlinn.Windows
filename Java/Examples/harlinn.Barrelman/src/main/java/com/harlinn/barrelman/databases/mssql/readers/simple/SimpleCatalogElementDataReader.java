package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimpleCatalogElementDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ce.[Id], \r\n" +
            "  ce.[EntityType], \r\n" +
            "  ce.[RowVersion], \r\n" +
            "  ce.[Catalog], \r\n" +
            "  ce.[Name] \r\n" +
            "FROM [CatalogElementView] ce \r\n";

    public final static String BaseViewName = "CatalogElementView";
    public final static String ViewAliasName = "ce";

    public final static int ID_FIELD_ID = 1;
    public final static int ENTITYTYPE_FIELD_ID = 2;
    public final static int ROWVERSION_FIELD_ID = 3;
    public final static int CATALOG_FIELD_ID = 4;
    public final static int NAME_FIELD_ID = 5;

    public SimpleCatalogElementDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final int getObjectType() throws SQLException {
        return getInt32( ENTITYTYPE_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getCatalog() throws SQLException {
        return getNullableGuid( CATALOG_FIELD_ID );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.CatalogElement );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeNullableGuid( getCatalog( ) );
        destination.writeStringUtf8( getName( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
