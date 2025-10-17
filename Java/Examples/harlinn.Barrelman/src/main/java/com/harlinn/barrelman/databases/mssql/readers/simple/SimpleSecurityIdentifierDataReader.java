package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class SimpleSecurityIdentifierDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  si.[Id], \r\n" +
            "  si.[EntityType], \r\n" +
            "  si.[RowVersion], \r\n" +
            "  si.[Domain], \r\n" +
            "  si.[Identity], \r\n" +
            "  si.[Description] \r\n" +
            "FROM [SecurityIdentifierView] si \r\n";

    public final static String BaseViewName = "SecurityIdentifierView";
    public final static String ViewAliasName = "si";

    public final static int ID_FIELD_ID = 1;
    public final static int ENTITYTYPE_FIELD_ID = 2;
    public final static int ROWVERSION_FIELD_ID = 3;
    public final static int DOMAIN_FIELD_ID = 4;
    public final static int IDENTITY_FIELD_ID = 5;
    public final static int DESCRIPTION_FIELD_ID = 6;

    public SimpleSecurityIdentifierDataReader( ResultSet resultSet ) {
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

    public final Guid getDomain() throws SQLException {
        return getGuid( DOMAIN_FIELD_ID );
    }

    public final String getIdentity() throws SQLException {
        return getString( IDENTITY_FIELD_ID );
    }

    public final String getDescription() throws SQLException {
        return getString( DESCRIPTION_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.SecurityIdentifier );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getDomain( ) );
        destination.writeStringUtf8( getIdentity( ) );
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
