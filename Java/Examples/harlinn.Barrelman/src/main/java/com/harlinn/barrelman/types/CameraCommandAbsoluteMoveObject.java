package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandAbsoluteMoveObject extends CameraCommandObject {

    private int _positionPanTiltMode = CameraPanTiltMode.Unknown;
    private Double _panAngle;
    private Double _tiltAngle;
    private int _positionFocalLengthMode = CameraFocalLengthMode.Unknown;
    private Double _focalLength;
    private int _speedPanTiltMode = CameraPanTiltMode.Unknown;
    private Double _panSpeed;
    private Double _tiltSpeed;
    private int _speedFocalLengthMode = CameraFocalLengthMode.Unknown;
    private Double _zoomSpeed;

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandAbsoluteMove;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandAbsoluteMoveObject( );
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

    public Double getPanAngle( ) {
        return _panAngle;
    }
    public void setPanAngle( Double value ) {
        if( _panAngle != value ) {
            this._panAngle = value;
            onPropertyChanged( );
        }
    }

    public Double getTiltAngle( ) {
        return _tiltAngle;
    }
    public void setTiltAngle( Double value ) {
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

    public Double getFocalLength( ) {
        return _focalLength;
    }
    public void setFocalLength( Double value ) {
        if( _focalLength != value ) {
            this._focalLength = value;
            onPropertyChanged( );
        }
    }

    public int getSpeedPanTiltMode( ) {
        return _speedPanTiltMode;
    }
    public void setSpeedPanTiltMode( int value ) {
        if( _speedPanTiltMode != value ) {
            this._speedPanTiltMode = value;
            onPropertyChanged( );
        }
    }

    public Double getPanSpeed( ) {
        return _panSpeed;
    }
    public void setPanSpeed( Double value ) {
        if( _panSpeed != value ) {
            this._panSpeed = value;
            onPropertyChanged( );
        }
    }

    public Double getTiltSpeed( ) {
        return _tiltSpeed;
    }
    public void setTiltSpeed( Double value ) {
        if( _tiltSpeed != value ) {
            this._tiltSpeed = value;
            onPropertyChanged( );
        }
    }

    public int getSpeedFocalLengthMode( ) {
        return _speedFocalLengthMode;
    }
    public void setSpeedFocalLengthMode( int value ) {
        if( _speedFocalLengthMode != value ) {
            this._speedFocalLengthMode = value;
            onPropertyChanged( );
        }
    }

    public Double getZoomSpeed( ) {
        return _zoomSpeed;
    }
    public void setZoomSpeed( Double value ) {
        if( _zoomSpeed != value ) {
            this._zoomSpeed = value;
            onPropertyChanged( );
        }
    }


}
