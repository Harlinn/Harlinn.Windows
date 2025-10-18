package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCallsignDataReader extends SimpleIdentityDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  c.[Id], \r\n" +
            "  c.[EntityType], \r\n" +
            "  c.[RowVersion], \r\n" +
            "  c.[Identifier] \r\n" +
            "FROM [CallsignView] c \r\n";

    public final static String BaseViewName = "CallsignView";
    public final static String ViewAliasName = "c";

    public final static int IDENTIFIER_FIELD_ID = 4;

    public SimpleCallsignDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final String getIdentifier() throws SQLException {
        return getString( IDENTIFIER_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeStringUtf8( getIdentifier( ) );
    }

    @Override
    public CallsignObject GetDataObject( ) throws SQLException {
        return new CallsignObject( ObjectState.Stored, getId( ), getRowVersion( ), getIdentifier( ) );
    }

}
