package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int64TimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    private long _minValue = 0;
    private long _maxValue = 0;

    @Override
    public int getObjectType( ) {
        return Kind.Int64TimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int64TimeseriesPropertyDefinitionObject( );
    }

    public long getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( long value ) {
        if( _minValue != value ) {
            this._minValue = value;
            onPropertyChanged( );
        }
    }

    public long getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( long value ) {
        if( _maxValue != value ) {
            this._maxValue = value;
            onPropertyChanged( );
        }
    }


}
