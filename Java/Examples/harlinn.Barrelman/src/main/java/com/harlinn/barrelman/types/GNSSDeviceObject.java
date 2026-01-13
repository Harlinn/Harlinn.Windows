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

public class GNSSDeviceObject extends DeviceObject {

    public final int KIND = Kind.GNSSDevice;

    private Guid _latitudeTimeseries;
    private Guid _longitudeTimeseries;
    private Guid _altitudeTimeseries;

    public GNSSDeviceObject( ) {
    }
    public GNSSDeviceObject( byte objectState, Guid id, long rowVersion, Guid host, String name, String description, Guid enabledTimeseries, Guid latitudeTimeseries, Guid longitudeTimeseries, Guid altitudeTimeseries ) {
        super( objectState, id, rowVersion, host, name, description, enabledTimeseries );
        this._latitudeTimeseries = latitudeTimeseries;
        this._longitudeTimeseries = longitudeTimeseries;
        this._altitudeTimeseries = altitudeTimeseries;
    }

    @Override
    public int getObjectType( ) {
        return Kind.GNSSDevice;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GNSSDeviceObject( );
    }

    public Guid getLatitudeTimeseries( ) {
        return _latitudeTimeseries;
    }
    public void setLatitudeTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _latitudeTimeseries, value ) ) {
            _latitudeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getLongitudeTimeseries( ) {
        return _longitudeTimeseries;
    }
    public void setLongitudeTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _longitudeTimeseries, value ) ) {
            _longitudeTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getAltitudeTimeseries( ) {
        return _altitudeTimeseries;
    }
    public void setAltitudeTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _altitudeTimeseries, value ) ) {
            _altitudeTimeseries = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( GNSSDeviceObject )target;
        targetObject._latitudeTimeseries = this._latitudeTimeseries;
        targetObject._longitudeTimeseries = this._longitudeTimeseries;
        targetObject._altitudeTimeseries = this._altitudeTimeseries;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (GNSSDeviceObject)obj;
        if( !Comparer.equalsNullableGuid( this._latitudeTimeseries, other._latitudeTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._longitudeTimeseries, other._longitudeTimeseries ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._altitudeTimeseries, other._altitudeTimeseries ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _latitudeTimeseries );
        destination.writeNullableGuid( _longitudeTimeseries );
        destination.writeNullableGuid( _altitudeTimeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _latitudeTimeseries = source.readNullableGuid( );
        _longitudeTimeseries = source.readNullableGuid( );
        _altitudeTimeseries = source.readNullableGuid( );
    }

}
