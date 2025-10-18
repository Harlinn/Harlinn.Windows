package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandRelativeMoveObject extends CameraCommandObject {

    public final int KIND = Kind.CameraCommandRelativeMove;

    private boolean _normalized = false;
    private Double _panAngle;
    private Double _tiltAngle;
    private Double _focalLength;
    private Double _panSpeed;
    private Double _tiltSpeed;
    private Double _zoomSpeed;

    public CameraCommandRelativeMoveObject( ) {
    }
    public CameraCommandRelativeMoveObject( byte objectState, Guid id, long rowVersion, Guid camera, DateTime timestamp, int deviceCommandSourceType, Guid deviceCommandSourceId, Guid reply, boolean normalized, Double panAngle, Double tiltAngle, Double focalLength, Double panSpeed, Double tiltSpeed, Double zoomSpeed ) {
        super( objectState, id, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        this._normalized = normalized;
        this._panAngle = panAngle;
        this._tiltAngle = tiltAngle;
        this._focalLength = focalLength;
        this._panSpeed = panSpeed;
        this._tiltSpeed = tiltSpeed;
        this._zoomSpeed = zoomSpeed;
    }

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandRelativeMove;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandRelativeMoveObject( );
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

    public Double getPanAngle( ) {
        return _panAngle;
    }
    public void setPanAngle( Double value ) {
        if( !Comparer.equalsNullableDouble( _panAngle, value ) ) {
            _panAngle = value;
            onPropertyChanged( );
        }
    }

    public Double getTiltAngle( ) {
        return _tiltAngle;
    }
    public void setTiltAngle( Double value ) {
        if( !Comparer.equalsNullableDouble( _tiltAngle, value ) ) {
            _tiltAngle = value;
            onPropertyChanged( );
        }
    }

    public Double getFocalLength( ) {
        return _focalLength;
    }
    public void setFocalLength( Double value ) {
        if( !Comparer.equalsNullableDouble( _focalLength, value ) ) {
            _focalLength = value;
            onPropertyChanged( );
        }
    }

    public Double getPanSpeed( ) {
        return _panSpeed;
    }
    public void setPanSpeed( Double value ) {
        if( !Comparer.equalsNullableDouble( _panSpeed, value ) ) {
            _panSpeed = value;
            onPropertyChanged( );
        }
    }

    public Double getTiltSpeed( ) {
        return _tiltSpeed;
    }
    public void setTiltSpeed( Double value ) {
        if( !Comparer.equalsNullableDouble( _tiltSpeed, value ) ) {
            _tiltSpeed = value;
            onPropertyChanged( );
        }
    }

    public Double getZoomSpeed( ) {
        return _zoomSpeed;
    }
    public void setZoomSpeed( Double value ) {
        if( !Comparer.equalsNullableDouble( _zoomSpeed, value ) ) {
            _zoomSpeed = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraCommandRelativeMoveObject )target;
        targetObject._normalized = this._normalized;
        targetObject._panAngle = this._panAngle;
        targetObject._tiltAngle = this._tiltAngle;
        targetObject._focalLength = this._focalLength;
        targetObject._panSpeed = this._panSpeed;
        targetObject._tiltSpeed = this._tiltSpeed;
        targetObject._zoomSpeed = this._zoomSpeed;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraCommandRelativeMoveObject)obj;
        if( !Comparer.equalsBoolean( this._normalized, other._normalized ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._panAngle, other._panAngle ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._tiltAngle, other._tiltAngle ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._focalLength, other._focalLength ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._panSpeed, other._panSpeed ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._tiltSpeed, other._tiltSpeed ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._zoomSpeed, other._zoomSpeed ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeBoolean( _normalized );
        destination.writeNullableDouble( _panAngle );
        destination.writeNullableDouble( _tiltAngle );
        destination.writeNullableDouble( _focalLength );
        destination.writeNullableDouble( _panSpeed );
        destination.writeNullableDouble( _tiltSpeed );
        destination.writeNullableDouble( _zoomSpeed );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _normalized = source.readBoolean( );
        _panAngle = source.readNullableDouble( );
        _tiltAngle = source.readNullableDouble( );
        _focalLength = source.readNullableDouble( );
        _panSpeed = source.readNullableDouble( );
        _tiltSpeed = source.readNullableDouble( );
        _zoomSpeed = source.readNullableDouble( );
    }

}
