package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GyroSpeedTimeseriesObject extends DoubleTimeseriesObject {

    private Guid _gyroDevice;

    @Override
    public int getObjectType( ) {
        return Kind.GyroSpeedTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GyroSpeedTimeseriesObject( );
    }

    public Guid getGyroDevice( ) {
        return _gyroDevice;
    }
    public void setGyroDevice( Guid value ) {
        if( !Comparer.equalsNullableGuid( _gyroDevice, value ) ) {
            _gyroDevice = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _gyroDevice );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _gyroDevice = source.readNullableGuid( );
    }

}
