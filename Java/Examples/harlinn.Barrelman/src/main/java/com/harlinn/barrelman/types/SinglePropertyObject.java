package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SinglePropertyObject extends PropertyObject {

    public final int KIND = Kind.SingleProperty;

    private float _value = 0.0f;

    public SinglePropertyObject( ) {
    }
    public SinglePropertyObject( byte objectState, Guid id, long rowVersion, Guid element, Guid definition, float value ) {
        super( objectState, id, rowVersion, element, definition );
        this._value = value;
    }

    @Override
    public int getObjectType( ) {
        return Kind.SingleProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SinglePropertyObject( );
    }

    public float getValue( ) {
        return _value;
    }
    public void setValue( float value ) {
        if( !Comparer.equalsSingle( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( SinglePropertyObject )target;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (SinglePropertyObject)obj;
        if( !Comparer.equalsSingle( this._value, other._value ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeSingle( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readSingle( );
    }

}
