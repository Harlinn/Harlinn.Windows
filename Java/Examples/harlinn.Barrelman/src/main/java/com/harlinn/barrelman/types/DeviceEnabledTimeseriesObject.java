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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( DeviceEnabledTimeseriesObject )target;
        targetObject._device = this._device;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (DeviceEnabledTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._device, other._device ) ) {
            return false;
        }
        return true;
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
