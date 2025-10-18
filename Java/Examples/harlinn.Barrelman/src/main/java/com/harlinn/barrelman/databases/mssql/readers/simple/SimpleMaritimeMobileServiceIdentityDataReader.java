package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleMaritimeMobileServiceIdentityDataReader extends SimpleIdentityDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  mmsi.[Id], \r\n" +
            "  mmsi.[EntityType], \r\n" +
            "  mmsi.[RowVersion], \r\n" +
            "  mmsi.[Identifier] \r\n" +
            "FROM [MaritimeMobileServiceIdentityView] mmsi \r\n";

    public final static String BaseViewName = "MaritimeMobileServiceIdentityView";
    public final static String ViewAliasName = "mmsi";

    public final static int IDENTIFIER_FIELD_ID = 4;

    public SimpleMaritimeMobileServiceIdentityDataReader( ResultSet resultSet ) {
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
    public MaritimeMobileServiceIdentityObject GetDataObject( ) throws SQLException {
        return new MaritimeMobileServiceIdentityObject( ObjectState.Stored, getId( ), getRowVersion( ), getIdentifier( ) );
    }

}
