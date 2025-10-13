package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraZoomCalibrationValueObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _zoomCalibration;
    private double _focalLength = 0.0;
    private double _focalLengthOffset = 0.0;

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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getZoomCalibration( ) {
        return _zoomCalibration;
    }
    public void setZoomCalibration( Guid value ) {
        if( _zoomCalibration != value ) {
            this._zoomCalibration = value;
            onPropertyChanged( );
        }
    }

    public double getFocalLength( ) {
        return _focalLength;
    }
    public void setFocalLength( double value ) {
        if( _focalLength != value ) {
            this._focalLength = value;
            onPropertyChanged( );
        }
    }

    public double getFocalLengthOffset( ) {
        return _focalLengthOffset;
    }
    public void setFocalLengthOffset( double value ) {
        if( _focalLengthOffset != value ) {
            this._focalLengthOffset = value;
            onPropertyChanged( );
        }
    }


}
