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

public class MediaServiceOptionsObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.MediaServiceOptions;

    private long _rowVersion = 0;
    private Guid _mediaService;
    private DateTime _timestamp;
    private int _rtspPortNumber = 0;
    private int _httpPortNumber = 0;

    public MediaServiceOptionsObject( ) {
    }
    public MediaServiceOptionsObject( byte objectState, Guid id, long rowVersion, Guid mediaService, DateTime timestamp, int rtspPortNumber, int httpPortNumber ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._mediaService = mediaService;
        this._timestamp = timestamp;
        this._rtspPortNumber = rtspPortNumber;
        this._httpPortNumber = httpPortNumber;
    }

    @Override
    public int getObjectType( ) {
        return Kind.MediaServiceOptions;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaServiceOptionsObject( );
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

    public Guid getMediaService( ) {
        return _mediaService;
    }
    public void setMediaService( Guid value ) {
        if( !Comparer.equalsGuid( _mediaService, value ) ) {
            _mediaService = value;
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

    public int getRtspPortNumber( ) {
        return _rtspPortNumber;
    }
    public void setRtspPortNumber( int value ) {
        if( !Comparer.equalsInt32( _rtspPortNumber, value ) ) {
            _rtspPortNumber = value;
            onPropertyChanged( );
        }
    }

    public int getHttpPortNumber( ) {
        return _httpPortNumber;
    }
    public void setHttpPortNumber( int value ) {
        if( !Comparer.equalsInt32( _httpPortNumber, value ) ) {
            _httpPortNumber = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( MediaServiceOptionsObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._mediaService = this._mediaService;
        targetObject._timestamp = this._timestamp;
        targetObject._rtspPortNumber = this._rtspPortNumber;
        targetObject._httpPortNumber = this._httpPortNumber;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (MediaServiceOptionsObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._mediaService, other._mediaService ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._rtspPortNumber, other._rtspPortNumber ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._httpPortNumber, other._httpPortNumber ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _mediaService );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _rtspPortNumber );
        destination.writeInt32( _httpPortNumber );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _mediaService = source.readGuid( );
        _timestamp = source.readDateTime( );
        _rtspPortNumber = source.readInt32( );
        _httpPortNumber = source.readInt32( );
    }

}
