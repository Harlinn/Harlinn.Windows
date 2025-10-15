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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( NameObject )target;
        targetObject._text = this._text;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (NameObject)obj;
        if( !Comparer.equalsString( this._text, other._text ) ) {
            return false;
        }
        return true;
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
