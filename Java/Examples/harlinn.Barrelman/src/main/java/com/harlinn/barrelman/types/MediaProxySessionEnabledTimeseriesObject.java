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

public class MediaProxySessionEnabledTimeseriesObject extends BooleanTimeseriesObject {

    public final int KIND = Kind.MediaProxySessionEnabledTimeseries;

    private Guid _proxySession;

    public MediaProxySessionEnabledTimeseriesObject( ) {
    }
    public MediaProxySessionEnabledTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid proxySession ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._proxySession = proxySession;
    }

    @Override
    public int getObjectType( ) {
        return Kind.MediaProxySessionEnabledTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaProxySessionEnabledTimeseriesObject( );
    }

    public Guid getProxySession( ) {
        return _proxySession;
    }
    public void setProxySession( Guid value ) {
        if( !Comparer.equalsNullableGuid( _proxySession, value ) ) {
            _proxySession = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( MediaProxySessionEnabledTimeseriesObject )target;
        targetObject._proxySession = this._proxySession;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (MediaProxySessionEnabledTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._proxySession, other._proxySession ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _proxySession );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _proxySession = source.readNullableGuid( );
    }

}
