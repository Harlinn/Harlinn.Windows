package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandRelativeMoveObject extends CameraCommandObject {

    private boolean _normalized = false;
    private Double _panAngle;
    private Double _tiltAngle;
    private Double _focalLength;
    private Double _panSpeed;
    private Double _tiltSpeed;
    private Double _zoomSpeed;

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandRelativeMove;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandRelativeMoveObject( );
    }

    public boolean getNormalized( ) {
        return _normalized;
    }
    public void setNormalized( boolean value ) {
        if( _normalized != value ) {
            this._normalized = value;
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

    public Double getFocalLength( ) {
        return _focalLength;
    }
    public void setFocalLength( Double value ) {
        if( _focalLength != value ) {
            this._focalLength = value;
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
