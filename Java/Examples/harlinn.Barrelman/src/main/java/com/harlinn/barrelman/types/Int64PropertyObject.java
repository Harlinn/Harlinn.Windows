package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int64PropertyObject extends PropertyObject {

    private long _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.Int64Property;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int64PropertyObject( );
    }

    public long getValue( ) {
        return _value;
    }
    public void setValue( long value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
