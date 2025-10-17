package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleInt32TimeseriesValueDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  i32tv.[Id], \r\n" +
            "  i32tv.[RowVersion], \r\n" +
            "  i32tv.[Timeseries], \r\n" +
            "  i32tv.[Timestamp], \r\n" +
            "  i32tv.[Value] \r\n" +
            "FROM [Int32TimeseriesValueView] i32tv \r\n";

    public final static String BaseViewName = "Int32TimeseriesValueView";
    public final static String ViewAliasName = "i32tv";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int TIMESERIES_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int VALUE_FIELD_ID = 5;

    public SimpleInt32TimeseriesValueDataReader( ResultSet resultSet ) {
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

    public final Integer getValue() throws SQLException {
        return getNullableInt32( VALUE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.Int32TimeseriesValue );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getTimeseries( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeNullableInt32( getValue( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
