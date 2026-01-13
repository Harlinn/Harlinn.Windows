/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class DateTimeTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    public final int KIND = Kind.DateTimeTimeseriesPropertyDefinition;

    private String _minValue = "";
    private String _maxValue = "";

    public DateTimeTimeseriesPropertyDefinitionObject( ) {
    }
    public DateTimeTimeseriesPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, String minValue, String maxValue ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._minValue = minValue;
        this._maxValue = maxValue;
    }

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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( DateTimeTimeseriesPropertyDefinitionObject )target;
        targetObject._minValue = this._minValue;
        targetObject._maxValue = this._maxValue;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (DateTimeTimeseriesPropertyDefinitionObject)obj;
        if( !Comparer.equalsString( this._minValue, other._minValue ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._maxValue, other._maxValue ) ) {
            return false;
        }
        return true;
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
