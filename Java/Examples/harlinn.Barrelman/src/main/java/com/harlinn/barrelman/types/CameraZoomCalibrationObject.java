package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraZoomCalibrationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _camera;
    private DateTime _timestamp;

    @Override
    public int getObjectType( ) {
        return Kind.CameraZoomCalibration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraZoomCalibrationObject( );
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

    public Guid getCamera( ) {
        return _camera;
    }
    public void setCamera( Guid value ) {
        if( _camera != value ) {
            this._camera = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( _timestamp != value ) {
            this._timestamp = value;
            onPropertyChanged( );
        }
    }


}
