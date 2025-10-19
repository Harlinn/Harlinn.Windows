package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTimeseriesInfoDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ti.[Id], \r\n" +
            "  ti.[RowVersion], \r\n" +
            "  ti.[FirstTimestamp], \r\n" +
            "  ti.[LastTimestamp], \r\n" +
            "  ti.[Count] \r\n" +
            "FROM [TimeseriesInfoView] ti \r\n";

    public final static String BaseViewName = "TimeseriesInfoView";
    public final static String ViewAliasName = "ti";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int FIRSTTIMESTAMP_FIELD_ID = 3;
    public final static int LASTTIMESTAMP_FIELD_ID = 4;
    public final static int COUNT_FIELD_ID = 5;

    public SimpleTimeseriesInfoDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final DateTime getFirstTimestamp() throws SQLException {
        return getNullableDateTimeFromLong( FIRSTTIMESTAMP_FIELD_ID );
    }

    public final DateTime getLastTimestamp() throws SQLException {
        return getNullableDateTimeFromLong( LASTTIMESTAMP_FIELD_ID );
    }

    public final long getCount() throws SQLException {
        return getInt64( COUNT_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.TimeseriesInfo );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeNullableDateTime( getFirstTimestamp( ) );
        destination.writeNullableDateTime( getLastTimestamp( ) );
        destination.writeInt64( getCount( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public TimeseriesInfoObject getDataObject( ) throws SQLException {
            return new TimeseriesInfoObject( ObjectState.Stored, getId( ), getRowVersion( ), getFirstTimestamp( ), getLastTimestamp( ), getCount( ) );
    }

}
