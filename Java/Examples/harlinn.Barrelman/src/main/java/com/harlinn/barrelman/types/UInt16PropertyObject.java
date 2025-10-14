package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt16PropertyObject extends PropertyObject {

    private short _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.UInt16Property;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt16PropertyObject( );
    }

    public short getValue( ) {
        return _value;
    }
    public void setValue( short value ) {
        if( !Comparer.equalsUInt16( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt16( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readUInt16( );
    }

}
