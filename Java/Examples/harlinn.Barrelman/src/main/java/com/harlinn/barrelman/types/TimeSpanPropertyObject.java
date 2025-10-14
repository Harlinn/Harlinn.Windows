package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TimeSpanPropertyObject extends PropertyObject {

    private TimeSpan _value;

    @Override
    public int getObjectType( ) {
        return Kind.TimeSpanProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TimeSpanPropertyObject( );
    }

    public TimeSpan getValue( ) {
        return _value;
    }
    public void setValue( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeTimeSpan( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readTimeSpan( );
    }

}
