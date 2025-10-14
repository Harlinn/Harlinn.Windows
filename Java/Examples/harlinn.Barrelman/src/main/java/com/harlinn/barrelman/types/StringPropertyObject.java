package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class StringPropertyObject extends PropertyObject {

    private String _value = "";

    @Override
    public int getObjectType( ) {
        return Kind.StringProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new StringPropertyObject( );
    }

    public String getValue( ) {
        return _value;
    }
    public void setValue( String value ) {
        if( !Comparer.equalsString( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readString( );
    }

}
