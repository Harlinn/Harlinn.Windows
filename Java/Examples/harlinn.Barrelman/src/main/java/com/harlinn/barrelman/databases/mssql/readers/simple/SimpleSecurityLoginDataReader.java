package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleSecurityLoginDataReader extends SimpleSecurityIdentifierDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  sl.[Id], \r\n" +
            "  sl.[EntityType], \r\n" +
            "  sl.[RowVersion], \r\n" +
            "  sl.[Domain], \r\n" +
            "  sl.[Identity], \r\n" +
            "  sl.[Description] \r\n" +
            "FROM [SecurityLoginView] sl \r\n";

    public final static String BaseViewName = "SecurityLoginView";
    public final static String ViewAliasName = "sl";

    public SimpleSecurityLoginDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
    }

    @Override
    public SecurityLoginObject getDataObject( ) throws SQLException {
        return new SecurityLoginObject( ObjectState.Stored, getId( ), getRowVersion( ), getDomain( ), getIdentity( ), getDescription( ) );
    }

}
