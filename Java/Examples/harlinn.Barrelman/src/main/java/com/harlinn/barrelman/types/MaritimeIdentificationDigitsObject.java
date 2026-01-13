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

public class MaritimeIdentificationDigitsObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.MaritimeIdentificationDigits;

    private long _rowVersion = 0;
    private int _code = 0;
    private Guid _country;

    public MaritimeIdentificationDigitsObject( ) {
    }
    public MaritimeIdentificationDigitsObject( byte objectState, Guid id, long rowVersion, int code, Guid country ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._code = code;
        this._country = country;
    }

    @Override
    public int getObjectType( ) {
        return Kind.MaritimeIdentificationDigits;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MaritimeIdentificationDigitsObject( );
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

    public int getCode( ) {
        return _code;
    }
    public void setCode( int value ) {
        if( !Comparer.equalsInt32( _code, value ) ) {
            _code = value;
            onPropertyChanged( );
        }
    }

    public Guid getCountry( ) {
        return _country;
    }
    public void setCountry( Guid value ) {
        if( !Comparer.equalsGuid( _country, value ) ) {
            _country = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( MaritimeIdentificationDigitsObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._code = this._code;
        targetObject._country = this._country;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (MaritimeIdentificationDigitsObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._code, other._code ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._country, other._country ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeInt32( _code );
        destination.writeGuid( _country );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _code = source.readInt32( );
        _country = source.readGuid( );
    }

}
