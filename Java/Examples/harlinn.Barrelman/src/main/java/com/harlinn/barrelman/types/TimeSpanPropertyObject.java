package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TimeSpanPropertyObject extends PropertyObject {

    private TimeSpan _value;

    @Override
    public int getObjectType( ) {
        return Kind.TimeSpanProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TimeSpanPropertyObject( );
    }

    public TimeSpan getValue( ) {
        return _value;
    }
    public void setValue( TimeSpan value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
