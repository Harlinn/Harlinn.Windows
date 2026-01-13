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

public class BaseStationObject extends ItemObject {

    public final int KIND = Kind.BaseStation;

    private String _name = "";
    private Guid _type;

    public BaseStationObject( ) {
    }
    public BaseStationObject( byte objectState, Guid id, long rowVersion, String name, Guid type ) {
        super( objectState, id, rowVersion );
        this._name = name;
        this._type = type;
    }

    @Override
    public int getObjectType( ) {
        return Kind.BaseStation;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BaseStationObject( );
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( !Comparer.equalsString( _name, value ) ) {
            _name = value;
            onPropertyChanged( );
        }
    }

    public Guid getType( ) {
        return _type;
    }
    public void setType( Guid value ) {
        if( !Comparer.equalsNullableGuid( _type, value ) ) {
            _type = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( BaseStationObject )target;
        targetObject._name = this._name;
        targetObject._type = this._type;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (BaseStationObject)obj;
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._type, other._type ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _name );
        destination.writeNullableGuid( _type );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _name = source.readString( );
        _type = source.readNullableGuid( );
    }

}
