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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getPanCalibration( ) {
        return _panCalibration;
    }
    public void setPanCalibration( Guid value ) {
        if( _panCalibration != value ) {
            this._panCalibration = value;
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

    public double getPanOffset( ) {
        return _panOffset;
    }
    public void setPanOffset( double value ) {
        if( _panOffset != value ) {
            this._panOffset = value;
            onPropertyChanged( );
        }
    }


}
