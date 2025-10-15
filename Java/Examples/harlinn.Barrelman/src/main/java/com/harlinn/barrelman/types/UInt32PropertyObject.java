package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt32PropertyObject extends PropertyObject {

    private int _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.UInt32Property;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt32PropertyObject( );
    }

    public int getValue( ) {
        return _value;
    }
    public void setValue( int value ) {
        if( !Comparer.equalsUInt32( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( UInt32PropertyObject )target;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (UInt32PropertyObject)obj;
        if( !Comparer.equalsUInt32( this._value, other._value ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt32( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readUInt32( );
    }

}
