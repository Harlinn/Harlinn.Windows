package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleBinaryTimeseriesValueDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  btv.[Id], \r\n" +
            "  btv.[RowVersion], \r\n" +
            "  btv.[Timeseries], \r\n" +
            "  btv.[Timestamp], \r\n" +
            "  btv.[Value] \r\n" +
            "FROM [BinaryTimeseriesValueView] btv \r\n";

    public final static String BaseViewName = "BinaryTimeseriesValueView";
    public final static String ViewAliasName = "btv";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int TIMESERIES_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int VALUE_FIELD_ID = 5;

    public SimpleBinaryTimeseriesValueDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getTimeseries() throws SQLException {
        return getGuid( TIMESERIES_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final byte[] getValue() throws SQLException {
        return getBinary( VALUE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.BinaryTimeseriesValue );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getTimeseries( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeUInt8Array( getValue( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
