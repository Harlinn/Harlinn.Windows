package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandSetWasherObject extends CameraCommandObject {

    public final int KIND = Kind.CameraCommandSetWasher;

    private boolean _enabled = false;

    public CameraCommandSetWasherObject( ) {
    }
    public CameraCommandSetWasherObject( byte objectState, Guid id, long rowVersion, Guid camera, DateTime timestamp, int deviceCommandSourceType, Guid deviceCommandSourceId, Guid reply, boolean enabled ) {
        super( objectState, id, rowVersion, camera, timestamp, deviceCommandSourceType, deviceCommandSourceId, reply );
        this._enabled = enabled;
    }

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandSetWasher;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandSetWasherObject( );
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
        var targetObject = ( CameraCommandSetWasherObject )target;
        targetObject._enabled = this._enabled;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraCommandSetWasherObject)obj;
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
