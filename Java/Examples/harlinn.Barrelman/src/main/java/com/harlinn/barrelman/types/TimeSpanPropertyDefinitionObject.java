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

public class TimeSpanPropertyDefinitionObject extends PropertyDefinitionObject {

    public final int KIND = Kind.TimeSpanPropertyDefinition;

    private TimeSpan _defaultValue;
    private TimeSpan _minValue;
    private TimeSpan _maxValue;

    public TimeSpanPropertyDefinitionObject( ) {
    }
    public TimeSpanPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, TimeSpan defaultValue, TimeSpan minValue, TimeSpan maxValue ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._defaultValue = defaultValue;
        this._minValue = minValue;
        this._maxValue = maxValue;
    }

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
        if( !Comparer.equalsTimeSpan( _defaultValue, value ) ) {
            _defaultValue = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getMinValue( ) {
        return _minValue;
    }
    public void setMinValue( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _minValue, value ) ) {
            _minValue = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getMaxValue( ) {
        return _maxValue;
    }
    public void setMaxValue( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _maxValue, value ) ) {
            _maxValue = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( TimeSpanPropertyDefinitionObject )target;
        targetObject._defaultValue = this._defaultValue;
        targetObject._minValue = this._minValue;
        targetObject._maxValue = this._maxValue;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (TimeSpanPropertyDefinitionObject)obj;
        if( !Comparer.equalsTimeSpan( this._defaultValue, other._defaultValue ) ) {
            return false;
        }
        if( !Comparer.equalsTimeSpan( this._minValue, other._minValue ) ) {
            return false;
        }
        if( !Comparer.equalsTimeSpan( this._maxValue, other._maxValue ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeTimeSpan( _defaultValue );
        destination.writeTimeSpan( _minValue );
        destination.writeTimeSpan( _maxValue );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _defaultValue = source.readTimeSpan( );
        _minValue = source.readTimeSpan( );
        _maxValue = source.readTimeSpan( );
    }

}
