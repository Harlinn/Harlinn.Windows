package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandAbsoluteMoveObject extends CameraCommandObject {

    private int _positionPanTiltMode = CameraPanTiltMode.Unknown;
    private Double _panAngle;
    private Double _tiltAngle;
    private int _positionFocalLengthMode = CameraFocalLengthMode.Unknown;
    private Double _focalLength;
    private int _speedPanTiltMode = CameraPanTiltMode.Unknown;
    private Double _panSpeed;
    private Double _tiltSpeed;
    private int _speedFocalLengthMode = CameraFocalLengthMode.Unknown;
    private Double _zoomSpeed;

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandAbsoluteMove;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandAbsoluteMoveObject( );
    }

    public int getPositionPanTiltMode( ) {
        return _positionPanTiltMode;
    }
    public void setPositionPanTiltMode( int value ) {
        if( !Comparer.equalsInt32( _positionPanTiltMode, value ) ) {
            _positionPanTiltMode = value;
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

    public int getPositionFocalLengthMode( ) {
        return _positionFocalLengthMode;
    }
    public void setPositionFocalLengthMode( int value ) {
        if( !Comparer.equalsInt32( _positionFocalLengthMode, value ) ) {
            _positionFocalLengthMode = value;
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

    public int getSpeedPanTiltMode( ) {
        return _speedPanTiltMode;
    }
    public void setSpeedPanTiltMode( int value ) {
        if( !Comparer.equalsInt32( _speedPanTiltMode, value ) ) {
            _speedPanTiltMode = value;
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

    public int getSpeedFocalLengthMode( ) {
        return _speedFocalLengthMode;
    }
    public void setSpeedFocalLengthMode( int value ) {
        if( !Comparer.equalsInt32( _speedFocalLengthMode, value ) ) {
            _speedFocalLengthMode = value;
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
        destination.writeInt32( _positionPanTiltMode );
        destination.writeNullableDouble( _panAngle );
        destination.writeNullableDouble( _tiltAngle );
        destination.writeInt32( _positionFocalLengthMode );
        destination.writeNullableDouble( _focalLength );
        destination.writeInt32( _speedPanTiltMode );
        destination.writeNullableDouble( _panSpeed );
        destination.writeNullableDouble( _tiltSpeed );
        destination.writeInt32( _speedFocalLengthMode );
        destination.writeNullableDouble( _zoomSpeed );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _positionPanTiltMode = source.readInt32( );
        _panAngle = source.readNullableDouble( );
        _tiltAngle = source.readNullableDouble( );
        _positionFocalLengthMode = source.readInt32( );
        _focalLength = source.readNullableDouble( );
        _speedPanTiltMode = source.readInt32( );
        _panSpeed = source.readNullableDouble( );
        _tiltSpeed = source.readNullableDouble( );
        _speedFocalLengthMode = source.readInt32( );
        _zoomSpeed = source.readNullableDouble( );
    }

}
