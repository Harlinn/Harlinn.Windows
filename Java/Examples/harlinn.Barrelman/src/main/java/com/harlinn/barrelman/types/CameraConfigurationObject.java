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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getCamera( ) {
        return _camera;
    }
    public void setCamera( Guid value ) {
        if( _camera != value ) {
            this._camera = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( _timestamp != value ) {
            this._timestamp = value;
            onPropertyChanged( );
        }
    }

    public int getCameraControlProtocol( ) {
        return _cameraControlProtocol;
    }
    public void setCameraControlProtocol( int value ) {
        if( _cameraControlProtocol != value ) {
            this._cameraControlProtocol = value;
            onPropertyChanged( );
        }
    }

    public String getCameraURL( ) {
        return _cameraURL;
    }
    public void setCameraURL( String value ) {
        if( _cameraURL != value ) {
            this._cameraURL = value;
            onPropertyChanged( );
        }
    }

    public String getConfigurationURL( ) {
        return _configurationURL;
    }
    public void setConfigurationURL( String value ) {
        if( _configurationURL != value ) {
            this._configurationURL = value;
            onPropertyChanged( );
        }
    }

    public String getUserName( ) {
        return _userName;
    }
    public void setUserName( String value ) {
        if( _userName != value ) {
            this._userName = value;
            onPropertyChanged( );
        }
    }

    public String getPassword( ) {
        return _password;
    }
    public void setPassword( String value ) {
        if( _password != value ) {
            this._password = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseRtspUriOverride( ) {
        return _useRtspUriOverride;
    }
    public void setUseRtspUriOverride( boolean value ) {
        if( _useRtspUriOverride != value ) {
            this._useRtspUriOverride = value;
            onPropertyChanged( );
        }
    }

    public String getRtspUriOverride( ) {
        return _rtspUriOverride;
    }
    public void setRtspUriOverride( String value ) {
        if( _rtspUriOverride != value ) {
            this._rtspUriOverride = value;
            onPropertyChanged( );
        }
    }

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( _latitude != value ) {
            this._latitude = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( _longitude != value ) {
            this._longitude = value;
            onPropertyChanged( );
        }
    }

    public double getAltitude( ) {
        return _altitude;
    }
    public void setAltitude( double value ) {
        if( _altitude != value ) {
            this._altitude = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseRelativePosition( ) {
        return _useRelativePosition;
    }
    public void setUseRelativePosition( boolean value ) {
        if( _useRelativePosition != value ) {
            this._useRelativePosition = value;
            onPropertyChanged( );
        }
    }

    public int getPanTiltMode( ) {
        return _panTiltMode;
    }
    public void setPanTiltMode( int value ) {
        if( _panTiltMode != value ) {
            this._panTiltMode = value;
            onPropertyChanged( );
        }
    }

    public double getMinTiltAngle( ) {
        return _minTiltAngle;
    }
    public void setMinTiltAngle( double value ) {
        if( _minTiltAngle != value ) {
            this._minTiltAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMaxTiltAngle( ) {
        return _maxTiltAngle;
    }
    public void setMaxTiltAngle( double value ) {
        if( _maxTiltAngle != value ) {
            this._maxTiltAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMinTiltScaleAngle( ) {
        return _minTiltScaleAngle;
    }
    public void setMinTiltScaleAngle( double value ) {
        if( _minTiltScaleAngle != value ) {
            this._minTiltScaleAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMaxTiltScaleAngle( ) {
        return _maxTiltScaleAngle;
    }
    public void setMaxTiltScaleAngle( double value ) {
        if( _maxTiltScaleAngle != value ) {
            this._maxTiltScaleAngle = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseReverseTiltAngle( ) {
        return _useReverseTiltAngle;
    }
    public void setUseReverseTiltAngle( boolean value ) {
        if( _useReverseTiltAngle != value ) {
            this._useReverseTiltAngle = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseReverseNormalizedTiltAngle( ) {
        return _useReverseNormalizedTiltAngle;
    }
    public void setUseReverseNormalizedTiltAngle( boolean value ) {
        if( _useReverseNormalizedTiltAngle != value ) {
            this._useReverseNormalizedTiltAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMinTiltVelocity( ) {
        return _minTiltVelocity;
    }
    public void setMinTiltVelocity( double value ) {
        if( _minTiltVelocity != value ) {
            this._minTiltVelocity = value;
            onPropertyChanged( );
        }
    }

    public double getMaxTiltVelocity( ) {
        return _maxTiltVelocity;
    }
    public void setMaxTiltVelocity( double value ) {
        if( _maxTiltVelocity != value ) {
            this._maxTiltVelocity = value;
            onPropertyChanged( );
        }
    }

    public double getMinTiltSpeed( ) {
        return _minTiltSpeed;
    }
    public void setMinTiltSpeed( double value ) {
        if( _minTiltSpeed != value ) {
            this._minTiltSpeed = value;
            onPropertyChanged( );
        }
    }

    public double getMaxTiltSpeed( ) {
        return _maxTiltSpeed;
    }
    public void setMaxTiltSpeed( double value ) {
        if( _maxTiltSpeed != value ) {
            this._maxTiltSpeed = value;
            onPropertyChanged( );
        }
    }

    public double getMinPanAngle( ) {
        return _minPanAngle;
    }
    public void setMinPanAngle( double value ) {
        if( _minPanAngle != value ) {
            this._minPanAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMaxPanAngle( ) {
        return _maxPanAngle;
    }
    public void setMaxPanAngle( double value ) {
        if( _maxPanAngle != value ) {
            this._maxPanAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMinPanScaleAngle( ) {
        return _minPanScaleAngle;
    }
    public void setMinPanScaleAngle( double value ) {
        if( _minPanScaleAngle != value ) {
            this._minPanScaleAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMaxPanScaleAngle( ) {
        return _maxPanScaleAngle;
    }
    public void setMaxPanScaleAngle( double value ) {
        if( _maxPanScaleAngle != value ) {
            this._maxPanScaleAngle = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseReversePanAngle( ) {
        return _useReversePanAngle;
    }
    public void setUseReversePanAngle( boolean value ) {
        if( _useReversePanAngle != value ) {
            this._useReversePanAngle = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseReverseNormalizedPanAngle( ) {
        return _useReverseNormalizedPanAngle;
    }
    public void setUseReverseNormalizedPanAngle( boolean value ) {
        if( _useReverseNormalizedPanAngle != value ) {
            this._useReverseNormalizedPanAngle = value;
            onPropertyChanged( );
        }
    }

    public double getMinPanVelocity( ) {
        return _minPanVelocity;
    }
    public void setMinPanVelocity( double value ) {
        if( _minPanVelocity != value ) {
            this._minPanVelocity = value;
            onPropertyChanged( );
        }
    }

    public double getMaxPanVelocity( ) {
        return _maxPanVelocity;
    }
    public void setMaxPanVelocity( double value ) {
        if( _maxPanVelocity != value ) {
            this._maxPanVelocity = value;
            onPropertyChanged( );
        }
    }

    public double getMinPanSpeed( ) {
        return _minPanSpeed;
    }
    public void setMinPanSpeed( double value ) {
        if( _minPanSpeed != value ) {
            this._minPanSpeed = value;
            onPropertyChanged( );
        }
    }

    public double getMaxPanSpeed( ) {
        return _maxPanSpeed;
    }
    public void setMaxPanSpeed( double value ) {
        if( _maxPanSpeed != value ) {
            this._maxPanSpeed = value;
            onPropertyChanged( );
        }
    }

    public int getFocalLengthMode( ) {
        return _focalLengthMode;
    }
    public void setFocalLengthMode( int value ) {
        if( _focalLengthMode != value ) {
            this._focalLengthMode = value;
            onPropertyChanged( );
        }
    }

    public double getMinFocalLength( ) {
        return _minFocalLength;
    }
    public void setMinFocalLength( double value ) {
        if( _minFocalLength != value ) {
            this._minFocalLength = value;
            onPropertyChanged( );
        }
    }

    public double getMaxFocalLength( ) {
        return _maxFocalLength;
    }
    public void setMaxFocalLength( double value ) {
        if( _maxFocalLength != value ) {
            this._maxFocalLength = value;
            onPropertyChanged( );
        }
    }

    public double getMinFocalLengthScale( ) {
        return _minFocalLengthScale;
    }
    public void setMinFocalLengthScale( double value ) {
        if( _minFocalLengthScale != value ) {
            this._minFocalLengthScale = value;
            onPropertyChanged( );
        }
    }

    public double getMaxFocalLengthScale( ) {
        return _maxFocalLengthScale;
    }
    public void setMaxFocalLengthScale( double value ) {
        if( _maxFocalLengthScale != value ) {
            this._maxFocalLengthScale = value;
            onPropertyChanged( );
        }
    }

    public double getMinZoomVelocity( ) {
        return _minZoomVelocity;
    }
    public void setMinZoomVelocity( double value ) {
        if( _minZoomVelocity != value ) {
            this._minZoomVelocity = value;
            onPropertyChanged( );
        }
    }

    public double getMaxZoomVelocity( ) {
        return _maxZoomVelocity;
    }
    public void setMaxZoomVelocity( double value ) {
        if( _maxZoomVelocity != value ) {
            this._maxZoomVelocity = value;
            onPropertyChanged( );
        }
    }

    public double getMinZoomSpeed( ) {
        return _minZoomSpeed;
    }
    public void setMinZoomSpeed( double value ) {
        if( _minZoomSpeed != value ) {
            this._minZoomSpeed = value;
            onPropertyChanged( );
        }
    }

    public double getMaxZoomSpeed( ) {
        return _maxZoomSpeed;
    }
    public void setMaxZoomSpeed( double value ) {
        if( _maxZoomSpeed != value ) {
            this._maxZoomSpeed = value;
            onPropertyChanged( );
        }
    }

    public double getImageSensorWidth( ) {
        return _imageSensorWidth;
    }
    public void setImageSensorWidth( double value ) {
        if( _imageSensorWidth != value ) {
            this._imageSensorWidth = value;
            onPropertyChanged( );
        }
    }

    public double getImageSensorHeight( ) {
        return _imageSensorHeight;
    }
    public void setImageSensorHeight( double value ) {
        if( _imageSensorHeight != value ) {
            this._imageSensorHeight = value;
            onPropertyChanged( );
        }
    }

    public double getHomePanAngle( ) {
        return _homePanAngle;
    }
    public void setHomePanAngle( double value ) {
        if( _homePanAngle != value ) {
            this._homePanAngle = value;
            onPropertyChanged( );
        }
    }

    public double getHomeTiltAngle( ) {
        return _homeTiltAngle;
    }
    public void setHomeTiltAngle( double value ) {
        if( _homeTiltAngle != value ) {
            this._homeTiltAngle = value;
            onPropertyChanged( );
        }
    }

    public double getHomeFocalLength( ) {
        return _homeFocalLength;
    }
    public void setHomeFocalLength( double value ) {
        if( _homeFocalLength != value ) {
            this._homeFocalLength = value;
            onPropertyChanged( );
        }
    }

    public double getPanOffset( ) {
        return _panOffset;
    }
    public void setPanOffset( double value ) {
        if( _panOffset != value ) {
            this._panOffset = value;
            onPropertyChanged( );
        }
    }

    public double getTiltOffset( ) {
        return _tiltOffset;
    }
    public void setTiltOffset( double value ) {
        if( _tiltOffset != value ) {
            this._tiltOffset = value;
            onPropertyChanged( );
        }
    }

    public double getAimAltitude( ) {
        return _aimAltitude;
    }
    public void setAimAltitude( double value ) {
        if( _aimAltitude != value ) {
            this._aimAltitude = value;
            onPropertyChanged( );
        }
    }

    public double getMinimumTargetWidth( ) {
        return _minimumTargetWidth;
    }
    public void setMinimumTargetWidth( double value ) {
        if( _minimumTargetWidth != value ) {
            this._minimumTargetWidth = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getTargetLockTimeout( ) {
        return _targetLockTimeout;
    }
    public void setTargetLockTimeout( TimeSpan value ) {
        if( _targetLockTimeout != value ) {
            this._targetLockTimeout = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getUpdateStatusInterval( ) {
        return _updateStatusInterval;
    }
    public void setUpdateStatusInterval( TimeSpan value ) {
        if( _updateStatusInterval != value ) {
            this._updateStatusInterval = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getReadTimeout( ) {
        return _readTimeout;
    }
    public void setReadTimeout( TimeSpan value ) {
        if( _readTimeout != value ) {
            this._readTimeout = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getMoveCommandStatusDelay( ) {
        return _moveCommandStatusDelay;
    }
    public void setMoveCommandStatusDelay( TimeSpan value ) {
        if( _moveCommandStatusDelay != value ) {
            this._moveCommandStatusDelay = value;
            onPropertyChanged( );
        }
    }

    public String getPtzProfileName( ) {
        return _ptzProfileName;
    }
    public void setPtzProfileName( String value ) {
        if( _ptzProfileName != value ) {
            this._ptzProfileName = value;
            onPropertyChanged( );
        }
    }

    public String getPtzConfigurationToken( ) {
        return _ptzConfigurationToken;
    }
    public void setPtzConfigurationToken( String value ) {
        if( _ptzConfigurationToken != value ) {
            this._ptzConfigurationToken = value;
            onPropertyChanged( );
        }
    }

    public String getVideoSourceToken( ) {
        return _videoSourceToken;
    }
    public void setVideoSourceToken( String value ) {
        if( _videoSourceToken != value ) {
            this._videoSourceToken = value;
            onPropertyChanged( );
        }
    }


}
