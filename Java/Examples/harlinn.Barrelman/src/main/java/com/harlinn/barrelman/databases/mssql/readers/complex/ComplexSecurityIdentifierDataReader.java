package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexSecurityIdentifierDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  si.[Id], \r\n" +
            "  si.[EntityType], \r\n" +
            "  si.[RowVersion], \r\n" +
            "  si.[Domain], \r\n" +
            "  si.[Identity], \r\n" +
            "  sr.[Name], \r\n" +
            "  si.[Description] \r\n" +
            "FROM [SecurityIdentifierView] si \r\n" +
            "  LEFT JOIN [SecurityLogin] sl ON(si.[Id] = sl.[Id] ) \r\n" +
            "  LEFT JOIN [SecurityRole] sr ON(si.[Id] = sr.[Id] ) \r\n";

    public final static String BaseViewName = "SecurityIdentifierView";
    public final static String ViewAliasName = "si";

    public final static int SI_ID_FIELD_ID = 1;
    public final static int SI_KIND_FIELD_ID = 2;
    public final static int SI_ROWVERSION_FIELD_ID = 3;
    public final static int SI_DOMAIN_FIELD_ID = 4;
    public final static int SI_IDENTITY_FIELD_ID = 5;
    public final static int SR_NAME_FIELD_ID = 6;
    public final static int SI_DESCRIPTION_FIELD_ID = 7;

    public ComplexSecurityIdentifierDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( SI_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( SI_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( SI_ROWVERSION_FIELD_ID );
    }

    public Guid getDomain( ) throws SQLException {
        return getGuid( SI_DOMAIN_FIELD_ID );
    }

    public String getIdentity( ) throws SQLException {
        return getString( SI_IDENTITY_FIELD_ID );
    }

    public String getDescription( ) throws SQLException {
        return getString( SI_DESCRIPTION_FIELD_ID );
    }

    public String getSecurityRoleName( ) throws SQLException {
        return getString( SR_NAME_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.SecurityLogin: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getDomain( ) );
                destination.writeStringUtf8( getIdentity( ) );
                destination.writeStringUtf8( getDescription( ) );
            }
            break;
            case Kind.SecurityRole: {
                destination.writeInt32( kind );
                destination.writeUInt8( ObjectState.Stored );
                destination.writeGuid( getId( ) );
                destination.writeInt64( getRowVersion( ) );
                destination.writeGuid( getDomain( ) );
                destination.writeStringUtf8( getIdentity( ) );
                destination.writeStringUtf8( getDescription( ) );
                destination.writeStringUtf8( getSecurityRoleName( ) );
            }
            break;
            default: {
                var exc = new SQLException( "Cannot perform serialization for kind=" + kind + "." );
                throw exc;
            }
        }
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public SecurityIdentifierObject getDataObject( ) throws SQLException {
        var kind = getObjectType( );
        switch(kind) {
            case Kind.SecurityLogin: {
                return new SecurityLoginObject( ObjectState.Stored, getId( ), getRowVersion( ), getDomain( ), getIdentity( ), getDescription( ) );
            }
            case Kind.SecurityRole: {
                return new SecurityRoleObject( ObjectState.Stored, getId( ), getRowVersion( ), getDomain( ), getIdentity( ), getDescription( ), getSecurityRoleName( ) );
            }
            default: {
                var exc = new SQLException( "Cannot create an object for kind=" + kind + "." );
                throw exc;
            }
        }
    }

}

