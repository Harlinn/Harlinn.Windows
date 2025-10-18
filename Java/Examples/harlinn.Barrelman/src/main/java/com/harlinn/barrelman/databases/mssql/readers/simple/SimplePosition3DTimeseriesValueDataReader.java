package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimplePosition3DTimeseriesValueDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  p3dv.[Id], \r\n" +
            "  p3dv.[RowVersion], \r\n" +
            "  p3dv.[Timeseries], \r\n" +
            "  p3dv.[Timestamp], \r\n" +
            "  p3dv.[X], \r\n" +
            "  p3dv.[Y], \r\n" +
            "  p3dv.[Z] \r\n" +
            "FROM [Position3DTimeseriesValueView] p3dv \r\n";

    public final static String BaseViewName = "Position3DTimeseriesValueView";
    public final static String ViewAliasName = "p3dv";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int TIMESERIES_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int X_FIELD_ID = 5;
    public final static int Y_FIELD_ID = 6;
    public final static int Z_FIELD_ID = 7;

    public SimplePosition3DTimeseriesValueDataReader( ResultSet resultSet ) {
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

    public final Double getX() throws SQLException {
        return getNullableDouble( X_FIELD_ID );
    }

    public final Double getY() throws SQLException {
        return getNullableDouble( Y_FIELD_ID );
    }

    public final Double getZ() throws SQLException {
        return getNullableDouble( Z_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.Position3DTimeseriesValue );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getTimeseries( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeNullableDouble( getX( ) );
        destination.writeNullableDouble( getY( ) );
        destination.writeNullableDouble( getZ( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public Position3DTimeseriesValueObject GetDataObject( ) throws SQLException {
            return new Position3DTimeseriesValueObject( ObjectState.Stored, getId( ), getRowVersion( ), getTimeseries( ), getTimestamp( ), getX( ), getY( ), getZ( ) );
    }

}
