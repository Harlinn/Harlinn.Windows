package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraTiltCalibrationValueObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _tiltCalibration;
    private double _panAngle = 0.0;
    private double _tiltOffset = 0.0;

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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getTiltCalibration( ) {
        return _tiltCalibration;
    }
    public void setTiltCalibration( Guid value ) {
        if( _tiltCalibration != value ) {
            this._tiltCalibration = value;
            onPropertyChanged( );
        }
    }

    public double getPanAngle( ) {
        return _panAngle;
    }
    public void setPanAngle( double value ) {
        if( _panAngle != value ) {
            this._panAngle = value;
            onPropertyChanged( );
        }
    }

    public double getTiltOffset( ) {
        return _tiltOffset;
    }
    public void setTiltOffset( double value ) {
        if( _tiltOffset != value ) {
            this._tiltOffset = value;
            onPropertyChanged( );
        }
    }


}
