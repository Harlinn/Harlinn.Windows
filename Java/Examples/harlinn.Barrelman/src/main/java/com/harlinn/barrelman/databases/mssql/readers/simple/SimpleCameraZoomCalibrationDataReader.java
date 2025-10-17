package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraZoomCalibrationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  czc.[Id], \r\n" +
            "  czc.[RowVersion], \r\n" +
            "  czc.[Camera], \r\n" +
            "  czc.[Timestamp] \r\n" +
            "FROM [CameraZoomCalibrationView] czc \r\n";

    public final static String BaseViewName = "CameraZoomCalibrationView";
    public final static String ViewAliasName = "czc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int CAMERA_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;

    public SimpleCameraZoomCalibrationDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getCamera() throws SQLException {
        return getGuid( CAMERA_FIELD_ID );
    }

    public final DateTime getTimestamp() throws SQLException {
        return getDateTimeFromLong( TIMESTAMP_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.CameraZoomCalibration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getCamera( ) );
        destination.writeDateTime( getTimestamp( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
