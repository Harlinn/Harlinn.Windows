package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CircularZoneObject extends ZoneObject {

    private double _radius = 0.0;

    @Override
    public int getObjectType( ) {
        return Kind.CircularZone;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CircularZoneObject( );
    }

    public double getRadius( ) {
        return _radius;
    }
    public void setRadius( double value ) {
        if( _radius != value ) {
            this._radius = value;
            onPropertyChanged( );
        }
    }


}
