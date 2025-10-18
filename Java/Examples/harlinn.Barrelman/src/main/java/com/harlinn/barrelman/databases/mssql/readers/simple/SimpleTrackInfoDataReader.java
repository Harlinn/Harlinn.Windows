package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleTrackInfoDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ti.[Id], \r\n" +
            "  ti.[RowVersion], \r\n" +
            "  ti.[FirstTimestamp], \r\n" +
            "  ti.[LastTimestamp], \r\n" +
            "  ti.[Count], \r\n" +
            "  ti.[NorthWestLatitude], \r\n" +
            "  ti.[NorthWestLongitude], \r\n" +
            "  ti.[SouthEastLatitude], \r\n" +
            "  ti.[SouthEastLongitude] \r\n" +
            "FROM [TrackInfoView] ti \r\n";

    public final static String BaseViewName = "TrackInfoView";
    public final static String ViewAliasName = "ti";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int FIRSTTIMESTAMP_FIELD_ID = 3;
    public final static int LASTTIMESTAMP_FIELD_ID = 4;
    public final static int COUNT_FIELD_ID = 5;
    public final static int NORTHWESTLATITUDE_FIELD_ID = 6;
    public final static int NORTHWESTLONGITUDE_FIELD_ID = 7;
    public final static int SOUTHEASTLATITUDE_FIELD_ID = 8;
    public final static int SOUTHEASTLONGITUDE_FIELD_ID = 9;

    public SimpleTrackInfoDataReader( ResultSet resultSet ) {
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

    public final Double getNorthWestLatitude() throws SQLException {
        return getNullableDouble( NORTHWESTLATITUDE_FIELD_ID );
    }

    public final Double getNorthWestLongitude() throws SQLException {
        return getNullableDouble( NORTHWESTLONGITUDE_FIELD_ID );
    }

    public final Double getSouthEastLatitude() throws SQLException {
        return getNullableDouble( SOUTHEASTLATITUDE_FIELD_ID );
    }

    public final Double getSouthEastLongitude() throws SQLException {
        return getNullableDouble( SOUTHEASTLONGITUDE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.TrackInfo );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeNullableDateTime( getFirstTimestamp( ) );
        destination.writeNullableDateTime( getLastTimestamp( ) );
        destination.writeInt64( getCount( ) );
        destination.writeNullableDouble( getNorthWestLatitude( ) );
        destination.writeNullableDouble( getNorthWestLongitude( ) );
        destination.writeNullableDouble( getSouthEastLatitude( ) );
        destination.writeNullableDouble( getSouthEastLongitude( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public TrackInfoObject GetDataObject( ) throws SQLException {
            return new TrackInfoObject( ObjectState.Stored, getId( ), getRowVersion( ), getFirstTimestamp( ), getLastTimestamp( ), getCount( ), getNorthWestLatitude( ), getNorthWestLongitude( ), getSouthEastLatitude( ), getSouthEastLongitude( ) );
    }

}
