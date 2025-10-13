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
        if( _defaultValue != value ) {
            this._defaultValue = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( TimeSpan value ) {
        if( _minValue != value ) {
            this._minValue = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( TimeSpan value ) {
        if( _maxValue != value ) {
            this._maxValue = value;
            onPropertyChanged( );
        }
    }


}
