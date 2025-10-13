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
        if( _enabled != value ) {
            this._enabled = value;
            onPropertyChanged( );
        }
    }


}
