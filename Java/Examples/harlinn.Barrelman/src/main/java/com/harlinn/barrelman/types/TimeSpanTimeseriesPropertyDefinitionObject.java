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
