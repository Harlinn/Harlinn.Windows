package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCollectionInfoDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ci.[Id], \r\n" +
            "  ci.[RowVersion], \r\n" +
            "  ci.[Count] \r\n" +
            "FROM [CollectionInfoView] ci \r\n";

    public final static String BaseViewName = "CollectionInfoView";
    public final static String ViewAliasName = "ci";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int COUNT_FIELD_ID = 3;

    public SimpleCollectionInfoDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final long getCount() throws SQLException {
        return getInt64( COUNT_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.CollectionInfo );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeInt64( getCount( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
