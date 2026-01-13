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

public class CameraZoomCalibrationValueObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.CameraZoomCalibrationValue;

    private long _rowVersion = 0;
    private Guid _zoomCalibration;
    private double _focalLength = 0.0;
    private double _focalLengthOffset = 0.0;

    public CameraZoomCalibrationValueObject( ) {
    }
    public CameraZoomCalibrationValueObject( byte objectState, Guid id, long rowVersion, Guid zoomCalibration, double focalLength, double focalLengthOffset ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._zoomCalibration = zoomCalibration;
        this._focalLength = focalLength;
        this._focalLengthOffset = focalLengthOffset;
    }

    @Override
    public int getObjectType( ) {
        return Kind.CameraZoomCalibrationValue;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraZoomCalibrationValueObject( );
    }

    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getZoomCalibration( ) {
        return _zoomCalibration;
    }
    public void setZoomCalibration( Guid value ) {
        if( !Comparer.equalsGuid( _zoomCalibration, value ) ) {
            _zoomCalibration = value;
            onPropertyChanged( );
        }
    }

    public double getFocalLength( ) {
        return _focalLength;
    }
    public void setFocalLength( double value ) {
        if( !Comparer.equalsDouble( _focalLength, value ) ) {
            _focalLength = value;
            onPropertyChanged( );
        }
    }

    public double getFocalLengthOffset( ) {
        return _focalLengthOffset;
    }
    public void setFocalLengthOffset( double value ) {
        if( !Comparer.equalsDouble( _focalLengthOffset, value ) ) {
            _focalLengthOffset = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraZoomCalibrationValueObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._zoomCalibration = this._zoomCalibration;
        targetObject._focalLength = this._focalLength;
        targetObject._focalLengthOffset = this._focalLengthOffset;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraZoomCalibrationValueObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._zoomCalibration, other._zoomCalibration ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._focalLength, other._focalLength ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._focalLengthOffset, other._focalLengthOffset ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _zoomCalibration );
        destination.writeDouble( _focalLength );
        destination.writeDouble( _focalLengthOffset );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _zoomCalibration = source.readGuid( );
        _focalLength = source.readDouble( );
        _focalLengthOffset = source.readDouble( );
    }

}
