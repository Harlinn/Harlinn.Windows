package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleMapElementDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  me.[Id], \r\n" +
            "  me.[RowVersion], \r\n" +
            "  me.[Item], \r\n" +
            "  me.[ElementType], \r\n" +
            "  me.[Latitude], \r\n" +
            "  me.[Longitude], \r\n" +
            "  me.[Angle], \r\n" +
            "  me.[Left], \r\n" +
            "  me.[Top], \r\n" +
            "  me.[Width], \r\n" +
            "  me.[Height], \r\n" +
            "  me.[Label], \r\n" +
            "  me.[Data] \r\n" +
            "FROM [MapElementView] me \r\n";

    public final static String BaseViewName = "MapElementView";
    public final static String ViewAliasName = "me";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int ITEM_FIELD_ID = 3;
    public final static int ELEMENTTYPE_FIELD_ID = 4;
    public final static int LATITUDE_FIELD_ID = 5;
    public final static int LONGITUDE_FIELD_ID = 6;
    public final static int ANGLE_FIELD_ID = 7;
    public final static int LEFT_FIELD_ID = 8;
    public final static int TOP_FIELD_ID = 9;
    public final static int WIDTH_FIELD_ID = 10;
    public final static int HEIGHT_FIELD_ID = 11;
    public final static int LABEL_FIELD_ID = 12;
    public final static int DATA_FIELD_ID = 13;

    public SimpleMapElementDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getItem() throws SQLException {
        return getGuid( ITEM_FIELD_ID );
    }

    public final int getElementType() throws SQLException {
        return getInt32( ELEMENTTYPE_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getAngle() throws SQLException {
        return getDouble( ANGLE_FIELD_ID );
    }

    public final double getLeft() throws SQLException {
        return getDouble( LEFT_FIELD_ID );
    }

    public final double getTop() throws SQLException {
        return getDouble( TOP_FIELD_ID );
    }

    public final double getWidth() throws SQLException {
        return getDouble( WIDTH_FIELD_ID );
    }

    public final double getHeight() throws SQLException {
        return getDouble( HEIGHT_FIELD_ID );
    }

    public final String getLabel() throws SQLException {
        return getString( LABEL_FIELD_ID );
    }

    public final byte[] getData() throws SQLException {
        return getBinary( DATA_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.MapElement );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getItem( ) );
        destination.writeInt32( getElementType( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getAngle( ) );
        destination.writeDouble( getLeft( ) );
        destination.writeDouble( getTop( ) );
        destination.writeDouble( getWidth( ) );
        destination.writeDouble( getHeight( ) );
        destination.writeStringUtf8( getLabel( ) );
        destination.writeUInt8Array( getData( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
