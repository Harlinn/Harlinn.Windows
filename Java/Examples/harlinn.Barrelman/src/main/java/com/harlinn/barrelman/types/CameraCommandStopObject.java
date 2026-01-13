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

public class CameraCommandStopObject extends CameraCommandObject {

    public final int KIND = Kind.CameraCommandStop;

    private boolean _panTilt = false;
    private boolean _zoom = false;

    public CameraCommandStopObject( ) {
    }
    public CameraCommandStopObject( byte objectState, Guid id, long rowVersion, Guid camera, DateTime timestamp, int deviceCommandSourceType, Guid deviceCommandSourceId, Guid reply, boolean panTilt, boolean zoom ) {
        super( objectState, id, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        this._panTilt = panTilt;
        this._zoom = zoom;
    }

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandStop;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandStopObject( );
    }

    public boolean getPanTilt( ) {
        return _panTilt;
    }
    public void setPanTilt( boolean value ) {
        if( !Comparer.equalsBoolean( _panTilt, value ) ) {
            _panTilt = value;
            onPropertyChanged( );
        }
    }

    public boolean getZoom( ) {
        return _zoom;
    }
    public void setZoom( boolean value ) {
        if( !Comparer.equalsBoolean( _zoom, value ) ) {
            _zoom = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CameraCommandStopObject )target;
        targetObject._panTilt = this._panTilt;
        targetObject._zoom = this._zoom;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraCommandStopObject)obj;
        if( !Comparer.equalsBoolean( this._panTilt, other._panTilt ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._zoom, other._zoom ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeBoolean( _panTilt );
        destination.writeBoolean( _zoom );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _panTilt = source.readBoolean( );
        _zoom = source.readBoolean( );
    }

}
