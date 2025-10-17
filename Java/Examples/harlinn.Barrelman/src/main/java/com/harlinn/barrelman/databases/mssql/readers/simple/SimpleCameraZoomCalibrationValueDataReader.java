package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraZoomCalibrationValueDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  czcv.[Id], \r\n" +
            "  czcv.[RowVersion], \r\n" +
            "  czcv.[ZoomCalibration], \r\n" +
            "  czcv.[FocalLength], \r\n" +
            "  czcv.[FocalLengthOffset] \r\n" +
            "FROM [CameraZoomCalibrationValueView] czcv \r\n";

    public final static String BaseViewName = "CameraZoomCalibrationValueView";
    public final static String ViewAliasName = "czcv";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int ZOOMCALIBRATION_FIELD_ID = 3;
    public final static int FOCALLENGTH_FIELD_ID = 4;
    public final static int FOCALLENGTHOFFSET_FIELD_ID = 5;

    public SimpleCameraZoomCalibrationValueDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getZoomCalibration() throws SQLException {
        return getGuid( ZOOMCALIBRATION_FIELD_ID );
    }

    public final double getFocalLength() throws SQLException {
        return getDouble( FOCALLENGTH_FIELD_ID );
    }

    public final double getFocalLengthOffset() throws SQLException {
        return getDouble( FOCALLENGTHOFFSET_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.CameraZoomCalibrationValue );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getZoomCalibration( ) );
        destination.writeDouble( getFocalLength( ) );
        destination.writeDouble( getFocalLengthOffset( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
