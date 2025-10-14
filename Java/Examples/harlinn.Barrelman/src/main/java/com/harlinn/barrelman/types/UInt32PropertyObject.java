package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt32PropertyObject extends PropertyObject {

    private int _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.UInt32Property;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt32PropertyObject( );
    }

    public int getValue( ) {
        return _value;
    }
    public void setValue( int value ) {
        if( !Comparer.equalsUInt32( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt32( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readUInt32( );
    }

}
