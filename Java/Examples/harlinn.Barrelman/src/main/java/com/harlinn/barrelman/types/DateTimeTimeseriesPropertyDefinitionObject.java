package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class DateTimeTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    private String _minValue = "";
    private String _maxValue = "";

    @Override
    public int getObjectType( ) {
        return Kind.DateTimeTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new DateTimeTimeseriesPropertyDefinitionObject( );
    }

    public String getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( String value ) {
        if( !Comparer.equalsString( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public String getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( String value ) {
        if( !Comparer.equalsString( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _minValue );
        destination.writeStringUtf8( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _minValue = source.readString( );
        _maxValue = source.readString( );
    }

}
