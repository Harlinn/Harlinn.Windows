package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class DoublePropertyObject extends PropertyObject {

    private double _value = 0.0;

    @Override
    public int getObjectType( ) {
        return Kind.DoubleProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new DoublePropertyObject( );
    }

    public double getValue( ) {
        return _value;
    }
    public void setValue( double value ) {
        if( _value != value ) {
            this._value = value;
            onPropertyChanged( );
        }
    }


}
