package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BooleanPropertyObject extends PropertyObject {

    public final int KIND = Kind.BooleanProperty;

    private boolean _value = false;

    public BooleanPropertyObject( ) {
    }
    public BooleanPropertyObject( byte objectState, Guid id, long rowVersion, Guid element, Guid definition, boolean value ) {
        super( objectState, id, rowVersion, element, definition );
        this._value = value;
    }

    @Override
    public int getObjectType( ) {
        return Kind.BooleanProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BooleanPropertyObject( );
    }

    public boolean getValue( ) {
        return _value;
    }
    public void setValue( boolean value ) {
        if( !Comparer.equalsBoolean( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( BooleanPropertyObject )target;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (BooleanPropertyObject)obj;
        if( !Comparer.equalsBoolean( this._value, other._value ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeBoolean( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readBoolean( );
    }

}
