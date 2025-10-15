package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class StringTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    private String _pattern = "";

    @Override
    public int getObjectType( ) {
        return Kind.StringTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new StringTimeseriesPropertyDefinitionObject( );
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
        var targetObject = ( StringTimeseriesPropertyDefinitionObject )target;
        targetObject._pattern = this._pattern;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (StringTimeseriesPropertyDefinitionObject)obj;
        if( !Comparer.equalsString( this._pattern, other._pattern ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _pattern );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _pattern = source.readString( );
    }

}
