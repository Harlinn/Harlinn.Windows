package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class DateTimePropertyObject extends PropertyObject {

    private DateTime _value;

    @Override
    public int getObjectType( ) {
        return Kind.DateTimeProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new DateTimePropertyObject( );
    }

    public DateTime getValue( ) {
        return _value;
    }
    public void setValue( DateTime value ) {
        if( !Comparer.equalsDateTime( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeDateTime( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readDateTime( );
    }

}
