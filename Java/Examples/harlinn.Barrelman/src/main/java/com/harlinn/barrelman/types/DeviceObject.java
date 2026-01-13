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

public abstract class DeviceObject extends ItemObject {

    public final int KIND = Kind.Device;

    private Guid _host;
    private String _name = "";
    private String _description = "";
    private Guid _enabledTimeseries;

    public DeviceObject( ) {
    }
    public DeviceObject( byte objectState, Guid id, long rowVersion, Guid host, String name, String description, Guid enabledTimeseries ) {
        super( objectState, id, rowVersion );
        this._host = host;
        this._name = name;
        this._description = description;
        this._enabledTimeseries = enabledTimeseries;
    }


    public Guid getHost( ) {
        return _host;
    }
    public void setHost( Guid value ) {
        if( !Comparer.equalsGuid( _host, value ) ) {
            _host = value;
            onPropertyChanged( );
        }
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( !Comparer.equalsString( _name, value ) ) {
            _name = value;
            onPropertyChanged( );
        }
    }

    public String getDescription( ) {
        return _description;
    }
    public void setDescription( String value ) {
        if( !Comparer.equalsString( _description, value ) ) {
            _description = value;
            onPropertyChanged( );
        }
    }

    public Guid getEnabledTimeseries( ) {
        return _enabledTimeseries;
    }
    public void setEnabledTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _enabledTimeseries, value ) ) {
            _enabledTimeseries = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( DeviceObject )target;
        targetObject._host = this._host;
        targetObject._name = this._name;
        targetObject._description = this._description;
        targetObject._enabledTimeseries = this._enabledTimeseries;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (DeviceObject)obj;
        if( !Comparer.equalsGuid( this._host, other._host ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._description, other._description ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._enabledTimeseries, other._enabledTimeseries ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeGuid( _host );
        destination.writeStringUtf8( _name );
        destination.writeStringUtf8( _description );
        destination.writeNullableGuid( _enabledTimeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _host = source.readGuid( );
        _name = source.readString( );
        _description = source.readString( );
        _enabledTimeseries = source.readNullableGuid( );
    }

}
