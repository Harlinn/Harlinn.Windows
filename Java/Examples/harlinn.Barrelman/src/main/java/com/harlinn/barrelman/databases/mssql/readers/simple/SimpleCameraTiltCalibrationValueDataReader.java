package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraTiltCalibrationValueDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ctcv.[Id], \r\n" +
            "  ctcv.[RowVersion], \r\n" +
            "  ctcv.[TiltCalibration], \r\n" +
            "  ctcv.[PanAngle], \r\n" +
            "  ctcv.[TiltOffset] \r\n" +
            "FROM [CameraTiltCalibrationValueView] ctcv \r\n";

    public final static String BaseViewName = "CameraTiltCalibrationValueView";
    public final static String ViewAliasName = "ctcv";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int TILTCALIBRATION_FIELD_ID = 3;
    public final static int PANANGLE_FIELD_ID = 4;
    public final static int TILTOFFSET_FIELD_ID = 5;

    public SimpleCameraTiltCalibrationValueDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getTiltCalibration() throws SQLException {
        return getGuid( TILTCALIBRATION_FIELD_ID );
    }

    public final double getPanAngle() throws SQLException {
        return getDouble( PANANGLE_FIELD_ID );
    }

    public final double getTiltOffset() throws SQLException {
        return getDouble( TILTOFFSET_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.CameraTiltCalibrationValue );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getTiltCalibration( ) );
        destination.writeDouble( getPanAngle( ) );
        destination.writeDouble( getTiltOffset( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
