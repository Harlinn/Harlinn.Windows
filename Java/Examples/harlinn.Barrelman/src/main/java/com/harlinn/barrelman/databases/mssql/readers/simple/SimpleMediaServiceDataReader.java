package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleMediaServiceDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ms.[Id], \r\n" +
            "  ms.[RowVersion], \r\n" +
            "  ms.[EnabledTimeseries] \r\n" +
            "FROM [MediaServiceView] ms \r\n";

    public final static String BaseViewName = "MediaServiceView";
    public final static String ViewAliasName = "ms";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int ENABLEDTIMESERIES_FIELD_ID = 3;

    public SimpleMediaServiceDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getEnabledTimeseries() throws SQLException {
        return getNullableGuid( ENABLEDTIMESERIES_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.MediaService );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeNullableGuid( getEnabledTimeseries( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
