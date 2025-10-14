package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BinaryPropertyObject extends PropertyObject {

    private byte[] _value = new byte[0];

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
