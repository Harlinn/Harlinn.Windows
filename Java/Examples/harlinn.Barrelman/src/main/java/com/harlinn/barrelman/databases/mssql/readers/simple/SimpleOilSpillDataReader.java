package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleOilSpillDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  os.[Id], \r\n" +
            "  os.[RowVersion], \r\n" +
            "  os.[OilSpillDetector], \r\n" +
            "  os.[Timestamp], \r\n" +
            "  os.[OilArea], \r\n" +
            "  os.[Shape], \r\n" +
            "  os.[BSI], \r\n" +
            "  os.[Oil], \r\n" +
            "  os.[Trace] \r\n" +
            "FROM [OilSpillView] os \r\n";

    public final static String BaseViewName = "OilSpillView";
    public final static String ViewAliasName = "os";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int OILSPILLDETECTOR_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int OILAREA_FIELD_ID = 5;
    public final static int SHAPE_FIELD_ID = 6;
    public final static int BSI_FIELD_ID = 7;
    public final static int OIL_FIELD_ID = 8;
    public final static int TRACE_FIELD_ID = 9;

    public SimpleOilSpillDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getOilSpillDetector() throws SQLException {
        return getGuid( OILSPILLDETECTOR_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public final double getOilArea() throws SQLException {
        return getDouble( OILAREA_FIELD_ID );
    }

    public final byte[] getShape() throws SQLException {
        return getBinary( SHAPE_FIELD_ID );
    }

    public final byte[] getBSI() throws SQLException {
        return getBinary( BSI_FIELD_ID );
    }

    public final byte[] getOil() throws SQLException {
        return getBinary( OIL_FIELD_ID );
    }

    public final byte[] getTrace() throws SQLException {
        return getBinary( TRACE_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.OilSpill );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getOilSpillDetector( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeDouble( getOilArea( ) );
        destination.writeUInt8Array( getShape( ) );
        destination.writeUInt8Array( getBSI( ) );
        destination.writeUInt8Array( getOil( ) );
        destination.writeUInt8Array( getTrace( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
