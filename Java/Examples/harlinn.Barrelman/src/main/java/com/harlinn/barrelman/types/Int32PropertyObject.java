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

public class Int32PropertyObject extends PropertyObject {

    public final int KIND = Kind.Int32Property;

    private int _value = 0;

    public Int32PropertyObject( ) {
    }
    public Int32PropertyObject( byte objectState, Guid id, long rowVersion, Guid element, Guid definition, int value ) {
        super( objectState, id, rowVersion, element, definition );
        this._value = value;
    }

    @Override
    public int getObjectType( ) {
        return Kind.Int32Property;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Int32PropertyObject( );
    }

    public int getValue( ) {
        return _value;
    }
    public void setValue( int value ) {
        if( !Comparer.equalsInt32( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( Int32PropertyObject )target;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (Int32PropertyObject)obj;
        if( !Comparer.equalsInt32( this._value, other._value ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _value = source.readInt32( );
    }

}
