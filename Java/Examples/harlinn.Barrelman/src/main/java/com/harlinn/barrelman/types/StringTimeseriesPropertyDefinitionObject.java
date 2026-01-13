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

public class StringTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    public final int KIND = Kind.StringTimeseriesPropertyDefinition;

    private String _pattern = "";

    public StringTimeseriesPropertyDefinitionObject( ) {
    }
    public StringTimeseriesPropertyDefinitionObject( byte objectState, Guid id, long rowVersion, Guid elementType, String name, String description, String pattern ) {
        super( objectState, id, rowVersion, elementType, name, description );
        this._pattern = pattern;
    }

    @Override
    public int getObjectType( ) {
        return Kind.StringTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new StringTimeseriesPropertyDefinitionObject( );
    }

    public String getPattern( ) {
        return _pattern;
    }
    public void setPattern( String value ) {
        if( !Comparer.equalsString( _pattern, value ) ) {
            _pattern = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( StringTimeseriesPropertyDefinitionObject )target;
        targetObject._pattern = this._pattern;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (StringTimeseriesPropertyDefinitionObject)obj;
        if( !Comparer.equalsString( this._pattern, other._pattern ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _pattern );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _pattern = source.readString( );
    }

}
