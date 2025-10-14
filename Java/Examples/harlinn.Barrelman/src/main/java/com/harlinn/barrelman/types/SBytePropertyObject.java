package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SBytePropertyObject extends PropertyObject {

    private byte _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.SByteProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SBytePropertyObject( );
    }

    public byte getValue( ) {
        return _value;
    }
    public void setValue( byte value ) {
        if( !Comparer.equalsInt8( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt8( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readInt8( );
    }

}
