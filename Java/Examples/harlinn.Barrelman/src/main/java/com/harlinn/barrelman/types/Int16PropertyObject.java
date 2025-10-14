package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int16PropertyObject extends PropertyObject {

    private short _value = 0;

    @Override
    public int getObjectType( ) {
        return Kind.Int16Property;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int16PropertyObject( );
    }

    public short getValue( ) {
        return _value;
    }
    public void setValue( short value ) {
        if( !Comparer.equalsInt16( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt16( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readInt16( );
    }

}
