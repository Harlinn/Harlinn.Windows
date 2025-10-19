package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleSecurityDomainDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sd.[Id], \r\n" +
            "  sd.[RowVersion], \r\n" +
            "  sd.[Name], \r\n" +
            "  sd.[Description] \r\n" +
            "FROM [SecurityDomainView] sd \r\n";

    public final static String BaseViewName = "SecurityDomainView";
    public final static String ViewAliasName = "sd";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int NAME_FIELD_ID = 3;
    public final static int DESCRIPTION_FIELD_ID = 4;

    public SimpleSecurityDomainDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final String getDescription() throws SQLException {
        return getString( DESCRIPTION_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.SecurityDomain );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
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

    public SecurityDomainObject getDataObject( ) throws SQLException {
            return new SecurityDomainObject( ObjectState.Stored, getId( ), getRowVersion( ), getName( ), getDescription( ) );
    }

}
