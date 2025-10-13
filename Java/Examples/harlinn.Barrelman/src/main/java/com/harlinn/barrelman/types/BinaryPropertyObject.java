package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BinaryPropertyObject extends PropertyObject {

    private byte[] _value = new byte[0];

    @Override
    public int getObjectType( ) {
        return Kind.BinaryProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BinaryPropertyObject( );
    }

    public byte[] getValue( ) {
        return _value;
    }
    public void setValue( byte[] value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
