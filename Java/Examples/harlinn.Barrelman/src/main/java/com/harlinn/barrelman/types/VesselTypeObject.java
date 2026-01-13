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

public class VesselTypeObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.VesselType;

    private long _rowVersion = 0;
    private String _name = "";
    private int _code = 0;

    public VesselTypeObject( ) {
    }
    public VesselTypeObject( byte objectState, Guid id, long rowVersion, String name, int code ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._name = name;
        this._code = code;
    }

    @Override
    public int getObjectType( ) {
        return Kind.VesselType;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new VesselTypeObject( );
    }

    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
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

    public int getCode( ) {
        return _code;
    }
    public void setCode( int value ) {
        if( !Comparer.equalsInt32( _code, value ) ) {
            _code = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( VesselTypeObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._name = this._name;
        targetObject._code = this._code;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (VesselTypeObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._code, other._code ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeStringUtf8( _name );
        destination.writeInt32( _code );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _name = source.readString( );
        _code = source.readInt32( );
    }

}
