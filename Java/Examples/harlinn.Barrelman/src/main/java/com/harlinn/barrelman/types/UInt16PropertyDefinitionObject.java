package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt16PropertyDefinitionObject extends PropertyDefinitionObject {

    private short _defaultValue = 0;
    private short _minValue = 0;
    private short _maxValue = 0;

    @Override
    public int getObjectType( ) {
        return Kind.UInt16PropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt16PropertyDefinitionObject( );
    }

    public short getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( short value ) {
        if( _defaultValue != value ) {
            this._defaultValue = value;
            onPropertyChanged( );
        }
    }

    public short getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( short value ) {
        if( _minValue != value ) {
            this._minValue = value;
            onPropertyChanged( );
        }
    }

    public short getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( short value ) {
        if( _maxValue != value ) {
            this._maxValue = value;
            onPropertyChanged( );
        }
    }


}
