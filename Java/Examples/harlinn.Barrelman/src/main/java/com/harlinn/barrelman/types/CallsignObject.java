package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CallsignObject extends IdentityObject {

    private String _identifier = "";

    @Override
    public int getObjectType( ) {
        return Kind.Callsign;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CallsignObject( );
    }

    public String getIdentifier( ) {
        return _identifier;
    }
    public void setIdentifier( String value ) {
        if( !Comparer.equalsString( _identifier, value ) ) {
            _identifier = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CallsignObject )target;
        targetObject._identifier = this._identifier;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CallsignObject)obj;
        if( !Comparer.equalsString( this._identifier, other._identifier ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _identifier );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _identifier = source.readString( );
    }

}
