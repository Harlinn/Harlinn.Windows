package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleCameraConfigurationDataReader extends ResultSetWrapper {
    public final static String BaseQuery = "SELECT \r\n" +
            "  cc.[Id], \r\n" +
            "  cc.[RowVersion], \r\n" +
            "  cc.[Camera], \r\n" +
            "  cc.[Timestamp], \r\n" +
            "  cc.[CameraControlProtocol], \r\n" +
            "  cc.[CameraURL], \r\n" +
            "  cc.[ConfigurationURL], \r\n" +
            "  cc.[UserName], \r\n" +
            "  cc.[Password], \r\n" +
            "  cc.[UseRtspUriOverride], \r\n" +
            "  cc.[RtspUriOverride], \r\n" +
            "  cc.[Latitude], \r\n" +
            "  cc.[Longitude], \r\n" +
            "  cc.[Altitude], \r\n" +
            "  cc.[UseRelativePosition], \r\n" +
            "  cc.[PanTiltMode], \r\n" +
            "  cc.[MinTiltAngle], \r\n" +
            "  cc.[MaxTiltAngle], \r\n" +
            "  cc.[MinTiltScaleAngle], \r\n" +
            "  cc.[MaxTiltScaleAngle], \r\n" +
            "  cc.[UseReverseTiltAngle], \r\n" +
            "  cc.[UseReverseNormalizedTiltAngle], \r\n" +
            "  cc.[MinTiltVelocity], \r\n" +
            "  cc.[MaxTiltVelocity], \r\n" +
            "  cc.[MinTiltSpeed], \r\n" +
            "  cc.[MaxTiltSpeed], \r\n" +
            "  cc.[MinPanAngle], \r\n" +
            "  cc.[MaxPanAngle], \r\n" +
            "  cc.[MinPanScaleAngle], \r\n" +
            "  cc.[MaxPanScaleAngle], \r\n" +
            "  cc.[UseReversePanAngle], \r\n" +
            "  cc.[UseReverseNormalizedPanAngle], \r\n" +
            "  cc.[MinPanVelocity], \r\n" +
            "  cc.[MaxPanVelocity], \r\n" +
            "  cc.[MinPanSpeed], \r\n" +
            "  cc.[MaxPanSpeed], \r\n" +
            "  cc.[FocalLengthMode], \r\n" +
            "  cc.[MinFocalLength], \r\n" +
            "  cc.[MaxFocalLength], \r\n" +
            "  cc.[MinFocalLengthScale], \r\n" +
            "  cc.[MaxFocalLengthScale], \r\n" +
            "  cc.[MinZoomVelocity], \r\n" +
            "  cc.[MaxZoomVelocity], \r\n" +
            "  cc.[MinZoomSpeed], \r\n" +
            "  cc.[MaxZoomSpeed], \r\n" +
            "  cc.[ImageSensorWidth], \r\n" +
            "  cc.[ImageSensorHeight], \r\n" +
            "  cc.[HomePanAngle], \r\n" +
            "  cc.[HomeTiltAngle], \r\n" +
            "  cc.[HomeFocalLength], \r\n" +
            "  cc.[PanOffset], \r\n" +
            "  cc.[TiltOffset], \r\n" +
            "  cc.[AimAltitude], \r\n" +
            "  cc.[MinimumTargetWidth], \r\n" +
            "  cc.[TargetLockTimeout], \r\n" +
            "  cc.[UpdateStatusInterval], \r\n" +
            "  cc.[ReadTimeout], \r\n" +
            "  cc.[MoveCommandStatusDelay], \r\n" +
            "  cc.[PtzProfileName], \r\n" +
            "  cc.[PtzConfigurationToken], \r\n" +
            "  cc.[VideoSourceToken] \r\n" +
            "FROM [CameraConfigurationView] cc \r\n";

    public final static String BaseViewName = "CameraConfigurationView";
    public final static String ViewAliasName = "cc";

    public final static int ID_FIELD_ID = 1;
    public final static int ROWVERSION_FIELD_ID = 2;
    public final static int CAMERA_FIELD_ID = 3;
    public final static int TIMESTAMP_FIELD_ID = 4;
    public final static int CAMERACONTROLPROTOCOL_FIELD_ID = 5;
    public final static int CAMERAURL_FIELD_ID = 6;
    public final static int CONFIGURATIONURL_FIELD_ID = 7;
    public final static int USERNAME_FIELD_ID = 8;
    public final static int PASSWORD_FIELD_ID = 9;
    public final static int USERTSPURIOVERRIDE_FIELD_ID = 10;
    public final static int RTSPURIOVERRIDE_FIELD_ID = 11;
    public final static int LATITUDE_FIELD_ID = 12;
    public final static int LONGITUDE_FIELD_ID = 13;
    public final static int ALTITUDE_FIELD_ID = 14;
    public final static int USERELATIVEPOSITION_FIELD_ID = 15;
    public final static int PANTILTMODE_FIELD_ID = 16;
    public final static int MINTILTANGLE_FIELD_ID = 17;
    public final static int MAXTILTANGLE_FIELD_ID = 18;
    public final static int MINTILTSCALEANGLE_FIELD_ID = 19;
    public final static int MAXTILTSCALEANGLE_FIELD_ID = 20;
    public final static int USEREVERSETILTANGLE_FIELD_ID = 21;
    public final static int USEREVERSENORMALIZEDTILTANGLE_FIELD_ID = 22;
    public final static int MINTILTVELOCITY_FIELD_ID = 23;
    public final static int MAXTILTVELOCITY_FIELD_ID = 24;
    public final static int MINTILTSPEED_FIELD_ID = 25;
    public final static int MAXTILTSPEED_FIELD_ID = 26;
    public final static int MINPANANGLE_FIELD_ID = 27;
    public final static int MAXPANANGLE_FIELD_ID = 28;
    public final static int MINPANSCALEANGLE_FIELD_ID = 29;
    public final static int MAXPANSCALEANGLE_FIELD_ID = 30;
    public final static int USEREVERSEPANANGLE_FIELD_ID = 31;
    public final static int USEREVERSENORMALIZEDPANANGLE_FIELD_ID = 32;
    public final static int MINPANVELOCITY_FIELD_ID = 33;
    public final static int MAXPANVELOCITY_FIELD_ID = 34;
    public final static int MINPANSPEED_FIELD_ID = 35;
    public final static int MAXPANSPEED_FIELD_ID = 36;
    public final static int FOCALLENGTHMODE_FIELD_ID = 37;
    public final static int MINFOCALLENGTH_FIELD_ID = 38;
    public final static int MAXFOCALLENGTH_FIELD_ID = 39;
    public final static int MINFOCALLENGTHSCALE_FIELD_ID = 40;
    public final static int MAXFOCALLENGTHSCALE_FIELD_ID = 41;
    public final static int MINZOOMVELOCITY_FIELD_ID = 42;
    public final static int MAXZOOMVELOCITY_FIELD_ID = 43;
    public final static int MINZOOMSPEED_FIELD_ID = 44;
    public final static int MAXZOOMSPEED_FIELD_ID = 45;
    public final static int IMAGESENSORWIDTH_FIELD_ID = 46;
    public final static int IMAGESENSORHEIGHT_FIELD_ID = 47;
    public final static int HOMEPANANGLE_FIELD_ID = 48;
    public final static int HOMETILTANGLE_FIELD_ID = 49;
    public final static int HOMEFOCALLENGTH_FIELD_ID = 50;
    public final static int PANOFFSET_FIELD_ID = 51;
    public final static int TILTOFFSET_FIELD_ID = 52;
    public final static int AIMALTITUDE_FIELD_ID = 53;
    public final static int MINIMUMTARGETWIDTH_FIELD_ID = 54;
    public final static int TARGETLOCKTIMEOUT_FIELD_ID = 55;
    public final static int UPDATESTATUSINTERVAL_FIELD_ID = 56;
    public final static int READTIMEOUT_FIELD_ID = 57;
    public final static int MOVECOMMANDSTATUSDELAY_FIELD_ID = 58;
    public final static int PTZPROFILENAME_FIELD_ID = 59;
    public final static int PTZCONFIGURATIONTOKEN_FIELD_ID = 60;
    public final static int VIDEOSOURCETOKEN_FIELD_ID = 61;

    public SimpleCameraConfigurationDataReader( ResultSet resultSet ) {
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

    public final int getCameraControlProtocol() throws SQLException {
        return getInt32( CAMERACONTROLPROTOCOL_FIELD_ID );
    }

    public final String getCameraURL() throws SQLException {
        return getString( CAMERAURL_FIELD_ID );
    }

    public final String getConfigurationURL() throws SQLException {
        return getString( CONFIGURATIONURL_FIELD_ID );
    }

    public final String getUserName() throws SQLException {
        return getString( USERNAME_FIELD_ID );
    }

    public final String getPassword() throws SQLException {
        return getString( PASSWORD_FIELD_ID );
    }

    public final boolean getUseRtspUriOverride() throws SQLException {
        return getBoolean( USERTSPURIOVERRIDE_FIELD_ID );
    }

    public final String getRtspUriOverride() throws SQLException {
        return getString( RTSPURIOVERRIDE_FIELD_ID );
    }

    public final double getLatitude() throws SQLException {
        return getDouble( LATITUDE_FIELD_ID );
    }

    public final double getLongitude() throws SQLException {
        return getDouble( LONGITUDE_FIELD_ID );
    }

    public final double getAltitude() throws SQLException {
        return getDouble( ALTITUDE_FIELD_ID );
    }

    public final boolean getUseRelativePosition() throws SQLException {
        return getBoolean( USERELATIVEPOSITION_FIELD_ID );
    }

    public final int getPanTiltMode() throws SQLException {
        return getInt32( PANTILTMODE_FIELD_ID );
    }

    public final double getMinTiltAngle() throws SQLException {
        return getDouble( MINTILTANGLE_FIELD_ID );
    }

    public final double getMaxTiltAngle() throws SQLException {
        return getDouble( MAXTILTANGLE_FIELD_ID );
    }

    public final double getMinTiltScaleAngle() throws SQLException {
        return getDouble( MINTILTSCALEANGLE_FIELD_ID );
    }

    public final double getMaxTiltScaleAngle() throws SQLException {
        return getDouble( MAXTILTSCALEANGLE_FIELD_ID );
    }

    public final boolean getUseReverseTiltAngle() throws SQLException {
        return getBoolean( USEREVERSETILTANGLE_FIELD_ID );
    }

    public final boolean getUseReverseNormalizedTiltAngle() throws SQLException {
        return getBoolean( USEREVERSENORMALIZEDTILTANGLE_FIELD_ID );
    }

    public final double getMinTiltVelocity() throws SQLException {
        return getDouble( MINTILTVELOCITY_FIELD_ID );
    }

    public final double getMaxTiltVelocity() throws SQLException {
        return getDouble( MAXTILTVELOCITY_FIELD_ID );
    }

    public final double getMinTiltSpeed() throws SQLException {
        return getDouble( MINTILTSPEED_FIELD_ID );
    }

    public final double getMaxTiltSpeed() throws SQLException {
        return getDouble( MAXTILTSPEED_FIELD_ID );
    }

    public final double getMinPanAngle() throws SQLException {
        return getDouble( MINPANANGLE_FIELD_ID );
    }

    public final double getMaxPanAngle() throws SQLException {
        return getDouble( MAXPANANGLE_FIELD_ID );
    }

    public final double getMinPanScaleAngle() throws SQLException {
        return getDouble( MINPANSCALEANGLE_FIELD_ID );
    }

    public final double getMaxPanScaleAngle() throws SQLException {
        return getDouble( MAXPANSCALEANGLE_FIELD_ID );
    }

    public final boolean getUseReversePanAngle() throws SQLException {
        return getBoolean( USEREVERSEPANANGLE_FIELD_ID );
    }

    public final boolean getUseReverseNormalizedPanAngle() throws SQLException {
        return getBoolean( USEREVERSENORMALIZEDPANANGLE_FIELD_ID );
    }

    public final double getMinPanVelocity() throws SQLException {
        return getDouble( MINPANVELOCITY_FIELD_ID );
    }

    public final double getMaxPanVelocity() throws SQLException {
        return getDouble( MAXPANVELOCITY_FIELD_ID );
    }

    public final double getMinPanSpeed() throws SQLException {
        return getDouble( MINPANSPEED_FIELD_ID );
    }

    public final double getMaxPanSpeed() throws SQLException {
        return getDouble( MAXPANSPEED_FIELD_ID );
    }

    public final int getFocalLengthMode() throws SQLException {
        return getInt32( FOCALLENGTHMODE_FIELD_ID );
    }

    public final double getMinFocalLength() throws SQLException {
        return getDouble( MINFOCALLENGTH_FIELD_ID );
    }

    public final double getMaxFocalLength() throws SQLException {
        return getDouble( MAXFOCALLENGTH_FIELD_ID );
    }

    public final double getMinFocalLengthScale() throws SQLException {
        return getDouble( MINFOCALLENGTHSCALE_FIELD_ID );
    }

    public final double getMaxFocalLengthScale() throws SQLException {
        return getDouble( MAXFOCALLENGTHSCALE_FIELD_ID );
    }

    public final double getMinZoomVelocity() throws SQLException {
        return getDouble( MINZOOMVELOCITY_FIELD_ID );
    }

    public final double getMaxZoomVelocity() throws SQLException {
        return getDouble( MAXZOOMVELOCITY_FIELD_ID );
    }

    public final double getMinZoomSpeed() throws SQLException {
        return getDouble( MINZOOMSPEED_FIELD_ID );
    }

    public final double getMaxZoomSpeed() throws SQLException {
        return getDouble( MAXZOOMSPEED_FIELD_ID );
    }

    public final double getImageSensorWidth() throws SQLException {
        return getDouble( IMAGESENSORWIDTH_FIELD_ID );
    }

    public final double getImageSensorHeight() throws SQLException {
        return getDouble( IMAGESENSORHEIGHT_FIELD_ID );
    }

    public final double getHomePanAngle() throws SQLException {
        return getDouble( HOMEPANANGLE_FIELD_ID );
    }

    public final double getHomeTiltAngle() throws SQLException {
        return getDouble( HOMETILTANGLE_FIELD_ID );
    }

    public final double getHomeFocalLength() throws SQLException {
        return getDouble( HOMEFOCALLENGTH_FIELD_ID );
    }

    public final double getPanOffset() throws SQLException {
        return getDouble( PANOFFSET_FIELD_ID );
    }

    public final double getTiltOffset() throws SQLException {
        return getDouble( TILTOFFSET_FIELD_ID );
    }

    public final double getAimAltitude() throws SQLException {
        return getDouble( AIMALTITUDE_FIELD_ID );
    }

    public final double getMinimumTargetWidth() throws SQLException {
        return getDouble( MINIMUMTARGETWIDTH_FIELD_ID );
    }

    public final TimeSpan getTargetLockTimeout() throws SQLException {
        return getTimeSpan( TARGETLOCKTIMEOUT_FIELD_ID );
    }

    public final TimeSpan getUpdateStatusInterval() throws SQLException {
        return getTimeSpan( UPDATESTATUSINTERVAL_FIELD_ID );
    }

    public final TimeSpan getReadTimeout() throws SQLException {
        return getTimeSpan( READTIMEOUT_FIELD_ID );
    }

    public final TimeSpan getMoveCommandStatusDelay() throws SQLException {
        return getTimeSpan( MOVECOMMANDSTATUSDELAY_FIELD_ID );
    }

    public final String getPtzProfileName() throws SQLException {
        return getString( PTZPROFILENAME_FIELD_ID );
    }

    public final String getPtzConfigurationToken() throws SQLException {
        return getString( PTZCONFIGURATIONTOKEN_FIELD_ID );
    }

    public final String getVideoSourceToken() throws SQLException {
        return getString( VIDEOSOURCETOKEN_FIELD_ID );
    }

    public void writeTo(BinaryWriter destination) throws SQLException {
        destination.writeInt32( Kind.CameraConfiguration );
        destination.writeUInt8( ObjectState.Stored );
        destination.writeGuid( getId( ) );
        destination.writeInt64( getRowVersion( ) );
        destination.writeGuid( getCamera( ) );
        destination.writeDateTime( getTimestamp( ) );
        destination.writeInt32( getCameraControlProtocol( ) );
        destination.writeStringUtf8( getCameraURL( ) );
        destination.writeStringUtf8( getConfigurationURL( ) );
        destination.writeStringUtf8( getUserName( ) );
        destination.writeStringUtf8( getPassword( ) );
        destination.writeBoolean( getUseRtspUriOverride( ) );
        destination.writeStringUtf8( getRtspUriOverride( ) );
        destination.writeDouble( getLatitude( ) );
        destination.writeDouble( getLongitude( ) );
        destination.writeDouble( getAltitude( ) );
        destination.writeBoolean( getUseRelativePosition( ) );
        destination.writeInt32( getPanTiltMode( ) );
        destination.writeDouble( getMinTiltAngle( ) );
        destination.writeDouble( getMaxTiltAngle( ) );
        destination.writeDouble( getMinTiltScaleAngle( ) );
        destination.writeDouble( getMaxTiltScaleAngle( ) );
        destination.writeBoolean( getUseReverseTiltAngle( ) );
        destination.writeBoolean( getUseReverseNormalizedTiltAngle( ) );
        destination.writeDouble( getMinTiltVelocity( ) );
        destination.writeDouble( getMaxTiltVelocity( ) );
        destination.writeDouble( getMinTiltSpeed( ) );
        destination.writeDouble( getMaxTiltSpeed( ) );
        destination.writeDouble( getMinPanAngle( ) );
        destination.writeDouble( getMaxPanAngle( ) );
        destination.writeDouble( getMinPanScaleAngle( ) );
        destination.writeDouble( getMaxPanScaleAngle( ) );
        destination.writeBoolean( getUseReversePanAngle( ) );
        destination.writeBoolean( getUseReverseNormalizedPanAngle( ) );
        destination.writeDouble( getMinPanVelocity( ) );
        destination.writeDouble( getMaxPanVelocity( ) );
        destination.writeDouble( getMinPanSpeed( ) );
        destination.writeDouble( getMaxPanSpeed( ) );
        destination.writeInt32( getFocalLengthMode( ) );
        destination.writeDouble( getMinFocalLength( ) );
        destination.writeDouble( getMaxFocalLength( ) );
        destination.writeDouble( getMinFocalLengthScale( ) );
        destination.writeDouble( getMaxFocalLengthScale( ) );
        destination.writeDouble( getMinZoomVelocity( ) );
        destination.writeDouble( getMaxZoomVelocity( ) );
        destination.writeDouble( getMinZoomSpeed( ) );
        destination.writeDouble( getMaxZoomSpeed( ) );
        destination.writeDouble( getImageSensorWidth( ) );
        destination.writeDouble( getImageSensorHeight( ) );
        destination.writeDouble( getHomePanAngle( ) );
        destination.writeDouble( getHomeTiltAngle( ) );
        destination.writeDouble( getHomeFocalLength( ) );
        destination.writeDouble( getPanOffset( ) );
        destination.writeDouble( getTiltOffset( ) );
        destination.writeDouble( getAimAltitude( ) );
        destination.writeDouble( getMinimumTargetWidth( ) );
        destination.writeTimeSpan( getTargetLockTimeout( ) );
        destination.writeTimeSpan( getUpdateStatusInterval( ) );
        destination.writeTimeSpan( getReadTimeout( ) );
        destination.writeTimeSpan( getMoveCommandStatusDelay( ) );
        destination.writeStringUtf8( getPtzProfileName( ) );
        destination.writeStringUtf8( getPtzConfigurationToken( ) );
        destination.writeStringUtf8( getVideoSourceToken( ) );
    }

    public void writeResultSetTo( BinaryWriter destination ) throws SQLException {
        while ( next( ) ) {
            destination.writeBoolean( true );
            writeTo( destination );
        }
        destination.writeBoolean( false );
    }

    public CameraConfigurationObject getDataObject( ) throws SQLException {
            return new CameraConfigurationObject( ObjectState.Stored, getId( ), getRowVersion( ), getCamera( ), getTimestamp( ), getCameraControlProtocol( ), getCameraURL( ), getConfigurationURL( ), getUserName( ), getPassword( ), getUseRtspUriOverride( ), getRtspUriOverride( ), getLatitude( ), getLongitude( ), getAltitude( ), getUseRelativePosition( ), getPanTiltMode( ), getMinTiltAngle( ), getMaxTiltAngle( ), getMinTiltScaleAngle( ), getMaxTiltScaleAngle( ), getUseReverseTiltAngle( ), getUseReverseNormalizedTiltAngle( ), getMinTiltVelocity( ), getMaxTiltVelocity( ), getMinTiltSpeed( ), getMaxTiltSpeed( ), getMinPanAngle( ), getMaxPanAngle( ), getMinPanScaleAngle( ), getMaxPanScaleAngle( ), getUseReversePanAngle( ), getUseReverseNormalizedPanAngle( ), getMinPanVelocity( ), getMaxPanVelocity( ), getMinPanSpeed( ), getMaxPanSpeed( ), getFocalLengthMode( ), getMinFocalLength( ), getMaxFocalLength( ), getMinFocalLengthScale( ), getMaxFocalLengthScale( ), getMinZoomVelocity( ), getMaxZoomVelocity( ), getMinZoomSpeed( ), getMaxZoomSpeed( ), getImageSensorWidth( ), getImageSensorHeight( ), getHomePanAngle( ), getHomeTiltAngle( ), getHomeFocalLength( ), getPanOffset( ), getTiltOffset( ), getAimAltitude( ), getMinimumTargetWidth( ), getTargetLockTimeout( ), getUpdateStatusInterval( ), getReadTimeout( ), getMoveCommandStatusDelay( ), getPtzProfileName( ), getPtzConfigurationToken( ), getVideoSourceToken( ) );
    }

}
