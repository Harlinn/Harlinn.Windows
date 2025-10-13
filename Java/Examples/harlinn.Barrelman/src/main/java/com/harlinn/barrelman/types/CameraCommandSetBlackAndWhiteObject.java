package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CameraCommandSetBlackAndWhiteObject extends CameraCommandObject {

    private boolean _enabled = false;

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
        if( _enabled != value ) {
            this._enabled = value;
            onPropertyChanged( );
        }
    }


}
