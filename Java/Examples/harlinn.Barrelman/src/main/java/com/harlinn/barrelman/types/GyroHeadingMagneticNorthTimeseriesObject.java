package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GyroHeadingMagneticNorthTimeseriesObject extends DoubleTimeseriesObject {

    private Guid _gyroDevice;

    @Override
    public int getObjectType( ) {
        return Kind.GyroHeadingMagneticNorthTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GyroHeadingMagneticNorthTimeseriesObject( );
    }

    public Guid getGyroDevice( ) {
        return _gyroDevice;
    }
    public void setGyroDevice( Guid value ) {
        if( _gyroDevice != value ) {
            this._gyroDevice = value;
            onPropertyChanged( );
        }
    }


}
