package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandSetAutoFocusObject extends CameraCommandObject {

    private boolean _enabled = false;

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandSetAutoFocus;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandSetAutoFocusObject( );
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
        var targetObject = ( CameraCommandSetAutoFocusObject )target;
        targetObject._enabled = this._enabled;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CameraCommandSetAutoFocusObject)obj;
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
