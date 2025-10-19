package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleMapServiceOptionsDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  mso.[Id], \r\n" +
            "  mso.[RowVersion], \r\n" +
            "  mso.[Timestamp], \r\n" +
            "  mso.[IpAddress], \r\n" +
            "  mso.[Port], \r\n" +
            "  mso.[ImageScaleFactorX], \r\n" +
            "  mso.[ImageOffsetX], \r\n" +
            "  mso.[ImageScaleFactorY], \r\n" +
            "  mso.[ImageOffsetY] \r\n" +
            "FROM [MapServiceOptionsView] mso \r\n";

    public final static String BaseViewName = "MapServiceOptionsView";
    public final static String ViewAliasName = "mso";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int TIMESTAMP_FIELD_ID = 3;
    public final static int IPADDRESS_FIELD_ID = 4;
    public final static int PORT_FIELD_ID = 5;
    public final static int IMAGESCALEFACTORX_FIELD_ID = 6;
    public final static int IMAGEOFFSETX_FIELD_ID = 7;
    public final static int IMAGESCALEFACTORY_FIELD_ID = 8;
    public final static int IMAGEOFFSETY_FIELD_ID = 9;

    public SimpleMapServiceOptionsDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final String getIpAddress() throws SQLException {
        return getString( IPADDRESS_FIELD_ID );
    }

    public final int getPort() throws SQLException {
        return getInt32( PORT_FIELD_ID );
    }

    public final double getImageScaleFactorX() throws SQLException {
        return getDouble( IMAGESCALEFACTORX_FIELD_ID );
    }

    public final double getImageOffsetX() throws SQLException {
        return getDouble( IMAGEOFFSETX_FIELD_ID );
    }

    public final double getImageScaleFactorY() throws SQLException {
        return getDouble( IMAGESCALEFACTORY_FIELD_ID );
    }

    public final double getImageOffsetY() throws SQLException {
        return getDouble( IMAGEOFFSETY_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.MapServiceOptions );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeStringUtf8( getIpAddress( ) );
        destination.writeInt32( getPort( ) );
        destination.writeDouble( getImageScaleFactorX( ) );
        destination.writeDouble( getImageOffsetX( ) );
        destination.writeDouble( getImageScaleFactorY( ) );
        destination.writeDouble( getImageOffsetY( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public MapServiceOptionsObject getDataObject( ) throws SQLException {
            return new MapServiceOptionsObject( ObjectState.Stored, getId( ), getRowVersion( ), getTimestamp( ), getIpAddress( ), getPort( ), getImageScaleFactorX( ), getImageOffsetX( ), getImageScaleFactorY( ), getImageOffsetY( ) );
    }

}
