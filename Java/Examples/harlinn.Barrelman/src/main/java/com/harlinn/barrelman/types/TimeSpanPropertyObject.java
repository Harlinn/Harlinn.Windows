package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TimeSpanPropertyObject extends PropertyObject {

    public final int KIND = Kind.TimeSpanProperty;

    private TimeSpan _value;

    public TimeSpanPropertyObject( ) {
    }
    public TimeSpanPropertyObject( byte objectState, Guid id, long rowVersion, Guid element, Guid definition, TimeSpan value ) {
        super( objectState, id, rowVersion, element, definition );
        this._value = value;
    }

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
        if( !Comparer.equalsTimeSpan( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( TimeSpanPropertyObject )target;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (TimeSpanPropertyObject)obj;
        if( !Comparer.equalsTimeSpan( this._value, other._value ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeTimeSpan( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readTimeSpan( );
    }

}
