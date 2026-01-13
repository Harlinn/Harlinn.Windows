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

public class RadomeStatusTimeseriesObject extends UInt32TimeseriesObject {

    public final int KIND = Kind.RadomeStatusTimeseries;

    private Guid _radome;

    public RadomeStatusTimeseriesObject( ) {
    }
    public RadomeStatusTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid radome ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._radome = radome;
    }

    @Override
    public int getObjectType( ) {
        return Kind.RadomeStatusTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadomeStatusTimeseriesObject( );
    }

    public Guid getRadome( ) {
        return _radome;
    }
    public void setRadome( Guid value ) {
        if( !Comparer.equalsNullableGuid( _radome, value ) ) {
            _radome = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( RadomeStatusTimeseriesObject )target;
        targetObject._radome = this._radome;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadomeStatusTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._radome, other._radome ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _radome );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _radome = source.readNullableGuid( );
    }

}
