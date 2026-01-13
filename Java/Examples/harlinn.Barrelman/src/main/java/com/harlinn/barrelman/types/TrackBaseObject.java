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

public abstract class TrackBaseObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.TrackBase;

    private long _rowVersion = 0;
    private Guid _tracker;
    private long _trackNumber = 0;
    private DateTime _timestamp;

    public TrackBaseObject( ) {
    }
    public TrackBaseObject( byte objectState, Guid id, long rowVersion, Guid tracker, long trackNumber, DateTime timestamp ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._tracker = tracker;
        this._trackNumber = trackNumber;
        this._timestamp = timestamp;
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

    public Guid getTracker( ) {
        return _tracker;
    }
    public void setTracker( Guid value ) {
        if( !Comparer.equalsGuid( _tracker, value ) ) {
            _tracker = value;
            onPropertyChanged( );
        }
    }

    public long getTrackNumber( ) {
        return _trackNumber;
    }
    public void setTrackNumber( long value ) {
        if( !Comparer.equalsInt64( _trackNumber, value ) ) {
            _trackNumber = value;
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



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( TrackBaseObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._tracker = this._tracker;
        targetObject._trackNumber = this._trackNumber;
        targetObject._timestamp = this._timestamp;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (TrackBaseObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._tracker, other._tracker ) ) {
            return false;
        }
        if( !Comparer.equalsInt64( this._trackNumber, other._trackNumber ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _tracker );
        destination.writeInt64( _trackNumber );
        destination.writeDateTime( _timestamp );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _tracker = source.readGuid( );
        _trackNumber = source.readInt64( );
        _timestamp = source.readDateTime( );
    }

}
