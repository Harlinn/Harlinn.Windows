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

public class ElementObject extends CatalogElementObject {

    public final int KIND = Kind.Element;

    private Guid _elementType;

    public ElementObject( ) {
    }
    public ElementObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, Guid elementType ) {
        super( objectState, id, rowVersion, catalog, name );
        this._elementType = elementType;
    }

    @Override
    public int getObjectType( ) {
        return Kind.Element;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ElementObject( );
    }

    public Guid getElementType( ) {
        return _elementType;
    }
    public void setElementType( Guid value ) {
        if( !Comparer.equalsNullableGuid( _elementType, value ) ) {
            _elementType = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( ElementObject )target;
        targetObject._elementType = this._elementType;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ElementObject)obj;
        if( !Comparer.equalsNullableGuid( this._elementType, other._elementType ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _elementType );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _elementType = source.readNullableGuid( );
    }

}
