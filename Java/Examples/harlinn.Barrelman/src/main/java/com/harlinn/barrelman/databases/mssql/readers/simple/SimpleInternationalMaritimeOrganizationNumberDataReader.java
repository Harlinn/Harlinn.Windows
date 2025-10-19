package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInternationalMaritimeOrganizationNumberDataReader extends SimpleIdentityDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  imon.[Id], \r\n" +
            "  imon.[EntityType], \r\n" +
            "  imon.[RowVersion], \r\n" +
            "  imon.[Identifier] \r\n" +
            "FROM [InternationalMaritimeOrganizationNumberView] imon \r\n";

    public final static String BaseViewName = "InternationalMaritimeOrganizationNumberView";
    public final static String ViewAliasName = "imon";

    public final static int IDENTIFIER_FIELD_ID = 4;

    public SimpleInternationalMaritimeOrganizationNumberDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final long getIdentifier() throws SQLException {
        return getInt64( IDENTIFIER_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt64( getIdentifier( ) );
    }

    @Override
    public InternationalMaritimeOrganizationNumberObject getDataObject( ) throws SQLException {
        return new InternationalMaritimeOrganizationNumberObject( ObjectState.Stored, getId( ), getRowVersion( ), getIdentifier( ) );
    }

}
