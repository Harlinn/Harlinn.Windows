package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleMapInfoDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  mi.[Id], \r\n" +
            "  mi.[RowVersion], \r\n" +
            "  mi.[Scale], \r\n" +
            "  mi.[Latitude], \r\n" +
            "  mi.[Longitude], \r\n" +
            "  mi.[NorthWestLatitude], \r\n" +
            "  mi.[NorthWestLongitude], \r\n" +
            "  mi.[SouthEastLatitude], \r\n" +
            "  mi.[SouthEastLongitude], \r\n" +
            "  mi.[Image] \r\n" +
            "FROM [MapInfoView] mi \r\n";

    public final static String BaseViewName = "MapInfoView";
    public final static String ViewAliasName = "mi";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int SCALE_FIELD_ID = 3;
    public final static int LATITUDE_FIELD_ID = 4;
    public final static int LONGITUDE_FIELD_ID = 5;
    public final static int NORTHWESTLATITUDE_FIELD_ID = 6;
    public final static int NORTHWESTLONGITUDE_FIELD_ID = 7;
    public final static int SOUTHEASTLATITUDE_FIELD_ID = 8;
    public final static int SOUTHEASTLONGITUDE_FIELD_ID = 9;
    public final static int IMAGE_FIELD_ID = 10;

    public SimpleMapInfoDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final int getScale() throws SQLException {
        return getInt32( SCALE_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getNorthWestLatitude() throws SQLException {
        return getDouble( NORTHWESTLATITUDE_FIELD_ID );
    }

    public final double getNorthWestLongitude() throws SQLException {
        return getDouble( NORTHWESTLONGITUDE_FIELD_ID );
    }

    public final double getSouthEastLatitude() throws SQLException {
        return getDouble( SOUTHEASTLATITUDE_FIELD_ID );
    }

    public final double getSouthEastLongitude() throws SQLException {
        return getDouble( SOUTHEASTLONGITUDE_FIELD_ID );
    }

    public final byte[] getImage() throws SQLException {
        return getBinary( IMAGE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.MapInfo );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeInt32( getScale( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getNorthWestLatitude( ) );
        destination.writeDouble( getNorthWestLongitude( ) );
        destination.writeDouble( getSouthEastLatitude( ) );
        destination.writeDouble( getSouthEastLongitude( ) );
        destination.writeUInt8Array( getImage( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public MapInfoObject getDataObject( ) throws SQLException {
            return new MapInfoObject( ObjectState.Stored, getId( ), getRowVersion( ), getScale( ), getLatitude( ), getLongitude( ), getNorthWestLatitude( ), getNorthWestLongitude( ), getSouthEastLatitude( ), getSouthEastLongitude( ), getImage( ) );
    }

}
