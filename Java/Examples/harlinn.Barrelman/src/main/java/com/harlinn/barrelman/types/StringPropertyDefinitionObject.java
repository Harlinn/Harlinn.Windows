package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class StringPropertyDefinitionObject extends PropertyDefinitionObject {

    private String _defaultValue = "";
    private String _pattern = "";

    @Override
    public int getObjectType( ) {
        return Kind.StringPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new StringPropertyDefinitionObject( );
    }

    public String getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( String value ) {
        if( !Comparer.equalsString( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }

    public String getPattern( ) {
        return _pattern;
    }
    public void setPattern( String value ) {
        if( !Comparer.equalsString( _pattern, value ) ) {
            _pattern = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( StringPropertyDefinitionObject )target;
        targetObject._defaultValue = this._defaultValue;
        targetObject._pattern = this._pattern;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (StringPropertyDefinitionObject)obj;
        if( !Comparer.equalsString( this._defaultValue, other._defaultValue ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._pattern, other._pattern ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _defaultValue );
        destination.writeStringUtf8( _pattern );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readString( );
        _pattern = source.readString( );
    }

}
