package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SinglePropertyObject extends PropertyObject {

    private float _value = 0.0f;

    @Override
    public int getObjectType( ) {
        return Kind.SingleProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SinglePropertyObject( );
    }

    public float getValue( ) {
        return _value;
    }
    public void setValue( float value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
