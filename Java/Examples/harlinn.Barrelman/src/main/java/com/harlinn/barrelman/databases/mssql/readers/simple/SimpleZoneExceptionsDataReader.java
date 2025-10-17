package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleZoneExceptionsDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ze.[Id], \r\n" +
            "  ze.[RowVersion], \r\n" +
            "  ze.[Zone], \r\n" +
            "  ze.[Timestamp] \r\n" +
            "FROM [ZoneExceptionsView] ze \r\n";

    public final static String BaseViewName = "ZoneExceptionsView";
    public final static String ViewAliasName = "ze";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int ZONE_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;

    public SimpleZoneExceptionsDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getZone() throws SQLException {
        return getGuid( ZONE_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.ZoneExceptions );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getZone( ) );
        destination.writeDateTime( getTimestamp( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
