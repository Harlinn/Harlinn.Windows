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
        if( !Comparer.equalsInt64( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( Int64PropertyObject )target;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (Int64PropertyObject)obj;
        if( !Comparer.equalsInt64( this._value, other._value ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readInt64( );
    }

}
