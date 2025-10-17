package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleItemIdentityLinkDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  iil.[Id], \r\n" +
            "  iil.[RowVersion], \r\n" +
            "  iil.[Item], \r\n" +
            "  iil.[Identity], \r\n" +
            "  iil.[Start], \r\n" +
            "  iil.[End] \r\n" +
            "FROM [ItemIdentityLinkView] iil \r\n";

    public final static String BaseViewName = "ItemIdentityLinkView";
    public final static String ViewAliasName = "iil";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int ITEM_FIELD_ID = 3;
    public final static int IDENTITY_FIELD_ID = 4;
    public final static int START_FIELD_ID = 5;
    public final static int END_FIELD_ID = 6;

    public SimpleItemIdentityLinkDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getItem() throws SQLException {
        return getGuid( ITEM_FIELD_ID );
    }

    public final Guid getIdentity() throws SQLException {
        return getGuid( IDENTITY_FIELD_ID );
    }

    public final DateTime getStart() throws SQLException {
        return getDateTimeFromLong( START_FIELD_ID );
    }

    public final DateTime getEnd() throws SQLException {
        return getNullableDateTimeFromLong( END_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.ItemIdentityLink );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getItem( ) );
        destination.writeGuid( getIdentity( ) );
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

}
