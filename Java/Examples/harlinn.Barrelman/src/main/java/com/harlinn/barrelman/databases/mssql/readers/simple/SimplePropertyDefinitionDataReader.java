package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimplePropertyDefinitionDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  pd.[Id], \r\n" +
            "  pd.[EntityType], \r\n" +
            "  pd.[RowVersion], \r\n" +
            "  pd.[ElementType], \r\n" +
            "  pd.[Name], \r\n" +
            "  pd.[Description] \r\n" +
            "FROM [PropertyDefinitionView] pd \r\n";

    public final static String BaseViewName = "PropertyDefinitionView";
    public final static String ViewAliasName = "pd";

    public final static int ID_FIELD_ID = 1;
    public final static int ENTITYTYPE_FIELD_ID = 2;
    public final static int ROWVERSION_FIELD_ID = 3;
    public final static int ELEMENTTYPE_FIELD_ID = 4;
    public final static int NAME_FIELD_ID = 5;
    public final static int DESCRIPTION_FIELD_ID = 6;

    public SimplePropertyDefinitionDataReader( ResultSet resultSet ) {
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

    public final Guid getElementType() throws SQLException {
        return getGuid( ELEMENTTYPE_FIELD_ID );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final String getDescription() throws SQLException {
        return getString( DESCRIPTION_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.PropertyDefinition );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getElementType( ) );
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

    public abstract PropertyDefinitionObject getDataObject( ) throws SQLException;

}
