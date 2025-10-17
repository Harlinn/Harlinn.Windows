package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimpleNamespaceElementDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ne.[Id], \r\n" +
            "  ne.[EntityType], \r\n" +
            "  ne.[RowVersion], \r\n" +
            "  ne.[Namespace], \r\n" +
            "  ne.[Name], \r\n" +
            "  ne.[Description] \r\n" +
            "FROM [NamespaceElementView] ne \r\n";

    public final static String BaseViewName = "NamespaceElementView";
    public final static String ViewAliasName = "ne";

    public final static int ID_FIELD_ID = 1;
    public final static int ENTITYTYPE_FIELD_ID = 2;
    public final static int ROWVERSION_FIELD_ID = 3;
    public final static int NAMESPACE_FIELD_ID = 4;
    public final static int NAME_FIELD_ID = 5;
    public final static int DESCRIPTION_FIELD_ID = 6;

    public SimpleNamespaceElementDataReader( ResultSet resultSet ) {
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

    public final Guid getNamespace() throws SQLException {
        return getGuid( NAMESPACE_FIELD_ID );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final String getDescription() throws SQLException {
        return getString( DESCRIPTION_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.NamespaceElement );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getNamespace( ) );
        destination.writeStringUtf8( getName( ) );
        destination.writeStringUtf8( getDescription( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
