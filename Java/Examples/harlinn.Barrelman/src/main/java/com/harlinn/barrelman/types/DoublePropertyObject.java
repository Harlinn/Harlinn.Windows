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
        if( !Comparer.equalsDouble( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeDouble( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readDouble( );
    }

}
