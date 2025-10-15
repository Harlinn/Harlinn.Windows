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
        if( !Comparer.equalsBoolean( _normalized, value ) ) {
            _normalized = value;
            onPropertyChanged( );
        }
    }

    public Double getPanVelocity( ) {
        return _panVelocity;
    }
    public void setPanVelocity( Double value ) {
        if( !Comparer.equalsNullableDouble( _panVelocity, value ) ) {
            _panVelocity = value;
            onPropertyChanged( );
        }
    }

    public Double getTiltVelocity( ) {
        return _tiltVelocity;
    }
    public void setTiltVelocity( Double value ) {
        if( !Comparer.equalsNullableDouble( _tiltVelocity, value ) ) {
            _tiltVelocity = value;
            onPropertyChanged( );
        }
    }

    public Double getZoomVelocity( ) {
        return _zoomVelocity;
    }
    public void setZoomVelocity( Double value ) {
        if( !Comparer.equalsNullableDouble( _zoomVelocity, value ) ) {
            _zoomVelocity = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getDuration( ) {
        return _duration;
    }
    public void setDuration( TimeSpan value ) {
        if( !Comparer.equalsNullableTimeSpan( _duration, value ) ) {
            _duration = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraCommandContinuousMoveObject )target;
        targetObject._normalized = this._normalized;
        targetObject._panVelocity = this._panVelocity;
        targetObject._tiltVelocity = this._tiltVelocity;
        targetObject._zoomVelocity = this._zoomVelocity;
        targetObject._duration = this._duration;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraCommandContinuousMoveObject)obj;
        if( !Comparer.equalsBoolean( this._normalized, other._normalized ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._panVelocity, other._panVelocity ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._tiltVelocity, other._tiltVelocity ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._zoomVelocity, other._zoomVelocity ) ) {
            return false;
        }
        if( !Comparer.equalsNullableTimeSpan( this._duration, other._duration ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeBoolean( _normalized );
        destination.writeNullableDouble( _panVelocity );
        destination.writeNullableDouble( _tiltVelocity );
        destination.writeNullableDouble( _zoomVelocity );
        destination.writeNullableTimeSpan( _duration );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _normalized = source.readBoolean( );
        _panVelocity = source.readNullableDouble( );
        _tiltVelocity = source.readNullableDouble( );
        _zoomVelocity = source.readNullableDouble( );
        _duration = source.readNullableTimeSpan( );
    }

}
