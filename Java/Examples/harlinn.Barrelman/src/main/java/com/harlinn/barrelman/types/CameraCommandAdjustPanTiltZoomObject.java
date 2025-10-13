package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandAdjustPanTiltZoomObject extends CameraCommandObject {

    private Double _x;
    private Double _y;
    private Double _z;

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandAdjustPanTiltZoom;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandAdjustPanTiltZoomObject( );
    }

    public Double getX( ) {
        return _x;
    }
    public void setX( Double value ) {
        if( _x != value ) {
            this._x = value;
            onPropertyChanged( );
        }
    }

    public Double getY( ) {
        return _y;
    }
    public void setY( Double value ) {
        if( _y != value ) {
            this._y = value;
            onPropertyChanged( );
        }
    }

    public Double getZ( ) {
        return _z;
    }
    public void setZ( Double value ) {
        if( _z != value ) {
            this._z = value;
            onPropertyChanged( );
        }
    }


}
