package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class StringPropertyObject extends PropertyObject {

    private String _value = "";

    @Override
    public int getObjectType( ) {
        return Kind.StringProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new StringPropertyObject( );
    }

    public String getValue( ) {
        return _value;
    }
    public void setValue( String value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
