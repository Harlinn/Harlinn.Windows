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

public class CameraTiltCalibrationValueObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.CameraTiltCalibrationValue;

    private long _rowVersion = 0;
    private Guid _tiltCalibration;
    private double _panAngle = 0.0;
    private double _tiltOffset = 0.0;

    public CameraTiltCalibrationValueObject( ) {
    }
    public CameraTiltCalibrationValueObject( byte objectState, Guid id, long rowVersion, Guid tiltCalibration, double panAngle, double tiltOffset ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._tiltCalibration = tiltCalibration;
        this._panAngle = panAngle;
        this._tiltOffset = tiltOffset;
    }

    @Override
    public int getObjectType( ) {
        return Kind.CameraTiltCalibrationValue;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraTiltCalibrationValueObject( );
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

    public Guid getTiltCalibration( ) {
        return _tiltCalibration;
    }
    public void setTiltCalibration( Guid value ) {
        if( !Comparer.equalsGuid( _tiltCalibration, value ) ) {
            _tiltCalibration = value;
            onPropertyChanged( );
        }
    }

    public double getPanAngle( ) {
        return _panAngle;
    }
    public void setPanAngle( double value ) {
        if( !Comparer.equalsDouble( _panAngle, value ) ) {
            _panAngle = value;
            onPropertyChanged( );
        }
    }

    public double getTiltOffset( ) {
        return _tiltOffset;
    }
    public void setTiltOffset( double value ) {
        if( !Comparer.equalsDouble( _tiltOffset, value ) ) {
            _tiltOffset = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraTiltCalibrationValueObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._tiltCalibration = this._tiltCalibration;
        targetObject._panAngle = this._panAngle;
        targetObject._tiltOffset = this._tiltOffset;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraTiltCalibrationValueObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._tiltCalibration, other._tiltCalibration ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._panAngle, other._panAngle ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._tiltOffset, other._tiltOffset ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _tiltCalibration );
        destination.writeDouble( _panAngle );
        destination.writeDouble( _tiltOffset );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _tiltCalibration = source.readGuid( );
        _panAngle = source.readDouble( );
        _tiltOffset = source.readDouble( );
    }

}
