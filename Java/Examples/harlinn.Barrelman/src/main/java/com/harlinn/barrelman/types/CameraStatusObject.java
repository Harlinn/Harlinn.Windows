package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraStatusObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _camera;
    private Guid _track;
    private DateTime _timestamp;
    private int _positionPanTiltMode = CameraPanTiltMode.Unknown;
    private double _panAngle = 0.0;
    private double _tiltAngle = 0.0;
    private int _positionFocalLengthMode = CameraFocalLengthMode.Unknown;
    private double _focalLength = 0.0;
    private int _panTiltMoveStatus = CameraMoveStatus.Unknown;
    private int _zoomMoveStatus = CameraMoveStatus.Unknown;
    private int _velocityPanTiltMode = CameraPanTiltMode.Unknown;
    private Double _panVelocity;
    private Double _tiltVelocity;
    private int _velocityFocalLengthMode = CameraFocalLengthMode.Unknown;
    private Double _zoomVelocity;
    private int _activeFeatures = CameraFeatures.None;
    private String _error = "";

    @Override
    public int getObjectType( ) {
        return Kind.CameraStatus;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraStatusObject( );
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

    public Guid getTrack( ) {
        return _track;
    }
    public void setTrack( Guid value ) {
        if( _track != value ) {
            this._track = value;
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

    public int getPositionPanTiltMode( ) {
        return _positionPanTiltMode;
    }
    public void setPositionPanTiltMode( int value ) {
        if( _positionPanTiltMode != value ) {
            this._positionPanTiltMode = value;
            onPropertyChanged( );
        }
    }

    public double getPanAngle( ) {
        return _panAngle;
    }
    public void setPanAngle( double value ) {
        if( _panAngle != value ) {
            this._panAngle = value;
            onPropertyChanged( );
        }
    }

    public double getTiltAngle( ) {
        return _tiltAngle;
    }
    public void setTiltAngle( double value ) {
        if( _tiltAngle != value ) {
            this._tiltAngle = value;
            onPropertyChanged( );
        }
    }

    public int getPositionFocalLengthMode( ) {
        return _positionFocalLengthMode;
    }
    public void setPositionFocalLengthMode( int value ) {
        if( _positionFocalLengthMode != value ) {
            this._positionFocalLengthMode = value;
            onPropertyChanged( );
        }
    }

    public double getFocalLength( ) {
        return _focalLength;
    }
    public void setFocalLength( double value ) {
        if( _focalLength != value ) {
            this._focalLength = value;
            onPropertyChanged( );
        }
    }

    public int getPanTiltMoveStatus( ) {
        return _panTiltMoveStatus;
    }
    public void setPanTiltMoveStatus( int value ) {
        if( _panTiltMoveStatus != value ) {
            this._panTiltMoveStatus = value;
            onPropertyChanged( );
        }
    }

    public int getZoomMoveStatus( ) {
        return _zoomMoveStatus;
    }
    public void setZoomMoveStatus( int value ) {
        if( _zoomMoveStatus != value ) {
            this._zoomMoveStatus = value;
            onPropertyChanged( );
        }
    }

    public int getVelocityPanTiltMode( ) {
        return _velocityPanTiltMode;
    }
    public void setVelocityPanTiltMode( int value ) {
        if( _velocityPanTiltMode != value ) {
            this._velocityPanTiltMode = value;
            onPropertyChanged( );
        }
    }

    public Double getPanVelocity( ) {
        return _panVelocity;
    }
    public void setPanVelocity( Double value ) {
        if( _panVelocity != value ) {
            this._panVelocity = value;
            onPropertyChanged( );
        }
    }

    public Double getTiltVelocity( ) {
        return _tiltVelocity;
    }
    public void setTiltVelocity( Double value ) {
        if( _tiltVelocity != value ) {
            this._tiltVelocity = value;
            onPropertyChanged( );
        }
    }

    public int getVelocityFocalLengthMode( ) {
        return _velocityFocalLengthMode;
    }
    public void setVelocityFocalLengthMode( int value ) {
        if( _velocityFocalLengthMode != value ) {
            this._velocityFocalLengthMode = value;
            onPropertyChanged( );
        }
    }

    public Double getZoomVelocity( ) {
        return _zoomVelocity;
    }
    public void setZoomVelocity( Double value ) {
        if( _zoomVelocity != value ) {
            this._zoomVelocity = value;
            onPropertyChanged( );
        }
    }

    public int getActiveFeatures( ) {
        return _activeFeatures;
    }
    public void setActiveFeatures( int value ) {
        if( _activeFeatures != value ) {
            this._activeFeatures = value;
            onPropertyChanged( );
        }
    }

    public String getError( ) {
        return _error;
    }
    public void setError( String value ) {
        if( _error != value ) {
            this._error = value;
            onPropertyChanged( );
        }
    }


}
