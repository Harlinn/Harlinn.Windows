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

public class CameraCommandSetBlackAndWhiteObject extends CameraCommandObject {

    public final int KIND = Kind.CameraCommandSetBlackAndWhite;

    private boolean _enabled = false;

    public CameraCommandSetBlackAndWhiteObject( ) {
    }
    public CameraCommandSetBlackAndWhiteObject( byte objectState, Guid id, long rowVersion, Guid camera, DateTime timestamp, int deviceCommandSourceType, Guid deviceCommandSourceId, Guid reply, boolean enabled ) {
        super( objectState, id, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        this._enabled = enabled;
    }

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandSetBlackAndWhite;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandSetBlackAndWhiteObject( );
    }

    public boolean getEnabled( ) {
        return _enabled;
    }
    public void setEnabled( boolean value ) {
        if( !Comparer.equalsBoolean( _enabled, value ) ) {
            _enabled = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraCommandSetBlackAndWhiteObject )target;
        targetObject._enabled = this._enabled;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraCommandSetBlackAndWhiteObject)obj;
        if( !Comparer.equalsBoolean( this._enabled, other._enabled ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeBoolean( _enabled );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _enabled = source.readBoolean( );
    }

}
