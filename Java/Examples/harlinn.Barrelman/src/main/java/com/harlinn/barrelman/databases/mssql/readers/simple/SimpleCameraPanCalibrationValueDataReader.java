package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraPanCalibrationValueDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  cpcv.[Id], \r\n" +
            "  cpcv.[RowVersion], \r\n" +
            "  cpcv.[PanCalibration], \r\n" +
            "  cpcv.[PanAngle], \r\n" +
            "  cpcv.[PanOffset] \r\n" +
            "FROM [CameraPanCalibrationValueView] cpcv \r\n";

    public final static String BaseViewName = "CameraPanCalibrationValueView";
    public final static String ViewAliasName = "cpcv";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int PANCALIBRATION_FIELD_ID = 3;
    public final static int PANANGLE_FIELD_ID = 4;
    public final static int PANOFFSET_FIELD_ID = 5;

    public SimpleCameraPanCalibrationValueDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final Guid getId() throws SQLException {
        return getGuid( ID_FIELD_ID );
    }

    public final long getRowVersion() throws SQLException {
        return getInt64( ROWVERSION_FIELD_ID );
    }

    public final Guid getPanCalibration() throws SQLException {
        return getGuid( PANCALIBRATION_FIELD_ID );
    }

    public final double getPanAngle() throws SQLException {
        return getDouble( PANANGLE_FIELD_ID );
    }

    public final double getPanOffset() throws SQLException {
        return getDouble( PANOFFSET_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.CameraPanCalibrationValue );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getPanCalibration( ) );
        destination.writeDouble( getPanAngle( ) );
        destination.writeDouble( getPanOffset( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

}
