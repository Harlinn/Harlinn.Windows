package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandSetWiperObject extends CameraCommandObject {

    private boolean _enabled = false;

    @Override
    public int getObjectType( ) {
        return Kind.CameraCommandSetWiper;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CameraCommandSetWiperObject( );
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
