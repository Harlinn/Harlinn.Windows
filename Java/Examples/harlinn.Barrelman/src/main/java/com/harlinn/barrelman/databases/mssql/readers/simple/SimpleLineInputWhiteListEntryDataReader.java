package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleLineInputWhiteListEntryDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  liwle.[Id], \r\n" +
            "  liwle.[RowVersion], \r\n" +
            "  liwle.[LineInputDevice], \r\n" +
            "  liwle.[HostName], \r\n" +
            "  liwle.[Port] \r\n" +
            "FROM [LineInputWhiteListEntryView] liwle \r\n";

    public final static String BaseViewName = "LineInputWhiteListEntryView";
    public final static String ViewAliasName = "liwle";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int LINEINPUTDEVICE_FIELD_ID = 3;
    public final static int HOSTNAME_FIELD_ID = 4;
    public final static int PORT_FIELD_ID = 5;

    public SimpleLineInputWhiteListEntryDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getLineInputDevice() throws SQLException {
        return getGuid( LINEINPUTDEVICE_FIELD_ID );
    }

    public final String getHostName() throws SQLException {
        return getString( HOSTNAME_FIELD_ID );
    }

    public final int getPort() throws SQLException {
        return getInt32( PORT_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.LineInputWhiteListEntry );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getLineInputDevice( ) );
        destination.writeStringUtf8( getHostName( ) );
        destination.writeInt32( getPort( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public LineInputWhiteListEntryObject GetDataObject( ) throws SQLException {
            return new LineInputWhiteListEntryObject( ObjectState.Stored, getId( ), getRowVersion( ), getLineInputDevice( ), getHostName( ), getPort( ) );
    }

}
