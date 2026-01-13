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

public class MediaProxySessionFileObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.MediaProxySessionFile;

    private long _rowVersion = 0;
    private Guid _proxySession;
    private DateTime _timestamp;
    private String _streamName = "";

    public MediaProxySessionFileObject( ) {
    }
    public MediaProxySessionFileObject( byte objectState, Guid id, long rowVersion, Guid proxySession, DateTime timestamp, String streamName ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._proxySession = proxySession;
        this._timestamp = timestamp;
        this._streamName = streamName;
    }

    @Override
    public int getObjectType( ) {
        return Kind.MediaProxySessionFile;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaProxySessionFileObject( );
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

    public Guid getProxySession( ) {
        return _proxySession;
    }
    public void setProxySession( Guid value ) {
        if( !Comparer.equalsGuid( _proxySession, value ) ) {
            _proxySession = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( !Comparer.equalsDateTime( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
    }

    public String getStreamName( ) {
        return _streamName;
    }
    public void setStreamName( String value ) {
        if( !Comparer.equalsString( _streamName, value ) ) {
            _streamName = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( MediaProxySessionFileObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._proxySession = this._proxySession;
        targetObject._timestamp = this._timestamp;
        targetObject._streamName = this._streamName;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (MediaProxySessionFileObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._proxySession, other._proxySession ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._streamName, other._streamName ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _proxySession );
        destination.writeDateTime( _timestamp );
        destination.writeStringUtf8( _streamName );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _proxySession = source.readGuid( );
        _timestamp = source.readDateTime( );
        _streamName = source.readString( );
    }

}
