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

public class RadomeCommandReplyObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.RadomeCommandReply;

    private long _rowVersion = 0;
    private Guid _radome;
    private DateTime _timestamp;
    private Guid _command;
    private int _status = DeviceCommandReplyStatus.Unknown;
    private String _message = "";

    public RadomeCommandReplyObject( ) {
    }
    public RadomeCommandReplyObject( byte objectState, Guid id, long rowVersion, Guid radome, DateTime timestamp, Guid command, int status, String message ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._radome = radome;
        this._timestamp = timestamp;
        this._command = command;
        this._status = status;
        this._message = message;
    }

    @Override
    public int getObjectType( ) {
        return Kind.RadomeCommandReply;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadomeCommandReplyObject( );
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

    public Guid getRadome( ) {
        return _radome;
    }
    public void setRadome( Guid value ) {
        if( !Comparer.equalsGuid( _radome, value ) ) {
            _radome = value;
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

    public Guid getCommand( ) {
        return _command;
    }
    public void setCommand( Guid value ) {
        if( !Comparer.equalsNullableGuid( _command, value ) ) {
            _command = value;
            onPropertyChanged( );
        }
    }

    public int getStatus( ) {
        return _status;
    }
    public void setStatus( int value ) {
        if( !Comparer.equalsInt32( _status, value ) ) {
            _status = value;
            onPropertyChanged( );
        }
    }

    public String getMessage( ) {
        return _message;
    }
    public void setMessage( String value ) {
        if( !Comparer.equalsString( _message, value ) ) {
            _message = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( RadomeCommandReplyObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._radome = this._radome;
        targetObject._timestamp = this._timestamp;
        targetObject._command = this._command;
        targetObject._status = this._status;
        targetObject._message = this._message;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadomeCommandReplyObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._radome, other._radome ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._command, other._command ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._status, other._status ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._message, other._message ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _radome );
        destination.writeDateTime( _timestamp );
        destination.writeNullableGuid( _command );
        destination.writeInt32( _status );
        destination.writeStringUtf8( _message );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _radome = source.readGuid( );
        _timestamp = source.readDateTime( );
        _command = source.readNullableGuid( );
        _status = source.readInt32( );
        _message = source.readString( );
    }

}
