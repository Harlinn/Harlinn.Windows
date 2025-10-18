package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleSecurityRoleDataReader extends SimpleSecurityIdentifierDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sr.[Id], \r\n" +
            "  sr.[EntityType], \r\n" +
            "  sr.[RowVersion], \r\n" +
            "  sr.[Domain], \r\n" +
            "  sr.[Identity], \r\n" +
            "  sr.[Description], \r\n" +
            "  sr.[Name] \r\n" +
            "FROM [SecurityRoleView] sr \r\n";

    public final static String BaseViewName = "SecurityRoleView";
    public final static String ViewAliasName = "sr";

    public final static int NAME_FIELD_ID = 7;

    public SimpleSecurityRoleDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getName( ) );
    }

    @Override
    public SecurityRoleObject GetDataObject( ) throws SQLException {
        return new SecurityRoleObject( ObjectState.Stored, getId( ), getRowVersion( ), getDomain( ), getIdentity( ), getDescription( ), getName( ) );
    }

}
