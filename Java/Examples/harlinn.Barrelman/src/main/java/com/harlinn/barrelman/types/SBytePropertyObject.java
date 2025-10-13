package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SBytePropertyObject extends PropertyObject {

    private byte _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.SByteProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SBytePropertyObject( );
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
