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

public class ProcessTrackValueResultObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.ProcessTrackValueResult;

    private long _rowVersion = 0;
    private boolean _createdNewTrack = false;
    private Guid _trackId;

    public ProcessTrackValueResultObject( ) {
    }
    public ProcessTrackValueResultObject( byte objectState, Guid id, long rowVersion, boolean createdNewTrack, Guid trackId ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._createdNewTrack = createdNewTrack;
        this._trackId = trackId;
    }

    @Override
    public int getObjectType( ) {
        return Kind.ProcessTrackValueResult;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ProcessTrackValueResultObject( );
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

    public boolean getCreatedNewTrack( ) {
        return _createdNewTrack;
    }
    public void setCreatedNewTrack( boolean value ) {
        if( !Comparer.equalsBoolean( _createdNewTrack, value ) ) {
            _createdNewTrack = value;
            onPropertyChanged( );
        }
    }

    public Guid getTrackId( ) {
        return _trackId;
    }
    public void setTrackId( Guid value ) {
        if( !Comparer.equalsGuid( _trackId, value ) ) {
            _trackId = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( ProcessTrackValueResultObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._createdNewTrack = this._createdNewTrack;
        targetObject._trackId = this._trackId;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ProcessTrackValueResultObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._createdNewTrack, other._createdNewTrack ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._trackId, other._trackId ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeBoolean( _createdNewTrack );
        destination.writeGuid( _trackId );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _createdNewTrack = source.readBoolean( );
        _trackId = source.readGuid( );
    }

}
