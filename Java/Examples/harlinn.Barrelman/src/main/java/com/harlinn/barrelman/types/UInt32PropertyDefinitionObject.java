package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt32PropertyDefinitionObject extends PropertyDefinitionObject {

    public final int KIND = Kind.UInt32PropertyDefinition;

    private int _defaultValue = 0;
    private int _minValue = 0;
    private int _maxValue = 0;

    public UInt32PropertyDefinitionObject( ) {
    }
    public UInt32PropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, int defaultValue, int minValue, int maxValue ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._defaultValue = defaultValue;
        this._minValue = minValue;
        this._maxValue = maxValue;
    }

    @Override
    public int getObjectType( ) {
        return Kind.UInt32PropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt32PropertyDefinitionObject( );
    }

    public int getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( int value ) {
        if( !Comparer.equalsUInt32( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }

    public int getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( int value ) {
        if( !Comparer.equalsUInt32( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public int getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( int value ) {
        if( !Comparer.equalsUInt32( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( UInt32PropertyDefinitionObject )target;
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
        var other = (UInt32PropertyDefinitionObject)obj;
        if( !Comparer.equalsUInt32( this._defaultValue, other._defaultValue ) ) {
            return false;
        }
        if( !Comparer.equalsUInt32( this._minValue, other._minValue ) ) {
            return false;
        }
        if( !Comparer.equalsUInt32( this._maxValue, other._maxValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt32( _defaultValue );
        destination.writeUInt32( _minValue );
        destination.writeUInt32( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readUInt32( );
        _minValue = source.readUInt32( );
        _maxValue = source.readUInt32( );
    }

}
