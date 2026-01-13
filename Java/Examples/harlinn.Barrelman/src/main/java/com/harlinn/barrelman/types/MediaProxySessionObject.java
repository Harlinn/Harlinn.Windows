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

public class MediaProxySessionObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.MediaProxySession;

    private long _rowVersion = 0;
    private Guid _service;
    private String _name = "";
    private Guid _enabledTimeseries;

    public MediaProxySessionObject( ) {
    }
    public MediaProxySessionObject( byte objectState, Guid id, long rowVersion, Guid service, String name, Guid enabledTimeseries ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._service = service;
        this._name = name;
        this._enabledTimeseries = enabledTimeseries;
    }

    @Override
    public int getObjectType( ) {
        return Kind.MediaProxySession;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaProxySessionObject( );
    }

    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getService( ) {
        return _service;
    }
    public void setService( Guid value ) {
        if( !Comparer.equalsGuid( _service, value ) ) {
            _service = value;
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
        var targetObject = ( MediaProxySessionObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._service = this._service;
        targetObject._name = this._name;
        targetObject._enabledTimeseries = this._enabledTimeseries;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (MediaProxySessionObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._service, other._service ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
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
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _service );
        destination.writeStringUtf8( _name );
        destination.writeNullableGuid( _enabledTimeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _service = source.readGuid( );
        _name = source.readString( );
        _enabledTimeseries = source.readNullableGuid( );
    }

}
