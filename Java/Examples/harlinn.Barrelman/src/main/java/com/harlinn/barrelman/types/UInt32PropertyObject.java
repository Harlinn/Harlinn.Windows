package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt32PropertyObject extends PropertyObject {

    private int _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.UInt32Property;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt32PropertyObject( );
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
