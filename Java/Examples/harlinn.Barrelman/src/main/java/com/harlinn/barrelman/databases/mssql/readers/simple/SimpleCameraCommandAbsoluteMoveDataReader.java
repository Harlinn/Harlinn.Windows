package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraCommandAbsoluteMoveDataReader extends SimpleCameraCommandDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  ccam.[Id], \r\n" +
            "  ccam.[EntityType], \r\n" +
            "  ccam.[RowVersion], \r\n" +
            "  ccam.[Camera], \r\n" +
            "  ccam.[Timestamp], \r\n" +
            "  ccam.[DeviceCommandSourceType], \r\n" +
            "  ccam.[DeviceCommandSourceId], \r\n" +
            "  ccam.[Reply], \r\n" +
            "  ccam.[PositionPanTiltMode], \r\n" +
            "  ccam.[PanAngle], \r\n" +
            "  ccam.[TiltAngle], \r\n" +
            "  ccam.[PositionFocalLengthMode], \r\n" +
            "  ccam.[FocalLength], \r\n" +
            "  ccam.[SpeedPanTiltMode], \r\n" +
            "  ccam.[PanSpeed], \r\n" +
            "  ccam.[TiltSpeed], \r\n" +
            "  ccam.[SpeedFocalLengthMode], \r\n" +
            "  ccam.[ZoomSpeed] \r\n" +
            "FROM [CameraCommandAbsoluteMoveView] ccam \r\n";

    public final static String BaseViewName = "CameraCommandAbsoluteMoveView";
    public final static String ViewAliasName = "ccam";

    public final static int POSITIONPANTILTMODE_FIELD_ID = 9;
    public final static int PANANGLE_FIELD_ID = 10;
    public final static int TILTANGLE_FIELD_ID = 11;
    public final static int POSITIONFOCALLENGTHMODE_FIELD_ID = 12;
    public final static int FOCALLENGTH_FIELD_ID = 13;
    public final static int SPEEDPANTILTMODE_FIELD_ID = 14;
    public final static int PANSPEED_FIELD_ID = 15;
    public final static int TILTSPEED_FIELD_ID = 16;
    public final static int SPEEDFOCALLENGTHMODE_FIELD_ID = 17;
    public final static int ZOOMSPEED_FIELD_ID = 18;

    public SimpleCameraCommandAbsoluteMoveDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getPositionPanTiltMode() throws SQLException {
        return getInt32( POSITIONPANTILTMODE_FIELD_ID );
    }

    public final Double getPanAngle() throws SQLException {
        return getNullableDouble( PANANGLE_FIELD_ID );
    }

    public final Double getTiltAngle() throws SQLException {
        return getNullableDouble( TILTANGLE_FIELD_ID );
    }

    public final int getPositionFocalLengthMode() throws SQLException {
        return getInt32( POSITIONFOCALLENGTHMODE_FIELD_ID );
    }

    public final Double getFocalLength() throws SQLException {
        return getNullableDouble( FOCALLENGTH_FIELD_ID );
    }

    public final int getSpeedPanTiltMode() throws SQLException {
        return getInt32( SPEEDPANTILTMODE_FIELD_ID );
    }

    public final Double getPanSpeed() throws SQLException {
        return getNullableDouble( PANSPEED_FIELD_ID );
    }

    public final Double getTiltSpeed() throws SQLException {
        return getNullableDouble( TILTSPEED_FIELD_ID );
    }

    public final int getSpeedFocalLengthMode() throws SQLException {
        return getInt32( SPEEDFOCALLENGTHMODE_FIELD_ID );
    }

    public final Double getZoomSpeed() throws SQLException {
        return getNullableDouble( ZOOMSPEED_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getPositionPanTiltMode( ) );
        destination.writeNullableDouble( getPanAngle( ) );
        destination.writeNullableDouble( getTiltAngle( ) );
        destination.writeInt32( getPositionFocalLengthMode( ) );
        destination.writeNullableDouble( getFocalLength( ) );
        destination.writeInt32( getSpeedPanTiltMode( ) );
        destination.writeNullableDouble( getPanSpeed( ) );
        destination.writeNullableDouble( getTiltSpeed( ) );
        destination.writeInt32( getSpeedFocalLengthMode( ) );
        destination.writeNullableDouble( getZoomSpeed( ) );
    }

}
