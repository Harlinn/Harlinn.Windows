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
        if( !Comparer.equalsNullableDouble( _x, value ) ) {
            _x = value;
            onPropertyChanged( );
        }
    }

    public Double getY( ) {
        return _y;
    }
    public void setY( Double value ) {
        if( !Comparer.equalsNullableDouble( _y, value ) ) {
            _y = value;
            onPropertyChanged( );
        }
    }

    public Double getZ( ) {
        return _z;
    }
    public void setZ( Double value ) {
        if( !Comparer.equalsNullableDouble( _z, value ) ) {
            _z = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraCommandAdjustPanTiltZoomObject )target;
        targetObject._x = this._x;
        targetObject._y = this._y;
        targetObject._z = this._z;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraCommandAdjustPanTiltZoomObject)obj;
        if( !Comparer.equalsNullableDouble( this._x, other._x ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._y, other._y ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._z, other._z ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableDouble( _x );
        destination.writeNullableDouble( _y );
        destination.writeNullableDouble( _z );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _x = source.readNullableDouble( );
        _y = source.readNullableDouble( );
        _z = source.readNullableDouble( );
    }

}
