package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt16PropertyObject extends PropertyObject {

    private short _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.UInt16Property;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt16PropertyObject( );
    }

    public short getValue( ) {
        return _value;
    }
    public void setValue( short value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
