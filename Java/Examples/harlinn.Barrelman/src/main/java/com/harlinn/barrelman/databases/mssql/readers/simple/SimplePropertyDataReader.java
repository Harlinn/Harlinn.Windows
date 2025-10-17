package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimplePropertyDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  p.[Id], \r\n" +
            "  p.[EntityType], \r\n" +
            "  p.[RowVersion], \r\n" +
            "  p.[Element], \r\n" +
            "  p.[Definition] \r\n" +
            "FROM [PropertyView] p \r\n";

    public final static String BaseViewName = "PropertyView";
    public final static String ViewAliasName = "p";

    public final static int ID_FIELD_ID = 1;
    public final static int ENTITYTYPE_FIELD_ID = 2;
    public final static int ROWVERSION_FIELD_ID = 3;
    public final static int ELEMENT_FIELD_ID = 4;
    public final static int DEFINITION_FIELD_ID = 5;

    public SimplePropertyDataReader( ResultSet resultSet ) {
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

    public final Guid getElement() throws SQLException {
        return getGuid( ELEMENT_FIELD_ID );
    }

    public final Guid getDefinition() throws SQLException {
        return getGuid( DEFINITION_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.Property );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getElement( ) );
        destination.writeGuid( getDefinition( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
