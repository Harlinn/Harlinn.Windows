package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandStopObject extends CameraCommandObject {

    private boolean _panTilt = false;
    private boolean _zoom = false;

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandStop;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandStopObject( );
    }

    public boolean getPanTilt( ) {
        return _panTilt;
    }
    public void setPanTilt( boolean value ) {
        if( _panTilt != value ) {
            this._panTilt = value;
            onPropertyChanged( );
        }
    }

    public boolean getZoom( ) {
        return _zoom;
    }
    public void setZoom( boolean value ) {
        if( _zoom != value ) {
            this._zoom = value;
            onPropertyChanged( );
        }
    }


}
