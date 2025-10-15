package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraPanCalibrationValueObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _panCalibration;
    private double _panAngle = 0.0;
    private double _panOffset = 0.0;

    @Override
    public int getObjectType( ) {
        return Kind.CameraPanCalibrationValue;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraPanCalibrationValueObject( );
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

    public Guid getPanCalibration( ) {
        return _panCalibration;
    }
    public void setPanCalibration( Guid value ) {
        if( !Comparer.equalsGuid( _panCalibration, value ) ) {
            _panCalibration = value;
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

    public double getPanOffset( ) {
        return _panOffset;
    }
    public void setPanOffset( double value ) {
        if( !Comparer.equalsDouble( _panOffset, value ) ) {
            _panOffset = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraPanCalibrationValueObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._panCalibration = this._panCalibration;
        targetObject._panAngle = this._panAngle;
        targetObject._panOffset = this._panOffset;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraPanCalibrationValueObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._panCalibration, other._panCalibration ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._panAngle, other._panAngle ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._panOffset, other._panOffset ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _panCalibration );
        destination.writeDouble( _panAngle );
        destination.writeDouble( _panOffset );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _panCalibration = source.readGuid( );
        _panAngle = source.readDouble( );
        _panOffset = source.readDouble( );
    }

}
