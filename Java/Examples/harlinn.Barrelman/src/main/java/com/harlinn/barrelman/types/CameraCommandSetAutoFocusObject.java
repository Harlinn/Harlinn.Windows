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
        if( _enabled != value ) {
            this._enabled = value;
            onPropertyChanged( );
        }
    }


}
