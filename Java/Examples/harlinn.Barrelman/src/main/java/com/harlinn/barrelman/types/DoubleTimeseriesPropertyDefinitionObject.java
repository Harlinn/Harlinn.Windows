package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class DoubleTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    public final int KIND = Kind.DoubleTimeseriesPropertyDefinition;

    private double _minValue = 0.0;
    private double _maxValue = 0.0;

    public DoubleTimeseriesPropertyDefinitionObject( ) {
    }
    public DoubleTimeseriesPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, double minValue, double maxValue ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._minValue = minValue;
        this._maxValue = maxValue;
    }

    @Override
    public int getObjectType( ) {
        return Kind.DoubleTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new DoubleTimeseriesPropertyDefinitionObject( );
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
        var targetObject = ( DoubleTimeseriesPropertyDefinitionObject )target;
        targetObject._minValue = this._minValue;
        targetObject._maxValue = this._maxValue;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (DoubleTimeseriesPropertyDefinitionObject)obj;
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
        destination.writeDouble( _minValue );
        destination.writeDouble( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _minValue = source.readDouble( );
        _maxValue = source.readDouble( );
    }

}
