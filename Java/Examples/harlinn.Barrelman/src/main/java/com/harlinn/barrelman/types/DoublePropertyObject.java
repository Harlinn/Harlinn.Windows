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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( DoublePropertyObject )target;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (DoublePropertyObject)obj;
        if( !Comparer.equalsDouble( this._value, other._value ) ) {
            return false;
        }
        return true;
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
