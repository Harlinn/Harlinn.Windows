package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class DateTimePropertyDefinitionObject extends PropertyDefinitionObject {

    private String _defaultValue = "";
    private String _minValue = "";
    private String _maxValue = "";

    @Override
    public int getObjectType( ) {
        return Kind.DateTimePropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new DateTimePropertyDefinitionObject( );
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

    public String getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( String value ) {
        if( !Comparer.equalsString( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public String getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( String value ) {
        if( !Comparer.equalsString( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( DateTimePropertyDefinitionObject )target;
        targetObject._defaultValue = this._defaultValue;
        targetObject._minValue = this._minValue;
        targetObject._maxValue = this._maxValue;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (DateTimePropertyDefinitionObject)obj;
        if( !Comparer.equalsString( this._defaultValue, other._defaultValue ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._minValue, other._minValue ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._maxValue, other._maxValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _defaultValue );
        destination.writeStringUtf8( _minValue );
        destination.writeStringUtf8( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readString( );
        _minValue = source.readString( );
        _maxValue = source.readString( );
    }

}
