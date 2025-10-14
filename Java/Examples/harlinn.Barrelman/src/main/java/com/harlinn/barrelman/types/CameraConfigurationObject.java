package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _camera;
    private DateTime _timestamp;
    private int _cameraControlProtocol = CameraControlProtocol.Unknown;
    private String _cameraURL = "";
    private String _configurationURL = "";
    private String _userName = "";
    private String _password = "";
    private boolean _useRtspUriOverride = false;
    private String _rtspUriOverride = "";
    private double _latitude = 0.0;
    private double _longitude = 0.0;
    private double _altitude = 0.0;
    private boolean _useRelativePosition = false;
    private int _panTiltMode = CameraPanTiltMode.Unknown;
    private double _minTiltAngle = 0.0;
    private double _maxTiltAngle = 0.0;
    private double _minTiltScaleAngle = 0.0;
    private double _maxTiltScaleAngle = 0.0;
    private boolean _useReverseTiltAngle = false;
    private boolean _useReverseNormalizedTiltAngle = false;
    private double _minTiltVelocity = 0.0;
    private double _maxTiltVelocity = 0.0;
    private double _minTiltSpeed = 0.0;
    private double _maxTiltSpeed = 0.0;
    private double _minPanAngle = 0.0;
    private double _maxPanAngle = 0.0;
    private double _minPanScaleAngle = 0.0;
    private double _maxPanScaleAngle = 0.0;
    private boolean _useReversePanAngle = false;
    private boolean _useReverseNormalizedPanAngle = false;
    private double _minPanVelocity = 0.0;
    private double _maxPanVelocity = 0.0;
    private double _minPanSpeed = 0.0;
    private double _maxPanSpeed = 0.0;
    private int _focalLengthMode = CameraFocalLengthMode.Unknown;
    private double _minFocalLength = 0.0;
    private double _maxFocalLength = 0.0;
    private double _minFocalLengthScale = 0.0;
    private double _maxFocalLengthScale = 0.0;
    private double _minZoomVelocity = 0.0;
    private double _maxZoomVelocity = 0.0;
    private double _minZoomSpeed = 0.0;
    private double _maxZoomSpeed = 0.0;
    private double _imageSensorWidth = 0.0;
    private double _imageSensorHeight = 0.0;
    private double _homePanAngle = 0.0;
    private double _homeTiltAngle = 0.0;
    private double _homeFocalLength = 0.0;
    private double _panOffset = 0.0;
    private double _tiltOffset = 0.0;
    private double _aimAltitude = 0.0;
    private double _minimumTargetWidth = 0.0;
    private TimeSpan _targetLockTimeout;
    private TimeSpan _updateStatusInterval;
    private TimeSpan _readTimeout;
    private TimeSpan _moveCommandStatusDelay;
    private String _ptzProfileName = "";
    private String _ptzConfigurationToken = "";
    private String _videoSourceToken = "";

    @Override
    public int getObjectType( ) {
        return Kind.CameraConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraConfigurationObject( );
    }

    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getCamera( ) {
        return _camera;
    }
    public void setCamera( Guid value ) {
        if( !Comparer.equalsGuid( _camera, value ) ) {
            _camera = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( !Comparer.equalsDateTime( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
    }

    public int getCameraControlProtocol( ) {
        return _cameraControlProtocol;
    }
    public void setCameraControlProtocol( int value ) {
        if( !Comparer.equalsInt32( _cameraControlProtocol, value ) ) {
            _cameraControlProtocol = value;
            onPropertyChanged( );
        }
    }

    public String getCameraURL( ) {
        return _cameraURL;
    }
    public void setCameraURL( String value ) {
        if( !Comparer.equalsString( _cameraURL, value ) ) {
            _cameraURL = value;
            onPropertyChanged( );
        }
    }

    public String getConfigurationURL( ) {
        return _configurationURL;
    }
    public void setConfigurationURL( String value ) {
        if( !Comparer.equalsString( _configurationURL, value ) ) {
            _configurationURL = value;
            onPropertyChanged( );
        }
    }

    public String getUserName( ) {
        return _userName;
    }
    public void setUserName( String value ) {
        if( !Comparer.equalsString( _userName, value ) ) {
            _userName = value;
            onPropertyChanged( );
        }
    }

    public String getPassword( ) {
        return _password;
    }
    public void setPassword( String value ) {
        if( !Comparer.equalsString( _password, value ) ) {
            _password = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseRtspUriOverride( ) {
        return _useRtspUriOverride;
    }
    public void setUseRtspUriOverride( boolean value ) {
        if( !Comparer.equalsBoolean( _useRtspUriOverride, value ) ) {
            _useRtspUriOverride = value;
            onPropertyChanged( );
        }
    }

    public String getRtspUriOverride( ) {
        return _rtspUriOverride;
    }
    public void setRtspUriOverride( String value ) {
        if( !Comparer.equalsString( _rtspUriOverride, value ) ) {
            _rtspUriOverride = value;
            onPropertyChanged( );
        }
    }

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( !Comparer.equalsDouble( _latitude, value ) ) {
            _latitude = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( !Comparer.equalsDouble( _longitude, value ) ) {
            _longitude = value;
            onPropertyChanged( );
        }
    }

    public double getAltitude( ) {
        return _altitude;
    }
    public void setAltitude( double value ) {
        if( !Comparer.equalsDouble( _altitude, value ) ) {
            _altitude = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseRelativePosition( ) {
        return _useRelativePosition;
    }
    public void setUseRelativePosition( boolean value ) {
        if( !Comparer.equalsBoolean( _useRelativePosition, value ) ) {
            _useRelativePosition = value;
            onPropertyChanged( );
        }
    }

    public int getPanTiltMode( ) {
        return _panTiltMode;
    }
    public void setPanTiltMode( int value ) {
        if( !Comparer.equalsInt32( _panTiltMode, value ) ) {
            _panTiltMode = value;
            onPropertyChanged( );
        }
    }

    public double getMinTiltAngle( ) {
        return _minTiltAngle;
    }
    public void setMinTiltAngle( double value ) {
        if( !Comparer.equalsDouble( _minTiltAngle, value ) ) {
            _minTiltAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMaxTiltAngle( ) {
        return _maxTiltAngle;
    }
    public void setMaxTiltAngle( double value ) {
        if( !Comparer.equalsDouble( _maxTiltAngle, value ) ) {
            _maxTiltAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMinTiltScaleAngle( ) {
        return _minTiltScaleAngle;
    }
    public void setMinTiltScaleAngle( double value ) {
        if( !Comparer.equalsDouble( _minTiltScaleAngle, value ) ) {
            _minTiltScaleAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMaxTiltScaleAngle( ) {
        return _maxTiltScaleAngle;
    }
    public void setMaxTiltScaleAngle( double value ) {
        if( !Comparer.equalsDouble( _maxTiltScaleAngle, value ) ) {
            _maxTiltScaleAngle = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseReverseTiltAngle( ) {
        return _useReverseTiltAngle;
    }
    public void setUseReverseTiltAngle( boolean value ) {
        if( !Comparer.equalsBoolean( _useReverseTiltAngle, value ) ) {
            _useReverseTiltAngle = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseReverseNormalizedTiltAngle( ) {
        return _useReverseNormalizedTiltAngle;
    }
    public void setUseReverseNormalizedTiltAngle( boolean value ) {
        if( !Comparer.equalsBoolean( _useReverseNormalizedTiltAngle, value ) ) {
            _useReverseNormalizedTiltAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMinTiltVelocity( ) {
        return _minTiltVelocity;
    }
    public void setMinTiltVelocity( double value ) {
        if( !Comparer.equalsDouble( _minTiltVelocity, value ) ) {
            _minTiltVelocity = value;
            onPropertyChanged( );
        }
    }

    public double getMaxTiltVelocity( ) {
        return _maxTiltVelocity;
    }
    public void setMaxTiltVelocity( double value ) {
        if( !Comparer.equalsDouble( _maxTiltVelocity, value ) ) {
            _maxTiltVelocity = value;
            onPropertyChanged( );
        }
    }

    public double getMinTiltSpeed( ) {
        return _minTiltSpeed;
    }
    public void setMinTiltSpeed( double value ) {
        if( !Comparer.equalsDouble( _minTiltSpeed, value ) ) {
            _minTiltSpeed = value;
            onPropertyChanged( );
        }
    }

    public double getMaxTiltSpeed( ) {
        return _maxTiltSpeed;
    }
    public void setMaxTiltSpeed( double value ) {
        if( !Comparer.equalsDouble( _maxTiltSpeed, value ) ) {
            _maxTiltSpeed = value;
            onPropertyChanged( );
        }
    }

    public double getMinPanAngle( ) {
        return _minPanAngle;
    }
    public void setMinPanAngle( double value ) {
        if( !Comparer.equalsDouble( _minPanAngle, value ) ) {
            _minPanAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMaxPanAngle( ) {
        return _maxPanAngle;
    }
    public void setMaxPanAngle( double value ) {
        if( !Comparer.equalsDouble( _maxPanAngle, value ) ) {
            _maxPanAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMinPanScaleAngle( ) {
        return _minPanScaleAngle;
    }
    public void setMinPanScaleAngle( double value ) {
        if( !Comparer.equalsDouble( _minPanScaleAngle, value ) ) {
            _minPanScaleAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMaxPanScaleAngle( ) {
        return _maxPanScaleAngle;
    }
    public void setMaxPanScaleAngle( double value ) {
        if( !Comparer.equalsDouble( _maxPanScaleAngle, value ) ) {
            _maxPanScaleAngle = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseReversePanAngle( ) {
        return _useReversePanAngle;
    }
    public void setUseReversePanAngle( boolean value ) {
        if( !Comparer.equalsBoolean( _useReversePanAngle, value ) ) {
            _useReversePanAngle = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseReverseNormalizedPanAngle( ) {
        return _useReverseNormalizedPanAngle;
    }
    public void setUseReverseNormalizedPanAngle( boolean value ) {
        if( !Comparer.equalsBoolean( _useReverseNormalizedPanAngle, value ) ) {
            _useReverseNormalizedPanAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMinPanVelocity( ) {
        return _minPanVelocity;
    }
    public void setMinPanVelocity( double value ) {
        if( !Comparer.equalsDouble( _minPanVelocity, value ) ) {
            _minPanVelocity = value;
            onPropertyChanged( );
        }
    }

    public double getMaxPanVelocity( ) {
        return _maxPanVelocity;
    }
    public void setMaxPanVelocity( double value ) {
        if( !Comparer.equalsDouble( _maxPanVelocity, value ) ) {
            _maxPanVelocity = value;
            onPropertyChanged( );
        }
    }

    public double getMinPanSpeed( ) {
        return _minPanSpeed;
    }
    public void setMinPanSpeed( double value ) {
        if( !Comparer.equalsDouble( _minPanSpeed, value ) ) {
            _minPanSpeed = value;
            onPropertyChanged( );
        }
    }

    public double getMaxPanSpeed( ) {
        return _maxPanSpeed;
    }
    public void setMaxPanSpeed( double value ) {
        if( !Comparer.equalsDouble( _maxPanSpeed, value ) ) {
            _maxPanSpeed = value;
            onPropertyChanged( );
        }
    }

    public int getFocalLengthMode( ) {
        return _focalLengthMode;
    }
    public void setFocalLengthMode( int value ) {
        if( !Comparer.equalsInt32( _focalLengthMode, value ) ) {
            _focalLengthMode = value;
            onPropertyChanged( );
        }
    }

    public double getMinFocalLength( ) {
        return _minFocalLength;
    }
    public void setMinFocalLength( double value ) {
        if( !Comparer.equalsDouble( _minFocalLength, value ) ) {
            _minFocalLength = value;
            onPropertyChanged( );
        }
    }

    public double getMaxFocalLength( ) {
        return _maxFocalLength;
    }
    public void setMaxFocalLength( double value ) {
        if( !Comparer.equalsDouble( _maxFocalLength, value ) ) {
            _maxFocalLength = value;
            onPropertyChanged( );
        }
    }

    public double getMinFocalLengthScale( ) {
        return _minFocalLengthScale;
    }
    public void setMinFocalLengthScale( double value ) {
        if( !Comparer.equalsDouble( _minFocalLengthScale, value ) ) {
            _minFocalLengthScale = value;
            onPropertyChanged( );
        }
    }

    public double getMaxFocalLengthScale( ) {
        return _maxFocalLengthScale;
    }
    public void setMaxFocalLengthScale( double value ) {
        if( !Comparer.equalsDouble( _maxFocalLengthScale, value ) ) {
            _maxFocalLengthScale = value;
            onPropertyChanged( );
        }
    }

    public double getMinZoomVelocity( ) {
        return _minZoomVelocity;
    }
    public void setMinZoomVelocity( double value ) {
        if( !Comparer.equalsDouble( _minZoomVelocity, value ) ) {
            _minZoomVelocity = value;
            onPropertyChanged( );
        }
    }

    public double getMaxZoomVelocity( ) {
        return _maxZoomVelocity;
    }
    public void setMaxZoomVelocity( double value ) {
        if( !Comparer.equalsDouble( _maxZoomVelocity, value ) ) {
            _maxZoomVelocity = value;
            onPropertyChanged( );
        }
    }

    public double getMinZoomSpeed( ) {
        return _minZoomSpeed;
    }
    public void setMinZoomSpeed( double value ) {
        if( !Comparer.equalsDouble( _minZoomSpeed, value ) ) {
            _minZoomSpeed = value;
            onPropertyChanged( );
        }
    }

    public double getMaxZoomSpeed( ) {
        return _maxZoomSpeed;
    }
    public void setMaxZoomSpeed( double value ) {
        if( !Comparer.equalsDouble( _maxZoomSpeed, value ) ) {
            _maxZoomSpeed = value;
            onPropertyChanged( );
        }
    }

    public double getImageSensorWidth( ) {
        return _imageSensorWidth;
    }
    public void setImageSensorWidth( double value ) {
        if( !Comparer.equalsDouble( _imageSensorWidth, value ) ) {
            _imageSensorWidth = value;
            onPropertyChanged( );
        }
    }

    public double getImageSensorHeight( ) {
        return _imageSensorHeight;
    }
    public void setImageSensorHeight( double value ) {
        if( !Comparer.equalsDouble( _imageSensorHeight, value ) ) {
            _imageSensorHeight = value;
            onPropertyChanged( );
        }
    }

    public double getHomePanAngle( ) {
        return _homePanAngle;
    }
    public void setHomePanAngle( double value ) {
        if( !Comparer.equalsDouble( _homePanAngle, value ) ) {
            _homePanAngle = value;
            onPropertyChanged( );
        }
    }

    public double getHomeTiltAngle( ) {
        return _homeTiltAngle;
    }
    public void setHomeTiltAngle( double value ) {
        if( !Comparer.equalsDouble( _homeTiltAngle, value ) ) {
            _homeTiltAngle = value;
            onPropertyChanged( );
        }
    }

    public double getHomeFocalLength( ) {
        return _homeFocalLength;
    }
    public void setHomeFocalLength( double value ) {
        if( !Comparer.equalsDouble( _homeFocalLength, value ) ) {
            _homeFocalLength = value;
            onPropertyChanged( );
        }
    }

    public double getPanOffset( ) {
        return _panOffset;
    }
    public void setPanOffset( double value ) {
        if( !Comparer.equalsDouble( _panOffset, value ) ) {
            _panOffset = value;
            onPropertyChanged( );
        }
    }

    public double getTiltOffset( ) {
        return _tiltOffset;
    }
    public void setTiltOffset( double value ) {
        if( !Comparer.equalsDouble( _tiltOffset, value ) ) {
            _tiltOffset = value;
            onPropertyChanged( );
        }
    }

    public double getAimAltitude( ) {
        return _aimAltitude;
    }
    public void setAimAltitude( double value ) {
        if( !Comparer.equalsDouble( _aimAltitude, value ) ) {
            _aimAltitude = value;
            onPropertyChanged( );
        }
    }

    public double getMinimumTargetWidth( ) {
        return _minimumTargetWidth;
    }
    public void setMinimumTargetWidth( double value ) {
        if( !Comparer.equalsDouble( _minimumTargetWidth, value ) ) {
            _minimumTargetWidth = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getTargetLockTimeout( ) {
        return _targetLockTimeout;
    }
    public void setTargetLockTimeout( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _targetLockTimeout, value ) ) {
            _targetLockTimeout = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getUpdateStatusInterval( ) {
        return _updateStatusInterval;
    }
    public void setUpdateStatusInterval( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _updateStatusInterval, value ) ) {
            _updateStatusInterval = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getReadTimeout( ) {
        return _readTimeout;
    }
    public void setReadTimeout( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _readTimeout, value ) ) {
            _readTimeout = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getMoveCommandStatusDelay( ) {
        return _moveCommandStatusDelay;
    }
    public void setMoveCommandStatusDelay( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _moveCommandStatusDelay, value ) ) {
            _moveCommandStatusDelay = value;
            onPropertyChanged( );
        }
    }

    public String getPtzProfileName( ) {
        return _ptzProfileName;
    }
    public void setPtzProfileName( String value ) {
        if( !Comparer.equalsString( _ptzProfileName, value ) ) {
            _ptzProfileName = value;
            onPropertyChanged( );
        }
    }

    public String getPtzConfigurationToken( ) {
        return _ptzConfigurationToken;
    }
    public void setPtzConfigurationToken( String value ) {
        if( !Comparer.equalsString( _ptzConfigurationToken, value ) ) {
            _ptzConfigurationToken = value;
            onPropertyChanged( );
        }
    }

    public String getVideoSourceToken( ) {
        return _videoSourceToken;
    }
    public void setVideoSourceToken( String value ) {
        if( !Comparer.equalsString( _videoSourceToken, value ) ) {
            _videoSourceToken = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _camera );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _cameraControlProtocol );
        destination.writeStringUtf8( _cameraURL );
        destination.writeStringUtf8( _configurationURL );
        destination.writeStringUtf8( _userName );
        destination.writeStringUtf8( _password );
        destination.writeBoolean( _useRtspUriOverride );
        destination.writeStringUtf8( _rtspUriOverride );
        destination.writeDouble( _latitude );
        destination.writeDouble( _longitude );
        destination.writeDouble( _altitude );
        destination.writeBoolean( _useRelativePosition );
        destination.writeInt32( _panTiltMode );
        destination.writeDouble( _minTiltAngle );
        destination.writeDouble( _maxTiltAngle );
        destination.writeDouble( _minTiltScaleAngle );
        destination.writeDouble( _maxTiltScaleAngle );
        destination.writeBoolean( _useReverseTiltAngle );
        destination.writeBoolean( _useReverseNormalizedTiltAngle );
        destination.writeDouble( _minTiltVelocity );
        destination.writeDouble( _maxTiltVelocity );
        destination.writeDouble( _minTiltSpeed );
        destination.writeDouble( _maxTiltSpeed );
        destination.writeDouble( _minPanAngle );
        destination.writeDouble( _maxPanAngle );
        destination.writeDouble( _minPanScaleAngle );
        destination.writeDouble( _maxPanScaleAngle );
        destination.writeBoolean( _useReversePanAngle );
        destination.writeBoolean( _useReverseNormalizedPanAngle );
        destination.writeDouble( _minPanVelocity );
        destination.writeDouble( _maxPanVelocity );
        destination.writeDouble( _minPanSpeed );
        destination.writeDouble( _maxPanSpeed );
        destination.writeInt32( _focalLengthMode );
        destination.writeDouble( _minFocalLength );
        destination.writeDouble( _maxFocalLength );
        destination.writeDouble( _minFocalLengthScale );
        destination.writeDouble( _maxFocalLengthScale );
        destination.writeDouble( _minZoomVelocity );
        destination.writeDouble( _maxZoomVelocity );
        destination.writeDouble( _minZoomSpeed );
        destination.writeDouble( _maxZoomSpeed );
        destination.writeDouble( _imageSensorWidth );
        destination.writeDouble( _imageSensorHeight );
        destination.writeDouble( _homePanAngle );
        destination.writeDouble( _homeTiltAngle );
        destination.writeDouble( _homeFocalLength );
        destination.writeDouble( _panOffset );
        destination.writeDouble( _tiltOffset );
        destination.writeDouble( _aimAltitude );
        destination.writeDouble( _minimumTargetWidth );
        destination.writeTimeSpan( _targetLockTimeout );
        destination.writeTimeSpan( _updateStatusInterval );
        destination.writeTimeSpan( _readTimeout );
        destination.writeTimeSpan( _moveCommandStatusDelay );
        destination.writeStringUtf8( _ptzProfileName );
        destination.writeStringUtf8( _ptzConfigurationToken );
        destination.writeStringUtf8( _videoSourceToken );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _camera = source.readGuid( );
        _timestamp = source.readDateTime( );
        _cameraControlProtocol = source.readInt32( );
        _cameraURL = source.readString( );
        _configurationURL = source.readString( );
        _userName = source.readString( );
        _password = source.readString( );
        _useRtspUriOverride = source.readBoolean( );
        _rtspUriOverride = source.readString( );
        _latitude = source.readDouble( );
        _longitude = source.readDouble( );
        _altitude = source.readDouble( );
        _useRelativePosition = source.readBoolean( );
        _panTiltMode = source.readInt32( );
        _minTiltAngle = source.readDouble( );
        _maxTiltAngle = source.readDouble( );
        _minTiltScaleAngle = source.readDouble( );
        _maxTiltScaleAngle = source.readDouble( );
        _useReverseTiltAngle = source.readBoolean( );
        _useReverseNormalizedTiltAngle = source.readBoolean( );
        _minTiltVelocity = source.readDouble( );
        _maxTiltVelocity = source.readDouble( );
        _minTiltSpeed = source.readDouble( );
        _maxTiltSpeed = source.readDouble( );
        _minPanAngle = source.readDouble( );
        _maxPanAngle = source.readDouble( );
        _minPanScaleAngle = source.readDouble( );
        _maxPanScaleAngle = source.readDouble( );
        _useReversePanAngle = source.readBoolean( );
        _useReverseNormalizedPanAngle = source.readBoolean( );
        _minPanVelocity = source.readDouble( );
        _maxPanVelocity = source.readDouble( );
        _minPanSpeed = source.readDouble( );
        _maxPanSpeed = source.readDouble( );
        _focalLengthMode = source.readInt32( );
        _minFocalLength = source.readDouble( );
        _maxFocalLength = source.readDouble( );
        _minFocalLengthScale = source.readDouble( );
        _maxFocalLengthScale = source.readDouble( );
        _minZoomVelocity = source.readDouble( );
        _maxZoomVelocity = source.readDouble( );
        _minZoomSpeed = source.readDouble( );
        _maxZoomSpeed = source.readDouble( );
        _imageSensorWidth = source.readDouble( );
        _imageSensorHeight = source.readDouble( );
        _homePanAngle = source.readDouble( );
        _homeTiltAngle = source.readDouble( );
        _homeFocalLength = source.readDouble( );
        _panOffset = source.readDouble( );
        _tiltOffset = source.readDouble( );
        _aimAltitude = source.readDouble( );
        _minimumTargetWidth = source.readDouble( );
        _targetLockTimeout = source.readTimeSpan( );
        _updateStatusInterval = source.readTimeSpan( );
        _readTimeout = source.readTimeSpan( );
        _moveCommandStatusDelay = source.readTimeSpan( );
        _ptzProfileName = source.readString( );
        _ptzConfigurationToken = source.readString( );
        _videoSourceToken = source.readString( );
    }

}
