package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BytePropertyObject extends PropertyObject {

    private byte _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.ByteProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BytePropertyObject( );
    }

    public byte getValue( ) {
        return _value;
    }
    public void setValue( byte value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
