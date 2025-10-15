package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class DoublePropertyDefinitionObject extends PropertyDefinitionObject {

    private double _defaultValue = 0.0;
    private double _minValue = 0.0;
    private double _maxValue = 0.0;

    @Override
    public int getObjectType( ) {
        return Kind.DoublePropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new DoublePropertyDefinitionObject( );
    }

    public double getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( double value ) {
        if( !Comparer.equalsDouble( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }

    public double getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( double value ) {
        if( !Comparer.equalsDouble( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public double getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( double value ) {
        if( !Comparer.equalsDouble( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( DoublePropertyDefinitionObject )target;
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
        var other = (DoublePropertyDefinitionObject)obj;
        if( !Comparer.equalsDouble( this._defaultValue, other._defaultValue ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._minValue, other._minValue ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._maxValue, other._maxValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeDouble( _defaultValue );
        destination.writeDouble( _minValue );
        destination.writeDouble( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readDouble( );
        _minValue = source.readDouble( );
        _maxValue = source.readDouble( );
    }

}
