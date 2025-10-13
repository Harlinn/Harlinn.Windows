package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class DoubleTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    private double _minValue = 0.0;
    private double _maxValue = 0.0;

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
        if( _minValue != value ) {
            this._minValue = value;
            onPropertyChanged( );
        }
    }

    public double getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( double value ) {
        if( _maxValue != value ) {
            this._maxValue = value;
            onPropertyChanged( );
        }
    }


}
