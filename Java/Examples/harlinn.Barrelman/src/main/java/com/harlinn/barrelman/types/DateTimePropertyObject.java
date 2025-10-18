package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class DateTimePropertyObject extends PropertyObject {

    public final int KIND = Kind.DateTimeProperty;

    private DateTime _value;

    public DateTimePropertyObject( ) {
    }
    public DateTimePropertyObject( byte objectState, Guid id, long rowVersion, Guid element, Guid definition, DateTime value ) {
        super( objectState, id, rowVersion, element, definition );
        this._value = value;
    }

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
        if( !Comparer.equalsDateTime( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( DateTimePropertyObject )target;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (DateTimePropertyObject)obj;
        if( !Comparer.equalsDateTime( this._value, other._value ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeDateTime( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readDateTime( );
    }

}
