package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class DateTimePropertyObject extends PropertyObject {

    private DateTime _value;

    @Override
    public int getObjectType( ) {
        return Kind.DateTimeProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new DateTimePropertyObject( );
    }

    public DateTime getValue( ) {
        return _value;
    }
    public void setValue( DateTime value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
