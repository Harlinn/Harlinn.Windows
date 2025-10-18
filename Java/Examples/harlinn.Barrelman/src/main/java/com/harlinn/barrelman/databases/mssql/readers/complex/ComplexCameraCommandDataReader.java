package com.harlinn.barrelman.databases.mssql.readers.complex;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ComplexCameraCommandDataReader extends ResultSetWrapper {

    public final static String BaseQuery = "SELECT \r\n" +
            "  cc.[Id], \r\n" +
            "  cc.[EntityType], \r\n" +
            "  cc.[RowVersion], \r\n" +
            "  cc.[Camera], \r\n" +
            "  cc.[Timestamp], \r\n" +
            "  cc.[DeviceCommandSourceType], \r\n" +
            "  cc.[DeviceCommandSourceId], \r\n" +
            "  cc.[Reply], \r\n" +
            "  ccam.[PositionPanTiltMode], \r\n" +
            "  ccam.[PanAngle], \r\n" +
            "  ccam.[TiltAngle], \r\n" +
            "  ccam.[PositionFocalLengthMode], \r\n" +
            "  ccam.[FocalLength], \r\n" +
            "  ccam.[SpeedPanTiltMode], \r\n" +
            "  ccam.[PanSpeed], \r\n" +
            "  ccam.[TiltSpeed], \r\n" +
            "  ccam.[SpeedFocalLengthMode], \r\n" +
            "  ccam.[ZoomSpeed], \r\n" +
            "  ccaptz.[X], \r\n" +
            "  ccaptz.[Y], \r\n" +
            "  ccaptz.[Z], \r\n" +
            "  cccm.[Normalized], \r\n" +
            "  cccm.[PanVelocity], \r\n" +
            "  cccm.[TiltVelocity], \r\n" +
            "  cccm.[ZoomVelocity], \r\n" +
            "  cccm.[Duration], \r\n" +
            "  ccgm.[Latitude], \r\n" +
            "  ccgm.[Longitude], \r\n" +
            "  ccgm.[Altitude], \r\n" +
            "  ccgm.[ViewportWidth], \r\n" +
            "  ccgm.[ViewportHeight], \r\n" +
            "  ccrm.[Normalized], \r\n" +
            "  ccrm.[PanAngle], \r\n" +
            "  ccrm.[TiltAngle], \r\n" +
            "  ccrm.[FocalLength], \r\n" +
            "  ccrm.[PanSpeed], \r\n" +
            "  ccrm.[TiltSpeed], \r\n" +
            "  ccrm.[ZoomSpeed], \r\n" +
            "  ccsaf.[Enabled], \r\n" +
            "  ccsbaw.[Enabled], \r\n" +
            "  ccsf.[TrackId], \r\n" +
            "  ccsf.[Reason], \r\n" +
            "  ccsirl.[Enabled], \r\n" +
            "  cwa.[Enabled], \r\n" +
            "  cwi.[Enabled], \r\n" +
            "  ccs.[PanTilt], \r\n" +
            "  ccs.[Zoom] \r\n" +
            "FROM [CameraCommandView] cc \r\n" +
            "  LEFT JOIN [CameraCommandAbsoluteMove] ccam ON(cc.[Id] = ccam.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandAdjustPanTiltZoom] ccaptz ON(cc.[Id] = ccaptz.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandContinuousMove] cccm ON(cc.[Id] = cccm.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandGeoMove] ccgm ON(cc.[Id] = ccgm.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandRelativeMove] ccrm ON(cc.[Id] = ccrm.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandReleasePTZOwnership] crlp ON(cc.[Id] = crlp.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandRequestPTZOwnership] crqp ON(cc.[Id] = crqp.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandSetAutoFocus] ccsaf ON(cc.[Id] = ccsaf.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandSetBlackAndWhite] ccsbaw ON(cc.[Id] = ccsbaw.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandSetFollowed] ccsf ON(cc.[Id] = ccsf.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandSetInfraRedLamp] ccsirl ON(cc.[Id] = ccsirl.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandSetWasher] cwa ON(cc.[Id] = cwa.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandSetWiper] cwi ON(cc.[Id] = cwi.[Id] ) \r\n" +
            "  LEFT JOIN [CameraCommandStop] ccs ON(cc.[Id] = ccs.[Id] ) \r\n";

    public final static String BaseViewName = "CameraCommandView";
    public final static String ViewAliasName = "cc";

    public final static int CC_ID_FIELD_ID = 1;
    public final static int CC_KIND_FIELD_ID = 2;
    public final static int CC_ROWVERSION_FIELD_ID = 3;
    public final static int CC_CAMERA_FIELD_ID = 4;
    public final static int CC_TIMESTAMP_FIELD_ID = 5;
    public final static int CC_DEVICECOMMANDSOURCETYPE_FIELD_ID = 6;
    public final static int CC_DEVICECOMMANDSOURCEID_FIELD_ID = 7;
    public final static int CC_REPLY_FIELD_ID = 8;
    public final static int CCAM_POSITIONPANTILTMODE_FIELD_ID = 9;
    public final static int CCAM_PANANGLE_FIELD_ID = 10;
    public final static int CCAM_TILTANGLE_FIELD_ID = 11;
    public final static int CCAM_POSITIONFOCALLENGTHMODE_FIELD_ID = 12;
    public final static int CCAM_FOCALLENGTH_FIELD_ID = 13;
    public final static int CCAM_SPEEDPANTILTMODE_FIELD_ID = 14;
    public final static int CCAM_PANSPEED_FIELD_ID = 15;
    public final static int CCAM_TILTSPEED_FIELD_ID = 16;
    public final static int CCAM_SPEEDFOCALLENGTHMODE_FIELD_ID = 17;
    public final static int CCAM_ZOOMSPEED_FIELD_ID = 18;
    public final static int CCAPTZ_X_FIELD_ID = 19;
    public final static int CCAPTZ_Y_FIELD_ID = 20;
    public final static int CCAPTZ_Z_FIELD_ID = 21;
    public final static int CCCM_NORMALIZED_FIELD_ID = 22;
    public final static int CCCM_PANVELOCITY_FIELD_ID = 23;
    public final static int CCCM_TILTVELOCITY_FIELD_ID = 24;
    public final static int CCCM_ZOOMVELOCITY_FIELD_ID = 25;
    public final static int CCCM_DURATION_FIELD_ID = 26;
    public final static int CCGM_LATITUDE_FIELD_ID = 27;
    public final static int CCGM_LONGITUDE_FIELD_ID = 28;
    public final static int CCGM_ALTITUDE_FIELD_ID = 29;
    public final static int CCGM_VIEWPORTWIDTH_FIELD_ID = 30;
    public final static int CCGM_VIEWPORTHEIGHT_FIELD_ID = 31;
    public final static int CCRM_NORMALIZED_FIELD_ID = 32;
    public final static int CCRM_PANANGLE_FIELD_ID = 33;
    public final static int CCRM_TILTANGLE_FIELD_ID = 34;
    public final static int CCRM_FOCALLENGTH_FIELD_ID = 35;
    public final static int CCRM_PANSPEED_FIELD_ID = 36;
    public final static int CCRM_TILTSPEED_FIELD_ID = 37;
    public final static int CCRM_ZOOMSPEED_FIELD_ID = 38;
    public final static int CCSAF_ENABLED_FIELD_ID = 39;
    public final static int CCSBAW_ENABLED_FIELD_ID = 40;
    public final static int CCSF_TRACKID_FIELD_ID = 41;
    public final static int CCSF_REASON_FIELD_ID = 42;
    public final static int CCSIRL_ENABLED_FIELD_ID = 43;
    public final static int CWA_ENABLED_FIELD_ID = 44;
    public final static int CWI_ENABLED_FIELD_ID = 45;
    public final static int CCS_PANTILT_FIELD_ID = 46;
    public final static int CCS_ZOOM_FIELD_ID = 47;

    public ComplexCameraCommandDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public Guid getId( ) throws SQLException {
        return getGuid( CC_ID_FIELD_ID );
    }

    public int getObjectType() throws SQLException {
        return getInt32( CC_KIND_FIELD_ID );
    }

    public long getRowVersion( ) throws SQLException {
        return getInt64( CC_ROWVERSION_FIELD_ID );
    }

    public Guid getCamera( ) throws SQLException {
        return getGuid( CC_CAMERA_FIELD_ID );
    }

    public DateTime getTimestamp( ) throws SQLException {
        return getDateTimeFromLong( CC_TIMESTAMP_FIELD_ID );
    }

    public int getDeviceCommandSourceType( ) throws SQLException {
        return getInt32( CC_DEVICECOMMANDSOURCETYPE_FIELD_ID );
    }

    public Guid getDeviceCommandSourceId( ) throws SQLException {
        return getGuid( CC_DEVICECOMMANDSOURCEID_FIELD_ID );
    }

    public Guid getReply( ) throws SQLException {
        return getNullableGuid( CC_REPLY_FIELD_ID );
    }

    public int getCameraCommandAbsoluteMovePositionPanTiltMode( ) throws SQLException {
        return getInt32( CCAM_POSITIONPANTILTMODE_FIELD_ID );
    }

    public Double getCameraCommandAbsoluteMovePanAngle( ) throws SQLException {
        return getNullableDouble( CCAM_PANANGLE_FIELD_ID );
    }

    public Double getCameraCommandAbsoluteMoveTiltAngle( ) throws SQLException {
        return getNullableDouble( CCAM_TILTANGLE_FIELD_ID );
    }

    public int getCameraCommandAbsoluteMovePositionFocalLengthMode( ) throws SQLException {
        return getInt32( CCAM_POSITIONFOCALLENGTHMODE_FIELD_ID );
    }

    public Double getCameraCommandAbsoluteMoveFocalLength( ) throws SQLException {
        return getNullableDouble( CCAM_FOCALLENGTH_FIELD_ID );
    }

    public int getCameraCommandAbsoluteMoveSpeedPanTiltMode( ) throws SQLException {
        return getInt32( CCAM_SPEEDPANTILTMODE_FIELD_ID );
    }

    public Double getCameraCommandAbsoluteMovePanSpeed( ) throws SQLException {
        return getNullableDouble( CCAM_PANSPEED_FIELD_ID );
    }

    public Double getCameraCommandAbsoluteMoveTiltSpeed( ) throws SQLException {
        return getNullableDouble( CCAM_TILTSPEED_FIELD_ID );
    }

    public int getCameraCommandAbsoluteMoveSpeedFocalLengthMode( ) throws SQLException {
        return getInt32( CCAM_SPEEDFOCALLENGTHMODE_FIELD_ID );
    }

    public Double getCameraCommandAbsoluteMoveZoomSpeed( ) throws SQLException {
        return getNullableDouble( CCAM_ZOOMSPEED_FIELD_ID );
    }

    public Double getCameraCommandAdjustPanTiltZoomX( ) throws SQLException {
        return getNullableDouble( CCAPTZ_X_FIELD_ID );
    }

    public Double getCameraCommandAdjustPanTiltZoomY( ) throws SQLException {
        return getNullableDouble( CCAPTZ_Y_FIELD_ID );
    }

    public Double getCameraCommandAdjustPanTiltZoomZ( ) throws SQLException {
        return getNullableDouble( CCAPTZ_Z_FIELD_ID );
    }

    public boolean getCameraCommandContinuousMoveNormalized( ) throws SQLException {
        return getBoolean( CCCM_NORMALIZED_FIELD_ID );
    }

    public Double getCameraCommandContinuousMovePanVelocity( ) throws SQLException {
        return getNullableDouble( CCCM_PANVELOCITY_FIELD_ID );
    }

    public Double getCameraCommandContinuousMoveTiltVelocity( ) throws SQLException {
        return getNullableDouble( CCCM_TILTVELOCITY_FIELD_ID );
    }

    public Double getCameraCommandContinuousMoveZoomVelocity( ) throws SQLException {
        return getNullableDouble( CCCM_ZOOMVELOCITY_FIELD_ID );
    }

    public TimeSpan getCameraCommandContinuousMoveDuration( ) throws SQLException {
        return getNullableTimeSpan( CCCM_DURATION_FIELD_ID );
    }

    public double getCameraCommandGeoMoveLatitude( ) throws SQLException {
        return getDouble( CCGM_LATITUDE_FIELD_ID );
    }

    public double getCameraCommandGeoMoveLongitude( ) throws SQLException {
        return getDouble( CCGM_LONGITUDE_FIELD_ID );
    }

    public Double getCameraCommandGeoMoveAltitude( ) throws SQLException {
        return getNullableDouble( CCGM_ALTITUDE_FIELD_ID );
    }

    public Double getCameraCommandGeoMoveViewportWidth( ) throws SQLException {
        return getNullableDouble( CCGM_VIEWPORTWIDTH_FIELD_ID );
    }

    public Double getCameraCommandGeoMoveViewportHeight( ) throws SQLException {
        return getNullableDouble( CCGM_VIEWPORTHEIGHT_FIELD_ID );
    }

    public boolean getCameraCommandRelativeMoveNormalized( ) throws SQLException {
        return getBoolean( CCRM_NORMALIZED_FIELD_ID );
    }

    public Double getCameraCommandRelativeMovePanAngle( ) throws SQLException {
        return getNullableDouble( CCRM_PANANGLE_FIELD_ID );
    }

    public Double getCameraCommandRelativeMoveTiltAngle( ) throws SQLException {
        return getNullableDouble( CCRM_TILTANGLE_FIELD_ID );
    }

    public Double getCameraCommandRelativeMoveFocalLength( ) throws SQLException {
        return getNullableDouble( CCRM_FOCALLENGTH_FIELD_ID );
    }

    public Double getCameraCommandRelativeMovePanSpeed( ) throws SQLException {
        return getNullableDouble( CCRM_PANSPEED_FIELD_ID );
    }

    public Double getCameraCommandRelativeMoveTiltSpeed( ) throws SQLException {
        return getNullableDouble( CCRM_TILTSPEED_FIELD_ID );
    }

    public Double getCameraCommandRelativeMoveZoomSpeed( ) throws SQLException {
        return getNullableDouble( CCRM_ZOOMSPEED_FIELD_ID );
    }

    public boolean getCameraCommandSetAutoFocusEnabled( ) throws SQLException {
        return getBoolean( CCSAF_ENABLED_FIELD_ID );
    }

    public boolean getCameraCommandSetBlackAndWhiteEnabled( ) throws SQLException {
        return getBoolean( CCSBAW_ENABLED_FIELD_ID );
    }

    public Guid getCameraCommandSetFollowedTrackId( ) throws SQLException {
        return getGuid( CCSF_TRACKID_FIELD_ID );
    }

    public int getCameraCommandSetFollowedReason( ) throws SQLException {
        return getInt32( CCSF_REASON_FIELD_ID );
    }

    public boolean getCameraCommandSetInfraRedLampEnabled( ) throws SQLException {
        return getBoolean( CCSIRL_ENABLED_FIELD_ID );
    }

    public boolean getCameraCommandSetWasherEnabled( ) throws SQLException {
        return getBoolean( CWA_ENABLED_FIELD_ID );
    }

    public boolean getCameraCommandSetWiperEnabled( ) throws SQLException {
        return getBoolean( CWI_ENABLED_FIELD_ID );
    }

    public boolean getCameraCommandStopPanTilt( ) throws SQLException {
        return getBoolean( CCS_PANTILT_FIELD_ID );
    }

    public boolean getCameraCommandStopZoom( ) throws SQLException {
        return getBoolean( CCS_ZOOM_FIELD_ID );
    }

}

