package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimplePosition2DTimeseriesValueDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  p2dv.[Id], \r\n" +
            "  p2dv.[RowVersion], \r\n" +
            "  p2dv.[Timeseries], \r\n" +
            "  p2dv.[Timestamp], \r\n" +
            "  p2dv.[X], \r\n" +
            "  p2dv.[Y] \r\n" +
            "FROM [Position2DTimeseriesValueView] p2dv \r\n";

    public final static String BaseViewName = "Position2DTimeseriesValueView";
    public final static String ViewAliasName = "p2dv";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int TIMESERIES_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int X_FIELD_ID = 5;
    public final static int Y_FIELD_ID = 6;

    public SimplePosition2DTimeseriesValueDataReader( ResultSet resultSet ) {
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

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.Position2DTimeseriesValue );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getTimeseries( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeNullableDouble( getX( ) );
        destination.writeNullableDouble( getY( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public Position2DTimeseriesValueObject GetDataObject( ) throws SQLException {
            return new Position2DTimeseriesValueObject( ObjectState.Stored, getId( ), getRowVersion( ), getTimeseries( ), getTimestamp( ), getX( ), getY( ) );
    }

}
