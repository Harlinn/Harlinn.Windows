package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GuidPropertyDefinitionObject extends PropertyDefinitionObject {

    public final int KIND = Kind.GuidPropertyDefinition;

    private Guid _defaultValue;

    public GuidPropertyDefinitionObject( ) {
    }
    public GuidPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, Guid defaultValue ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._defaultValue = defaultValue;
    }

    @Override
    public int getObjectType( ) {
        return Kind.GuidPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GuidPropertyDefinitionObject( );
    }

    public Guid getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( Guid value ) {
        if( !Comparer.equalsGuid( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( GuidPropertyDefinitionObject )target;
        targetObject._defaultValue = this._defaultValue;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (GuidPropertyDefinitionObject)obj;
        if( !Comparer.equalsGuid( this._defaultValue, other._defaultValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeGuid( _defaultValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readGuid( );
    }

}
