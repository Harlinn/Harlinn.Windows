package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int32PropertyObject extends PropertyObject {

    private int _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.Int32Property;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int32PropertyObject( );
    }

    public int getValue( ) {
        return _value;
    }
    public void setValue( int value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
