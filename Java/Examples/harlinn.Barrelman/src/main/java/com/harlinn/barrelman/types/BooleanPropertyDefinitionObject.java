package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BooleanPropertyDefinitionObject extends PropertyDefinitionObject {

    public final int KIND = Kind.BooleanPropertyDefinition;

    private boolean _defaultValue = false;

    public BooleanPropertyDefinitionObject( ) {
    }
    public BooleanPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, boolean defaultValue ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._defaultValue = defaultValue;
    }

    @Override
    public int getObjectType( ) {
        return Kind.BooleanPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BooleanPropertyDefinitionObject( );
    }

    public boolean getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( boolean value ) {
        if( !Comparer.equalsBoolean( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( BooleanPropertyDefinitionObject )target;
        targetObject._defaultValue = this._defaultValue;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (BooleanPropertyDefinitionObject)obj;
        if( !Comparer.equalsBoolean( this._defaultValue, other._defaultValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeBoolean( _defaultValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readBoolean( );
    }

}
