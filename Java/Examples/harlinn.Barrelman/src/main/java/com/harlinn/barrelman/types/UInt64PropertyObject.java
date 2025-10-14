package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt64PropertyObject extends PropertyObject {

    private long _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.UInt64Property;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt64PropertyObject( );
    }

    public long getValue( ) {
        return _value;
    }
    public void setValue( long value ) {
        if( !Comparer.equalsInt64( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readInt64( );
    }

}
