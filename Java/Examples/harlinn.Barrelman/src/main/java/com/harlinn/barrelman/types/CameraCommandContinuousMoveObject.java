package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandContinuousMoveObject extends CameraCommandObject {

    private boolean _normalized = false;
    private Double _panVelocity;
    private Double _tiltVelocity;
    private Double _zoomVelocity;
    private TimeSpan _duration;

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandContinuousMove;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandContinuousMoveObject( );
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

    public Double getZoomVelocity( ) {
        return _zoomVelocity;
    }
    public void setZoomVelocity( Double value ) {
        if( _zoomVelocity != value ) {
            this._zoomVelocity = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getDuration( ) {
        return _duration;
    }
    public void setDuration( TimeSpan value ) {
        if( _duration != value ) {
            this._duration = value;
            onPropertyChanged( );
        }
    }


}
