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
