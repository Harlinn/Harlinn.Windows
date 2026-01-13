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

public class TimeSpanPropertyObject extends PropertyObject {

    public final int KIND = Kind.TimeSpanProperty;

    private TimeSpan _value;

    public TimeSpanPropertyObject( ) {
    }
    public TimeSpanPropertyObject( byte objectState, Guid id, long rowVersion, Guid element, Guid definition, TimeSpan value ) {
        super( objectState, id, rowVersion, element, definition );
        this._value = value;
    }

    @Override
    public int getObjectType( ) {
        return Kind.TimeSpanProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TimeSpanPropertyObject( );
    }

    public TimeSpan getValue( ) {
        return _value;
    }
    public void setValue( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( TimeSpanPropertyObject )target;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (TimeSpanPropertyObject)obj;
        if( !Comparer.equalsTimeSpan( this._value, other._value ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeTimeSpan( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readTimeSpan( );
    }

}
