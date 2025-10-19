package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleItemParentChildLinkDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ipcl.[Id], \r\n" +
            "  ipcl.[RowVersion], \r\n" +
            "  ipcl.[Parent], \r\n" +
            "  ipcl.[Child], \r\n" +
            "  ipcl.[Timestamp] \r\n" +
            "FROM [ItemParentChildLinkView] ipcl \r\n";

    public final static String BaseViewName = "ItemParentChildLinkView";
    public final static String ViewAliasName = "ipcl";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int PARENT_FIELD_ID = 3;
    public final static int CHILD_FIELD_ID = 4;
    public final static int TIMESTAMP_FIELD_ID = 5;

    public SimpleItemParentChildLinkDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getParent() throws SQLException {
        return getGuid( PARENT_FIELD_ID );
    }

    public final Guid getChild() throws SQLException {
        return getGuid( CHILD_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.ItemParentChildLink );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getParent( ) );
        destination.writeGuid( getChild( ) );
        destination.writeDateTime( getTimestamp( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public ItemParentChildLinkObject getDataObject( ) throws SQLException {
            return new ItemParentChildLinkObject( ObjectState.Stored, getId( ), getRowVersion( ), getParent( ), getChild( ), getTimestamp( ) );
    }

}
