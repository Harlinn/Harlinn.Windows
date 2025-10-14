package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class NameObject extends IdentityObject {

    private String _text = "";

    @Override
    public int getObjectType( ) {
        return Kind.Name;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new NameObject( );
    }

    public String getText( ) {
        return _text;
    }
    public void setText( String value ) {
        if( !Comparer.equalsString( _text, value ) ) {
            _text = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _text );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _text = source.readString( );
    }

}
