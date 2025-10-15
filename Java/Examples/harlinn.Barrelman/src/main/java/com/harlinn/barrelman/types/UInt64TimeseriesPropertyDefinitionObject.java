package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class UInt64TimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    private long _minValue = 0;
    private long _maxValue = 0;

    @Override
    public int getObjectType( ) {
        return Kind.UInt64TimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new UInt64TimeseriesPropertyDefinitionObject( );
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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( UInt64TimeseriesPropertyDefinitionObject )target;
        targetObject._minValue = this._minValue;
        targetObject._maxValue = this._maxValue;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (UInt64TimeseriesPropertyDefinitionObject)obj;
        if( !Comparer.equalsInt64( this._minValue, other._minValue ) ) {
            return false;
        }
        if( !Comparer.equalsInt64( this._maxValue, other._maxValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _minValue );
        destination.writeInt64( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _minValue = source.readInt64( );
        _maxValue = source.readInt64( );
    }

}
