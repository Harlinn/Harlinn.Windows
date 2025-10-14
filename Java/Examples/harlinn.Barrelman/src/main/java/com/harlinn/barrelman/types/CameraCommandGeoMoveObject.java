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
        if( !Comparer.equalsDouble( _latitude, value ) ) {
            _latitude = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( !Comparer.equalsDouble( _longitude, value ) ) {
            _longitude = value;
            onPropertyChanged( );
        }
    }

    public Double getAltitude( ) {
        return _altitude;
    }
    public void setAltitude( Double value ) {
        if( !Comparer.equalsNullableDouble( _altitude, value ) ) {
            _altitude = value;
            onPropertyChanged( );
        }
    }

    public Double getViewportWidth( ) {
        return _viewportWidth;
    }
    public void setViewportWidth( Double value ) {
        if( !Comparer.equalsNullableDouble( _viewportWidth, value ) ) {
            _viewportWidth = value;
            onPropertyChanged( );
        }
    }

    public Double getViewportHeight( ) {
        return _viewportHeight;
    }
    public void setViewportHeight( Double value ) {
        if( !Comparer.equalsNullableDouble( _viewportHeight, value ) ) {
            _viewportHeight = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeDouble( _latitude );
        destination.writeDouble( _longitude );
        destination.writeNullableDouble( _altitude );
        destination.writeNullableDouble( _viewportWidth );
        destination.writeNullableDouble( _viewportHeight );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _latitude = source.readDouble( );
        _longitude = source.readDouble( );
        _altitude = source.readNullableDouble( );
        _viewportWidth = source.readNullableDouble( );
        _viewportHeight = source.readNullableDouble( );
    }

}
