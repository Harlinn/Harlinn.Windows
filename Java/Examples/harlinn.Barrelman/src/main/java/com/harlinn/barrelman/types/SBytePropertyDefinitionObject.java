package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SBytePropertyDefinitionObject extends PropertyDefinitionObject {

    private byte _defaultValue = 0;
    private byte _minValue = 0;
    private byte _maxValue = 0;

    @Override
    public int getObjectType( ) {
        return Kind.SBytePropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new SBytePropertyDefinitionObject( );
    }

    public byte getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( byte value ) {
        if( !Comparer.equalsInt8( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }

    public byte getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( byte value ) {
        if( !Comparer.equalsInt8( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public byte getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( byte value ) {
        if( !Comparer.equalsInt8( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( SBytePropertyDefinitionObject )target;
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
        var other = (SBytePropertyDefinitionObject)obj;
        if( !Comparer.equalsInt8( this._defaultValue, other._defaultValue ) ) {
            return false;
        }
        if( !Comparer.equalsInt8( this._minValue, other._minValue ) ) {
            return false;
        }
        if( !Comparer.equalsInt8( this._maxValue, other._maxValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt8( _defaultValue );
        destination.writeInt8( _minValue );
        destination.writeInt8( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readInt8( );
        _minValue = source.readInt8( );
        _maxValue = source.readInt8( );
    }

}
