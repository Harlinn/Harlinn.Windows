package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleSecurityIdentifierRoleLinkDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sirl.[Id], \r\n" +
            "  sirl.[RowVersion], \r\n" +
            "  sirl.[Member], \r\n" +
            "  sirl.[Role], \r\n" +
            "  sirl.[Start], \r\n" +
            "  sirl.[End] \r\n" +
            "FROM [SecurityIdentifierRoleLinkView] sirl \r\n";

    public final static String BaseViewName = "SecurityIdentifierRoleLinkView";
    public final static String ViewAliasName = "sirl";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int MEMBER_FIELD_ID = 3;
    public final static int ROLE_FIELD_ID = 4;
    public final static int START_FIELD_ID = 5;
    public final static int END_FIELD_ID = 6;

    public SimpleSecurityIdentifierRoleLinkDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getMember() throws SQLException {
        return getGuid( MEMBER_FIELD_ID );
    }

    public final Guid getRole() throws SQLException {
        return getGuid( ROLE_FIELD_ID );
    }

    public final DateTime getStart() throws SQLException {
        return getDateTimeFromLong( START_FIELD_ID );
    }

    public final DateTime getEnd() throws SQLException {
        return getNullableDateTimeFromLong( END_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.SecurityIdentifierRoleLink );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getMember( ) );
        destination.writeGuid( getRole( ) );
        destination.writeDateTime( getStart( ) );
        destination.writeNullableDateTime( getEnd( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public SecurityIdentifierRoleLinkObject getDataObject( ) throws SQLException {
            return new SecurityIdentifierRoleLinkObject( ObjectState.Stored, getId( ), getRowVersion( ), getMember( ), getRole( ), getStart( ), getEnd( ) );
    }

}
