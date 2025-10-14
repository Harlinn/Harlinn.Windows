package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Int64PropertyDefinitionObject extends PropertyDefinitionObject {

    private long _defaultValue = 0;
    private long _minValue = 0;
    private long _maxValue = 0;

    @Override
    public int getObjectType( ) {
        return Kind.Int64PropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int64PropertyDefinitionObject( );
    }

    public long getDefaultValue( ) {
        return _defaultValue;
    }
    public void setDefaultValue( long value ) {
        if( !Comparer.equalsInt64( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }

    public long getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( long value ) {
        if( !Comparer.equalsInt64( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public long getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( long value ) {
        if( !Comparer.equalsInt64( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _defaultValue );
        destination.writeInt64( _minValue );
        destination.writeInt64( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readInt64( );
        _minValue = source.readInt64( );
        _maxValue = source.readInt64( );
    }

}
