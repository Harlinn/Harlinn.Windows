/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandAbsoluteMoveObject extends CameraCommandObject {

    public final int KIND = Kind.CameraCommandAbsoluteMove;

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

    public CameraCommandAbsoluteMoveObject( ) {
    }
    public CameraCommandAbsoluteMoveObject( byte objectState, Guid id, long rowVersion, Guid camera, DateTime timestamp, int deviceCommandSourceType, Guid deviceCommandSourceId, Guid reply, int positionPanTiltMode, Double panAngle, Double tiltAngle, int positionFocalLengthMode, Double focalLength, int speedPanTiltMode, Double panSpeed, Double tiltSpeed, int speedFocalLengthMode, Double zoomSpeed ) {
        super( objectState, id, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        this._positionPanTiltMode = positionPanTiltMode;
        this._panAngle = panAngle;
        this._tiltAngle = tiltAngle;
        this._positionFocalLengthMode = positionFocalLengthMode;
        this._focalLength = focalLength;
        this._speedPanTiltMode = speedPanTiltMode;
        this._panSpeed = panSpeed;
        this._tiltSpeed = tiltSpeed;
        this._speedFocalLengthMode = speedFocalLengthMode;
        this._zoomSpeed = zoomSpeed;
    }

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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraCommandAbsoluteMoveObject )target;
        targetObject._positionPanTiltMode = this._positionPanTiltMode;
        targetObject._panAngle = this._panAngle;
        targetObject._tiltAngle = this._tiltAngle;
        targetObject._positionFocalLengthMode = this._positionFocalLengthMode;
        targetObject._focalLength = this._focalLength;
        targetObject._speedPanTiltMode = this._speedPanTiltMode;
        targetObject._panSpeed = this._panSpeed;
        targetObject._tiltSpeed = this._tiltSpeed;
        targetObject._speedFocalLengthMode = this._speedFocalLengthMode;
        targetObject._zoomSpeed = this._zoomSpeed;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraCommandAbsoluteMoveObject)obj;
        if( !Comparer.equalsInt32( this._positionPanTiltMode, other._positionPanTiltMode ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._panAngle, other._panAngle ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._tiltAngle, other._tiltAngle ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._positionFocalLengthMode, other._positionFocalLengthMode ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._focalLength, other._focalLength ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._speedPanTiltMode, other._speedPanTiltMode ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._panSpeed, other._panSpeed ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._tiltSpeed, other._tiltSpeed ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._speedFocalLengthMode, other._speedFocalLengthMode ) ) {
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
