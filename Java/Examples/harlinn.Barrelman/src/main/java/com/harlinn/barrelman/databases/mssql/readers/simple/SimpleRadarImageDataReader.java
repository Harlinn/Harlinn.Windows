package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleRadarImageDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ri.[Id], \r\n" +
            "  ri.[RowVersion], \r\n" +
            "  ri.[Radar], \r\n" +
            "  ri.[Timestamp], \r\n" +
            "  ri.[Depth], \r\n" +
            "  ri.[Resolution], \r\n" +
            "  ri.[Range], \r\n" +
            "  ri.[Image] \r\n" +
            "FROM [RadarImageView] ri \r\n";

    public final static String BaseViewName = "RadarImageView";
    public final static String ViewAliasName = "ri";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int RADAR_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int DEPTH_FIELD_ID = 5;
    public final static int RESOLUTION_FIELD_ID = 6;
    public final static int RANGE_FIELD_ID = 7;
    public final static int IMAGE_FIELD_ID = 8;

    public SimpleRadarImageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getRadar() throws SQLException {
        return getGuid( RADAR_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final int getDepth() throws SQLException {
        return getUInt32( DEPTH_FIELD_ID );
    }

    public final int getResolution() throws SQLException {
        return getInt32( RESOLUTION_FIELD_ID );
    }

    public final int getRange() throws SQLException {
        return getInt32( RANGE_FIELD_ID );
    }

    public final byte[] getImage() throws SQLException {
        return getBinary( IMAGE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.RadarImage );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getRadar( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeUInt32( getDepth( ) );
        destination.writeInt32( getResolution( ) );
        destination.writeInt32( getRange( ) );
        destination.writeUInt8Array( getImage( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
