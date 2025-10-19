package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleMediaProxySessionDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  mps.[Id], \r\n" +
            "  mps.[RowVersion], \r\n" +
            "  mps.[Service], \r\n" +
            "  mps.[Name], \r\n" +
            "  mps.[EnabledTimeseries] \r\n" +
            "FROM [MediaProxySessionView] mps \r\n";

    public final static String BaseViewName = "MediaProxySessionView";
    public final static String ViewAliasName = "mps";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int SERVICE_FIELD_ID = 3;
    public final static int NAME_FIELD_ID = 4;
    public final static int ENABLEDTIMESERIES_FIELD_ID = 5;

    public SimpleMediaProxySessionDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getService() throws SQLException {
        return getGuid( SERVICE_FIELD_ID );
    }

    public final String getName() throws SQLException {
        return getString( NAME_FIELD_ID );
    }

    public final Guid getEnabledTimeseries() throws SQLException {
        return getNullableGuid( ENABLEDTIMESERIES_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.MediaProxySession );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getService( ) );
        destination.writeStringUtf8( getName( ) );
        destination.writeNullableGuid( getEnabledTimeseries( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public MediaProxySessionObject getDataObject( ) throws SQLException {
            return new MediaProxySessionObject( ObjectState.Stored, getId( ), getRowVersion( ), getService( ), getName( ), getEnabledTimeseries( ) );
    }

}
