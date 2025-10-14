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
        if( !Comparer.equalsDouble( _radius, value ) ) {
            _radius = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeDouble( _radius );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _radius = source.readDouble( );
    }

}
