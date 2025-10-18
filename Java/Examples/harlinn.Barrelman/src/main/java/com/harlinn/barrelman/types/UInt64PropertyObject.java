package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt64PropertyObject extends PropertyObject {

    public final int KIND = Kind.UInt64Property;

    private long _value = 0;

    public UInt64PropertyObject( ) {
    }
    public UInt64PropertyObject( byte objectState, Guid id, long rowVersion, Guid element, Guid definition, long value ) {
        super( objectState, id, rowVersion, element, definition );
        this._value = value;
    }

    @Override
    public int getObjectType( ) {
        return Kind.UInt64Property;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt64PropertyObject( );
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
        var targetObject = ( UInt64PropertyObject )target;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (UInt64PropertyObject)obj;
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
