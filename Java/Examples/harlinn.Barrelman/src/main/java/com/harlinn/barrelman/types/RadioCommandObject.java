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

public class RadioCommandObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.RadioCommand;

    private long _rowVersion = 0;
    private Guid _radio;
    private DateTime _timestamp;
    private int _deviceCommandSourceType = DeviceCommandSourceType.Unknown;
    private Guid _deviceCommandSourceId;
    private Guid _reply;

    public RadioCommandObject( ) {
    }
    public RadioCommandObject( byte objectState, Guid id, long rowVersion, Guid radio, DateTime timestamp, int deviceCommandSourceType, Guid deviceCommandSourceId, Guid reply ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._radio = radio;
        this._timestamp = timestamp;
        this._deviceCommandSourceType = deviceCommandSourceType;
        this._deviceCommandSourceId = deviceCommandSourceId;
        this._reply = reply;
    }

    @Override
    public int getObjectType( ) {
        return Kind.RadioCommand;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadioCommandObject( );
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

    public Guid getRadio( ) {
        return _radio;
    }
    public void setRadio( Guid value ) {
        if( !Comparer.equalsGuid( _radio, value ) ) {
            _radio = value;
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

    public int getDeviceCommandSourceType( ) {
        return _deviceCommandSourceType;
    }
    public void setDeviceCommandSourceType( int value ) {
        if( !Comparer.equalsInt32( _deviceCommandSourceType, value ) ) {
            _deviceCommandSourceType = value;
            onPropertyChanged( );
        }
    }

    public Guid getDeviceCommandSourceId( ) {
        return _deviceCommandSourceId;
    }
    public void setDeviceCommandSourceId( Guid value ) {
        if( !Comparer.equalsGuid( _deviceCommandSourceId, value ) ) {
            _deviceCommandSourceId = value;
            onPropertyChanged( );
        }
    }

    public Guid getReply( ) {
        return _reply;
    }
    public void setReply( Guid value ) {
        if( !Comparer.equalsNullableGuid( _reply, value ) ) {
            _reply = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( RadioCommandObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._radio = this._radio;
        targetObject._timestamp = this._timestamp;
        targetObject._deviceCommandSourceType = this._deviceCommandSourceType;
        targetObject._deviceCommandSourceId = this._deviceCommandSourceId;
        targetObject._reply = this._reply;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadioCommandObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._radio, other._radio ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._deviceCommandSourceType, other._deviceCommandSourceType ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._deviceCommandSourceId, other._deviceCommandSourceId ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._reply, other._reply ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _radio );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _deviceCommandSourceType );
        destination.writeGuid( _deviceCommandSourceId );
        destination.writeNullableGuid( _reply );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _radio = source.readGuid( );
        _timestamp = source.readDateTime( );
        _deviceCommandSourceType = source.readInt32( );
        _deviceCommandSourceId = source.readGuid( );
        _reply = source.readNullableGuid( );
    }

}
