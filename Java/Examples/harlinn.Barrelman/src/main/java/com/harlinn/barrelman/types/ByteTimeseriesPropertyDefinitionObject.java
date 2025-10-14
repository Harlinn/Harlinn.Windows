package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ByteTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    private byte _minValue = 0;
    private byte _maxValue = 0;

    @Override
    public int getObjectType( ) {
        return Kind.ByteTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ByteTimeseriesPropertyDefinitionObject( );
    }

    public byte getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( byte value ) {
        if( !Comparer.equalsUInt8( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public byte getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( byte value ) {
        if( !Comparer.equalsUInt8( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt8( _minValue );
        destination.writeUInt8( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _minValue = source.readUInt8( );
        _maxValue = source.readUInt8( );
    }

}
