package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TimeSpanTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    private TimeSpan _minValue;
    private TimeSpan _maxValue;

    @Override
    public int getObjectType( ) {
        return Kind.TimeSpanTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TimeSpanTimeseriesPropertyDefinitionObject( );
    }

    public TimeSpan getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( TimeSpanTimeseriesPropertyDefinitionObject )target;
        targetObject._minValue = this._minValue;
        targetObject._maxValue = this._maxValue;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (TimeSpanTimeseriesPropertyDefinitionObject)obj;
        if( !Comparer.equalsTimeSpan( this._minValue, other._minValue ) ) {
            return false;
        }
        if( !Comparer.equalsTimeSpan( this._maxValue, other._maxValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeTimeSpan( _minValue );
        destination.writeTimeSpan( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _minValue = source.readTimeSpan( );
        _maxValue = source.readTimeSpan( );
    }

}
