package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TimeSpanPropertyDefinitionObject extends PropertyDefinitionObject {

    private TimeSpan _defaultValue;
    private TimeSpan _minValue;
    private TimeSpan _maxValue;

    @Override
    public int getObjectType( ) {
        return Kind.TimeSpanPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TimeSpanPropertyDefinitionObject( );
    }

    public TimeSpan getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
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
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeTimeSpan( _defaultValue );
        destination.writeTimeSpan( _minValue );
        destination.writeTimeSpan( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readTimeSpan( );
        _minValue = source.readTimeSpan( );
        _maxValue = source.readTimeSpan( );
    }

}
