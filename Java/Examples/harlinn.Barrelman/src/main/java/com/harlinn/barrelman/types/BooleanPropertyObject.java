package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BooleanPropertyObject extends PropertyObject {

    private boolean _value = false;

    @Override
    public int getObjectType( ) {
        return Kind.BooleanProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BooleanPropertyObject( );
    }

    public boolean getValue( ) {
        return _value;
    }
    public void setValue( boolean value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
