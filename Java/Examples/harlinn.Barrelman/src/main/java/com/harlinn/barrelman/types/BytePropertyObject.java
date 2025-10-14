package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BytePropertyObject extends PropertyObject {

    private byte _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.ByteProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BytePropertyObject( );
    }

    public byte getValue( ) {
        return _value;
    }
    public void setValue( byte value ) {
        if( !Comparer.equalsUInt8( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt8( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readUInt8( );
    }

}
