package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ReferencePropertyObject extends PropertyObject {

    private Guid _value;

    @Override
    public int getObjectType( ) {
        return Kind.ReferenceProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ReferencePropertyObject( );
    }

    public Guid getValue( ) {
        return _value;
    }
    public void setValue( Guid value ) {
        if( !Comparer.equalsNullableGuid( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( ReferencePropertyObject )target;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ReferencePropertyObject)obj;
        if( !Comparer.equalsNullableGuid( this._value, other._value ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readNullableGuid( );
    }

}
