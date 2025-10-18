package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandGeoMoveObject extends CameraCommandObject {

    public final int KIND = Kind.CameraCommandGeoMove;

    private double _latitude = 0.0;
    private double _longitude = 0.0;
    private Double _altitude;
    private Double _viewportWidth;
    private Double _viewportHeight;

    public CameraCommandGeoMoveObject( ) {
    }
    public CameraCommandGeoMoveObject( byte objectState, Guid id, long rowVersion, Guid camera, DateTime timestamp, int deviceCommandSourceType, Guid deviceCommandSourceId, Guid reply, double latitude, double longitude, Double altitude, Double viewportWidth, Double viewportHeight ) {
        super( objectState, id, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        this._latitude = latitude;
        this._longitude = longitude;
        this._altitude = altitude;
        this._viewportWidth = viewportWidth;
        this._viewportHeight = viewportHeight;
    }

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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraCommandGeoMoveObject )target;
        targetObject._latitude = this._latitude;
        targetObject._longitude = this._longitude;
        targetObject._altitude = this._altitude;
        targetObject._viewportWidth = this._viewportWidth;
        targetObject._viewportHeight = this._viewportHeight;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraCommandGeoMoveObject)obj;
        if( !Comparer.equalsDouble( this._latitude, other._latitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._longitude, other._longitude ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._altitude, other._altitude ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._viewportWidth, other._viewportWidth ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._viewportHeight, other._viewportHeight ) ) {
            return false;
        }
        return true;
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
