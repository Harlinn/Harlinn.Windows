package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BinaryPropertyObject extends PropertyObject {

    public final int KIND = Kind.BinaryProperty;

    private byte[] _value = new byte[0];

    public BinaryPropertyObject( ) {
    }
    public BinaryPropertyObject( byte objectState, Guid id, long rowVersion, Guid element, Guid definition, byte[] value ) {
        super( objectState, id, rowVersion, element, definition );
        this._value = value;
    }

    @Override
    public int getObjectType( ) {
        return Kind.BinaryProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BinaryPropertyObject( );
    }

    public byte[] getValue( ) {
        return _value;
    }
    public void setValue( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _value, value ) ) {
            _value = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( BinaryPropertyObject )target;
        targetObject._value = this._value != null ? this._value.clone() : this._value;;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (BinaryPropertyObject)obj;
        if( !Comparer.equalsUInt8Array( this._value, other._value ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt8Array( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readUInt8Array( );
    }

}
