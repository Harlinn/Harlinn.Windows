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

public class AisDeviceRawMessageObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.AisDeviceRawMessage;

    private long _rowVersion = 0;
    private Guid _aisDevice;
    private DateTime _timestamp;
    private boolean _isSent = false;
    private String _message = "";

    public AisDeviceRawMessageObject( ) {
    }
    public AisDeviceRawMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime timestamp, boolean isSent, String message ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._aisDevice = aisDevice;
        this._timestamp = timestamp;
        this._isSent = isSent;
        this._message = message;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisDeviceRawMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisDeviceRawMessageObject( );
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

    public Guid getAisDevice( ) {
        return _aisDevice;
    }
    public void setAisDevice( Guid value ) {
        if( !Comparer.equalsGuid( _aisDevice, value ) ) {
            _aisDevice = value;
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

    public boolean getIsSent( ) {
        return _isSent;
    }
    public void setIsSent( boolean value ) {
        if( !Comparer.equalsBoolean( _isSent, value ) ) {
            _isSent = value;
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
        var targetObject = ( AisDeviceRawMessageObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._aisDevice = this._aisDevice;
        targetObject._timestamp = this._timestamp;
        targetObject._isSent = this._isSent;
        targetObject._message = this._message;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisDeviceRawMessageObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._aisDevice, other._aisDevice ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._isSent, other._isSent ) ) {
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
        destination.writeGuid( _aisDevice );
        destination.writeDateTime( _timestamp );
        destination.writeBoolean( _isSent );
        destination.writeStringUtf8( _message );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _aisDevice = source.readGuid( );
        _timestamp = source.readDateTime( );
        _isSent = source.readBoolean( );
        _message = source.readString( );
    }

}
