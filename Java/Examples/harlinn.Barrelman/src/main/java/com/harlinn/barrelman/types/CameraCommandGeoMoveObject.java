package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandGeoMoveObject extends CameraCommandObject {

    private double _latitude = 0.0;
    private double _longitude = 0.0;
    private Double _altitude;
    private Double _viewportWidth;
    private Double _viewportHeight;

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandGeoMove;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandGeoMoveObject( );
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

    public Double getAltitude( ) {
        return _altitude;
    }
    public void setAltitude( Double value ) {
        if( _altitude != value ) {
            this._altitude = value;
            onPropertyChanged( );
        }
    }

    public Double getViewportWidth( ) {
        return _viewportWidth;
    }
    public void setViewportWidth( Double value ) {
        if( _viewportWidth != value ) {
            this._viewportWidth = value;
            onPropertyChanged( );
        }
    }

    public Double getViewportHeight( ) {
        return _viewportHeight;
    }
    public void setViewportHeight( Double value ) {
        if( _viewportHeight != value ) {
            this._viewportHeight = value;
            onPropertyChanged( );
        }
    }


}
