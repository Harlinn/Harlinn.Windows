package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class DeviceEnabledTimeseriesObject extends BooleanTimeseriesObject {

    private Guid _device;

    @Override
    public int getObjectType( ) {
        return Kind.DeviceEnabledTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new DeviceEnabledTimeseriesObject( );
    }

    public Guid getDevice( ) {
        return _device;
    }
    public void setDevice( Guid value ) {
        if( !Comparer.equalsNullableGuid( _device, value ) ) {
            _device = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _device );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _device = source.readNullableGuid( );
    }

}
