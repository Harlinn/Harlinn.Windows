package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class StringPropertyObject extends PropertyObject {

    private String _value = "";

    @Override
    public int getObjectType( ) {
        return Kind.StringProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new StringPropertyObject( );
    }

    public String getValue( ) {
        return _value;
    }
    public void setValue( String value ) {
        if( !Comparer.equalsString( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( StringPropertyObject )target;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (StringPropertyObject)obj;
        if( !Comparer.equalsString( this._value, other._value ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readString( );
    }

}
