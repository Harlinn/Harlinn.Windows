package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandRelativeMoveObject extends CameraCommandObject {

    private boolean _normalized = false;
    private Double _panAngle;
    private Double _tiltAngle;
    private Double _focalLength;
    private Double _panSpeed;
    private Double _tiltSpeed;
    private Double _zoomSpeed;

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
