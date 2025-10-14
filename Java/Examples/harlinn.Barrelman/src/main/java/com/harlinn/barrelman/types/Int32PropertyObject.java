package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int32PropertyObject extends PropertyObject {

    private int _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.Int32Property;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int32PropertyObject( );
    }

    public int getValue( ) {
        return _value;
    }
    public void setValue( int value ) {
        if( !Comparer.equalsInt32( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readInt32( );
    }

}
