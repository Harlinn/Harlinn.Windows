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

public class CameraCommandSetFollowedObject extends CameraCommandObject {

    public final int KIND = Kind.CameraCommandSetFollowed;

    private Guid _trackId;
    private int _reason = CameraFollowReason.Alarm;

    public CameraCommandSetFollowedObject( ) {
    }
    public CameraCommandSetFollowedObject( byte objectState, Guid id, long rowVersion, Guid camera, DateTime timestamp, int deviceCommandSourceType, Guid deviceCommandSourceId, Guid reply, Guid trackId, int reason ) {
        super( objectState, id, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        this._trackId = trackId;
        this._reason = reason;
    }

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandSetFollowed;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandSetFollowedObject( );
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

    public int getReason( ) {
        return _reason;
    }
    public void setReason( int value ) {
        if( !Comparer.equalsInt32( _reason, value ) ) {
            _reason = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraCommandSetFollowedObject )target;
        targetObject._trackId = this._trackId;
        targetObject._reason = this._reason;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraCommandSetFollowedObject)obj;
        if( !Comparer.equalsGuid( this._trackId, other._trackId ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._reason, other._reason ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeGuid( _trackId );
        destination.writeInt32( _reason );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _trackId = source.readGuid( );
        _reason = source.readInt32( );
    }

}
