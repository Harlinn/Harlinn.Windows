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
