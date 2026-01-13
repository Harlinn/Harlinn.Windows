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

public abstract class AisMessageObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.AisMessage;

    private long _rowVersion = 0;
    private Guid _aisDevice;
    private DateTime _receivedTimestamp;
    private long _messageSequenceNumber = 0;
    private int _repeat = 0;
    private Guid _mmsi;

    public AisMessageObject( ) {
    }
    public AisMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._aisDevice = aisDevice;
        this._receivedTimestamp = receivedTimestamp;
        this._messageSequenceNumber = messageSequenceNumber;
        this._repeat = repeat;
        this._mmsi = mmsi;
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

    public DateTime getReceivedTimestamp( ) {
        return _receivedTimestamp;
    }
    public void setReceivedTimestamp( DateTime value ) {
        if( !Comparer.equalsDateTime( _receivedTimestamp, value ) ) {
            _receivedTimestamp = value;
            onPropertyChanged( );
        }
    }

    public long getMessageSequenceNumber( ) {
        return _messageSequenceNumber;
    }
    public void setMessageSequenceNumber( long value ) {
        if( !Comparer.equalsInt64( _messageSequenceNumber, value ) ) {
            _messageSequenceNumber = value;
            onPropertyChanged( );
        }
    }

    public int getRepeat( ) {
        return _repeat;
    }
    public void setRepeat( int value ) {
        if( !Comparer.equalsInt32( _repeat, value ) ) {
            _repeat = value;
            onPropertyChanged( );
        }
    }

    public Guid getMmsi( ) {
        return _mmsi;
    }
    public void setMmsi( Guid value ) {
        if( !Comparer.equalsNullableGuid( _mmsi, value ) ) {
            _mmsi = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisMessageObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._aisDevice = this._aisDevice;
        targetObject._receivedTimestamp = this._receivedTimestamp;
        targetObject._messageSequenceNumber = this._messageSequenceNumber;
        targetObject._repeat = this._repeat;
        targetObject._mmsi = this._mmsi;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisMessageObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._aisDevice, other._aisDevice ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._receivedTimestamp, other._receivedTimestamp ) ) {
            return false;
        }
        if( !Comparer.equalsInt64( this._messageSequenceNumber, other._messageSequenceNumber ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._repeat, other._repeat ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._mmsi, other._mmsi ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _aisDevice );
        destination.writeDateTime( _receivedTimestamp );
        destination.writeInt64( _messageSequenceNumber );
        destination.writeInt32( _repeat );
        destination.writeNullableGuid( _mmsi );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _aisDevice = source.readGuid( );
        _receivedTimestamp = source.readDateTime( );
        _messageSequenceNumber = source.readInt64( );
        _repeat = source.readInt32( );
        _mmsi = source.readNullableGuid( );
    }

}
