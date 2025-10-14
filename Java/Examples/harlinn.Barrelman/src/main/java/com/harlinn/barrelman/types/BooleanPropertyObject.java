package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BooleanPropertyObject extends PropertyObject {

    private boolean _value = false;

    @Override
    public int getObjectType( ) {
        return Kind.BooleanProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BooleanPropertyObject( );
    }

    public boolean getValue( ) {
        return _value;
    }
    public void setValue( boolean value ) {
        if( !Comparer.equalsBoolean( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeBoolean( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readBoolean( );
    }

}
