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

public class DeviceEnabledTimeseriesObject extends BooleanTimeseriesObject {

    public final int KIND = Kind.DeviceEnabledTimeseries;

    private Guid _device;

    public DeviceEnabledTimeseriesObject( ) {
    }
    public DeviceEnabledTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid device ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._device = device;
    }

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
